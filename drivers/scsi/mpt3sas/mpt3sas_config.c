<शैली गुरु>
/*
 * This module provides common API क्रम accessing firmware configuration pages
 *
 * This code is based on drivers/scsi/mpt3sas/mpt3sas_base.c
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

#समावेश "mpt3sas_base.h"

/* local definitions */

/* Timeout क्रम config page request (in seconds) */
#घोषणा MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT 15

/* Common sgl flags क्रम READING a config page. */
#घोषणा MPT3_CONFIG_COMMON_SGLFLAGS ((MPI2_SGE_FLAGS_SIMPLE_ELEMENT | \
	MPI2_SGE_FLAGS_LAST_ELEMENT | MPI2_SGE_FLAGS_END_OF_BUFFER \
	| MPI2_SGE_FLAGS_END_OF_LIST) << MPI2_SGE_FLAGS_SHIFT)

/* Common sgl flags क्रम WRITING a config page. */
#घोषणा MPT3_CONFIG_COMMON_WRITE_SGLFLAGS ((MPI2_SGE_FLAGS_SIMPLE_ELEMENT | \
	MPI2_SGE_FLAGS_LAST_ELEMENT | MPI2_SGE_FLAGS_END_OF_BUFFER \
	| MPI2_SGE_FLAGS_END_OF_LIST | MPI2_SGE_FLAGS_HOST_TO_IOC) \
	<< MPI2_SGE_FLAGS_SHIFT)

/**
 * काष्ठा config_request - obtain dma memory via routine
 * @sz: size
 * @page: virt poपूर्णांकer
 * @page_dma: phys poपूर्णांकer
 *
 */
काष्ठा config_request अणु
	u16			sz;
	व्योम			*page;
	dma_addr_t		page_dma;
पूर्ण;

/**
 * _config_display_some_debug - debug routine
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @calling_function_name: string pass from calling function
 * @mpi_reply: reply message frame
 * Context: none.
 *
 * Function क्रम displaying debug info helpful when debugging issues
 * in this module.
 */
अटल व्योम
_config_display_some_debug(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid,
	अक्षर *calling_function_name, MPI2DefaultReply_t *mpi_reply)
अणु
	Mpi2ConfigRequest_t *mpi_request;
	अक्षर *desc = शून्य;

	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	चयन (mpi_request->Header.PageType & MPI2_CONFIG_PAGETYPE_MASK) अणु
	हाल MPI2_CONFIG_PAGETYPE_IO_UNIT:
		desc = "io_unit";
		अवरोध;
	हाल MPI2_CONFIG_PAGETYPE_IOC:
		desc = "ioc";
		अवरोध;
	हाल MPI2_CONFIG_PAGETYPE_BIOS:
		desc = "bios";
		अवरोध;
	हाल MPI2_CONFIG_PAGETYPE_RAID_VOLUME:
		desc = "raid_volume";
		अवरोध;
	हाल MPI2_CONFIG_PAGETYPE_MANUFACTURING:
		desc = "manufacturing";
		अवरोध;
	हाल MPI2_CONFIG_PAGETYPE_RAID_PHYSDISK:
		desc = "physdisk";
		अवरोध;
	हाल MPI2_CONFIG_PAGETYPE_EXTENDED:
		चयन (mpi_request->ExtPageType) अणु
		हाल MPI2_CONFIG_EXTPAGETYPE_SAS_IO_UNIT:
			desc = "sas_io_unit";
			अवरोध;
		हाल MPI2_CONFIG_EXTPAGETYPE_SAS_EXPANDER:
			desc = "sas_expander";
			अवरोध;
		हाल MPI2_CONFIG_EXTPAGETYPE_SAS_DEVICE:
			desc = "sas_device";
			अवरोध;
		हाल MPI2_CONFIG_EXTPAGETYPE_SAS_PHY:
			desc = "sas_phy";
			अवरोध;
		हाल MPI2_CONFIG_EXTPAGETYPE_LOG:
			desc = "log";
			अवरोध;
		हाल MPI2_CONFIG_EXTPAGETYPE_ENCLOSURE:
			desc = "enclosure";
			अवरोध;
		हाल MPI2_CONFIG_EXTPAGETYPE_RAID_CONFIG:
			desc = "raid_config";
			अवरोध;
		हाल MPI2_CONFIG_EXTPAGETYPE_DRIVER_MAPPING:
			desc = "driver_mapping";
			अवरोध;
		हाल MPI2_CONFIG_EXTPAGETYPE_SAS_PORT:
			desc = "sas_port";
			अवरोध;
		हाल MPI2_CONFIG_EXTPAGETYPE_EXT_MANUFACTURING:
			desc = "ext_manufacturing";
			अवरोध;
		हाल MPI2_CONFIG_EXTPAGETYPE_PCIE_IO_UNIT:
			desc = "pcie_io_unit";
			अवरोध;
		हाल MPI2_CONFIG_EXTPAGETYPE_PCIE_SWITCH:
			desc = "pcie_switch";
			अवरोध;
		हाल MPI2_CONFIG_EXTPAGETYPE_PCIE_DEVICE:
			desc = "pcie_device";
			अवरोध;
		हाल MPI2_CONFIG_EXTPAGETYPE_PCIE_LINK:
			desc = "pcie_link";
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (!desc)
		वापस;

	ioc_info(ioc, "%s: %s(%d), action(%d), form(0x%08x), smid(%d)\n",
		 calling_function_name, desc,
		 mpi_request->Header.PageNumber, mpi_request->Action,
		 le32_to_cpu(mpi_request->PageAddress), smid);

	अगर (!mpi_reply)
		वापस;

	अगर (mpi_reply->IOCStatus || mpi_reply->IOCLogInfo)
		ioc_info(ioc, "\tiocstatus(0x%04x), loginfo(0x%08x)\n",
			 le16_to_cpu(mpi_reply->IOCStatus),
			 le32_to_cpu(mpi_reply->IOCLogInfo));
पूर्ण

/**
 * _config_alloc_config_dma_memory - obtain physical memory
 * @ioc: per adapter object
 * @mem: काष्ठा config_request
 *
 * A wrapper क्रम obtaining dma-able memory क्रम config page request.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_config_alloc_config_dma_memory(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा config_request *mem)
अणु
	पूर्णांक r = 0;

	अगर (mem->sz > ioc->config_page_sz) अणु
		mem->page = dma_alloc_coherent(&ioc->pdev->dev, mem->sz,
		    &mem->page_dma, GFP_KERNEL);
		अगर (!mem->page) अणु
			ioc_err(ioc, "%s: dma_alloc_coherent failed asking for (%d) bytes!!\n",
				__func__, mem->sz);
			r = -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु /* use पंचांगp buffer अगर less than 512 bytes */
		mem->page = ioc->config_page;
		mem->page_dma = ioc->config_page_dma;
	पूर्ण
	ioc->config_vaddr = mem->page;
	वापस r;
पूर्ण

