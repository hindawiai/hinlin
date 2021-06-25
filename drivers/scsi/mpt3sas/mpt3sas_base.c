<शैली गुरु>
/*
 * This is the Fusion MPT base driver providing common API layer पूर्णांकerface
 * क्रम access to MPT (Message Passing Technology) firmware.
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

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/समय.स>
#समावेश <linux/kसमय.स>
#समावेश <linux/kthपढ़ो.h>
#समावेश <यंत्र/page.h>        /* To get host page size per arch */
#समावेश <linux/aer.h>


#समावेश "mpt3sas_base.h"

अटल MPT_CALLBACK	mpt_callbacks[MPT_MAX_CALLBACKS];


#घोषणा FAULT_POLLING_INTERVAL 1000 /* in milliseconds */

 /* maximum controller queue depth */
#घोषणा MAX_HBA_QUEUE_DEPTH	30000
#घोषणा MAX_CHAIN_DEPTH		100000
अटल पूर्णांक max_queue_depth = -1;
module_param(max_queue_depth, पूर्णांक, 0444);
MODULE_PARM_DESC(max_queue_depth, " max controller queue depth ");

अटल पूर्णांक max_sgl_entries = -1;
module_param(max_sgl_entries, पूर्णांक, 0444);
MODULE_PARM_DESC(max_sgl_entries, " max sg entries ");

अटल पूर्णांक msix_disable = -1;
module_param(msix_disable, पूर्णांक, 0444);
MODULE_PARM_DESC(msix_disable, " disable msix routed interrupts (default=0)");

अटल पूर्णांक smp_affinity_enable = 1;
module_param(smp_affinity_enable, पूर्णांक, 0444);
MODULE_PARM_DESC(smp_affinity_enable, "SMP affinity feature enable/disable Default: enable(1)");

अटल पूर्णांक max_msix_vectors = -1;
module_param(max_msix_vectors, पूर्णांक, 0444);
MODULE_PARM_DESC(max_msix_vectors,
	" max msix vectors");

अटल पूर्णांक irqpoll_weight = -1;
module_param(irqpoll_weight, पूर्णांक, 0444);
MODULE_PARM_DESC(irqpoll_weight,
	"irq poll weight (default= one fourth of HBA queue depth)");

अटल पूर्णांक mpt3sas_fwfault_debug;
MODULE_PARM_DESC(mpt3sas_fwfault_debug,
	" enable detection of firmware fault and halt firmware - (default=0)");

अटल पूर्णांक perf_mode = -1;
module_param(perf_mode, पूर्णांक, 0444);
MODULE_PARM_DESC(perf_mode,
	"Performance mode (only for Aero/Sea Generation), options:\n\t\t"
	"0 - balanced: high iops mode is enabled &\n\t\t"
	"interrupt coalescing is enabled only on high iops queues,\n\t\t"
	"1 - iops: high iops mode is disabled &\n\t\t"
	"interrupt coalescing is enabled on all queues,\n\t\t"
	"2 - latency: high iops mode is disabled &\n\t\t"
	"interrupt coalescing is enabled on all queues with timeout value 0xA,\n"
	"\t\tdefault - default perf_mode is 'balanced'"
	);

क्रमागत mpt3sas_perf_mode अणु
	MPT_PERF_MODE_DEFAULT	= -1,
	MPT_PERF_MODE_BALANCED	= 0,
	MPT_PERF_MODE_IOPS	= 1,
	MPT_PERF_MODE_LATENCY	= 2,
पूर्ण;

अटल पूर्णांक
_base_रुको_on_iocstate(काष्ठा MPT3SAS_ADAPTER *ioc,
		u32 ioc_state, पूर्णांक समयout);
अटल पूर्णांक
_base_get_ioc_facts(काष्ठा MPT3SAS_ADAPTER *ioc);
अटल व्योम
_base_clear_outstanding_commands(काष्ठा MPT3SAS_ADAPTER *ioc);

/**
 * mpt3sas_base_check_cmd_समयout - Function
 *		to check समयout and command termination due
 *		to Host reset.
 *
 * @ioc:	per adapter object.
 * @status:	Status of issued command.
 * @mpi_request:mf request poपूर्णांकer.
 * @sz:		size of buffer.
 *
 * @Returns - 1/0 Reset to be करोne or Not
 */
u8
mpt3sas_base_check_cmd_समयout(काष्ठा MPT3SAS_ADAPTER *ioc,
		u8 status, व्योम *mpi_request, पूर्णांक sz)
अणु
	u8 issue_reset = 0;

	अगर (!(status & MPT3_CMD_RESET))
		issue_reset = 1;

	ioc_err(ioc, "Command %s\n",
		issue_reset == 0 ? "terminated due to Host Reset" : "Timeout");
	_debug_dump_mf(mpi_request, sz);

	वापस issue_reset;
पूर्ण

/**
 * _scsih_set_fwfault_debug - global setting of ioc->fwfault_debug.
 * @val: ?
 * @kp: ?
 *
 * Return: ?
 */
अटल पूर्णांक
_scsih_set_fwfault_debug(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक ret = param_set_पूर्णांक(val, kp);
	काष्ठा MPT3SAS_ADAPTER *ioc;

	अगर (ret)
		वापस ret;

	/* global ioc spinlock to protect controller list on list operations */
	pr_info("setting fwfault_debug(%d)\n", mpt3sas_fwfault_debug);
	spin_lock(&gioc_lock);
	list_क्रम_each_entry(ioc, &mpt3sas_ioc_list, list)
		ioc->fwfault_debug = mpt3sas_fwfault_debug;
	spin_unlock(&gioc_lock);
	वापस 0;
पूर्ण
module_param_call(mpt3sas_fwfault_debug, _scsih_set_fwfault_debug,
	param_get_पूर्णांक, &mpt3sas_fwfault_debug, 0644);

/**
 * _base_पढ़ोl_aero - retry पढ़ोl क्रम max three बार.
 * @addr: MPT Fusion प्रणाली पूर्णांकerface रेजिस्टर address
 *
 * Retry the पढ़ोl() क्रम max three बार अगर it माला_लो zero value
 * जबतक पढ़ोing the प्रणाली पूर्णांकerface रेजिस्टर.
 */
अटल अंतरभूत u32
_base_पढ़ोl_aero(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u32 i = 0, ret_val;

	करो अणु
		ret_val = पढ़ोl(addr);
		i++;
	पूर्ण जबतक (ret_val == 0 && i < 3);

	वापस ret_val;
पूर्ण

अटल अंतरभूत u32
_base_पढ़ोl(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस पढ़ोl(addr);
पूर्ण

/**
 * _base_clone_reply_to_sys_mem - copies reply to reply मुक्त iomem
 *				  in BAR0 space.
 *
 * @ioc: per adapter object
 * @reply: reply message frame(lower 32bit addr)
 * @index: System request message index.
 */
अटल व्योम
_base_clone_reply_to_sys_mem(काष्ठा MPT3SAS_ADAPTER *ioc, u32 reply,
		u32 index)
अणु
	/*
	 * 256 is offset within sys रेजिस्टर.
	 * 256 offset MPI frame starts. Max MPI frame supported is 32.
	 * 32 * 128 = 4K. From here, Clone of reply मुक्त क्रम mcpu starts
	 */
	u16 cmd_credit = ioc->facts.RequestCredit + 1;
	व्योम __iomem *reply_मुक्त_iomem = (व्योम __iomem *)ioc->chip +
			MPI_FRAME_START_OFFSET +
			(cmd_credit * ioc->request_sz) + (index * माप(u32));

	ग_लिखोl(reply, reply_मुक्त_iomem);
पूर्ण

/**
 * _base_clone_mpi_to_sys_mem - Writes/copies MPI frames
 *				to प्रणाली/BAR0 region.
 *
 * @dst_iomem: Poपूर्णांकer to the destination location in BAR0 space.
 * @src: Poपूर्णांकer to the Source data.
 * @size: Size of data to be copied.
 */
अटल व्योम
_base_clone_mpi_to_sys_mem(व्योम *dst_iomem, व्योम *src, u32 size)
अणु
	पूर्णांक i;
	u32 *src_virt_mem = (u32 *)src;

	क्रम (i = 0; i < size/4; i++)
		ग_लिखोl((u32)src_virt_mem[i],
				(व्योम __iomem *)dst_iomem + (i * 4));
पूर्ण

/**
 * _base_clone_to_sys_mem - Writes/copies data to प्रणाली/BAR0 region
 *
 * @dst_iomem: Poपूर्णांकer to the destination location in BAR0 space.
 * @src: Poपूर्णांकer to the Source data.
 * @size: Size of data to be copied.
 */
अटल व्योम
_base_clone_to_sys_mem(व्योम __iomem *dst_iomem, व्योम *src, u32 size)
अणु
	पूर्णांक i;
	u32 *src_virt_mem = (u32 *)(src);

	क्रम (i = 0; i < size/4; i++)
		ग_लिखोl((u32)src_virt_mem[i],
			(व्योम __iomem *)dst_iomem + (i * 4));
पूर्ण

/**
 * _base_get_chain - Calculates and Returns भव chain address
 *			 क्रम the provided smid in BAR0 space.
 *
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @sge_chain_count: Scatter gather chain count.
 *
 * Return: the chain address.
 */
अटल अंतरभूत व्योम __iomem*
_base_get_chain(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid,
		u8 sge_chain_count)
अणु
	व्योम __iomem *base_chain, *chain_virt;
	u16 cmd_credit = ioc->facts.RequestCredit + 1;

	base_chain  = (व्योम __iomem *)ioc->chip + MPI_FRAME_START_OFFSET +
		(cmd_credit * ioc->request_sz) +
		REPLY_FREE_POOL_SIZE;
	chain_virt = base_chain + (smid * ioc->facts.MaxChainDepth *
			ioc->request_sz) + (sge_chain_count * ioc->request_sz);
	वापस chain_virt;
पूर्ण

/**
 * _base_get_chain_phys - Calculates and Returns physical address
 *			in BAR0 क्रम scatter gather chains, क्रम
 *			the provided smid.
 *
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @sge_chain_count: Scatter gather chain count.
 *
 * Return: Physical chain address.
 */
अटल अंतरभूत phys_addr_t
_base_get_chain_phys(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid,
		u8 sge_chain_count)
अणु
	phys_addr_t base_chain_phys, chain_phys;
	u16 cmd_credit = ioc->facts.RequestCredit + 1;

	base_chain_phys  = ioc->chip_phys + MPI_FRAME_START_OFFSET +
		(cmd_credit * ioc->request_sz) +
		REPLY_FREE_POOL_SIZE;
	chain_phys = base_chain_phys + (smid * ioc->facts.MaxChainDepth *
			ioc->request_sz) + (sge_chain_count * ioc->request_sz);
	वापस chain_phys;
पूर्ण

/**
 * _base_get_buffer_bar0 - Calculates and Returns BAR0 mapped Host
 *			buffer address क्रम the provided smid.
 *			(Each smid can have 64K starts from 17024)
 *
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 *
 * Return: Poपूर्णांकer to buffer location in BAR0.
 */

अटल व्योम __iomem *
_base_get_buffer_bar0(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid)
अणु
	u16 cmd_credit = ioc->facts.RequestCredit + 1;
	// Added extra 1 to reach end of chain.
	व्योम __iomem *chain_end = _base_get_chain(ioc,
			cmd_credit + 1,
			ioc->facts.MaxChainDepth);
	वापस chain_end + (smid * 64 * 1024);
पूर्ण

/**
 * _base_get_buffer_phys_bar0 - Calculates and Returns BAR0 mapped
 *		Host buffer Physical address क्रम the provided smid.
 *		(Each smid can have 64K starts from 17024)
 *
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 *
 * Return: Poपूर्णांकer to buffer location in BAR0.
 */
अटल phys_addr_t
_base_get_buffer_phys_bar0(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid)
अणु
	u16 cmd_credit = ioc->facts.RequestCredit + 1;
	phys_addr_t chain_end_phys = _base_get_chain_phys(ioc,
			cmd_credit + 1,
			ioc->facts.MaxChainDepth);
	वापस chain_end_phys + (smid * 64 * 1024);
पूर्ण

/**
 * _base_get_chain_buffer_dma_to_chain_buffer - Iterates chain
 *			lookup list and Provides chain_buffer
 *			address क्रम the matching dma address.
 *			(Each smid can have 64K starts from 17024)
 *
 * @ioc: per adapter object
 * @chain_buffer_dma: Chain buffer dma address.
 *
 * Return: Poपूर्णांकer to chain buffer. Or Null on Failure.
 */
अटल व्योम *
_base_get_chain_buffer_dma_to_chain_buffer(काष्ठा MPT3SAS_ADAPTER *ioc,
		dma_addr_t chain_buffer_dma)
अणु
	u16 index, j;
	काष्ठा chain_tracker *ct;

	क्रम (index = 0; index < ioc->scsiio_depth; index++) अणु
		क्रम (j = 0; j < ioc->chains_needed_per_io; j++) अणु
			ct = &ioc->chain_lookup[index].chains_per_smid[j];
			अगर (ct && ct->chain_buffer_dma == chain_buffer_dma)
				वापस ct->chain_buffer;
		पूर्ण
	पूर्ण
	ioc_info(ioc, "Provided chain_buffer_dma address is not in the lookup list\n");
	वापस शून्य;
पूर्ण

/**
 * _clone_sg_entries -	MPI EP's scsiio and config requests
 *			are handled here. Base function क्रम
 *			द्विगुन buffering, beक्रमe submitting
 *			the requests.
 *
 * @ioc: per adapter object.
 * @mpi_request: mf request poपूर्णांकer.
 * @smid: प्रणाली request message index.
 */
अटल व्योम _clone_sg_entries(काष्ठा MPT3SAS_ADAPTER *ioc,
		व्योम *mpi_request, u16 smid)
अणु
	Mpi2SGESimple32_t *sgel, *sgel_next;
	u32  sgl_flags, sge_chain_count = 0;
	bool is_ग_लिखो = false;
	u16 i = 0;
	व्योम __iomem *buffer_iomem;
	phys_addr_t buffer_iomem_phys;
	व्योम __iomem *buff_ptr;
	phys_addr_t buff_ptr_phys;
	व्योम __iomem *dst_chain_addr[MCPU_MAX_CHAINS_PER_IO];
	व्योम *src_chain_addr[MCPU_MAX_CHAINS_PER_IO];
	phys_addr_t dst_addr_phys;
	MPI2RequestHeader_t *request_hdr;
	काष्ठा scsi_cmnd *scmd;
	काष्ठा scatterlist *sg_scmd = शून्य;
	पूर्णांक is_scsiio_req = 0;

	request_hdr = (MPI2RequestHeader_t *) mpi_request;

	अगर (request_hdr->Function == MPI2_FUNCTION_SCSI_IO_REQUEST) अणु
		Mpi25SCSIIORequest_t *scsiio_request =
			(Mpi25SCSIIORequest_t *)mpi_request;
		sgel = (Mpi2SGESimple32_t *) &scsiio_request->SGL;
		is_scsiio_req = 1;
	पूर्ण अन्यथा अगर (request_hdr->Function == MPI2_FUNCTION_CONFIG) अणु
		Mpi2ConfigRequest_t  *config_req =
			(Mpi2ConfigRequest_t *)mpi_request;
		sgel = (Mpi2SGESimple32_t *) &config_req->PageBufferSGE;
	पूर्ण अन्यथा
		वापस;

	/* From smid we can get scsi_cmd, once we have sg_scmd,
	 * we just need to get sg_virt and sg_next to get virual
	 * address associated with sgel->Address.
	 */

	अगर (is_scsiio_req) अणु
		/* Get scsi_cmd using smid */
		scmd = mpt3sas_scsih_scsi_lookup_get(ioc, smid);
		अगर (scmd == शून्य) अणु
			ioc_err(ioc, "scmd is NULL\n");
			वापस;
		पूर्ण

		/* Get sg_scmd from scmd provided */
		sg_scmd = scsi_sglist(scmd);
	पूर्ण

	/*
	 * 0 - 255	System रेजिस्टर
	 * 256 - 4352	MPI Frame. (This is based on maxCredit 32)
	 * 4352 - 4864	Reply_मुक्त pool (512 byte is reserved
	 *		considering maxCredit 32. Reply need extra
	 *		room, क्रम mCPU हाल kept four बार of
	 *		maxCredit).
	 * 4864 - 17152	SGE chain element. (32cmd * 3 chain of
	 *		128 byte size = 12288)
	 * 17152 - x	Host buffer mapped with smid.
	 *		(Each smid can have 64K Max IO.)
	 * BAR0+Last 1K MSIX Addr and Data
	 * Total size in use 2113664 bytes of 4MB BAR0
	 */

	buffer_iomem = _base_get_buffer_bar0(ioc, smid);
	buffer_iomem_phys = _base_get_buffer_phys_bar0(ioc, smid);

	buff_ptr = buffer_iomem;
	buff_ptr_phys = buffer_iomem_phys;
	WARN_ON(buff_ptr_phys > U32_MAX);

	अगर (le32_to_cpu(sgel->FlagsLength) &
			(MPI2_SGE_FLAGS_HOST_TO_IOC << MPI2_SGE_FLAGS_SHIFT))
		is_ग_लिखो = true;

	क्रम (i = 0; i < MPT_MIN_PHYS_SEGMENTS + ioc->facts.MaxChainDepth; i++) अणु

		sgl_flags =
		    (le32_to_cpu(sgel->FlagsLength) >> MPI2_SGE_FLAGS_SHIFT);

		चयन (sgl_flags & MPI2_SGE_FLAGS_ELEMENT_MASK) अणु
		हाल MPI2_SGE_FLAGS_CHAIN_ELEMENT:
			/*
			 * Helper function which on passing
			 * chain_buffer_dma वापसs chain_buffer. Get
			 * the भव address क्रम sgel->Address
			 */
			sgel_next =
				_base_get_chain_buffer_dma_to_chain_buffer(ioc,
						le32_to_cpu(sgel->Address));
			अगर (sgel_next == शून्य)
				वापस;
			/*
			 * This is coping 128 byte chain
			 * frame (not a host buffer)
			 */
			dst_chain_addr[sge_chain_count] =
				_base_get_chain(ioc,
					smid, sge_chain_count);
			src_chain_addr[sge_chain_count] =
						(व्योम *) sgel_next;
			dst_addr_phys = _base_get_chain_phys(ioc,
						smid, sge_chain_count);
			WARN_ON(dst_addr_phys > U32_MAX);
			sgel->Address =
				cpu_to_le32(lower_32_bits(dst_addr_phys));
			sgel = sgel_next;
			sge_chain_count++;
			अवरोध;
		हाल MPI2_SGE_FLAGS_SIMPLE_ELEMENT:
			अगर (is_ग_लिखो) अणु
				अगर (is_scsiio_req) अणु
					_base_clone_to_sys_mem(buff_ptr,
					    sg_virt(sg_scmd),
					    (le32_to_cpu(sgel->FlagsLength) &
					    0x00ffffff));
					/*
					 * FIXME: this relies on a a zero
					 * PCI mem_offset.
					 */
					sgel->Address =
					    cpu_to_le32((u32)buff_ptr_phys);
				पूर्ण अन्यथा अणु
					_base_clone_to_sys_mem(buff_ptr,
					    ioc->config_vaddr,
					    (le32_to_cpu(sgel->FlagsLength) &
					    0x00ffffff));
					sgel->Address =
					    cpu_to_le32((u32)buff_ptr_phys);
				पूर्ण
			पूर्ण
			buff_ptr += (le32_to_cpu(sgel->FlagsLength) &
			    0x00ffffff);
			buff_ptr_phys += (le32_to_cpu(sgel->FlagsLength) &
			    0x00ffffff);
			अगर ((le32_to_cpu(sgel->FlagsLength) &
			    (MPI2_SGE_FLAGS_END_OF_BUFFER
					<< MPI2_SGE_FLAGS_SHIFT)))
				जाओ eob_clone_chain;
			अन्यथा अणु
				/*
				 * Every single element in MPT will have
				 * associated sg_next. Better to sanity that
				 * sg_next is not शून्य, but it will be a bug
				 * अगर it is null.
				 */
				अगर (is_scsiio_req) अणु
					sg_scmd = sg_next(sg_scmd);
					अगर (sg_scmd)
						sgel++;
					अन्यथा
						जाओ eob_clone_chain;
				पूर्ण
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

eob_clone_chain:
	क्रम (i = 0; i < sge_chain_count; i++) अणु
		अगर (is_scsiio_req)
			_base_clone_to_sys_mem(dst_chain_addr[i],
				src_chain_addr[i], ioc->request_sz);
	पूर्ण
पूर्ण

/**
 *  mpt3sas_हटाओ_dead_ioc_func - kthपढ़ो context to हटाओ dead ioc
 * @arg: input argument, used to derive ioc
 *
 * Return:
 * 0 अगर controller is हटाओd from pci subप्रणाली.
 * -1 क्रम other हाल.
 */
अटल पूर्णांक mpt3sas_हटाओ_dead_ioc_func(व्योम *arg)
अणु
	काष्ठा MPT3SAS_ADAPTER *ioc = (काष्ठा MPT3SAS_ADAPTER *)arg;
	काष्ठा pci_dev *pdev;

	अगर (!ioc)
		वापस -1;

	pdev = ioc->pdev;
	अगर (!pdev)
		वापस -1;
	pci_stop_and_हटाओ_bus_device_locked(pdev);
	वापस 0;
पूर्ण

/**
 * _base_sync_drv_fw_बारtamp - Sync Drive-Fw TimeStamp.
 * @ioc: Per Adapter Object
 *
 * Return nothing.
 */
अटल व्योम _base_sync_drv_fw_बारtamp(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	Mpi26IoUnitControlRequest_t *mpi_request;
	Mpi26IoUnitControlReply_t *mpi_reply;
	u16 smid;
	kसमय_प्रकार current_समय;
	u64 TimeStamp = 0;
	u8 issue_reset = 0;

	mutex_lock(&ioc->scsih_cmds.mutex);
	अगर (ioc->scsih_cmds.status != MPT3_CMD_NOT_USED) अणु
		ioc_err(ioc, "scsih_cmd in use %s\n", __func__);
		जाओ out;
	पूर्ण
	ioc->scsih_cmds.status = MPT3_CMD_PENDING;
	smid = mpt3sas_base_get_smid(ioc, ioc->scsih_cb_idx);
	अगर (!smid) अणु
		ioc_err(ioc, "Failed obtaining a smid %s\n", __func__);
		ioc->scsih_cmds.status = MPT3_CMD_NOT_USED;
		जाओ out;
	पूर्ण
	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	ioc->scsih_cmds.smid = smid;
	स_रखो(mpi_request, 0, माप(Mpi26IoUnitControlRequest_t));
	mpi_request->Function = MPI2_FUNCTION_IO_UNIT_CONTROL;
	mpi_request->Operation = MPI26_CTRL_OP_SET_IOC_PARAMETER;
	mpi_request->IOCParameter = MPI26_SET_IOC_PARAMETER_SYNC_TIMESTAMP;
	current_समय = kसमय_get_real();
	TimeStamp = kसमय_प्रकारo_ms(current_समय);
	mpi_request->Reserved7 = cpu_to_le32(TimeStamp & 0xFFFFFFFF);
	mpi_request->IOCParameterValue = cpu_to_le32(TimeStamp >> 32);
	init_completion(&ioc->scsih_cmds.करोne);
	ioc->put_smid_शेष(ioc, smid);
	dinitprपूर्णांकk(ioc, ioc_info(ioc,
	    "Io Unit Control Sync TimeStamp (sending), @time %lld ms\n",
	    TimeStamp));
	रुको_क्रम_completion_समयout(&ioc->scsih_cmds.करोne,
		MPT3SAS_TIMESYNC_TIMEOUT_SECONDS*HZ);
	अगर (!(ioc->scsih_cmds.status & MPT3_CMD_COMPLETE)) अणु
		mpt3sas_check_cmd_समयout(ioc,
		    ioc->scsih_cmds.status, mpi_request,
		    माप(Mpi2SasIoUnitControlRequest_t)/4, issue_reset);
		जाओ issue_host_reset;
	पूर्ण
	अगर (ioc->scsih_cmds.status & MPT3_CMD_REPLY_VALID) अणु
		mpi_reply = ioc->scsih_cmds.reply;
		dinitprपूर्णांकk(ioc, ioc_info(ioc,
		    "Io Unit Control sync timestamp (complete): ioc_status(0x%04x), loginfo(0x%08x)\n",
		    le16_to_cpu(mpi_reply->IOCStatus),
		    le32_to_cpu(mpi_reply->IOCLogInfo)));
	पूर्ण
issue_host_reset:
	अगर (issue_reset)
		mpt3sas_base_hard_reset_handler(ioc, FORCE_BIG_HAMMER);
	ioc->scsih_cmds.status = MPT3_CMD_NOT_USED;
out:
	mutex_unlock(&ioc->scsih_cmds.mutex);
पूर्ण

/**
 * _base_fault_reset_work - workq handling ioc fault conditions
 * @work: input argument, used to derive ioc
 *
 * Context: sleep.
 */
अटल व्योम
_base_fault_reset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा MPT3SAS_ADAPTER *ioc =
	    container_of(work, काष्ठा MPT3SAS_ADAPTER, fault_reset_work.work);
	अचिन्हित दीर्घ	 flags;
	u32 करोorbell;
	पूर्णांक rc;
	काष्ठा task_काष्ठा *p;


	spin_lock_irqsave(&ioc->ioc_reset_in_progress_lock, flags);
	अगर ((ioc->shost_recovery && (ioc->ioc_coredump_loop == 0)) ||
			ioc->pci_error_recovery)
		जाओ rearm_समयr;
	spin_unlock_irqrestore(&ioc->ioc_reset_in_progress_lock, flags);

	करोorbell = mpt3sas_base_get_iocstate(ioc, 0);
	अगर ((करोorbell & MPI2_IOC_STATE_MASK) == MPI2_IOC_STATE_MASK) अणु
		ioc_err(ioc, "SAS host is non-operational !!!!\n");

		/* It may be possible that EEH recovery can resolve some of
		 * pci bus failure issues rather removing the dead ioc function
		 * by considering controller is in a non-operational state. So
		 * here priority is given to the EEH recovery. If it करोesn't
		 * not resolve this issue, mpt3sas driver will consider this
		 * controller to non-operational state and हटाओ the dead ioc
		 * function.
		 */
		अगर (ioc->non_operational_loop++ < 5) अणु
			spin_lock_irqsave(&ioc->ioc_reset_in_progress_lock,
							 flags);
			जाओ rearm_समयr;
		पूर्ण

		/*
		 * Call _scsih_flush_pending_cmds callback so that we flush all
		 * pending commands back to OS. This call is required to aovid
		 * deadlock at block layer. Dead IOC will fail to करो diag reset,
		 * and this call is safe since dead ioc will never वापस any
		 * command back from HW.
		 */
		ioc->schedule_dead_ioc_flush_running_cmds(ioc);
		/*
		 * Set हटाओ_host flag early since kernel thपढ़ो will
		 * take some समय to execute.
		 */
		ioc->हटाओ_host = 1;
		/*Remove the Dead Host */
		p = kthपढ़ो_run(mpt3sas_हटाओ_dead_ioc_func, ioc,
		    "%s_dead_ioc_%d", ioc->driver_name, ioc->id);
		अगर (IS_ERR(p))
			ioc_err(ioc, "%s: Running mpt3sas_dead_ioc thread failed !!!!\n",
				__func__);
		अन्यथा
			ioc_err(ioc, "%s: Running mpt3sas_dead_ioc thread success !!!!\n",
				__func__);
		वापस; /* करोn't rearm समयr */
	पूर्ण

	अगर ((करोorbell & MPI2_IOC_STATE_MASK) == MPI2_IOC_STATE_COREDUMP) अणु
		u8 समयout = (ioc->manu_pg11.CoreDumpTOSec) ?
		    ioc->manu_pg11.CoreDumpTOSec :
		    MPT3SAS_DEFAULT_COREDUMP_TIMEOUT_SECONDS;

		समयout /= (FAULT_POLLING_INTERVAL/1000);

		अगर (ioc->ioc_coredump_loop == 0) अणु
			mpt3sas_prपूर्णांक_coredump_info(ioc,
			    करोorbell & MPI2_DOORBELL_DATA_MASK);
			/* करो not accept any IOs and disable the पूर्णांकerrupts */
			spin_lock_irqsave(
			    &ioc->ioc_reset_in_progress_lock, flags);
			ioc->shost_recovery = 1;
			spin_unlock_irqrestore(
			    &ioc->ioc_reset_in_progress_lock, flags);
			mpt3sas_base_mask_पूर्णांकerrupts(ioc);
			_base_clear_outstanding_commands(ioc);
		पूर्ण

		ioc_info(ioc, "%s: CoreDump loop %d.",
		    __func__, ioc->ioc_coredump_loop);

		/* Wait until CoreDump completes or बार out */
		अगर (ioc->ioc_coredump_loop++ < समयout) अणु
			spin_lock_irqsave(
			    &ioc->ioc_reset_in_progress_lock, flags);
			जाओ rearm_समयr;
		पूर्ण
	पूर्ण

	अगर (ioc->ioc_coredump_loop) अणु
		अगर ((करोorbell & MPI2_IOC_STATE_MASK) != MPI2_IOC_STATE_COREDUMP)
			ioc_err(ioc, "%s: CoreDump completed. LoopCount: %d",
			    __func__, ioc->ioc_coredump_loop);
		अन्यथा
			ioc_err(ioc, "%s: CoreDump Timed out. LoopCount: %d",
			    __func__, ioc->ioc_coredump_loop);
		ioc->ioc_coredump_loop = MPT3SAS_COREDUMP_LOOP_DONE;
	पूर्ण
	ioc->non_operational_loop = 0;
	अगर ((करोorbell & MPI2_IOC_STATE_MASK) != MPI2_IOC_STATE_OPERATIONAL) अणु
		rc = mpt3sas_base_hard_reset_handler(ioc, FORCE_BIG_HAMMER);
		ioc_warn(ioc, "%s: hard reset: %s\n",
			 __func__, rc == 0 ? "success" : "failed");
		करोorbell = mpt3sas_base_get_iocstate(ioc, 0);
		अगर ((करोorbell & MPI2_IOC_STATE_MASK) == MPI2_IOC_STATE_FAULT) अणु
			mpt3sas_prपूर्णांक_fault_code(ioc, करोorbell &
			    MPI2_DOORBELL_DATA_MASK);
		पूर्ण अन्यथा अगर ((करोorbell & MPI2_IOC_STATE_MASK) ==
		    MPI2_IOC_STATE_COREDUMP)
			mpt3sas_prपूर्णांक_coredump_info(ioc, करोorbell &
			    MPI2_DOORBELL_DATA_MASK);
		अगर (rc && (करोorbell & MPI2_IOC_STATE_MASK) !=
		    MPI2_IOC_STATE_OPERATIONAL)
			वापस; /* करोn't rearm समयr */
	पूर्ण
	ioc->ioc_coredump_loop = 0;
	अगर (ioc->समय_sync_पूर्णांकerval &&
	    ++ioc->बारtamp_update_count >= ioc->समय_sync_पूर्णांकerval) अणु
		ioc->बारtamp_update_count = 0;
		_base_sync_drv_fw_बारtamp(ioc);
	पूर्ण
	spin_lock_irqsave(&ioc->ioc_reset_in_progress_lock, flags);
 rearm_समयr:
	अगर (ioc->fault_reset_work_q)
		queue_delayed_work(ioc->fault_reset_work_q,
		    &ioc->fault_reset_work,
		    msecs_to_jअगरfies(FAULT_POLLING_INTERVAL));
	spin_unlock_irqrestore(&ioc->ioc_reset_in_progress_lock, flags);
पूर्ण

/**
 * mpt3sas_base_start_watchकरोg - start the fault_reset_work_q
 * @ioc: per adapter object
 *
 * Context: sleep.
 */
व्योम
mpt3sas_base_start_watchकरोg(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	अचिन्हित दीर्घ	 flags;

	अगर (ioc->fault_reset_work_q)
		वापस;

	ioc->बारtamp_update_count = 0;
	/* initialize fault polling */

	INIT_DELAYED_WORK(&ioc->fault_reset_work, _base_fault_reset_work);
	snम_लिखो(ioc->fault_reset_work_q_name,
	    माप(ioc->fault_reset_work_q_name), "poll_%s%d_status",
	    ioc->driver_name, ioc->id);
	ioc->fault_reset_work_q =
		create_singlethपढ़ो_workqueue(ioc->fault_reset_work_q_name);
	अगर (!ioc->fault_reset_work_q) अणु
		ioc_err(ioc, "%s: failed (line=%d)\n", __func__, __LINE__);
		वापस;
	पूर्ण
	spin_lock_irqsave(&ioc->ioc_reset_in_progress_lock, flags);
	अगर (ioc->fault_reset_work_q)
		queue_delayed_work(ioc->fault_reset_work_q,
		    &ioc->fault_reset_work,
		    msecs_to_jअगरfies(FAULT_POLLING_INTERVAL));
	spin_unlock_irqrestore(&ioc->ioc_reset_in_progress_lock, flags);
पूर्ण

/**
 * mpt3sas_base_stop_watchकरोg - stop the fault_reset_work_q
 * @ioc: per adapter object
 *
 * Context: sleep.
 */
व्योम
mpt3sas_base_stop_watchकरोg(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा workqueue_काष्ठा *wq;

	spin_lock_irqsave(&ioc->ioc_reset_in_progress_lock, flags);
	wq = ioc->fault_reset_work_q;
	ioc->fault_reset_work_q = शून्य;
	spin_unlock_irqrestore(&ioc->ioc_reset_in_progress_lock, flags);
	अगर (wq) अणु
		अगर (!cancel_delayed_work_sync(&ioc->fault_reset_work))
			flush_workqueue(wq);
		destroy_workqueue(wq);
	पूर्ण
पूर्ण

/**
 * mpt3sas_base_fault_info - verbose translation of firmware FAULT code
 * @ioc: per adapter object
 * @fault_code: fault code
 */
व्योम
mpt3sas_base_fault_info(काष्ठा MPT3SAS_ADAPTER *ioc , u16 fault_code)
अणु
	ioc_err(ioc, "fault_state(0x%04x)!\n", fault_code);
पूर्ण

/**
 * mpt3sas_base_coredump_info - verbose translation of firmware CoreDump state
 * @ioc: per adapter object
 * @fault_code: fault code
 *
 * Return nothing.
 */
व्योम
mpt3sas_base_coredump_info(काष्ठा MPT3SAS_ADAPTER *ioc, u16 fault_code)
अणु
	ioc_err(ioc, "coredump_state(0x%04x)!\n", fault_code);
पूर्ण

/**
 * mpt3sas_base_रुको_क्रम_coredump_completion - Wait until coredump
 * completes or बार out
 * @ioc: per adapter object
 * @caller: caller function name
 *
 * Returns 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_base_रुको_क्रम_coredump_completion(काष्ठा MPT3SAS_ADAPTER *ioc,
		स्थिर अक्षर *caller)
अणु
	u8 समयout = (ioc->manu_pg11.CoreDumpTOSec) ?
			ioc->manu_pg11.CoreDumpTOSec :
			MPT3SAS_DEFAULT_COREDUMP_TIMEOUT_SECONDS;

	पूर्णांक ioc_state = _base_रुको_on_iocstate(ioc, MPI2_IOC_STATE_FAULT,
					समयout);

	अगर (ioc_state)
		ioc_err(ioc,
		    "%s: CoreDump timed out. (ioc_state=0x%x)\n",
		    caller, ioc_state);
	अन्यथा
		ioc_info(ioc,
		    "%s: CoreDump completed. (ioc_state=0x%x)\n",
		    caller, ioc_state);

	वापस ioc_state;
पूर्ण

/**
 * mpt3sas_halt_firmware - halt's mpt controller firmware
 * @ioc: per adapter object
 *
 * For debugging समयout related issues.  Writing 0xCOFFEE00
 * to the करोorbell रेजिस्टर will halt controller firmware. With
 * the purpose to stop both driver and firmware, the enduser can
 * obtain a ring buffer from controller UART.
 */
व्योम
mpt3sas_halt_firmware(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	u32 करोorbell;

	अगर (!ioc->fwfault_debug)
		वापस;

	dump_stack();

	करोorbell = ioc->base_पढ़ोl(&ioc->chip->Doorbell);
	अगर ((करोorbell & MPI2_IOC_STATE_MASK) == MPI2_IOC_STATE_FAULT) अणु
		mpt3sas_prपूर्णांक_fault_code(ioc, करोorbell &
		    MPI2_DOORBELL_DATA_MASK);
	पूर्ण अन्यथा अगर ((करोorbell & MPI2_IOC_STATE_MASK) ==
	    MPI2_IOC_STATE_COREDUMP) अणु
		mpt3sas_prपूर्णांक_coredump_info(ioc, करोorbell &
		    MPI2_DOORBELL_DATA_MASK);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0xC0FFEE00, &ioc->chip->Doorbell);
		ioc_err(ioc, "Firmware is halted due to command timeout\n");
	पूर्ण

	अगर (ioc->fwfault_debug == 2)
		क्रम (;;)
			;
	अन्यथा
		panic("panic in %s\n", __func__);
पूर्ण

/**
 * _base_sas_ioc_info - verbose translation of the ioc status
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @request_hdr: request mf
 */
अटल व्योम
_base_sas_ioc_info(काष्ठा MPT3SAS_ADAPTER *ioc, MPI2DefaultReply_t *mpi_reply,
	MPI2RequestHeader_t *request_hdr)
अणु
	u16 ioc_status = le16_to_cpu(mpi_reply->IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अक्षर *desc = शून्य;
	u16 frame_sz;
	अक्षर *func_str = शून्य;

	/* SCSI_IO, RAID_PASS are handled from _scsih_scsi_ioc_info */
	अगर (request_hdr->Function == MPI2_FUNCTION_SCSI_IO_REQUEST ||
	    request_hdr->Function == MPI2_FUNCTION_RAID_SCSI_IO_PASSTHROUGH ||
	    request_hdr->Function == MPI2_FUNCTION_EVENT_NOTIFICATION)
		वापस;

	अगर (ioc_status == MPI2_IOCSTATUS_CONFIG_INVALID_PAGE)
		वापस;
	/*
	 * Older Firmware version करोesn't support driver trigger pages.
	 * So, skip displaying 'config invalid type' type
	 * of error message.
	 */
	अगर (request_hdr->Function == MPI2_FUNCTION_CONFIG) अणु
		Mpi2ConfigRequest_t *rqst = (Mpi2ConfigRequest_t *)request_hdr;

		अगर ((rqst->ExtPageType ==
		    MPI2_CONFIG_EXTPAGETYPE_DRIVER_PERSISTENT_TRIGGER) &&
		    !(ioc->logging_level & MPT_DEBUG_CONFIG)) अणु
			वापस;
		पूर्ण
	पूर्ण

	चयन (ioc_status) अणु

/****************************************************************************
*  Common IOCStatus values क्रम all replies
****************************************************************************/

	हाल MPI2_IOCSTATUS_INVALID_FUNCTION:
		desc = "invalid function";
		अवरोध;
	हाल MPI2_IOCSTATUS_BUSY:
		desc = "busy";
		अवरोध;
	हाल MPI2_IOCSTATUS_INVALID_SGL:
		desc = "invalid sgl";
		अवरोध;
	हाल MPI2_IOCSTATUS_INTERNAL_ERROR:
		desc = "internal error";
		अवरोध;
	हाल MPI2_IOCSTATUS_INVALID_VPID:
		desc = "invalid vpid";
		अवरोध;
	हाल MPI2_IOCSTATUS_INSUFFICIENT_RESOURCES:
		desc = "insufficient resources";
		अवरोध;
	हाल MPI2_IOCSTATUS_INSUFFICIENT_POWER:
		desc = "insufficient power";
		अवरोध;
	हाल MPI2_IOCSTATUS_INVALID_FIELD:
		desc = "invalid field";
		अवरोध;
	हाल MPI2_IOCSTATUS_INVALID_STATE:
		desc = "invalid state";
		अवरोध;
	हाल MPI2_IOCSTATUS_OP_STATE_NOT_SUPPORTED:
		desc = "op state not supported";
		अवरोध;

/****************************************************************************
*  Config IOCStatus values
****************************************************************************/

	हाल MPI2_IOCSTATUS_CONFIG_INVALID_ACTION:
		desc = "config invalid action";
		अवरोध;
	हाल MPI2_IOCSTATUS_CONFIG_INVALID_TYPE:
		desc = "config invalid type";
		अवरोध;
	हाल MPI2_IOCSTATUS_CONFIG_INVALID_PAGE:
		desc = "config invalid page";
		अवरोध;
	हाल MPI2_IOCSTATUS_CONFIG_INVALID_DATA:
		desc = "config invalid data";
		अवरोध;
	हाल MPI2_IOCSTATUS_CONFIG_NO_DEFAULTS:
		desc = "config no defaults";
		अवरोध;
	हाल MPI2_IOCSTATUS_CONFIG_CANT_COMMIT:
		desc = "config cant commit";
		अवरोध;

/****************************************************************************
*  SCSI IO Reply
****************************************************************************/

	हाल MPI2_IOCSTATUS_SCSI_RECOVERED_ERROR:
	हाल MPI2_IOCSTATUS_SCSI_INVALID_DEVHANDLE:
	हाल MPI2_IOCSTATUS_SCSI_DEVICE_NOT_THERE:
	हाल MPI2_IOCSTATUS_SCSI_DATA_OVERRUN:
	हाल MPI2_IOCSTATUS_SCSI_DATA_UNDERRUN:
	हाल MPI2_IOCSTATUS_SCSI_IO_DATA_ERROR:
	हाल MPI2_IOCSTATUS_SCSI_PROTOCOL_ERROR:
	हाल MPI2_IOCSTATUS_SCSI_TASK_TERMINATED:
	हाल MPI2_IOCSTATUS_SCSI_RESIDUAL_MISMATCH:
	हाल MPI2_IOCSTATUS_SCSI_TASK_MGMT_FAILED:
	हाल MPI2_IOCSTATUS_SCSI_IOC_TERMINATED:
	हाल MPI2_IOCSTATUS_SCSI_EXT_TERMINATED:
		अवरोध;

/****************************************************************************
*  For use by SCSI Initiator and SCSI Target end-to-end data protection
****************************************************************************/

	हाल MPI2_IOCSTATUS_EEDP_GUARD_ERROR:
		desc = "eedp guard error";
		अवरोध;
	हाल MPI2_IOCSTATUS_EEDP_REF_TAG_ERROR:
		desc = "eedp ref tag error";
		अवरोध;
	हाल MPI2_IOCSTATUS_EEDP_APP_TAG_ERROR:
		desc = "eedp app tag error";
		अवरोध;

/****************************************************************************
*  SCSI Target values
****************************************************************************/

	हाल MPI2_IOCSTATUS_TARGET_INVALID_IO_INDEX:
		desc = "target invalid io index";
		अवरोध;
	हाल MPI2_IOCSTATUS_TARGET_ABORTED:
		desc = "target aborted";
		अवरोध;
	हाल MPI2_IOCSTATUS_TARGET_NO_CONN_RETRYABLE:
		desc = "target no conn retryable";
		अवरोध;
	हाल MPI2_IOCSTATUS_TARGET_NO_CONNECTION:
		desc = "target no connection";
		अवरोध;
	हाल MPI2_IOCSTATUS_TARGET_XFER_COUNT_MISMATCH:
		desc = "target xfer count mismatch";
		अवरोध;
	हाल MPI2_IOCSTATUS_TARGET_DATA_OFFSET_ERROR:
		desc = "target data offset error";
		अवरोध;
	हाल MPI2_IOCSTATUS_TARGET_TOO_MUCH_WRITE_DATA:
		desc = "target too much write data";
		अवरोध;
	हाल MPI2_IOCSTATUS_TARGET_IU_TOO_SHORT:
		desc = "target iu too short";
		अवरोध;
	हाल MPI2_IOCSTATUS_TARGET_ACK_NAK_TIMEOUT:
		desc = "target ack nak timeout";
		अवरोध;
	हाल MPI2_IOCSTATUS_TARGET_NAK_RECEIVED:
		desc = "target nak received";
		अवरोध;

/****************************************************************************
*  Serial Attached SCSI values
****************************************************************************/

	हाल MPI2_IOCSTATUS_SAS_SMP_REQUEST_FAILED:
		desc = "smp request failed";
		अवरोध;
	हाल MPI2_IOCSTATUS_SAS_SMP_DATA_OVERRUN:
		desc = "smp data overrun";
		अवरोध;

/****************************************************************************
*  Diagnostic Buffer Post / Diagnostic Release values
****************************************************************************/

	हाल MPI2_IOCSTATUS_DIAGNOSTIC_RELEASED:
		desc = "diagnostic released";
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!desc)
		वापस;

	चयन (request_hdr->Function) अणु
	हाल MPI2_FUNCTION_CONFIG:
		frame_sz = माप(Mpi2ConfigRequest_t) + ioc->sge_size;
		func_str = "config_page";
		अवरोध;
	हाल MPI2_FUNCTION_SCSI_TASK_MGMT:
		frame_sz = माप(Mpi2SCSITaskManagementRequest_t);
		func_str = "task_mgmt";
		अवरोध;
	हाल MPI2_FUNCTION_SAS_IO_UNIT_CONTROL:
		frame_sz = माप(Mpi2SasIoUnitControlRequest_t);
		func_str = "sas_iounit_ctl";
		अवरोध;
	हाल MPI2_FUNCTION_SCSI_ENCLOSURE_PROCESSOR:
		frame_sz = माप(Mpi2SepRequest_t);
		func_str = "enclosure";
		अवरोध;
	हाल MPI2_FUNCTION_IOC_INIT:
		frame_sz = माप(Mpi2IOCInitRequest_t);
		func_str = "ioc_init";
		अवरोध;
	हाल MPI2_FUNCTION_PORT_ENABLE:
		frame_sz = माप(Mpi2PortEnableRequest_t);
		func_str = "port_enable";
		अवरोध;
	हाल MPI2_FUNCTION_SMP_PASSTHROUGH:
		frame_sz = माप(Mpi2SmpPassthroughRequest_t) + ioc->sge_size;
		func_str = "smp_passthru";
		अवरोध;
	हाल MPI2_FUNCTION_NVME_ENCAPSULATED:
		frame_sz = माप(Mpi26NVMeEncapsulatedRequest_t) +
		    ioc->sge_size;
		func_str = "nvme_encapsulated";
		अवरोध;
	शेष:
		frame_sz = 32;
		func_str = "unknown";
		अवरोध;
	पूर्ण

	ioc_warn(ioc, "ioc_status: %s(0x%04x), request(0x%p),(%s)\n",
		 desc, ioc_status, request_hdr, func_str);

	_debug_dump_mf(request_hdr, frame_sz/4);
पूर्ण

/**
 * _base_display_event_data - verbose translation of firmware asyn events
 * @ioc: per adapter object
 * @mpi_reply: reply mf payload वापसed from firmware
 */
अटल व्योम
_base_display_event_data(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2EventNotअगरicationReply_t *mpi_reply)
अणु
	अक्षर *desc = शून्य;
	u16 event;

	अगर (!(ioc->logging_level & MPT_DEBUG_EVENTS))
		वापस;

	event = le16_to_cpu(mpi_reply->Event);

	चयन (event) अणु
	हाल MPI2_EVENT_LOG_DATA:
		desc = "Log Data";
		अवरोध;
	हाल MPI2_EVENT_STATE_CHANGE:
		desc = "Status Change";
		अवरोध;
	हाल MPI2_EVENT_HARD_RESET_RECEIVED:
		desc = "Hard Reset Received";
		अवरोध;
	हाल MPI2_EVENT_EVENT_CHANGE:
		desc = "Event Change";
		अवरोध;
	हाल MPI2_EVENT_SAS_DEVICE_STATUS_CHANGE:
		desc = "Device Status Change";
		अवरोध;
	हाल MPI2_EVENT_IR_OPERATION_STATUS:
		अगर (!ioc->hide_ir_msg)
			desc = "IR Operation Status";
		अवरोध;
	हाल MPI2_EVENT_SAS_DISCOVERY:
	अणु
		Mpi2EventDataSasDiscovery_t *event_data =
		    (Mpi2EventDataSasDiscovery_t *)mpi_reply->EventData;
		ioc_info(ioc, "Discovery: (%s)",
			 event_data->ReasonCode == MPI2_EVENT_SAS_DISC_RC_STARTED ?
			 "start" : "stop");
		अगर (event_data->DiscoveryStatus)
			pr_cont(" discovery_status(0x%08x)",
			    le32_to_cpu(event_data->DiscoveryStatus));
		pr_cont("\n");
		वापस;
	पूर्ण
	हाल MPI2_EVENT_SAS_BROADCAST_PRIMITIVE:
		desc = "SAS Broadcast Primitive";
		अवरोध;
	हाल MPI2_EVENT_SAS_INIT_DEVICE_STATUS_CHANGE:
		desc = "SAS Init Device Status Change";
		अवरोध;
	हाल MPI2_EVENT_SAS_INIT_TABLE_OVERFLOW:
		desc = "SAS Init Table Overflow";
		अवरोध;
	हाल MPI2_EVENT_SAS_TOPOLOGY_CHANGE_LIST:
		desc = "SAS Topology Change List";
		अवरोध;
	हाल MPI2_EVENT_SAS_ENCL_DEVICE_STATUS_CHANGE:
		desc = "SAS Enclosure Device Status Change";
		अवरोध;
	हाल MPI2_EVENT_IR_VOLUME:
		अगर (!ioc->hide_ir_msg)
			desc = "IR Volume";
		अवरोध;
	हाल MPI2_EVENT_IR_PHYSICAL_DISK:
		अगर (!ioc->hide_ir_msg)
			desc = "IR Physical Disk";
		अवरोध;
	हाल MPI2_EVENT_IR_CONFIGURATION_CHANGE_LIST:
		अगर (!ioc->hide_ir_msg)
			desc = "IR Configuration Change List";
		अवरोध;
	हाल MPI2_EVENT_LOG_ENTRY_ADDED:
		अगर (!ioc->hide_ir_msg)
			desc = "Log Entry Added";
		अवरोध;
	हाल MPI2_EVENT_TEMP_THRESHOLD:
		desc = "Temperature Threshold";
		अवरोध;
	हाल MPI2_EVENT_ACTIVE_CABLE_EXCEPTION:
		desc = "Cable Event";
		अवरोध;
	हाल MPI2_EVENT_SAS_DEVICE_DISCOVERY_ERROR:
		desc = "SAS Device Discovery Error";
		अवरोध;
	हाल MPI2_EVENT_PCIE_DEVICE_STATUS_CHANGE:
		desc = "PCIE Device Status Change";
		अवरोध;
	हाल MPI2_EVENT_PCIE_ENUMERATION:
	अणु
		Mpi26EventDataPCIeEnumeration_t *event_data =
			(Mpi26EventDataPCIeEnumeration_t *)mpi_reply->EventData;
		ioc_info(ioc, "PCIE Enumeration: (%s)",
			 event_data->ReasonCode == MPI26_EVENT_PCIE_ENUM_RC_STARTED ?
			 "start" : "stop");
		अगर (event_data->EnumerationStatus)
			pr_cont("enumeration_status(0x%08x)",
				le32_to_cpu(event_data->EnumerationStatus));
		pr_cont("\n");
		वापस;
	पूर्ण
	हाल MPI2_EVENT_PCIE_TOPOLOGY_CHANGE_LIST:
		desc = "PCIE Topology Change List";
		अवरोध;
	पूर्ण

	अगर (!desc)
		वापस;

	ioc_info(ioc, "%s\n", desc);
पूर्ण

/**
 * _base_sas_log_info - verbose translation of firmware log info
 * @ioc: per adapter object
 * @log_info: log info
 */
अटल व्योम
_base_sas_log_info(काष्ठा MPT3SAS_ADAPTER *ioc , u32 log_info)
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
	अक्षर *originator_str = शून्य;

	sas_loginfo.loginfo = log_info;
	अगर (sas_loginfo.dw.bus_type != 3 /*SAS*/)
		वापस;

	/* each nexus loss loginfo */
	अगर (log_info == 0x31170000)
		वापस;

	/* eat the loginfos associated with task पातs */
	अगर (ioc->ignore_loginfos && (log_info == 0x30050000 || log_info ==
	    0x31140000 || log_info == 0x31130000))
		वापस;

	चयन (sas_loginfo.dw.originator) अणु
	हाल 0:
		originator_str = "IOP";
		अवरोध;
	हाल 1:
		originator_str = "PL";
		अवरोध;
	हाल 2:
		अगर (!ioc->hide_ir_msg)
			originator_str = "IR";
		अन्यथा
			originator_str = "WarpDrive";
		अवरोध;
	पूर्ण

	ioc_warn(ioc, "log_info(0x%08x): originator(%s), code(0x%02x), sub_code(0x%04x)\n",
		 log_info,
		 originator_str, sas_loginfo.dw.code, sas_loginfo.dw.subcode);
पूर्ण

/**
 * _base_display_reply_info -
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @msix_index: MSIX table index supplied by the OS
 * @reply: reply message frame(lower 32bit addr)
 */
अटल व्योम
_base_display_reply_info(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid, u8 msix_index,
	u32 reply)
अणु
	MPI2DefaultReply_t *mpi_reply;
	u16 ioc_status;
	u32 loginfo = 0;

	mpi_reply = mpt3sas_base_get_reply_virt_addr(ioc, reply);
	अगर (unlikely(!mpi_reply)) अणु
		ioc_err(ioc, "mpi_reply not valid at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस;
	पूर्ण
	ioc_status = le16_to_cpu(mpi_reply->IOCStatus);

	अगर ((ioc_status & MPI2_IOCSTATUS_MASK) &&
	    (ioc->logging_level & MPT_DEBUG_REPLY)) अणु
		_base_sas_ioc_info(ioc , mpi_reply,
		   mpt3sas_base_get_msg_frame(ioc, smid));
	पूर्ण

	अगर (ioc_status & MPI2_IOCSTATUS_FLAG_LOG_INFO_AVAILABLE) अणु
		loginfo = le32_to_cpu(mpi_reply->IOCLogInfo);
		_base_sas_log_info(ioc, loginfo);
	पूर्ण

	अगर (ioc_status || loginfo) अणु
		ioc_status &= MPI2_IOCSTATUS_MASK;
		mpt3sas_trigger_mpi(ioc, ioc_status, loginfo);
	पूर्ण
पूर्ण

/**
 * mpt3sas_base_करोne - base पूर्णांकernal command completion routine
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @msix_index: MSIX table index supplied by the OS
 * @reply: reply message frame(lower 32bit addr)
 *
 * Return:
 * 1 meaning mf should be मुक्तd from _base_पूर्णांकerrupt
 * 0 means the mf is मुक्तd from this function.
 */
u8
mpt3sas_base_करोne(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid, u8 msix_index,
	u32 reply)
अणु
	MPI2DefaultReply_t *mpi_reply;

	mpi_reply = mpt3sas_base_get_reply_virt_addr(ioc, reply);
	अगर (mpi_reply && mpi_reply->Function == MPI2_FUNCTION_EVENT_ACK)
		वापस mpt3sas_check_क्रम_pending_पूर्णांकernal_cmds(ioc, smid);

	अगर (ioc->base_cmds.status == MPT3_CMD_NOT_USED)
		वापस 1;

	ioc->base_cmds.status |= MPT3_CMD_COMPLETE;
	अगर (mpi_reply) अणु
		ioc->base_cmds.status |= MPT3_CMD_REPLY_VALID;
		स_नकल(ioc->base_cmds.reply, mpi_reply, mpi_reply->MsgLength*4);
	पूर्ण
	ioc->base_cmds.status &= ~MPT3_CMD_PENDING;

	complete(&ioc->base_cmds.करोne);
	वापस 1;
पूर्ण

/**
 * _base_async_event - मुख्य callback handler क्रम firmware asyn events
 * @ioc: per adapter object
 * @msix_index: MSIX table index supplied by the OS
 * @reply: reply message frame(lower 32bit addr)
 *
 * Return:
 * 1 meaning mf should be मुक्तd from _base_पूर्णांकerrupt
 * 0 means the mf is मुक्तd from this function.
 */
अटल u8
_base_async_event(काष्ठा MPT3SAS_ADAPTER *ioc, u8 msix_index, u32 reply)
अणु
	Mpi2EventNotअगरicationReply_t *mpi_reply;
	Mpi2EventAckRequest_t *ack_request;
	u16 smid;
	काष्ठा _event_ack_list *delayed_event_ack;

	mpi_reply = mpt3sas_base_get_reply_virt_addr(ioc, reply);
	अगर (!mpi_reply)
		वापस 1;
	अगर (mpi_reply->Function != MPI2_FUNCTION_EVENT_NOTIFICATION)
		वापस 1;

	_base_display_event_data(ioc, mpi_reply);

	अगर (!(mpi_reply->AckRequired & MPI2_EVENT_NOTIFICATION_ACK_REQUIRED))
		जाओ out;
	smid = mpt3sas_base_get_smid(ioc, ioc->base_cb_idx);
	अगर (!smid) अणु
		delayed_event_ack = kzalloc(माप(*delayed_event_ack),
					GFP_ATOMIC);
		अगर (!delayed_event_ack)
			जाओ out;
		INIT_LIST_HEAD(&delayed_event_ack->list);
		delayed_event_ack->Event = mpi_reply->Event;
		delayed_event_ack->EventContext = mpi_reply->EventContext;
		list_add_tail(&delayed_event_ack->list,
				&ioc->delayed_event_ack_list);
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "DELAYED: EVENT ACK: event (0x%04x)\n",
				    le16_to_cpu(mpi_reply->Event)));
		जाओ out;
	पूर्ण

	ack_request = mpt3sas_base_get_msg_frame(ioc, smid);
	स_रखो(ack_request, 0, माप(Mpi2EventAckRequest_t));
	ack_request->Function = MPI2_FUNCTION_EVENT_ACK;
	ack_request->Event = mpi_reply->Event;
	ack_request->EventContext = mpi_reply->EventContext;
	ack_request->VF_ID = 0;  /* TODO */
	ack_request->VP_ID = 0;
	ioc->put_smid_शेष(ioc, smid);

 out:

	/* scsih callback handler */
	mpt3sas_scsih_event_callback(ioc, msix_index, reply);

	/* ctl callback handler */
	mpt3sas_ctl_event_callback(ioc, msix_index, reply);

	वापस 1;
पूर्ण

अटल काष्ठा scsiio_tracker *
_get_st_from_smid(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid)
अणु
	काष्ठा scsi_cmnd *cmd;

	अगर (WARN_ON(!smid) ||
	    WARN_ON(smid >= ioc->hi_priority_smid))
		वापस शून्य;

	cmd = mpt3sas_scsih_scsi_lookup_get(ioc, smid);
	अगर (cmd)
		वापस scsi_cmd_priv(cmd);

	वापस शून्य;
पूर्ण

/**
 * _base_get_cb_idx - obtain the callback index
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 *
 * Return: callback index.
 */
अटल u8
_base_get_cb_idx(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid)
अणु
	पूर्णांक i;
	u16 ctl_smid = ioc->scsiio_depth - INTERNAL_SCSIIO_CMDS_COUNT + 1;
	u8 cb_idx = 0xFF;

	अगर (smid < ioc->hi_priority_smid) अणु
		काष्ठा scsiio_tracker *st;

		अगर (smid < ctl_smid) अणु
			st = _get_st_from_smid(ioc, smid);
			अगर (st)
				cb_idx = st->cb_idx;
		पूर्ण अन्यथा अगर (smid == ctl_smid)
			cb_idx = ioc->ctl_cb_idx;
	पूर्ण अन्यथा अगर (smid < ioc->पूर्णांकernal_smid) अणु
		i = smid - ioc->hi_priority_smid;
		cb_idx = ioc->hpr_lookup[i].cb_idx;
	पूर्ण अन्यथा अगर (smid <= ioc->hba_queue_depth) अणु
		i = smid - ioc->पूर्णांकernal_smid;
		cb_idx = ioc->पूर्णांकernal_lookup[i].cb_idx;
	पूर्ण
	वापस cb_idx;
पूर्ण

/**
 * mpt3sas_base_mask_पूर्णांकerrupts - disable पूर्णांकerrupts
 * @ioc: per adapter object
 *
 * Disabling ResetIRQ, Reply and Doorbell Interrupts
 */
व्योम
mpt3sas_base_mask_पूर्णांकerrupts(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	u32 him_रेजिस्टर;

	ioc->mask_पूर्णांकerrupts = 1;
	him_रेजिस्टर = ioc->base_पढ़ोl(&ioc->chip->HostInterruptMask);
	him_रेजिस्टर |= MPI2_HIM_DIM + MPI2_HIM_RIM + MPI2_HIM_RESET_IRQ_MASK;
	ग_लिखोl(him_रेजिस्टर, &ioc->chip->HostInterruptMask);
	ioc->base_पढ़ोl(&ioc->chip->HostInterruptMask);
पूर्ण

/**
 * mpt3sas_base_unmask_पूर्णांकerrupts - enable पूर्णांकerrupts
 * @ioc: per adapter object
 *
 * Enabling only Reply Interrupts
 */
व्योम
mpt3sas_base_unmask_पूर्णांकerrupts(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	u32 him_रेजिस्टर;

	him_रेजिस्टर = ioc->base_पढ़ोl(&ioc->chip->HostInterruptMask);
	him_रेजिस्टर &= ~MPI2_HIM_RIM;
	ग_लिखोl(him_रेजिस्टर, &ioc->chip->HostInterruptMask);
	ioc->mask_पूर्णांकerrupts = 0;
पूर्ण

जोड़ reply_descriptor अणु
	u64 word;
	काष्ठा अणु
		u32 low;
		u32 high;
	पूर्ण u;
पूर्ण;

अटल u32 base_mod64(u64 भागidend, u32 भागisor)
अणु
	u32 reमुख्यder;

	अगर (!भागisor)
		pr_err("mpt3sas: DIVISOR is zero, in div fn\n");
	reमुख्यder = करो_भाग(भागidend, भागisor);
	वापस reमुख्यder;
पूर्ण

/**
 * _base_process_reply_queue - Process reply descriptors from reply
 *		descriptor post queue.
 * @reply_q: per IRQ's reply queue object.
 *
 * Return: number of reply descriptors processed from reply
 *		descriptor queue.
 */
अटल पूर्णांक
_base_process_reply_queue(काष्ठा adapter_reply_queue *reply_q)
अणु
	जोड़ reply_descriptor rd;
	u64 completed_cmds;
	u8 request_descript_type;
	u16 smid;
	u8 cb_idx;
	u32 reply;
	u8 msix_index = reply_q->msix_index;
	काष्ठा MPT3SAS_ADAPTER *ioc = reply_q->ioc;
	Mpi2ReplyDescriptorsUnion_t *rpf;
	u8 rc;

	completed_cmds = 0;
	अगर (!atomic_add_unless(&reply_q->busy, 1, 1))
		वापस completed_cmds;

	rpf = &reply_q->reply_post_मुक्त[reply_q->reply_post_host_index];
	request_descript_type = rpf->Default.ReplyFlags
	     & MPI2_RPY_DESCRIPT_FLAGS_TYPE_MASK;
	अगर (request_descript_type == MPI2_RPY_DESCRIPT_FLAGS_UNUSED) अणु
		atomic_dec(&reply_q->busy);
		वापस completed_cmds;
	पूर्ण

	cb_idx = 0xFF;
	करो अणु
		rd.word = le64_to_cpu(rpf->Words);
		अगर (rd.u.low == अच_पूर्णांक_उच्च || rd.u.high == अच_पूर्णांक_उच्च)
			जाओ out;
		reply = 0;
		smid = le16_to_cpu(rpf->Default.DescriptorTypeDependent1);
		अगर (request_descript_type ==
		    MPI25_RPY_DESCRIPT_FLAGS_FAST_PATH_SCSI_IO_SUCCESS ||
		    request_descript_type ==
		    MPI2_RPY_DESCRIPT_FLAGS_SCSI_IO_SUCCESS ||
		    request_descript_type ==
		    MPI26_RPY_DESCRIPT_FLAGS_PCIE_ENCAPSULATED_SUCCESS) अणु
			cb_idx = _base_get_cb_idx(ioc, smid);
			अगर ((likely(cb_idx < MPT_MAX_CALLBACKS)) &&
			    (likely(mpt_callbacks[cb_idx] != शून्य))) अणु
				rc = mpt_callbacks[cb_idx](ioc, smid,
				    msix_index, 0);
				अगर (rc)
					mpt3sas_base_मुक्त_smid(ioc, smid);
			पूर्ण
		पूर्ण अन्यथा अगर (request_descript_type ==
		    MPI2_RPY_DESCRIPT_FLAGS_ADDRESS_REPLY) अणु
			reply = le32_to_cpu(
			    rpf->AddressReply.ReplyFrameAddress);
			अगर (reply > ioc->reply_dma_max_address ||
			    reply < ioc->reply_dma_min_address)
				reply = 0;
			अगर (smid) अणु
				cb_idx = _base_get_cb_idx(ioc, smid);
				अगर ((likely(cb_idx < MPT_MAX_CALLBACKS)) &&
				    (likely(mpt_callbacks[cb_idx] != शून्य))) अणु
					rc = mpt_callbacks[cb_idx](ioc, smid,
					    msix_index, reply);
					अगर (reply)
						_base_display_reply_info(ioc,
						    smid, msix_index, reply);
					अगर (rc)
						mpt3sas_base_मुक्त_smid(ioc,
						    smid);
				पूर्ण
			पूर्ण अन्यथा अणु
				_base_async_event(ioc, msix_index, reply);
			पूर्ण

			/* reply मुक्त queue handling */
			अगर (reply) अणु
				ioc->reply_मुक्त_host_index =
				    (ioc->reply_मुक्त_host_index ==
				    (ioc->reply_मुक्त_queue_depth - 1)) ?
				    0 : ioc->reply_मुक्त_host_index + 1;
				ioc->reply_मुक्त[ioc->reply_मुक्त_host_index] =
				    cpu_to_le32(reply);
				अगर (ioc->is_mcpu_endpoपूर्णांक)
					_base_clone_reply_to_sys_mem(ioc,
						reply,
						ioc->reply_मुक्त_host_index);
				ग_लिखोl(ioc->reply_मुक्त_host_index,
				    &ioc->chip->ReplyFreeHostIndex);
			पूर्ण
		पूर्ण

		rpf->Words = cpu_to_le64(ULदीर्घ_उच्च);
		reply_q->reply_post_host_index =
		    (reply_q->reply_post_host_index ==
		    (ioc->reply_post_queue_depth - 1)) ? 0 :
		    reply_q->reply_post_host_index + 1;
		request_descript_type =
		    reply_q->reply_post_मुक्त[reply_q->reply_post_host_index].
		    Default.ReplyFlags & MPI2_RPY_DESCRIPT_FLAGS_TYPE_MASK;
		completed_cmds++;
		/* Update the reply post host index after continuously
		 * processing the threshold number of Reply Descriptors.
		 * So that FW can find enough entries to post the Reply
		 * Descriptors in the reply descriptor post queue.
		 */
		अगर (completed_cmds >= ioc->thresh_hold) अणु
			अगर (ioc->combined_reply_queue) अणु
				ग_लिखोl(reply_q->reply_post_host_index |
						((msix_index  & 7) <<
						 MPI2_RPHI_MSIX_INDEX_SHIFT),
				    ioc->replyPostRegisterIndex[msix_index/8]);
			पूर्ण अन्यथा अणु
				ग_लिखोl(reply_q->reply_post_host_index |
						(msix_index <<
						 MPI2_RPHI_MSIX_INDEX_SHIFT),
						&ioc->chip->ReplyPostHostIndex);
			पूर्ण
			अगर (!reply_q->irq_poll_scheduled) अणु
				reply_q->irq_poll_scheduled = true;
				irq_poll_sched(&reply_q->irqpoll);
			पूर्ण
			atomic_dec(&reply_q->busy);
			वापस completed_cmds;
		पूर्ण
		अगर (request_descript_type == MPI2_RPY_DESCRIPT_FLAGS_UNUSED)
			जाओ out;
		अगर (!reply_q->reply_post_host_index)
			rpf = reply_q->reply_post_मुक्त;
		अन्यथा
			rpf++;
	पूर्ण जबतक (1);

 out:

	अगर (!completed_cmds) अणु
		atomic_dec(&reply_q->busy);
		वापस completed_cmds;
	पूर्ण

	अगर (ioc->is_warpdrive) अणु
		ग_लिखोl(reply_q->reply_post_host_index,
		ioc->reply_post_host_index[msix_index]);
		atomic_dec(&reply_q->busy);
		वापस completed_cmds;
	पूर्ण

	/* Update Reply Post Host Index.
	 * For those HBA's which support combined reply queue feature
	 * 1. Get the correct Supplemental Reply Post Host Index Register.
	 *    i.e. (msix_index / 8)th entry from Supplemental Reply Post Host
	 *    Index Register address bank i.e replyPostRegisterIndex[],
	 * 2. Then update this रेजिस्टर with new reply host index value
	 *    in ReplyPostIndex field and the MSIxIndex field with
	 *    msix_index value reduced to a value between 0 and 7,
	 *    using a modulo 8 operation. Since each Supplemental Reply Post
	 *    Host Index Register supports 8 MSI-X vectors.
	 *
	 * For other HBA's just update the Reply Post Host Index रेजिस्टर with
	 * new reply host index value in ReplyPostIndex Field and msix_index
	 * value in MSIxIndex field.
	 */
	अगर (ioc->combined_reply_queue)
		ग_लिखोl(reply_q->reply_post_host_index | ((msix_index  & 7) <<
			MPI2_RPHI_MSIX_INDEX_SHIFT),
			ioc->replyPostRegisterIndex[msix_index/8]);
	अन्यथा
		ग_लिखोl(reply_q->reply_post_host_index | (msix_index <<
			MPI2_RPHI_MSIX_INDEX_SHIFT),
			&ioc->chip->ReplyPostHostIndex);
	atomic_dec(&reply_q->busy);
	वापस completed_cmds;
पूर्ण

/**
 * _base_पूर्णांकerrupt - MPT adapter (IOC) specअगरic पूर्णांकerrupt handler.
 * @irq: irq number (not used)
 * @bus_id: bus identअगरier cookie == poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *
 * Return: IRQ_HANDLED अगर processed, अन्यथा IRQ_NONE.
 */
अटल irqवापस_t
_base_पूर्णांकerrupt(पूर्णांक irq, व्योम *bus_id)
अणु
	काष्ठा adapter_reply_queue *reply_q = bus_id;
	काष्ठा MPT3SAS_ADAPTER *ioc = reply_q->ioc;

	अगर (ioc->mask_पूर्णांकerrupts)
		वापस IRQ_NONE;
	अगर (reply_q->irq_poll_scheduled)
		वापस IRQ_HANDLED;
	वापस ((_base_process_reply_queue(reply_q) > 0) ?
			IRQ_HANDLED : IRQ_NONE);
पूर्ण

/**
 * _base_irqpoll - IRQ poll callback handler
 * @irqpoll: irq_poll object
 * @budget: irq poll weight
 *
 * वापसs number of reply descriptors processed
 */
अटल पूर्णांक
_base_irqpoll(काष्ठा irq_poll *irqpoll, पूर्णांक budget)
अणु
	काष्ठा adapter_reply_queue *reply_q;
	पूर्णांक num_entries = 0;

	reply_q = container_of(irqpoll, काष्ठा adapter_reply_queue,
			irqpoll);
	अगर (reply_q->irq_line_enable) अणु
		disable_irq_nosync(reply_q->os_irq);
		reply_q->irq_line_enable = false;
	पूर्ण
	num_entries = _base_process_reply_queue(reply_q);
	अगर (num_entries < budget) अणु
		irq_poll_complete(irqpoll);
		reply_q->irq_poll_scheduled = false;
		reply_q->irq_line_enable = true;
		enable_irq(reply_q->os_irq);
		/*
		 * Go क्रम one more round of processing the
		 * reply descriptor post queue inहाल अगर HBA
		 * Firmware has posted some reply descriptors
		 * जबतक reenabling the IRQ.
		 */
		_base_process_reply_queue(reply_q);
	पूर्ण

	वापस num_entries;
पूर्ण

/**
 * _base_init_irqpolls - initliaze IRQ polls
 * @ioc: per adapter object
 *
 * वापसs nothing
 */
अटल व्योम
_base_init_irqpolls(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	काष्ठा adapter_reply_queue *reply_q, *next;

	अगर (list_empty(&ioc->reply_queue_list))
		वापस;

	list_क्रम_each_entry_safe(reply_q, next, &ioc->reply_queue_list, list) अणु
		irq_poll_init(&reply_q->irqpoll,
			ioc->hba_queue_depth/4, _base_irqpoll);
		reply_q->irq_poll_scheduled = false;
		reply_q->irq_line_enable = true;
		reply_q->os_irq = pci_irq_vector(ioc->pdev,
		    reply_q->msix_index);
	पूर्ण
पूर्ण

/**
 * _base_is_controller_msix_enabled - is controller support muli-reply queues
 * @ioc: per adapter object
 *
 * Return: Whether or not MSI/X is enabled.
 */
अटल अंतरभूत पूर्णांक
_base_is_controller_msix_enabled(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	वापस (ioc->facts.IOCCapabilities &
	    MPI2_IOCFACTS_CAPABILITY_MSI_X_INDEX) && ioc->msix_enable;
पूर्ण

/**
 * mpt3sas_base_sync_reply_irqs - flush pending MSIX पूर्णांकerrupts
 * @ioc: per adapter object
 * @poll: poll over reply descriptor pools inहाल पूर्णांकerrupt क्रम
 *		समयd-out SCSI command got delayed
 * Context: non ISR conext
 *
 * Called when a Task Management request has completed.
 */
व्योम
mpt3sas_base_sync_reply_irqs(काष्ठा MPT3SAS_ADAPTER *ioc, u8 poll)
अणु
	काष्ठा adapter_reply_queue *reply_q;

	/* If MSIX capability is turned off
	 * then multi-queues are not enabled
	 */
	अगर (!_base_is_controller_msix_enabled(ioc))
		वापस;

	list_क्रम_each_entry(reply_q, &ioc->reply_queue_list, list) अणु
		अगर (ioc->shost_recovery || ioc->हटाओ_host ||
				ioc->pci_error_recovery)
			वापस;
		/* TMs are on msix_index == 0 */
		अगर (reply_q->msix_index == 0)
			जारी;
		synchronize_irq(pci_irq_vector(ioc->pdev, reply_q->msix_index));
		अगर (reply_q->irq_poll_scheduled) अणु
			/* Calling irq_poll_disable will रुको क्रम any pending
			 * callbacks to have completed.
			 */
			irq_poll_disable(&reply_q->irqpoll);
			irq_poll_enable(&reply_q->irqpoll);
			/* check how the scheduled poll has ended,
			 * clean up only अगर necessary
			 */
			अगर (reply_q->irq_poll_scheduled) अणु
				reply_q->irq_poll_scheduled = false;
				reply_q->irq_line_enable = true;
				enable_irq(reply_q->os_irq);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (poll)
		_base_process_reply_queue(reply_q);
पूर्ण

/**
 * mpt3sas_base_release_callback_handler - clear पूर्णांकerrupt callback handler
 * @cb_idx: callback index
 */
व्योम
mpt3sas_base_release_callback_handler(u8 cb_idx)
अणु
	mpt_callbacks[cb_idx] = शून्य;
पूर्ण

/**
 * mpt3sas_base_रेजिस्टर_callback_handler - obtain index क्रम the पूर्णांकerrupt callback handler
 * @cb_func: callback function
 *
 * Return: Index of @cb_func.
 */
u8
mpt3sas_base_रेजिस्टर_callback_handler(MPT_CALLBACK cb_func)
अणु
	u8 cb_idx;

	क्रम (cb_idx = MPT_MAX_CALLBACKS-1; cb_idx; cb_idx--)
		अगर (mpt_callbacks[cb_idx] == शून्य)
			अवरोध;

	mpt_callbacks[cb_idx] = cb_func;
	वापस cb_idx;
पूर्ण

/**
 * mpt3sas_base_initialize_callback_handler - initialize the पूर्णांकerrupt callback handler
 */
व्योम
mpt3sas_base_initialize_callback_handler(व्योम)
अणु
	u8 cb_idx;

	क्रम (cb_idx = 0; cb_idx < MPT_MAX_CALLBACKS; cb_idx++)
		mpt3sas_base_release_callback_handler(cb_idx);
पूर्ण


/**
 * _base_build_zero_len_sge - build zero length sg entry
 * @ioc: per adapter object
 * @paddr: भव address क्रम SGE
 *
 * Create a zero length scatter gather entry to insure the IOCs hardware has
 * something to use अगर the target device goes brain dead and tries
 * to send data even when none is asked क्रम.
 */
अटल व्योम
_base_build_zero_len_sge(काष्ठा MPT3SAS_ADAPTER *ioc, व्योम *paddr)
अणु
	u32 flags_length = (u32)((MPI2_SGE_FLAGS_LAST_ELEMENT |
	    MPI2_SGE_FLAGS_END_OF_BUFFER | MPI2_SGE_FLAGS_END_OF_LIST |
	    MPI2_SGE_FLAGS_SIMPLE_ELEMENT) <<
	    MPI2_SGE_FLAGS_SHIFT);
	ioc->base_add_sg_single(paddr, flags_length, -1);
पूर्ण

/**
 * _base_add_sg_single_32 - Place a simple 32 bit SGE at address pAddr.
 * @paddr: भव address क्रम SGE
 * @flags_length: SGE flags and data transfer length
 * @dma_addr: Physical address
 */
अटल व्योम
_base_add_sg_single_32(व्योम *paddr, u32 flags_length, dma_addr_t dma_addr)
अणु
	Mpi2SGESimple32_t *sgel = paddr;

	flags_length |= (MPI2_SGE_FLAGS_32_BIT_ADDRESSING |
	    MPI2_SGE_FLAGS_SYSTEM_ADDRESS) << MPI2_SGE_FLAGS_SHIFT;
	sgel->FlagsLength = cpu_to_le32(flags_length);
	sgel->Address = cpu_to_le32(dma_addr);
पूर्ण


/**
 * _base_add_sg_single_64 - Place a simple 64 bit SGE at address pAddr.
 * @paddr: भव address क्रम SGE
 * @flags_length: SGE flags and data transfer length
 * @dma_addr: Physical address
 */
अटल व्योम
_base_add_sg_single_64(व्योम *paddr, u32 flags_length, dma_addr_t dma_addr)
अणु
	Mpi2SGESimple64_t *sgel = paddr;

	flags_length |= (MPI2_SGE_FLAGS_64_BIT_ADDRESSING |
	    MPI2_SGE_FLAGS_SYSTEM_ADDRESS) << MPI2_SGE_FLAGS_SHIFT;
	sgel->FlagsLength = cpu_to_le32(flags_length);
	sgel->Address = cpu_to_le64(dma_addr);
पूर्ण

/**
 * _base_get_chain_buffer_tracker - obtain chain tracker
 * @ioc: per adapter object
 * @scmd: SCSI commands of the IO request
 *
 * Return: chain tracker from chain_lookup table using key as
 * smid and smid's chain_offset.
 */
अटल काष्ठा chain_tracker *
_base_get_chain_buffer_tracker(काष्ठा MPT3SAS_ADAPTER *ioc,
			       काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा chain_tracker *chain_req;
	काष्ठा scsiio_tracker *st = scsi_cmd_priv(scmd);
	u16 smid = st->smid;
	u8 chain_offset =
	   atomic_पढ़ो(&ioc->chain_lookup[smid - 1].chain_offset);

	अगर (chain_offset == ioc->chains_needed_per_io)
		वापस शून्य;

	chain_req = &ioc->chain_lookup[smid - 1].chains_per_smid[chain_offset];
	atomic_inc(&ioc->chain_lookup[smid - 1].chain_offset);
	वापस chain_req;
पूर्ण


/**
 * _base_build_sg - build generic sg
 * @ioc: per adapter object
 * @psge: भव address क्रम SGE
 * @data_out_dma: physical address क्रम WRITES
 * @data_out_sz: data xfer size क्रम WRITES
 * @data_in_dma: physical address क्रम READS
 * @data_in_sz: data xfer size क्रम READS
 */
अटल व्योम
_base_build_sg(काष्ठा MPT3SAS_ADAPTER *ioc, व्योम *psge,
	dma_addr_t data_out_dma, माप_प्रकार data_out_sz, dma_addr_t data_in_dma,
	माप_प्रकार data_in_sz)
अणु
	u32 sgl_flags;

	अगर (!data_out_sz && !data_in_sz) अणु
		_base_build_zero_len_sge(ioc, psge);
		वापस;
	पूर्ण

	अगर (data_out_sz && data_in_sz) अणु
		/* WRITE sgel first */
		sgl_flags = (MPI2_SGE_FLAGS_SIMPLE_ELEMENT |
		    MPI2_SGE_FLAGS_END_OF_BUFFER | MPI2_SGE_FLAGS_HOST_TO_IOC);
		sgl_flags = sgl_flags << MPI2_SGE_FLAGS_SHIFT;
		ioc->base_add_sg_single(psge, sgl_flags |
		    data_out_sz, data_out_dma);

		/* incr sgel */
		psge += ioc->sge_size;

		/* READ sgel last */
		sgl_flags = (MPI2_SGE_FLAGS_SIMPLE_ELEMENT |
		    MPI2_SGE_FLAGS_LAST_ELEMENT | MPI2_SGE_FLAGS_END_OF_BUFFER |
		    MPI2_SGE_FLAGS_END_OF_LIST);
		sgl_flags = sgl_flags << MPI2_SGE_FLAGS_SHIFT;
		ioc->base_add_sg_single(psge, sgl_flags |
		    data_in_sz, data_in_dma);
	पूर्ण अन्यथा अगर (data_out_sz) /* WRITE */ अणु
		sgl_flags = (MPI2_SGE_FLAGS_SIMPLE_ELEMENT |
		    MPI2_SGE_FLAGS_LAST_ELEMENT | MPI2_SGE_FLAGS_END_OF_BUFFER |
		    MPI2_SGE_FLAGS_END_OF_LIST | MPI2_SGE_FLAGS_HOST_TO_IOC);
		sgl_flags = sgl_flags << MPI2_SGE_FLAGS_SHIFT;
		ioc->base_add_sg_single(psge, sgl_flags |
		    data_out_sz, data_out_dma);
	पूर्ण अन्यथा अगर (data_in_sz) /* READ */ अणु
		sgl_flags = (MPI2_SGE_FLAGS_SIMPLE_ELEMENT |
		    MPI2_SGE_FLAGS_LAST_ELEMENT | MPI2_SGE_FLAGS_END_OF_BUFFER |
		    MPI2_SGE_FLAGS_END_OF_LIST);
		sgl_flags = sgl_flags << MPI2_SGE_FLAGS_SHIFT;
		ioc->base_add_sg_single(psge, sgl_flags |
		    data_in_sz, data_in_dma);
	पूर्ण
पूर्ण

/* IEEE क्रमmat sgls */

/**
 * _base_build_nvme_prp - This function is called क्रम NVMe end devices to build
 * a native SGL (NVMe PRP). The native SGL is built starting in the first PRP
 * entry of the NVMe message (PRP1).  If the data buffer is small enough to be
 * described entirely using PRP1, then PRP2 is not used.  If needed, PRP2 is
 * used to describe a larger data buffer.  If the data buffer is too large to
 * describe using the two PRP entriess inside the NVMe message, then PRP1
 * describes the first data memory segment, and PRP2 contains a poपूर्णांकer to a PRP
 * list located अन्यथाwhere in memory to describe the reमुख्यing data memory
 * segments.  The PRP list will be contiguous.
 *
 * The native SGL क्रम NVMe devices is a Physical Region Page (PRP).  A PRP
 * consists of a list of PRP entries to describe a number of noncontigous
 * physical memory segments as a single memory buffer, just as a SGL करोes.  Note
 * however, that this function is only used by the IOCTL call, so the memory
 * given will be guaranteed to be contiguous.  There is no need to translate
 * non-contiguous SGL पूर्णांकo a PRP in this हाल.  All PRPs will describe
 * contiguous space that is one page size each.
 *
 * Each NVMe message contains two PRP entries.  The first (PRP1) either contains
 * a PRP list poपूर्णांकer or a PRP element, depending upon the command.  PRP2
 * contains the second PRP element अगर the memory being described fits within 2
 * PRP entries, or a PRP list poपूर्णांकer अगर the PRP spans more than two entries.
 *
 * A PRP list poपूर्णांकer contains the address of a PRP list, काष्ठाured as a linear
 * array of PRP entries.  Each PRP entry in this list describes a segment of
 * physical memory.
 *
 * Each 64-bit PRP entry comprises an address and an offset field.  The address
 * always poपूर्णांकs at the beginning of a 4KB physical memory page, and the offset
 * describes where within that 4KB page the memory segment begins.  Only the
 * first element in a PRP list may contain a non-zero offest, implying that all
 * memory segments following the first begin at the start of a 4KB page.
 *
 * Each PRP element normally describes 4KB of physical memory, with exceptions
 * क्रम the first and last elements in the list.  If the memory being described
 * by the list begins at a non-zero offset within the first 4KB page, then the
 * first PRP element will contain a non-zero offset indicating where the region
 * begins within the 4KB page.  The last memory segment may end beक्रमe the end
 * of the 4KB segment, depending upon the overall size of the memory being
 * described by the PRP list.
 *
 * Since PRP entries lack any indication of size, the overall data buffer length
 * is used to determine where the end of the data memory buffer is located, and
 * how many PRP entries are required to describe it.
 *
 * @ioc: per adapter object
 * @smid: प्रणाली request message index क्रम getting asscociated SGL
 * @nvme_encap_request: the NVMe request msg frame poपूर्णांकer
 * @data_out_dma: physical address क्रम WRITES
 * @data_out_sz: data xfer size क्रम WRITES
 * @data_in_dma: physical address क्रम READS
 * @data_in_sz: data xfer size क्रम READS
 */
अटल व्योम
_base_build_nvme_prp(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid,
	Mpi26NVMeEncapsulatedRequest_t *nvme_encap_request,
	dma_addr_t data_out_dma, माप_प्रकार data_out_sz, dma_addr_t data_in_dma,
	माप_प्रकार data_in_sz)
अणु
	पूर्णांक		prp_size = NVME_PRP_SIZE;
	__le64		*prp_entry, *prp1_entry, *prp2_entry;
	__le64		*prp_page;
	dma_addr_t	prp_entry_dma, prp_page_dma, dma_addr;
	u32		offset, entry_len;
	u32		page_mask_result, page_mask;
	माप_प्रकार		length;
	काष्ठा mpt3sas_nvme_cmd *nvme_cmd =
		(व्योम *)nvme_encap_request->NVMe_Command;

	/*
	 * Not all commands require a data transfer. If no data, just वापस
	 * without स्थिरructing any PRP.
	 */
	अगर (!data_in_sz && !data_out_sz)
		वापस;
	prp1_entry = &nvme_cmd->prp1;
	prp2_entry = &nvme_cmd->prp2;
	prp_entry = prp1_entry;
	/*
	 * For the PRP entries, use the specially allocated buffer of
	 * contiguous memory.
	 */
	prp_page = (__le64 *)mpt3sas_base_get_pcie_sgl(ioc, smid);
	prp_page_dma = mpt3sas_base_get_pcie_sgl_dma(ioc, smid);

	/*
	 * Check अगर we are within 1 entry of a page boundary we करोn't
	 * want our first entry to be a PRP List entry.
	 */
	page_mask = ioc->page_size - 1;
	page_mask_result = (uपूर्णांकptr_t)((u8 *)prp_page + prp_size) & page_mask;
	अगर (!page_mask_result) अणु
		/* Bump up to next page boundary. */
		prp_page = (__le64 *)((u8 *)prp_page + prp_size);
		prp_page_dma = prp_page_dma + prp_size;
	पूर्ण

	/*
	 * Set PRP physical poपूर्णांकer, which initially poपूर्णांकs to the current PRP
	 * DMA memory page.
	 */
	prp_entry_dma = prp_page_dma;

	/* Get physical address and length of the data buffer. */
	अगर (data_in_sz) अणु
		dma_addr = data_in_dma;
		length = data_in_sz;
	पूर्ण अन्यथा अणु
		dma_addr = data_out_dma;
		length = data_out_sz;
	पूर्ण

	/* Loop जबतक the length is not zero. */
	जबतक (length) अणु
		/*
		 * Check अगर we need to put a list poपूर्णांकer here अगर we are at
		 * page boundary - prp_size (8 bytes).
		 */
		page_mask_result = (prp_entry_dma + prp_size) & page_mask;
		अगर (!page_mask_result) अणु
			/*
			 * This is the last entry in a PRP List, so we need to
			 * put a PRP list poपूर्णांकer here.  What this करोes is:
			 *   - bump the current memory poपूर्णांकer to the next
			 *     address, which will be the next full page.
			 *   - set the PRP Entry to poपूर्णांक to that page.  This
			 *     is now the PRP List poपूर्णांकer.
			 *   - bump the PRP Entry poपूर्णांकer the start of the
			 *     next page.  Since all of this PRP memory is
			 *     contiguous, no need to get a new page - it's
			 *     just the next address.
			 */
			prp_entry_dma++;
			*prp_entry = cpu_to_le64(prp_entry_dma);
			prp_entry++;
		पूर्ण

		/* Need to handle अगर entry will be part of a page. */
		offset = dma_addr & page_mask;
		entry_len = ioc->page_size - offset;

		अगर (prp_entry == prp1_entry) अणु
			/*
			 * Must fill in the first PRP poपूर्णांकer (PRP1) beक्रमe
			 * moving on.
			 */
			*prp1_entry = cpu_to_le64(dma_addr);

			/*
			 * Now poपूर्णांक to the second PRP entry within the
			 * command (PRP2).
			 */
			prp_entry = prp2_entry;
		पूर्ण अन्यथा अगर (prp_entry == prp2_entry) अणु
			/*
			 * Should the PRP2 entry be a PRP List poपूर्णांकer or just
			 * a regular PRP poपूर्णांकer?  If there is more than one
			 * more page of data, must use a PRP List poपूर्णांकer.
			 */
			अगर (length > ioc->page_size) अणु
				/*
				 * PRP2 will contain a PRP List poपूर्णांकer because
				 * more PRP's are needed with this command. The
				 * list will start at the beginning of the
				 * contiguous buffer.
				 */
				*prp2_entry = cpu_to_le64(prp_entry_dma);

				/*
				 * The next PRP Entry will be the start of the
				 * first PRP List.
				 */
				prp_entry = prp_page;
			पूर्ण अन्यथा अणु
				/*
				 * After this, the PRP Entries are complete.
				 * This command uses 2 PRP's and no PRP list.
				 */
				*prp2_entry = cpu_to_le64(dma_addr);
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * Put entry in list and bump the addresses.
			 *
			 * After PRP1 and PRP2 are filled in, this will fill in
			 * all reमुख्यing PRP entries in a PRP List, one per
			 * each समय through the loop.
			 */
			*prp_entry = cpu_to_le64(dma_addr);
			prp_entry++;
			prp_entry_dma++;
		पूर्ण

		/*
		 * Bump the phys address of the command's data buffer by the
		 * entry_len.
		 */
		dma_addr += entry_len;

		/* Decrement length accounting क्रम last partial page. */
		अगर (entry_len > length)
			length = 0;
		अन्यथा
			length -= entry_len;
	पूर्ण
पूर्ण

/**
 * base_make_prp_nvme -
 * Prepare PRPs(Physical Region Page)- SGLs specअगरic to NVMe drives only
 *
 * @ioc:		per adapter object
 * @scmd:		SCSI command from the mid-layer
 * @mpi_request:	mpi request
 * @smid:		msg Index
 * @sge_count:		scatter gather element count.
 *
 * Return:		true: PRPs are built
 *			false: IEEE SGLs needs to be built
 */
अटल व्योम
base_make_prp_nvme(काष्ठा MPT3SAS_ADAPTER *ioc,
		काष्ठा scsi_cmnd *scmd,
		Mpi25SCSIIORequest_t *mpi_request,
		u16 smid, पूर्णांक sge_count)
अणु
	पूर्णांक sge_len, num_prp_in_chain = 0;
	Mpi25IeeeSgeChain64_t *मुख्य_chain_element, *ptr_first_sgl;
	__le64 *curr_buff;
	dma_addr_t msg_dma, sge_addr, offset;
	u32 page_mask, page_mask_result;
	काष्ठा scatterlist *sg_scmd;
	u32 first_prp_len;
	पूर्णांक data_len = scsi_bufflen(scmd);
	u32 nvme_pg_size;

	nvme_pg_size = max_t(u32, ioc->page_size, NVME_PRP_PAGE_SIZE);
	/*
	 * Nvme has a very convoluted prp क्रमmat.  One prp is required
	 * क्रम each page or partial page. Driver need to split up OS sg_list
	 * entries अगर it is दीर्घer than one page or cross a page
	 * boundary.  Driver also have to insert a PRP list poपूर्णांकer entry as
	 * the last entry in each physical page of the PRP list.
	 *
	 * NOTE: The first PRP "entry" is actually placed in the first
	 * SGL entry in the मुख्य message as IEEE 64 क्रमmat.  The 2nd
	 * entry in the मुख्य message is the chain element, and the rest
	 * of the PRP entries are built in the contiguous pcie buffer.
	 */
	page_mask = nvme_pg_size - 1;

	/*
	 * Native SGL is needed.
	 * Put a chain element in मुख्य message frame that poपूर्णांकs to the first
	 * chain buffer.
	 *
	 * NOTE:  The ChainOffset field must be 0 when using a chain poपूर्णांकer to
	 *        a native SGL.
	 */

	/* Set मुख्य message chain element poपूर्णांकer */
	मुख्य_chain_element = (pMpi25IeeeSgeChain64_t)&mpi_request->SGL;
	/*
	 * For NVMe the chain element needs to be the 2nd SG entry in the मुख्य
	 * message.
	 */
	मुख्य_chain_element = (Mpi25IeeeSgeChain64_t *)
		((u8 *)मुख्य_chain_element + माप(MPI25_IEEE_SGE_CHAIN64));

	/*
	 * For the PRP entries, use the specially allocated buffer of
	 * contiguous memory.  Normal chain buffers can't be used
	 * because each chain buffer would need to be the size of an OS
	 * page (4k).
	 */
	curr_buff = mpt3sas_base_get_pcie_sgl(ioc, smid);
	msg_dma = mpt3sas_base_get_pcie_sgl_dma(ioc, smid);

	मुख्य_chain_element->Address = cpu_to_le64(msg_dma);
	मुख्य_chain_element->NextChainOffset = 0;
	मुख्य_chain_element->Flags = MPI2_IEEE_SGE_FLAGS_CHAIN_ELEMENT |
			MPI2_IEEE_SGE_FLAGS_SYSTEM_ADDR |
			MPI26_IEEE_SGE_FLAGS_NSF_NVME_PRP;

	/* Build first prp, sge need not to be page aligned*/
	ptr_first_sgl = (pMpi25IeeeSgeChain64_t)&mpi_request->SGL;
	sg_scmd = scsi_sglist(scmd);
	sge_addr = sg_dma_address(sg_scmd);
	sge_len = sg_dma_len(sg_scmd);

	offset = sge_addr & page_mask;
	first_prp_len = nvme_pg_size - offset;

	ptr_first_sgl->Address = cpu_to_le64(sge_addr);
	ptr_first_sgl->Length = cpu_to_le32(first_prp_len);

	data_len -= first_prp_len;

	अगर (sge_len > first_prp_len) अणु
		sge_addr += first_prp_len;
		sge_len -= first_prp_len;
	पूर्ण अन्यथा अगर (data_len && (sge_len == first_prp_len)) अणु
		sg_scmd = sg_next(sg_scmd);
		sge_addr = sg_dma_address(sg_scmd);
		sge_len = sg_dma_len(sg_scmd);
	पूर्ण

	क्रम (;;) अणु
		offset = sge_addr & page_mask;

		/* Put PRP poपूर्णांकer due to page boundary*/
		page_mask_result = (uपूर्णांकptr_t)(curr_buff + 1) & page_mask;
		अगर (unlikely(!page_mask_result)) अणु
			scmd_prपूर्णांकk(KERN_NOTICE,
				scmd, "page boundary curr_buff: 0x%p\n",
				curr_buff);
			msg_dma += 8;
			*curr_buff = cpu_to_le64(msg_dma);
			curr_buff++;
			num_prp_in_chain++;
		पूर्ण

		*curr_buff = cpu_to_le64(sge_addr);
		curr_buff++;
		msg_dma += 8;
		num_prp_in_chain++;

		sge_addr += nvme_pg_size;
		sge_len -= nvme_pg_size;
		data_len -= nvme_pg_size;

		अगर (data_len <= 0)
			अवरोध;

		अगर (sge_len > 0)
			जारी;

		sg_scmd = sg_next(sg_scmd);
		sge_addr = sg_dma_address(sg_scmd);
		sge_len = sg_dma_len(sg_scmd);
	पूर्ण

	मुख्य_chain_element->Length =
		cpu_to_le32(num_prp_in_chain * माप(u64));
	वापस;
पूर्ण

अटल bool
base_is_prp_possible(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _pcie_device *pcie_device, काष्ठा scsi_cmnd *scmd, पूर्णांक sge_count)
अणु
	u32 data_length = 0;
	bool build_prp = true;

	data_length = scsi_bufflen(scmd);
	अगर (pcie_device &&
	    (mpt3sas_scsih_is_pcie_scsi_device(pcie_device->device_info))) अणु
		build_prp = false;
		वापस build_prp;
	पूर्ण

	/* If Datalenth is <= 16K and number of SGEै s entries are <= 2
	 * we built IEEE SGL
	 */
	अगर ((data_length <= NVME_PRP_PAGE_SIZE*4) && (sge_count <= 2))
		build_prp = false;

	वापस build_prp;
पूर्ण

/**
 * _base_check_pcie_native_sgl - This function is called क्रम PCIe end devices to
 * determine अगर the driver needs to build a native SGL.  If so, that native
 * SGL is built in the special contiguous buffers allocated especially क्रम
 * PCIe SGL creation.  If the driver will not build a native SGL, वापस
 * TRUE and a normal IEEE SGL will be built.  Currently this routine
 * supports NVMe.
 * @ioc: per adapter object
 * @mpi_request: mf request poपूर्णांकer
 * @smid: प्रणाली request message index
 * @scmd: scsi command
 * @pcie_device: poपूर्णांकs to the PCIe device's info
 *
 * Return: 0 अगर native SGL was built, 1 अगर no SGL was built
 */
अटल पूर्णांक
_base_check_pcie_native_sgl(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi25SCSIIORequest_t *mpi_request, u16 smid, काष्ठा scsi_cmnd *scmd,
	काष्ठा _pcie_device *pcie_device)
अणु
	पूर्णांक sges_left;

	/* Get the SG list poपूर्णांकer and info. */
	sges_left = scsi_dma_map(scmd);
	अगर (sges_left < 0) अणु
		sdev_prपूर्णांकk(KERN_ERR, scmd->device,
			"scsi_dma_map failed: request for %d bytes!\n",
			scsi_bufflen(scmd));
		वापस 1;
	पूर्ण

	/* Check अगर we need to build a native SG list. */
	अगर (!base_is_prp_possible(ioc, pcie_device,
				scmd, sges_left)) अणु
		/* We built a native SG list, just वापस. */
		जाओ out;
	पूर्ण

	/*
	 * Build native NVMe PRP.
	 */
	base_make_prp_nvme(ioc, scmd, mpi_request,
			smid, sges_left);

	वापस 0;
out:
	scsi_dma_unmap(scmd);
	वापस 1;
पूर्ण

/**
 * _base_add_sg_single_ieee - add sg element क्रम IEEE क्रमmat
 * @paddr: भव address क्रम SGE
 * @flags: SGE flags
 * @chain_offset: number of 128 byte elements from start of segment
 * @length: data transfer length
 * @dma_addr: Physical address
 */
अटल व्योम
_base_add_sg_single_ieee(व्योम *paddr, u8 flags, u8 chain_offset, u32 length,
	dma_addr_t dma_addr)
अणु
	Mpi25IeeeSgeChain64_t *sgel = paddr;

	sgel->Flags = flags;
	sgel->NextChainOffset = chain_offset;
	sgel->Length = cpu_to_le32(length);
	sgel->Address = cpu_to_le64(dma_addr);
पूर्ण

/**
 * _base_build_zero_len_sge_ieee - build zero length sg entry क्रम IEEE क्रमmat
 * @ioc: per adapter object
 * @paddr: भव address क्रम SGE
 *
 * Create a zero length scatter gather entry to insure the IOCs hardware has
 * something to use अगर the target device goes brain dead and tries
 * to send data even when none is asked क्रम.
 */
अटल व्योम
_base_build_zero_len_sge_ieee(काष्ठा MPT3SAS_ADAPTER *ioc, व्योम *paddr)
अणु
	u8 sgl_flags = (MPI2_IEEE_SGE_FLAGS_SIMPLE_ELEMENT |
		MPI2_IEEE_SGE_FLAGS_SYSTEM_ADDR |
		MPI25_IEEE_SGE_FLAGS_END_OF_LIST);

	_base_add_sg_single_ieee(paddr, sgl_flags, 0, 0, -1);
पूर्ण

/**
 * _base_build_sg_scmd - मुख्य sg creation routine
 *		pcie_device is unused here!
 * @ioc: per adapter object
 * @scmd: scsi command
 * @smid: प्रणाली request message index
 * @unused: unused pcie_device poपूर्णांकer
 * Context: none.
 *
 * The मुख्य routine that builds scatter gather table from a given
 * scsi request sent via the .queuecommand मुख्य handler.
 *
 * Return: 0 success, anything अन्यथा error
 */
अटल पूर्णांक
_base_build_sg_scmd(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा scsi_cmnd *scmd, u16 smid, काष्ठा _pcie_device *unused)
अणु
	Mpi2SCSIIORequest_t *mpi_request;
	dma_addr_t chain_dma;
	काष्ठा scatterlist *sg_scmd;
	व्योम *sg_local, *chain;
	u32 chain_offset;
	u32 chain_length;
	u32 chain_flags;
	पूर्णांक sges_left;
	u32 sges_in_segment;
	u32 sgl_flags;
	u32 sgl_flags_last_element;
	u32 sgl_flags_end_buffer;
	काष्ठा chain_tracker *chain_req;

	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);

	/* init scatter gather flags */
	sgl_flags = MPI2_SGE_FLAGS_SIMPLE_ELEMENT;
	अगर (scmd->sc_data_direction == DMA_TO_DEVICE)
		sgl_flags |= MPI2_SGE_FLAGS_HOST_TO_IOC;
	sgl_flags_last_element = (sgl_flags | MPI2_SGE_FLAGS_LAST_ELEMENT)
	    << MPI2_SGE_FLAGS_SHIFT;
	sgl_flags_end_buffer = (sgl_flags | MPI2_SGE_FLAGS_LAST_ELEMENT |
	    MPI2_SGE_FLAGS_END_OF_BUFFER | MPI2_SGE_FLAGS_END_OF_LIST)
	    << MPI2_SGE_FLAGS_SHIFT;
	sgl_flags = sgl_flags << MPI2_SGE_FLAGS_SHIFT;

	sg_scmd = scsi_sglist(scmd);
	sges_left = scsi_dma_map(scmd);
	अगर (sges_left < 0) अणु
		sdev_prपूर्णांकk(KERN_ERR, scmd->device,
		 "scsi_dma_map failed: request for %d bytes!\n",
		 scsi_bufflen(scmd));
		वापस -ENOMEM;
	पूर्ण

	sg_local = &mpi_request->SGL;
	sges_in_segment = ioc->max_sges_in_मुख्य_message;
	अगर (sges_left <= sges_in_segment)
		जाओ fill_in_last_segment;

	mpi_request->ChainOffset = (दुरत्व(Mpi2SCSIIORequest_t, SGL) +
	    (sges_in_segment * ioc->sge_size))/4;

	/* fill in मुख्य message segment when there is a chain following */
	जबतक (sges_in_segment) अणु
		अगर (sges_in_segment == 1)
			ioc->base_add_sg_single(sg_local,
			    sgl_flags_last_element | sg_dma_len(sg_scmd),
			    sg_dma_address(sg_scmd));
		अन्यथा
			ioc->base_add_sg_single(sg_local, sgl_flags |
			    sg_dma_len(sg_scmd), sg_dma_address(sg_scmd));
		sg_scmd = sg_next(sg_scmd);
		sg_local += ioc->sge_size;
		sges_left--;
		sges_in_segment--;
	पूर्ण

	/* initializing the chain flags and poपूर्णांकers */
	chain_flags = MPI2_SGE_FLAGS_CHAIN_ELEMENT << MPI2_SGE_FLAGS_SHIFT;
	chain_req = _base_get_chain_buffer_tracker(ioc, scmd);
	अगर (!chain_req)
		वापस -1;
	chain = chain_req->chain_buffer;
	chain_dma = chain_req->chain_buffer_dma;
	करो अणु
		sges_in_segment = (sges_left <=
		    ioc->max_sges_in_chain_message) ? sges_left :
		    ioc->max_sges_in_chain_message;
		chain_offset = (sges_left == sges_in_segment) ?
		    0 : (sges_in_segment * ioc->sge_size)/4;
		chain_length = sges_in_segment * ioc->sge_size;
		अगर (chain_offset) अणु
			chain_offset = chain_offset <<
			    MPI2_SGE_CHAIN_OFFSET_SHIFT;
			chain_length += ioc->sge_size;
		पूर्ण
		ioc->base_add_sg_single(sg_local, chain_flags | chain_offset |
		    chain_length, chain_dma);
		sg_local = chain;
		अगर (!chain_offset)
			जाओ fill_in_last_segment;

		/* fill in chain segments */
		जबतक (sges_in_segment) अणु
			अगर (sges_in_segment == 1)
				ioc->base_add_sg_single(sg_local,
				    sgl_flags_last_element |
				    sg_dma_len(sg_scmd),
				    sg_dma_address(sg_scmd));
			अन्यथा
				ioc->base_add_sg_single(sg_local, sgl_flags |
				    sg_dma_len(sg_scmd),
				    sg_dma_address(sg_scmd));
			sg_scmd = sg_next(sg_scmd);
			sg_local += ioc->sge_size;
			sges_left--;
			sges_in_segment--;
		पूर्ण

		chain_req = _base_get_chain_buffer_tracker(ioc, scmd);
		अगर (!chain_req)
			वापस -1;
		chain = chain_req->chain_buffer;
		chain_dma = chain_req->chain_buffer_dma;
	पूर्ण जबतक (1);


 fill_in_last_segment:

	/* fill the last segment */
	जबतक (sges_left) अणु
		अगर (sges_left == 1)
			ioc->base_add_sg_single(sg_local, sgl_flags_end_buffer |
			    sg_dma_len(sg_scmd), sg_dma_address(sg_scmd));
		अन्यथा
			ioc->base_add_sg_single(sg_local, sgl_flags |
			    sg_dma_len(sg_scmd), sg_dma_address(sg_scmd));
		sg_scmd = sg_next(sg_scmd);
		sg_local += ioc->sge_size;
		sges_left--;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * _base_build_sg_scmd_ieee - मुख्य sg creation routine क्रम IEEE क्रमmat
 * @ioc: per adapter object
 * @scmd: scsi command
 * @smid: प्रणाली request message index
 * @pcie_device: Poपूर्णांकer to pcie_device. If set, the pcie native sgl will be
 * स्थिरructed on need.
 * Context: none.
 *
 * The मुख्य routine that builds scatter gather table from a given
 * scsi request sent via the .queuecommand मुख्य handler.
 *
 * Return: 0 success, anything अन्यथा error
 */
अटल पूर्णांक
_base_build_sg_scmd_ieee(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा scsi_cmnd *scmd, u16 smid, काष्ठा _pcie_device *pcie_device)
अणु
	Mpi25SCSIIORequest_t *mpi_request;
	dma_addr_t chain_dma;
	काष्ठा scatterlist *sg_scmd;
	व्योम *sg_local, *chain;
	u32 chain_offset;
	u32 chain_length;
	पूर्णांक sges_left;
	u32 sges_in_segment;
	u8 simple_sgl_flags;
	u8 simple_sgl_flags_last;
	u8 chain_sgl_flags;
	काष्ठा chain_tracker *chain_req;

	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);

	/* init scatter gather flags */
	simple_sgl_flags = MPI2_IEEE_SGE_FLAGS_SIMPLE_ELEMENT |
	    MPI2_IEEE_SGE_FLAGS_SYSTEM_ADDR;
	simple_sgl_flags_last = simple_sgl_flags |
	    MPI25_IEEE_SGE_FLAGS_END_OF_LIST;
	chain_sgl_flags = MPI2_IEEE_SGE_FLAGS_CHAIN_ELEMENT |
	    MPI2_IEEE_SGE_FLAGS_SYSTEM_ADDR;

	/* Check अगर we need to build a native SG list. */
	अगर ((pcie_device) && (_base_check_pcie_native_sgl(ioc, mpi_request,
			smid, scmd, pcie_device) == 0)) अणु
		/* We built a native SG list, just वापस. */
		वापस 0;
	पूर्ण

	sg_scmd = scsi_sglist(scmd);
	sges_left = scsi_dma_map(scmd);
	अगर (sges_left < 0) अणु
		sdev_prपूर्णांकk(KERN_ERR, scmd->device,
			"scsi_dma_map failed: request for %d bytes!\n",
			scsi_bufflen(scmd));
		वापस -ENOMEM;
	पूर्ण

	sg_local = &mpi_request->SGL;
	sges_in_segment = (ioc->request_sz -
		   दुरत्व(Mpi25SCSIIORequest_t, SGL))/ioc->sge_size_ieee;
	अगर (sges_left <= sges_in_segment)
		जाओ fill_in_last_segment;

	mpi_request->ChainOffset = (sges_in_segment - 1 /* chain element */) +
	    (दुरत्व(Mpi25SCSIIORequest_t, SGL)/ioc->sge_size_ieee);

	/* fill in मुख्य message segment when there is a chain following */
	जबतक (sges_in_segment > 1) अणु
		_base_add_sg_single_ieee(sg_local, simple_sgl_flags, 0,
		    sg_dma_len(sg_scmd), sg_dma_address(sg_scmd));
		sg_scmd = sg_next(sg_scmd);
		sg_local += ioc->sge_size_ieee;
		sges_left--;
		sges_in_segment--;
	पूर्ण

	/* initializing the poपूर्णांकers */
	chain_req = _base_get_chain_buffer_tracker(ioc, scmd);
	अगर (!chain_req)
		वापस -1;
	chain = chain_req->chain_buffer;
	chain_dma = chain_req->chain_buffer_dma;
	करो अणु
		sges_in_segment = (sges_left <=
		    ioc->max_sges_in_chain_message) ? sges_left :
		    ioc->max_sges_in_chain_message;
		chain_offset = (sges_left == sges_in_segment) ?
		    0 : sges_in_segment;
		chain_length = sges_in_segment * ioc->sge_size_ieee;
		अगर (chain_offset)
			chain_length += ioc->sge_size_ieee;
		_base_add_sg_single_ieee(sg_local, chain_sgl_flags,
		    chain_offset, chain_length, chain_dma);

		sg_local = chain;
		अगर (!chain_offset)
			जाओ fill_in_last_segment;

		/* fill in chain segments */
		जबतक (sges_in_segment) अणु
			_base_add_sg_single_ieee(sg_local, simple_sgl_flags, 0,
			    sg_dma_len(sg_scmd), sg_dma_address(sg_scmd));
			sg_scmd = sg_next(sg_scmd);
			sg_local += ioc->sge_size_ieee;
			sges_left--;
			sges_in_segment--;
		पूर्ण

		chain_req = _base_get_chain_buffer_tracker(ioc, scmd);
		अगर (!chain_req)
			वापस -1;
		chain = chain_req->chain_buffer;
		chain_dma = chain_req->chain_buffer_dma;
	पूर्ण जबतक (1);


 fill_in_last_segment:

	/* fill the last segment */
	जबतक (sges_left > 0) अणु
		अगर (sges_left == 1)
			_base_add_sg_single_ieee(sg_local,
			    simple_sgl_flags_last, 0, sg_dma_len(sg_scmd),
			    sg_dma_address(sg_scmd));
		अन्यथा
			_base_add_sg_single_ieee(sg_local, simple_sgl_flags, 0,
			    sg_dma_len(sg_scmd), sg_dma_address(sg_scmd));
		sg_scmd = sg_next(sg_scmd);
		sg_local += ioc->sge_size_ieee;
		sges_left--;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * _base_build_sg_ieee - build generic sg क्रम IEEE क्रमmat
 * @ioc: per adapter object
 * @psge: भव address क्रम SGE
 * @data_out_dma: physical address क्रम WRITES
 * @data_out_sz: data xfer size क्रम WRITES
 * @data_in_dma: physical address क्रम READS
 * @data_in_sz: data xfer size क्रम READS
 */
अटल व्योम
_base_build_sg_ieee(काष्ठा MPT3SAS_ADAPTER *ioc, व्योम *psge,
	dma_addr_t data_out_dma, माप_प्रकार data_out_sz, dma_addr_t data_in_dma,
	माप_प्रकार data_in_sz)
अणु
	u8 sgl_flags;

	अगर (!data_out_sz && !data_in_sz) अणु
		_base_build_zero_len_sge_ieee(ioc, psge);
		वापस;
	पूर्ण

	अगर (data_out_sz && data_in_sz) अणु
		/* WRITE sgel first */
		sgl_flags = MPI2_IEEE_SGE_FLAGS_SIMPLE_ELEMENT |
		    MPI2_IEEE_SGE_FLAGS_SYSTEM_ADDR;
		_base_add_sg_single_ieee(psge, sgl_flags, 0, data_out_sz,
		    data_out_dma);

		/* incr sgel */
		psge += ioc->sge_size_ieee;

		/* READ sgel last */
		sgl_flags |= MPI25_IEEE_SGE_FLAGS_END_OF_LIST;
		_base_add_sg_single_ieee(psge, sgl_flags, 0, data_in_sz,
		    data_in_dma);
	पूर्ण अन्यथा अगर (data_out_sz) /* WRITE */ अणु
		sgl_flags = MPI2_IEEE_SGE_FLAGS_SIMPLE_ELEMENT |
		    MPI25_IEEE_SGE_FLAGS_END_OF_LIST |
		    MPI2_IEEE_SGE_FLAGS_SYSTEM_ADDR;
		_base_add_sg_single_ieee(psge, sgl_flags, 0, data_out_sz,
		    data_out_dma);
	पूर्ण अन्यथा अगर (data_in_sz) /* READ */ अणु
		sgl_flags = MPI2_IEEE_SGE_FLAGS_SIMPLE_ELEMENT |
		    MPI25_IEEE_SGE_FLAGS_END_OF_LIST |
		    MPI2_IEEE_SGE_FLAGS_SYSTEM_ADDR;
		_base_add_sg_single_ieee(psge, sgl_flags, 0, data_in_sz,
		    data_in_dma);
	पूर्ण
पूर्ण

#घोषणा convert_to_kb(x) ((x) << (PAGE_SHIFT - 10))

/**
 * _base_config_dma_addressing - set dma addressing
 * @ioc: per adapter object
 * @pdev: PCI device काष्ठा
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_base_config_dma_addressing(काष्ठा MPT3SAS_ADAPTER *ioc, काष्ठा pci_dev *pdev)
अणु
	काष्ठा sysinfo s;

	अगर (ioc->is_mcpu_endpoपूर्णांक ||
	    माप(dma_addr_t) == 4 || ioc->use_32bit_dma ||
	    dma_get_required_mask(&pdev->dev) <= 32)
		ioc->dma_mask = 32;
	/* Set 63 bit DMA mask क्रम all SAS3 and SAS35 controllers */
	अन्यथा अगर (ioc->hba_mpi_version_beदीर्घed > MPI2_VERSION)
		ioc->dma_mask = 63;
	अन्यथा
		ioc->dma_mask = 64;

	अगर (dma_set_mask(&pdev->dev, DMA_BIT_MASK(ioc->dma_mask)) ||
	    dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(ioc->dma_mask)))
		वापस -ENODEV;

	अगर (ioc->dma_mask > 32) अणु
		ioc->base_add_sg_single = &_base_add_sg_single_64;
		ioc->sge_size = माप(Mpi2SGESimple64_t);
	पूर्ण अन्यथा अणु
		ioc->base_add_sg_single = &_base_add_sg_single_32;
		ioc->sge_size = माप(Mpi2SGESimple32_t);
	पूर्ण

	si_meminfo(&s);
	ioc_info(ioc, "%d BIT PCI BUS DMA ADDRESSING SUPPORTED, total mem (%ld kB)\n",
		ioc->dma_mask, convert_to_kb(s.totalram));

	वापस 0;
पूर्ण

/**
 * _base_check_enable_msix - checks MSIX capabable.
 * @ioc: per adapter object
 *
 * Check to see अगर card is capable of MSIX, and set number
 * of available msix vectors
 */
अटल पूर्णांक
_base_check_enable_msix(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	पूर्णांक base;
	u16 message_control;

	/* Check whether controller SAS2008 B0 controller,
	 * अगर it is SAS2008 B0 controller use IO-APIC instead of MSIX
	 */
	अगर (ioc->pdev->device == MPI2_MFGPAGE_DEVID_SAS2008 &&
	    ioc->pdev->revision == SAS2_PCI_DEVICE_B0_REVISION) अणु
		वापस -EINVAL;
	पूर्ण

	base = pci_find_capability(ioc->pdev, PCI_CAP_ID_MSIX);
	अगर (!base) अणु
		dfailprपूर्णांकk(ioc, ioc_info(ioc, "msix not supported\n"));
		वापस -EINVAL;
	पूर्ण

	/* get msix vector count */
	/* NUMA_IO not supported क्रम older controllers */
	अगर (ioc->pdev->device == MPI2_MFGPAGE_DEVID_SAS2004 ||
	    ioc->pdev->device == MPI2_MFGPAGE_DEVID_SAS2008 ||
	    ioc->pdev->device == MPI2_MFGPAGE_DEVID_SAS2108_1 ||
	    ioc->pdev->device == MPI2_MFGPAGE_DEVID_SAS2108_2 ||
	    ioc->pdev->device == MPI2_MFGPAGE_DEVID_SAS2108_3 ||
	    ioc->pdev->device == MPI2_MFGPAGE_DEVID_SAS2116_1 ||
	    ioc->pdev->device == MPI2_MFGPAGE_DEVID_SAS2116_2)
		ioc->msix_vector_count = 1;
	अन्यथा अणु
		pci_पढ़ो_config_word(ioc->pdev, base + 2, &message_control);
		ioc->msix_vector_count = (message_control & 0x3FF) + 1;
	पूर्ण
	dinitprपूर्णांकk(ioc, ioc_info(ioc, "msix is supported, vector_count(%d)\n",
				  ioc->msix_vector_count));
	वापस 0;
पूर्ण

/**
 * _base_मुक्त_irq - मुक्त irq
 * @ioc: per adapter object
 *
 * Freeing respective reply_queue from the list.
 */
अटल व्योम
_base_मुक्त_irq(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	काष्ठा adapter_reply_queue *reply_q, *next;

	अगर (list_empty(&ioc->reply_queue_list))
		वापस;

	list_क्रम_each_entry_safe(reply_q, next, &ioc->reply_queue_list, list) अणु
		list_del(&reply_q->list);
		अगर (ioc->smp_affinity_enable)
			irq_set_affinity_hपूर्णांक(pci_irq_vector(ioc->pdev,
			    reply_q->msix_index), शून्य);
		मुक्त_irq(pci_irq_vector(ioc->pdev, reply_q->msix_index),
			 reply_q);
		kमुक्त(reply_q);
	पूर्ण
पूर्ण

/**
 * _base_request_irq - request irq
 * @ioc: per adapter object
 * @index: msix index पूर्णांकo vector table
 *
 * Inserting respective reply_queue पूर्णांकo the list.
 */
अटल पूर्णांक
_base_request_irq(काष्ठा MPT3SAS_ADAPTER *ioc, u8 index)
अणु
	काष्ठा pci_dev *pdev = ioc->pdev;
	काष्ठा adapter_reply_queue *reply_q;
	पूर्णांक r;

	reply_q =  kzalloc(माप(काष्ठा adapter_reply_queue), GFP_KERNEL);
	अगर (!reply_q) अणु
		ioc_err(ioc, "unable to allocate memory %zu!\n",
			माप(काष्ठा adapter_reply_queue));
		वापस -ENOMEM;
	पूर्ण
	reply_q->ioc = ioc;
	reply_q->msix_index = index;

	atomic_set(&reply_q->busy, 0);
	अगर (ioc->msix_enable)
		snम_लिखो(reply_q->name, MPT_NAME_LENGTH, "%s%d-msix%d",
		    ioc->driver_name, ioc->id, index);
	अन्यथा
		snम_लिखो(reply_q->name, MPT_NAME_LENGTH, "%s%d",
		    ioc->driver_name, ioc->id);
	r = request_irq(pci_irq_vector(pdev, index), _base_पूर्णांकerrupt,
			IRQF_SHARED, reply_q->name, reply_q);
	अगर (r) अणु
		pr_err("%s: unable to allocate interrupt %d!\n",
		       reply_q->name, pci_irq_vector(pdev, index));
		kमुक्त(reply_q);
		वापस -EBUSY;
	पूर्ण

	INIT_LIST_HEAD(&reply_q->list);
	list_add_tail(&reply_q->list, &ioc->reply_queue_list);
	वापस 0;
पूर्ण

/**
 * _base_assign_reply_queues - assigning msix index क्रम each cpu
 * @ioc: per adapter object
 *
 * The enduser would need to set the affinity via /proc/irq/#/smp_affinity
 *
 * It would nice अगर we could call irq_set_affinity, however it is not
 * an exported symbol
 */
अटल व्योम
_base_assign_reply_queues(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	अचिन्हित पूर्णांक cpu, nr_cpus, nr_msix, index = 0;
	काष्ठा adapter_reply_queue *reply_q;
	पूर्णांक local_numa_node;

	अगर (!_base_is_controller_msix_enabled(ioc))
		वापस;

	अगर (ioc->msix_load_balance)
		वापस;

	स_रखो(ioc->cpu_msix_table, 0, ioc->cpu_msix_table_sz);

	nr_cpus = num_online_cpus();
	nr_msix = ioc->reply_queue_count = min(ioc->reply_queue_count,
					       ioc->facts.MaxMSIxVectors);
	अगर (!nr_msix)
		वापस;

	अगर (ioc->smp_affinity_enable) अणु

		/*
		 * set irq affinity to local numa node क्रम those irqs
		 * corresponding to high iops queues.
		 */
		अगर (ioc->high_iops_queues) अणु
			local_numa_node = dev_to_node(&ioc->pdev->dev);
			क्रम (index = 0; index < ioc->high_iops_queues;
			    index++) अणु
				irq_set_affinity_hपूर्णांक(pci_irq_vector(ioc->pdev,
				    index), cpumask_of_node(local_numa_node));
			पूर्ण
		पूर्ण

		list_क्रम_each_entry(reply_q, &ioc->reply_queue_list, list) अणु
			स्थिर cpumask_t *mask;

			अगर (reply_q->msix_index < ioc->high_iops_queues)
				जारी;

			mask = pci_irq_get_affinity(ioc->pdev,
			    reply_q->msix_index);
			अगर (!mask) अणु
				ioc_warn(ioc, "no affinity for msi %x\n",
					 reply_q->msix_index);
				जाओ fall_back;
			पूर्ण

			क्रम_each_cpu_and(cpu, mask, cpu_online_mask) अणु
				अगर (cpu >= ioc->cpu_msix_table_sz)
					अवरोध;
				ioc->cpu_msix_table[cpu] = reply_q->msix_index;
			पूर्ण
		पूर्ण
		वापस;
	पूर्ण

fall_back:
	cpu = cpumask_first(cpu_online_mask);
	nr_msix -= ioc->high_iops_queues;
	index = 0;

	list_क्रम_each_entry(reply_q, &ioc->reply_queue_list, list) अणु
		अचिन्हित पूर्णांक i, group = nr_cpus / nr_msix;

		अगर (reply_q->msix_index < ioc->high_iops_queues)
			जारी;

		अगर (cpu >= nr_cpus)
			अवरोध;

		अगर (index < nr_cpus % nr_msix)
			group++;

		क्रम (i = 0 ; i < group ; i++) अणु
			ioc->cpu_msix_table[cpu] = reply_q->msix_index;
			cpu = cpumask_next(cpu, cpu_online_mask);
		पूर्ण
		index++;
	पूर्ण
पूर्ण

/**
 * _base_check_and_enable_high_iops_queues - enable high iops mode
 * @ioc: per adapter object
 * @hba_msix_vector_count: msix vectors supported by HBA
 *
 * Enable high iops queues only अगर
 *  - HBA is a SEA/AERO controller and
 *  - MSI-Xs vector supported by the HBA is 128 and
 *  - total CPU count in the प्रणाली >=16 and
 *  - loaded driver with शेष max_msix_vectors module parameter and
 *  - प्रणाली booted in non kdump mode
 *
 * वापसs nothing.
 */
अटल व्योम
_base_check_and_enable_high_iops_queues(काष्ठा MPT3SAS_ADAPTER *ioc,
		पूर्णांक hba_msix_vector_count)
अणु
	u16 lnksta, speed;

	अगर (perf_mode == MPT_PERF_MODE_IOPS ||
	    perf_mode == MPT_PERF_MODE_LATENCY) अणु
		ioc->high_iops_queues = 0;
		वापस;
	पूर्ण

	अगर (perf_mode == MPT_PERF_MODE_DEFAULT) अणु

		pcie_capability_पढ़ो_word(ioc->pdev, PCI_EXP_LNKSTA, &lnksta);
		speed = lnksta & PCI_EXP_LNKSTA_CLS;

		अगर (speed < 0x4) अणु
			ioc->high_iops_queues = 0;
			वापस;
		पूर्ण
	पूर्ण

	अगर (!reset_devices && ioc->is_aero_ioc &&
	    hba_msix_vector_count == MPT3SAS_GEN35_MAX_MSIX_QUEUES &&
	    num_online_cpus() >= MPT3SAS_HIGH_IOPS_REPLY_QUEUES &&
	    max_msix_vectors == -1)
		ioc->high_iops_queues = MPT3SAS_HIGH_IOPS_REPLY_QUEUES;
	अन्यथा
		ioc->high_iops_queues = 0;
पूर्ण

/**
 * _base_disable_msix - disables msix
 * @ioc: per adapter object
 *
 */
अटल व्योम
_base_disable_msix(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	अगर (!ioc->msix_enable)
		वापस;
	pci_मुक्त_irq_vectors(ioc->pdev);
	ioc->msix_enable = 0;
पूर्ण

/**
 * _base_alloc_irq_vectors - allocate msix vectors
 * @ioc: per adapter object
 *
 */
अटल पूर्णांक
_base_alloc_irq_vectors(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	पूर्णांक i, irq_flags = PCI_IRQ_MSIX;
	काष्ठा irq_affinity desc = अणु .pre_vectors = ioc->high_iops_queues पूर्ण;
	काष्ठा irq_affinity *descp = &desc;

	अगर (ioc->smp_affinity_enable)
		irq_flags |= PCI_IRQ_AFFINITY;
	अन्यथा
		descp = शून्य;

	ioc_info(ioc, " %d %d\n", ioc->high_iops_queues,
	    ioc->reply_queue_count);

	i = pci_alloc_irq_vectors_affinity(ioc->pdev,
	    ioc->high_iops_queues,
	    ioc->reply_queue_count, irq_flags, descp);

	वापस i;
पूर्ण

/**
 * _base_enable_msix - enables msix, failback to io_apic
 * @ioc: per adapter object
 *
 */
अटल पूर्णांक
_base_enable_msix(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	पूर्णांक r;
	पूर्णांक i, local_max_msix_vectors;
	u8 try_msix = 0;

	ioc->msix_load_balance = false;

	अगर (msix_disable == -1 || msix_disable == 0)
		try_msix = 1;

	अगर (!try_msix)
		जाओ try_ioapic;

	अगर (_base_check_enable_msix(ioc) != 0)
		जाओ try_ioapic;

	ioc_info(ioc, "MSI-X vectors supported: %d\n", ioc->msix_vector_count);
	pr_info("\t no of cores: %d, max_msix_vectors: %d\n",
		ioc->cpu_count, max_msix_vectors);
	अगर (ioc->is_aero_ioc)
		_base_check_and_enable_high_iops_queues(ioc,
			ioc->msix_vector_count);
	ioc->reply_queue_count =
		min_t(पूर्णांक, ioc->cpu_count + ioc->high_iops_queues,
		ioc->msix_vector_count);

	अगर (!ioc->rdpq_array_enable && max_msix_vectors == -1)
		local_max_msix_vectors = (reset_devices) ? 1 : 8;
	अन्यथा
		local_max_msix_vectors = max_msix_vectors;

	अगर (local_max_msix_vectors > 0)
		ioc->reply_queue_count = min_t(पूर्णांक, local_max_msix_vectors,
			ioc->reply_queue_count);
	अन्यथा अगर (local_max_msix_vectors == 0)
		जाओ try_ioapic;

	/*
	 * Enable msix_load_balance only अगर combined reply queue mode is
	 * disabled on SAS3 & above generation HBA devices.
	 */
	अगर (!ioc->combined_reply_queue &&
	    ioc->hba_mpi_version_beदीर्घed != MPI2_VERSION) अणु
		ioc_info(ioc,
		    "combined ReplyQueue is off, Enabling msix load balance\n");
		ioc->msix_load_balance = true;
	पूर्ण

	/*
	 * smp affinity setting is not need when msix load balance
	 * is enabled.
	 */
	अगर (ioc->msix_load_balance)
		ioc->smp_affinity_enable = 0;

	r = _base_alloc_irq_vectors(ioc);
	अगर (r < 0) अणु
		ioc_info(ioc, "pci_alloc_irq_vectors failed (r=%d) !!!\n", r);
		जाओ try_ioapic;
	पूर्ण

	ioc->msix_enable = 1;
	ioc->reply_queue_count = r;
	क्रम (i = 0; i < ioc->reply_queue_count; i++) अणु
		r = _base_request_irq(ioc, i);
		अगर (r) अणु
			_base_मुक्त_irq(ioc);
			_base_disable_msix(ioc);
			जाओ try_ioapic;
		पूर्ण
	पूर्ण

	ioc_info(ioc, "High IOPs queues : %s\n",
			ioc->high_iops_queues ? "enabled" : "disabled");

	वापस 0;

/* failback to io_apic पूर्णांकerrupt routing */
 try_ioapic:
	ioc->high_iops_queues = 0;
	ioc_info(ioc, "High IOPs queues : disabled\n");
	ioc->reply_queue_count = 1;
	r = pci_alloc_irq_vectors(ioc->pdev, 1, 1, PCI_IRQ_LEGACY);
	अगर (r < 0) अणु
		dfailprपूर्णांकk(ioc,
			    ioc_info(ioc, "pci_alloc_irq_vector(legacy) failed (r=%d) !!!\n",
				     r));
	पूर्ण अन्यथा
		r = _base_request_irq(ioc, 0);

	वापस r;
पूर्ण

/**
 * mpt3sas_base_unmap_resources - मुक्त controller resources
 * @ioc: per adapter object
 */
अटल व्योम
mpt3sas_base_unmap_resources(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	काष्ठा pci_dev *pdev = ioc->pdev;

	dनिकासprपूर्णांकk(ioc, ioc_info(ioc, "%s\n", __func__));

	_base_मुक्त_irq(ioc);
	_base_disable_msix(ioc);

	kमुक्त(ioc->replyPostRegisterIndex);
	ioc->replyPostRegisterIndex = शून्य;


	अगर (ioc->chip_phys) अणु
		iounmap(ioc->chip);
		ioc->chip_phys = 0;
	पूर्ण

	अगर (pci_is_enabled(pdev)) अणु
		pci_release_selected_regions(ioc->pdev, ioc->bars);
		pci_disable_pcie_error_reporting(pdev);
		pci_disable_device(pdev);
	पूर्ण
पूर्ण

अटल पूर्णांक
_base_diag_reset(काष्ठा MPT3SAS_ADAPTER *ioc);

/**
 * _base_check_क्रम_fault_and_issue_reset - check अगर IOC is in fault state
 *     and अगर it is in fault state then issue diag reset.
 * @ioc: per adapter object
 *
 * Returns: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_base_check_क्रम_fault_and_issue_reset(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	u32 ioc_state;
	पूर्णांक rc = -EFAULT;

	dinitprपूर्णांकk(ioc, pr_info("%s\n", __func__));
	अगर (ioc->pci_error_recovery)
		वापस 0;
	ioc_state = mpt3sas_base_get_iocstate(ioc, 0);
	dhsprपूर्णांकk(ioc, pr_info("%s: ioc_state(0x%08x)\n", __func__, ioc_state));

	अगर ((ioc_state & MPI2_IOC_STATE_MASK) == MPI2_IOC_STATE_FAULT) अणु
		mpt3sas_prपूर्णांक_fault_code(ioc, ioc_state &
		    MPI2_DOORBELL_DATA_MASK);
		rc = _base_diag_reset(ioc);
	पूर्ण अन्यथा अगर ((ioc_state & MPI2_IOC_STATE_MASK) ==
	    MPI2_IOC_STATE_COREDUMP) अणु
		mpt3sas_prपूर्णांक_coredump_info(ioc, ioc_state &
		     MPI2_DOORBELL_DATA_MASK);
		mpt3sas_base_रुको_क्रम_coredump_completion(ioc, __func__);
		rc = _base_diag_reset(ioc);
	पूर्ण

	वापस rc;
पूर्ण

/**
 * mpt3sas_base_map_resources - map in controller resources (io/irq/memap)
 * @ioc: per adapter object
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_base_map_resources(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	काष्ठा pci_dev *pdev = ioc->pdev;
	u32 memap_sz;
	u32 pio_sz;
	पूर्णांक i, r = 0, rc;
	u64 pio_chip = 0;
	phys_addr_t chip_phys = 0;
	काष्ठा adapter_reply_queue *reply_q;

	dinitprपूर्णांकk(ioc, ioc_info(ioc, "%s\n", __func__));

	ioc->bars = pci_select_bars(pdev, IORESOURCE_MEM);
	अगर (pci_enable_device_mem(pdev)) अणु
		ioc_warn(ioc, "pci_enable_device_mem: failed\n");
		ioc->bars = 0;
		वापस -ENODEV;
	पूर्ण


	अगर (pci_request_selected_regions(pdev, ioc->bars,
	    ioc->driver_name)) अणु
		ioc_warn(ioc, "pci_request_selected_regions: failed\n");
		ioc->bars = 0;
		r = -ENODEV;
		जाओ out_fail;
	पूर्ण

/* AER (Advanced Error Reporting) hooks */
	pci_enable_pcie_error_reporting(pdev);

	pci_set_master(pdev);


	अगर (_base_config_dma_addressing(ioc, pdev) != 0) अणु
		ioc_warn(ioc, "no suitable DMA mask for %s\n", pci_name(pdev));
		r = -ENODEV;
		जाओ out_fail;
	पूर्ण

	क्रम (i = 0, memap_sz = 0, pio_sz = 0; (i < DEVICE_COUNT_RESOURCE) &&
	     (!memap_sz || !pio_sz); i++) अणु
		अगर (pci_resource_flags(pdev, i) & IORESOURCE_IO) अणु
			अगर (pio_sz)
				जारी;
			pio_chip = (u64)pci_resource_start(pdev, i);
			pio_sz = pci_resource_len(pdev, i);
		पूर्ण अन्यथा अगर (pci_resource_flags(pdev, i) & IORESOURCE_MEM) अणु
			अगर (memap_sz)
				जारी;
			ioc->chip_phys = pci_resource_start(pdev, i);
			chip_phys = ioc->chip_phys;
			memap_sz = pci_resource_len(pdev, i);
			ioc->chip = ioremap(ioc->chip_phys, memap_sz);
		पूर्ण
	पूर्ण

	अगर (ioc->chip == शून्य) अणु
		ioc_err(ioc,
		    "unable to map adapter memory! or resource not found\n");
		r = -EINVAL;
		जाओ out_fail;
	पूर्ण

	mpt3sas_base_mask_पूर्णांकerrupts(ioc);

	r = _base_get_ioc_facts(ioc);
	अगर (r) अणु
		rc = _base_check_क्रम_fault_and_issue_reset(ioc);
		अगर (rc || (_base_get_ioc_facts(ioc)))
			जाओ out_fail;
	पूर्ण

	अगर (!ioc->rdpq_array_enable_asचिन्हित) अणु
		ioc->rdpq_array_enable = ioc->rdpq_array_capable;
		ioc->rdpq_array_enable_asचिन्हित = 1;
	पूर्ण

	r = _base_enable_msix(ioc);
	अगर (r)
		जाओ out_fail;

	अगर (!ioc->is_driver_loading)
		_base_init_irqpolls(ioc);
	/* Use the Combined reply queue feature only क्रम SAS3 C0 & higher
	 * revision HBAs and also only when reply queue count is greater than 8
	 */
	अगर (ioc->combined_reply_queue) अणु
		/* Determine the Supplemental Reply Post Host Index Registers
		 * Addresse. Supplemental Reply Post Host Index Registers
		 * starts at offset MPI25_SUP_REPLY_POST_HOST_INDEX_OFFSET and
		 * each रेजिस्टर is at offset bytes of
		 * MPT3_SUP_REPLY_POST_HOST_INDEX_REG_OFFSET from previous one.
		 */
		ioc->replyPostRegisterIndex = kसुस्मृति(
		     ioc->combined_reply_index_count,
		     माप(resource_माप_प्रकार *), GFP_KERNEL);
		अगर (!ioc->replyPostRegisterIndex) अणु
			ioc_err(ioc,
			    "allocation for replyPostRegisterIndex failed!\n");
			r = -ENOMEM;
			जाओ out_fail;
		पूर्ण

		क्रम (i = 0; i < ioc->combined_reply_index_count; i++) अणु
			ioc->replyPostRegisterIndex[i] = (resource_माप_प्रकार *)
			     ((u8 __क्रमce *)&ioc->chip->Doorbell +
			     MPI25_SUP_REPLY_POST_HOST_INDEX_OFFSET +
			     (i * MPT3_SUP_REPLY_POST_HOST_INDEX_REG_OFFSET));
		पूर्ण
	पूर्ण

	अगर (ioc->is_warpdrive) अणु
		ioc->reply_post_host_index[0] = (resource_माप_प्रकार __iomem *)
		    &ioc->chip->ReplyPostHostIndex;

		क्रम (i = 1; i < ioc->cpu_msix_table_sz; i++)
			ioc->reply_post_host_index[i] =
			(resource_माप_प्रकार __iomem *)
			((u8 __iomem *)&ioc->chip->Doorbell + (0x4000 + ((i - 1)
			* 4)));
	पूर्ण

	list_क्रम_each_entry(reply_q, &ioc->reply_queue_list, list)
		pr_info("%s: %s enabled: IRQ %d\n",
			reply_q->name,
			ioc->msix_enable ? "PCI-MSI-X" : "IO-APIC",
			pci_irq_vector(ioc->pdev, reply_q->msix_index));

	ioc_info(ioc, "iomem(%pap), mapped(0x%p), size(%d)\n",
		 &chip_phys, ioc->chip, memap_sz);
	ioc_info(ioc, "ioport(0x%016llx), size(%d)\n",
		 (अचिन्हित दीर्घ दीर्घ)pio_chip, pio_sz);

	/* Save PCI configuration state क्रम recovery from PCI AER/EEH errors */
	pci_save_state(pdev);
	वापस 0;

 out_fail:
	mpt3sas_base_unmap_resources(ioc);
	वापस r;
पूर्ण

/**
 * mpt3sas_base_get_msg_frame - obtain request mf poपूर्णांकer
 * @ioc: per adapter object
 * @smid: प्रणाली request message index(smid zero is invalid)
 *
 * Return: virt poपूर्णांकer to message frame.
 */
व्योम *
mpt3sas_base_get_msg_frame(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid)
अणु
	वापस (व्योम *)(ioc->request + (smid * ioc->request_sz));
पूर्ण

/**
 * mpt3sas_base_get_sense_buffer - obtain a sense buffer virt addr
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 *
 * Return: virt poपूर्णांकer to sense buffer.
 */
व्योम *
mpt3sas_base_get_sense_buffer(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid)
अणु
	वापस (व्योम *)(ioc->sense + ((smid - 1) * SCSI_SENSE_BUFFERSIZE));
पूर्ण

/**
 * mpt3sas_base_get_sense_buffer_dma - obtain a sense buffer dma addr
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 *
 * Return: phys poपूर्णांकer to the low 32bit address of the sense buffer.
 */
__le32
mpt3sas_base_get_sense_buffer_dma(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid)
अणु
	वापस cpu_to_le32(ioc->sense_dma + ((smid - 1) *
	    SCSI_SENSE_BUFFERSIZE));
पूर्ण

/**
 * mpt3sas_base_get_pcie_sgl - obtain a PCIe SGL virt addr
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 *
 * Return: virt poपूर्णांकer to a PCIe SGL.
 */
व्योम *
mpt3sas_base_get_pcie_sgl(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid)
अणु
	वापस (व्योम *)(ioc->pcie_sg_lookup[smid - 1].pcie_sgl);
पूर्ण

/**
 * mpt3sas_base_get_pcie_sgl_dma - obtain a PCIe SGL dma addr
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 *
 * Return: phys poपूर्णांकer to the address of the PCIe buffer.
 */
dma_addr_t
mpt3sas_base_get_pcie_sgl_dma(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid)
अणु
	वापस ioc->pcie_sg_lookup[smid - 1].pcie_sgl_dma;
पूर्ण

/**
 * mpt3sas_base_get_reply_virt_addr - obtain reply frames virt address
 * @ioc: per adapter object
 * @phys_addr: lower 32 physical addr of the reply
 *
 * Converts 32bit lower physical addr पूर्णांकo a virt address.
 */
व्योम *
mpt3sas_base_get_reply_virt_addr(काष्ठा MPT3SAS_ADAPTER *ioc, u32 phys_addr)
अणु
	अगर (!phys_addr)
		वापस शून्य;
	वापस ioc->reply + (phys_addr - (u32)ioc->reply_dma);
पूर्ण

/**
 * _base_get_msix_index - get the msix index
 * @ioc: per adapter object
 * @scmd: scsi_cmnd object
 *
 * वापसs msix index of general reply queues,
 * i.e. reply queue on which IO request's reply
 * should be posted by the HBA firmware.
 */
अटल अंतरभूत u8
_base_get_msix_index(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा scsi_cmnd *scmd)
अणु
	/* Enables reply_queue load balancing */
	अगर (ioc->msix_load_balance)
		वापस ioc->reply_queue_count ?
		    base_mod64(atomic64_add_वापस(1,
		    &ioc->total_io_cnt), ioc->reply_queue_count) : 0;

	अगर (scmd && ioc->shost->nr_hw_queues > 1) अणु
		u32 tag = blk_mq_unique_tag(scmd->request);

		वापस blk_mq_unique_tag_to_hwq(tag) +
			ioc->high_iops_queues;
	पूर्ण

	वापस ioc->cpu_msix_table[raw_smp_processor_id()];
पूर्ण

/**
 * _base_get_high_iops_msix_index - get the msix index of
 *				high iops queues
 * @ioc: per adapter object
 * @scmd: scsi_cmnd object
 *
 * Returns: msix index of high iops reply queues.
 * i.e. high iops reply queue on which IO request's
 * reply should be posted by the HBA firmware.
 */
अटल अंतरभूत u8
_base_get_high_iops_msix_index(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा scsi_cmnd *scmd)
अणु
	/**
	 * Round robin the IO पूर्णांकerrupts among the high iops
	 * reply queues in terms of batch count 16 when outstanding
	 * IOs on the target device is >=8.
	 */

	अगर (scsi_device_busy(scmd->device) > MPT3SAS_DEVICE_HIGH_IOPS_DEPTH)
		वापस base_mod64((
		    atomic64_add_वापस(1, &ioc->high_iops_outstanding) /
		    MPT3SAS_HIGH_IOPS_BATCH_COUNT),
		    MPT3SAS_HIGH_IOPS_REPLY_QUEUES);

	वापस _base_get_msix_index(ioc, scmd);
पूर्ण

/**
 * mpt3sas_base_get_smid - obtain a मुक्त smid from पूर्णांकernal queue
 * @ioc: per adapter object
 * @cb_idx: callback index
 *
 * Return: smid (zero is invalid)
 */
u16
mpt3sas_base_get_smid(काष्ठा MPT3SAS_ADAPTER *ioc, u8 cb_idx)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा request_tracker *request;
	u16 smid;

	spin_lock_irqsave(&ioc->scsi_lookup_lock, flags);
	अगर (list_empty(&ioc->पूर्णांकernal_मुक्त_list)) अणु
		spin_unlock_irqrestore(&ioc->scsi_lookup_lock, flags);
		ioc_err(ioc, "%s: smid not available\n", __func__);
		वापस 0;
	पूर्ण

	request = list_entry(ioc->पूर्णांकernal_मुक्त_list.next,
	    काष्ठा request_tracker, tracker_list);
	request->cb_idx = cb_idx;
	smid = request->smid;
	list_del(&request->tracker_list);
	spin_unlock_irqrestore(&ioc->scsi_lookup_lock, flags);
	वापस smid;
पूर्ण

/**
 * mpt3sas_base_get_smid_scsiio - obtain a मुक्त smid from scsiio queue
 * @ioc: per adapter object
 * @cb_idx: callback index
 * @scmd: poपूर्णांकer to scsi command object
 *
 * Return: smid (zero is invalid)
 */
u16
mpt3sas_base_get_smid_scsiio(काष्ठा MPT3SAS_ADAPTER *ioc, u8 cb_idx,
	काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा scsiio_tracker *request = scsi_cmd_priv(scmd);
	u16 smid;
	u32 tag, unique_tag;

	unique_tag = blk_mq_unique_tag(scmd->request);
	tag = blk_mq_unique_tag_to_tag(unique_tag);

	/*
	 * Store hw queue number corresponding to the tag.
	 * This hw queue number is used later to determine
	 * the unique_tag using the logic below. This unique_tag
	 * is used to retrieve the scmd poपूर्णांकer corresponding
	 * to tag using scsi_host_find_tag() API.
	 *
	 * tag = smid - 1;
	 * unique_tag = ioc->io_queue_num[tag] << BLK_MQ_UNIQUE_TAG_BITS | tag;
	 */
	ioc->io_queue_num[tag] = blk_mq_unique_tag_to_hwq(unique_tag);

	smid = tag + 1;
	request->cb_idx = cb_idx;
	request->smid = smid;
	request->scmd = scmd;
	INIT_LIST_HEAD(&request->chain_list);
	वापस smid;
पूर्ण

/**
 * mpt3sas_base_get_smid_hpr - obtain a मुक्त smid from hi-priority queue
 * @ioc: per adapter object
 * @cb_idx: callback index
 *
 * Return: smid (zero is invalid)
 */
u16
mpt3sas_base_get_smid_hpr(काष्ठा MPT3SAS_ADAPTER *ioc, u8 cb_idx)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा request_tracker *request;
	u16 smid;

	spin_lock_irqsave(&ioc->scsi_lookup_lock, flags);
	अगर (list_empty(&ioc->hpr_मुक्त_list)) अणु
		spin_unlock_irqrestore(&ioc->scsi_lookup_lock, flags);
		वापस 0;
	पूर्ण

	request = list_entry(ioc->hpr_मुक्त_list.next,
	    काष्ठा request_tracker, tracker_list);
	request->cb_idx = cb_idx;
	smid = request->smid;
	list_del(&request->tracker_list);
	spin_unlock_irqrestore(&ioc->scsi_lookup_lock, flags);
	वापस smid;
पूर्ण

अटल व्योम
_base_recovery_check(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	/*
	 * See _रुको_क्रम_commands_to_complete() call with regards to this code.
	 */
	अगर (ioc->shost_recovery && ioc->pending_io_count) अणु
		ioc->pending_io_count = scsi_host_busy(ioc->shost);
		अगर (ioc->pending_io_count == 0)
			wake_up(&ioc->reset_wq);
	पूर्ण
पूर्ण

व्योम mpt3sas_base_clear_st(काष्ठा MPT3SAS_ADAPTER *ioc,
			   काष्ठा scsiio_tracker *st)
अणु
	अगर (WARN_ON(st->smid == 0))
		वापस;
	st->cb_idx = 0xFF;
	st->direct_io = 0;
	st->scmd = शून्य;
	atomic_set(&ioc->chain_lookup[st->smid - 1].chain_offset, 0);
	st->smid = 0;
पूर्ण

/**
 * mpt3sas_base_मुक्त_smid - put smid back on मुक्त_list
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 */
व्योम
mpt3sas_base_मुक्त_smid(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	अगर (smid < ioc->hi_priority_smid) अणु
		काष्ठा scsiio_tracker *st;
		व्योम *request;

		st = _get_st_from_smid(ioc, smid);
		अगर (!st) अणु
			_base_recovery_check(ioc);
			वापस;
		पूर्ण

		/* Clear MPI request frame */
		request = mpt3sas_base_get_msg_frame(ioc, smid);
		स_रखो(request, 0, ioc->request_sz);

		mpt3sas_base_clear_st(ioc, st);
		_base_recovery_check(ioc);
		ioc->io_queue_num[smid - 1] = 0;
		वापस;
	पूर्ण

	spin_lock_irqsave(&ioc->scsi_lookup_lock, flags);
	अगर (smid < ioc->पूर्णांकernal_smid) अणु
		/* hi-priority */
		i = smid - ioc->hi_priority_smid;
		ioc->hpr_lookup[i].cb_idx = 0xFF;
		list_add(&ioc->hpr_lookup[i].tracker_list, &ioc->hpr_मुक्त_list);
	पूर्ण अन्यथा अगर (smid <= ioc->hba_queue_depth) अणु
		/* पूर्णांकernal queue */
		i = smid - ioc->पूर्णांकernal_smid;
		ioc->पूर्णांकernal_lookup[i].cb_idx = 0xFF;
		list_add(&ioc->पूर्णांकernal_lookup[i].tracker_list,
		    &ioc->पूर्णांकernal_मुक्त_list);
	पूर्ण
	spin_unlock_irqrestore(&ioc->scsi_lookup_lock, flags);
पूर्ण

/**
 * _base_mpi_ep_ग_लिखोq - 32 bit ग_लिखो to MMIO
 * @b: data payload
 * @addr: address in MMIO space
 * @ग_लिखोq_lock: spin lock
 *
 * This special handling क्रम MPI EP to take care of 32 bit
 * environment where its not quarenteed to send the entire word
 * in one transfer.
 */
अटल अंतरभूत व्योम
_base_mpi_ep_ग_लिखोq(__u64 b, अस्थिर व्योम __iomem *addr,
					spinlock_t *ग_लिखोq_lock)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(ग_लिखोq_lock, flags);
	__raw_ग_लिखोl((u32)(b), addr);
	__raw_ग_लिखोl((u32)(b >> 32), (addr + 4));
	spin_unlock_irqrestore(ग_लिखोq_lock, flags);
पूर्ण

/**
 * _base_ग_लिखोq - 64 bit ग_लिखो to MMIO
 * @b: data payload
 * @addr: address in MMIO space
 * @ग_लिखोq_lock: spin lock
 *
 * Glue क्रम handling an atomic 64 bit word to MMIO. This special handling takes
 * care of 32 bit environment where its not quarenteed to send the entire word
 * in one transfer.
 */
#अगर defined(ग_लिखोq) && defined(CONFIG_64BIT)
अटल अंतरभूत व्योम
_base_ग_लिखोq(__u64 b, अस्थिर व्योम __iomem *addr, spinlock_t *ग_लिखोq_lock)
अणु
	wmb();
	__raw_ग_लिखोq(b, addr);
	barrier();
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम
_base_ग_लिखोq(__u64 b, अस्थिर व्योम __iomem *addr, spinlock_t *ग_लिखोq_lock)
अणु
	_base_mpi_ep_ग_लिखोq(b, addr, ग_लिखोq_lock);
पूर्ण
#पूर्ण_अगर

/**
 * _base_set_and_get_msix_index - get the msix index and assign to msix_io
 *                                variable of scsi tracker
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 *
 * वापसs msix index.
 */
अटल u8
_base_set_and_get_msix_index(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid)
अणु
	काष्ठा scsiio_tracker *st = शून्य;

	अगर (smid < ioc->hi_priority_smid)
		st = _get_st_from_smid(ioc, smid);

	अगर (st == शून्य)
		वापस  _base_get_msix_index(ioc, शून्य);

	st->msix_io = ioc->get_msix_index_क्रम_smlio(ioc, st->scmd);
	वापस st->msix_io;
पूर्ण

/**
 * _base_put_smid_mpi_ep_scsi_io - send SCSI_IO request to firmware
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @handle: device handle
 */
अटल व्योम
_base_put_smid_mpi_ep_scsi_io(काष्ठा MPT3SAS_ADAPTER *ioc,
	u16 smid, u16 handle)
अणु
	Mpi2RequestDescriptorUnion_t descriptor;
	u64 *request = (u64 *)&descriptor;
	व्योम *mpi_req_iomem;
	__le32 *mfp = (__le32 *)mpt3sas_base_get_msg_frame(ioc, smid);

	_clone_sg_entries(ioc, (व्योम *) mfp, smid);
	mpi_req_iomem = (व्योम __क्रमce *)ioc->chip +
			MPI_FRAME_START_OFFSET + (smid * ioc->request_sz);
	_base_clone_mpi_to_sys_mem(mpi_req_iomem, (व्योम *)mfp,
					ioc->request_sz);
	descriptor.SCSIIO.RequestFlags = MPI2_REQ_DESCRIPT_FLAGS_SCSI_IO;
	descriptor.SCSIIO.MSIxIndex = _base_set_and_get_msix_index(ioc, smid);
	descriptor.SCSIIO.SMID = cpu_to_le16(smid);
	descriptor.SCSIIO.DevHandle = cpu_to_le16(handle);
	descriptor.SCSIIO.LMID = 0;
	_base_mpi_ep_ग_लिखोq(*request, &ioc->chip->RequestDescriptorPostLow,
	    &ioc->scsi_lookup_lock);
पूर्ण

/**
 * _base_put_smid_scsi_io - send SCSI_IO request to firmware
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @handle: device handle
 */
अटल व्योम
_base_put_smid_scsi_io(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid, u16 handle)
अणु
	Mpi2RequestDescriptorUnion_t descriptor;
	u64 *request = (u64 *)&descriptor;


	descriptor.SCSIIO.RequestFlags = MPI2_REQ_DESCRIPT_FLAGS_SCSI_IO;
	descriptor.SCSIIO.MSIxIndex = _base_set_and_get_msix_index(ioc, smid);
	descriptor.SCSIIO.SMID = cpu_to_le16(smid);
	descriptor.SCSIIO.DevHandle = cpu_to_le16(handle);
	descriptor.SCSIIO.LMID = 0;
	_base_ग_लिखोq(*request, &ioc->chip->RequestDescriptorPostLow,
	    &ioc->scsi_lookup_lock);
पूर्ण

/**
 * _base_put_smid_fast_path - send fast path request to firmware
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @handle: device handle
 */
अटल व्योम
_base_put_smid_fast_path(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid,
	u16 handle)
अणु
	Mpi2RequestDescriptorUnion_t descriptor;
	u64 *request = (u64 *)&descriptor;

	descriptor.SCSIIO.RequestFlags =
	    MPI25_REQ_DESCRIPT_FLAGS_FAST_PATH_SCSI_IO;
	descriptor.SCSIIO.MSIxIndex = _base_set_and_get_msix_index(ioc, smid);
	descriptor.SCSIIO.SMID = cpu_to_le16(smid);
	descriptor.SCSIIO.DevHandle = cpu_to_le16(handle);
	descriptor.SCSIIO.LMID = 0;
	_base_ग_लिखोq(*request, &ioc->chip->RequestDescriptorPostLow,
	    &ioc->scsi_lookup_lock);
पूर्ण

/**
 * _base_put_smid_hi_priority - send Task Management request to firmware
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @msix_task: msix_task will be same as msix of IO inहाल of task पात अन्यथा 0.
 */
अटल व्योम
_base_put_smid_hi_priority(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid,
	u16 msix_task)
अणु
	Mpi2RequestDescriptorUnion_t descriptor;
	व्योम *mpi_req_iomem;
	u64 *request;

	अगर (ioc->is_mcpu_endpoपूर्णांक) अणु
		__le32 *mfp = (__le32 *)mpt3sas_base_get_msg_frame(ioc, smid);

		/* TBD 256 is offset within sys रेजिस्टर. */
		mpi_req_iomem = (व्योम __क्रमce *)ioc->chip
					+ MPI_FRAME_START_OFFSET
					+ (smid * ioc->request_sz);
		_base_clone_mpi_to_sys_mem(mpi_req_iomem, (व्योम *)mfp,
							ioc->request_sz);
	पूर्ण

	request = (u64 *)&descriptor;

	descriptor.HighPriority.RequestFlags =
	    MPI2_REQ_DESCRIPT_FLAGS_HIGH_PRIORITY;
	descriptor.HighPriority.MSIxIndex =  msix_task;
	descriptor.HighPriority.SMID = cpu_to_le16(smid);
	descriptor.HighPriority.LMID = 0;
	descriptor.HighPriority.Reserved1 = 0;
	अगर (ioc->is_mcpu_endpoपूर्णांक)
		_base_mpi_ep_ग_लिखोq(*request,
				&ioc->chip->RequestDescriptorPostLow,
				&ioc->scsi_lookup_lock);
	अन्यथा
		_base_ग_लिखोq(*request, &ioc->chip->RequestDescriptorPostLow,
		    &ioc->scsi_lookup_lock);
पूर्ण

/**
 * mpt3sas_base_put_smid_nvme_encap - send NVMe encapsulated request to
 *  firmware
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 */
व्योम
mpt3sas_base_put_smid_nvme_encap(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid)
अणु
	Mpi2RequestDescriptorUnion_t descriptor;
	u64 *request = (u64 *)&descriptor;

	descriptor.Default.RequestFlags =
		MPI26_REQ_DESCRIPT_FLAGS_PCIE_ENCAPSULATED;
	descriptor.Default.MSIxIndex =  _base_set_and_get_msix_index(ioc, smid);
	descriptor.Default.SMID = cpu_to_le16(smid);
	descriptor.Default.LMID = 0;
	descriptor.Default.DescriptorTypeDependent = 0;
	_base_ग_लिखोq(*request, &ioc->chip->RequestDescriptorPostLow,
	    &ioc->scsi_lookup_lock);
पूर्ण

/**
 * _base_put_smid_शेष - Default, primarily used क्रम config pages
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 */
अटल व्योम
_base_put_smid_शेष(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid)
अणु
	Mpi2RequestDescriptorUnion_t descriptor;
	व्योम *mpi_req_iomem;
	u64 *request;

	अगर (ioc->is_mcpu_endpoपूर्णांक) अणु
		__le32 *mfp = (__le32 *)mpt3sas_base_get_msg_frame(ioc, smid);

		_clone_sg_entries(ioc, (व्योम *) mfp, smid);
		/* TBD 256 is offset within sys रेजिस्टर */
		mpi_req_iomem = (व्योम __क्रमce *)ioc->chip +
			MPI_FRAME_START_OFFSET + (smid * ioc->request_sz);
		_base_clone_mpi_to_sys_mem(mpi_req_iomem, (व्योम *)mfp,
							ioc->request_sz);
	पूर्ण
	request = (u64 *)&descriptor;
	descriptor.Default.RequestFlags = MPI2_REQ_DESCRIPT_FLAGS_DEFAULT_TYPE;
	descriptor.Default.MSIxIndex = _base_set_and_get_msix_index(ioc, smid);
	descriptor.Default.SMID = cpu_to_le16(smid);
	descriptor.Default.LMID = 0;
	descriptor.Default.DescriptorTypeDependent = 0;
	अगर (ioc->is_mcpu_endpoपूर्णांक)
		_base_mpi_ep_ग_लिखोq(*request,
				&ioc->chip->RequestDescriptorPostLow,
				&ioc->scsi_lookup_lock);
	अन्यथा
		_base_ग_लिखोq(*request, &ioc->chip->RequestDescriptorPostLow,
				&ioc->scsi_lookup_lock);
पूर्ण

/**
 * _base_put_smid_scsi_io_atomic - send SCSI_IO request to firmware using
 *   Atomic Request Descriptor
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @handle: device handle, unused in this function, क्रम function type match
 *
 * Return nothing.
 */
अटल व्योम
_base_put_smid_scsi_io_atomic(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid,
	u16 handle)
अणु
	Mpi26AtomicRequestDescriptor_t descriptor;
	u32 *request = (u32 *)&descriptor;

	descriptor.RequestFlags = MPI2_REQ_DESCRIPT_FLAGS_SCSI_IO;
	descriptor.MSIxIndex = _base_set_and_get_msix_index(ioc, smid);
	descriptor.SMID = cpu_to_le16(smid);

	ग_लिखोl(cpu_to_le32(*request), &ioc->chip->AtomicRequestDescriptorPost);
पूर्ण

/**
 * _base_put_smid_fast_path_atomic - send fast path request to firmware
 * using Atomic Request Descriptor
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @handle: device handle, unused in this function, क्रम function type match
 * Return nothing
 */
अटल व्योम
_base_put_smid_fast_path_atomic(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid,
	u16 handle)
अणु
	Mpi26AtomicRequestDescriptor_t descriptor;
	u32 *request = (u32 *)&descriptor;

	descriptor.RequestFlags = MPI25_REQ_DESCRIPT_FLAGS_FAST_PATH_SCSI_IO;
	descriptor.MSIxIndex = _base_set_and_get_msix_index(ioc, smid);
	descriptor.SMID = cpu_to_le16(smid);

	ग_लिखोl(cpu_to_le32(*request), &ioc->chip->AtomicRequestDescriptorPost);
पूर्ण

/**
 * _base_put_smid_hi_priority_atomic - send Task Management request to
 * firmware using Atomic Request Descriptor
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @msix_task: msix_task will be same as msix of IO inहाल of task पात अन्यथा 0
 *
 * Return nothing.
 */
अटल व्योम
_base_put_smid_hi_priority_atomic(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid,
	u16 msix_task)
अणु
	Mpi26AtomicRequestDescriptor_t descriptor;
	u32 *request = (u32 *)&descriptor;

	descriptor.RequestFlags = MPI2_REQ_DESCRIPT_FLAGS_HIGH_PRIORITY;
	descriptor.MSIxIndex = msix_task;
	descriptor.SMID = cpu_to_le16(smid);

	ग_लिखोl(cpu_to_le32(*request), &ioc->chip->AtomicRequestDescriptorPost);
पूर्ण

/**
 * _base_put_smid_शेष_atomic - Default, primarily used क्रम config pages
 * use Atomic Request Descriptor
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 *
 * Return nothing.
 */
अटल व्योम
_base_put_smid_शेष_atomic(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid)
अणु
	Mpi26AtomicRequestDescriptor_t descriptor;
	u32 *request = (u32 *)&descriptor;

	descriptor.RequestFlags = MPI2_REQ_DESCRIPT_FLAGS_DEFAULT_TYPE;
	descriptor.MSIxIndex = _base_set_and_get_msix_index(ioc, smid);
	descriptor.SMID = cpu_to_le16(smid);

	ग_लिखोl(cpu_to_le32(*request), &ioc->chip->AtomicRequestDescriptorPost);
पूर्ण

/**
 * _base_display_OEMs_bअक्रमing - Display bअक्रमing string
 * @ioc: per adapter object
 */
अटल व्योम
_base_display_OEMs_bअक्रमing(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	अगर (ioc->pdev->subप्रणाली_venकरोr != PCI_VENDOR_ID_INTEL)
		वापस;

	चयन (ioc->pdev->subप्रणाली_venकरोr) अणु
	हाल PCI_VENDOR_ID_INTEL:
		चयन (ioc->pdev->device) अणु
		हाल MPI2_MFGPAGE_DEVID_SAS2008:
			चयन (ioc->pdev->subप्रणाली_device) अणु
			हाल MPT2SAS_INTEL_RMS2LL080_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT2SAS_INTEL_RMS2LL080_BRANDING);
				अवरोध;
			हाल MPT2SAS_INTEL_RMS2LL040_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT2SAS_INTEL_RMS2LL040_BRANDING);
				अवरोध;
			हाल MPT2SAS_INTEL_SSD910_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT2SAS_INTEL_SSD910_BRANDING);
				अवरोध;
			शेष:
				ioc_info(ioc, "Intel(R) Controller: Subsystem ID: 0x%X\n",
					 ioc->pdev->subप्रणाली_device);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल MPI2_MFGPAGE_DEVID_SAS2308_2:
			चयन (ioc->pdev->subप्रणाली_device) अणु
			हाल MPT2SAS_INTEL_RS25GB008_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT2SAS_INTEL_RS25GB008_BRANDING);
				अवरोध;
			हाल MPT2SAS_INTEL_RMS25JB080_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT2SAS_INTEL_RMS25JB080_BRANDING);
				अवरोध;
			हाल MPT2SAS_INTEL_RMS25JB040_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT2SAS_INTEL_RMS25JB040_BRANDING);
				अवरोध;
			हाल MPT2SAS_INTEL_RMS25KB080_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT2SAS_INTEL_RMS25KB080_BRANDING);
				अवरोध;
			हाल MPT2SAS_INTEL_RMS25KB040_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT2SAS_INTEL_RMS25KB040_BRANDING);
				अवरोध;
			हाल MPT2SAS_INTEL_RMS25LB040_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT2SAS_INTEL_RMS25LB040_BRANDING);
				अवरोध;
			हाल MPT2SAS_INTEL_RMS25LB080_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT2SAS_INTEL_RMS25LB080_BRANDING);
				अवरोध;
			शेष:
				ioc_info(ioc, "Intel(R) Controller: Subsystem ID: 0x%X\n",
					 ioc->pdev->subप्रणाली_device);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल MPI25_MFGPAGE_DEVID_SAS3008:
			चयन (ioc->pdev->subप्रणाली_device) अणु
			हाल MPT3SAS_INTEL_RMS3JC080_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT3SAS_INTEL_RMS3JC080_BRANDING);
				अवरोध;

			हाल MPT3SAS_INTEL_RS3GC008_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT3SAS_INTEL_RS3GC008_BRANDING);
				अवरोध;
			हाल MPT3SAS_INTEL_RS3FC044_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT3SAS_INTEL_RS3FC044_BRANDING);
				अवरोध;
			हाल MPT3SAS_INTEL_RS3UC080_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT3SAS_INTEL_RS3UC080_BRANDING);
				अवरोध;
			शेष:
				ioc_info(ioc, "Intel(R) Controller: Subsystem ID: 0x%X\n",
					 ioc->pdev->subप्रणाली_device);
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			ioc_info(ioc, "Intel(R) Controller: Subsystem ID: 0x%X\n",
				 ioc->pdev->subप्रणाली_device);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल PCI_VENDOR_ID_DELL:
		चयन (ioc->pdev->device) अणु
		हाल MPI2_MFGPAGE_DEVID_SAS2008:
			चयन (ioc->pdev->subप्रणाली_device) अणु
			हाल MPT2SAS_DELL_6GBPS_SAS_HBA_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT2SAS_DELL_6GBPS_SAS_HBA_BRANDING);
				अवरोध;
			हाल MPT2SAS_DELL_PERC_H200_ADAPTER_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT2SAS_DELL_PERC_H200_ADAPTER_BRANDING);
				अवरोध;
			हाल MPT2SAS_DELL_PERC_H200_INTEGRATED_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT2SAS_DELL_PERC_H200_INTEGRATED_BRANDING);
				अवरोध;
			हाल MPT2SAS_DELL_PERC_H200_MODULAR_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT2SAS_DELL_PERC_H200_MODULAR_BRANDING);
				अवरोध;
			हाल MPT2SAS_DELL_PERC_H200_EMBEDDED_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT2SAS_DELL_PERC_H200_EMBEDDED_BRANDING);
				अवरोध;
			हाल MPT2SAS_DELL_PERC_H200_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT2SAS_DELL_PERC_H200_BRANDING);
				अवरोध;
			हाल MPT2SAS_DELL_6GBPS_SAS_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT2SAS_DELL_6GBPS_SAS_BRANDING);
				अवरोध;
			शेष:
				ioc_info(ioc, "Dell 6Gbps HBA: Subsystem ID: 0x%X\n",
					 ioc->pdev->subप्रणाली_device);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल MPI25_MFGPAGE_DEVID_SAS3008:
			चयन (ioc->pdev->subप्रणाली_device) अणु
			हाल MPT3SAS_DELL_12G_HBA_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT3SAS_DELL_12G_HBA_BRANDING);
				अवरोध;
			शेष:
				ioc_info(ioc, "Dell 12Gbps HBA: Subsystem ID: 0x%X\n",
					 ioc->pdev->subप्रणाली_device);
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			ioc_info(ioc, "Dell HBA: Subsystem ID: 0x%X\n",
				 ioc->pdev->subप्रणाली_device);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल PCI_VENDOR_ID_CISCO:
		चयन (ioc->pdev->device) अणु
		हाल MPI25_MFGPAGE_DEVID_SAS3008:
			चयन (ioc->pdev->subप्रणाली_device) अणु
			हाल MPT3SAS_CISCO_12G_8E_HBA_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT3SAS_CISCO_12G_8E_HBA_BRANDING);
				अवरोध;
			हाल MPT3SAS_CISCO_12G_8I_HBA_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT3SAS_CISCO_12G_8I_HBA_BRANDING);
				अवरोध;
			हाल MPT3SAS_CISCO_12G_AVILA_HBA_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT3SAS_CISCO_12G_AVILA_HBA_BRANDING);
				अवरोध;
			शेष:
				ioc_info(ioc, "Cisco 12Gbps SAS HBA: Subsystem ID: 0x%X\n",
					 ioc->pdev->subप्रणाली_device);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल MPI25_MFGPAGE_DEVID_SAS3108_1:
			चयन (ioc->pdev->subप्रणाली_device) अणु
			हाल MPT3SAS_CISCO_12G_AVILA_HBA_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT3SAS_CISCO_12G_AVILA_HBA_BRANDING);
				अवरोध;
			हाल MPT3SAS_CISCO_12G_COLUSA_MEZZANINE_HBA_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT3SAS_CISCO_12G_COLUSA_MEZZANINE_HBA_BRANDING);
				अवरोध;
			शेष:
				ioc_info(ioc, "Cisco 12Gbps SAS HBA: Subsystem ID: 0x%X\n",
					 ioc->pdev->subप्रणाली_device);
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			ioc_info(ioc, "Cisco SAS HBA: Subsystem ID: 0x%X\n",
				 ioc->pdev->subप्रणाली_device);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल MPT2SAS_HP_3PAR_SSVID:
		चयन (ioc->pdev->device) अणु
		हाल MPI2_MFGPAGE_DEVID_SAS2004:
			चयन (ioc->pdev->subप्रणाली_device) अणु
			हाल MPT2SAS_HP_DAUGHTER_2_4_INTERNAL_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT2SAS_HP_DAUGHTER_2_4_INTERNAL_BRANDING);
				अवरोध;
			शेष:
				ioc_info(ioc, "HP 6Gbps SAS HBA: Subsystem ID: 0x%X\n",
					 ioc->pdev->subप्रणाली_device);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल MPI2_MFGPAGE_DEVID_SAS2308_2:
			चयन (ioc->pdev->subप्रणाली_device) अणु
			हाल MPT2SAS_HP_2_4_INTERNAL_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT2SAS_HP_2_4_INTERNAL_BRANDING);
				अवरोध;
			हाल MPT2SAS_HP_2_4_EXTERNAL_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT2SAS_HP_2_4_EXTERNAL_BRANDING);
				अवरोध;
			हाल MPT2SAS_HP_1_4_INTERNAL_1_4_EXTERNAL_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT2SAS_HP_1_4_INTERNAL_1_4_EXTERNAL_BRANDING);
				अवरोध;
			हाल MPT2SAS_HP_EMBEDDED_2_4_INTERNAL_SSDID:
				ioc_info(ioc, "%s\n",
					 MPT2SAS_HP_EMBEDDED_2_4_INTERNAL_BRANDING);
				अवरोध;
			शेष:
				ioc_info(ioc, "HP 6Gbps SAS HBA: Subsystem ID: 0x%X\n",
					 ioc->pdev->subप्रणाली_device);
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			ioc_info(ioc, "HP SAS HBA: Subsystem ID: 0x%X\n",
				 ioc->pdev->subप्रणाली_device);
			अवरोध;
		पूर्ण
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * _base_display_fwpkg_version - sends FWUpload request to pull FWPkg
 *				version from FW Image Header.
 * @ioc: per adapter object
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
	अटल पूर्णांक
_base_display_fwpkg_version(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	Mpi2FWImageHeader_t *fw_img_hdr;
	Mpi26ComponentImageHeader_t *cmp_img_hdr;
	Mpi25FWUploadRequest_t *mpi_request;
	Mpi2FWUploadReply_t mpi_reply;
	पूर्णांक r = 0;
	u32  package_version = 0;
	व्योम *fwpkg_data = शून्य;
	dma_addr_t fwpkg_data_dma;
	u16 smid, ioc_status;
	माप_प्रकार data_length;

	dinitprपूर्णांकk(ioc, ioc_info(ioc, "%s\n", __func__));

	अगर (ioc->base_cmds.status & MPT3_CMD_PENDING) अणु
		ioc_err(ioc, "%s: internal command already in use\n", __func__);
		वापस -EAGAIN;
	पूर्ण

	data_length = माप(Mpi2FWImageHeader_t);
	fwpkg_data = dma_alloc_coherent(&ioc->pdev->dev, data_length,
			&fwpkg_data_dma, GFP_KERNEL);
	अगर (!fwpkg_data) अणु
		ioc_err(ioc,
		    "Memory allocation for fwpkg data failed at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस -ENOMEM;
	पूर्ण

	smid = mpt3sas_base_get_smid(ioc, ioc->base_cb_idx);
	अगर (!smid) अणु
		ioc_err(ioc, "%s: failed obtaining a smid\n", __func__);
		r = -EAGAIN;
		जाओ out;
	पूर्ण

	ioc->base_cmds.status = MPT3_CMD_PENDING;
	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	ioc->base_cmds.smid = smid;
	स_रखो(mpi_request, 0, माप(Mpi25FWUploadRequest_t));
	mpi_request->Function = MPI2_FUNCTION_FW_UPLOAD;
	mpi_request->ImageType = MPI2_FW_UPLOAD_ITYPE_FW_FLASH;
	mpi_request->ImageSize = cpu_to_le32(data_length);
	ioc->build_sg(ioc, &mpi_request->SGL, 0, 0, fwpkg_data_dma,
			data_length);
	init_completion(&ioc->base_cmds.करोne);
	ioc->put_smid_शेष(ioc, smid);
	/* Wait क्रम 15 seconds */
	रुको_क्रम_completion_समयout(&ioc->base_cmds.करोne,
			FW_IMG_HDR_READ_TIMEOUT*HZ);
	ioc_info(ioc, "%s: complete\n", __func__);
	अगर (!(ioc->base_cmds.status & MPT3_CMD_COMPLETE)) अणु
		ioc_err(ioc, "%s: timeout\n", __func__);
		_debug_dump_mf(mpi_request,
				माप(Mpi25FWUploadRequest_t)/4);
		r = -ETIME;
	पूर्ण अन्यथा अणु
		स_रखो(&mpi_reply, 0, माप(Mpi2FWUploadReply_t));
		अगर (ioc->base_cmds.status & MPT3_CMD_REPLY_VALID) अणु
			स_नकल(&mpi_reply, ioc->base_cmds.reply,
					माप(Mpi2FWUploadReply_t));
			ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
						MPI2_IOCSTATUS_MASK;
			अगर (ioc_status == MPI2_IOCSTATUS_SUCCESS) अणु
				fw_img_hdr = (Mpi2FWImageHeader_t *)fwpkg_data;
				अगर (le32_to_cpu(fw_img_hdr->Signature) ==
				    MPI26_IMAGE_HEADER_SIGNATURE0_MPI26) अणु
					cmp_img_hdr =
					    (Mpi26ComponentImageHeader_t *)
					    (fwpkg_data);
					package_version =
					    le32_to_cpu(
					    cmp_img_hdr->ApplicationSpecअगरic);
				पूर्ण अन्यथा
					package_version =
					    le32_to_cpu(
					    fw_img_hdr->PackageVersion.Word);
				अगर (package_version)
					ioc_info(ioc,
					"FW Package Ver(%02d.%02d.%02d.%02d)\n",
					((package_version) & 0xFF000000) >> 24,
					((package_version) & 0x00FF0000) >> 16,
					((package_version) & 0x0000FF00) >> 8,
					(package_version) & 0x000000FF);
			पूर्ण अन्यथा अणु
				_debug_dump_mf(&mpi_reply,
						माप(Mpi2FWUploadReply_t)/4);
			पूर्ण
		पूर्ण
	पूर्ण
	ioc->base_cmds.status = MPT3_CMD_NOT_USED;
out:
	अगर (fwpkg_data)
		dma_मुक्त_coherent(&ioc->pdev->dev, data_length, fwpkg_data,
				fwpkg_data_dma);
	वापस r;
पूर्ण

/**
 * _base_display_ioc_capabilities - Disply IOC's capabilities.
 * @ioc: per adapter object
 */
अटल व्योम
_base_display_ioc_capabilities(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	पूर्णांक i = 0;
	अक्षर desc[16];
	u32 iounit_pg1_flags;
	u32 bios_version;

	bios_version = le32_to_cpu(ioc->bios_pg3.BiosVersion);
	म_नकलन(desc, ioc->manu_pg0.ChipName, 16);
	ioc_info(ioc, "%s: FWVersion(%02d.%02d.%02d.%02d), ChipRevision(0x%02x), BiosVersion(%02d.%02d.%02d.%02d)\n",
		 desc,
		 (ioc->facts.FWVersion.Word & 0xFF000000) >> 24,
		 (ioc->facts.FWVersion.Word & 0x00FF0000) >> 16,
		 (ioc->facts.FWVersion.Word & 0x0000FF00) >> 8,
		 ioc->facts.FWVersion.Word & 0x000000FF,
		 ioc->pdev->revision,
		 (bios_version & 0xFF000000) >> 24,
		 (bios_version & 0x00FF0000) >> 16,
		 (bios_version & 0x0000FF00) >> 8,
		 bios_version & 0x000000FF);

	_base_display_OEMs_bअक्रमing(ioc);

	अगर (ioc->facts.ProtocolFlags & MPI2_IOCFACTS_PROTOCOL_NVME_DEVICES) अणु
		pr_info("%sNVMe", i ? "," : "");
		i++;
	पूर्ण

	ioc_info(ioc, "Protocol=(");

	अगर (ioc->facts.ProtocolFlags & MPI2_IOCFACTS_PROTOCOL_SCSI_INITIATOR) अणु
		pr_cont("Initiator");
		i++;
	पूर्ण

	अगर (ioc->facts.ProtocolFlags & MPI2_IOCFACTS_PROTOCOL_SCSI_TARGET) अणु
		pr_cont("%sTarget", i ? "," : "");
		i++;
	पूर्ण

	i = 0;
	pr_cont("), Capabilities=(");

	अगर (!ioc->hide_ir_msg) अणु
		अगर (ioc->facts.IOCCapabilities &
		    MPI2_IOCFACTS_CAPABILITY_INTEGRATED_RAID) अणु
			pr_cont("Raid");
			i++;
		पूर्ण
	पूर्ण

	अगर (ioc->facts.IOCCapabilities & MPI2_IOCFACTS_CAPABILITY_TLR) अणु
		pr_cont("%sTLR", i ? "," : "");
		i++;
	पूर्ण

	अगर (ioc->facts.IOCCapabilities & MPI2_IOCFACTS_CAPABILITY_MULTICAST) अणु
		pr_cont("%sMulticast", i ? "," : "");
		i++;
	पूर्ण

	अगर (ioc->facts.IOCCapabilities &
	    MPI2_IOCFACTS_CAPABILITY_BIसूचीECTIONAL_TARGET) अणु
		pr_cont("%sBIDI Target", i ? "," : "");
		i++;
	पूर्ण

	अगर (ioc->facts.IOCCapabilities & MPI2_IOCFACTS_CAPABILITY_EEDP) अणु
		pr_cont("%sEEDP", i ? "," : "");
		i++;
	पूर्ण

	अगर (ioc->facts.IOCCapabilities &
	    MPI2_IOCFACTS_CAPABILITY_SNAPSHOT_BUFFER) अणु
		pr_cont("%sSnapshot Buffer", i ? "," : "");
		i++;
	पूर्ण

	अगर (ioc->facts.IOCCapabilities &
	    MPI2_IOCFACTS_CAPABILITY_DIAG_TRACE_BUFFER) अणु
		pr_cont("%sDiag Trace Buffer", i ? "," : "");
		i++;
	पूर्ण

	अगर (ioc->facts.IOCCapabilities &
	    MPI2_IOCFACTS_CAPABILITY_EXTENDED_BUFFER) अणु
		pr_cont("%sDiag Extended Buffer", i ? "," : "");
		i++;
	पूर्ण

	अगर (ioc->facts.IOCCapabilities &
	    MPI2_IOCFACTS_CAPABILITY_TASK_SET_FULL_HANDLING) अणु
		pr_cont("%sTask Set Full", i ? "," : "");
		i++;
	पूर्ण

	iounit_pg1_flags = le32_to_cpu(ioc->iounit_pg1.Flags);
	अगर (!(iounit_pg1_flags & MPI2_IOUNITPAGE1_NATIVE_COMMAND_Q_DISABLE)) अणु
		pr_cont("%sNCQ", i ? "," : "");
		i++;
	पूर्ण

	pr_cont(")\n");
पूर्ण

/**
 * mpt3sas_base_update_missing_delay - change the missing delay समयrs
 * @ioc: per adapter object
 * @device_missing_delay: amount of समय till device is reported missing
 * @io_missing_delay: पूर्णांकerval IO is वापसed when there is a missing device
 *
 * Passed on the command line, this function will modअगरy the device missing
 * delay, as well as the io missing delay. This should be called at driver
 * load समय.
 */
व्योम
mpt3sas_base_update_missing_delay(काष्ठा MPT3SAS_ADAPTER *ioc,
	u16 device_missing_delay, u8 io_missing_delay)
अणु
	u16 dmd, dmd_new, dmd_orignal;
	u8 io_missing_delay_original;
	u16 sz;
	Mpi2SasIOUnitPage1_t *sas_iounit_pg1 = शून्य;
	Mpi2ConfigReply_t mpi_reply;
	u8 num_phys = 0;
	u16 ioc_status;

	mpt3sas_config_get_number_hba_phys(ioc, &num_phys);
	अगर (!num_phys)
		वापस;

	sz = दुरत्व(Mpi2SasIOUnitPage1_t, PhyData) + (num_phys *
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

	/* device missing delay */
	dmd = sas_iounit_pg1->ReportDeviceMissingDelay;
	अगर (dmd & MPI2_SASIOUNIT1_REPORT_MISSING_UNIT_16)
		dmd = (dmd & MPI2_SASIOUNIT1_REPORT_MISSING_TIMEOUT_MASK) * 16;
	अन्यथा
		dmd = dmd & MPI2_SASIOUNIT1_REPORT_MISSING_TIMEOUT_MASK;
	dmd_orignal = dmd;
	अगर (device_missing_delay > 0x7F) अणु
		dmd = (device_missing_delay > 0x7F0) ? 0x7F0 :
		    device_missing_delay;
		dmd = dmd / 16;
		dmd |= MPI2_SASIOUNIT1_REPORT_MISSING_UNIT_16;
	पूर्ण अन्यथा
		dmd = device_missing_delay;
	sas_iounit_pg1->ReportDeviceMissingDelay = dmd;

	/* io missing delay */
	io_missing_delay_original = sas_iounit_pg1->IODeviceMissingDelay;
	sas_iounit_pg1->IODeviceMissingDelay = io_missing_delay;

	अगर (!mpt3sas_config_set_sas_iounit_pg1(ioc, &mpi_reply, sas_iounit_pg1,
	    sz)) अणु
		अगर (dmd & MPI2_SASIOUNIT1_REPORT_MISSING_UNIT_16)
			dmd_new = (dmd &
			    MPI2_SASIOUNIT1_REPORT_MISSING_TIMEOUT_MASK) * 16;
		अन्यथा
			dmd_new =
		    dmd & MPI2_SASIOUNIT1_REPORT_MISSING_TIMEOUT_MASK;
		ioc_info(ioc, "device_missing_delay: old(%d), new(%d)\n",
			 dmd_orignal, dmd_new);
		ioc_info(ioc, "ioc_missing_delay: old(%d), new(%d)\n",
			 io_missing_delay_original,
			 io_missing_delay);
		ioc->device_missing_delay = dmd_new;
		ioc->io_missing_delay = io_missing_delay;
	पूर्ण

out:
	kमुक्त(sas_iounit_pg1);
पूर्ण

/**
 * _base_update_ioc_page1_अंतरभूतwith_perf_mode - Update IOC Page1 fields
 *    according to perक्रमmance mode.
 * @ioc : per adapter object
 *
 * Return nothing.
 */
अटल व्योम
_base_update_ioc_page1_अंतरभूतwith_perf_mode(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	Mpi2IOCPage1_t ioc_pg1;
	Mpi2ConfigReply_t mpi_reply;

	mpt3sas_config_get_ioc_pg1(ioc, &mpi_reply, &ioc->ioc_pg1_copy);
	स_नकल(&ioc_pg1, &ioc->ioc_pg1_copy, माप(Mpi2IOCPage1_t));

	चयन (perf_mode) अणु
	हाल MPT_PERF_MODE_DEFAULT:
	हाल MPT_PERF_MODE_BALANCED:
		अगर (ioc->high_iops_queues) अणु
			ioc_info(ioc,
				"Enable interrupt coalescing only for first\t"
				"%d reply queues\n",
				MPT3SAS_HIGH_IOPS_REPLY_QUEUES);
			/*
			 * If 31st bit is zero then पूर्णांकerrupt coalescing is
			 * enabled क्रम all reply descriptor post queues.
			 * If 31st bit is set to one then user can
			 * enable/disable पूर्णांकerrupt coalescing on per reply
			 * descriptor post queue group(8) basis. So to enable
			 * पूर्णांकerrupt coalescing only on first reply descriptor
			 * post queue group 31st bit and zero th bit is enabled.
			 */
			ioc_pg1.ProductSpecअगरic = cpu_to_le32(0x80000000 |
			    ((1 << MPT3SAS_HIGH_IOPS_REPLY_QUEUES/8) - 1));
			mpt3sas_config_set_ioc_pg1(ioc, &mpi_reply, &ioc_pg1);
			ioc_info(ioc, "performance mode: balanced\n");
			वापस;
		पूर्ण
		fallthrough;
	हाल MPT_PERF_MODE_LATENCY:
		/*
		 * Enable पूर्णांकerrupt coalescing on all reply queues
		 * with समयout value 0xA
		 */
		ioc_pg1.CoalescingTimeout = cpu_to_le32(0xa);
		ioc_pg1.Flags |= cpu_to_le32(MPI2_IOCPAGE1_REPLY_COALESCING);
		ioc_pg1.ProductSpecअगरic = 0;
		mpt3sas_config_set_ioc_pg1(ioc, &mpi_reply, &ioc_pg1);
		ioc_info(ioc, "performance mode: latency\n");
		अवरोध;
	हाल MPT_PERF_MODE_IOPS:
		/*
		 * Enable पूर्णांकerrupt coalescing on all reply queues.
		 */
		ioc_info(ioc,
		    "performance mode: iops with coalescing timeout: 0x%x\n",
		    le32_to_cpu(ioc_pg1.CoalescingTimeout));
		ioc_pg1.Flags |= cpu_to_le32(MPI2_IOCPAGE1_REPLY_COALESCING);
		ioc_pg1.ProductSpecअगरic = 0;
		mpt3sas_config_set_ioc_pg1(ioc, &mpi_reply, &ioc_pg1);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * _base_get_event_diag_triggers - get event diag trigger values from
 *				persistent pages
 * @ioc : per adapter object
 *
 * Return nothing.
 */
अटल व्योम
_base_get_event_diag_triggers(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	Mpi26DriverTriggerPage2_t trigger_pg2;
	काष्ठा SL_WH_EVENT_TRIGGER_T *event_tg;
	MPI26_DRIVER_MPI_EVENT_TIGGER_ENTRY *mpi_event_tg;
	Mpi2ConfigReply_t mpi_reply;
	पूर्णांक r = 0, i = 0;
	u16 count = 0;
	u16 ioc_status;

	r = mpt3sas_config_get_driver_trigger_pg2(ioc, &mpi_reply,
	    &trigger_pg2);
	अगर (r)
		वापस;

	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		dinitprपूर्णांकk(ioc,
		    ioc_err(ioc,
		    "%s: Failed to get trigger pg2, ioc_status(0x%04x)\n",
		   __func__, ioc_status));
		वापस;
	पूर्ण

	अगर (le16_to_cpu(trigger_pg2.NumMPIEventTrigger)) अणु
		count = le16_to_cpu(trigger_pg2.NumMPIEventTrigger);
		count = min_t(u16, NUM_VALID_ENTRIES, count);
		ioc->diag_trigger_event.ValidEntries = count;

		event_tg = &ioc->diag_trigger_event.EventTriggerEntry[0];
		mpi_event_tg = &trigger_pg2.MPIEventTriggers[0];
		क्रम (i = 0; i < count; i++) अणु
			event_tg->EventValue = le16_to_cpu(
			    mpi_event_tg->MPIEventCode);
			event_tg->LogEntryQualअगरier = le16_to_cpu(
			    mpi_event_tg->MPIEventCodeSpecअगरic);
			event_tg++;
			mpi_event_tg++;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * _base_get_scsi_diag_triggers - get scsi diag trigger values from
 *				persistent pages
 * @ioc : per adapter object
 *
 * Return nothing.
 */
अटल व्योम
_base_get_scsi_diag_triggers(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	Mpi26DriverTriggerPage3_t trigger_pg3;
	काष्ठा SL_WH_SCSI_TRIGGER_T *scsi_tg;
	MPI26_DRIVER_SCSI_SENSE_TIGGER_ENTRY *mpi_scsi_tg;
	Mpi2ConfigReply_t mpi_reply;
	पूर्णांक r = 0, i = 0;
	u16 count = 0;
	u16 ioc_status;

	r = mpt3sas_config_get_driver_trigger_pg3(ioc, &mpi_reply,
	    &trigger_pg3);
	अगर (r)
		वापस;

	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		dinitprपूर्णांकk(ioc,
		    ioc_err(ioc,
		    "%s: Failed to get trigger pg3, ioc_status(0x%04x)\n",
		    __func__, ioc_status));
		वापस;
	पूर्ण

	अगर (le16_to_cpu(trigger_pg3.NumSCSISenseTrigger)) अणु
		count = le16_to_cpu(trigger_pg3.NumSCSISenseTrigger);
		count = min_t(u16, NUM_VALID_ENTRIES, count);
		ioc->diag_trigger_scsi.ValidEntries = count;

		scsi_tg = &ioc->diag_trigger_scsi.SCSITriggerEntry[0];
		mpi_scsi_tg = &trigger_pg3.SCSISenseTriggers[0];
		क्रम (i = 0; i < count; i++) अणु
			scsi_tg->ASCQ = mpi_scsi_tg->ASCQ;
			scsi_tg->ASC = mpi_scsi_tg->ASC;
			scsi_tg->SenseKey = mpi_scsi_tg->SenseKey;

			scsi_tg++;
			mpi_scsi_tg++;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * _base_get_mpi_diag_triggers - get mpi diag trigger values from
 *				persistent pages
 * @ioc : per adapter object
 *
 * Return nothing.
 */
अटल व्योम
_base_get_mpi_diag_triggers(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	Mpi26DriverTriggerPage4_t trigger_pg4;
	काष्ठा SL_WH_MPI_TRIGGER_T *status_tg;
	MPI26_DRIVER_IOCSTATUS_LOGINFO_TIGGER_ENTRY *mpi_status_tg;
	Mpi2ConfigReply_t mpi_reply;
	पूर्णांक r = 0, i = 0;
	u16 count = 0;
	u16 ioc_status;

	r = mpt3sas_config_get_driver_trigger_pg4(ioc, &mpi_reply,
	    &trigger_pg4);
	अगर (r)
		वापस;

	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		dinitprपूर्णांकk(ioc,
		    ioc_err(ioc,
		    "%s: Failed to get trigger pg4, ioc_status(0x%04x)\n",
		    __func__, ioc_status));
		वापस;
	पूर्ण

	अगर (le16_to_cpu(trigger_pg4.NumIOCStatusLogInfoTrigger)) अणु
		count = le16_to_cpu(trigger_pg4.NumIOCStatusLogInfoTrigger);
		count = min_t(u16, NUM_VALID_ENTRIES, count);
		ioc->diag_trigger_mpi.ValidEntries = count;

		status_tg = &ioc->diag_trigger_mpi.MPITriggerEntry[0];
		mpi_status_tg = &trigger_pg4.IOCStatusLoginfoTriggers[0];

		क्रम (i = 0; i < count; i++) अणु
			status_tg->IOCStatus = le16_to_cpu(
			    mpi_status_tg->IOCStatus);
			status_tg->IocLogInfo = le32_to_cpu(
			    mpi_status_tg->LogInfo);

			status_tg++;
			mpi_status_tg++;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * _base_get_master_diag_triggers - get master diag trigger values from
 *				persistent pages
 * @ioc : per adapter object
 *
 * Return nothing.
 */
अटल व्योम
_base_get_master_diag_triggers(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	Mpi26DriverTriggerPage1_t trigger_pg1;
	Mpi2ConfigReply_t mpi_reply;
	पूर्णांक r;
	u16 ioc_status;

	r = mpt3sas_config_get_driver_trigger_pg1(ioc, &mpi_reply,
	    &trigger_pg1);
	अगर (r)
		वापस;

	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		dinitprपूर्णांकk(ioc,
		    ioc_err(ioc,
		    "%s: Failed to get trigger pg1, ioc_status(0x%04x)\n",
		   __func__, ioc_status));
		वापस;
	पूर्ण

	अगर (le16_to_cpu(trigger_pg1.NumMasterTrigger))
		ioc->diag_trigger_master.MasterData |=
		    le32_to_cpu(
		    trigger_pg1.MasterTriggers[0].MasterTriggerFlags);
पूर्ण

/**
 * _base_check_क्रम_trigger_pages_support - checks whether HBA FW supports
 *					driver trigger pages or not
 * @ioc : per adapter object
 *
 * Returns trigger flags mask अगर HBA FW supports driver trigger pages,
 * otherwise वापसs EFAULT.
 */
अटल पूर्णांक
_base_check_क्रम_trigger_pages_support(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	Mpi26DriverTriggerPage0_t trigger_pg0;
	पूर्णांक r = 0;
	Mpi2ConfigReply_t mpi_reply;
	u16 ioc_status;

	r = mpt3sas_config_get_driver_trigger_pg0(ioc, &mpi_reply,
	    &trigger_pg0);
	अगर (r)
		वापस -EFAULT;

	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS)
		वापस -EFAULT;

	वापस le16_to_cpu(trigger_pg0.TriggerFlags);
पूर्ण

/**
 * _base_get_diag_triggers - Retrieve diag trigger values from
 *				persistent pages.
 * @ioc : per adapter object
 *
 * Return nothing.
 */
अटल व्योम
_base_get_diag_triggers(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	पूर्णांक trigger_flags;

	/*
	 * Default setting of master trigger.
	 */
	ioc->diag_trigger_master.MasterData =
	    (MASTER_TRIGGER_FW_FAULT + MASTER_TRIGGER_ADAPTER_RESET);

	trigger_flags = _base_check_क्रम_trigger_pages_support(ioc);
	अगर (trigger_flags < 0)
		वापस;

	ioc->supports_trigger_pages = 1;

	/*
	 * Retrieve master diag trigger values from driver trigger pg1
	 * अगर master trigger bit enabled in TriggerFlags.
	 */
	अगर ((u16)trigger_flags &
	    MPI26_DRIVER_TRIGGER0_FLAG_MASTER_TRIGGER_VALID)
		_base_get_master_diag_triggers(ioc);

	/*
	 * Retrieve event diag trigger values from driver trigger pg2
	 * अगर event trigger bit enabled in TriggerFlags.
	 */
	अगर ((u16)trigger_flags &
	    MPI26_DRIVER_TRIGGER0_FLAG_MPI_EVENT_TRIGGER_VALID)
		_base_get_event_diag_triggers(ioc);

	/*
	 * Retrieve scsi diag trigger values from driver trigger pg3
	 * अगर scsi trigger bit enabled in TriggerFlags.
	 */
	अगर ((u16)trigger_flags &
	    MPI26_DRIVER_TRIGGER0_FLAG_SCSI_SENSE_TRIGGER_VALID)
		_base_get_scsi_diag_triggers(ioc);
	/*
	 * Retrieve mpi error diag trigger values from driver trigger pg4
	 * अगर loginfo trigger bit enabled in TriggerFlags.
	 */
	अगर ((u16)trigger_flags &
	    MPI26_DRIVER_TRIGGER0_FLAG_LOGINFO_TRIGGER_VALID)
		_base_get_mpi_diag_triggers(ioc);
पूर्ण

/**
 * _base_update_diag_trigger_pages - Update the driver trigger pages after
 *			online FW update, inहाल updated FW supports driver
 *			trigger pages.
 * @ioc : per adapter object
 *
 * Return nothing.
 */
अटल व्योम
_base_update_diag_trigger_pages(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु

	अगर (ioc->diag_trigger_master.MasterData)
		mpt3sas_config_update_driver_trigger_pg1(ioc,
		    &ioc->diag_trigger_master, 1);

	अगर (ioc->diag_trigger_event.ValidEntries)
		mpt3sas_config_update_driver_trigger_pg2(ioc,
		    &ioc->diag_trigger_event, 1);

	अगर (ioc->diag_trigger_scsi.ValidEntries)
		mpt3sas_config_update_driver_trigger_pg3(ioc,
		    &ioc->diag_trigger_scsi, 1);

	अगर (ioc->diag_trigger_mpi.ValidEntries)
		mpt3sas_config_update_driver_trigger_pg4(ioc,
		    &ioc->diag_trigger_mpi, 1);
पूर्ण

/**
 * _base_अटल_config_pages - अटल start of day config pages
 * @ioc: per adapter object
 */
अटल व्योम
_base_अटल_config_pages(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	Mpi2ConfigReply_t mpi_reply;
	u32 iounit_pg1_flags;
	पूर्णांक tg_flags = 0;
	ioc->nvme_पात_समयout = 30;
	mpt3sas_config_get_manufacturing_pg0(ioc, &mpi_reply, &ioc->manu_pg0);
	अगर (ioc->ir_firmware)
		mpt3sas_config_get_manufacturing_pg10(ioc, &mpi_reply,
		    &ioc->manu_pg10);

	/*
	 * Ensure correct T10 PI operation अगर venकरोr left EEDPTagMode
	 * flag unset in NVDATA.
	 */
	mpt3sas_config_get_manufacturing_pg11(ioc, &mpi_reply, &ioc->manu_pg11);
	अगर (!ioc->is_gen35_ioc && ioc->manu_pg11.EEDPTagMode == 0) अणु
		pr_err("%s: overriding NVDATA EEDPTagMode setting\n",
		    ioc->name);
		ioc->manu_pg11.EEDPTagMode &= ~0x3;
		ioc->manu_pg11.EEDPTagMode |= 0x1;
		mpt3sas_config_set_manufacturing_pg11(ioc, &mpi_reply,
		    &ioc->manu_pg11);
	पूर्ण
	अगर (ioc->manu_pg11.AddlFlags2 & NVME_TASK_MNGT_CUSTOM_MASK)
		ioc->पंचांग_custom_handling = 1;
	अन्यथा अणु
		ioc->पंचांग_custom_handling = 0;
		अगर (ioc->manu_pg11.NVMeAbortTO < NVME_TASK_ABORT_MIN_TIMEOUT)
			ioc->nvme_पात_समयout = NVME_TASK_ABORT_MIN_TIMEOUT;
		अन्यथा अगर (ioc->manu_pg11.NVMeAbortTO >
					NVME_TASK_ABORT_MAX_TIMEOUT)
			ioc->nvme_पात_समयout = NVME_TASK_ABORT_MAX_TIMEOUT;
		अन्यथा
			ioc->nvme_पात_समयout = ioc->manu_pg11.NVMeAbortTO;
	पूर्ण
	ioc->समय_sync_पूर्णांकerval =
	    ioc->manu_pg11.TimeSyncInterval & MPT3SAS_TIMESYNC_MASK;
	अगर (ioc->समय_sync_पूर्णांकerval) अणु
		अगर (ioc->manu_pg11.TimeSyncInterval & MPT3SAS_TIMESYNC_UNIT_MASK)
			ioc->समय_sync_पूर्णांकerval =
			    ioc->समय_sync_पूर्णांकerval * SECONDS_PER_HOUR;
		अन्यथा
			ioc->समय_sync_पूर्णांकerval =
			    ioc->समय_sync_पूर्णांकerval * SECONDS_PER_MIN;
		dinitprपूर्णांकk(ioc, ioc_info(ioc,
		    "Driver-FW TimeSync interval is %d seconds. ManuPg11 TimeSync Unit is in %s\n",
		    ioc->समय_sync_पूर्णांकerval, (ioc->manu_pg11.TimeSyncInterval &
		    MPT3SAS_TIMESYNC_UNIT_MASK) ? "Hour" : "Minute"));
	पूर्ण अन्यथा अणु
		अगर (ioc->is_gen35_ioc)
			ioc_warn(ioc,
			    "TimeSync Interval in Manuf page-11 is not enabled. Periodic Time-Sync will be disabled\n");
	पूर्ण
	mpt3sas_config_get_bios_pg2(ioc, &mpi_reply, &ioc->bios_pg2);
	mpt3sas_config_get_bios_pg3(ioc, &mpi_reply, &ioc->bios_pg3);
	mpt3sas_config_get_ioc_pg8(ioc, &mpi_reply, &ioc->ioc_pg8);
	mpt3sas_config_get_iounit_pg0(ioc, &mpi_reply, &ioc->iounit_pg0);
	mpt3sas_config_get_iounit_pg1(ioc, &mpi_reply, &ioc->iounit_pg1);
	mpt3sas_config_get_iounit_pg8(ioc, &mpi_reply, &ioc->iounit_pg8);
	_base_display_ioc_capabilities(ioc);

	/*
	 * Enable task_set_full handling in iounit_pg1 when the
	 * facts capabilities indicate that its supported.
	 */
	iounit_pg1_flags = le32_to_cpu(ioc->iounit_pg1.Flags);
	अगर ((ioc->facts.IOCCapabilities &
	    MPI2_IOCFACTS_CAPABILITY_TASK_SET_FULL_HANDLING))
		iounit_pg1_flags &=
		    ~MPI2_IOUNITPAGE1_DISABLE_TASK_SET_FULL_HANDLING;
	अन्यथा
		iounit_pg1_flags |=
		    MPI2_IOUNITPAGE1_DISABLE_TASK_SET_FULL_HANDLING;
	ioc->iounit_pg1.Flags = cpu_to_le32(iounit_pg1_flags);
	mpt3sas_config_set_iounit_pg1(ioc, &mpi_reply, &ioc->iounit_pg1);

	अगर (ioc->iounit_pg8.NumSensors)
		ioc->temp_sensors_count = ioc->iounit_pg8.NumSensors;
	अगर (ioc->is_aero_ioc)
		_base_update_ioc_page1_अंतरभूतwith_perf_mode(ioc);
	अगर (ioc->is_gen35_ioc) अणु
		अगर (ioc->is_driver_loading)
			_base_get_diag_triggers(ioc);
		अन्यथा अणु
			/*
			 * In हाल of online HBA FW update operation,
			 * check whether updated FW supports the driver trigger
			 * pages or not.
			 * - If previous FW has not supported driver trigger
			 *   pages and newer FW supports them then update these
			 *   pages with current diag trigger values.
			 * - If previous FW has supported driver trigger pages
			 *   and new FW करोesn't support them then disable
			 *   support_trigger_pages flag.
			 */
			tg_flags = _base_check_क्रम_trigger_pages_support(ioc);
			अगर (!ioc->supports_trigger_pages && tg_flags != -EFAULT)
				_base_update_diag_trigger_pages(ioc);
			अन्यथा अगर (ioc->supports_trigger_pages &&
			    tg_flags == -EFAULT)
				ioc->supports_trigger_pages = 0;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * mpt3sas_मुक्त_enclosure_list - release memory
 * @ioc: per adapter object
 *
 * Free memory allocated during enclosure add.
 */
व्योम
mpt3sas_मुक्त_enclosure_list(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	काष्ठा _enclosure_node *enclosure_dev, *enclosure_dev_next;

	/* Free enclosure list */
	list_क्रम_each_entry_safe(enclosure_dev,
			enclosure_dev_next, &ioc->enclosure_list, list) अणु
		list_del(&enclosure_dev->list);
		kमुक्त(enclosure_dev);
	पूर्ण
पूर्ण

/**
 * _base_release_memory_pools - release memory
 * @ioc: per adapter object
 *
 * Free memory allocated from _base_allocate_memory_pools.
 */
अटल व्योम
_base_release_memory_pools(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	पूर्णांक i = 0;
	पूर्णांक j = 0;
	पूर्णांक dma_alloc_count = 0;
	काष्ठा chain_tracker *ct;
	पूर्णांक count = ioc->rdpq_array_enable ? ioc->reply_queue_count : 1;

	dनिकासprपूर्णांकk(ioc, ioc_info(ioc, "%s\n", __func__));

	अगर (ioc->request) अणु
		dma_मुक्त_coherent(&ioc->pdev->dev, ioc->request_dma_sz,
		    ioc->request,  ioc->request_dma);
		dनिकासprपूर्णांकk(ioc,
			    ioc_info(ioc, "request_pool(0x%p): free\n",
				     ioc->request));
		ioc->request = शून्य;
	पूर्ण

	अगर (ioc->sense) अणु
		dma_pool_मुक्त(ioc->sense_dma_pool, ioc->sense, ioc->sense_dma);
		dma_pool_destroy(ioc->sense_dma_pool);
		dनिकासprपूर्णांकk(ioc,
			    ioc_info(ioc, "sense_pool(0x%p): free\n",
				     ioc->sense));
		ioc->sense = शून्य;
	पूर्ण

	अगर (ioc->reply) अणु
		dma_pool_मुक्त(ioc->reply_dma_pool, ioc->reply, ioc->reply_dma);
		dma_pool_destroy(ioc->reply_dma_pool);
		dनिकासprपूर्णांकk(ioc,
			    ioc_info(ioc, "reply_pool(0x%p): free\n",
				     ioc->reply));
		ioc->reply = शून्य;
	पूर्ण

	अगर (ioc->reply_मुक्त) अणु
		dma_pool_मुक्त(ioc->reply_मुक्त_dma_pool, ioc->reply_मुक्त,
		    ioc->reply_मुक्त_dma);
		dma_pool_destroy(ioc->reply_मुक्त_dma_pool);
		dनिकासprपूर्णांकk(ioc,
			    ioc_info(ioc, "reply_free_pool(0x%p): free\n",
				     ioc->reply_मुक्त));
		ioc->reply_मुक्त = शून्य;
	पूर्ण

	अगर (ioc->reply_post) अणु
		dma_alloc_count = DIV_ROUND_UP(count,
				RDPQ_MAX_INDEX_IN_ONE_CHUNK);
		क्रम (i = 0; i < count; i++) अणु
			अगर (i % RDPQ_MAX_INDEX_IN_ONE_CHUNK == 0
			    && dma_alloc_count) अणु
				अगर (ioc->reply_post[i].reply_post_मुक्त) अणु
					dma_pool_मुक्त(
					    ioc->reply_post_मुक्त_dma_pool,
					    ioc->reply_post[i].reply_post_मुक्त,
					ioc->reply_post[i].reply_post_मुक्त_dma);
					dनिकासprपूर्णांकk(ioc, ioc_info(ioc,
					   "reply_post_free_pool(0x%p): free\n",
					   ioc->reply_post[i].reply_post_मुक्त));
					ioc->reply_post[i].reply_post_मुक्त =
									शून्य;
				पूर्ण
				--dma_alloc_count;
			पूर्ण
		पूर्ण
		dma_pool_destroy(ioc->reply_post_मुक्त_dma_pool);
		अगर (ioc->reply_post_मुक्त_array &&
			ioc->rdpq_array_enable) अणु
			dma_pool_मुक्त(ioc->reply_post_मुक्त_array_dma_pool,
			    ioc->reply_post_मुक्त_array,
			    ioc->reply_post_मुक्त_array_dma);
			ioc->reply_post_मुक्त_array = शून्य;
		पूर्ण
		dma_pool_destroy(ioc->reply_post_मुक्त_array_dma_pool);
		kमुक्त(ioc->reply_post);
	पूर्ण

	अगर (ioc->pcie_sgl_dma_pool) अणु
		क्रम (i = 0; i < ioc->scsiio_depth; i++) अणु
			dma_pool_मुक्त(ioc->pcie_sgl_dma_pool,
					ioc->pcie_sg_lookup[i].pcie_sgl,
					ioc->pcie_sg_lookup[i].pcie_sgl_dma);
			ioc->pcie_sg_lookup[i].pcie_sgl = शून्य;
		पूर्ण
		dma_pool_destroy(ioc->pcie_sgl_dma_pool);
	पूर्ण
	अगर (ioc->config_page) अणु
		dनिकासprपूर्णांकk(ioc,
			    ioc_info(ioc, "config_page(0x%p): free\n",
				     ioc->config_page));
		dma_मुक्त_coherent(&ioc->pdev->dev, ioc->config_page_sz,
		    ioc->config_page, ioc->config_page_dma);
	पूर्ण

	kमुक्त(ioc->hpr_lookup);
	ioc->hpr_lookup = शून्य;
	kमुक्त(ioc->पूर्णांकernal_lookup);
	ioc->पूर्णांकernal_lookup = शून्य;
	अगर (ioc->chain_lookup) अणु
		क्रम (i = 0; i < ioc->scsiio_depth; i++) अणु
			क्रम (j = ioc->chains_per_prp_buffer;
			    j < ioc->chains_needed_per_io; j++) अणु
				ct = &ioc->chain_lookup[i].chains_per_smid[j];
				अगर (ct && ct->chain_buffer)
					dma_pool_मुक्त(ioc->chain_dma_pool,
						ct->chain_buffer,
						ct->chain_buffer_dma);
			पूर्ण
			kमुक्त(ioc->chain_lookup[i].chains_per_smid);
		पूर्ण
		dma_pool_destroy(ioc->chain_dma_pool);
		kमुक्त(ioc->chain_lookup);
		ioc->chain_lookup = शून्य;
	पूर्ण

	kमुक्त(ioc->io_queue_num);
	ioc->io_queue_num = शून्य;
पूर्ण

/**
 * mpt3sas_check_same_4gb_region - checks whether all reply queues in a set are
 *	having same upper 32bits in their base memory address.
 * @reply_pool_start_address: Base address of a reply queue set
 * @pool_sz: Size of single Reply Descriptor Post Queues pool size
 *
 * Return: 1 अगर reply queues in a set have a same upper 32bits in their base
 * memory address, अन्यथा 0.
 */

अटल पूर्णांक
mpt3sas_check_same_4gb_region(दीर्घ reply_pool_start_address, u32 pool_sz)
अणु
	दीर्घ reply_pool_end_address;

	reply_pool_end_address = reply_pool_start_address + pool_sz;

	अगर (upper_32_bits(reply_pool_start_address) ==
		upper_32_bits(reply_pool_end_address))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/**
 * _base_reduce_hba_queue_depth- Retry with reduced queue depth
 * @ioc: Adapter object
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 **/
अटल अंतरभूत पूर्णांक
_base_reduce_hba_queue_depth(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	पूर्णांक reduce_sz = 64;

	अगर ((ioc->hba_queue_depth - reduce_sz) >
	    (ioc->पूर्णांकernal_depth + INTERNAL_SCSIIO_CMDS_COUNT)) अणु
		ioc->hba_queue_depth -= reduce_sz;
		वापस 0;
	पूर्ण अन्यथा
		वापस -ENOMEM;
पूर्ण

/**
 * _base_allocate_pcie_sgl_pool - Allocating DMA'able memory
 *			क्रम pcie sgl pools.
 * @ioc: Adapter object
 * @sz: DMA Pool size
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */

अटल पूर्णांक
_base_allocate_pcie_sgl_pool(काष्ठा MPT3SAS_ADAPTER *ioc, u32 sz)
अणु
	पूर्णांक i = 0, j = 0;
	काष्ठा chain_tracker *ct;

	ioc->pcie_sgl_dma_pool =
	    dma_pool_create("PCIe SGL pool", &ioc->pdev->dev, sz,
	    ioc->page_size, 0);
	अगर (!ioc->pcie_sgl_dma_pool) अणु
		ioc_err(ioc, "PCIe SGL pool: dma_pool_create failed\n");
		वापस -ENOMEM;
	पूर्ण

	ioc->chains_per_prp_buffer = sz/ioc->chain_segment_sz;
	ioc->chains_per_prp_buffer =
	    min(ioc->chains_per_prp_buffer, ioc->chains_needed_per_io);
	क्रम (i = 0; i < ioc->scsiio_depth; i++) अणु
		ioc->pcie_sg_lookup[i].pcie_sgl =
		    dma_pool_alloc(ioc->pcie_sgl_dma_pool, GFP_KERNEL,
		    &ioc->pcie_sg_lookup[i].pcie_sgl_dma);
		अगर (!ioc->pcie_sg_lookup[i].pcie_sgl) अणु
			ioc_err(ioc, "PCIe SGL pool: dma_pool_alloc failed\n");
			वापस -EAGAIN;
		पूर्ण

		अगर (!mpt3sas_check_same_4gb_region(
		    (दीर्घ)ioc->pcie_sg_lookup[i].pcie_sgl, sz)) अणु
			ioc_err(ioc, "PCIE SGLs are not in same 4G !! pcie sgl (0x%p) dma = (0x%llx)\n",
			    ioc->pcie_sg_lookup[i].pcie_sgl,
			    (अचिन्हित दीर्घ दीर्घ)
			    ioc->pcie_sg_lookup[i].pcie_sgl_dma);
			ioc->use_32bit_dma = true;
			वापस -EAGAIN;
		पूर्ण

		क्रम (j = 0; j < ioc->chains_per_prp_buffer; j++) अणु
			ct = &ioc->chain_lookup[i].chains_per_smid[j];
			ct->chain_buffer =
			    ioc->pcie_sg_lookup[i].pcie_sgl +
			    (j * ioc->chain_segment_sz);
			ct->chain_buffer_dma =
			    ioc->pcie_sg_lookup[i].pcie_sgl_dma +
			    (j * ioc->chain_segment_sz);
		पूर्ण
	पूर्ण
	dinitprपूर्णांकk(ioc, ioc_info(ioc,
	    "PCIe sgl pool depth(%d), element_size(%d), pool_size(%d kB)\n",
	    ioc->scsiio_depth, sz, (sz * ioc->scsiio_depth)/1024));
	dinitprपूर्णांकk(ioc, ioc_info(ioc,
	    "Number of chains can fit in a PRP page(%d)\n",
	    ioc->chains_per_prp_buffer));
	वापस 0;
पूर्ण

/**
 * _base_allocate_chain_dma_pool - Allocating DMA'able memory
 *			क्रम chain dma pool.
 * @ioc: Adapter object
 * @sz: DMA Pool size
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_base_allocate_chain_dma_pool(काष्ठा MPT3SAS_ADAPTER *ioc, u32 sz)
अणु
	पूर्णांक i = 0, j = 0;
	काष्ठा chain_tracker *ctr;

	ioc->chain_dma_pool = dma_pool_create("chain pool", &ioc->pdev->dev,
	    ioc->chain_segment_sz, 16, 0);
	अगर (!ioc->chain_dma_pool)
		वापस -ENOMEM;

	क्रम (i = 0; i < ioc->scsiio_depth; i++) अणु
		क्रम (j = ioc->chains_per_prp_buffer;
		    j < ioc->chains_needed_per_io; j++) अणु
			ctr = &ioc->chain_lookup[i].chains_per_smid[j];
			ctr->chain_buffer = dma_pool_alloc(ioc->chain_dma_pool,
			    GFP_KERNEL, &ctr->chain_buffer_dma);
			अगर (!ctr->chain_buffer)
				वापस -EAGAIN;
			अगर (!mpt3sas_check_same_4gb_region((दीर्घ)
			    ctr->chain_buffer, ioc->chain_segment_sz)) अणु
				ioc_err(ioc,
				    "Chain buffers are not in same 4G !!! Chain buff (0x%p) dma = (0x%llx)\n",
				    ctr->chain_buffer,
				    (अचिन्हित दीर्घ दीर्घ)ctr->chain_buffer_dma);
				ioc->use_32bit_dma = true;
				वापस -EAGAIN;
			पूर्ण
		पूर्ण
	पूर्ण
	dinitprपूर्णांकk(ioc, ioc_info(ioc,
	    "chain_lookup depth (%d), frame_size(%d), pool_size(%d kB)\n",
	    ioc->scsiio_depth, ioc->chain_segment_sz, ((ioc->scsiio_depth *
	    (ioc->chains_needed_per_io - ioc->chains_per_prp_buffer) *
	    ioc->chain_segment_sz))/1024));
	वापस 0;
पूर्ण

/**
 * _base_allocate_sense_dma_pool - Allocating DMA'able memory
 *			क्रम sense dma pool.
 * @ioc: Adapter object
 * @sz: DMA Pool size
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_base_allocate_sense_dma_pool(काष्ठा MPT3SAS_ADAPTER *ioc, u32 sz)
अणु
	ioc->sense_dma_pool =
	    dma_pool_create("sense pool", &ioc->pdev->dev, sz, 4, 0);
	अगर (!ioc->sense_dma_pool)
		वापस -ENOMEM;
	ioc->sense = dma_pool_alloc(ioc->sense_dma_pool,
	    GFP_KERNEL, &ioc->sense_dma);
	अगर (!ioc->sense)
		वापस -EAGAIN;
	अगर (!mpt3sas_check_same_4gb_region((दीर्घ)ioc->sense, sz)) अणु
		dinitprपूर्णांकk(ioc, pr_err(
		    "Bad Sense Pool! sense (0x%p) sense_dma = (0x%llx)\n",
		    ioc->sense, (अचिन्हित दीर्घ दीर्घ) ioc->sense_dma));
		ioc->use_32bit_dma = true;
		वापस -EAGAIN;
	पूर्ण
	ioc_info(ioc,
	    "sense pool(0x%p) - dma(0x%llx): depth(%d), element_size(%d), pool_size (%d kB)\n",
	    ioc->sense, (अचिन्हित दीर्घ दीर्घ)ioc->sense_dma,
	    ioc->scsiio_depth, SCSI_SENSE_BUFFERSIZE, sz/1024);
	वापस 0;
पूर्ण

/**
 * _base_allocate_reply_pool - Allocating DMA'able memory
 *			क्रम reply pool.
 * @ioc: Adapter object
 * @sz: DMA Pool size
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_base_allocate_reply_pool(काष्ठा MPT3SAS_ADAPTER *ioc, u32 sz)
अणु
	/* reply pool, 4 byte align */
	ioc->reply_dma_pool = dma_pool_create("reply pool",
	    &ioc->pdev->dev, sz, 4, 0);
	अगर (!ioc->reply_dma_pool)
		वापस -ENOMEM;
	ioc->reply = dma_pool_alloc(ioc->reply_dma_pool, GFP_KERNEL,
	    &ioc->reply_dma);
	अगर (!ioc->reply)
		वापस -EAGAIN;
	अगर (!mpt3sas_check_same_4gb_region((दीर्घ)ioc->reply_मुक्त, sz)) अणु
		dinitprपूर्णांकk(ioc, pr_err(
		    "Bad Reply Pool! Reply (0x%p) Reply dma = (0x%llx)\n",
		    ioc->reply, (अचिन्हित दीर्घ दीर्घ) ioc->reply_dma));
		ioc->use_32bit_dma = true;
		वापस -EAGAIN;
	पूर्ण
	ioc->reply_dma_min_address = (u32)(ioc->reply_dma);
	ioc->reply_dma_max_address = (u32)(ioc->reply_dma) + sz;
	ioc_info(ioc,
	    "reply pool(0x%p) - dma(0x%llx): depth(%d), frame_size(%d), pool_size(%d kB)\n",
	    ioc->reply, (अचिन्हित दीर्घ दीर्घ)ioc->reply_dma,
	    ioc->reply_मुक्त_queue_depth, ioc->reply_sz, sz/1024);
	वापस 0;
पूर्ण

/**
 * _base_allocate_reply_मुक्त_dma_pool - Allocating DMA'able memory
 *			क्रम reply मुक्त dma pool.
 * @ioc: Adapter object
 * @sz: DMA Pool size
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_base_allocate_reply_मुक्त_dma_pool(काष्ठा MPT3SAS_ADAPTER *ioc, u32 sz)
अणु
	/* reply मुक्त queue, 16 byte align */
	ioc->reply_मुक्त_dma_pool = dma_pool_create(
	    "reply_free pool", &ioc->pdev->dev, sz, 16, 0);
	अगर (!ioc->reply_मुक्त_dma_pool)
		वापस -ENOMEM;
	ioc->reply_मुक्त = dma_pool_alloc(ioc->reply_मुक्त_dma_pool,
	    GFP_KERNEL, &ioc->reply_मुक्त_dma);
	अगर (!ioc->reply_मुक्त)
		वापस -EAGAIN;
	अगर (!mpt3sas_check_same_4gb_region((दीर्घ)ioc->reply_मुक्त, sz)) अणु
		dinitprपूर्णांकk(ioc,
		    pr_err("Bad Reply Free Pool! Reply Free (0x%p) Reply Free dma = (0x%llx)\n",
		    ioc->reply_मुक्त, (अचिन्हित दीर्घ दीर्घ) ioc->reply_मुक्त_dma));
		ioc->use_32bit_dma = true;
		वापस -EAGAIN;
	पूर्ण
	स_रखो(ioc->reply_मुक्त, 0, sz);
	dinitprपूर्णांकk(ioc, ioc_info(ioc,
	    "reply_free pool(0x%p): depth(%d), element_size(%d), pool_size(%d kB)\n",
	    ioc->reply_मुक्त, ioc->reply_मुक्त_queue_depth, 4, sz/1024));
	dinitprपूर्णांकk(ioc, ioc_info(ioc,
	    "reply_free_dma (0x%llx)\n",
	    (अचिन्हित दीर्घ दीर्घ)ioc->reply_मुक्त_dma));
	वापस 0;
पूर्ण

/**
 * _base_allocate_reply_post_मुक्त_array - Allocating DMA'able memory
 *			क्रम reply post मुक्त array.
 * @ioc: Adapter object
 * @reply_post_मुक्त_array_sz: DMA Pool size
 * Return: 0 क्रम success, non-zero क्रम failure.
 */

अटल पूर्णांक
_base_allocate_reply_post_मुक्त_array(काष्ठा MPT3SAS_ADAPTER *ioc,
	u32 reply_post_मुक्त_array_sz)
अणु
	ioc->reply_post_मुक्त_array_dma_pool =
	    dma_pool_create("reply_post_free_array pool",
	    &ioc->pdev->dev, reply_post_मुक्त_array_sz, 16, 0);
	अगर (!ioc->reply_post_मुक्त_array_dma_pool)
		वापस -ENOMEM;
	ioc->reply_post_मुक्त_array =
	    dma_pool_alloc(ioc->reply_post_मुक्त_array_dma_pool,
	    GFP_KERNEL, &ioc->reply_post_मुक्त_array_dma);
	अगर (!ioc->reply_post_मुक्त_array)
		वापस -EAGAIN;
	अगर (!mpt3sas_check_same_4gb_region((दीर्घ)ioc->reply_post_मुक्त_array,
	    reply_post_मुक्त_array_sz)) अणु
		dinitprपूर्णांकk(ioc, pr_err(
		    "Bad Reply Free Pool! Reply Free (0x%p) Reply Free dma = (0x%llx)\n",
		    ioc->reply_मुक्त,
		    (अचिन्हित दीर्घ दीर्घ) ioc->reply_मुक्त_dma));
		ioc->use_32bit_dma = true;
		वापस -EAGAIN;
	पूर्ण
	वापस 0;
पूर्ण
/**
 * base_alloc_rdpq_dma_pool - Allocating DMA'able memory
 *                     क्रम reply queues.
 * @ioc: per adapter object
 * @sz: DMA Pool size
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
base_alloc_rdpq_dma_pool(काष्ठा MPT3SAS_ADAPTER *ioc, पूर्णांक sz)
अणु
	पूर्णांक i = 0;
	u32 dma_alloc_count = 0;
	पूर्णांक reply_post_मुक्त_sz = ioc->reply_post_queue_depth *
		माप(Mpi2DefaultReplyDescriptor_t);
	पूर्णांक count = ioc->rdpq_array_enable ? ioc->reply_queue_count : 1;

	ioc->reply_post = kसुस्मृति(count, माप(काष्ठा reply_post_काष्ठा),
			GFP_KERNEL);
	अगर (!ioc->reply_post)
		वापस -ENOMEM;
	/*
	 *  For INVADER_SERIES each set of 8 reply queues(0-7, 8-15, ..) and
	 *  VENTURA_SERIES each set of 16 reply queues(0-15, 16-31, ..) should
	 *  be within 4GB boundary i.e reply queues in a set must have same
	 *  upper 32-bits in their memory address. so here driver is allocating
	 *  the DMA'able memory क्रम reply queues according.
	 *  Driver uses limitation of
	 *  VENTURA_SERIES to manage INVADER_SERIES as well.
	 */
	dma_alloc_count = DIV_ROUND_UP(count,
				RDPQ_MAX_INDEX_IN_ONE_CHUNK);
	ioc->reply_post_मुक्त_dma_pool =
		dma_pool_create("reply_post_free pool",
		    &ioc->pdev->dev, sz, 16, 0);
	अगर (!ioc->reply_post_मुक्त_dma_pool)
		वापस -ENOMEM;
	क्रम (i = 0; i < count; i++) अणु
		अगर ((i % RDPQ_MAX_INDEX_IN_ONE_CHUNK == 0) && dma_alloc_count) अणु
			ioc->reply_post[i].reply_post_मुक्त =
			    dma_pool_zalloc(ioc->reply_post_मुक्त_dma_pool,
				GFP_KERNEL,
				&ioc->reply_post[i].reply_post_मुक्त_dma);
			अगर (!ioc->reply_post[i].reply_post_मुक्त)
				वापस -ENOMEM;
			/*
			 * Each set of RDPQ pool must satisfy 4gb boundary
			 * restriction.
			 * 1) Check अगर allocated resources क्रम RDPQ pool are in
			 *	the same 4GB range.
			 * 2) If #1 is true, जारी with 64 bit DMA.
			 * 3) If #1 is false, वापस 1. which means मुक्त all the
			 * resources and set DMA mask to 32 and allocate.
			 */
			अगर (!mpt3sas_check_same_4gb_region(
				(दीर्घ)ioc->reply_post[i].reply_post_मुक्त, sz)) अणु
				dinitprपूर्णांकk(ioc,
				    ioc_err(ioc, "bad Replypost free pool(0x%p)"
				    "reply_post_free_dma = (0x%llx)\n",
				    ioc->reply_post[i].reply_post_मुक्त,
				    (अचिन्हित दीर्घ दीर्घ)
				    ioc->reply_post[i].reply_post_मुक्त_dma));
				वापस -EAGAIN;
			पूर्ण
			dma_alloc_count--;

		पूर्ण अन्यथा अणु
			ioc->reply_post[i].reply_post_मुक्त =
			    (Mpi2ReplyDescriptorsUnion_t *)
			    ((दीर्घ)ioc->reply_post[i-1].reply_post_मुक्त
			    + reply_post_मुक्त_sz);
			ioc->reply_post[i].reply_post_मुक्त_dma =
			    (dma_addr_t)
			    (ioc->reply_post[i-1].reply_post_मुक्त_dma +
			    reply_post_मुक्त_sz);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * _base_allocate_memory_pools - allocate start of day memory pools
 * @ioc: per adapter object
 *
 * Return: 0 success, anything अन्यथा error.
 */
अटल पूर्णांक
_base_allocate_memory_pools(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	काष्ठा mpt3sas_facts *facts;
	u16 max_sge_elements;
	u16 chains_needed_per_io;
	u32 sz, total_sz, reply_post_मुक्त_sz, reply_post_मुक्त_array_sz;
	u32 retry_sz;
	u32 rdpq_sz = 0, sense_sz = 0;
	u16 max_request_credit, nvme_blocks_needed;
	अचिन्हित लघु sg_tablesize;
	u16 sge_size;
	पूर्णांक i;
	पूर्णांक ret = 0, rc = 0;

	dinitprपूर्णांकk(ioc, ioc_info(ioc, "%s\n", __func__));


	retry_sz = 0;
	facts = &ioc->facts;

	/* command line tunables क्रम max sgl entries */
	अगर (max_sgl_entries != -1)
		sg_tablesize = max_sgl_entries;
	अन्यथा अणु
		अगर (ioc->hba_mpi_version_beदीर्घed == MPI2_VERSION)
			sg_tablesize = MPT2SAS_SG_DEPTH;
		अन्यथा
			sg_tablesize = MPT3SAS_SG_DEPTH;
	पूर्ण

	/* max sgl entries <= MPT_KDUMP_MIN_PHYS_SEGMENTS in KDUMP mode */
	अगर (reset_devices)
		sg_tablesize = min_t(अचिन्हित लघु, sg_tablesize,
		   MPT_KDUMP_MIN_PHYS_SEGMENTS);

	अगर (ioc->is_mcpu_endpoपूर्णांक)
		ioc->shost->sg_tablesize = MPT_MIN_PHYS_SEGMENTS;
	अन्यथा अणु
		अगर (sg_tablesize < MPT_MIN_PHYS_SEGMENTS)
			sg_tablesize = MPT_MIN_PHYS_SEGMENTS;
		अन्यथा अगर (sg_tablesize > MPT_MAX_PHYS_SEGMENTS) अणु
			sg_tablesize = min_t(अचिन्हित लघु, sg_tablesize,
					SG_MAX_SEGMENTS);
			ioc_warn(ioc, "sg_tablesize(%u) is bigger than kernel defined SG_CHUNK_SIZE(%u)\n",
				 sg_tablesize, MPT_MAX_PHYS_SEGMENTS);
		पूर्ण
		ioc->shost->sg_tablesize = sg_tablesize;
	पूर्ण

	ioc->पूर्णांकernal_depth = min_t(पूर्णांक, (facts->HighPriorityCredit + (5)),
		(facts->RequestCredit / 4));
	अगर (ioc->पूर्णांकernal_depth < INTERNAL_CMDS_COUNT) अणु
		अगर (facts->RequestCredit <= (INTERNAL_CMDS_COUNT +
				INTERNAL_SCSIIO_CMDS_COUNT)) अणु
			ioc_err(ioc, "IOC doesn't have enough Request Credits, it has just %d number of credits\n",
				facts->RequestCredit);
			वापस -ENOMEM;
		पूर्ण
		ioc->पूर्णांकernal_depth = 10;
	पूर्ण

	ioc->hi_priority_depth = ioc->पूर्णांकernal_depth - (5);
	/* command line tunables  क्रम max controller queue depth */
	अगर (max_queue_depth != -1 && max_queue_depth != 0) अणु
		max_request_credit = min_t(u16, max_queue_depth +
			ioc->पूर्णांकernal_depth, facts->RequestCredit);
		अगर (max_request_credit > MAX_HBA_QUEUE_DEPTH)
			max_request_credit =  MAX_HBA_QUEUE_DEPTH;
	पूर्ण अन्यथा अगर (reset_devices)
		max_request_credit = min_t(u16, facts->RequestCredit,
		    (MPT3SAS_KDUMP_SCSI_IO_DEPTH + ioc->पूर्णांकernal_depth));
	अन्यथा
		max_request_credit = min_t(u16, facts->RequestCredit,
		    MAX_HBA_QUEUE_DEPTH);

	/* Firmware मुख्यtains additional facts->HighPriorityCredit number of
	 * credits क्रम HiPriprity Request messages, so hba queue depth will be
	 * sum of max_request_credit and high priority queue depth.
	 */
	ioc->hba_queue_depth = max_request_credit + ioc->hi_priority_depth;

	/* request frame size */
	ioc->request_sz = facts->IOCRequestFrameSize * 4;

	/* reply frame size */
	ioc->reply_sz = facts->ReplyFrameSize * 4;

	/* chain segment size */
	अगर (ioc->hba_mpi_version_beदीर्घed != MPI2_VERSION) अणु
		अगर (facts->IOCMaxChainSegmentSize)
			ioc->chain_segment_sz =
					facts->IOCMaxChainSegmentSize *
					MAX_CHAIN_ELEMT_SZ;
		अन्यथा
		/* set to 128 bytes size अगर IOCMaxChainSegmentSize is zero */
			ioc->chain_segment_sz = DEFAULT_NUM_FWCHAIN_ELEMTS *
						    MAX_CHAIN_ELEMT_SZ;
	पूर्ण अन्यथा
		ioc->chain_segment_sz = ioc->request_sz;

	/* calculate the max scatter element size */
	sge_size = max_t(u16, ioc->sge_size, ioc->sge_size_ieee);

 retry_allocation:
	total_sz = 0;
	/* calculate number of sg elements left over in the 1st frame */
	max_sge_elements = ioc->request_sz - ((माप(Mpi2SCSIIORequest_t) -
	    माप(Mpi2SGEIOUnion_t)) + sge_size);
	ioc->max_sges_in_मुख्य_message = max_sge_elements/sge_size;

	/* now करो the same क्रम a chain buffer */
	max_sge_elements = ioc->chain_segment_sz - sge_size;
	ioc->max_sges_in_chain_message = max_sge_elements/sge_size;

	/*
	 *  MPT3SAS_SG_DEPTH = CONFIG_FUSION_MAX_SGE
	 */
	chains_needed_per_io = ((ioc->shost->sg_tablesize -
	   ioc->max_sges_in_मुख्य_message)/ioc->max_sges_in_chain_message)
	    + 1;
	अगर (chains_needed_per_io > facts->MaxChainDepth) अणु
		chains_needed_per_io = facts->MaxChainDepth;
		ioc->shost->sg_tablesize = min_t(u16,
		ioc->max_sges_in_मुख्य_message + (ioc->max_sges_in_chain_message
		* chains_needed_per_io), ioc->shost->sg_tablesize);
	पूर्ण
	ioc->chains_needed_per_io = chains_needed_per_io;

	/* reply मुक्त queue sizing - taking पूर्णांकo account क्रम 64 FW events */
	ioc->reply_मुक्त_queue_depth = ioc->hba_queue_depth + 64;

	/* mCPU manage single counters क्रम simplicity */
	अगर (ioc->is_mcpu_endpoपूर्णांक)
		ioc->reply_post_queue_depth = ioc->reply_मुक्त_queue_depth;
	अन्यथा अणु
		/* calculate reply descriptor post queue depth */
		ioc->reply_post_queue_depth = ioc->hba_queue_depth +
			ioc->reply_मुक्त_queue_depth +  1;
		/* align the reply post queue on the next 16 count boundary */
		अगर (ioc->reply_post_queue_depth % 16)
			ioc->reply_post_queue_depth += 16 -
				(ioc->reply_post_queue_depth % 16);
	पूर्ण

	अगर (ioc->reply_post_queue_depth >
	    facts->MaxReplyDescriptorPostQueueDepth) अणु
		ioc->reply_post_queue_depth =
				facts->MaxReplyDescriptorPostQueueDepth -
		    (facts->MaxReplyDescriptorPostQueueDepth % 16);
		ioc->hba_queue_depth =
				((ioc->reply_post_queue_depth - 64) / 2) - 1;
		ioc->reply_मुक्त_queue_depth = ioc->hba_queue_depth + 64;
	पूर्ण

	ioc_info(ioc,
	    "scatter gather: sge_in_main_msg(%d), sge_per_chain(%d), "
	    "sge_per_io(%d), chains_per_io(%d)\n",
	    ioc->max_sges_in_मुख्य_message,
	    ioc->max_sges_in_chain_message,
	    ioc->shost->sg_tablesize,
	    ioc->chains_needed_per_io);

	/* reply post queue, 16 byte align */
	reply_post_मुक्त_sz = ioc->reply_post_queue_depth *
	    माप(Mpi2DefaultReplyDescriptor_t);
	rdpq_sz = reply_post_मुक्त_sz * RDPQ_MAX_INDEX_IN_ONE_CHUNK;
	अगर ((_base_is_controller_msix_enabled(ioc) && !ioc->rdpq_array_enable)
	    || (ioc->reply_queue_count < RDPQ_MAX_INDEX_IN_ONE_CHUNK))
		rdpq_sz = reply_post_मुक्त_sz * ioc->reply_queue_count;
	ret = base_alloc_rdpq_dma_pool(ioc, rdpq_sz);
	अगर (ret == -EAGAIN) अणु
		/*
		 * Free allocated bad RDPQ memory pools.
		 * Change dma coherent mask to 32 bit and पुनः_स्मृतिate RDPQ
		 */
		_base_release_memory_pools(ioc);
		ioc->use_32bit_dma = true;
		अगर (_base_config_dma_addressing(ioc, ioc->pdev) != 0) अणु
			ioc_err(ioc,
			    "32 DMA mask failed %s\n", pci_name(ioc->pdev));
			वापस -ENODEV;
		पूर्ण
		अगर (base_alloc_rdpq_dma_pool(ioc, rdpq_sz))
			वापस -ENOMEM;
	पूर्ण अन्यथा अगर (ret == -ENOMEM)
		वापस -ENOMEM;
	total_sz = rdpq_sz * (!ioc->rdpq_array_enable ? 1 :
	    DIV_ROUND_UP(ioc->reply_queue_count, RDPQ_MAX_INDEX_IN_ONE_CHUNK));
	ioc->scsiio_depth = ioc->hba_queue_depth -
	    ioc->hi_priority_depth - ioc->पूर्णांकernal_depth;

	/* set the scsi host can_queue depth
	 * with some पूर्णांकernal commands that could be outstanding
	 */
	ioc->shost->can_queue = ioc->scsiio_depth - INTERNAL_SCSIIO_CMDS_COUNT;
	dinitprपूर्णांकk(ioc,
		    ioc_info(ioc, "scsi host: can_queue depth (%d)\n",
			     ioc->shost->can_queue));

	/* contiguous pool क्रम request and chains, 16 byte align, one extra "
	 * "frame क्रम smid=0
	 */
	ioc->chain_depth = ioc->chains_needed_per_io * ioc->scsiio_depth;
	sz = ((ioc->scsiio_depth + 1) * ioc->request_sz);

	/* hi-priority queue */
	sz += (ioc->hi_priority_depth * ioc->request_sz);

	/* पूर्णांकernal queue */
	sz += (ioc->पूर्णांकernal_depth * ioc->request_sz);

	ioc->request_dma_sz = sz;
	ioc->request = dma_alloc_coherent(&ioc->pdev->dev, sz,
			&ioc->request_dma, GFP_KERNEL);
	अगर (!ioc->request) अणु
		ioc_err(ioc, "request pool: dma_alloc_coherent failed: hba_depth(%d), chains_per_io(%d), frame_sz(%d), total(%d kB)\n",
			ioc->hba_queue_depth, ioc->chains_needed_per_io,
			ioc->request_sz, sz / 1024);
		अगर (ioc->scsiio_depth < MPT3SAS_SAS_QUEUE_DEPTH)
			जाओ out;
		retry_sz = 64;
		ioc->hba_queue_depth -= retry_sz;
		_base_release_memory_pools(ioc);
		जाओ retry_allocation;
	पूर्ण

	अगर (retry_sz)
		ioc_err(ioc, "request pool: dma_alloc_coherent succeed: hba_depth(%d), chains_per_io(%d), frame_sz(%d), total(%d kb)\n",
			ioc->hba_queue_depth, ioc->chains_needed_per_io,
			ioc->request_sz, sz / 1024);

	/* hi-priority queue */
	ioc->hi_priority = ioc->request + ((ioc->scsiio_depth + 1) *
	    ioc->request_sz);
	ioc->hi_priority_dma = ioc->request_dma + ((ioc->scsiio_depth + 1) *
	    ioc->request_sz);

	/* पूर्णांकernal queue */
	ioc->पूर्णांकernal = ioc->hi_priority + (ioc->hi_priority_depth *
	    ioc->request_sz);
	ioc->पूर्णांकernal_dma = ioc->hi_priority_dma + (ioc->hi_priority_depth *
	    ioc->request_sz);

	ioc_info(ioc,
	    "request pool(0x%p) - dma(0x%llx): "
	    "depth(%d), frame_size(%d), pool_size(%d kB)\n",
	    ioc->request, (अचिन्हित दीर्घ दीर्घ) ioc->request_dma,
	    ioc->hba_queue_depth, ioc->request_sz,
	    (ioc->hba_queue_depth * ioc->request_sz) / 1024);

	total_sz += sz;

	dinitprपूर्णांकk(ioc,
		    ioc_info(ioc, "scsiio(0x%p): depth(%d)\n",
			     ioc->request, ioc->scsiio_depth));

	ioc->chain_depth = min_t(u32, ioc->chain_depth, MAX_CHAIN_DEPTH);
	sz = ioc->scsiio_depth * माप(काष्ठा chain_lookup);
	ioc->chain_lookup = kzalloc(sz, GFP_KERNEL);
	अगर (!ioc->chain_lookup) अणु
		ioc_err(ioc, "chain_lookup: __get_free_pages failed\n");
		जाओ out;
	पूर्ण

	sz = ioc->chains_needed_per_io * माप(काष्ठा chain_tracker);
	क्रम (i = 0; i < ioc->scsiio_depth; i++) अणु
		ioc->chain_lookup[i].chains_per_smid = kzalloc(sz, GFP_KERNEL);
		अगर (!ioc->chain_lookup[i].chains_per_smid) अणु
			ioc_err(ioc, "chain_lookup: kzalloc failed\n");
			जाओ out;
		पूर्ण
	पूर्ण

	/* initialize hi-priority queue smid's */
	ioc->hpr_lookup = kसुस्मृति(ioc->hi_priority_depth,
	    माप(काष्ठा request_tracker), GFP_KERNEL);
	अगर (!ioc->hpr_lookup) अणु
		ioc_err(ioc, "hpr_lookup: kcalloc failed\n");
		जाओ out;
	पूर्ण
	ioc->hi_priority_smid = ioc->scsiio_depth + 1;
	dinitprपूर्णांकk(ioc,
		    ioc_info(ioc, "hi_priority(0x%p): depth(%d), start smid(%d)\n",
			     ioc->hi_priority,
			     ioc->hi_priority_depth, ioc->hi_priority_smid));

	/* initialize पूर्णांकernal queue smid's */
	ioc->पूर्णांकernal_lookup = kसुस्मृति(ioc->पूर्णांकernal_depth,
	    माप(काष्ठा request_tracker), GFP_KERNEL);
	अगर (!ioc->पूर्णांकernal_lookup) अणु
		ioc_err(ioc, "internal_lookup: kcalloc failed\n");
		जाओ out;
	पूर्ण
	ioc->पूर्णांकernal_smid = ioc->hi_priority_smid + ioc->hi_priority_depth;
	dinitprपूर्णांकk(ioc,
		    ioc_info(ioc, "internal(0x%p): depth(%d), start smid(%d)\n",
			     ioc->पूर्णांकernal,
			     ioc->पूर्णांकernal_depth, ioc->पूर्णांकernal_smid));

	ioc->io_queue_num = kसुस्मृति(ioc->scsiio_depth,
	    माप(u16), GFP_KERNEL);
	अगर (!ioc->io_queue_num)
		जाओ out;
	/*
	 * The number of NVMe page sized blocks needed is:
	 *     (((sg_tablesize * 8) - 1) / (page_size - 8)) + 1
	 * ((sg_tablesize * 8) - 1) is the max PRP's minus the first PRP entry
	 * that is placed in the मुख्य message frame.  8 is the size of each PRP
	 * entry or PRP list poपूर्णांकer entry.  8 is subtracted from page_size
	 * because of the PRP list poपूर्णांकer entry at the end of a page, so this
	 * is not counted as a PRP entry.  The 1 added page is a round up.
	 *
	 * To aव्योम allocation failures due to the amount of memory that could
	 * be required क्रम NVMe PRP's, only each set of NVMe blocks will be
	 * contiguous, so a new set is allocated क्रम each possible I/O.
	 */

	ioc->chains_per_prp_buffer = 0;
	अगर (ioc->facts.ProtocolFlags & MPI2_IOCFACTS_PROTOCOL_NVME_DEVICES) अणु
		nvme_blocks_needed =
			(ioc->shost->sg_tablesize * NVME_PRP_SIZE) - 1;
		nvme_blocks_needed /= (ioc->page_size - NVME_PRP_SIZE);
		nvme_blocks_needed++;

		sz = माप(काष्ठा pcie_sg_list) * ioc->scsiio_depth;
		ioc->pcie_sg_lookup = kzalloc(sz, GFP_KERNEL);
		अगर (!ioc->pcie_sg_lookup) अणु
			ioc_info(ioc, "PCIe SGL lookup: kzalloc failed\n");
			जाओ out;
		पूर्ण
		sz = nvme_blocks_needed * ioc->page_size;
		rc = _base_allocate_pcie_sgl_pool(ioc, sz);
		अगर (rc == -ENOMEM)
			वापस -ENOMEM;
		अन्यथा अगर (rc == -EAGAIN)
			जाओ try_32bit_dma;
		total_sz += sz * ioc->scsiio_depth;
	पूर्ण

	rc = _base_allocate_chain_dma_pool(ioc, ioc->chain_segment_sz);
	अगर (rc == -ENOMEM)
		वापस -ENOMEM;
	अन्यथा अगर (rc == -EAGAIN)
		जाओ try_32bit_dma;
	total_sz += ioc->chain_segment_sz * ((ioc->chains_needed_per_io -
		ioc->chains_per_prp_buffer) * ioc->scsiio_depth);
	dinitprपूर्णांकk(ioc,
	    ioc_info(ioc, "chain pool depth(%d), frame_size(%d), pool_size(%d kB)\n",
	    ioc->chain_depth, ioc->chain_segment_sz,
	    (ioc->chain_depth * ioc->chain_segment_sz) / 1024));
	/* sense buffers, 4 byte align */
	sense_sz = ioc->scsiio_depth * SCSI_SENSE_BUFFERSIZE;
	rc = _base_allocate_sense_dma_pool(ioc, sense_sz);
	अगर (rc  == -ENOMEM)
		वापस -ENOMEM;
	अन्यथा अगर (rc == -EAGAIN)
		जाओ try_32bit_dma;
	total_sz += sense_sz;
	ioc_info(ioc,
	    "sense pool(0x%p)- dma(0x%llx): depth(%d),"
	    "element_size(%d), pool_size(%d kB)\n",
	    ioc->sense, (अचिन्हित दीर्घ दीर्घ)ioc->sense_dma, ioc->scsiio_depth,
	    SCSI_SENSE_BUFFERSIZE, sz / 1024);
	/* reply pool, 4 byte align */
	sz = ioc->reply_मुक्त_queue_depth * ioc->reply_sz;
	rc = _base_allocate_reply_pool(ioc, sz);
	अगर (rc == -ENOMEM)
		वापस -ENOMEM;
	अन्यथा अगर (rc == -EAGAIN)
		जाओ try_32bit_dma;
	total_sz += sz;

	/* reply मुक्त queue, 16 byte align */
	sz = ioc->reply_मुक्त_queue_depth * 4;
	rc = _base_allocate_reply_मुक्त_dma_pool(ioc, sz);
	अगर (rc  == -ENOMEM)
		वापस -ENOMEM;
	अन्यथा अगर (rc == -EAGAIN)
		जाओ try_32bit_dma;
	dinitprपूर्णांकk(ioc,
		    ioc_info(ioc, "reply_free_dma (0x%llx)\n",
			     (अचिन्हित दीर्घ दीर्घ)ioc->reply_मुक्त_dma));
	total_sz += sz;
	अगर (ioc->rdpq_array_enable) अणु
		reply_post_मुक्त_array_sz = ioc->reply_queue_count *
		    माप(Mpi2IOCInitRDPQArrayEntry);
		rc = _base_allocate_reply_post_मुक्त_array(ioc,
		    reply_post_मुक्त_array_sz);
		अगर (rc == -ENOMEM)
			वापस -ENOMEM;
		अन्यथा अगर (rc == -EAGAIN)
			जाओ try_32bit_dma;
	पूर्ण
	ioc->config_page_sz = 512;
	ioc->config_page = dma_alloc_coherent(&ioc->pdev->dev,
			ioc->config_page_sz, &ioc->config_page_dma, GFP_KERNEL);
	अगर (!ioc->config_page) अणु
		ioc_err(ioc, "config page: dma_pool_alloc failed\n");
		जाओ out;
	पूर्ण

	ioc_info(ioc, "config page(0x%p) - dma(0x%llx): size(%d)\n",
	    ioc->config_page, (अचिन्हित दीर्घ दीर्घ)ioc->config_page_dma,
	    ioc->config_page_sz);
	total_sz += ioc->config_page_sz;

	ioc_info(ioc, "Allocated physical memory: size(%d kB)\n",
		 total_sz / 1024);
	ioc_info(ioc, "Current Controller Queue Depth(%d),Max Controller Queue Depth(%d)\n",
		 ioc->shost->can_queue, facts->RequestCredit);
	ioc_info(ioc, "Scatter Gather Elements per IO(%d)\n",
		 ioc->shost->sg_tablesize);
	वापस 0;

try_32bit_dma:
	_base_release_memory_pools(ioc);
	अगर (ioc->use_32bit_dma && (ioc->dma_mask > 32)) अणु
		/* Change dma coherent mask to 32 bit and पुनः_स्मृतिate */
		अगर (_base_config_dma_addressing(ioc, ioc->pdev) != 0) अणु
			pr_err("Setting 32 bit coherent DMA mask Failed %s\n",
			    pci_name(ioc->pdev));
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अगर (_base_reduce_hba_queue_depth(ioc) != 0)
		वापस -ENOMEM;
	जाओ retry_allocation;

 out:
	वापस -ENOMEM;
पूर्ण

/**
 * mpt3sas_base_get_iocstate - Get the current state of a MPT adapter.
 * @ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 * @cooked: Request raw or cooked IOC state
 *
 * Return: all IOC Doorbell रेजिस्टर bits अगर cooked==0, अन्यथा just the
 * Doorbell bits in MPI_IOC_STATE_MASK.
 */
u32
mpt3sas_base_get_iocstate(काष्ठा MPT3SAS_ADAPTER *ioc, पूर्णांक cooked)
अणु
	u32 s, sc;

	s = ioc->base_पढ़ोl(&ioc->chip->Doorbell);
	sc = s & MPI2_IOC_STATE_MASK;
	वापस cooked ? sc : s;
पूर्ण

/**
 * _base_रुको_on_iocstate - रुकोing on a particular ioc state
 * @ioc: ?
 * @ioc_state: controller state अणु READY, OPERATIONAL, or RESET पूर्ण
 * @समयout: समयout in second
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_base_रुको_on_iocstate(काष्ठा MPT3SAS_ADAPTER *ioc, u32 ioc_state, पूर्णांक समयout)
अणु
	u32 count, cntdn;
	u32 current_state;

	count = 0;
	cntdn = 1000 * समयout;
	करो अणु
		current_state = mpt3sas_base_get_iocstate(ioc, 1);
		अगर (current_state == ioc_state)
			वापस 0;
		अगर (count && current_state == MPI2_IOC_STATE_FAULT)
			अवरोध;
		अगर (count && current_state == MPI2_IOC_STATE_COREDUMP)
			अवरोध;

		usleep_range(1000, 1500);
		count++;
	पूर्ण जबतक (--cntdn);

	वापस current_state;
पूर्ण

/**
 * _base_dump_reg_set -	This function will prपूर्णांक hexdump of रेजिस्टर set.
 * @ioc: per adapter object
 *
 * Returns nothing.
 */
अटल अंतरभूत व्योम
_base_dump_reg_set(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	अचिन्हित पूर्णांक i, sz = 256;
	u32 __iomem *reg = (u32 __iomem *)ioc->chip;

	ioc_info(ioc, "System Register set:\n");
	क्रम (i = 0; i < (sz / माप(u32)); i++)
		pr_info("%08x: %08x\n", (i * 4), पढ़ोl(&reg[i]));
पूर्ण

/**
 * _base_रुको_क्रम_करोorbell_पूर्णांक - रुकोing क्रम controller पूर्णांकerrupt(generated by
 * a ग_लिखो to the करोorbell)
 * @ioc: per adapter object
 * @समयout: समयout in seconds
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 *
 * Notes: MPI2_HIS_IOC2SYS_DB_STATUS - set to one when IOC ग_लिखोs to करोorbell.
 */

अटल पूर्णांक
_base_रुको_क्रम_करोorbell_पूर्णांक(काष्ठा MPT3SAS_ADAPTER *ioc, पूर्णांक समयout)
अणु
	u32 cntdn, count;
	u32 पूर्णांक_status;

	count = 0;
	cntdn = 1000 * समयout;
	करो अणु
		पूर्णांक_status = ioc->base_पढ़ोl(&ioc->chip->HostInterruptStatus);
		अगर (पूर्णांक_status & MPI2_HIS_IOC2SYS_DB_STATUS) अणु
			dhsprपूर्णांकk(ioc,
				  ioc_info(ioc, "%s: successful count(%d), timeout(%d)\n",
					   __func__, count, समयout));
			वापस 0;
		पूर्ण

		usleep_range(1000, 1500);
		count++;
	पूर्ण जबतक (--cntdn);

	ioc_err(ioc, "%s: failed due to timeout count(%d), int_status(%x)!\n",
		__func__, count, पूर्णांक_status);
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक
_base_spin_on_करोorbell_पूर्णांक(काष्ठा MPT3SAS_ADAPTER *ioc, पूर्णांक समयout)
अणु
	u32 cntdn, count;
	u32 पूर्णांक_status;

	count = 0;
	cntdn = 2000 * समयout;
	करो अणु
		पूर्णांक_status = ioc->base_पढ़ोl(&ioc->chip->HostInterruptStatus);
		अगर (पूर्णांक_status & MPI2_HIS_IOC2SYS_DB_STATUS) अणु
			dhsprपूर्णांकk(ioc,
				  ioc_info(ioc, "%s: successful count(%d), timeout(%d)\n",
					   __func__, count, समयout));
			वापस 0;
		पूर्ण

		udelay(500);
		count++;
	पूर्ण जबतक (--cntdn);

	ioc_err(ioc, "%s: failed due to timeout count(%d), int_status(%x)!\n",
		__func__, count, पूर्णांक_status);
	वापस -EFAULT;

पूर्ण

/**
 * _base_रुको_क्रम_करोorbell_ack - रुकोing क्रम controller to पढ़ो the करोorbell.
 * @ioc: per adapter object
 * @समयout: समयout in second
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 *
 * Notes: MPI2_HIS_SYS2IOC_DB_STATUS - set to one when host ग_लिखोs to
 * करोorbell.
 */
अटल पूर्णांक
_base_रुको_क्रम_करोorbell_ack(काष्ठा MPT3SAS_ADAPTER *ioc, पूर्णांक समयout)
अणु
	u32 cntdn, count;
	u32 पूर्णांक_status;
	u32 करोorbell;

	count = 0;
	cntdn = 1000 * समयout;
	करो अणु
		पूर्णांक_status = ioc->base_पढ़ोl(&ioc->chip->HostInterruptStatus);
		अगर (!(पूर्णांक_status & MPI2_HIS_SYS2IOC_DB_STATUS)) अणु
			dhsprपूर्णांकk(ioc,
				  ioc_info(ioc, "%s: successful count(%d), timeout(%d)\n",
					   __func__, count, समयout));
			वापस 0;
		पूर्ण अन्यथा अगर (पूर्णांक_status & MPI2_HIS_IOC2SYS_DB_STATUS) अणु
			करोorbell = ioc->base_पढ़ोl(&ioc->chip->Doorbell);
			अगर ((करोorbell & MPI2_IOC_STATE_MASK) ==
			    MPI2_IOC_STATE_FAULT) अणु
				mpt3sas_prपूर्णांक_fault_code(ioc, करोorbell);
				वापस -EFAULT;
			पूर्ण
			अगर ((करोorbell & MPI2_IOC_STATE_MASK) ==
			    MPI2_IOC_STATE_COREDUMP) अणु
				mpt3sas_prपूर्णांक_coredump_info(ioc, करोorbell);
				वापस -EFAULT;
			पूर्ण
		पूर्ण अन्यथा अगर (पूर्णांक_status == 0xFFFFFFFF)
			जाओ out;

		usleep_range(1000, 1500);
		count++;
	पूर्ण जबतक (--cntdn);

 out:
	ioc_err(ioc, "%s: failed due to timeout count(%d), int_status(%x)!\n",
		__func__, count, पूर्णांक_status);
	वापस -EFAULT;
पूर्ण

/**
 * _base_रुको_क्रम_करोorbell_not_used - रुकोing क्रम करोorbell to not be in use
 * @ioc: per adapter object
 * @समयout: समयout in second
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_base_रुको_क्रम_करोorbell_not_used(काष्ठा MPT3SAS_ADAPTER *ioc, पूर्णांक समयout)
अणु
	u32 cntdn, count;
	u32 करोorbell_reg;

	count = 0;
	cntdn = 1000 * समयout;
	करो अणु
		करोorbell_reg = ioc->base_पढ़ोl(&ioc->chip->Doorbell);
		अगर (!(करोorbell_reg & MPI2_DOORBELL_USED)) अणु
			dhsprपूर्णांकk(ioc,
				  ioc_info(ioc, "%s: successful count(%d), timeout(%d)\n",
					   __func__, count, समयout));
			वापस 0;
		पूर्ण

		usleep_range(1000, 1500);
		count++;
	पूर्ण जबतक (--cntdn);

	ioc_err(ioc, "%s: failed due to timeout count(%d), doorbell_reg(%x)!\n",
		__func__, count, करोorbell_reg);
	वापस -EFAULT;
पूर्ण

/**
 * _base_send_ioc_reset - send करोorbell reset
 * @ioc: per adapter object
 * @reset_type: currently only supports: MPI2_FUNCTION_IOC_MESSAGE_UNIT_RESET
 * @समयout: समयout in second
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_base_send_ioc_reset(काष्ठा MPT3SAS_ADAPTER *ioc, u8 reset_type, पूर्णांक समयout)
अणु
	u32 ioc_state;
	पूर्णांक r = 0;
	अचिन्हित दीर्घ flags;

	अगर (reset_type != MPI2_FUNCTION_IOC_MESSAGE_UNIT_RESET) अणु
		ioc_err(ioc, "%s: unknown reset_type\n", __func__);
		वापस -EFAULT;
	पूर्ण

	अगर (!(ioc->facts.IOCCapabilities &
	   MPI2_IOCFACTS_CAPABILITY_EVENT_REPLAY))
		वापस -EFAULT;

	ioc_info(ioc, "sending message unit reset !!\n");

	ग_लिखोl(reset_type << MPI2_DOORBELL_FUNCTION_SHIFT,
	    &ioc->chip->Doorbell);
	अगर ((_base_रुको_क्रम_करोorbell_ack(ioc, 15))) अणु
		r = -EFAULT;
		जाओ out;
	पूर्ण

	ioc_state = _base_रुको_on_iocstate(ioc, MPI2_IOC_STATE_READY, समयout);
	अगर (ioc_state) अणु
		ioc_err(ioc, "%s: failed going to ready state (ioc_state=0x%x)\n",
			__func__, ioc_state);
		r = -EFAULT;
		जाओ out;
	पूर्ण
 out:
	अगर (r != 0) अणु
		ioc_state = mpt3sas_base_get_iocstate(ioc, 0);
		spin_lock_irqsave(&ioc->ioc_reset_in_progress_lock, flags);
		/*
		 * Wait क्रम IOC state CoreDump to clear only during
		 * HBA initialization & release समय.
		 */
		अगर ((ioc_state & MPI2_IOC_STATE_MASK) ==
		    MPI2_IOC_STATE_COREDUMP && (ioc->is_driver_loading == 1 ||
		    ioc->fault_reset_work_q == शून्य)) अणु
			spin_unlock_irqrestore(
			    &ioc->ioc_reset_in_progress_lock, flags);
			mpt3sas_prपूर्णांक_coredump_info(ioc, ioc_state);
			mpt3sas_base_रुको_क्रम_coredump_completion(ioc,
			    __func__);
			spin_lock_irqsave(
			    &ioc->ioc_reset_in_progress_lock, flags);
		पूर्ण
		spin_unlock_irqrestore(&ioc->ioc_reset_in_progress_lock, flags);
	पूर्ण
	ioc_info(ioc, "message unit reset: %s\n",
		 r == 0 ? "SUCCESS" : "FAILED");
	वापस r;
पूर्ण

/**
 * mpt3sas_रुको_क्रम_ioc - IOC's operational state is checked here.
 * @ioc: per adapter object
 * @समयout: समयout in seconds
 *
 * Return: Waits up to समयout seconds क्रम the IOC to
 * become operational. Returns 0 अगर IOC is present
 * and operational; otherwise वापसs -EFAULT.
 */

पूर्णांक
mpt3sas_रुको_क्रम_ioc(काष्ठा MPT3SAS_ADAPTER *ioc, पूर्णांक समयout)
अणु
	पूर्णांक रुको_state_count = 0;
	u32 ioc_state;

	करो अणु
		ioc_state = mpt3sas_base_get_iocstate(ioc, 1);
		अगर (ioc_state == MPI2_IOC_STATE_OPERATIONAL)
			अवरोध;
		ssleep(1);
		ioc_info(ioc, "%s: waiting for operational state(count=%d)\n",
				__func__, ++रुको_state_count);
	पूर्ण जबतक (--समयout);
	अगर (!समयout) अणु
		ioc_err(ioc, "%s: failed due to ioc not operational\n", __func__);
		वापस -EFAULT;
	पूर्ण
	अगर (रुको_state_count)
		ioc_info(ioc, "ioc is operational\n");
	वापस 0;
पूर्ण

/**
 * _base_handshake_req_reply_रुको - send request thru करोorbell पूर्णांकerface
 * @ioc: per adapter object
 * @request_bytes: request length
 * @request: poपूर्णांकer having request payload
 * @reply_bytes: reply length
 * @reply: poपूर्णांकer to reply payload
 * @समयout: समयout in second
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_base_handshake_req_reply_रुको(काष्ठा MPT3SAS_ADAPTER *ioc, पूर्णांक request_bytes,
	u32 *request, पूर्णांक reply_bytes, u16 *reply, पूर्णांक समयout)
अणु
	MPI2DefaultReply_t *शेष_reply = (MPI2DefaultReply_t *)reply;
	पूर्णांक i;
	u8 failed;
	__le32 *mfp;

	/* make sure करोorbell is not in use */
	अगर ((ioc->base_पढ़ोl(&ioc->chip->Doorbell) & MPI2_DOORBELL_USED)) अणु
		ioc_err(ioc, "doorbell is in use (line=%d)\n", __LINE__);
		वापस -EFAULT;
	पूर्ण

	/* clear pending करोorbell पूर्णांकerrupts from previous state changes */
	अगर (ioc->base_पढ़ोl(&ioc->chip->HostInterruptStatus) &
	    MPI2_HIS_IOC2SYS_DB_STATUS)
		ग_लिखोl(0, &ioc->chip->HostInterruptStatus);

	/* send message to ioc */
	ग_लिखोl(((MPI2_FUNCTION_HANDSHAKE<<MPI2_DOORBELL_FUNCTION_SHIFT) |
	    ((request_bytes/4)<<MPI2_DOORBELL_ADD_DWORDS_SHIFT)),
	    &ioc->chip->Doorbell);

	अगर ((_base_spin_on_करोorbell_पूर्णांक(ioc, 5))) अणु
		ioc_err(ioc, "doorbell handshake int failed (line=%d)\n",
			__LINE__);
		वापस -EFAULT;
	पूर्ण
	ग_लिखोl(0, &ioc->chip->HostInterruptStatus);

	अगर ((_base_रुको_क्रम_करोorbell_ack(ioc, 5))) अणु
		ioc_err(ioc, "doorbell handshake ack failed (line=%d)\n",
			__LINE__);
		वापस -EFAULT;
	पूर्ण

	/* send message 32-bits at a समय */
	क्रम (i = 0, failed = 0; i < request_bytes/4 && !failed; i++) अणु
		ग_लिखोl(cpu_to_le32(request[i]), &ioc->chip->Doorbell);
		अगर ((_base_रुको_क्रम_करोorbell_ack(ioc, 5)))
			failed = 1;
	पूर्ण

	अगर (failed) अणु
		ioc_err(ioc, "doorbell handshake sending request failed (line=%d)\n",
			__LINE__);
		वापस -EFAULT;
	पूर्ण

	/* now रुको क्रम the reply */
	अगर ((_base_रुको_क्रम_करोorbell_पूर्णांक(ioc, समयout))) अणु
		ioc_err(ioc, "doorbell handshake int failed (line=%d)\n",
			__LINE__);
		वापस -EFAULT;
	पूर्ण

	/* पढ़ो the first two 16-bits, it gives the total length of the reply */
	reply[0] = le16_to_cpu(ioc->base_पढ़ोl(&ioc->chip->Doorbell)
	    & MPI2_DOORBELL_DATA_MASK);
	ग_लिखोl(0, &ioc->chip->HostInterruptStatus);
	अगर ((_base_रुको_क्रम_करोorbell_पूर्णांक(ioc, 5))) अणु
		ioc_err(ioc, "doorbell handshake int failed (line=%d)\n",
			__LINE__);
		वापस -EFAULT;
	पूर्ण
	reply[1] = le16_to_cpu(ioc->base_पढ़ोl(&ioc->chip->Doorbell)
	    & MPI2_DOORBELL_DATA_MASK);
	ग_लिखोl(0, &ioc->chip->HostInterruptStatus);

	क्रम (i = 2; i < शेष_reply->MsgLength * 2; i++)  अणु
		अगर ((_base_रुको_क्रम_करोorbell_पूर्णांक(ioc, 5))) अणु
			ioc_err(ioc, "doorbell handshake int failed (line=%d)\n",
				__LINE__);
			वापस -EFAULT;
		पूर्ण
		अगर (i >=  reply_bytes/2) /* overflow हाल */
			ioc->base_पढ़ोl(&ioc->chip->Doorbell);
		अन्यथा
			reply[i] = le16_to_cpu(
			    ioc->base_पढ़ोl(&ioc->chip->Doorbell)
			    & MPI2_DOORBELL_DATA_MASK);
		ग_लिखोl(0, &ioc->chip->HostInterruptStatus);
	पूर्ण

	_base_रुको_क्रम_करोorbell_पूर्णांक(ioc, 5);
	अगर (_base_रुको_क्रम_करोorbell_not_used(ioc, 5) != 0) अणु
		dhsprपूर्णांकk(ioc,
			  ioc_info(ioc, "doorbell is in use (line=%d)\n",
				   __LINE__));
	पूर्ण
	ग_लिखोl(0, &ioc->chip->HostInterruptStatus);

	अगर (ioc->logging_level & MPT_DEBUG_INIT) अणु
		mfp = (__le32 *)reply;
		pr_info("\toffset:data\n");
		क्रम (i = 0; i < reply_bytes/4; i++)
			ioc_info(ioc, "\t[0x%02x]:%08x\n", i*4,
			    le32_to_cpu(mfp[i]));
	पूर्ण
	वापस 0;
पूर्ण

/**
 * mpt3sas_base_sas_iounit_control - send sas iounit control to FW
 * @ioc: per adapter object
 * @mpi_reply: the reply payload from FW
 * @mpi_request: the request payload sent to FW
 *
 * The SAS IO Unit Control Request message allows the host to perक्रमm low-level
 * operations, such as resets on the PHYs of the IO Unit, also allows the host
 * to obtain the IOC asचिन्हित device handles क्रम a device अगर it has other
 * identअगरying inक्रमmation about the device, in addition allows the host to
 * हटाओ IOC resources associated with the device.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_base_sas_iounit_control(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2SasIoUnitControlReply_t *mpi_reply,
	Mpi2SasIoUnitControlRequest_t *mpi_request)
अणु
	u16 smid;
	u8 issue_reset = 0;
	पूर्णांक rc;
	व्योम *request;

	dinitprपूर्णांकk(ioc, ioc_info(ioc, "%s\n", __func__));

	mutex_lock(&ioc->base_cmds.mutex);

	अगर (ioc->base_cmds.status != MPT3_CMD_NOT_USED) अणु
		ioc_err(ioc, "%s: base_cmd in use\n", __func__);
		rc = -EAGAIN;
		जाओ out;
	पूर्ण

	rc = mpt3sas_रुको_क्रम_ioc(ioc, IOC_OPERATIONAL_WAIT_COUNT);
	अगर (rc)
		जाओ out;

	smid = mpt3sas_base_get_smid(ioc, ioc->base_cb_idx);
	अगर (!smid) अणु
		ioc_err(ioc, "%s: failed obtaining a smid\n", __func__);
		rc = -EAGAIN;
		जाओ out;
	पूर्ण

	rc = 0;
	ioc->base_cmds.status = MPT3_CMD_PENDING;
	request = mpt3sas_base_get_msg_frame(ioc, smid);
	ioc->base_cmds.smid = smid;
	स_नकल(request, mpi_request, माप(Mpi2SasIoUnitControlRequest_t));
	अगर (mpi_request->Operation == MPI2_SAS_OP_PHY_HARD_RESET ||
	    mpi_request->Operation == MPI2_SAS_OP_PHY_LINK_RESET)
		ioc->ioc_link_reset_in_progress = 1;
	init_completion(&ioc->base_cmds.करोne);
	ioc->put_smid_शेष(ioc, smid);
	रुको_क्रम_completion_समयout(&ioc->base_cmds.करोne,
	    msecs_to_jअगरfies(10000));
	अगर ((mpi_request->Operation == MPI2_SAS_OP_PHY_HARD_RESET ||
	    mpi_request->Operation == MPI2_SAS_OP_PHY_LINK_RESET) &&
	    ioc->ioc_link_reset_in_progress)
		ioc->ioc_link_reset_in_progress = 0;
	अगर (!(ioc->base_cmds.status & MPT3_CMD_COMPLETE)) अणु
		mpt3sas_check_cmd_समयout(ioc, ioc->base_cmds.status,
		    mpi_request, माप(Mpi2SasIoUnitControlRequest_t)/4,
		    issue_reset);
		जाओ issue_host_reset;
	पूर्ण
	अगर (ioc->base_cmds.status & MPT3_CMD_REPLY_VALID)
		स_नकल(mpi_reply, ioc->base_cmds.reply,
		    माप(Mpi2SasIoUnitControlReply_t));
	अन्यथा
		स_रखो(mpi_reply, 0, माप(Mpi2SasIoUnitControlReply_t));
	ioc->base_cmds.status = MPT3_CMD_NOT_USED;
	जाओ out;

 issue_host_reset:
	अगर (issue_reset)
		mpt3sas_base_hard_reset_handler(ioc, FORCE_BIG_HAMMER);
	ioc->base_cmds.status = MPT3_CMD_NOT_USED;
	rc = -EFAULT;
 out:
	mutex_unlock(&ioc->base_cmds.mutex);
	वापस rc;
पूर्ण

/**
 * mpt3sas_base_scsi_enclosure_processor - sending request to sep device
 * @ioc: per adapter object
 * @mpi_reply: the reply payload from FW
 * @mpi_request: the request payload sent to FW
 *
 * The SCSI Enclosure Processor request message causes the IOC to
 * communicate with SES devices to control LED status संकेतs.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_base_scsi_enclosure_processor(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2SepReply_t *mpi_reply, Mpi2SepRequest_t *mpi_request)
अणु
	u16 smid;
	u8 issue_reset = 0;
	पूर्णांक rc;
	व्योम *request;

	dinitprपूर्णांकk(ioc, ioc_info(ioc, "%s\n", __func__));

	mutex_lock(&ioc->base_cmds.mutex);

	अगर (ioc->base_cmds.status != MPT3_CMD_NOT_USED) अणु
		ioc_err(ioc, "%s: base_cmd in use\n", __func__);
		rc = -EAGAIN;
		जाओ out;
	पूर्ण

	rc = mpt3sas_रुको_क्रम_ioc(ioc, IOC_OPERATIONAL_WAIT_COUNT);
	अगर (rc)
		जाओ out;

	smid = mpt3sas_base_get_smid(ioc, ioc->base_cb_idx);
	अगर (!smid) अणु
		ioc_err(ioc, "%s: failed obtaining a smid\n", __func__);
		rc = -EAGAIN;
		जाओ out;
	पूर्ण

	rc = 0;
	ioc->base_cmds.status = MPT3_CMD_PENDING;
	request = mpt3sas_base_get_msg_frame(ioc, smid);
	ioc->base_cmds.smid = smid;
	स_रखो(request, 0, ioc->request_sz);
	स_नकल(request, mpi_request, माप(Mpi2SepReply_t));
	init_completion(&ioc->base_cmds.करोne);
	ioc->put_smid_शेष(ioc, smid);
	रुको_क्रम_completion_समयout(&ioc->base_cmds.करोne,
	    msecs_to_jअगरfies(10000));
	अगर (!(ioc->base_cmds.status & MPT3_CMD_COMPLETE)) अणु
		mpt3sas_check_cmd_समयout(ioc,
		    ioc->base_cmds.status, mpi_request,
		    माप(Mpi2SepRequest_t)/4, issue_reset);
		जाओ issue_host_reset;
	पूर्ण
	अगर (ioc->base_cmds.status & MPT3_CMD_REPLY_VALID)
		स_नकल(mpi_reply, ioc->base_cmds.reply,
		    माप(Mpi2SepReply_t));
	अन्यथा
		स_रखो(mpi_reply, 0, माप(Mpi2SepReply_t));
	ioc->base_cmds.status = MPT3_CMD_NOT_USED;
	जाओ out;

 issue_host_reset:
	अगर (issue_reset)
		mpt3sas_base_hard_reset_handler(ioc, FORCE_BIG_HAMMER);
	ioc->base_cmds.status = MPT3_CMD_NOT_USED;
	rc = -EFAULT;
 out:
	mutex_unlock(&ioc->base_cmds.mutex);
	वापस rc;
पूर्ण

/**
 * _base_get_port_facts - obtain port facts reply and save in ioc
 * @ioc: per adapter object
 * @port: ?
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_base_get_port_facts(काष्ठा MPT3SAS_ADAPTER *ioc, पूर्णांक port)
अणु
	Mpi2PortFactsRequest_t mpi_request;
	Mpi2PortFactsReply_t mpi_reply;
	काष्ठा mpt3sas_port_facts *pfacts;
	पूर्णांक mpi_reply_sz, mpi_request_sz, r;

	dinitprपूर्णांकk(ioc, ioc_info(ioc, "%s\n", __func__));

	mpi_reply_sz = माप(Mpi2PortFactsReply_t);
	mpi_request_sz = माप(Mpi2PortFactsRequest_t);
	स_रखो(&mpi_request, 0, mpi_request_sz);
	mpi_request.Function = MPI2_FUNCTION_PORT_FACTS;
	mpi_request.PortNumber = port;
	r = _base_handshake_req_reply_रुको(ioc, mpi_request_sz,
	    (u32 *)&mpi_request, mpi_reply_sz, (u16 *)&mpi_reply, 5);

	अगर (r != 0) अणु
		ioc_err(ioc, "%s: handshake failed (r=%d)\n", __func__, r);
		वापस r;
	पूर्ण

	pfacts = &ioc->pfacts[port];
	स_रखो(pfacts, 0, माप(काष्ठा mpt3sas_port_facts));
	pfacts->PortNumber = mpi_reply.PortNumber;
	pfacts->VP_ID = mpi_reply.VP_ID;
	pfacts->VF_ID = mpi_reply.VF_ID;
	pfacts->MaxPostedCmdBuffers =
	    le16_to_cpu(mpi_reply.MaxPostedCmdBuffers);

	वापस 0;
पूर्ण

/**
 * _base_रुको_क्रम_iocstate - Wait until the card is in READY or OPERATIONAL
 * @ioc: per adapter object
 * @समयout:
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_base_रुको_क्रम_iocstate(काष्ठा MPT3SAS_ADAPTER *ioc, पूर्णांक समयout)
अणु
	u32 ioc_state;
	पूर्णांक rc;

	dinitprपूर्णांकk(ioc, ioc_info(ioc, "%s\n", __func__));

	अगर (ioc->pci_error_recovery) अणु
		dfailprपूर्णांकk(ioc,
			    ioc_info(ioc, "%s: host in pci error recovery\n",
				     __func__));
		वापस -EFAULT;
	पूर्ण

	ioc_state = mpt3sas_base_get_iocstate(ioc, 0);
	dhsprपूर्णांकk(ioc,
		  ioc_info(ioc, "%s: ioc_state(0x%08x)\n",
			   __func__, ioc_state));

	अगर (((ioc_state & MPI2_IOC_STATE_MASK) == MPI2_IOC_STATE_READY) ||
	    (ioc_state & MPI2_IOC_STATE_MASK) == MPI2_IOC_STATE_OPERATIONAL)
		वापस 0;

	अगर (ioc_state & MPI2_DOORBELL_USED) अणु
		dhsprपूर्णांकk(ioc, ioc_info(ioc, "unexpected doorbell active!\n"));
		जाओ issue_diag_reset;
	पूर्ण

	अगर ((ioc_state & MPI2_IOC_STATE_MASK) == MPI2_IOC_STATE_FAULT) अणु
		mpt3sas_prपूर्णांक_fault_code(ioc, ioc_state &
		    MPI2_DOORBELL_DATA_MASK);
		जाओ issue_diag_reset;
	पूर्ण अन्यथा अगर ((ioc_state & MPI2_IOC_STATE_MASK) ==
	    MPI2_IOC_STATE_COREDUMP) अणु
		ioc_info(ioc,
		    "%s: Skipping the diag reset here. (ioc_state=0x%x)\n",
		    __func__, ioc_state);
		वापस -EFAULT;
	पूर्ण

	ioc_state = _base_रुको_on_iocstate(ioc, MPI2_IOC_STATE_READY, समयout);
	अगर (ioc_state) अणु
		dfailprपूर्णांकk(ioc,
			    ioc_info(ioc, "%s: failed going to ready state (ioc_state=0x%x)\n",
				     __func__, ioc_state));
		वापस -EFAULT;
	पूर्ण

 issue_diag_reset:
	rc = _base_diag_reset(ioc);
	वापस rc;
पूर्ण

/**
 * _base_get_ioc_facts - obtain ioc facts reply and save in ioc
 * @ioc: per adapter object
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_base_get_ioc_facts(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	Mpi2IOCFactsRequest_t mpi_request;
	Mpi2IOCFactsReply_t mpi_reply;
	काष्ठा mpt3sas_facts *facts;
	पूर्णांक mpi_reply_sz, mpi_request_sz, r;

	dinitprपूर्णांकk(ioc, ioc_info(ioc, "%s\n", __func__));

	r = _base_रुको_क्रम_iocstate(ioc, 10);
	अगर (r) अणु
		dfailprपूर्णांकk(ioc,
			    ioc_info(ioc, "%s: failed getting to correct state\n",
				     __func__));
		वापस r;
	पूर्ण
	mpi_reply_sz = माप(Mpi2IOCFactsReply_t);
	mpi_request_sz = माप(Mpi2IOCFactsRequest_t);
	स_रखो(&mpi_request, 0, mpi_request_sz);
	mpi_request.Function = MPI2_FUNCTION_IOC_FACTS;
	r = _base_handshake_req_reply_रुको(ioc, mpi_request_sz,
	    (u32 *)&mpi_request, mpi_reply_sz, (u16 *)&mpi_reply, 5);

	अगर (r != 0) अणु
		ioc_err(ioc, "%s: handshake failed (r=%d)\n", __func__, r);
		वापस r;
	पूर्ण

	facts = &ioc->facts;
	स_रखो(facts, 0, माप(काष्ठा mpt3sas_facts));
	facts->MsgVersion = le16_to_cpu(mpi_reply.MsgVersion);
	facts->HeaderVersion = le16_to_cpu(mpi_reply.HeaderVersion);
	facts->VP_ID = mpi_reply.VP_ID;
	facts->VF_ID = mpi_reply.VF_ID;
	facts->IOCExceptions = le16_to_cpu(mpi_reply.IOCExceptions);
	facts->MaxChainDepth = mpi_reply.MaxChainDepth;
	facts->WhoInit = mpi_reply.WhoInit;
	facts->NumberOfPorts = mpi_reply.NumberOfPorts;
	facts->MaxMSIxVectors = mpi_reply.MaxMSIxVectors;
	अगर (ioc->msix_enable && (facts->MaxMSIxVectors <=
	    MAX_COMBINED_MSIX_VECTORS(ioc->is_gen35_ioc)))
		ioc->combined_reply_queue = 0;
	facts->RequestCredit = le16_to_cpu(mpi_reply.RequestCredit);
	facts->MaxReplyDescriptorPostQueueDepth =
	    le16_to_cpu(mpi_reply.MaxReplyDescriptorPostQueueDepth);
	facts->ProductID = le16_to_cpu(mpi_reply.ProductID);
	facts->IOCCapabilities = le32_to_cpu(mpi_reply.IOCCapabilities);
	अगर ((facts->IOCCapabilities & MPI2_IOCFACTS_CAPABILITY_INTEGRATED_RAID))
		ioc->ir_firmware = 1;
	अगर ((facts->IOCCapabilities &
	      MPI2_IOCFACTS_CAPABILITY_RDPQ_ARRAY_CAPABLE) && (!reset_devices))
		ioc->rdpq_array_capable = 1;
	अगर ((facts->IOCCapabilities & MPI26_IOCFACTS_CAPABILITY_ATOMIC_REQ)
	    && ioc->is_aero_ioc)
		ioc->atomic_desc_capable = 1;
	facts->FWVersion.Word = le32_to_cpu(mpi_reply.FWVersion.Word);
	facts->IOCRequestFrameSize =
	    le16_to_cpu(mpi_reply.IOCRequestFrameSize);
	अगर (ioc->hba_mpi_version_beदीर्घed != MPI2_VERSION) अणु
		facts->IOCMaxChainSegmentSize =
			le16_to_cpu(mpi_reply.IOCMaxChainSegmentSize);
	पूर्ण
	facts->MaxInitiators = le16_to_cpu(mpi_reply.MaxInitiators);
	facts->MaxTarमाला_लो = le16_to_cpu(mpi_reply.MaxTarमाला_लो);
	ioc->shost->max_id = -1;
	facts->MaxSasExpanders = le16_to_cpu(mpi_reply.MaxSasExpanders);
	facts->MaxEnclosures = le16_to_cpu(mpi_reply.MaxEnclosures);
	facts->ProtocolFlags = le16_to_cpu(mpi_reply.ProtocolFlags);
	facts->HighPriorityCredit =
	    le16_to_cpu(mpi_reply.HighPriorityCredit);
	facts->ReplyFrameSize = mpi_reply.ReplyFrameSize;
	facts->MaxDevHandle = le16_to_cpu(mpi_reply.MaxDevHandle);
	facts->CurrentHostPageSize = mpi_reply.CurrentHostPageSize;

	/*
	 * Get the Page Size from IOC Facts. If it's 0, शेष to 4k.
	 */
	ioc->page_size = 1 << facts->CurrentHostPageSize;
	अगर (ioc->page_size == 1) अणु
		ioc_info(ioc, "CurrentHostPageSize is 0: Setting default host page size to 4k\n");
		ioc->page_size = 1 << MPT3SAS_HOST_PAGE_SIZE_4K;
	पूर्ण
	dinitprपूर्णांकk(ioc,
		    ioc_info(ioc, "CurrentHostPageSize(%d)\n",
			     facts->CurrentHostPageSize));

	dinitprपूर्णांकk(ioc,
		    ioc_info(ioc, "hba queue depth(%d), max chains per io(%d)\n",
			     facts->RequestCredit, facts->MaxChainDepth));
	dinitprपूर्णांकk(ioc,
		    ioc_info(ioc, "request frame size(%d), reply frame size(%d)\n",
			     facts->IOCRequestFrameSize * 4,
			     facts->ReplyFrameSize * 4));
	वापस 0;
पूर्ण

/**
 * _base_send_ioc_init - send ioc_init to firmware
 * @ioc: per adapter object
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_base_send_ioc_init(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	Mpi2IOCInitRequest_t mpi_request;
	Mpi2IOCInitReply_t mpi_reply;
	पूर्णांक i, r = 0;
	kसमय_प्रकार current_समय;
	u16 ioc_status;
	u32 reply_post_मुक्त_array_sz = 0;

	dinitprपूर्णांकk(ioc, ioc_info(ioc, "%s\n", __func__));

	स_रखो(&mpi_request, 0, माप(Mpi2IOCInitRequest_t));
	mpi_request.Function = MPI2_FUNCTION_IOC_INIT;
	mpi_request.WhoInit = MPI2_WHOINIT_HOST_DRIVER;
	mpi_request.VF_ID = 0; /* TODO */
	mpi_request.VP_ID = 0;
	mpi_request.MsgVersion = cpu_to_le16(ioc->hba_mpi_version_beदीर्घed);
	mpi_request.HeaderVersion = cpu_to_le16(MPI2_HEADER_VERSION);
	mpi_request.HostPageSize = MPT3SAS_HOST_PAGE_SIZE_4K;

	अगर (_base_is_controller_msix_enabled(ioc))
		mpi_request.HostMSIxVectors = ioc->reply_queue_count;
	mpi_request.SystemRequestFrameSize = cpu_to_le16(ioc->request_sz/4);
	mpi_request.ReplyDescriptorPostQueueDepth =
	    cpu_to_le16(ioc->reply_post_queue_depth);
	mpi_request.ReplyFreeQueueDepth =
	    cpu_to_le16(ioc->reply_मुक्त_queue_depth);

	mpi_request.SenseBufferAddressHigh =
	    cpu_to_le32((u64)ioc->sense_dma >> 32);
	mpi_request.SystemReplyAddressHigh =
	    cpu_to_le32((u64)ioc->reply_dma >> 32);
	mpi_request.SystemRequestFrameBaseAddress =
	    cpu_to_le64((u64)ioc->request_dma);
	mpi_request.ReplyFreeQueueAddress =
	    cpu_to_le64((u64)ioc->reply_मुक्त_dma);

	अगर (ioc->rdpq_array_enable) अणु
		reply_post_मुक्त_array_sz = ioc->reply_queue_count *
		    माप(Mpi2IOCInitRDPQArrayEntry);
		स_रखो(ioc->reply_post_मुक्त_array, 0, reply_post_मुक्त_array_sz);
		क्रम (i = 0; i < ioc->reply_queue_count; i++)
			ioc->reply_post_मुक्त_array[i].RDPQBaseAddress =
			    cpu_to_le64(
				(u64)ioc->reply_post[i].reply_post_मुक्त_dma);
		mpi_request.MsgFlags = MPI2_IOCINIT_MSGFLAG_RDPQ_ARRAY_MODE;
		mpi_request.ReplyDescriptorPostQueueAddress =
		    cpu_to_le64((u64)ioc->reply_post_मुक्त_array_dma);
	पूर्ण अन्यथा अणु
		mpi_request.ReplyDescriptorPostQueueAddress =
		    cpu_to_le64((u64)ioc->reply_post[0].reply_post_मुक्त_dma);
	पूर्ण

	/*
	 * Set the flag to enable CoreDump state feature in IOC firmware.
	 */
	mpi_request.ConfigurationFlags |=
	    cpu_to_le16(MPI26_IOCINIT_CFGFLAGS_COREDUMP_ENABLE);

	/* This समय stamp specअगरies number of milliseconds
	 * since epoch ~ midnight January 1, 1970.
	 */
	current_समय = kसमय_get_real();
	mpi_request.TimeStamp = cpu_to_le64(kसमय_प्रकारo_ms(current_समय));

	अगर (ioc->logging_level & MPT_DEBUG_INIT) अणु
		__le32 *mfp;
		पूर्णांक i;

		mfp = (__le32 *)&mpi_request;
		ioc_info(ioc, "\toffset:data\n");
		क्रम (i = 0; i < माप(Mpi2IOCInitRequest_t)/4; i++)
			ioc_info(ioc, "\t[0x%02x]:%08x\n", i*4,
			    le32_to_cpu(mfp[i]));
	पूर्ण

	r = _base_handshake_req_reply_रुको(ioc,
	    माप(Mpi2IOCInitRequest_t), (u32 *)&mpi_request,
	    माप(Mpi2IOCInitReply_t), (u16 *)&mpi_reply, 30);

	अगर (r != 0) अणु
		ioc_err(ioc, "%s: handshake failed (r=%d)\n", __func__, r);
		वापस r;
	पूर्ण

	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) & MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS ||
	    mpi_reply.IOCLogInfo) अणु
		ioc_err(ioc, "%s: failed\n", __func__);
		r = -EIO;
	पूर्ण

	/* Reset TimeSync Counter*/
	ioc->बारtamp_update_count = 0;
	वापस r;
पूर्ण

/**
 * mpt3sas_port_enable_करोne - command completion routine क्रम port enable
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @msix_index: MSIX table index supplied by the OS
 * @reply: reply message frame(lower 32bit addr)
 *
 * Return: 1 meaning mf should be मुक्तd from _base_पूर्णांकerrupt
 *          0 means the mf is मुक्तd from this function.
 */
u8
mpt3sas_port_enable_करोne(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid, u8 msix_index,
	u32 reply)
अणु
	MPI2DefaultReply_t *mpi_reply;
	u16 ioc_status;

	अगर (ioc->port_enable_cmds.status == MPT3_CMD_NOT_USED)
		वापस 1;

	mpi_reply = mpt3sas_base_get_reply_virt_addr(ioc, reply);
	अगर (!mpi_reply)
		वापस 1;

	अगर (mpi_reply->Function != MPI2_FUNCTION_PORT_ENABLE)
		वापस 1;

	ioc->port_enable_cmds.status &= ~MPT3_CMD_PENDING;
	ioc->port_enable_cmds.status |= MPT3_CMD_COMPLETE;
	ioc->port_enable_cmds.status |= MPT3_CMD_REPLY_VALID;
	स_नकल(ioc->port_enable_cmds.reply, mpi_reply, mpi_reply->MsgLength*4);
	ioc_status = le16_to_cpu(mpi_reply->IOCStatus) & MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS)
		ioc->port_enable_failed = 1;

	अगर (ioc->is_driver_loading) अणु
		अगर (ioc_status == MPI2_IOCSTATUS_SUCCESS) अणु
			mpt3sas_port_enable_complete(ioc);
			वापस 1;
		पूर्ण अन्यथा अणु
			ioc->start_scan_failed = ioc_status;
			ioc->start_scan = 0;
			वापस 1;
		पूर्ण
	पूर्ण
	complete(&ioc->port_enable_cmds.करोne);
	वापस 1;
पूर्ण

/**
 * _base_send_port_enable - send port_enable(discovery stuff) to firmware
 * @ioc: per adapter object
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_base_send_port_enable(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	Mpi2PortEnableRequest_t *mpi_request;
	Mpi2PortEnableReply_t *mpi_reply;
	पूर्णांक r = 0;
	u16 smid;
	u16 ioc_status;

	ioc_info(ioc, "sending port enable !!\n");

	अगर (ioc->port_enable_cmds.status & MPT3_CMD_PENDING) अणु
		ioc_err(ioc, "%s: internal command already in use\n", __func__);
		वापस -EAGAIN;
	पूर्ण

	smid = mpt3sas_base_get_smid(ioc, ioc->port_enable_cb_idx);
	अगर (!smid) अणु
		ioc_err(ioc, "%s: failed obtaining a smid\n", __func__);
		वापस -EAGAIN;
	पूर्ण

	ioc->port_enable_cmds.status = MPT3_CMD_PENDING;
	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	ioc->port_enable_cmds.smid = smid;
	स_रखो(mpi_request, 0, माप(Mpi2PortEnableRequest_t));
	mpi_request->Function = MPI2_FUNCTION_PORT_ENABLE;

	init_completion(&ioc->port_enable_cmds.करोne);
	ioc->put_smid_शेष(ioc, smid);
	रुको_क्रम_completion_समयout(&ioc->port_enable_cmds.करोne, 300*HZ);
	अगर (!(ioc->port_enable_cmds.status & MPT3_CMD_COMPLETE)) अणु
		ioc_err(ioc, "%s: timeout\n", __func__);
		_debug_dump_mf(mpi_request,
		    माप(Mpi2PortEnableRequest_t)/4);
		अगर (ioc->port_enable_cmds.status & MPT3_CMD_RESET)
			r = -EFAULT;
		अन्यथा
			r = -ETIME;
		जाओ out;
	पूर्ण

	mpi_reply = ioc->port_enable_cmds.reply;
	ioc_status = le16_to_cpu(mpi_reply->IOCStatus) & MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		ioc_err(ioc, "%s: failed with (ioc_status=0x%08x)\n",
			__func__, ioc_status);
		r = -EFAULT;
		जाओ out;
	पूर्ण

 out:
	ioc->port_enable_cmds.status = MPT3_CMD_NOT_USED;
	ioc_info(ioc, "port enable: %s\n", r == 0 ? "SUCCESS" : "FAILED");
	वापस r;
पूर्ण

/**
 * mpt3sas_port_enable - initiate firmware discovery (करोn't रुको क्रम reply)
 * @ioc: per adapter object
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_port_enable(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	Mpi2PortEnableRequest_t *mpi_request;
	u16 smid;

	ioc_info(ioc, "sending port enable !!\n");

	अगर (ioc->port_enable_cmds.status & MPT3_CMD_PENDING) अणु
		ioc_err(ioc, "%s: internal command already in use\n", __func__);
		वापस -EAGAIN;
	पूर्ण

	smid = mpt3sas_base_get_smid(ioc, ioc->port_enable_cb_idx);
	अगर (!smid) अणु
		ioc_err(ioc, "%s: failed obtaining a smid\n", __func__);
		वापस -EAGAIN;
	पूर्ण

	ioc->port_enable_cmds.status = MPT3_CMD_PENDING;
	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	ioc->port_enable_cmds.smid = smid;
	स_रखो(mpi_request, 0, माप(Mpi2PortEnableRequest_t));
	mpi_request->Function = MPI2_FUNCTION_PORT_ENABLE;

	ioc->put_smid_शेष(ioc, smid);
	वापस 0;
पूर्ण

/**
 * _base_determine_रुको_on_discovery - desposition
 * @ioc: per adapter object
 *
 * Decide whether to रुको on discovery to complete. Used to either
 * locate boot device, or report volumes ahead of physical devices.
 *
 * Return: 1 क्रम रुको, 0 क्रम करोn't रुको.
 */
अटल पूर्णांक
_base_determine_रुको_on_discovery(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	/* We रुको क्रम discovery to complete अगर IR firmware is loaded.
	 * The sas topology events arrive beक्रमe PD events, so we need समय to
	 * turn on the bit in ioc->pd_handles to indicate PD
	 * Also, it maybe required to report Volumes ahead of physical
	 * devices when MPI2_IOCPAGE8_IRFLAGS_LOW_VOLUME_MAPPING is set.
	 */
	अगर (ioc->ir_firmware)
		वापस 1;

	/* अगर no Bios, then we करोn't need to रुको */
	अगर (!ioc->bios_pg3.BiosVersion)
		वापस 0;

	/* Bios is present, then we drop करोwn here.
	 *
	 * If there any entries in the Bios Page 2, then we रुको
	 * क्रम discovery to complete.
	 */

	/* Current Boot Device */
	अगर ((ioc->bios_pg2.CurrentBootDeviceForm &
	    MPI2_BIOSPAGE2_FORM_MASK) ==
	    MPI2_BIOSPAGE2_FORM_NO_DEVICE_SPECIFIED &&
	/* Request Boot Device */
	   (ioc->bios_pg2.ReqBootDeviceForm &
	    MPI2_BIOSPAGE2_FORM_MASK) ==
	    MPI2_BIOSPAGE2_FORM_NO_DEVICE_SPECIFIED &&
	/* Alternate Request Boot Device */
	   (ioc->bios_pg2.ReqAltBootDeviceForm &
	    MPI2_BIOSPAGE2_FORM_MASK) ==
	    MPI2_BIOSPAGE2_FORM_NO_DEVICE_SPECIFIED)
		वापस 0;

	वापस 1;
पूर्ण

/**
 * _base_unmask_events - turn on notअगरication क्रम this event
 * @ioc: per adapter object
 * @event: firmware event
 *
 * The mask is stored in ioc->event_masks.
 */
अटल व्योम
_base_unmask_events(काष्ठा MPT3SAS_ADAPTER *ioc, u16 event)
अणु
	u32 desired_event;

	अगर (event >= 128)
		वापस;

	desired_event = (1 << (event % 32));

	अगर (event < 32)
		ioc->event_masks[0] &= ~desired_event;
	अन्यथा अगर (event < 64)
		ioc->event_masks[1] &= ~desired_event;
	अन्यथा अगर (event < 96)
		ioc->event_masks[2] &= ~desired_event;
	अन्यथा अगर (event < 128)
		ioc->event_masks[3] &= ~desired_event;
पूर्ण

/**
 * _base_event_notअगरication - send event notअगरication
 * @ioc: per adapter object
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_base_event_notअगरication(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	Mpi2EventNotअगरicationRequest_t *mpi_request;
	u16 smid;
	पूर्णांक r = 0;
	पूर्णांक i;

	dinitprपूर्णांकk(ioc, ioc_info(ioc, "%s\n", __func__));

	अगर (ioc->base_cmds.status & MPT3_CMD_PENDING) अणु
		ioc_err(ioc, "%s: internal command already in use\n", __func__);
		वापस -EAGAIN;
	पूर्ण

	smid = mpt3sas_base_get_smid(ioc, ioc->base_cb_idx);
	अगर (!smid) अणु
		ioc_err(ioc, "%s: failed obtaining a smid\n", __func__);
		वापस -EAGAIN;
	पूर्ण
	ioc->base_cmds.status = MPT3_CMD_PENDING;
	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	ioc->base_cmds.smid = smid;
	स_रखो(mpi_request, 0, माप(Mpi2EventNotअगरicationRequest_t));
	mpi_request->Function = MPI2_FUNCTION_EVENT_NOTIFICATION;
	mpi_request->VF_ID = 0; /* TODO */
	mpi_request->VP_ID = 0;
	क्रम (i = 0; i < MPI2_EVENT_NOTIFY_EVENTMASK_WORDS; i++)
		mpi_request->EventMasks[i] =
		    cpu_to_le32(ioc->event_masks[i]);
	init_completion(&ioc->base_cmds.करोne);
	ioc->put_smid_शेष(ioc, smid);
	रुको_क्रम_completion_समयout(&ioc->base_cmds.करोne, 30*HZ);
	अगर (!(ioc->base_cmds.status & MPT3_CMD_COMPLETE)) अणु
		ioc_err(ioc, "%s: timeout\n", __func__);
		_debug_dump_mf(mpi_request,
		    माप(Mpi2EventNotअगरicationRequest_t)/4);
		अगर (ioc->base_cmds.status & MPT3_CMD_RESET)
			r = -EFAULT;
		अन्यथा
			r = -ETIME;
	पूर्ण अन्यथा
		dinitprपूर्णांकk(ioc, ioc_info(ioc, "%s: complete\n", __func__));
	ioc->base_cmds.status = MPT3_CMD_NOT_USED;
	वापस r;
पूर्ण

/**
 * mpt3sas_base_validate_event_type - validating event types
 * @ioc: per adapter object
 * @event_type: firmware event
 *
 * This will turn on firmware event notअगरication when application
 * ask क्रम that event. We करोn't mask events that are alपढ़ोy enabled.
 */
व्योम
mpt3sas_base_validate_event_type(काष्ठा MPT3SAS_ADAPTER *ioc, u32 *event_type)
अणु
	पूर्णांक i, j;
	u32 event_mask, desired_event;
	u8 send_update_to_fw;

	क्रम (i = 0, send_update_to_fw = 0; i <
	    MPI2_EVENT_NOTIFY_EVENTMASK_WORDS; i++) अणु
		event_mask = ~event_type[i];
		desired_event = 1;
		क्रम (j = 0; j < 32; j++) अणु
			अगर (!(event_mask & desired_event) &&
			    (ioc->event_masks[i] & desired_event)) अणु
				ioc->event_masks[i] &= ~desired_event;
				send_update_to_fw = 1;
			पूर्ण
			desired_event = (desired_event << 1);
		पूर्ण
	पूर्ण

	अगर (!send_update_to_fw)
		वापस;

	mutex_lock(&ioc->base_cmds.mutex);
	_base_event_notअगरication(ioc);
	mutex_unlock(&ioc->base_cmds.mutex);
पूर्ण

/**
 * _base_diag_reset - the "big hammer" start of day reset
 * @ioc: per adapter object
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_base_diag_reset(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	u32 host_diagnostic;
	u32 ioc_state;
	u32 count;
	u32 hcb_size;

	ioc_info(ioc, "sending diag reset !!\n");

	pci_cfg_access_lock(ioc->pdev);

	drsprपूर्णांकk(ioc, ioc_info(ioc, "clear interrupts\n"));

	count = 0;
	करो अणु
		/* Write magic sequence to WriteSequence रेजिस्टर
		 * Loop until in diagnostic mode
		 */
		drsprपूर्णांकk(ioc, ioc_info(ioc, "write magic sequence\n"));
		ग_लिखोl(MPI2_WRSEQ_FLUSH_KEY_VALUE, &ioc->chip->WriteSequence);
		ग_लिखोl(MPI2_WRSEQ_1ST_KEY_VALUE, &ioc->chip->WriteSequence);
		ग_लिखोl(MPI2_WRSEQ_2ND_KEY_VALUE, &ioc->chip->WriteSequence);
		ग_लिखोl(MPI2_WRSEQ_3RD_KEY_VALUE, &ioc->chip->WriteSequence);
		ग_लिखोl(MPI2_WRSEQ_4TH_KEY_VALUE, &ioc->chip->WriteSequence);
		ग_लिखोl(MPI2_WRSEQ_5TH_KEY_VALUE, &ioc->chip->WriteSequence);
		ग_लिखोl(MPI2_WRSEQ_6TH_KEY_VALUE, &ioc->chip->WriteSequence);

		/* रुको 100 msec */
		msleep(100);

		अगर (count++ > 20) अणु
			ioc_info(ioc,
			    "Stop writing magic sequence after 20 retries\n");
			_base_dump_reg_set(ioc);
			जाओ out;
		पूर्ण

		host_diagnostic = ioc->base_पढ़ोl(&ioc->chip->HostDiagnostic);
		drsprपूर्णांकk(ioc,
			  ioc_info(ioc, "wrote magic sequence: count(%d), host_diagnostic(0x%08x)\n",
				   count, host_diagnostic));

	पूर्ण जबतक ((host_diagnostic & MPI2_DIAG_DIAG_WRITE_ENABLE) == 0);

	hcb_size = ioc->base_पढ़ोl(&ioc->chip->HCBSize);

	drsprपूर्णांकk(ioc, ioc_info(ioc, "diag reset: issued\n"));
	ग_लिखोl(host_diagnostic | MPI2_DIAG_RESET_ADAPTER,
	     &ioc->chip->HostDiagnostic);

	/*This delay allows the chip PCIe hardware समय to finish reset tasks*/
	msleep(MPI2_HARD_RESET_PCIE_FIRST_READ_DELAY_MICRO_SEC/1000);

	/* Approximately 300 second max रुको */
	क्रम (count = 0; count < (300000000 /
		MPI2_HARD_RESET_PCIE_SECOND_READ_DELAY_MICRO_SEC); count++) अणु

		host_diagnostic = ioc->base_पढ़ोl(&ioc->chip->HostDiagnostic);

		अगर (host_diagnostic == 0xFFFFFFFF) अणु
			ioc_info(ioc,
			    "Invalid host diagnostic register value\n");
			_base_dump_reg_set(ioc);
			जाओ out;
		पूर्ण
		अगर (!(host_diagnostic & MPI2_DIAG_RESET_ADAPTER))
			अवरोध;

		msleep(MPI2_HARD_RESET_PCIE_SECOND_READ_DELAY_MICRO_SEC / 1000);
	पूर्ण

	अगर (host_diagnostic & MPI2_DIAG_HCB_MODE) अणु

		drsprपूर्णांकk(ioc,
			  ioc_info(ioc, "restart the adapter assuming the HCB Address points to good F/W\n"));
		host_diagnostic &= ~MPI2_DIAG_BOOT_DEVICE_SELECT_MASK;
		host_diagnostic |= MPI2_DIAG_BOOT_DEVICE_SELECT_HCDW;
		ग_लिखोl(host_diagnostic, &ioc->chip->HostDiagnostic);

		drsprपूर्णांकk(ioc, ioc_info(ioc, "re-enable the HCDW\n"));
		ग_लिखोl(hcb_size | MPI2_HCB_SIZE_HCB_ENABLE,
		    &ioc->chip->HCBSize);
	पूर्ण

	drsprपूर्णांकk(ioc, ioc_info(ioc, "restart the adapter\n"));
	ग_लिखोl(host_diagnostic & ~MPI2_DIAG_HOLD_IOC_RESET,
	    &ioc->chip->HostDiagnostic);

	drsprपूर्णांकk(ioc,
		  ioc_info(ioc, "disable writes to the diagnostic register\n"));
	ग_लिखोl(MPI2_WRSEQ_FLUSH_KEY_VALUE, &ioc->chip->WriteSequence);

	drsprपूर्णांकk(ioc, ioc_info(ioc, "Wait for FW to go to the READY state\n"));
	ioc_state = _base_रुको_on_iocstate(ioc, MPI2_IOC_STATE_READY, 20);
	अगर (ioc_state) अणु
		ioc_err(ioc, "%s: failed going to ready state (ioc_state=0x%x)\n",
			__func__, ioc_state);
		_base_dump_reg_set(ioc);
		जाओ out;
	पूर्ण

	pci_cfg_access_unlock(ioc->pdev);
	ioc_info(ioc, "diag reset: SUCCESS\n");
	वापस 0;

 out:
	pci_cfg_access_unlock(ioc->pdev);
	ioc_err(ioc, "diag reset: FAILED\n");
	वापस -EFAULT;
पूर्ण

/**
 * _base_make_ioc_पढ़ोy - put controller in READY state
 * @ioc: per adapter object
 * @type: FORCE_BIG_HAMMER or SOFT_RESET
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_base_make_ioc_पढ़ोy(काष्ठा MPT3SAS_ADAPTER *ioc, क्रमागत reset_type type)
अणु
	u32 ioc_state;
	पूर्णांक rc;
	पूर्णांक count;

	dinitprपूर्णांकk(ioc, ioc_info(ioc, "%s\n", __func__));

	अगर (ioc->pci_error_recovery)
		वापस 0;

	ioc_state = mpt3sas_base_get_iocstate(ioc, 0);
	dhsprपूर्णांकk(ioc,
		  ioc_info(ioc, "%s: ioc_state(0x%08x)\n",
			   __func__, ioc_state));

	/* अगर in RESET state, it should move to READY state लघुly */
	count = 0;
	अगर ((ioc_state & MPI2_IOC_STATE_MASK) == MPI2_IOC_STATE_RESET) अणु
		जबतक ((ioc_state & MPI2_IOC_STATE_MASK) !=
		    MPI2_IOC_STATE_READY) अणु
			अगर (count++ == 10) अणु
				ioc_err(ioc, "%s: failed going to ready state (ioc_state=0x%x)\n",
					__func__, ioc_state);
				वापस -EFAULT;
			पूर्ण
			ssleep(1);
			ioc_state = mpt3sas_base_get_iocstate(ioc, 0);
		पूर्ण
	पूर्ण

	अगर ((ioc_state & MPI2_IOC_STATE_MASK) == MPI2_IOC_STATE_READY)
		वापस 0;

	अगर (ioc_state & MPI2_DOORBELL_USED) अणु
		ioc_info(ioc, "unexpected doorbell active!\n");
		जाओ issue_diag_reset;
	पूर्ण

	अगर ((ioc_state & MPI2_IOC_STATE_MASK) == MPI2_IOC_STATE_FAULT) अणु
		mpt3sas_prपूर्णांक_fault_code(ioc, ioc_state &
		    MPI2_DOORBELL_DATA_MASK);
		जाओ issue_diag_reset;
	पूर्ण

	अगर ((ioc_state & MPI2_IOC_STATE_MASK) == MPI2_IOC_STATE_COREDUMP) अणु
		/*
		 * अगर host reset is invoked जबतक watch करोg thपढ़ो is रुकोing
		 * क्रम IOC state to be changed to Fault state then driver has
		 * to रुको here क्रम CoreDump state to clear otherwise reset
		 * will be issued to the FW and FW move the IOC state to
		 * reset state without copying the FW logs to coredump region.
		 */
		अगर (ioc->ioc_coredump_loop != MPT3SAS_COREDUMP_LOOP_DONE) अणु
			mpt3sas_prपूर्णांक_coredump_info(ioc, ioc_state &
			    MPI2_DOORBELL_DATA_MASK);
			mpt3sas_base_रुको_क्रम_coredump_completion(ioc,
			    __func__);
		पूर्ण
		जाओ issue_diag_reset;
	पूर्ण

	अगर (type == FORCE_BIG_HAMMER)
		जाओ issue_diag_reset;

	अगर ((ioc_state & MPI2_IOC_STATE_MASK) == MPI2_IOC_STATE_OPERATIONAL)
		अगर (!(_base_send_ioc_reset(ioc,
		    MPI2_FUNCTION_IOC_MESSAGE_UNIT_RESET, 15))) अणु
			वापस 0;
	पूर्ण

 issue_diag_reset:
	rc = _base_diag_reset(ioc);
	वापस rc;
पूर्ण

/**
 * _base_make_ioc_operational - put controller in OPERATIONAL state
 * @ioc: per adapter object
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_base_make_ioc_operational(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	पूर्णांक r, i, index, rc;
	अचिन्हित दीर्घ	flags;
	u32 reply_address;
	u16 smid;
	काष्ठा _tr_list *delayed_tr, *delayed_tr_next;
	काष्ठा _sc_list *delayed_sc, *delayed_sc_next;
	काष्ठा _event_ack_list *delayed_event_ack, *delayed_event_ack_next;
	u8 hide_flag;
	काष्ठा adapter_reply_queue *reply_q;
	Mpi2ReplyDescriptorsUnion_t *reply_post_मुक्त_contig;

	dinitprपूर्णांकk(ioc, ioc_info(ioc, "%s\n", __func__));

	/* clean the delayed target reset list */
	list_क्रम_each_entry_safe(delayed_tr, delayed_tr_next,
	    &ioc->delayed_tr_list, list) अणु
		list_del(&delayed_tr->list);
		kमुक्त(delayed_tr);
	पूर्ण


	list_क्रम_each_entry_safe(delayed_tr, delayed_tr_next,
	    &ioc->delayed_tr_volume_list, list) अणु
		list_del(&delayed_tr->list);
		kमुक्त(delayed_tr);
	पूर्ण

	list_क्रम_each_entry_safe(delayed_sc, delayed_sc_next,
	    &ioc->delayed_sc_list, list) अणु
		list_del(&delayed_sc->list);
		kमुक्त(delayed_sc);
	पूर्ण

	list_क्रम_each_entry_safe(delayed_event_ack, delayed_event_ack_next,
	    &ioc->delayed_event_ack_list, list) अणु
		list_del(&delayed_event_ack->list);
		kमुक्त(delayed_event_ack);
	पूर्ण

	spin_lock_irqsave(&ioc->scsi_lookup_lock, flags);

	/* hi-priority queue */
	INIT_LIST_HEAD(&ioc->hpr_मुक्त_list);
	smid = ioc->hi_priority_smid;
	क्रम (i = 0; i < ioc->hi_priority_depth; i++, smid++) अणु
		ioc->hpr_lookup[i].cb_idx = 0xFF;
		ioc->hpr_lookup[i].smid = smid;
		list_add_tail(&ioc->hpr_lookup[i].tracker_list,
		    &ioc->hpr_मुक्त_list);
	पूर्ण

	/* पूर्णांकernal queue */
	INIT_LIST_HEAD(&ioc->पूर्णांकernal_मुक्त_list);
	smid = ioc->पूर्णांकernal_smid;
	क्रम (i = 0; i < ioc->पूर्णांकernal_depth; i++, smid++) अणु
		ioc->पूर्णांकernal_lookup[i].cb_idx = 0xFF;
		ioc->पूर्णांकernal_lookup[i].smid = smid;
		list_add_tail(&ioc->पूर्णांकernal_lookup[i].tracker_list,
		    &ioc->पूर्णांकernal_मुक्त_list);
	पूर्ण

	spin_unlock_irqrestore(&ioc->scsi_lookup_lock, flags);

	/* initialize Reply Free Queue */
	क्रम (i = 0, reply_address = (u32)ioc->reply_dma ;
	    i < ioc->reply_मुक्त_queue_depth ; i++, reply_address +=
	    ioc->reply_sz) अणु
		ioc->reply_मुक्त[i] = cpu_to_le32(reply_address);
		अगर (ioc->is_mcpu_endpoपूर्णांक)
			_base_clone_reply_to_sys_mem(ioc,
					reply_address, i);
	पूर्ण

	/* initialize reply queues */
	अगर (ioc->is_driver_loading)
		_base_assign_reply_queues(ioc);

	/* initialize Reply Post Free Queue */
	index = 0;
	reply_post_मुक्त_contig = ioc->reply_post[0].reply_post_मुक्त;
	list_क्रम_each_entry(reply_q, &ioc->reply_queue_list, list) अणु
		/*
		 * If RDPQ is enabled, चयन to the next allocation.
		 * Otherwise advance within the contiguous region.
		 */
		अगर (ioc->rdpq_array_enable) अणु
			reply_q->reply_post_मुक्त =
				ioc->reply_post[index++].reply_post_मुक्त;
		पूर्ण अन्यथा अणु
			reply_q->reply_post_मुक्त = reply_post_मुक्त_contig;
			reply_post_मुक्त_contig += ioc->reply_post_queue_depth;
		पूर्ण

		reply_q->reply_post_host_index = 0;
		क्रम (i = 0; i < ioc->reply_post_queue_depth; i++)
			reply_q->reply_post_मुक्त[i].Words =
			    cpu_to_le64(ULदीर्घ_उच्च);
		अगर (!_base_is_controller_msix_enabled(ioc))
			जाओ skip_init_reply_post_मुक्त_queue;
	पूर्ण
 skip_init_reply_post_मुक्त_queue:

	r = _base_send_ioc_init(ioc);
	अगर (r) अणु
		/*
		 * No need to check IOC state क्रम fault state & issue
		 * diag reset during host reset. This check is need
		 * only during driver load समय.
		 */
		अगर (!ioc->is_driver_loading)
			वापस r;

		rc = _base_check_क्रम_fault_and_issue_reset(ioc);
		अगर (rc || (_base_send_ioc_init(ioc)))
			वापस r;
	पूर्ण

	/* initialize reply मुक्त host index */
	ioc->reply_मुक्त_host_index = ioc->reply_मुक्त_queue_depth - 1;
	ग_लिखोl(ioc->reply_मुक्त_host_index, &ioc->chip->ReplyFreeHostIndex);

	/* initialize reply post host index */
	list_क्रम_each_entry(reply_q, &ioc->reply_queue_list, list) अणु
		अगर (ioc->combined_reply_queue)
			ग_लिखोl((reply_q->msix_index & 7)<<
			   MPI2_RPHI_MSIX_INDEX_SHIFT,
			   ioc->replyPostRegisterIndex[reply_q->msix_index/8]);
		अन्यथा
			ग_लिखोl(reply_q->msix_index <<
				MPI2_RPHI_MSIX_INDEX_SHIFT,
				&ioc->chip->ReplyPostHostIndex);

		अगर (!_base_is_controller_msix_enabled(ioc))
			जाओ skip_init_reply_post_host_index;
	पूर्ण

 skip_init_reply_post_host_index:

	mpt3sas_base_unmask_पूर्णांकerrupts(ioc);

	अगर (ioc->hba_mpi_version_beदीर्घed != MPI2_VERSION) अणु
		r = _base_display_fwpkg_version(ioc);
		अगर (r)
			वापस r;
	पूर्ण

	_base_अटल_config_pages(ioc);
	r = _base_event_notअगरication(ioc);
	अगर (r)
		वापस r;

	अगर (ioc->is_driver_loading) अणु

		अगर (ioc->is_warpdrive && ioc->manu_pg10.OEMIdentअगरier
		    == 0x80) अणु
			hide_flag = (u8) (
			    le32_to_cpu(ioc->manu_pg10.OEMSpecअगरicFlags0) &
			    MFG_PAGE10_HIDE_SSDS_MASK);
			अगर (hide_flag != MFG_PAGE10_HIDE_SSDS_MASK)
				ioc->mfg_pg10_hide_flag = hide_flag;
		पूर्ण

		ioc->रुको_क्रम_discovery_to_complete =
		    _base_determine_रुको_on_discovery(ioc);

		वापस r; /* scan_start and scan_finished support */
	पूर्ण

	r = _base_send_port_enable(ioc);
	अगर (r)
		वापस r;

	वापस r;
पूर्ण

/**
 * mpt3sas_base_मुक्त_resources - मुक्त resources controller resources
 * @ioc: per adapter object
 */
व्योम
mpt3sas_base_मुक्त_resources(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	dनिकासprपूर्णांकk(ioc, ioc_info(ioc, "%s\n", __func__));

	/* synchronizing मुक्तing resource with pci_access_mutex lock */
	mutex_lock(&ioc->pci_access_mutex);
	अगर (ioc->chip_phys && ioc->chip) अणु
		mpt3sas_base_mask_पूर्णांकerrupts(ioc);
		ioc->shost_recovery = 1;
		_base_make_ioc_पढ़ोy(ioc, SOFT_RESET);
		ioc->shost_recovery = 0;
	पूर्ण

	mpt3sas_base_unmap_resources(ioc);
	mutex_unlock(&ioc->pci_access_mutex);
	वापस;
पूर्ण

/**
 * mpt3sas_base_attach - attach controller instance
 * @ioc: per adapter object
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_base_attach(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	पूर्णांक r, i, rc;
	पूर्णांक cpu_id, last_cpu_id = 0;

	dinitprपूर्णांकk(ioc, ioc_info(ioc, "%s\n", __func__));

	/* setup cpu_msix_table */
	ioc->cpu_count = num_online_cpus();
	क्रम_each_online_cpu(cpu_id)
		last_cpu_id = cpu_id;
	ioc->cpu_msix_table_sz = last_cpu_id + 1;
	ioc->cpu_msix_table = kzalloc(ioc->cpu_msix_table_sz, GFP_KERNEL);
	ioc->reply_queue_count = 1;
	अगर (!ioc->cpu_msix_table) अणु
		ioc_info(ioc, "Allocation for cpu_msix_table failed!!!\n");
		r = -ENOMEM;
		जाओ out_मुक्त_resources;
	पूर्ण

	अगर (ioc->is_warpdrive) अणु
		ioc->reply_post_host_index = kसुस्मृति(ioc->cpu_msix_table_sz,
		    माप(resource_माप_प्रकार *), GFP_KERNEL);
		अगर (!ioc->reply_post_host_index) अणु
			ioc_info(ioc, "Allocation for reply_post_host_index failed!!!\n");
			r = -ENOMEM;
			जाओ out_मुक्त_resources;
		पूर्ण
	पूर्ण

	ioc->smp_affinity_enable = smp_affinity_enable;

	ioc->rdpq_array_enable_asचिन्हित = 0;
	ioc->use_32bit_dma = false;
	ioc->dma_mask = 64;
	अगर (ioc->is_aero_ioc)
		ioc->base_पढ़ोl = &_base_पढ़ोl_aero;
	अन्यथा
		ioc->base_पढ़ोl = &_base_पढ़ोl;
	r = mpt3sas_base_map_resources(ioc);
	अगर (r)
		जाओ out_मुक्त_resources;

	pci_set_drvdata(ioc->pdev, ioc->shost);
	r = _base_get_ioc_facts(ioc);
	अगर (r) अणु
		rc = _base_check_क्रम_fault_and_issue_reset(ioc);
		अगर (rc || (_base_get_ioc_facts(ioc)))
			जाओ out_मुक्त_resources;
	पूर्ण

	चयन (ioc->hba_mpi_version_beदीर्घed) अणु
	हाल MPI2_VERSION:
		ioc->build_sg_scmd = &_base_build_sg_scmd;
		ioc->build_sg = &_base_build_sg;
		ioc->build_zero_len_sge = &_base_build_zero_len_sge;
		ioc->get_msix_index_क्रम_smlio = &_base_get_msix_index;
		अवरोध;
	हाल MPI25_VERSION:
	हाल MPI26_VERSION:
		/*
		 * In SAS3.0,
		 * SCSI_IO, SMP_PASSTHRU, SATA_PASSTHRU, Target Assist, and
		 * Target Status - all require the IEEE क्रमmated scatter gather
		 * elements.
		 */
		ioc->build_sg_scmd = &_base_build_sg_scmd_ieee;
		ioc->build_sg = &_base_build_sg_ieee;
		ioc->build_nvme_prp = &_base_build_nvme_prp;
		ioc->build_zero_len_sge = &_base_build_zero_len_sge_ieee;
		ioc->sge_size_ieee = माप(Mpi2IeeeSgeSimple64_t);
		अगर (ioc->high_iops_queues)
			ioc->get_msix_index_क्रम_smlio =
					&_base_get_high_iops_msix_index;
		अन्यथा
			ioc->get_msix_index_क्रम_smlio = &_base_get_msix_index;
		अवरोध;
	पूर्ण
	अगर (ioc->atomic_desc_capable) अणु
		ioc->put_smid_शेष = &_base_put_smid_शेष_atomic;
		ioc->put_smid_scsi_io = &_base_put_smid_scsi_io_atomic;
		ioc->put_smid_fast_path =
				&_base_put_smid_fast_path_atomic;
		ioc->put_smid_hi_priority =
				&_base_put_smid_hi_priority_atomic;
	पूर्ण अन्यथा अणु
		ioc->put_smid_शेष = &_base_put_smid_शेष;
		ioc->put_smid_fast_path = &_base_put_smid_fast_path;
		ioc->put_smid_hi_priority = &_base_put_smid_hi_priority;
		अगर (ioc->is_mcpu_endpoपूर्णांक)
			ioc->put_smid_scsi_io =
				&_base_put_smid_mpi_ep_scsi_io;
		अन्यथा
			ioc->put_smid_scsi_io = &_base_put_smid_scsi_io;
	पूर्ण
	/*
	 * These function poपूर्णांकers क्रम other requests that करोn't
	 * the require IEEE scatter gather elements.
	 *
	 * For example Configuration Pages and SAS IOUNIT Control करोn't.
	 */
	ioc->build_sg_mpi = &_base_build_sg;
	ioc->build_zero_len_sge_mpi = &_base_build_zero_len_sge;

	r = _base_make_ioc_पढ़ोy(ioc, SOFT_RESET);
	अगर (r)
		जाओ out_मुक्त_resources;

	ioc->pfacts = kसुस्मृति(ioc->facts.NumberOfPorts,
	    माप(काष्ठा mpt3sas_port_facts), GFP_KERNEL);
	अगर (!ioc->pfacts) अणु
		r = -ENOMEM;
		जाओ out_मुक्त_resources;
	पूर्ण

	क्रम (i = 0 ; i < ioc->facts.NumberOfPorts; i++) अणु
		r = _base_get_port_facts(ioc, i);
		अगर (r) अणु
			rc = _base_check_क्रम_fault_and_issue_reset(ioc);
			अगर (rc || (_base_get_port_facts(ioc, i)))
				जाओ out_मुक्त_resources;
		पूर्ण
	पूर्ण

	r = _base_allocate_memory_pools(ioc);
	अगर (r)
		जाओ out_मुक्त_resources;

	अगर (irqpoll_weight > 0)
		ioc->thresh_hold = irqpoll_weight;
	अन्यथा
		ioc->thresh_hold = ioc->hba_queue_depth/4;

	_base_init_irqpolls(ioc);
	init_रुकोqueue_head(&ioc->reset_wq);

	/* allocate memory pd handle biपंचांगask list */
	ioc->pd_handles_sz = (ioc->facts.MaxDevHandle / 8);
	अगर (ioc->facts.MaxDevHandle % 8)
		ioc->pd_handles_sz++;
	ioc->pd_handles = kzalloc(ioc->pd_handles_sz,
	    GFP_KERNEL);
	अगर (!ioc->pd_handles) अणु
		r = -ENOMEM;
		जाओ out_मुक्त_resources;
	पूर्ण
	ioc->blocking_handles = kzalloc(ioc->pd_handles_sz,
	    GFP_KERNEL);
	अगर (!ioc->blocking_handles) अणु
		r = -ENOMEM;
		जाओ out_मुक्त_resources;
	पूर्ण

	/* allocate memory क्रम pending OS device add list */
	ioc->pend_os_device_add_sz = (ioc->facts.MaxDevHandle / 8);
	अगर (ioc->facts.MaxDevHandle % 8)
		ioc->pend_os_device_add_sz++;
	ioc->pend_os_device_add = kzalloc(ioc->pend_os_device_add_sz,
	    GFP_KERNEL);
	अगर (!ioc->pend_os_device_add) अणु
		r = -ENOMEM;
		जाओ out_मुक्त_resources;
	पूर्ण

	ioc->device_हटाओ_in_progress_sz = ioc->pend_os_device_add_sz;
	ioc->device_हटाओ_in_progress =
		kzalloc(ioc->device_हटाओ_in_progress_sz, GFP_KERNEL);
	अगर (!ioc->device_हटाओ_in_progress) अणु
		r = -ENOMEM;
		जाओ out_मुक्त_resources;
	पूर्ण

	ioc->fwfault_debug = mpt3sas_fwfault_debug;

	/* base पूर्णांकernal command bits */
	mutex_init(&ioc->base_cmds.mutex);
	ioc->base_cmds.reply = kzalloc(ioc->reply_sz, GFP_KERNEL);
	ioc->base_cmds.status = MPT3_CMD_NOT_USED;

	/* port_enable command bits */
	ioc->port_enable_cmds.reply = kzalloc(ioc->reply_sz, GFP_KERNEL);
	ioc->port_enable_cmds.status = MPT3_CMD_NOT_USED;

	/* transport पूर्णांकernal command bits */
	ioc->transport_cmds.reply = kzalloc(ioc->reply_sz, GFP_KERNEL);
	ioc->transport_cmds.status = MPT3_CMD_NOT_USED;
	mutex_init(&ioc->transport_cmds.mutex);

	/* scsih पूर्णांकernal command bits */
	ioc->scsih_cmds.reply = kzalloc(ioc->reply_sz, GFP_KERNEL);
	ioc->scsih_cmds.status = MPT3_CMD_NOT_USED;
	mutex_init(&ioc->scsih_cmds.mutex);

	/* task management पूर्णांकernal command bits */
	ioc->पंचांग_cmds.reply = kzalloc(ioc->reply_sz, GFP_KERNEL);
	ioc->पंचांग_cmds.status = MPT3_CMD_NOT_USED;
	mutex_init(&ioc->पंचांग_cmds.mutex);

	/* config page पूर्णांकernal command bits */
	ioc->config_cmds.reply = kzalloc(ioc->reply_sz, GFP_KERNEL);
	ioc->config_cmds.status = MPT3_CMD_NOT_USED;
	mutex_init(&ioc->config_cmds.mutex);

	/* ctl module पूर्णांकernal command bits */
	ioc->ctl_cmds.reply = kzalloc(ioc->reply_sz, GFP_KERNEL);
	ioc->ctl_cmds.sense = kzalloc(SCSI_SENSE_BUFFERSIZE, GFP_KERNEL);
	ioc->ctl_cmds.status = MPT3_CMD_NOT_USED;
	mutex_init(&ioc->ctl_cmds.mutex);

	अगर (!ioc->base_cmds.reply || !ioc->port_enable_cmds.reply ||
	    !ioc->transport_cmds.reply || !ioc->scsih_cmds.reply ||
	    !ioc->पंचांग_cmds.reply || !ioc->config_cmds.reply ||
	    !ioc->ctl_cmds.reply || !ioc->ctl_cmds.sense) अणु
		r = -ENOMEM;
		जाओ out_मुक्त_resources;
	पूर्ण

	क्रम (i = 0; i < MPI2_EVENT_NOTIFY_EVENTMASK_WORDS; i++)
		ioc->event_masks[i] = -1;

	/* here we enable the events we care about */
	_base_unmask_events(ioc, MPI2_EVENT_SAS_DISCOVERY);
	_base_unmask_events(ioc, MPI2_EVENT_SAS_BROADCAST_PRIMITIVE);
	_base_unmask_events(ioc, MPI2_EVENT_SAS_TOPOLOGY_CHANGE_LIST);
	_base_unmask_events(ioc, MPI2_EVENT_SAS_DEVICE_STATUS_CHANGE);
	_base_unmask_events(ioc, MPI2_EVENT_SAS_ENCL_DEVICE_STATUS_CHANGE);
	_base_unmask_events(ioc, MPI2_EVENT_IR_CONFIGURATION_CHANGE_LIST);
	_base_unmask_events(ioc, MPI2_EVENT_IR_VOLUME);
	_base_unmask_events(ioc, MPI2_EVENT_IR_PHYSICAL_DISK);
	_base_unmask_events(ioc, MPI2_EVENT_IR_OPERATION_STATUS);
	_base_unmask_events(ioc, MPI2_EVENT_LOG_ENTRY_ADDED);
	_base_unmask_events(ioc, MPI2_EVENT_TEMP_THRESHOLD);
	_base_unmask_events(ioc, MPI2_EVENT_ACTIVE_CABLE_EXCEPTION);
	_base_unmask_events(ioc, MPI2_EVENT_SAS_DEVICE_DISCOVERY_ERROR);
	अगर (ioc->hba_mpi_version_beदीर्घed == MPI26_VERSION) अणु
		अगर (ioc->is_gen35_ioc) अणु
			_base_unmask_events(ioc,
				MPI2_EVENT_PCIE_DEVICE_STATUS_CHANGE);
			_base_unmask_events(ioc, MPI2_EVENT_PCIE_ENUMERATION);
			_base_unmask_events(ioc,
				MPI2_EVENT_PCIE_TOPOLOGY_CHANGE_LIST);
		पूर्ण
	पूर्ण
	r = _base_make_ioc_operational(ioc);
	अगर (r)
		जाओ out_मुक्त_resources;

	/*
	 * Copy current copy of IOCFacts in prev_fw_facts
	 * and it will be used during online firmware upgrade.
	 */
	स_नकल(&ioc->prev_fw_facts, &ioc->facts,
	    माप(काष्ठा mpt3sas_facts));

	ioc->non_operational_loop = 0;
	ioc->ioc_coredump_loop = 0;
	ioc->got_task_पात_from_ioctl = 0;
	वापस 0;

 out_मुक्त_resources:

	ioc->हटाओ_host = 1;

	mpt3sas_base_मुक्त_resources(ioc);
	_base_release_memory_pools(ioc);
	pci_set_drvdata(ioc->pdev, शून्य);
	kमुक्त(ioc->cpu_msix_table);
	अगर (ioc->is_warpdrive)
		kमुक्त(ioc->reply_post_host_index);
	kमुक्त(ioc->pd_handles);
	kमुक्त(ioc->blocking_handles);
	kमुक्त(ioc->device_हटाओ_in_progress);
	kमुक्त(ioc->pend_os_device_add);
	kमुक्त(ioc->पंचांग_cmds.reply);
	kमुक्त(ioc->transport_cmds.reply);
	kमुक्त(ioc->scsih_cmds.reply);
	kमुक्त(ioc->config_cmds.reply);
	kमुक्त(ioc->base_cmds.reply);
	kमुक्त(ioc->port_enable_cmds.reply);
	kमुक्त(ioc->ctl_cmds.reply);
	kमुक्त(ioc->ctl_cmds.sense);
	kमुक्त(ioc->pfacts);
	ioc->ctl_cmds.reply = शून्य;
	ioc->base_cmds.reply = शून्य;
	ioc->पंचांग_cmds.reply = शून्य;
	ioc->scsih_cmds.reply = शून्य;
	ioc->transport_cmds.reply = शून्य;
	ioc->config_cmds.reply = शून्य;
	ioc->pfacts = शून्य;
	वापस r;
पूर्ण


/**
 * mpt3sas_base_detach - हटाओ controller instance
 * @ioc: per adapter object
 */
व्योम
mpt3sas_base_detach(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	dनिकासprपूर्णांकk(ioc, ioc_info(ioc, "%s\n", __func__));

	mpt3sas_base_stop_watchकरोg(ioc);
	mpt3sas_base_मुक्त_resources(ioc);
	_base_release_memory_pools(ioc);
	mpt3sas_मुक्त_enclosure_list(ioc);
	pci_set_drvdata(ioc->pdev, शून्य);
	kमुक्त(ioc->cpu_msix_table);
	अगर (ioc->is_warpdrive)
		kमुक्त(ioc->reply_post_host_index);
	kमुक्त(ioc->pd_handles);
	kमुक्त(ioc->blocking_handles);
	kमुक्त(ioc->device_हटाओ_in_progress);
	kमुक्त(ioc->pend_os_device_add);
	kमुक्त(ioc->pfacts);
	kमुक्त(ioc->ctl_cmds.reply);
	kमुक्त(ioc->ctl_cmds.sense);
	kमुक्त(ioc->base_cmds.reply);
	kमुक्त(ioc->port_enable_cmds.reply);
	kमुक्त(ioc->पंचांग_cmds.reply);
	kमुक्त(ioc->transport_cmds.reply);
	kमुक्त(ioc->scsih_cmds.reply);
	kमुक्त(ioc->config_cmds.reply);
पूर्ण

/**
 * _base_pre_reset_handler - pre reset handler
 * @ioc: per adapter object
 */
अटल व्योम _base_pre_reset_handler(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	mpt3sas_scsih_pre_reset_handler(ioc);
	mpt3sas_ctl_pre_reset_handler(ioc);
	dपंचांगprपूर्णांकk(ioc, ioc_info(ioc, "%s: MPT3_IOC_PRE_RESET\n", __func__));
पूर्ण

/**
 * _base_clear_outstanding_mpt_commands - clears outstanding mpt commands
 * @ioc: per adapter object
 */
अटल व्योम
_base_clear_outstanding_mpt_commands(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	dपंचांगprपूर्णांकk(ioc,
	    ioc_info(ioc, "%s: clear outstanding mpt cmds\n", __func__));
	अगर (ioc->transport_cmds.status & MPT3_CMD_PENDING) अणु
		ioc->transport_cmds.status |= MPT3_CMD_RESET;
		mpt3sas_base_मुक्त_smid(ioc, ioc->transport_cmds.smid);
		complete(&ioc->transport_cmds.करोne);
	पूर्ण
	अगर (ioc->base_cmds.status & MPT3_CMD_PENDING) अणु
		ioc->base_cmds.status |= MPT3_CMD_RESET;
		mpt3sas_base_मुक्त_smid(ioc, ioc->base_cmds.smid);
		complete(&ioc->base_cmds.करोne);
	पूर्ण
	अगर (ioc->port_enable_cmds.status & MPT3_CMD_PENDING) अणु
		ioc->port_enable_failed = 1;
		ioc->port_enable_cmds.status |= MPT3_CMD_RESET;
		mpt3sas_base_मुक्त_smid(ioc, ioc->port_enable_cmds.smid);
		अगर (ioc->is_driver_loading) अणु
			ioc->start_scan_failed =
				MPI2_IOCSTATUS_INTERNAL_ERROR;
			ioc->start_scan = 0;
			ioc->port_enable_cmds.status =
				MPT3_CMD_NOT_USED;
		पूर्ण अन्यथा अणु
			complete(&ioc->port_enable_cmds.करोne);
		पूर्ण
	पूर्ण
	अगर (ioc->config_cmds.status & MPT3_CMD_PENDING) अणु
		ioc->config_cmds.status |= MPT3_CMD_RESET;
		mpt3sas_base_मुक्त_smid(ioc, ioc->config_cmds.smid);
		ioc->config_cmds.smid = अच_लघु_उच्च;
		complete(&ioc->config_cmds.करोne);
	पूर्ण
पूर्ण

/**
 * _base_clear_outstanding_commands - clear all outstanding commands
 * @ioc: per adapter object
 */
अटल व्योम _base_clear_outstanding_commands(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	mpt3sas_scsih_clear_outstanding_scsi_पंचांग_commands(ioc);
	mpt3sas_ctl_clear_outstanding_ioctls(ioc);
	_base_clear_outstanding_mpt_commands(ioc);
पूर्ण

/**
 * _base_reset_करोne_handler - reset करोne handler
 * @ioc: per adapter object
 */
अटल व्योम _base_reset_करोne_handler(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	mpt3sas_scsih_reset_करोne_handler(ioc);
	mpt3sas_ctl_reset_करोne_handler(ioc);
	dपंचांगprपूर्णांकk(ioc, ioc_info(ioc, "%s: MPT3_IOC_DONE_RESET\n", __func__));
पूर्ण

/**
 * mpt3sas_रुको_क्रम_commands_to_complete - reset controller
 * @ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *
 * This function is रुकोing 10s क्रम all pending commands to complete
 * prior to putting controller in reset.
 */
व्योम
mpt3sas_रुको_क्रम_commands_to_complete(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	u32 ioc_state;

	ioc->pending_io_count = 0;

	ioc_state = mpt3sas_base_get_iocstate(ioc, 0);
	अगर ((ioc_state & MPI2_IOC_STATE_MASK) != MPI2_IOC_STATE_OPERATIONAL)
		वापस;

	/* pending command count */
	ioc->pending_io_count = scsi_host_busy(ioc->shost);

	अगर (!ioc->pending_io_count)
		वापस;

	/* रुको क्रम pending commands to complete */
	रुको_event_समयout(ioc->reset_wq, ioc->pending_io_count == 0, 10 * HZ);
पूर्ण

/**
 * _base_check_ioc_facts_changes - Look क्रम increase/decrease of IOCFacts
 *     attributes during online firmware upgrade and update the corresponding
 *     IOC variables accordingly.
 *
 * @ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 */
अटल पूर्णांक
_base_check_ioc_facts_changes(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	u16 pd_handles_sz;
	व्योम *pd_handles = शून्य, *blocking_handles = शून्य;
	व्योम *pend_os_device_add = शून्य, *device_हटाओ_in_progress = शून्य;
	काष्ठा mpt3sas_facts *old_facts = &ioc->prev_fw_facts;

	अगर (ioc->facts.MaxDevHandle > old_facts->MaxDevHandle) अणु
		pd_handles_sz = (ioc->facts.MaxDevHandle / 8);
		अगर (ioc->facts.MaxDevHandle % 8)
			pd_handles_sz++;

		pd_handles = kपुनः_स्मृति(ioc->pd_handles, pd_handles_sz,
		    GFP_KERNEL);
		अगर (!pd_handles) अणु
			ioc_info(ioc,
			    "Unable to allocate the memory for pd_handles of sz: %d\n",
			    pd_handles_sz);
			वापस -ENOMEM;
		पूर्ण
		स_रखो(pd_handles + ioc->pd_handles_sz, 0,
		    (pd_handles_sz - ioc->pd_handles_sz));
		ioc->pd_handles = pd_handles;

		blocking_handles = kपुनः_स्मृति(ioc->blocking_handles,
		    pd_handles_sz, GFP_KERNEL);
		अगर (!blocking_handles) अणु
			ioc_info(ioc,
			    "Unable to allocate the memory for "
			    "blocking_handles of sz: %d\n",
			    pd_handles_sz);
			वापस -ENOMEM;
		पूर्ण
		स_रखो(blocking_handles + ioc->pd_handles_sz, 0,
		    (pd_handles_sz - ioc->pd_handles_sz));
		ioc->blocking_handles = blocking_handles;
		ioc->pd_handles_sz = pd_handles_sz;

		pend_os_device_add = kपुनः_स्मृति(ioc->pend_os_device_add,
		    pd_handles_sz, GFP_KERNEL);
		अगर (!pend_os_device_add) अणु
			ioc_info(ioc,
			    "Unable to allocate the memory for pend_os_device_add of sz: %d\n",
			    pd_handles_sz);
			वापस -ENOMEM;
		पूर्ण
		स_रखो(pend_os_device_add + ioc->pend_os_device_add_sz, 0,
		    (pd_handles_sz - ioc->pend_os_device_add_sz));
		ioc->pend_os_device_add = pend_os_device_add;
		ioc->pend_os_device_add_sz = pd_handles_sz;

		device_हटाओ_in_progress = kपुनः_स्मृति(
		    ioc->device_हटाओ_in_progress, pd_handles_sz, GFP_KERNEL);
		अगर (!device_हटाओ_in_progress) अणु
			ioc_info(ioc,
			    "Unable to allocate the memory for "
			    "device_remove_in_progress of sz: %d\n "
			    , pd_handles_sz);
			वापस -ENOMEM;
		पूर्ण
		स_रखो(device_हटाओ_in_progress +
		    ioc->device_हटाओ_in_progress_sz, 0,
		    (pd_handles_sz - ioc->device_हटाओ_in_progress_sz));
		ioc->device_हटाओ_in_progress = device_हटाओ_in_progress;
		ioc->device_हटाओ_in_progress_sz = pd_handles_sz;
	पूर्ण

	स_नकल(&ioc->prev_fw_facts, &ioc->facts, माप(काष्ठा mpt3sas_facts));
	वापस 0;
पूर्ण

/**
 * mpt3sas_base_hard_reset_handler - reset controller
 * @ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 * @type: FORCE_BIG_HAMMER or SOFT_RESET
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_base_hard_reset_handler(काष्ठा MPT3SAS_ADAPTER *ioc,
	क्रमागत reset_type type)
अणु
	पूर्णांक r;
	अचिन्हित दीर्घ flags;
	u32 ioc_state;
	u8 is_fault = 0, is_trigger = 0;

	dपंचांगprपूर्णांकk(ioc, ioc_info(ioc, "%s: enter\n", __func__));

	अगर (ioc->pci_error_recovery) अणु
		ioc_err(ioc, "%s: pci error recovery reset\n", __func__);
		r = 0;
		जाओ out_unlocked;
	पूर्ण

	अगर (mpt3sas_fwfault_debug)
		mpt3sas_halt_firmware(ioc);

	/* रुको क्रम an active reset in progress to complete */
	mutex_lock(&ioc->reset_in_progress_mutex);

	spin_lock_irqsave(&ioc->ioc_reset_in_progress_lock, flags);
	ioc->shost_recovery = 1;
	spin_unlock_irqrestore(&ioc->ioc_reset_in_progress_lock, flags);

	अगर ((ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
	    MPT3_DIAG_BUFFER_IS_REGISTERED) &&
	    (!(ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
	    MPT3_DIAG_BUFFER_IS_RELEASED))) अणु
		is_trigger = 1;
		ioc_state = mpt3sas_base_get_iocstate(ioc, 0);
		अगर ((ioc_state & MPI2_IOC_STATE_MASK) == MPI2_IOC_STATE_FAULT ||
		    (ioc_state & MPI2_IOC_STATE_MASK) ==
		    MPI2_IOC_STATE_COREDUMP) अणु
			is_fault = 1;
			ioc->htb_rel.trigger_info_dwords[1] =
			    (ioc_state & MPI2_DOORBELL_DATA_MASK);
		पूर्ण
	पूर्ण
	_base_pre_reset_handler(ioc);
	mpt3sas_रुको_क्रम_commands_to_complete(ioc);
	mpt3sas_base_mask_पूर्णांकerrupts(ioc);
	r = _base_make_ioc_पढ़ोy(ioc, type);
	अगर (r)
		जाओ out;
	_base_clear_outstanding_commands(ioc);

	/* If this hard reset is called जबतक port enable is active, then
	 * there is no reason to call make_ioc_operational
	 */
	अगर (ioc->is_driver_loading && ioc->port_enable_failed) अणु
		ioc->हटाओ_host = 1;
		r = -EFAULT;
		जाओ out;
	पूर्ण
	r = _base_get_ioc_facts(ioc);
	अगर (r)
		जाओ out;

	r = _base_check_ioc_facts_changes(ioc);
	अगर (r) अणु
		ioc_info(ioc,
		    "Some of the parameters got changed in this new firmware"
		    " image and it requires system reboot\n");
		जाओ out;
	पूर्ण
	अगर (ioc->rdpq_array_enable && !ioc->rdpq_array_capable)
		panic("%s: Issue occurred with flashing controller firmware."
		      "Please reboot the system and ensure that the correct"
		      " firmware version is running\n", ioc->name);

	r = _base_make_ioc_operational(ioc);
	अगर (!r)
		_base_reset_करोne_handler(ioc);

 out:
	ioc_info(ioc, "%s: %s\n", __func__, r == 0 ? "SUCCESS" : "FAILED");

	spin_lock_irqsave(&ioc->ioc_reset_in_progress_lock, flags);
	ioc->shost_recovery = 0;
	spin_unlock_irqrestore(&ioc->ioc_reset_in_progress_lock, flags);
	ioc->ioc_reset_count++;
	mutex_unlock(&ioc->reset_in_progress_mutex);

 out_unlocked:
	अगर ((r == 0) && is_trigger) अणु
		अगर (is_fault)
			mpt3sas_trigger_master(ioc, MASTER_TRIGGER_FW_FAULT);
		अन्यथा
			mpt3sas_trigger_master(ioc,
			    MASTER_TRIGGER_ADAPTER_RESET);
	पूर्ण
	dपंचांगprपूर्णांकk(ioc, ioc_info(ioc, "%s: exit\n", __func__));
	वापस r;
पूर्ण