/**
 * _config_मुक्त_config_dma_memory - wrapper to मुक्त the memory
 * @ioc: per adapter object
 * @mem: काष्ठा config_request
 *
 * A wrapper to मुक्त dma-able memory when using _config_alloc_config_dma_memory.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल व्योम
_config_मुक्त_config_dma_memory(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा config_request *mem)
अणु
	अगर (mem->sz > ioc->config_page_sz)
		dma_मुक्त_coherent(&ioc->pdev->dev, mem->sz, mem->page,
		    mem->page_dma);
पूर्ण

/**
 * mpt3sas_config_करोne - config page completion routine
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @msix_index: MSIX table index supplied by the OS
 * @reply: reply message frame(lower 32bit addr)
 * Context: none.
 *
 * The callback handler when using _config_request.
 *
 * Return: 1 meaning mf should be मुक्तd from _base_पूर्णांकerrupt
 *         0 means the mf is मुक्तd from this function.
 */
u8
mpt3sas_config_करोne(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid, u8 msix_index,
	u32 reply)
अणु
	MPI2DefaultReply_t *mpi_reply;

	अगर (ioc->config_cmds.status == MPT3_CMD_NOT_USED)
		वापस 1;
	अगर (ioc->config_cmds.smid != smid)
		वापस 1;
	ioc->config_cmds.status |= MPT3_CMD_COMPLETE;
	mpi_reply =  mpt3sas_base_get_reply_virt_addr(ioc, reply);
	अगर (mpi_reply) अणु
		ioc->config_cmds.status |= MPT3_CMD_REPLY_VALID;
		स_नकल(ioc->config_cmds.reply, mpi_reply,
		    mpi_reply->MsgLength*4);
	पूर्ण
	ioc->config_cmds.status &= ~MPT3_CMD_PENDING;
	अगर (ioc->logging_level & MPT_DEBUG_CONFIG)
		_config_display_some_debug(ioc, smid, "config_done", mpi_reply);
	ioc->config_cmds.smid = अच_लघु_उच्च;
	complete(&ioc->config_cmds.करोne);
	वापस 1;
पूर्ण

/**
 * _config_request - मुख्य routine क्रम sending config page requests
 * @ioc: per adapter object
 * @mpi_request: request message frame
 * @mpi_reply: reply mf payload वापसed from firmware
 * @समयout: समयout in seconds
 * @config_page: contents of the config page
 * @config_page_sz: size of config page
 * Context: sleep
 *
 * A generic API क्रम config page requests to firmware.
 *
 * The ioc->config_cmds.status flag should be MPT3_CMD_NOT_USED beक्रमe calling
 * this API.
 *
 * The callback index is set inside `ioc->config_cb_idx.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_config_request(काष्ठा MPT3SAS_ADAPTER *ioc, Mpi2ConfigRequest_t
	*mpi_request, Mpi2ConfigReply_t *mpi_reply, पूर्णांक समयout,
	व्योम *config_page, u16 config_page_sz)
अणु
	u16 smid;
	Mpi2ConfigRequest_t *config_request;
	पूर्णांक r;
	u8 retry_count, issue_host_reset = 0;
	काष्ठा config_request mem;
	u32 ioc_status = अच_पूर्णांक_उच्च;

	mutex_lock(&ioc->config_cmds.mutex);
	अगर (ioc->config_cmds.status != MPT3_CMD_NOT_USED) अणु
		ioc_err(ioc, "%s: config_cmd in use\n", __func__);
		mutex_unlock(&ioc->config_cmds.mutex);
		वापस -EAGAIN;
	पूर्ण

	retry_count = 0;
	स_रखो(&mem, 0, माप(काष्ठा config_request));

	mpi_request->VF_ID = 0; /* TODO */
	mpi_request->VP_ID = 0;

	अगर (config_page) अणु
		mpi_request->Header.PageVersion = mpi_reply->Header.PageVersion;
		mpi_request->Header.PageNumber = mpi_reply->Header.PageNumber;
		mpi_request->Header.PageType = mpi_reply->Header.PageType;
		mpi_request->Header.PageLength = mpi_reply->Header.PageLength;
		mpi_request->ExtPageLength = mpi_reply->ExtPageLength;
		mpi_request->ExtPageType = mpi_reply->ExtPageType;
		अगर (mpi_request->Header.PageLength)
			mem.sz = mpi_request->Header.PageLength * 4;
		अन्यथा
			mem.sz = le16_to_cpu(mpi_reply->ExtPageLength) * 4;
		r = _config_alloc_config_dma_memory(ioc, &mem);
		अगर (r != 0)
			जाओ out;
		अगर (mpi_request->Action ==
		    MPI2_CONFIG_ACTION_PAGE_WRITE_CURRENT ||
		    mpi_request->Action ==
		    MPI2_CONFIG_ACTION_PAGE_WRITE_NVRAM) अणु
			ioc->base_add_sg_single(&mpi_request->PageBufferSGE,
			    MPT3_CONFIG_COMMON_WRITE_SGLFLAGS | mem.sz,
			    mem.page_dma);
			स_नकल(mem.page, config_page, min_t(u16, mem.sz,
			    config_page_sz));
		पूर्ण अन्यथा अणु
			स_रखो(config_page, 0, config_page_sz);
			ioc->base_add_sg_single(&mpi_request->PageBufferSGE,
			    MPT3_CONFIG_COMMON_SGLFLAGS | mem.sz, mem.page_dma);
			स_रखो(mem.page, 0, min_t(u16, mem.sz, config_page_sz));
		पूर्ण
	पूर्ण

 retry_config:
	अगर (retry_count) अणु
		अगर (retry_count > 2) अणु /* attempt only 2 retries */
			r = -EFAULT;
			जाओ मुक्त_mem;
		पूर्ण
		ioc_info(ioc, "%s: attempting retry (%d)\n",
			 __func__, retry_count);
	पूर्ण

	r = mpt3sas_रुको_क्रम_ioc(ioc, MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT);
	अगर (r)
		जाओ मुक्त_mem;

	smid = mpt3sas_base_get_smid(ioc, ioc->config_cb_idx);
	अगर (!smid) अणु
		ioc_err(ioc, "%s: failed obtaining a smid\n", __func__);
		ioc->config_cmds.status = MPT3_CMD_NOT_USED;
		r = -EAGAIN;
		जाओ मुक्त_mem;
	पूर्ण

	r = 0;
	स_रखो(ioc->config_cmds.reply, 0, माप(Mpi2ConfigReply_t));
	ioc->config_cmds.status = MPT3_CMD_PENDING;
	config_request = mpt3sas_base_get_msg_frame(ioc, smid);
	ioc->config_cmds.smid = smid;
	स_नकल(config_request, mpi_request, माप(Mpi2ConfigRequest_t));
	अगर (ioc->logging_level & MPT_DEBUG_CONFIG)
		_config_display_some_debug(ioc, smid, "config_request", शून्य);
	init_completion(&ioc->config_cmds.करोne);
	ioc->put_smid_शेष(ioc, smid);
	रुको_क्रम_completion_समयout(&ioc->config_cmds.करोne, समयout*HZ);
	अगर (!(ioc->config_cmds.status & MPT3_CMD_COMPLETE)) अणु
		अगर (!(ioc->logging_level & MPT_DEBUG_CONFIG))
			_config_display_some_debug(ioc,
			    smid, "config_request", शून्य);
		ioc_err(ioc, "%s: command timeout\n", __func__);
		mpt3sas_base_check_cmd_समयout(ioc, ioc->config_cmds.status,
				mpi_request, माप(Mpi2ConfigRequest_t) / 4);
		retry_count++;
		अगर (ioc->config_cmds.smid == smid)
			mpt3sas_base_मुक्त_smid(ioc, smid);
		अगर ((ioc->shost_recovery) || (ioc->config_cmds.status &
		    MPT3_CMD_RESET) || ioc->pci_error_recovery)
			जाओ retry_config;
		issue_host_reset = 1;
		r = -EFAULT;
		जाओ मुक्त_mem;
	पूर्ण

	अगर (ioc->config_cmds.status & MPT3_CMD_REPLY_VALID) अणु
		स_नकल(mpi_reply, ioc->config_cmds.reply,
		    माप(Mpi2ConfigReply_t));

		/* Reply Frame Sanity Checks to workaround FW issues */
		अगर ((mpi_request->Header.PageType & 0xF) !=
		    (mpi_reply->Header.PageType & 0xF)) अणु
			अगर (!(ioc->logging_level & MPT_DEBUG_CONFIG))
				_config_display_some_debug(ioc,
				    smid, "config_request", शून्य);
			_debug_dump_mf(mpi_request, ioc->request_sz/4);
			_debug_dump_reply(mpi_reply, ioc->reply_sz/4);
			panic("%s: %s: Firmware BUG: mpi_reply mismatch: Requested PageType(0x%02x) Reply PageType(0x%02x)\n",
			      ioc->name, __func__,
			      mpi_request->Header.PageType & 0xF,
			      mpi_reply->Header.PageType & 0xF);
		पूर्ण

		अगर (((mpi_request->Header.PageType & 0xF) ==
		    MPI2_CONFIG_PAGETYPE_EXTENDED) &&
		    mpi_request->ExtPageType != mpi_reply->ExtPageType) अणु
			अगर (!(ioc->logging_level & MPT_DEBUG_CONFIG))
				_config_display_some_debug(ioc,
				    smid, "config_request", शून्य);
			_debug_dump_mf(mpi_request, ioc->request_sz/4);
			_debug_dump_reply(mpi_reply, ioc->reply_sz/4);
			panic("%s: %s: Firmware BUG: mpi_reply mismatch: Requested ExtPageType(0x%02x) Reply ExtPageType(0x%02x)\n",
			      ioc->name, __func__,
			      mpi_request->ExtPageType,
			      mpi_reply->ExtPageType);
		पूर्ण
		ioc_status = le16_to_cpu(mpi_reply->IOCStatus)
		    & MPI2_IOCSTATUS_MASK;
	पूर्ण

	अगर (retry_count)
		ioc_info(ioc, "%s: retry (%d) completed!!\n",
			 __func__, retry_count);

	अगर ((ioc_status == MPI2_IOCSTATUS_SUCCESS) &&
	    config_page && mpi_request->Action ==
	    MPI2_CONFIG_ACTION_PAGE_READ_CURRENT) अणु
		u8 *p = (u8 *)mem.page;

		/* Config Page Sanity Checks to workaround FW issues */
		अगर (p) अणु
			अगर ((mpi_request->Header.PageType & 0xF) !=
			    (p[3] & 0xF)) अणु
				अगर (!(ioc->logging_level & MPT_DEBUG_CONFIG))
					_config_display_some_debug(ioc,
					    smid, "config_request", शून्य);
				_debug_dump_mf(mpi_request, ioc->request_sz/4);
				_debug_dump_reply(mpi_reply, ioc->reply_sz/4);
				_debug_dump_config(p, min_t(u16, mem.sz,
				    config_page_sz)/4);
				panic("%s: %s: Firmware BUG: config page mismatch: Requested PageType(0x%02x) Reply PageType(0x%02x)\n",
				      ioc->name, __func__,
				      mpi_request->Header.PageType & 0xF,
				      p[3] & 0xF);
			पूर्ण

			अगर (((mpi_request->Header.PageType & 0xF) ==
			    MPI2_CONFIG_PAGETYPE_EXTENDED) &&
			    (mpi_request->ExtPageType != p[6])) अणु
				अगर (!(ioc->logging_level & MPT_DEBUG_CONFIG))
					_config_display_some_debug(ioc,
					    smid, "config_request", शून्य);
				_debug_dump_mf(mpi_request, ioc->request_sz/4);
				_debug_dump_reply(mpi_reply, ioc->reply_sz/4);
				_debug_dump_config(p, min_t(u16, mem.sz,
				    config_page_sz)/4);
				panic("%s: %s: Firmware BUG: config page mismatch: Requested ExtPageType(0x%02x) Reply ExtPageType(0x%02x)\n",
				      ioc->name, __func__,
				      mpi_request->ExtPageType, p[6]);
			पूर्ण
		पूर्ण
		स_नकल(config_page, mem.page, min_t(u16, mem.sz,
		    config_page_sz));
	पूर्ण

 मुक्त_mem:
	अगर (config_page)
		_config_मुक्त_config_dma_memory(ioc, &mem);
 out:
	ioc->config_cmds.status = MPT3_CMD_NOT_USED;
	mutex_unlock(&ioc->config_cmds.mutex);

	अगर (issue_host_reset)
		mpt3sas_base_hard_reset_handler(ioc, FORCE_BIG_HAMMER);
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_manufacturing_pg0 - obtain manufacturing page 0
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_manufacturing_pg0(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2ManufacturingPage0_t *config_page)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_MANUFACTURING;
	mpi_request.Header.PageNumber = 0;
	mpi_request.Header.PageVersion = MPI2_MANUFACTURING0_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_manufacturing_pg7 - obtain manufacturing page 7
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * @sz: size of buffer passed in config_page
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_manufacturing_pg7(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2ManufacturingPage7_t *config_page,
	u16 sz)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_MANUFACTURING;
	mpi_request.Header.PageNumber = 7;
	mpi_request.Header.PageVersion = MPI2_MANUFACTURING7_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    sz);
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_manufacturing_pg10 - obtain manufacturing page 10
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_manufacturing_pg10(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply,
	काष्ठा Mpi2ManufacturingPage10_t *config_page)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_MANUFACTURING;
	mpi_request.Header.PageNumber = 10;
	mpi_request.Header.PageVersion = MPI2_MANUFACTURING0_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_manufacturing_pg11 - obtain manufacturing page 11
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_manufacturing_pg11(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply,
	काष्ठा Mpi2ManufacturingPage11_t *config_page)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_MANUFACTURING;
	mpi_request.Header.PageNumber = 11;
	mpi_request.Header.PageVersion = MPI2_MANUFACTURING0_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_set_manufacturing_pg11 - set manufacturing page 11
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_set_manufacturing_pg11(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply,
	काष्ठा Mpi2ManufacturingPage11_t *config_page)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_MANUFACTURING;
	mpi_request.Header.PageNumber = 11;
	mpi_request.Header.PageVersion = MPI2_MANUFACTURING0_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_WRITE_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_bios_pg2 - obtain bios page 2
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_bios_pg2(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2BiosPage2_t *config_page)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_BIOS;
	mpi_request.Header.PageNumber = 2;
	mpi_request.Header.PageVersion = MPI2_BIOSPAGE2_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_bios_pg3 - obtain bios page 3
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_bios_pg3(काष्ठा MPT3SAS_ADAPTER *ioc, Mpi2ConfigReply_t
	*mpi_reply, Mpi2BiosPage3_t *config_page)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_BIOS;
	mpi_request.Header.PageNumber = 3;
	mpi_request.Header.PageVersion = MPI2_BIOSPAGE3_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_iounit_pg0 - obtain iounit page 0
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_iounit_pg0(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2IOUnitPage0_t *config_page)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_IO_UNIT;
	mpi_request.Header.PageNumber = 0;
	mpi_request.Header.PageVersion = MPI2_IOUNITPAGE0_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_iounit_pg1 - obtain iounit page 1
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_iounit_pg1(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2IOUnitPage1_t *config_page)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_IO_UNIT;
	mpi_request.Header.PageNumber = 1;
	mpi_request.Header.PageVersion = MPI2_IOUNITPAGE1_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_set_iounit_pg1 - set iounit page 1
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_set_iounit_pg1(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2IOUnitPage1_t *config_page)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_IO_UNIT;
	mpi_request.Header.PageNumber = 1;
	mpi_request.Header.PageVersion = MPI2_IOUNITPAGE1_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_WRITE_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_iounit_pg3 - obtain iounit page 3
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * @sz: size of buffer passed in config_page
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_iounit_pg3(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2IOUnitPage3_t *config_page, u16 sz)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_IO_UNIT;
	mpi_request.Header.PageNumber = 3;
	mpi_request.Header.PageVersion = MPI2_IOUNITPAGE3_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page, sz);
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_iounit_pg8 - obtain iounit page 8
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_iounit_pg8(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2IOUnitPage8_t *config_page)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_IO_UNIT;
	mpi_request.Header.PageNumber = 8;
	mpi_request.Header.PageVersion = MPI2_IOUNITPAGE8_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_ioc_pg8 - obtain ioc page 8
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_ioc_pg8(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2IOCPage8_t *config_page)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_IOC;
	mpi_request.Header.PageNumber = 8;
	mpi_request.Header.PageVersion = MPI2_IOCPAGE8_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण
/**
 * mpt3sas_config_get_ioc_pg1 - obtain ioc page 1
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_ioc_pg1(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2IOCPage1_t *config_page)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_IOC;
	mpi_request.Header.PageNumber = 1;
	mpi_request.Header.PageVersion = MPI2_IOCPAGE8_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_set_ioc_pg1 - modअगरy ioc page 1
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_set_ioc_pg1(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2IOCPage1_t *config_page)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_IOC;
	mpi_request.Header.PageNumber = 1;
	mpi_request.Header.PageVersion = MPI2_IOCPAGE8_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_WRITE_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_sas_device_pg0 - obtain sas device page 0
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * @क्रमm: GET_NEXT_HANDLE or HANDLE
 * @handle: device handle
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_sas_device_pg0(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2SasDevicePage0_t *config_page,
	u32 क्रमm, u32 handle)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_SAS_DEVICE;
	mpi_request.Header.PageVersion = MPI2_SASDEVICE0_PAGEVERSION;
	mpi_request.Header.PageNumber = 0;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.PageAddress = cpu_to_le32(क्रमm | handle);
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_sas_device_pg1 - obtain sas device page 1
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * @क्रमm: GET_NEXT_HANDLE or HANDLE
 * @handle: device handle
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_sas_device_pg1(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2SasDevicePage1_t *config_page,
	u32 क्रमm, u32 handle)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_SAS_DEVICE;
	mpi_request.Header.PageVersion = MPI2_SASDEVICE1_PAGEVERSION;
	mpi_request.Header.PageNumber = 1;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.PageAddress = cpu_to_le32(क्रमm | handle);
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_pcie_device_pg0 - obtain pcie device page 0
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * @क्रमm: GET_NEXT_HANDLE or HANDLE
 * @handle: device handle
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_pcie_device_pg0(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi26PCIeDevicePage0_t *config_page,
	u32 क्रमm, u32 handle)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_PCIE_DEVICE;
	mpi_request.Header.PageVersion = MPI26_PCIEDEVICE0_PAGEVERSION;
	mpi_request.Header.PageNumber = 0;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
			MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.PageAddress = cpu_to_le32(क्रमm | handle);
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
			MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
			माप(*config_page));
out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_pcie_device_pg2 - obtain pcie device page 2
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * @क्रमm: GET_NEXT_HANDLE or HANDLE
 * @handle: device handle
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_pcie_device_pg2(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi26PCIeDevicePage2_t *config_page,
	u32 क्रमm, u32 handle)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_PCIE_DEVICE;
	mpi_request.Header.PageVersion = MPI26_PCIEDEVICE2_PAGEVERSION;
	mpi_request.Header.PageNumber = 2;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
			MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.PageAddress = cpu_to_le32(क्रमm | handle);
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
			MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
			माप(*config_page));
out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_number_hba_phys - obtain number of phys on the host
 * @ioc: per adapter object
 * @num_phys: poपूर्णांकer वापसed with the number of phys
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_number_hba_phys(काष्ठा MPT3SAS_ADAPTER *ioc, u8 *num_phys)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;
	u16 ioc_status;
	Mpi2ConfigReply_t mpi_reply;
	Mpi2SasIOUnitPage0_t config_page;

	*num_phys = 0;
	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_SAS_IO_UNIT;
	mpi_request.Header.PageNumber = 0;
	mpi_request.Header.PageVersion = MPI2_SASIOUNITPAGE0_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, &mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, &mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, &config_page,
	    माप(Mpi2SasIOUnitPage0_t));
	अगर (!r) अणु
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		अगर (ioc_status == MPI2_IOCSTATUS_SUCCESS)
			*num_phys = config_page.NumPhys;
	पूर्ण
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_sas_iounit_pg0 - obtain sas iounit page 0
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * @sz: size of buffer passed in config_page
 * Context: sleep.
 *
 * Calling function should call config_get_number_hba_phys prior to
 * this function, so enough memory is allocated क्रम config_page.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_sas_iounit_pg0(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2SasIOUnitPage0_t *config_page,
	u16 sz)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_SAS_IO_UNIT;
	mpi_request.Header.PageNumber = 0;
	mpi_request.Header.PageVersion = MPI2_SASIOUNITPAGE0_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page, sz);
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_sas_iounit_pg1 - obtain sas iounit page 1
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * @sz: size of buffer passed in config_page
 * Context: sleep.
 *
 * Calling function should call config_get_number_hba_phys prior to
 * this function, so enough memory is allocated क्रम config_page.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_sas_iounit_pg1(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2SasIOUnitPage1_t *config_page,
	u16 sz)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_SAS_IO_UNIT;
	mpi_request.Header.PageNumber = 1;
	mpi_request.Header.PageVersion = MPI2_SASIOUNITPAGE1_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page, sz);
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_set_sas_iounit_pg1 - send sas iounit page 1
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * @sz: size of buffer passed in config_page
 * Context: sleep.
 *
 * Calling function should call config_get_number_hba_phys prior to
 * this function, so enough memory is allocated क्रम config_page.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_set_sas_iounit_pg1(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2SasIOUnitPage1_t *config_page,
	u16 sz)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_SAS_IO_UNIT;
	mpi_request.Header.PageNumber = 1;
	mpi_request.Header.PageVersion = MPI2_SASIOUNITPAGE1_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_WRITE_CURRENT;
	_config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page, sz);
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_WRITE_NVRAM;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page, sz);
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_expander_pg0 - obtain expander page 0
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * @क्रमm: GET_NEXT_HANDLE or HANDLE
 * @handle: expander handle
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_expander_pg0(काष्ठा MPT3SAS_ADAPTER *ioc, Mpi2ConfigReply_t
	*mpi_reply, Mpi2ExpanderPage0_t *config_page, u32 क्रमm, u32 handle)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_SAS_EXPANDER;
	mpi_request.Header.PageNumber = 0;
	mpi_request.Header.PageVersion = MPI2_SASEXPANDER0_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.PageAddress = cpu_to_le32(क्रमm | handle);
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_expander_pg1 - obtain expander page 1
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * @phy_number: phy number
 * @handle: expander handle
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_expander_pg1(काष्ठा MPT3SAS_ADAPTER *ioc, Mpi2ConfigReply_t
	*mpi_reply, Mpi2ExpanderPage1_t *config_page, u32 phy_number,
	u16 handle)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_SAS_EXPANDER;
	mpi_request.Header.PageNumber = 1;
	mpi_request.Header.PageVersion = MPI2_SASEXPANDER1_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.PageAddress =
	    cpu_to_le32(MPI2_SAS_EXPAND_PGAD_FORM_HNDL_PHY_NUM |
	    (phy_number << MPI2_SAS_EXPAND_PGAD_PHYNUM_SHIFT) | handle);
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_enclosure_pg0 - obtain enclosure page 0
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * @क्रमm: GET_NEXT_HANDLE or HANDLE
 * @handle: expander handle
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_enclosure_pg0(काष्ठा MPT3SAS_ADAPTER *ioc, Mpi2ConfigReply_t
	*mpi_reply, Mpi2SasEnclosurePage0_t *config_page, u32 क्रमm, u32 handle)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_ENCLOSURE;
	mpi_request.Header.PageNumber = 0;
	mpi_request.Header.PageVersion = MPI2_SASENCLOSURE0_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.PageAddress = cpu_to_le32(क्रमm | handle);
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_phy_pg0 - obtain phy page 0
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * @phy_number: phy number
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_phy_pg0(काष्ठा MPT3SAS_ADAPTER *ioc, Mpi2ConfigReply_t
	*mpi_reply, Mpi2SasPhyPage0_t *config_page, u32 phy_number)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_SAS_PHY;
	mpi_request.Header.PageNumber = 0;
	mpi_request.Header.PageVersion = MPI2_SASPHY0_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.PageAddress =
	    cpu_to_le32(MPI2_SAS_PHY_PGAD_FORM_PHY_NUMBER | phy_number);
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_phy_pg1 - obtain phy page 1
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * @phy_number: phy number
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_phy_pg1(काष्ठा MPT3SAS_ADAPTER *ioc, Mpi2ConfigReply_t
	*mpi_reply, Mpi2SasPhyPage1_t *config_page, u32 phy_number)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_SAS_PHY;
	mpi_request.Header.PageNumber = 1;
	mpi_request.Header.PageVersion = MPI2_SASPHY1_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.PageAddress =
	    cpu_to_le32(MPI2_SAS_PHY_PGAD_FORM_PHY_NUMBER | phy_number);
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_raid_volume_pg1 - obtain raid volume page 1
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * @क्रमm: GET_NEXT_HANDLE or HANDLE
 * @handle: volume handle
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_raid_volume_pg1(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2RaidVolPage1_t *config_page, u32 क्रमm,
	u32 handle)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_RAID_VOLUME;
	mpi_request.Header.PageNumber = 1;
	mpi_request.Header.PageVersion = MPI2_RAIDVOLPAGE1_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.PageAddress = cpu_to_le32(क्रमm | handle);
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_number_pds - obtain number of phys disk asचिन्हित to volume
 * @ioc: per adapter object
 * @handle: volume handle
 * @num_pds: वापसs pds count
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_number_pds(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle,
	u8 *num_pds)
अणु
	Mpi2ConfigRequest_t mpi_request;
	Mpi2RaidVolPage0_t config_page;
	Mpi2ConfigReply_t mpi_reply;
	पूर्णांक r;
	u16 ioc_status;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	*num_pds = 0;
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_RAID_VOLUME;
	mpi_request.Header.PageNumber = 0;
	mpi_request.Header.PageVersion = MPI2_RAIDVOLPAGE0_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, &mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.PageAddress =
	    cpu_to_le32(MPI2_RAID_VOLUME_PGAD_FORM_HANDLE | handle);
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, &mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, &config_page,
	    माप(Mpi2RaidVolPage0_t));
	अगर (!r) अणु
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		अगर (ioc_status == MPI2_IOCSTATUS_SUCCESS)
			*num_pds = config_page.NumPhysDisks;
	पूर्ण

 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_raid_volume_pg0 - obtain raid volume page 0
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * @क्रमm: GET_NEXT_HANDLE or HANDLE
 * @handle: volume handle
 * @sz: size of buffer passed in config_page
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_raid_volume_pg0(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2RaidVolPage0_t *config_page, u32 क्रमm,
	u32 handle, u16 sz)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_RAID_VOLUME;
	mpi_request.Header.PageNumber = 0;
	mpi_request.Header.PageVersion = MPI2_RAIDVOLPAGE0_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.PageAddress = cpu_to_le32(क्रमm | handle);
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page, sz);
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_phys_disk_pg0 - obtain phys disk page 0
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * @क्रमm: GET_NEXT_PHYSDISKNUM, PHYSDISKNUM, DEVHANDLE
 * @क्रमm_specअगरic: specअगरic to the क्रमm
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_phys_disk_pg0(काष्ठा MPT3SAS_ADAPTER *ioc, Mpi2ConfigReply_t
	*mpi_reply, Mpi2RaidPhysDiskPage0_t *config_page, u32 क्रमm,
	u32 क्रमm_specअगरic)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_RAID_PHYSDISK;
	mpi_request.Header.PageNumber = 0;
	mpi_request.Header.PageVersion = MPI2_RAIDPHYSDISKPAGE0_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.PageAddress = cpu_to_le32(क्रमm | क्रमm_specअगरic);
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_driver_trigger_pg0 - obtain driver trigger page 0
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * Context: sleep.
 *
 * Returns 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_driver_trigger_pg0(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi26DriverTriggerPage0_t *config_page)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType =
	    MPI2_CONFIG_EXTPAGETYPE_DRIVER_PERSISTENT_TRIGGER;
	mpi_request.Header.PageNumber = 0;
	mpi_request.Header.PageVersion = MPI26_DRIVER_TRIGGER_PAGE0_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * _config_set_driver_trigger_pg0 - ग_लिखो driver trigger page 0
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * Context: sleep.
 *
 * Returns 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_config_set_driver_trigger_pg0(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi26DriverTriggerPage0_t *config_page)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType =
	    MPI2_CONFIG_EXTPAGETYPE_DRIVER_PERSISTENT_TRIGGER;
	mpi_request.Header.PageNumber = 0;
	mpi_request.Header.PageVersion = MPI26_DRIVER_TRIGGER_PAGE0_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_WRITE_CURRENT;
	_config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_WRITE_NVRAM;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_update_driver_trigger_pg0 - update driver trigger page 0
 * @ioc: per adapter object
 * @trigger_flag: trigger type bit map
 * @set: set ot clear trigger values
 * Context: sleep.
 *
 * Returns 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
mpt3sas_config_update_driver_trigger_pg0(काष्ठा MPT3SAS_ADAPTER *ioc,
	u16 trigger_flag, bool set)
अणु
	Mpi26DriverTriggerPage0_t tg_pg0;
	Mpi2ConfigReply_t mpi_reply;
	पूर्णांक rc;
	u16 flags, ioc_status;

	rc = mpt3sas_config_get_driver_trigger_pg0(ioc, &mpi_reply, &tg_pg0);
	अगर (rc)
		वापस rc;
	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		dcprपूर्णांकk(ioc,
		    ioc_err(ioc,
		    "%s: Failed to get trigger pg0, ioc_status(0x%04x)\n",
		    __func__, ioc_status));
		वापस -EFAULT;
	पूर्ण

	अगर (set)
		flags = le16_to_cpu(tg_pg0.TriggerFlags) | trigger_flag;
	अन्यथा
		flags = le16_to_cpu(tg_pg0.TriggerFlags) & ~trigger_flag;

	tg_pg0.TriggerFlags = cpu_to_le16(flags);

	rc = _config_set_driver_trigger_pg0(ioc, &mpi_reply, &tg_pg0);
	अगर (rc)
		वापस rc;
	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		dcprपूर्णांकk(ioc,
		    ioc_err(ioc,
		    "%s: Failed to update trigger pg0, ioc_status(0x%04x)\n",
		    __func__, ioc_status));
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * mpt3sas_config_get_driver_trigger_pg1 - obtain driver trigger page 1
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * Context: sleep.
 *
 * Returns 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_driver_trigger_pg1(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi26DriverTriggerPage1_t *config_page)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType =
	    MPI2_CONFIG_EXTPAGETYPE_DRIVER_PERSISTENT_TRIGGER;
	mpi_request.Header.PageNumber = 1;
	mpi_request.Header.PageVersion = MPI26_DRIVER_TRIGGER_PAGE1_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * _config_set_driver_trigger_pg1 - ग_लिखो driver trigger page 1
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * Context: sleep.
 *
 * Returns 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_config_set_driver_trigger_pg1(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi26DriverTriggerPage1_t *config_page)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType =
	    MPI2_CONFIG_EXTPAGETYPE_DRIVER_PERSISTENT_TRIGGER;
	mpi_request.Header.PageNumber = 1;
	mpi_request.Header.PageVersion = MPI26_DRIVER_TRIGGER_PAGE1_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_WRITE_CURRENT;
	_config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_WRITE_NVRAM;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_update_driver_trigger_pg1 - update driver trigger page 1
 * @ioc: per adapter object
 * @master_tg: Master trigger bit map
 * @set: set ot clear trigger values
 * Context: sleep.
 *
 * Returns 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_update_driver_trigger_pg1(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा SL_WH_MASTER_TRIGGER_T *master_tg, bool set)
अणु
	Mpi26DriverTriggerPage1_t tg_pg1;
	Mpi2ConfigReply_t mpi_reply;
	पूर्णांक rc;
	u16 ioc_status;

	rc = mpt3sas_config_update_driver_trigger_pg0(ioc,
	    MPI26_DRIVER_TRIGGER0_FLAG_MASTER_TRIGGER_VALID, set);
	अगर (rc)
		वापस rc;

	rc = mpt3sas_config_get_driver_trigger_pg1(ioc, &mpi_reply, &tg_pg1);
	अगर (rc)
		जाओ out;

	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		dcprपूर्णांकk(ioc,
		    ioc_err(ioc,
		    "%s: Failed to get trigger pg1, ioc_status(0x%04x)\n",
		    __func__, ioc_status));
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (set) अणु
		tg_pg1.NumMasterTrigger = cpu_to_le16(1);
		tg_pg1.MasterTriggers[0].MasterTriggerFlags = cpu_to_le32(
		    master_tg->MasterData);
	पूर्ण अन्यथा अणु
		tg_pg1.NumMasterTrigger = 0;
		tg_pg1.MasterTriggers[0].MasterTriggerFlags = 0;
	पूर्ण

	rc = _config_set_driver_trigger_pg1(ioc, &mpi_reply, &tg_pg1);
	अगर (rc)
		जाओ out;

	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		dcprपूर्णांकk(ioc,
		    ioc_err(ioc,
		    "%s: Failed to get trigger pg1, ioc_status(0x%04x)\n",
		    __func__, ioc_status));
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	वापस 0;

out:
	mpt3sas_config_update_driver_trigger_pg0(ioc,
	    MPI26_DRIVER_TRIGGER0_FLAG_MASTER_TRIGGER_VALID, !set);

	वापस rc;
पूर्ण

/**
 * mpt3sas_config_get_driver_trigger_pg2 - obtain driver trigger page 2
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * Context: sleep.
 *
 * Returns 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_driver_trigger_pg2(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi26DriverTriggerPage2_t *config_page)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType =
	    MPI2_CONFIG_EXTPAGETYPE_DRIVER_PERSISTENT_TRIGGER;
	mpi_request.Header.PageNumber = 2;
	mpi_request.Header.PageVersion = MPI26_DRIVER_TRIGGER_PAGE2_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * _config_set_driver_trigger_pg2 - ग_लिखो driver trigger page 2
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * Context: sleep.
 *
 * Returns 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_config_set_driver_trigger_pg2(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi26DriverTriggerPage2_t *config_page)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType =
	    MPI2_CONFIG_EXTPAGETYPE_DRIVER_PERSISTENT_TRIGGER;
	mpi_request.Header.PageNumber = 2;
	mpi_request.Header.PageVersion = MPI26_DRIVER_TRIGGER_PAGE2_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_WRITE_CURRENT;
	_config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_WRITE_NVRAM;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_update_driver_trigger_pg2 - update driver trigger page 2
 * @ioc: per adapter object
 * @event_tg: list of Event Triggers
 * @set: set ot clear trigger values
 * Context: sleep.
 *
 * Returns 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_update_driver_trigger_pg2(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा SL_WH_EVENT_TRIGGERS_T *event_tg, bool set)
अणु
	Mpi26DriverTriggerPage2_t tg_pg2;
	Mpi2ConfigReply_t mpi_reply;
	पूर्णांक rc, i, count;
	u16 ioc_status;

	rc = mpt3sas_config_update_driver_trigger_pg0(ioc,
	    MPI26_DRIVER_TRIGGER0_FLAG_MPI_EVENT_TRIGGER_VALID, set);
	अगर (rc)
		वापस rc;

	rc = mpt3sas_config_get_driver_trigger_pg2(ioc, &mpi_reply, &tg_pg2);
	अगर (rc)
		जाओ out;

	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		dcprपूर्णांकk(ioc,
		    ioc_err(ioc,
		    "%s: Failed to get trigger pg2, ioc_status(0x%04x)\n",
		    __func__, ioc_status));
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (set) अणु
		count = event_tg->ValidEntries;
		tg_pg2.NumMPIEventTrigger = cpu_to_le16(count);
		क्रम (i = 0; i < count; i++) अणु
			tg_pg2.MPIEventTriggers[i].MPIEventCode =
			    cpu_to_le16(
			    event_tg->EventTriggerEntry[i].EventValue);
			tg_pg2.MPIEventTriggers[i].MPIEventCodeSpecअगरic =
			    cpu_to_le16(
			    event_tg->EventTriggerEntry[i].LogEntryQualअगरier);
		पूर्ण
	पूर्ण अन्यथा अणु
		tg_pg2.NumMPIEventTrigger = 0;
		स_रखो(&tg_pg2.MPIEventTriggers[0], 0,
		    NUM_VALID_ENTRIES * माप(
		    MPI26_DRIVER_MPI_EVENT_TIGGER_ENTRY));
	पूर्ण

	rc = _config_set_driver_trigger_pg2(ioc, &mpi_reply, &tg_pg2);
	अगर (rc)
		जाओ out;

	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		dcprपूर्णांकk(ioc,
		    ioc_err(ioc,
		    "%s: Failed to get trigger pg2, ioc_status(0x%04x)\n",
		    __func__, ioc_status));
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	वापस 0;

out:
	mpt3sas_config_update_driver_trigger_pg0(ioc,
	    MPI26_DRIVER_TRIGGER0_FLAG_MPI_EVENT_TRIGGER_VALID, !set);

	वापस rc;
पूर्ण

/**
 * mpt3sas_config_get_driver_trigger_pg3 - obtain driver trigger page 3
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * Context: sleep.
 *
 * Returns 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_driver_trigger_pg3(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi26DriverTriggerPage3_t *config_page)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType =
	    MPI2_CONFIG_EXTPAGETYPE_DRIVER_PERSISTENT_TRIGGER;
	mpi_request.Header.PageNumber = 3;
	mpi_request.Header.PageVersion = MPI26_DRIVER_TRIGGER_PAGE3_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * _config_set_driver_trigger_pg3 - ग_लिखो driver trigger page 3
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * Context: sleep.
 *
 * Returns 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_config_set_driver_trigger_pg3(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi26DriverTriggerPage3_t *config_page)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType =
	    MPI2_CONFIG_EXTPAGETYPE_DRIVER_PERSISTENT_TRIGGER;
	mpi_request.Header.PageNumber = 3;
	mpi_request.Header.PageVersion = MPI26_DRIVER_TRIGGER_PAGE3_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_WRITE_CURRENT;
	_config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_WRITE_NVRAM;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_update_driver_trigger_pg3 - update driver trigger page 3
 * @ioc: per adapter object
 * @scsi_tg: scsi trigger list
 * @set: set ot clear trigger values
 * Context: sleep.
 *
 * Returns 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_update_driver_trigger_pg3(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा SL_WH_SCSI_TRIGGERS_T *scsi_tg, bool set)
अणु
	Mpi26DriverTriggerPage3_t tg_pg3;
	Mpi2ConfigReply_t mpi_reply;
	पूर्णांक rc, i, count;
	u16 ioc_status;

	rc = mpt3sas_config_update_driver_trigger_pg0(ioc,
	    MPI26_DRIVER_TRIGGER0_FLAG_SCSI_SENSE_TRIGGER_VALID, set);
	अगर (rc)
		वापस rc;

	rc = mpt3sas_config_get_driver_trigger_pg3(ioc, &mpi_reply, &tg_pg3);
	अगर (rc)
		जाओ out;

	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		dcprपूर्णांकk(ioc,
		    ioc_err(ioc,
		    "%s: Failed to get trigger pg3, ioc_status(0x%04x)\n",
		    __func__, ioc_status));
		वापस -EFAULT;
	पूर्ण

	अगर (set) अणु
		count = scsi_tg->ValidEntries;
		tg_pg3.NumSCSISenseTrigger = cpu_to_le16(count);
		क्रम (i = 0; i < count; i++) अणु
			tg_pg3.SCSISenseTriggers[i].ASCQ =
			    scsi_tg->SCSITriggerEntry[i].ASCQ;
			tg_pg3.SCSISenseTriggers[i].ASC =
			    scsi_tg->SCSITriggerEntry[i].ASC;
			tg_pg3.SCSISenseTriggers[i].SenseKey =
			    scsi_tg->SCSITriggerEntry[i].SenseKey;
		पूर्ण
	पूर्ण अन्यथा अणु
		tg_pg3.NumSCSISenseTrigger = 0;
		स_रखो(&tg_pg3.SCSISenseTriggers[0], 0,
		    NUM_VALID_ENTRIES * माप(
		    MPI26_DRIVER_SCSI_SENSE_TIGGER_ENTRY));
	पूर्ण

	rc = _config_set_driver_trigger_pg3(ioc, &mpi_reply, &tg_pg3);
	अगर (rc)
		जाओ out;

	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		dcprपूर्णांकk(ioc,
		    ioc_err(ioc,
		    "%s: Failed to get trigger pg3, ioc_status(0x%04x)\n",
		     __func__, ioc_status));
		वापस -EFAULT;
	पूर्ण

	वापस 0;
out:
	mpt3sas_config_update_driver_trigger_pg0(ioc,
	    MPI26_DRIVER_TRIGGER0_FLAG_SCSI_SENSE_TRIGGER_VALID, !set);

	वापस rc;
पूर्ण

/**
 * mpt3sas_config_get_driver_trigger_pg4 - obtain driver trigger page 4
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * Context: sleep.
 *
 * Returns 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_driver_trigger_pg4(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi26DriverTriggerPage4_t *config_page)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType =
	    MPI2_CONFIG_EXTPAGETYPE_DRIVER_PERSISTENT_TRIGGER;
	mpi_request.Header.PageNumber = 4;
	mpi_request.Header.PageVersion = MPI26_DRIVER_TRIGGER_PAGE4_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * _config_set_driver_trigger_pg4 - ग_लिखो driver trigger page 4
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @config_page: contents of the config page
 * Context: sleep.
 *
 * Returns 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_config_set_driver_trigger_pg4(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi26DriverTriggerPage4_t *config_page)
अणु
	Mpi2ConfigRequest_t mpi_request;
	पूर्णांक r;

	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType =
	    MPI2_CONFIG_EXTPAGETYPE_DRIVER_PERSISTENT_TRIGGER;
	mpi_request.Header.PageNumber = 4;
	mpi_request.Header.PageVersion = MPI26_DRIVER_TRIGGER_PAGE4_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_WRITE_CURRENT;
	_config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_WRITE_NVRAM;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    माप(*config_page));
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_config_update_driver_trigger_pg4 - update driver trigger page 4
 * @ioc: per adapter object
 * @mpi_tg: mpi trigger list
 * @set: set ot clear trigger values
 * Context: sleep.
 *
 * Returns 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_update_driver_trigger_pg4(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा SL_WH_MPI_TRIGGERS_T *mpi_tg, bool set)
अणु
	Mpi26DriverTriggerPage4_t tg_pg4;
	Mpi2ConfigReply_t mpi_reply;
	पूर्णांक rc, i, count;
	u16 ioc_status;

	rc = mpt3sas_config_update_driver_trigger_pg0(ioc,
	    MPI26_DRIVER_TRIGGER0_FLAG_LOGINFO_TRIGGER_VALID, set);
	अगर (rc)
		वापस rc;

	rc = mpt3sas_config_get_driver_trigger_pg4(ioc, &mpi_reply, &tg_pg4);
	अगर (rc)
		जाओ out;

	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		dcprपूर्णांकk(ioc,
		    ioc_err(ioc,
		    "%s: Failed to get trigger pg4, ioc_status(0x%04x)\n",
		    __func__, ioc_status));
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (set) अणु
		count = mpi_tg->ValidEntries;
		tg_pg4.NumIOCStatusLogInfoTrigger = cpu_to_le16(count);
		क्रम (i = 0; i < count; i++) अणु
			tg_pg4.IOCStatusLoginfoTriggers[i].IOCStatus =
			    cpu_to_le16(mpi_tg->MPITriggerEntry[i].IOCStatus);
			tg_pg4.IOCStatusLoginfoTriggers[i].LogInfo =
			    cpu_to_le32(mpi_tg->MPITriggerEntry[i].IocLogInfo);
		पूर्ण
	पूर्ण अन्यथा अणु
		tg_pg4.NumIOCStatusLogInfoTrigger = 0;
		स_रखो(&tg_pg4.IOCStatusLoginfoTriggers[0], 0,
		    NUM_VALID_ENTRIES * माप(
		    MPI26_DRIVER_IOCSTATUS_LOGINFO_TIGGER_ENTRY));
	पूर्ण

	rc = _config_set_driver_trigger_pg4(ioc, &mpi_reply, &tg_pg4);
	अगर (rc)
		जाओ out;

	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		dcprपूर्णांकk(ioc,
		    ioc_err(ioc,
		    "%s: Failed to get trigger pg4, ioc_status(0x%04x)\n",
		    __func__, ioc_status));
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	वापस 0;

out:
	mpt3sas_config_update_driver_trigger_pg0(ioc,
	    MPI26_DRIVER_TRIGGER0_FLAG_LOGINFO_TRIGGER_VALID, !set);

	वापस rc;
पूर्ण

/**
 * mpt3sas_config_get_volume_handle - वापसs volume handle क्रम give hidden
 * raid components
 * @ioc: per adapter object
 * @pd_handle: phys disk handle
 * @volume_handle: volume handle
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_volume_handle(काष्ठा MPT3SAS_ADAPTER *ioc, u16 pd_handle,
	u16 *volume_handle)
अणु
	Mpi2RaidConfigurationPage0_t *config_page = शून्य;
	Mpi2ConfigRequest_t mpi_request;
	Mpi2ConfigReply_t mpi_reply;
	पूर्णांक r, i, config_page_sz;
	u16 ioc_status;
	पूर्णांक config_num;
	u16 element_type;
	u16 phys_disk_dev_handle;

	*volume_handle = 0;
	स_रखो(&mpi_request, 0, माप(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_RAID_CONFIG;
	mpi_request.Header.PageVersion = MPI2_RAIDCONFIG0_PAGEVERSION;
	mpi_request.Header.PageNumber = 0;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, &mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, शून्य, 0);
	अगर (r)
		जाओ out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	config_page_sz = (le16_to_cpu(mpi_reply.ExtPageLength) * 4);
	config_page = kदो_स्मृति(config_page_sz, GFP_KERNEL);
	अगर (!config_page) अणु
		r = -1;
		जाओ out;
	पूर्ण

	config_num = 0xff;
	जबतक (1) अणु
		mpi_request.PageAddress = cpu_to_le32(config_num +
		    MPI2_RAID_PGAD_FORM_GET_NEXT_CONFIGNUM);
		r = _config_request(ioc, &mpi_request, &mpi_reply,
		    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
		    config_page_sz);
		अगर (r)
			जाओ out;
		r = -1;
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS)
			जाओ out;
		क्रम (i = 0; i < config_page->NumElements; i++) अणु
			element_type = le16_to_cpu(config_page->
			    ConfigElement[i].ElementFlags) &
			    MPI2_RAIDCONFIG0_EFLAGS_MASK_ELEMENT_TYPE;
			अगर (element_type ==
			    MPI2_RAIDCONFIG0_EFLAGS_VOL_PHYS_DISK_ELEMENT ||
			    element_type ==
			    MPI2_RAIDCONFIG0_EFLAGS_OCE_ELEMENT) अणु
				phys_disk_dev_handle =
				    le16_to_cpu(config_page->ConfigElement[i].
				    PhysDiskDevHandle);
				अगर (phys_disk_dev_handle == pd_handle) अणु
					*volume_handle =
					    le16_to_cpu(config_page->
					    ConfigElement[i].VolDevHandle);
					r = 0;
					जाओ out;
				पूर्ण
			पूर्ण अन्यथा अगर (element_type ==
			    MPI2_RAIDCONFIG0_EFLAGS_HOT_SPARE_ELEMENT) अणु
				*volume_handle = 0;
				r = 0;
				जाओ out;
			पूर्ण
		पूर्ण
		config_num = config_page->ConfigNum;
	पूर्ण
 out:
	kमुक्त(config_page);
	वापस r;
पूर्ण

/**
 * mpt3sas_config_get_volume_wwid - वापसs wwid given the volume handle
 * @ioc: per adapter object
 * @volume_handle: volume handle
 * @wwid: volume wwid
 * Context: sleep.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_config_get_volume_wwid(काष्ठा MPT3SAS_ADAPTER *ioc, u16 volume_handle,
	u64 *wwid)
अणु
	Mpi2ConfigReply_t mpi_reply;
	Mpi2RaidVolPage1_t raid_vol_pg1;

	*wwid = 0;
	अगर (!(mpt3sas_config_get_raid_volume_pg1(ioc, &mpi_reply,
	    &raid_vol_pg1, MPI2_RAID_VOLUME_PGAD_FORM_HANDLE,
	    volume_handle))) अणु
		*wwid = le64_to_cpu(raid_vol_pg1.WWID);
		वापस 0;
	पूर्ण अन्यथा
		वापस -1;
पूर्ण
