<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*

  Linux Driver क्रम BusLogic MultiMaster and FlashPoपूर्णांक SCSI Host Adapters

  Copyright 1995-1998 by Leonard N. Zubkoff <lnz@dandelion.com>


  The author respectfully requests that any modअगरications to this software be
  sent directly to him क्रम evaluation and testing.

  Special thanks to Wayne Yen, Jin-Lon Hon, and Alex Win of BusLogic, whose
  advice has been invaluable, to David Gentzel, क्रम writing the original Linux
  BusLogic driver, and to Paul Gorपंचांगaker, क्रम being such a dedicated test site.

  Finally, special thanks to Mylex/BusLogic क्रम making the FlashPoपूर्णांक SCCB
  Manager available as मुक्तly redistributable source code.

*/

#घोषणा blogic_drvr_version		"2.1.17"
#घोषणा blogic_drvr_date		"12 September 2013"

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/types.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/mm.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/msकरोs_partition.h>
#समावेश <scsi/scsicam.h>

#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/पन.स>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश "BusLogic.h"
#समावेश "FlashPoint.c"

#अगर_अघोषित FAILURE
#घोषणा FAILURE (-1)
#पूर्ण_अगर

अटल काष्ठा scsi_host_ढाँचा blogic_ढाँचा;

/*
  blogic_drvr_options_count is a count of the number of BusLogic Driver
  Options specअगरications provided via the Linux Kernel Command Line or via
  the Loadable Kernel Module Installation Facility.
*/

अटल पूर्णांक blogic_drvr_options_count;


/*
  blogic_drvr_options is an array of Driver Options काष्ठाures representing
  BusLogic Driver Options specअगरications provided via the Linux Kernel Command
  Line or via the Loadable Kernel Module Installation Facility.
*/

अटल काष्ठा blogic_drvr_options blogic_drvr_options[BLOGIC_MAX_ADAPTERS];


/*
  BusLogic can be asचिन्हित a string by insmod.
*/

MODULE_LICENSE("GPL");
#अगर_घोषित MODULE
अटल अक्षर *BusLogic;
module_param(BusLogic, अक्षरp, 0);
#पूर्ण_अगर


/*
  blogic_probe_options is a set of Probe Options to be applied across
  all BusLogic Host Adapters.
*/

अटल काष्ठा blogic_probe_options blogic_probe_options;


/*
  blogic_global_options is a set of Global Options to be applied across
  all BusLogic Host Adapters.
*/

अटल काष्ठा blogic_global_options blogic_global_options;

अटल LIST_HEAD(blogic_host_list);

/*
  blogic_probeinfo_count is the number of entries in blogic_probeinfo_list.
*/

अटल पूर्णांक blogic_probeinfo_count;


/*
  blogic_probeinfo_list is the list of I/O Addresses and Bus Probe Inक्रमmation
  to be checked क्रम potential BusLogic Host Adapters.  It is initialized by
  पूर्णांकerrogating the PCI Configuration Space on PCI machines as well as from the
  list of standard BusLogic I/O Addresses.
*/

अटल काष्ठा blogic_probeinfo *blogic_probeinfo_list;


/*
  blogic_cmd_failure_reason holds a string identअगरying the reason why a
  call to blogic_cmd failed.  It is only non-शून्य when blogic_cmd
  वापसs a failure code.
*/

अटल अक्षर *blogic_cmd_failure_reason;

/*
  blogic_announce_drvr announces the Driver Version and Date, Author's
  Name, Copyright Notice, and Electronic Mail Address.
*/

अटल व्योम blogic_announce_drvr(काष्ठा blogic_adapter *adapter)
अणु
	blogic_announce("***** BusLogic SCSI Driver Version " blogic_drvr_version " of " blogic_drvr_date " *****\n", adapter);
	blogic_announce("Copyright 1995-1998 by Leonard N. Zubkoff <lnz@dandelion.com>\n", adapter);
पूर्ण


/*
  blogic_drvr_info वापसs the Host Adapter Name to identअगरy this SCSI
  Driver and Host Adapter.
*/

अटल स्थिर अक्षर *blogic_drvr_info(काष्ठा Scsi_Host *host)
अणु
	काष्ठा blogic_adapter *adapter =
				(काष्ठा blogic_adapter *) host->hostdata;
	वापस adapter->full_model;
पूर्ण

/*
  blogic_init_ccbs initializes a group of Command Control Blocks (CCBs)
  क्रम Host Adapter from the blk_size bytes located at blk_poपूर्णांकer.  The newly
  created CCBs are added to Host Adapter's मुक्त list.
*/

अटल व्योम blogic_init_ccbs(काष्ठा blogic_adapter *adapter, व्योम *blk_poपूर्णांकer,
				पूर्णांक blk_size, dma_addr_t blkp)
अणु
	काष्ठा blogic_ccb *ccb = (काष्ठा blogic_ccb *) blk_poपूर्णांकer;
	अचिन्हित पूर्णांक offset = 0;
	स_रखो(blk_poपूर्णांकer, 0, blk_size);
	ccb->allocgrp_head = blkp;
	ccb->allocgrp_size = blk_size;
	जबतक ((blk_size -= माप(काष्ठा blogic_ccb)) >= 0) अणु
		ccb->status = BLOGIC_CCB_FREE;
		ccb->adapter = adapter;
		ccb->dma_handle = (u32) blkp + offset;
		अगर (blogic_flashpoपूर्णांक_type(adapter)) अणु
			ccb->callback = blogic_qcompleted_ccb;
			ccb->base_addr = adapter->fpinfo.base_addr;
		पूर्ण
		ccb->next = adapter->मुक्त_ccbs;
		ccb->next_all = adapter->all_ccbs;
		adapter->मुक्त_ccbs = ccb;
		adapter->all_ccbs = ccb;
		adapter->alloc_ccbs++;
		ccb++;
		offset += माप(काष्ठा blogic_ccb);
	पूर्ण
पूर्ण


/*
  blogic_create_initccbs allocates the initial CCBs क्रम Host Adapter.
*/

अटल bool __init blogic_create_initccbs(काष्ठा blogic_adapter *adapter)
अणु
	पूर्णांक blk_size = BLOGIC_CCB_GRP_ALLOCSIZE * माप(काष्ठा blogic_ccb);
	व्योम *blk_poपूर्णांकer;
	dma_addr_t blkp;

	जबतक (adapter->alloc_ccbs < adapter->initccbs) अणु
		blk_poपूर्णांकer = dma_alloc_coherent(&adapter->pci_device->dev,
				blk_size, &blkp, GFP_KERNEL);
		अगर (blk_poपूर्णांकer == शून्य) अणु
			blogic_err("UNABLE TO ALLOCATE CCB GROUP - DETACHING\n",
					adapter);
			वापस false;
		पूर्ण
		blogic_init_ccbs(adapter, blk_poपूर्णांकer, blk_size, blkp);
	पूर्ण
	वापस true;
पूर्ण


/*
  blogic_destroy_ccbs deallocates the CCBs क्रम Host Adapter.
*/

अटल व्योम blogic_destroy_ccbs(काष्ठा blogic_adapter *adapter)
अणु
	काष्ठा blogic_ccb *next_ccb = adapter->all_ccbs, *ccb, *lastccb = शून्य;
	adapter->all_ccbs = शून्य;
	adapter->मुक्त_ccbs = शून्य;
	जबतक ((ccb = next_ccb) != शून्य) अणु
		next_ccb = ccb->next_all;
		अगर (ccb->allocgrp_head) अणु
			अगर (lastccb)
				dma_मुक्त_coherent(&adapter->pci_device->dev,
						lastccb->allocgrp_size, lastccb,
						lastccb->allocgrp_head);
			lastccb = ccb;
		पूर्ण
	पूर्ण
	अगर (lastccb)
		dma_मुक्त_coherent(&adapter->pci_device->dev,
				lastccb->allocgrp_size, lastccb,
				lastccb->allocgrp_head);
पूर्ण


/*
  blogic_create_addlccbs allocates Additional CCBs क्रम Host Adapter.  If
  allocation fails and there are no reमुख्यing CCBs available, the Driver Queue
  Depth is decreased to a known safe value to aव्योम potential deadlocks when
  multiple host adapters share the same IRQ Channel.
*/

अटल व्योम blogic_create_addlccbs(काष्ठा blogic_adapter *adapter,
					पूर्णांक addl_ccbs, bool prपूर्णांक_success)
अणु
	पूर्णांक blk_size = BLOGIC_CCB_GRP_ALLOCSIZE * माप(काष्ठा blogic_ccb);
	पूर्णांक prev_alloc = adapter->alloc_ccbs;
	व्योम *blk_poपूर्णांकer;
	dma_addr_t blkp;
	अगर (addl_ccbs <= 0)
		वापस;
	जबतक (adapter->alloc_ccbs - prev_alloc < addl_ccbs) अणु
		blk_poपूर्णांकer = dma_alloc_coherent(&adapter->pci_device->dev,
				blk_size, &blkp, GFP_KERNEL);
		अगर (blk_poपूर्णांकer == शून्य)
			अवरोध;
		blogic_init_ccbs(adapter, blk_poपूर्णांकer, blk_size, blkp);
	पूर्ण
	अगर (adapter->alloc_ccbs > prev_alloc) अणु
		अगर (prपूर्णांक_success)
			blogic_notice("Allocated %d additional CCBs (total now %d)\n", adapter, adapter->alloc_ccbs - prev_alloc, adapter->alloc_ccbs);
		वापस;
	पूर्ण
	blogic_notice("Failed to allocate additional CCBs\n", adapter);
	अगर (adapter->drvr_qdepth > adapter->alloc_ccbs - adapter->tgt_count) अणु
		adapter->drvr_qdepth = adapter->alloc_ccbs - adapter->tgt_count;
		adapter->scsi_host->can_queue = adapter->drvr_qdepth;
	पूर्ण
पूर्ण

/*
  blogic_alloc_ccb allocates a CCB from Host Adapter's मुक्त list,
  allocating more memory from the Kernel अगर necessary.  The Host Adapter's
  Lock should alपढ़ोy have been acquired by the caller.
*/

अटल काष्ठा blogic_ccb *blogic_alloc_ccb(काष्ठा blogic_adapter *adapter)
अणु
	अटल अचिन्हित दीर्घ serial;
	काष्ठा blogic_ccb *ccb;
	ccb = adapter->मुक्त_ccbs;
	अगर (ccb != शून्य) अणु
		ccb->serial = ++serial;
		adapter->मुक्त_ccbs = ccb->next;
		ccb->next = शून्य;
		अगर (adapter->मुक्त_ccbs == शून्य)
			blogic_create_addlccbs(adapter, adapter->inc_ccbs,
						true);
		वापस ccb;
	पूर्ण
	blogic_create_addlccbs(adapter, adapter->inc_ccbs, true);
	ccb = adapter->मुक्त_ccbs;
	अगर (ccb == शून्य)
		वापस शून्य;
	ccb->serial = ++serial;
	adapter->मुक्त_ccbs = ccb->next;
	ccb->next = शून्य;
	वापस ccb;
पूर्ण


/*
  blogic_dealloc_ccb deallocates a CCB, वापसing it to the Host Adapter's
  मुक्त list.  The Host Adapter's Lock should alपढ़ोy have been acquired by the
  caller.
*/

अटल व्योम blogic_dealloc_ccb(काष्ठा blogic_ccb *ccb, पूर्णांक dma_unmap)
अणु
	काष्ठा blogic_adapter *adapter = ccb->adapter;

	अगर (ccb->command != शून्य)
		scsi_dma_unmap(ccb->command);
	अगर (dma_unmap)
		dma_unmap_single(&adapter->pci_device->dev, ccb->sensedata,
			 ccb->sense_datalen, DMA_FROM_DEVICE);

	ccb->command = शून्य;
	ccb->status = BLOGIC_CCB_FREE;
	ccb->next = adapter->मुक्त_ccbs;
	adapter->मुक्त_ccbs = ccb;
पूर्ण


/*
  blogic_cmd sends the command opcode to adapter, optionally
  providing paramlen bytes of param and receiving at most
  replylen bytes of reply; any excess reply data is received but
  discarded.

  On success, this function वापसs the number of reply bytes पढ़ो from
  the Host Adapter (including any discarded data); on failure, it वापसs
  -1 अगर the command was invalid, or -2 अगर a समयout occurred.

  blogic_cmd is called exclusively during host adapter detection and
  initialization, so perक्रमmance and latency are not critical, and exclusive
  access to the Host Adapter hardware is assumed.  Once the host adapter and
  driver are initialized, the only Host Adapter command that is issued is the
  single byte Execute Mailbox Command operation code, which करोes not require
  रुकोing क्रम the Host Adapter Ready bit to be set in the Status Register.
*/

अटल पूर्णांक blogic_cmd(काष्ठा blogic_adapter *adapter, क्रमागत blogic_opcode opcode,
			व्योम *param, पूर्णांक paramlen, व्योम *reply, पूर्णांक replylen)
अणु
	अचिन्हित अक्षर *param_p = (अचिन्हित अक्षर *) param;
	अचिन्हित अक्षर *reply_p = (अचिन्हित अक्षर *) reply;
	जोड़ blogic_stat_reg statusreg;
	जोड़ blogic_पूर्णांक_reg पूर्णांकreg;
	अचिन्हित दीर्घ processor_flag = 0;
	पूर्णांक reply_b = 0, result;
	दीर्घ समयout;
	/*
	   Clear out the Reply Data अगर provided.
	 */
	अगर (replylen > 0)
		स_रखो(reply, 0, replylen);
	/*
	   If the IRQ Channel has not yet been acquired, then पूर्णांकerrupts
	   must be disabled जबतक issuing host adapter commands since a
	   Command Complete पूर्णांकerrupt could occur अगर the IRQ Channel was
	   previously enabled by another BusLogic Host Adapter or another
	   driver sharing the same IRQ Channel.
	 */
	अगर (!adapter->irq_acquired)
		local_irq_save(processor_flag);
	/*
	   Wait क्रम the Host Adapter Ready bit to be set and the
	   Command/Parameter Register Busy bit to be reset in the Status
	   Register.
	 */
	समयout = 10000;
	जबतक (--समयout >= 0) अणु
		statusreg.all = blogic_rdstatus(adapter);
		अगर (statusreg.sr.adapter_पढ़ोy && !statusreg.sr.cmd_param_busy)
			अवरोध;
		udelay(100);
	पूर्ण
	अगर (समयout < 0) अणु
		blogic_cmd_failure_reason =
				"Timeout waiting for Host Adapter Ready";
		result = -2;
		जाओ करोne;
	पूर्ण
	/*
	   Write the opcode to the Command/Parameter Register.
	 */
	adapter->adapter_cmd_complete = false;
	blogic_setcmdparam(adapter, opcode);
	/*
	   Write any additional Parameter Bytes.
	 */
	समयout = 10000;
	जबतक (paramlen > 0 && --समयout >= 0) अणु
		/*
		   Wait 100 microseconds to give the Host Adapter enough
		   समय to determine whether the last value written to the
		   Command/Parameter Register was valid or not. If the
		   Command Complete bit is set in the Interrupt Register,
		   then the Command Invalid bit in the Status Register will
		   be reset अगर the Operation Code or Parameter was valid
		   and the command has completed, or set अगर the Operation
		   Code or Parameter was invalid. If the Data In Register
		   Ready bit is set in the Status Register, then the
		   Operation Code was valid, and data is रुकोing to be पढ़ो
		   back from the Host Adapter. Otherwise, रुको क्रम the
		   Command/Parameter Register Busy bit in the Status
		   Register to be reset.
		 */
		udelay(100);
		पूर्णांकreg.all = blogic_rdपूर्णांक(adapter);
		statusreg.all = blogic_rdstatus(adapter);
		अगर (पूर्णांकreg.ir.cmd_complete)
			अवरोध;
		अगर (adapter->adapter_cmd_complete)
			अवरोध;
		अगर (statusreg.sr.datain_पढ़ोy)
			अवरोध;
		अगर (statusreg.sr.cmd_param_busy)
			जारी;
		blogic_setcmdparam(adapter, *param_p++);
		paramlen--;
	पूर्ण
	अगर (समयout < 0) अणु
		blogic_cmd_failure_reason =
				"Timeout waiting for Parameter Acceptance";
		result = -2;
		जाओ करोne;
	पूर्ण
	/*
	   The Modअगरy I/O Address command करोes not cause a Command Complete
	   Interrupt.
	 */
	अगर (opcode == BLOGIC_MOD_IOADDR) अणु
		statusreg.all = blogic_rdstatus(adapter);
		अगर (statusreg.sr.cmd_invalid) अणु
			blogic_cmd_failure_reason =
					"Modify I/O Address Invalid";
			result = -1;
			जाओ करोne;
		पूर्ण
		अगर (blogic_global_options.trace_config)
			blogic_notice("blogic_cmd(%02X) Status = %02X: (Modify I/O Address)\n", adapter, opcode, statusreg.all);
		result = 0;
		जाओ करोne;
	पूर्ण
	/*
	   Select an appropriate समयout value क्रम aरुकोing command completion.
	 */
	चयन (opcode) अणु
	हाल BLOGIC_INQ_DEV0TO7:
	हाल BLOGIC_INQ_DEV8TO15:
	हाल BLOGIC_INQ_DEV:
		/* Approximately 60 seconds. */
		समयout = 60 * 10000;
		अवरोध;
	शेष:
		/* Approximately 1 second. */
		समयout = 10000;
		अवरोध;
	पूर्ण
	/*
	   Receive any Reply Bytes, रुकोing क्रम either the Command
	   Complete bit to be set in the Interrupt Register, or क्रम the
	   Interrupt Handler to set the Host Adapter Command Completed
	   bit in the Host Adapter काष्ठाure.
	 */
	जबतक (--समयout >= 0) अणु
		पूर्णांकreg.all = blogic_rdपूर्णांक(adapter);
		statusreg.all = blogic_rdstatus(adapter);
		अगर (पूर्णांकreg.ir.cmd_complete)
			अवरोध;
		अगर (adapter->adapter_cmd_complete)
			अवरोध;
		अगर (statusreg.sr.datain_पढ़ोy) अणु
			अगर (++reply_b <= replylen)
				*reply_p++ = blogic_rddatain(adapter);
			अन्यथा
				blogic_rddatain(adapter);
		पूर्ण
		अगर (opcode == BLOGIC_FETCH_LOCALRAM &&
				statusreg.sr.adapter_पढ़ोy)
			अवरोध;
		udelay(100);
	पूर्ण
	अगर (समयout < 0) अणु
		blogic_cmd_failure_reason =
					"Timeout waiting for Command Complete";
		result = -2;
		जाओ करोne;
	पूर्ण
	/*
	   Clear any pending Command Complete Interrupt.
	 */
	blogic_पूर्णांकreset(adapter);
	/*
	   Provide tracing inक्रमmation अगर requested.
	 */
	अगर (blogic_global_options.trace_config) अणु
		पूर्णांक i;
		blogic_notice("blogic_cmd(%02X) Status = %02X: %2d ==> %2d:",
				adapter, opcode, statusreg.all, replylen,
				reply_b);
		अगर (replylen > reply_b)
			replylen = reply_b;
		क्रम (i = 0; i < replylen; i++)
			blogic_notice(" %02X", adapter,
					((अचिन्हित अक्षर *) reply)[i]);
		blogic_notice("\n", adapter);
	पूर्ण
	/*
	   Process Command Invalid conditions.
	 */
	अगर (statusreg.sr.cmd_invalid) अणु
		/*
		   Some early BusLogic Host Adapters may not recover
		   properly from a Command Invalid condition, so अगर this
		   appears to be the हाल, a Soft Reset is issued to the
		   Host Adapter.  Potentially invalid commands are never
		   attempted after Mailbox Initialization is perक्रमmed,
		   so there should be no Host Adapter state lost by a
		   Soft Reset in response to a Command Invalid condition.
		 */
		udelay(1000);
		statusreg.all = blogic_rdstatus(adapter);
		अगर (statusreg.sr.cmd_invalid || statusreg.sr.rsvd ||
				statusreg.sr.datain_पढ़ोy ||
				statusreg.sr.cmd_param_busy ||
				!statusreg.sr.adapter_पढ़ोy ||
				!statusreg.sr.init_reqd ||
				statusreg.sr.diag_active ||
				statusreg.sr.diag_failed) अणु
			blogic_softreset(adapter);
			udelay(1000);
		पूर्ण
		blogic_cmd_failure_reason = "Command Invalid";
		result = -1;
		जाओ करोne;
	पूर्ण
	/*
	   Handle Excess Parameters Supplied conditions.
	 */
	अगर (paramlen > 0) अणु
		blogic_cmd_failure_reason = "Excess Parameters Supplied";
		result = -1;
		जाओ करोne;
	पूर्ण
	/*
	   Indicate the command completed successfully.
	 */
	blogic_cmd_failure_reason = शून्य;
	result = reply_b;
	/*
	   Restore the पूर्णांकerrupt status अगर necessary and वापस.
	 */
करोne:
	अगर (!adapter->irq_acquired)
		local_irq_restore(processor_flag);
	वापस result;
पूर्ण


/*
  blogic_sort_probeinfo sorts a section of blogic_probeinfo_list in order
  of increasing PCI Bus and Device Number.
*/

अटल व्योम __init blogic_sort_probeinfo(काष्ठा blogic_probeinfo
					*probeinfo_list, पूर्णांक probeinfo_cnt)
अणु
	पूर्णांक last_exchange = probeinfo_cnt - 1, bound, j;

	जबतक (last_exchange > 0) अणु
		bound = last_exchange;
		last_exchange = 0;
		क्रम (j = 0; j < bound; j++) अणु
			काष्ठा blogic_probeinfo *probeinfo1 =
							&probeinfo_list[j];
			काष्ठा blogic_probeinfo *probeinfo2 =
							&probeinfo_list[j + 1];
			अगर (probeinfo1->bus > probeinfo2->bus ||
				(probeinfo1->bus == probeinfo2->bus &&
				(probeinfo1->dev > probeinfo2->dev))) अणु
				काष्ठा blogic_probeinfo पंचांगp_probeinfo;

				स_नकल(&पंचांगp_probeinfo, probeinfo1,
					माप(काष्ठा blogic_probeinfo));
				स_नकल(probeinfo1, probeinfo2,
					माप(काष्ठा blogic_probeinfo));
				स_नकल(probeinfo2, &पंचांगp_probeinfo,
					माप(काष्ठा blogic_probeinfo));
				last_exchange = j;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण


/*
  blogic_init_mm_probeinfo initializes the list of I/O Address
  and Bus Probe Inक्रमmation to be checked क्रम potential BusLogic MultiMaster
  SCSI Host Adapters by पूर्णांकerrogating the PCI Configuration Space on PCI
  machines as well as from the list of standard BusLogic MultiMaster ISA
  I/O Addresses.  It वापसs the number of PCI MultiMaster Host Adapters found.
*/

अटल पूर्णांक __init blogic_init_mm_probeinfo(काष्ठा blogic_adapter *adapter)
अणु
	काष्ठा blogic_probeinfo *pr_probeinfo =
		&blogic_probeinfo_list[blogic_probeinfo_count];
	पूर्णांक nonpr_mmindex = blogic_probeinfo_count + 1;
	पूर्णांक nonpr_mmcount = 0, mmcount = 0;
	bool क्रमce_scan_order = false;
	bool क्रमce_scan_order_checked = false;
	काष्ठा pci_dev *pci_device = शून्य;
	पूर्णांक i;
	अगर (blogic_probeinfo_count >= BLOGIC_MAX_ADAPTERS)
		वापस 0;
	blogic_probeinfo_count++;
	/*
	   Iterate over the MultiMaster PCI Host Adapters.  For each
	   क्रमागतerated host adapter, determine whether its ISA Compatible
	   I/O Port is enabled and अगर so, whether it is asचिन्हित the
	   Primary I/O Address.  A host adapter that is asचिन्हित the
	   Primary I/O Address will always be the preferred boot device.
	   The MultiMaster BIOS will first recognize a host adapter at
	   the Primary I/O Address, then any other PCI host adapters,
	   and finally any host adapters located at the reमुख्यing
	   standard ISA I/O Addresses.  When a PCI host adapter is found
	   with its ISA Compatible I/O Port enabled, a command is issued
	   to disable the ISA Compatible I/O Port, and it is noted that the
	   particular standard ISA I/O Address need not be probed.
	 */
	pr_probeinfo->io_addr = 0;
	जबतक ((pci_device = pci_get_device(PCI_VENDOR_ID_BUSLOGIC,
					PCI_DEVICE_ID_BUSLOGIC_MULTIMASTER,
					pci_device)) != शून्य) अणु
		काष्ठा blogic_adapter *host_adapter = adapter;
		काष्ठा blogic_adapter_info adapter_info;
		क्रमागत blogic_isa_ioport mod_ioaddr_req;
		अचिन्हित अक्षर bus;
		अचिन्हित अक्षर device;
		अचिन्हित पूर्णांक irq_ch;
		अचिन्हित दीर्घ base_addr0;
		अचिन्हित दीर्घ base_addr1;
		अचिन्हित दीर्घ io_addr;
		अचिन्हित दीर्घ pci_addr;

		अगर (pci_enable_device(pci_device))
			जारी;

		अगर (dma_set_mask(&pci_device->dev, DMA_BIT_MASK(32)))
			जारी;

		bus = pci_device->bus->number;
		device = pci_device->devfn >> 3;
		irq_ch = pci_device->irq;
		io_addr = base_addr0 = pci_resource_start(pci_device, 0);
		pci_addr = base_addr1 = pci_resource_start(pci_device, 1);

		अगर (pci_resource_flags(pci_device, 0) & IORESOURCE_MEM) अणु
			blogic_err("BusLogic: Base Address0 0x%lX not I/O for MultiMaster Host Adapter\n", शून्य, base_addr0);
			blogic_err("at PCI Bus %d Device %d I/O Address 0x%lX\n", शून्य, bus, device, io_addr);
			जारी;
		पूर्ण
		अगर (pci_resource_flags(pci_device, 1) & IORESOURCE_IO) अणु
			blogic_err("BusLogic: Base Address1 0x%lX not Memory for MultiMaster Host Adapter\n", शून्य, base_addr1);
			blogic_err("at PCI Bus %d Device %d PCI Address 0x%lX\n", शून्य, bus, device, pci_addr);
			जारी;
		पूर्ण
		अगर (irq_ch == 0) अणु
			blogic_err("BusLogic: IRQ Channel %d invalid for MultiMaster Host Adapter\n", शून्य, irq_ch);
			blogic_err("at PCI Bus %d Device %d I/O Address 0x%lX\n", शून्य, bus, device, io_addr);
			जारी;
		पूर्ण
		अगर (blogic_global_options.trace_probe) अणु
			blogic_notice("BusLogic: PCI MultiMaster Host Adapter detected at\n", शून्य);
			blogic_notice("BusLogic: PCI Bus %d Device %d I/O Address 0x%lX PCI Address 0x%lX\n", शून्य, bus, device, io_addr, pci_addr);
		पूर्ण
		/*
		   Issue the Inquire PCI Host Adapter Inक्रमmation command to determine
		   the ISA Compatible I/O Port.  If the ISA Compatible I/O Port is
		   known and enabled, note that the particular Standard ISA I/O
		   Address should not be probed.
		 */
		host_adapter->io_addr = io_addr;
		blogic_पूर्णांकreset(host_adapter);
		अगर (blogic_cmd(host_adapter, BLOGIC_INQ_PCI_INFO, शून्य, 0,
				&adapter_info, माप(adapter_info)) !=
				माप(adapter_info))
			adapter_info.isa_port = BLOGIC_IO_DISABLE;
		/*
		   Issue the Modअगरy I/O Address command to disable the
		   ISA Compatible I/O Port. On PCI Host Adapters, the
		   Modअगरy I/O Address command allows modअगरication of the
		   ISA compatible I/O Address that the Host Adapter
		   responds to; it करोes not affect the PCI compliant
		   I/O Address asचिन्हित at प्रणाली initialization.
		 */
		mod_ioaddr_req = BLOGIC_IO_DISABLE;
		blogic_cmd(host_adapter, BLOGIC_MOD_IOADDR, &mod_ioaddr_req,
				माप(mod_ioaddr_req), शून्य, 0);
		/*
		   For the first MultiMaster Host Adapter क्रमागतerated,
		   issue the Fetch Host Adapter Local RAM command to पढ़ो
		   byte 45 of the AutoSCSI area, क्रम the setting of the
		   "Use Bus And Device # For PCI Scanning Seq." option.
		   Issue the Inquire Board ID command since this option is
		   only valid क्रम the BT-948/958/958D.
		 */
		अगर (!क्रमce_scan_order_checked) अणु
			काष्ठा blogic_fetch_localram fetch_localram;
			काष्ठा blogic_स्वतःscsi_byte45 स्वतःscsi_byte45;
			काष्ठा blogic_board_id id;

			fetch_localram.offset = BLOGIC_AUTOSCSI_BASE + 45;
			fetch_localram.count = माप(स्वतःscsi_byte45);
			blogic_cmd(host_adapter, BLOGIC_FETCH_LOCALRAM,
					&fetch_localram, माप(fetch_localram),
					&स्वतःscsi_byte45,
					माप(स्वतःscsi_byte45));
			blogic_cmd(host_adapter, BLOGIC_GET_BOARD_ID, शून्य, 0,
					&id, माप(id));
			अगर (id.fw_ver_digit1 == '5')
				क्रमce_scan_order =
					स्वतःscsi_byte45.क्रमce_scan_order;
			क्रमce_scan_order_checked = true;
		पूर्ण
		/*
		   Determine whether this MultiMaster Host Adapter has its
		   ISA Compatible I/O Port enabled and is asचिन्हित the
		   Primary I/O Address. If it करोes, then it is the Primary
		   MultiMaster Host Adapter and must be recognized first.
		   If it करोes not, then it is added to the list क्रम probing
		   after any Primary MultiMaster Host Adapter is probed.
		 */
		अगर (adapter_info.isa_port == BLOGIC_IO_330) अणु
			pr_probeinfo->adapter_type = BLOGIC_MULTIMASTER;
			pr_probeinfo->adapter_bus_type = BLOGIC_PCI_BUS;
			pr_probeinfo->io_addr = io_addr;
			pr_probeinfo->pci_addr = pci_addr;
			pr_probeinfo->bus = bus;
			pr_probeinfo->dev = device;
			pr_probeinfo->irq_ch = irq_ch;
			pr_probeinfo->pci_device = pci_dev_get(pci_device);
			mmcount++;
		पूर्ण अन्यथा अगर (blogic_probeinfo_count < BLOGIC_MAX_ADAPTERS) अणु
			काष्ठा blogic_probeinfo *probeinfo =
				&blogic_probeinfo_list[blogic_probeinfo_count++];
			probeinfo->adapter_type = BLOGIC_MULTIMASTER;
			probeinfo->adapter_bus_type = BLOGIC_PCI_BUS;
			probeinfo->io_addr = io_addr;
			probeinfo->pci_addr = pci_addr;
			probeinfo->bus = bus;
			probeinfo->dev = device;
			probeinfo->irq_ch = irq_ch;
			probeinfo->pci_device = pci_dev_get(pci_device);
			nonpr_mmcount++;
			mmcount++;
		पूर्ण अन्यथा
			blogic_warn("BusLogic: Too many Host Adapters detected\n", शून्य);
	पूर्ण
	/*
	   If the AutoSCSI "Use Bus And Device # For PCI Scanning Seq."
	   option is ON क्रम the first क्रमागतerated MultiMaster Host Adapter,
	   and अगर that host adapter is a BT-948/958/958D, then the
	   MultiMaster BIOS will recognize MultiMaster Host Adapters in
	   the order of increasing PCI Bus and Device Number. In that हाल,
	   sort the probe inक्रमmation पूर्णांकo the same order the BIOS uses.
	   If this option is OFF, then the MultiMaster BIOS will recognize
	   MultiMaster Host Adapters in the order they are क्रमागतerated by
	   the PCI BIOS, and hence no sorting is necessary.
	 */
	अगर (क्रमce_scan_order)
		blogic_sort_probeinfo(&blogic_probeinfo_list[nonpr_mmindex],
					nonpr_mmcount);
	/*
	   Iterate over the older non-compliant MultiMaster PCI Host Adapters,
	   noting the PCI bus location and asचिन्हित IRQ Channel.
	 */
	pci_device = शून्य;
	जबतक ((pci_device = pci_get_device(PCI_VENDOR_ID_BUSLOGIC,
					PCI_DEVICE_ID_BUSLOGIC_MULTIMASTER_NC,
					pci_device)) != शून्य) अणु
		अचिन्हित अक्षर bus;
		अचिन्हित अक्षर device;
		अचिन्हित पूर्णांक irq_ch;
		अचिन्हित दीर्घ io_addr;

		अगर (pci_enable_device(pci_device))
			जारी;

		अगर (dma_set_mask(&pci_device->dev, DMA_BIT_MASK(32)))
			जारी;

		bus = pci_device->bus->number;
		device = pci_device->devfn >> 3;
		irq_ch = pci_device->irq;
		io_addr = pci_resource_start(pci_device, 0);

		अगर (io_addr == 0 || irq_ch == 0)
			जारी;
		क्रम (i = 0; i < blogic_probeinfo_count; i++) अणु
			काष्ठा blogic_probeinfo *probeinfo =
						&blogic_probeinfo_list[i];
			अगर (probeinfo->io_addr == io_addr &&
				probeinfo->adapter_type == BLOGIC_MULTIMASTER) अणु
				probeinfo->adapter_bus_type = BLOGIC_PCI_BUS;
				probeinfo->pci_addr = 0;
				probeinfo->bus = bus;
				probeinfo->dev = device;
				probeinfo->irq_ch = irq_ch;
				probeinfo->pci_device = pci_dev_get(pci_device);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस mmcount;
पूर्ण


/*
  blogic_init_fp_probeinfo initializes the list of I/O Address
  and Bus Probe Inक्रमmation to be checked क्रम potential BusLogic FlashPoपूर्णांक
  Host Adapters by पूर्णांकerrogating the PCI Configuration Space.  It वापसs the
  number of FlashPoपूर्णांक Host Adapters found.
*/

अटल पूर्णांक __init blogic_init_fp_probeinfo(काष्ठा blogic_adapter *adapter)
अणु
	पूर्णांक fpindex = blogic_probeinfo_count, fpcount = 0;
	काष्ठा pci_dev *pci_device = शून्य;
	/*
	   Interrogate PCI Configuration Space क्रम any FlashPoपूर्णांक Host Adapters.
	 */
	जबतक ((pci_device = pci_get_device(PCI_VENDOR_ID_BUSLOGIC,
					PCI_DEVICE_ID_BUSLOGIC_FLASHPOINT,
					pci_device)) != शून्य) अणु
		अचिन्हित अक्षर bus;
		अचिन्हित अक्षर device;
		अचिन्हित पूर्णांक irq_ch;
		अचिन्हित दीर्घ base_addr0;
		अचिन्हित दीर्घ base_addr1;
		अचिन्हित दीर्घ io_addr;
		अचिन्हित दीर्घ pci_addr;

		अगर (pci_enable_device(pci_device))
			जारी;

		अगर (dma_set_mask(&pci_device->dev, DMA_BIT_MASK(32)))
			जारी;

		bus = pci_device->bus->number;
		device = pci_device->devfn >> 3;
		irq_ch = pci_device->irq;
		io_addr = base_addr0 = pci_resource_start(pci_device, 0);
		pci_addr = base_addr1 = pci_resource_start(pci_device, 1);
#अगर_घोषित CONFIG_SCSI_FLASHPOINT
		अगर (pci_resource_flags(pci_device, 0) & IORESOURCE_MEM) अणु
			blogic_err("BusLogic: Base Address0 0x%lX not I/O for FlashPoint Host Adapter\n", शून्य, base_addr0);
			blogic_err("at PCI Bus %d Device %d I/O Address 0x%lX\n", शून्य, bus, device, io_addr);
			जारी;
		पूर्ण
		अगर (pci_resource_flags(pci_device, 1) & IORESOURCE_IO) अणु
			blogic_err("BusLogic: Base Address1 0x%lX not Memory for FlashPoint Host Adapter\n", शून्य, base_addr1);
			blogic_err("at PCI Bus %d Device %d PCI Address 0x%lX\n", शून्य, bus, device, pci_addr);
			जारी;
		पूर्ण
		अगर (irq_ch == 0) अणु
			blogic_err("BusLogic: IRQ Channel %d invalid for FlashPoint Host Adapter\n", शून्य, irq_ch);
			blogic_err("at PCI Bus %d Device %d I/O Address 0x%lX\n", शून्य, bus, device, io_addr);
			जारी;
		पूर्ण
		अगर (blogic_global_options.trace_probe) अणु
			blogic_notice("BusLogic: FlashPoint Host Adapter detected at\n", शून्य);
			blogic_notice("BusLogic: PCI Bus %d Device %d I/O Address 0x%lX PCI Address 0x%lX\n", शून्य, bus, device, io_addr, pci_addr);
		पूर्ण
		अगर (blogic_probeinfo_count < BLOGIC_MAX_ADAPTERS) अणु
			काष्ठा blogic_probeinfo *probeinfo =
				&blogic_probeinfo_list[blogic_probeinfo_count++];
			probeinfo->adapter_type = BLOGIC_FLASHPOINT;
			probeinfo->adapter_bus_type = BLOGIC_PCI_BUS;
			probeinfo->io_addr = io_addr;
			probeinfo->pci_addr = pci_addr;
			probeinfo->bus = bus;
			probeinfo->dev = device;
			probeinfo->irq_ch = irq_ch;
			probeinfo->pci_device = pci_dev_get(pci_device);
			fpcount++;
		पूर्ण अन्यथा
			blogic_warn("BusLogic: Too many Host Adapters detected\n", शून्य);
#अन्यथा
		blogic_err("BusLogic: FlashPoint Host Adapter detected at PCI Bus %d Device %d\n", शून्य, bus, device);
		blogic_err("BusLogic: I/O Address 0x%lX PCI Address 0x%lX, irq %d, but FlashPoint\n", शून्य, io_addr, pci_addr, irq_ch);
		blogic_err("BusLogic: support was omitted in this kernel configuration.\n", शून्य);
#पूर्ण_अगर
	पूर्ण
	/*
	   The FlashPoपूर्णांक BIOS will scan क्रम FlashPoपूर्णांक Host Adapters in the order of
	   increasing PCI Bus and Device Number, so sort the probe inक्रमmation पूर्णांकo
	   the same order the BIOS uses.
	 */
	blogic_sort_probeinfo(&blogic_probeinfo_list[fpindex], fpcount);
	वापस fpcount;
पूर्ण


/*
  blogic_init_probeinfo_list initializes the list of I/O Address and Bus
  Probe Inक्रमmation to be checked क्रम potential BusLogic SCSI Host Adapters by
  पूर्णांकerrogating the PCI Configuration Space on PCI machines as well as from the
  list of standard BusLogic MultiMaster ISA I/O Addresses.  By शेष, अगर both
  FlashPoपूर्णांक and PCI MultiMaster Host Adapters are present, this driver will
  probe क्रम FlashPoपूर्णांक Host Adapters first unless the BIOS primary disk is
  controlled by the first PCI MultiMaster Host Adapter, in which हाल
  MultiMaster Host Adapters will be probed first.  The BusLogic Driver Options
  specअगरications "MultiMasterFirst" and "FlashPointFirst" can be used to क्रमce
  a particular probe order.
*/

अटल व्योम __init blogic_init_probeinfo_list(काष्ठा blogic_adapter *adapter)
अणु
	/*
	   If a PCI BIOS is present, पूर्णांकerrogate it क्रम MultiMaster and
	   FlashPoपूर्णांक Host Adapters; otherwise, शेष to the standard
	   ISA MultiMaster probe.
	 */
	अगर (!blogic_probe_options.noprobe_pci) अणु
		अगर (blogic_probe_options.multimaster_first) अणु
			blogic_init_mm_probeinfo(adapter);
			blogic_init_fp_probeinfo(adapter);
		पूर्ण अन्यथा अगर (blogic_probe_options.flashpoपूर्णांक_first) अणु
			blogic_init_fp_probeinfo(adapter);
			blogic_init_mm_probeinfo(adapter);
		पूर्ण अन्यथा अणु
			पूर्णांक fpcount = blogic_init_fp_probeinfo(adapter);
			पूर्णांक mmcount = blogic_init_mm_probeinfo(adapter);
			अगर (fpcount > 0 && mmcount > 0) अणु
				काष्ठा blogic_probeinfo *probeinfo =
					&blogic_probeinfo_list[fpcount];
				काष्ठा blogic_adapter *myadapter = adapter;
				काष्ठा blogic_fetch_localram fetch_localram;
				काष्ठा blogic_bios_drvmap d0_mapbyte;

				जबतक (probeinfo->adapter_bus_type !=
						BLOGIC_PCI_BUS)
					probeinfo++;
				myadapter->io_addr = probeinfo->io_addr;
				fetch_localram.offset =
					BLOGIC_BIOS_BASE + BLOGIC_BIOS_DRVMAP;
				fetch_localram.count = माप(d0_mapbyte);
				blogic_cmd(myadapter, BLOGIC_FETCH_LOCALRAM,
						&fetch_localram,
						माप(fetch_localram),
						&d0_mapbyte,
						माप(d0_mapbyte));
				/*
				   If the Map Byte क्रम BIOS Drive 0 indicates
				   that BIOS Drive 0 is controlled by this
				   PCI MultiMaster Host Adapter, then reverse
				   the probe order so that MultiMaster Host
				   Adapters are probed beक्रमe FlashPoपूर्णांक Host
				   Adapters.
				 */
				अगर (d0_mapbyte.diskgeom != BLOGIC_BIOS_NODISK) अणु
					काष्ठा blogic_probeinfo saved_probeinfo[BLOGIC_MAX_ADAPTERS];
					पूर्णांक mmcount = blogic_probeinfo_count - fpcount;

					स_नकल(saved_probeinfo,
						blogic_probeinfo_list,
						blogic_probeinfo_count * माप(काष्ठा blogic_probeinfo));
					स_नकल(&blogic_probeinfo_list[0],
						&saved_probeinfo[fpcount],
						mmcount * माप(काष्ठा blogic_probeinfo));
					स_नकल(&blogic_probeinfo_list[mmcount],
						&saved_probeinfo[0],
						fpcount * माप(काष्ठा blogic_probeinfo));
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण


/*
  blogic_failure prपूर्णांकs a standardized error message, and then वापसs false.
*/

अटल bool blogic_failure(काष्ठा blogic_adapter *adapter, अक्षर *msg)
अणु
	blogic_announce_drvr(adapter);
	अगर (adapter->adapter_bus_type == BLOGIC_PCI_BUS) अणु
		blogic_err("While configuring BusLogic PCI Host Adapter at\n",
				adapter);
		blogic_err("Bus %d Device %d I/O Address 0x%lX PCI Address 0x%lX:\n", adapter, adapter->bus, adapter->dev, adapter->io_addr, adapter->pci_addr);
	पूर्ण अन्यथा
		blogic_err("While configuring BusLogic Host Adapter at I/O Address 0x%lX:\n", adapter, adapter->io_addr);
	blogic_err("%s FAILED - DETACHING\n", adapter, msg);
	अगर (blogic_cmd_failure_reason != शून्य)
		blogic_err("ADDITIONAL FAILURE INFO - %s\n", adapter,
				blogic_cmd_failure_reason);
	वापस false;
पूर्ण


/*
  blogic_probe probes क्रम a BusLogic Host Adapter.
*/

अटल bool __init blogic_probe(काष्ठा blogic_adapter *adapter)
अणु
	जोड़ blogic_stat_reg statusreg;
	जोड़ blogic_पूर्णांक_reg पूर्णांकreg;
	जोड़ blogic_geo_reg georeg;
	/*
	   FlashPoपूर्णांक Host Adapters are Probed by the FlashPoपूर्णांक SCCB Manager.
	 */
	अगर (blogic_flashpoपूर्णांक_type(adapter)) अणु
		काष्ठा fpoपूर्णांक_info *fpinfo = &adapter->fpinfo;
		fpinfo->base_addr = (u32) adapter->io_addr;
		fpinfo->irq_ch = adapter->irq_ch;
		fpinfo->present = false;
		अगर (!(FlashPoपूर्णांक_ProbeHostAdapter(fpinfo) == 0 &&
					fpinfo->present)) अणु
			blogic_err("BusLogic: FlashPoint Host Adapter detected at PCI Bus %d Device %d\n", adapter, adapter->bus, adapter->dev);
			blogic_err("BusLogic: I/O Address 0x%lX PCI Address 0x%lX, but FlashPoint\n", adapter, adapter->io_addr, adapter->pci_addr);
			blogic_err("BusLogic: Probe Function failed to validate it.\n", adapter);
			वापस false;
		पूर्ण
		अगर (blogic_global_options.trace_probe)
			blogic_notice("BusLogic_Probe(0x%lX): FlashPoint Found\n", adapter, adapter->io_addr);
		/*
		   Indicate the Host Adapter Probe completed successfully.
		 */
		वापस true;
	पूर्ण
	/*
	   Read the Status, Interrupt, and Geometry Registers to test अगर there are I/O
	   ports that respond, and to check the values to determine अगर they are from a
	   BusLogic Host Adapter.  A nonexistent I/O port will वापस 0xFF, in which
	   हाल there is definitely no BusLogic Host Adapter at this base I/O Address.
	   The test here is a subset of that used by the BusLogic Host Adapter BIOS.
	 */
	statusreg.all = blogic_rdstatus(adapter);
	पूर्णांकreg.all = blogic_rdपूर्णांक(adapter);
	georeg.all = blogic_rdgeom(adapter);
	अगर (blogic_global_options.trace_probe)
		blogic_notice("BusLogic_Probe(0x%lX): Status 0x%02X, Interrupt 0x%02X, Geometry 0x%02X\n", adapter, adapter->io_addr, statusreg.all, पूर्णांकreg.all, georeg.all);
	अगर (statusreg.all == 0 || statusreg.sr.diag_active ||
			statusreg.sr.cmd_param_busy || statusreg.sr.rsvd ||
			statusreg.sr.cmd_invalid || पूर्णांकreg.ir.rsvd != 0)
		वापस false;
	/*
	   Check the unकरोcumented Geometry Register to test अगर there is
	   an I/O port that responded.  Adaptec Host Adapters करो not
	   implement the Geometry Register, so this test helps serve to
	   aव्योम incorrectly recognizing an Adaptec 1542A or 1542B as a
	   BusLogic.  Unक्रमtunately, the Adaptec 1542C series करोes respond
	   to the Geometry Register I/O port, but it will be rejected
	   later when the Inquire Extended Setup Inक्रमmation command is
	   issued in blogic_checkadapter.  The AMI FastDisk Host Adapter
	   is a BusLogic clone that implements the same पूर्णांकerface as
	   earlier BusLogic Host Adapters, including the unकरोcumented
	   commands, and is thereक्रमe supported by this driver. However,
	   the AMI FastDisk always वापसs 0x00 upon पढ़ोing the Geometry
	   Register, so the extended translation option should always be
	   left disabled on the AMI FastDisk.
	 */
	अगर (georeg.all == 0xFF)
		वापस false;
	/*
	   Indicate the Host Adapter Probe completed successfully.
	 */
	वापस true;
पूर्ण


/*
  blogic_hwreset issues a Hardware Reset to the Host Adapter
  and रुकोs क्रम Host Adapter Diagnostics to complete.  If hard_reset is true, a
  Hard Reset is perक्रमmed which also initiates a SCSI Bus Reset.  Otherwise, a
  Soft Reset is perक्रमmed which only resets the Host Adapter without क्रमcing a
  SCSI Bus Reset.
*/

अटल bool blogic_hwreset(काष्ठा blogic_adapter *adapter, bool hard_reset)
अणु
	जोड़ blogic_stat_reg statusreg;
	पूर्णांक समयout;
	/*
	   FlashPoपूर्णांक Host Adapters are Hard Reset by the FlashPoपूर्णांक
	   SCCB Manager.
	 */
	अगर (blogic_flashpoपूर्णांक_type(adapter)) अणु
		काष्ठा fpoपूर्णांक_info *fpinfo = &adapter->fpinfo;
		fpinfo->softreset = !hard_reset;
		fpinfo->report_underrun = true;
		adapter->cardhandle =
			FlashPoपूर्णांक_HardwareResetHostAdapter(fpinfo);
		अगर (adapter->cardhandle == (व्योम *)FPOINT_BADCARD_HANDLE)
			वापस false;
		/*
		   Indicate the Host Adapter Hard Reset completed successfully.
		 */
		वापस true;
	पूर्ण
	/*
	   Issue a Hard Reset or Soft Reset Command to the Host Adapter.
	   The Host Adapter should respond by setting Diagnostic Active in
	   the Status Register.
	 */
	अगर (hard_reset)
		blogic_hardreset(adapter);
	अन्यथा
		blogic_softreset(adapter);
	/*
	   Wait until Diagnostic Active is set in the Status Register.
	 */
	समयout = 5 * 10000;
	जबतक (--समयout >= 0) अणु
		statusreg.all = blogic_rdstatus(adapter);
		अगर (statusreg.sr.diag_active)
			अवरोध;
		udelay(100);
	पूर्ण
	अगर (blogic_global_options.trace_hw_reset)
		blogic_notice("BusLogic_HardwareReset(0x%lX): Diagnostic Active, Status 0x%02X\n", adapter, adapter->io_addr, statusreg.all);
	अगर (समयout < 0)
		वापस false;
	/*
	   Wait 100 microseconds to allow completion of any initial diagnostic
	   activity which might leave the contents of the Status Register
	   unpredictable.
	 */
	udelay(100);
	/*
	   Wait until Diagnostic Active is reset in the Status Register.
	 */
	समयout = 10 * 10000;
	जबतक (--समयout >= 0) अणु
		statusreg.all = blogic_rdstatus(adapter);
		अगर (!statusreg.sr.diag_active)
			अवरोध;
		udelay(100);
	पूर्ण
	अगर (blogic_global_options.trace_hw_reset)
		blogic_notice("BusLogic_HardwareReset(0x%lX): Diagnostic Completed, Status 0x%02X\n", adapter, adapter->io_addr, statusreg.all);
	अगर (समयout < 0)
		वापस false;
	/*
	   Wait until at least one of the Diagnostic Failure, Host Adapter
	   Ready, or Data In Register Ready bits is set in the Status Register.
	 */
	समयout = 10000;
	जबतक (--समयout >= 0) अणु
		statusreg.all = blogic_rdstatus(adapter);
		अगर (statusreg.sr.diag_failed || statusreg.sr.adapter_पढ़ोy ||
				statusreg.sr.datain_पढ़ोy)
			अवरोध;
		udelay(100);
	पूर्ण
	अगर (blogic_global_options.trace_hw_reset)
		blogic_notice("BusLogic_HardwareReset(0x%lX): Host Adapter Ready, Status 0x%02X\n", adapter, adapter->io_addr, statusreg.all);
	अगर (समयout < 0)
		वापस false;
	/*
	   If Diagnostic Failure is set or Host Adapter Ready is reset,
	   then an error occurred during the Host Adapter diagnostics.
	   If Data In Register Ready is set, then there is an Error Code
	   available.
	 */
	अगर (statusreg.sr.diag_failed || !statusreg.sr.adapter_पढ़ोy) अणु
		blogic_cmd_failure_reason = शून्य;
		blogic_failure(adapter, "HARD RESET DIAGNOSTICS");
		blogic_err("HOST ADAPTER STATUS REGISTER = %02X\n", adapter,
				statusreg.all);
		अगर (statusreg.sr.datain_पढ़ोy)
			blogic_err("HOST ADAPTER ERROR CODE = %d\n", adapter,
					blogic_rddatain(adapter));
		वापस false;
	पूर्ण
	/*
	   Indicate the Host Adapter Hard Reset completed successfully.
	 */
	वापस true;
पूर्ण


/*
  blogic_checkadapter checks to be sure this really is a BusLogic
  Host Adapter.
*/

अटल bool __init blogic_checkadapter(काष्ठा blogic_adapter *adapter)
अणु
	काष्ठा blogic_ext_setup ext_setupinfo;
	अचिन्हित अक्षर req_replylen;
	bool result = true;
	/*
	   FlashPoपूर्णांक Host Adapters करो not require this protection.
	 */
	अगर (blogic_flashpoपूर्णांक_type(adapter))
		वापस true;
	/*
	   Issue the Inquire Extended Setup Inक्रमmation command. Only genuine
	   BusLogic Host Adapters and true clones support this command.
	   Adaptec 1542C series Host Adapters that respond to the Geometry
	   Register I/O port will fail this command.
	 */
	req_replylen = माप(ext_setupinfo);
	अगर (blogic_cmd(adapter, BLOGIC_INQ_EXTSETUP, &req_replylen,
				माप(req_replylen), &ext_setupinfo,
				माप(ext_setupinfo)) != माप(ext_setupinfo))
		result = false;
	/*
	   Provide tracing inक्रमmation अगर requested and वापस.
	 */
	अगर (blogic_global_options.trace_probe)
		blogic_notice("BusLogic_Check(0x%lX): MultiMaster %s\n", adapter,
				adapter->io_addr,
				(result ? "Found" : "Not Found"));
	वापस result;
पूर्ण


/*
  blogic_rdconfig पढ़ोs the Configuration Inक्रमmation
  from Host Adapter and initializes the Host Adapter काष्ठाure.
*/

अटल bool __init blogic_rdconfig(काष्ठा blogic_adapter *adapter)
अणु
	काष्ठा blogic_board_id id;
	काष्ठा blogic_config config;
	काष्ठा blogic_setup_info setupinfo;
	काष्ठा blogic_ext_setup ext_setupinfo;
	अचिन्हित अक्षर model[5];
	अचिन्हित अक्षर fw_ver_digit3;
	अचिन्हित अक्षर fw_ver_letter;
	काष्ठा blogic_adapter_info adapter_info;
	काष्ठा blogic_fetch_localram fetch_localram;
	काष्ठा blogic_स्वतःscsi स्वतःscsi;
	जोड़ blogic_geo_reg georeg;
	अचिन्हित अक्षर req_replylen;
	अचिन्हित अक्षर *tgt, ch;
	पूर्णांक tgt_id, i;
	/*
	   Configuration Inक्रमmation क्रम FlashPoपूर्णांक Host Adapters is
	   provided in the fpoपूर्णांक_info काष्ठाure by the FlashPoपूर्णांक
	   SCCB Manager's Probe Function. Initialize fields in the
	   Host Adapter काष्ठाure from the fpoपूर्णांक_info काष्ठाure.
	 */
	अगर (blogic_flashpoपूर्णांक_type(adapter)) अणु
		काष्ठा fpoपूर्णांक_info *fpinfo = &adapter->fpinfo;
		tgt = adapter->model;
		*tgt++ = 'B';
		*tgt++ = 'T';
		*tgt++ = '-';
		क्रम (i = 0; i < माप(fpinfo->model); i++)
			*tgt++ = fpinfo->model[i];
		*tgt++ = '\0';
		म_नकल(adapter->fw_ver, FLASHPOINT_FW_VER);
		adapter->scsi_id = fpinfo->scsi_id;
		adapter->ext_trans_enable = fpinfo->ext_trans_enable;
		adapter->parity = fpinfo->parity;
		adapter->reset_enabled = !fpinfo->softreset;
		adapter->level_पूर्णांक = true;
		adapter->wide = fpinfo->wide;
		adapter->dअगरferential = false;
		adapter->scam = true;
		adapter->ultra = true;
		adapter->ext_lun = true;
		adapter->terminfo_valid = true;
		adapter->low_term = fpinfo->low_term;
		adapter->high_term = fpinfo->high_term;
		adapter->scam_enabled = fpinfo->scam_enabled;
		adapter->scam_lev2 = fpinfo->scam_lev2;
		adapter->drvr_sglimit = BLOGIC_SG_LIMIT;
		adapter->maxdev = (adapter->wide ? 16 : 8);
		adapter->maxlun = 32;
		adapter->initccbs = 4 * BLOGIC_CCB_GRP_ALLOCSIZE;
		adapter->inc_ccbs = BLOGIC_CCB_GRP_ALLOCSIZE;
		adapter->drvr_qdepth = 255;
		adapter->adapter_qdepth = adapter->drvr_qdepth;
		adapter->sync_ok = fpinfo->sync_ok;
		adapter->fast_ok = fpinfo->fast_ok;
		adapter->ultra_ok = fpinfo->ultra_ok;
		adapter->wide_ok = fpinfo->wide_ok;
		adapter->discon_ok = fpinfo->discon_ok;
		adapter->tagq_ok = 0xFFFF;
		जाओ common;
	पूर्ण
	/*
	   Issue the Inquire Board ID command.
	 */
	अगर (blogic_cmd(adapter, BLOGIC_GET_BOARD_ID, शून्य, 0, &id,
				माप(id)) != माप(id))
		वापस blogic_failure(adapter, "INQUIRE BOARD ID");
	/*
	   Issue the Inquire Configuration command.
	 */
	अगर (blogic_cmd(adapter, BLOGIC_INQ_CONFIG, शून्य, 0, &config,
				माप(config))
	    != माप(config))
		वापस blogic_failure(adapter, "INQUIRE CONFIGURATION");
	/*
	   Issue the Inquire Setup Inक्रमmation command.
	 */
	req_replylen = माप(setupinfo);
	अगर (blogic_cmd(adapter, BLOGIC_INQ_SETUPINFO, &req_replylen,
				माप(req_replylen), &setupinfo,
				माप(setupinfo)) != माप(setupinfo))
		वापस blogic_failure(adapter, "INQUIRE SETUP INFORMATION");
	/*
	   Issue the Inquire Extended Setup Inक्रमmation command.
	 */
	req_replylen = माप(ext_setupinfo);
	अगर (blogic_cmd(adapter, BLOGIC_INQ_EXTSETUP, &req_replylen,
				माप(req_replylen), &ext_setupinfo,
				माप(ext_setupinfo)) != माप(ext_setupinfo))
		वापस blogic_failure(adapter,
					"INQUIRE EXTENDED SETUP INFORMATION");
	/*
	   Issue the Inquire Firmware Version 3rd Digit command.
	 */
	fw_ver_digit3 = '\0';
	अगर (id.fw_ver_digit1 > '0')
		अगर (blogic_cmd(adapter, BLOGIC_INQ_FWVER_D3, शून्य, 0,
				&fw_ver_digit3,
				माप(fw_ver_digit3)) != माप(fw_ver_digit3))
			वापस blogic_failure(adapter,
						"INQUIRE FIRMWARE 3RD DIGIT");
	/*
	   Issue the Inquire Host Adapter Model Number command.
	 */
	अगर (ext_setupinfo.bus_type == 'A' && id.fw_ver_digit1 == '2')
		/* BusLogic BT-542B ISA 2.xx */
		म_नकल(model, "542B");
	अन्यथा अगर (ext_setupinfo.bus_type == 'E' && id.fw_ver_digit1 == '2' &&
			(id.fw_ver_digit2 <= '1' || (id.fw_ver_digit2 == '2' &&
						     fw_ver_digit3 == '0')))
		/* BusLogic BT-742A EISA 2.1x or 2.20 */
		म_नकल(model, "742A");
	अन्यथा अगर (ext_setupinfo.bus_type == 'E' && id.fw_ver_digit1 == '0')
		/* AMI FastDisk EISA Series 441 0.x */
		म_नकल(model, "747A");
	अन्यथा अणु
		req_replylen = माप(model);
		अगर (blogic_cmd(adapter, BLOGIC_INQ_MODELNO, &req_replylen,
					माप(req_replylen), &model,
					माप(model)) != माप(model))
			वापस blogic_failure(adapter,
					"INQUIRE HOST ADAPTER MODEL NUMBER");
	पूर्ण
	/*
	   BusLogic MultiMaster Host Adapters can be identअगरied by their
	   model number and the major version number of their firmware
	   as follows:

	   5.xx       BusLogic "W" Series Host Adapters:
	   BT-948/958/958D
	   4.xx       BusLogic "C" Series Host Adapters:
	   BT-946C/956C/956CD/747C/757C/757CD/445C/545C/540CF
	   3.xx       BusLogic "S" Series Host Adapters:
	   BT-747S/747D/757S/757D/445S/545S/542D
	   BT-542B/742A (revision H)
	   2.xx       BusLogic "A" Series Host Adapters:
	   BT-542B/742A (revision G and below)
	   0.xx       AMI FastDisk VLB/EISA BusLogic Clone Host Adapter
	 */
	/*
	   Save the Model Name and Host Adapter Name in the Host Adapter
	   काष्ठाure.
	 */
	tgt = adapter->model;
	*tgt++ = 'B';
	*tgt++ = 'T';
	*tgt++ = '-';
	क्रम (i = 0; i < माप(model); i++) अणु
		ch = model[i];
		अगर (ch == ' ' || ch == '\0')
			अवरोध;
		*tgt++ = ch;
	पूर्ण
	*tgt++ = '\0';
	/*
	   Save the Firmware Version in the Host Adapter काष्ठाure.
	 */
	tgt = adapter->fw_ver;
	*tgt++ = id.fw_ver_digit1;
	*tgt++ = '.';
	*tgt++ = id.fw_ver_digit2;
	अगर (fw_ver_digit3 != ' ' && fw_ver_digit3 != '\0')
		*tgt++ = fw_ver_digit3;
	*tgt = '\0';
	/*
	   Issue the Inquire Firmware Version Letter command.
	 */
	अगर (म_भेद(adapter->fw_ver, "3.3") >= 0) अणु
		अगर (blogic_cmd(adapter, BLOGIC_INQ_FWVER_LETTER, शून्य, 0,
				&fw_ver_letter,
				माप(fw_ver_letter)) != माप(fw_ver_letter))
			वापस blogic_failure(adapter,
					"INQUIRE FIRMWARE VERSION LETTER");
		अगर (fw_ver_letter != ' ' && fw_ver_letter != '\0')
			*tgt++ = fw_ver_letter;
		*tgt = '\0';
	पूर्ण
	/*
	   Save the Host Adapter SCSI ID in the Host Adapter काष्ठाure.
	 */
	adapter->scsi_id = config.id;
	/*
	   Determine the Bus Type and save it in the Host Adapter काष्ठाure,
	   determine and save the IRQ Channel अगर necessary, and determine
	   and save the DMA Channel क्रम ISA Host Adapters.
	 */
	adapter->adapter_bus_type =
			blogic_adater_bus_types[adapter->model[3] - '4'];
	अगर (adapter->irq_ch == 0) अणु
		अगर (config.irq_ch9)
			adapter->irq_ch = 9;
		अन्यथा अगर (config.irq_ch10)
			adapter->irq_ch = 10;
		अन्यथा अगर (config.irq_ch11)
			adapter->irq_ch = 11;
		अन्यथा अगर (config.irq_ch12)
			adapter->irq_ch = 12;
		अन्यथा अगर (config.irq_ch14)
			adapter->irq_ch = 14;
		अन्यथा अगर (config.irq_ch15)
			adapter->irq_ch = 15;
	पूर्ण
	/*
	   Determine whether Extended Translation is enabled and save it in
	   the Host Adapter काष्ठाure.
	 */
	georeg.all = blogic_rdgeom(adapter);
	adapter->ext_trans_enable = georeg.gr.ext_trans_enable;
	/*
	   Save the Scatter Gather Limits, Level Sensitive Interrupt flag, Wide
	   SCSI flag, Dअगरferential SCSI flag, SCAM Supported flag, and
	   Ultra SCSI flag in the Host Adapter काष्ठाure.
	 */
	adapter->adapter_sglimit = ext_setupinfo.sg_limit;
	adapter->drvr_sglimit = adapter->adapter_sglimit;
	अगर (adapter->adapter_sglimit > BLOGIC_SG_LIMIT)
		adapter->drvr_sglimit = BLOGIC_SG_LIMIT;
	अगर (ext_setupinfo.misc.level_पूर्णांक)
		adapter->level_पूर्णांक = true;
	adapter->wide = ext_setupinfo.wide;
	adapter->dअगरferential = ext_setupinfo.dअगरferential;
	adapter->scam = ext_setupinfo.scam;
	adapter->ultra = ext_setupinfo.ultra;
	/*
	   Determine whether Extended LUN Format CCBs are supported and save the
	   inक्रमmation in the Host Adapter काष्ठाure.
	 */
	अगर (adapter->fw_ver[0] == '5' || (adapter->fw_ver[0] == '4' &&
				adapter->wide))
		adapter->ext_lun = true;
	/*
	   Issue the Inquire PCI Host Adapter Inक्रमmation command to पढ़ो the
	   Termination Inक्रमmation from "W" series MultiMaster Host Adapters.
	 */
	अगर (adapter->fw_ver[0] == '5') अणु
		अगर (blogic_cmd(adapter, BLOGIC_INQ_PCI_INFO, शून्य, 0,
				&adapter_info,
				माप(adapter_info)) != माप(adapter_info))
			वापस blogic_failure(adapter,
					"INQUIRE PCI HOST ADAPTER INFORMATION");
		/*
		   Save the Termination Inक्रमmation in the Host Adapter
		   काष्ठाure.
		 */
		अगर (adapter_info.genericinfo_valid) अणु
			adapter->terminfo_valid = true;
			adapter->low_term = adapter_info.low_term;
			adapter->high_term = adapter_info.high_term;
		पूर्ण
	पूर्ण
	/*
	   Issue the Fetch Host Adapter Local RAM command to पढ़ो the
	   AutoSCSI data from "W" and "C" series MultiMaster Host Adapters.
	 */
	अगर (adapter->fw_ver[0] >= '4') अणु
		fetch_localram.offset = BLOGIC_AUTOSCSI_BASE;
		fetch_localram.count = माप(स्वतःscsi);
		अगर (blogic_cmd(adapter, BLOGIC_FETCH_LOCALRAM, &fetch_localram,
					माप(fetch_localram), &स्वतःscsi,
					माप(स्वतःscsi)) != माप(स्वतःscsi))
			वापस blogic_failure(adapter,
						"FETCH HOST ADAPTER LOCAL RAM");
		/*
		   Save the Parity Checking Enabled, Bus Reset Enabled,
		   and Termination Inक्रमmation in the Host Adapter काष्ठाure.
		 */
		adapter->parity = स्वतःscsi.parity;
		adapter->reset_enabled = स्वतःscsi.reset_enabled;
		अगर (adapter->fw_ver[0] == '4') अणु
			adapter->terminfo_valid = true;
			adapter->low_term = स्वतःscsi.low_term;
			adapter->high_term = स्वतःscsi.high_term;
		पूर्ण
		/*
		   Save the Wide Permitted, Fast Permitted, Synchronous
		   Permitted, Disconnect Permitted, Ultra Permitted, and
		   SCAM Inक्रमmation in the Host Adapter काष्ठाure.
		 */
		adapter->wide_ok = स्वतःscsi.wide_ok;
		adapter->fast_ok = स्वतःscsi.fast_ok;
		adapter->sync_ok = स्वतःscsi.sync_ok;
		adapter->discon_ok = स्वतःscsi.discon_ok;
		अगर (adapter->ultra)
			adapter->ultra_ok = स्वतःscsi.ultra_ok;
		अगर (adapter->scam) अणु
			adapter->scam_enabled = स्वतःscsi.scam_enabled;
			adapter->scam_lev2 = स्वतःscsi.scam_lev2;
		पूर्ण
	पूर्ण
	/*
	   Initialize fields in the Host Adapter काष्ठाure क्रम "S" and "A"
	   series MultiMaster Host Adapters.
	 */
	अगर (adapter->fw_ver[0] < '4') अणु
		अगर (setupinfo.sync) अणु
			adapter->sync_ok = 0xFF;
			अगर (adapter->adapter_bus_type == BLOGIC_EISA_BUS) अणु
				अगर (ext_setupinfo.misc.fast_on_eisa)
					adapter->fast_ok = 0xFF;
				अगर (म_भेद(adapter->model, "BT-757") == 0)
					adapter->wide_ok = 0xFF;
			पूर्ण
		पूर्ण
		adapter->discon_ok = 0xFF;
		adapter->parity = setupinfo.parity;
		adapter->reset_enabled = true;
	पूर्ण
	/*
	   Determine the maximum number of Target IDs and Logical Units
	   supported by this driver क्रम Wide and Narrow Host Adapters.
	 */
	adapter->maxdev = (adapter->wide ? 16 : 8);
	adapter->maxlun = (adapter->ext_lun ? 32 : 8);
	/*
	   Select appropriate values क्रम the Mailbox Count, Driver Queue Depth,
	   Initial CCBs, and Incremental CCBs variables based on whether
	   or not Strict Round Robin Mode is supported.  If Strict Round
	   Robin Mode is supported, then there is no perक्रमmance degradation
	   in using the maximum possible number of Outgoing and Incoming
	   Mailboxes and allowing the Tagged and Untagged Queue Depths to
	   determine the actual utilization.  If Strict Round Robin Mode is
	   not supported, then the Host Adapter must scan all the Outgoing
	   Mailboxes whenever an Outgoing Mailbox entry is made, which can
	   cause a substantial perक्रमmance penalty.  The host adapters
	   actually have room to store the following number of CCBs
	   पूर्णांकernally; that is, they can पूर्णांकernally queue and manage this
	   many active commands on the SCSI bus simultaneously.  Perक्रमmance
	   measurements demonstrate that the Driver Queue Depth should be
	   set to the Mailbox Count, rather than the Host Adapter Queue
	   Depth (पूर्णांकernal CCB capacity), as it is more efficient to have the
	   queued commands रुकोing in Outgoing Mailboxes अगर necessary than
	   to block the process in the higher levels of the SCSI Subप्रणाली.

	   192          BT-948/958/958D
	   100          BT-946C/956C/956CD/747C/757C/757CD/445C
	   50   BT-545C/540CF
	   30   BT-747S/747D/757S/757D/445S/545S/542D/542B/742A
	 */
	अगर (adapter->fw_ver[0] == '5')
		adapter->adapter_qdepth = 192;
	अन्यथा अगर (adapter->fw_ver[0] == '4')
		adapter->adapter_qdepth = 100;
	अन्यथा
		adapter->adapter_qdepth = 30;
	अगर (म_भेद(adapter->fw_ver, "3.31") >= 0) अणु
		adapter->strict_rr = true;
		adapter->mbox_count = BLOGIC_MAX_MAILBOX;
	पूर्ण अन्यथा अणु
		adapter->strict_rr = false;
		adapter->mbox_count = 32;
	पूर्ण
	adapter->drvr_qdepth = adapter->mbox_count;
	adapter->initccbs = 4 * BLOGIC_CCB_GRP_ALLOCSIZE;
	adapter->inc_ccbs = BLOGIC_CCB_GRP_ALLOCSIZE;
	/*
	   Tagged Queuing support is available and operates properly on
	   all "W" series MultiMaster Host Adapters, on "C" series
	   MultiMaster Host Adapters with firmware version 4.22 and above,
	   and on "S" series MultiMaster Host Adapters with firmware version
	   3.35 and above.
	 */
	adapter->tagq_ok = 0;
	चयन (adapter->fw_ver[0]) अणु
	हाल '5':
		adapter->tagq_ok = 0xFFFF;
		अवरोध;
	हाल '4':
		अगर (म_भेद(adapter->fw_ver, "4.22") >= 0)
			adapter->tagq_ok = 0xFFFF;
		अवरोध;
	हाल '3':
		अगर (म_भेद(adapter->fw_ver, "3.35") >= 0)
			adapter->tagq_ok = 0xFFFF;
		अवरोध;
	पूर्ण
	/*
	   Determine the Host Adapter BIOS Address अगर the BIOS is enabled and
	   save it in the Host Adapter काष्ठाure.  The BIOS is disabled अगर the
	   bios_addr is 0.
	 */
	adapter->bios_addr = ext_setupinfo.bios_addr << 12;
	/*
	   BusLogic BT-445S Host Adapters prior to board revision E have a
	   hardware bug whereby when the BIOS is enabled, transfers to/from
	   the same address range the BIOS occupies modulo 16MB are handled
	   incorrectly.  Only properly functioning BT-445S Host Adapters
	   have firmware version 3.37.
	 */
	अगर (adapter->bios_addr > 0 &&
	    म_भेद(adapter->model, "BT-445S") == 0 &&
	    म_भेद(adapter->fw_ver, "3.37") < 0)
		वापस blogic_failure(adapter, "Too old firmware");
	/*
	   Initialize parameters common to MultiMaster and FlashPoपूर्णांक
	   Host Adapters.
	 */
common:
	/*
	   Initialize the Host Adapter Full Model Name from the Model Name.
	 */
	म_नकल(adapter->full_model, "BusLogic ");
	म_जोड़ो(adapter->full_model, adapter->model);
	/*
	   Select an appropriate value क्रम the Tagged Queue Depth either from a
	   BusLogic Driver Options specअगरication, or based on whether this Host
	   Adapter requires that ISA Bounce Buffers be used.  The Tagged Queue
	   Depth is left at 0 क्रम स्वतःmatic determination in
	   BusLogic_SelectQueueDepths. Initialize the Untagged Queue Depth.
	 */
	क्रम (tgt_id = 0; tgt_id < BLOGIC_MAXDEV; tgt_id++) अणु
		अचिन्हित अक्षर qdepth = 0;
		अगर (adapter->drvr_opts != शून्य &&
				adapter->drvr_opts->qdepth[tgt_id] > 0)
			qdepth = adapter->drvr_opts->qdepth[tgt_id];
		adapter->qdepth[tgt_id] = qdepth;
	पूर्ण
	adapter->untag_qdepth = BLOGIC_UNTAG_DEPTH;
	अगर (adapter->drvr_opts != शून्य)
		adapter->common_qdepth = adapter->drvr_opts->common_qdepth;
	अगर (adapter->common_qdepth > 0 &&
			adapter->common_qdepth < adapter->untag_qdepth)
		adapter->untag_qdepth = adapter->common_qdepth;
	/*
	   Tagged Queuing is only allowed अगर Disconnect/Reconnect is permitted.
	   Thereक्रमe, mask the Tagged Queuing Permitted Default bits with the
	   Disconnect/Reconnect Permitted bits.
	 */
	adapter->tagq_ok &= adapter->discon_ok;
	/*
	   Combine the शेष Tagged Queuing Permitted bits with any
	   BusLogic Driver Options Tagged Queuing specअगरication.
	 */
	अगर (adapter->drvr_opts != शून्य)
		adapter->tagq_ok = (adapter->drvr_opts->tagq_ok &
				adapter->drvr_opts->tagq_ok_mask) |
			(adapter->tagq_ok & ~adapter->drvr_opts->tagq_ok_mask);

	/*
	   Select an appropriate value क्रम Bus Settle Time either from a
	   BusLogic Driver Options specअगरication, or from
	   BLOGIC_BUS_SETTLE_TIME.
	 */
	अगर (adapter->drvr_opts != शून्य &&
			adapter->drvr_opts->bus_settle_समय > 0)
		adapter->bus_settle_समय = adapter->drvr_opts->bus_settle_समय;
	अन्यथा
		adapter->bus_settle_समय = BLOGIC_BUS_SETTLE_TIME;
	/*
	   Indicate पढ़ोing the Host Adapter Configuration completed
	   successfully.
	 */
	वापस true;
पूर्ण


/*
  blogic_reportconfig reports the configuration of Host Adapter.
*/

अटल bool __init blogic_reportconfig(काष्ठा blogic_adapter *adapter)
अणु
	अचिन्हित लघु alltgt_mask = (1 << adapter->maxdev) - 1;
	अचिन्हित लघु sync_ok, fast_ok;
	अचिन्हित लघु ultra_ok, wide_ok;
	अचिन्हित लघु discon_ok, tagq_ok;
	bool common_syncneg, common_tagq_depth;
	अक्षर syncstr[BLOGIC_MAXDEV + 1];
	अक्षर widestr[BLOGIC_MAXDEV + 1];
	अक्षर discon_str[BLOGIC_MAXDEV + 1];
	अक्षर tagq_str[BLOGIC_MAXDEV + 1];
	अक्षर *syncmsg = syncstr;
	अक्षर *widemsg = widestr;
	अक्षर *discon_msg = discon_str;
	अक्षर *tagq_msg = tagq_str;
	पूर्णांक tgt_id;

	blogic_info("Configuring BusLogic Model %s %s%s%s%s SCSI Host Adapter\n", adapter, adapter->model, blogic_adapter_busnames[adapter->adapter_bus_type], (adapter->wide ? " Wide" : ""), (adapter->dअगरferential ? " Differential" : ""), (adapter->ultra ? " Ultra" : ""));
	blogic_info("  Firmware Version: %s, I/O Address: 0x%lX, IRQ Channel: %d/%s\n", adapter, adapter->fw_ver, adapter->io_addr, adapter->irq_ch, (adapter->level_पूर्णांक ? "Level" : "Edge"));
	अगर (adapter->adapter_bus_type != BLOGIC_PCI_BUS) अणु
		blogic_info("  DMA Channel: None, ", adapter);
		अगर (adapter->bios_addr > 0)
			blogic_info("BIOS Address: 0x%lX, ", adapter,
					adapter->bios_addr);
		अन्यथा
			blogic_info("BIOS Address: None, ", adapter);
	पूर्ण अन्यथा अणु
		blogic_info("  PCI Bus: %d, Device: %d, Address: ", adapter,
				adapter->bus, adapter->dev);
		अगर (adapter->pci_addr > 0)
			blogic_info("0x%lX, ", adapter, adapter->pci_addr);
		अन्यथा
			blogic_info("Unassigned, ", adapter);
	पूर्ण
	blogic_info("Host Adapter SCSI ID: %d\n", adapter, adapter->scsi_id);
	blogic_info("  Parity Checking: %s, Extended Translation: %s\n",
			adapter, (adapter->parity ? "Enabled" : "Disabled"),
			(adapter->ext_trans_enable ? "Enabled" : "Disabled"));
	alltgt_mask &= ~(1 << adapter->scsi_id);
	sync_ok = adapter->sync_ok & alltgt_mask;
	fast_ok = adapter->fast_ok & alltgt_mask;
	ultra_ok = adapter->ultra_ok & alltgt_mask;
	अगर ((blogic_multimaster_type(adapter) &&
			(adapter->fw_ver[0] >= '4' ||
			 adapter->adapter_bus_type == BLOGIC_EISA_BUS)) ||
			blogic_flashpoपूर्णांक_type(adapter)) अणु
		common_syncneg = false;
		अगर (sync_ok == 0) अणु
			syncmsg = "Disabled";
			common_syncneg = true;
		पूर्ण अन्यथा अगर (sync_ok == alltgt_mask) अणु
			अगर (fast_ok == 0) अणु
				syncmsg = "Slow";
				common_syncneg = true;
			पूर्ण अन्यथा अगर (fast_ok == alltgt_mask) अणु
				अगर (ultra_ok == 0) अणु
					syncmsg = "Fast";
					common_syncneg = true;
				पूर्ण अन्यथा अगर (ultra_ok == alltgt_mask) अणु
					syncmsg = "Ultra";
					common_syncneg = true;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (!common_syncneg) अणु
			क्रम (tgt_id = 0; tgt_id < adapter->maxdev; tgt_id++)
				syncstr[tgt_id] = ((!(sync_ok & (1 << tgt_id))) ? 'N' : (!(fast_ok & (1 << tgt_id)) ? 'S' : (!(ultra_ok & (1 << tgt_id)) ? 'F' : 'U')));
			syncstr[adapter->scsi_id] = '#';
			syncstr[adapter->maxdev] = '\0';
		पूर्ण
	पूर्ण अन्यथा
		syncmsg = (sync_ok == 0 ? "Disabled" : "Enabled");
	wide_ok = adapter->wide_ok & alltgt_mask;
	अगर (wide_ok == 0)
		widemsg = "Disabled";
	अन्यथा अगर (wide_ok == alltgt_mask)
		widemsg = "Enabled";
	अन्यथा अणु
		क्रम (tgt_id = 0; tgt_id < adapter->maxdev; tgt_id++)
			widestr[tgt_id] = ((wide_ok & (1 << tgt_id)) ? 'Y' : 'N');
		widestr[adapter->scsi_id] = '#';
		widestr[adapter->maxdev] = '\0';
	पूर्ण
	discon_ok = adapter->discon_ok & alltgt_mask;
	अगर (discon_ok == 0)
		discon_msg = "Disabled";
	अन्यथा अगर (discon_ok == alltgt_mask)
		discon_msg = "Enabled";
	अन्यथा अणु
		क्रम (tgt_id = 0; tgt_id < adapter->maxdev; tgt_id++)
			discon_str[tgt_id] = ((discon_ok & (1 << tgt_id)) ? 'Y' : 'N');
		discon_str[adapter->scsi_id] = '#';
		discon_str[adapter->maxdev] = '\0';
	पूर्ण
	tagq_ok = adapter->tagq_ok & alltgt_mask;
	अगर (tagq_ok == 0)
		tagq_msg = "Disabled";
	अन्यथा अगर (tagq_ok == alltgt_mask)
		tagq_msg = "Enabled";
	अन्यथा अणु
		क्रम (tgt_id = 0; tgt_id < adapter->maxdev; tgt_id++)
			tagq_str[tgt_id] = ((tagq_ok & (1 << tgt_id)) ? 'Y' : 'N');
		tagq_str[adapter->scsi_id] = '#';
		tagq_str[adapter->maxdev] = '\0';
	पूर्ण
	blogic_info("  Synchronous Negotiation: %s, Wide Negotiation: %s\n",
			adapter, syncmsg, widemsg);
	blogic_info("  Disconnect/Reconnect: %s, Tagged Queuing: %s\n", adapter,
			discon_msg, tagq_msg);
	अगर (blogic_multimaster_type(adapter)) अणु
		blogic_info("  Scatter/Gather Limit: %d of %d segments, Mailboxes: %d\n", adapter, adapter->drvr_sglimit, adapter->adapter_sglimit, adapter->mbox_count);
		blogic_info("  Driver Queue Depth: %d, Host Adapter Queue Depth: %d\n", adapter, adapter->drvr_qdepth, adapter->adapter_qdepth);
	पूर्ण अन्यथा
		blogic_info("  Driver Queue Depth: %d, Scatter/Gather Limit: %d segments\n", adapter, adapter->drvr_qdepth, adapter->drvr_sglimit);
	blogic_info("  Tagged Queue Depth: ", adapter);
	common_tagq_depth = true;
	क्रम (tgt_id = 1; tgt_id < adapter->maxdev; tgt_id++)
		अगर (adapter->qdepth[tgt_id] != adapter->qdepth[0]) अणु
			common_tagq_depth = false;
			अवरोध;
		पूर्ण
	अगर (common_tagq_depth) अणु
		अगर (adapter->qdepth[0] > 0)
			blogic_info("%d", adapter, adapter->qdepth[0]);
		अन्यथा
			blogic_info("Automatic", adapter);
	पूर्ण अन्यथा
		blogic_info("Individual", adapter);
	blogic_info(", Untagged Queue Depth: %d\n", adapter,
			adapter->untag_qdepth);
	अगर (adapter->terminfo_valid) अणु
		अगर (adapter->wide)
			blogic_info("  SCSI Bus Termination: %s", adapter,
				(adapter->low_term ? (adapter->high_term ? "Both Enabled" : "Low Enabled") : (adapter->high_term ? "High Enabled" : "Both Disabled")));
		अन्यथा
			blogic_info("  SCSI Bus Termination: %s", adapter,
				(adapter->low_term ? "Enabled" : "Disabled"));
		अगर (adapter->scam)
			blogic_info(", SCAM: %s", adapter,
				(adapter->scam_enabled ? (adapter->scam_lev2 ? "Enabled, Level 2" : "Enabled, Level 1") : "Disabled"));
		blogic_info("\n", adapter);
	पूर्ण
	/*
	   Indicate reporting the Host Adapter configuration completed
	   successfully.
	 */
	वापस true;
पूर्ण


/*
  blogic_getres acquires the प्रणाली resources necessary to use
  Host Adapter.
*/

अटल bool __init blogic_getres(काष्ठा blogic_adapter *adapter)
अणु
	अगर (adapter->irq_ch == 0) अणु
		blogic_err("NO LEGAL INTERRUPT CHANNEL ASSIGNED - DETACHING\n",
				adapter);
		वापस false;
	पूर्ण
	/*
	   Acquire shared access to the IRQ Channel.
	 */
	अगर (request_irq(adapter->irq_ch, blogic_पूर्णांकhandler, IRQF_SHARED,
				adapter->full_model, adapter) < 0) अणु
		blogic_err("UNABLE TO ACQUIRE IRQ CHANNEL %d - DETACHING\n",
				adapter, adapter->irq_ch);
		वापस false;
	पूर्ण
	adapter->irq_acquired = true;
	/*
	   Indicate the System Resource Acquisition completed successfully,
	 */
	वापस true;
पूर्ण


/*
  blogic_relres releases any प्रणाली resources previously acquired
  by blogic_getres.
*/

अटल व्योम blogic_relres(काष्ठा blogic_adapter *adapter)
अणु
	/*
	   Release shared access to the IRQ Channel.
	 */
	अगर (adapter->irq_acquired)
		मुक्त_irq(adapter->irq_ch, adapter);
	/*
	   Release any allocated memory काष्ठाs not released अन्यथाwhere
	 */
	अगर (adapter->mbox_space)
		dma_मुक्त_coherent(&adapter->pci_device->dev, adapter->mbox_sz,
			adapter->mbox_space, adapter->mbox_space_handle);
	pci_dev_put(adapter->pci_device);
	adapter->mbox_space = शून्य;
	adapter->mbox_space_handle = 0;
	adapter->mbox_sz = 0;
पूर्ण


/*
  blogic_initadapter initializes Host Adapter.  This is the only
  function called during SCSI Host Adapter detection which modअगरies the state
  of the Host Adapter from its initial घातer on or hard reset state.
*/

अटल bool blogic_initadapter(काष्ठा blogic_adapter *adapter)
अणु
	काष्ठा blogic_exपंचांगbox_req exपंचांगbox_req;
	क्रमागत blogic_rr_req rr_req;
	क्रमागत blogic_setccb_fmt setccb_fmt;
	पूर्णांक tgt_id;

	/*
	   Initialize the poपूर्णांकers to the first and last CCBs that are
	   queued क्रम completion processing.
	 */
	adapter->firstccb = शून्य;
	adapter->lastccb = शून्य;

	/*
	   Initialize the Bus Device Reset Pending CCB, Tagged Queuing Active,
	   Command Successful Flag, Active Commands, and Commands Since Reset
	   क्रम each Target Device.
	 */
	क्रम (tgt_id = 0; tgt_id < adapter->maxdev; tgt_id++) अणु
		adapter->bdr_pend[tgt_id] = शून्य;
		adapter->tgt_flags[tgt_id].tagq_active = false;
		adapter->tgt_flags[tgt_id].cmd_good = false;
		adapter->active_cmds[tgt_id] = 0;
		adapter->cmds_since_rst[tgt_id] = 0;
	पूर्ण

	/*
	   FlashPoपूर्णांक Host Adapters करो not use Outgoing and Incoming Mailboxes.
	 */
	अगर (blogic_flashpoपूर्णांक_type(adapter))
		जाओ करोne;

	/*
	   Initialize the Outgoing and Incoming Mailbox poपूर्णांकers.
	 */
	adapter->mbox_sz = adapter->mbox_count * (माप(काष्ठा blogic_outbox) + माप(काष्ठा blogic_inbox));
	adapter->mbox_space = dma_alloc_coherent(&adapter->pci_device->dev,
				adapter->mbox_sz, &adapter->mbox_space_handle,
				GFP_KERNEL);
	अगर (adapter->mbox_space == शून्य)
		वापस blogic_failure(adapter, "MAILBOX ALLOCATION");
	adapter->first_outbox = (काष्ठा blogic_outbox *) adapter->mbox_space;
	adapter->last_outbox = adapter->first_outbox + adapter->mbox_count - 1;
	adapter->next_outbox = adapter->first_outbox;
	adapter->first_inbox = (काष्ठा blogic_inbox *) (adapter->last_outbox + 1);
	adapter->last_inbox = adapter->first_inbox + adapter->mbox_count - 1;
	adapter->next_inbox = adapter->first_inbox;

	/*
	   Initialize the Outgoing and Incoming Mailbox काष्ठाures.
	 */
	स_रखो(adapter->first_outbox, 0,
			adapter->mbox_count * माप(काष्ठा blogic_outbox));
	स_रखो(adapter->first_inbox, 0,
			adapter->mbox_count * माप(काष्ठा blogic_inbox));

	/*
	   Initialize the Host Adapter's Poपूर्णांकer to the Outgoing/Incoming
	   Mailboxes.
	 */
	exपंचांगbox_req.mbox_count = adapter->mbox_count;
	exपंचांगbox_req.base_mbox_addr = (u32) adapter->mbox_space_handle;
	अगर (blogic_cmd(adapter, BLOGIC_INIT_EXT_MBOX, &exपंचांगbox_req,
				माप(exपंचांगbox_req), शून्य, 0) < 0)
		वापस blogic_failure(adapter, "MAILBOX INITIALIZATION");
	/*
	   Enable Strict Round Robin Mode अगर supported by the Host Adapter. In
	   Strict Round Robin Mode, the Host Adapter only looks at the next
	   Outgoing Mailbox क्रम each new command, rather than scanning
	   through all the Outgoing Mailboxes to find any that have new
	   commands in them.  Strict Round Robin Mode is signअगरicantly more
	   efficient.
	 */
	अगर (adapter->strict_rr) अणु
		rr_req = BLOGIC_STRICT_RR_MODE;
		अगर (blogic_cmd(adapter, BLOGIC_STRICT_RR, &rr_req,
					माप(rr_req), शून्य, 0) < 0)
			वापस blogic_failure(adapter,
					"ENABLE STRICT ROUND ROBIN MODE");
	पूर्ण

	/*
	   For Host Adapters that support Extended LUN Format CCBs, issue the
	   Set CCB Format command to allow 32 Logical Units per Target Device.
	 */
	अगर (adapter->ext_lun) अणु
		setccb_fmt = BLOGIC_EXT_LUN_CCB;
		अगर (blogic_cmd(adapter, BLOGIC_SETCCB_FMT, &setccb_fmt,
					माप(setccb_fmt), शून्य, 0) < 0)
			वापस blogic_failure(adapter, "SET CCB FORMAT");
	पूर्ण

	/*
	   Announce Successful Initialization.
	 */
करोne:
	अगर (!adapter->adapter_initd) अणु
		blogic_info("*** %s Initialized Successfully ***\n", adapter,
				adapter->full_model);
		blogic_info("\n", adapter);
	पूर्ण अन्यथा
		blogic_warn("*** %s Initialized Successfully ***\n", adapter,
				adapter->full_model);
	adapter->adapter_initd = true;

	/*
	   Indicate the Host Adapter Initialization completed successfully.
	 */
	वापस true;
पूर्ण


/*
  blogic_inquiry inquires about the Target Devices accessible
  through Host Adapter.
*/

अटल bool __init blogic_inquiry(काष्ठा blogic_adapter *adapter)
अणु
	u16 installed_devs;
	u8 installed_devs0to7[8];
	काष्ठा blogic_setup_info setupinfo;
	u8 sync_period[BLOGIC_MAXDEV];
	अचिन्हित अक्षर req_replylen;
	पूर्णांक tgt_id;

	/*
	   Wait a few seconds between the Host Adapter Hard Reset which
	   initiates a SCSI Bus Reset and issuing any SCSI Commands. Some
	   SCSI devices get confused अगर they receive SCSI Commands too soon
	   after a SCSI Bus Reset.
	 */
	blogic_delay(adapter->bus_settle_समय);
	/*
	   FlashPoपूर्णांक Host Adapters करो not provide क्रम Target Device Inquiry.
	 */
	अगर (blogic_flashpoपूर्णांक_type(adapter))
		वापस true;
	/*
	   Inhibit the Target Device Inquiry अगर requested.
	 */
	अगर (adapter->drvr_opts != शून्य && adapter->drvr_opts->stop_tgt_inquiry)
		वापस true;
	/*
	   Issue the Inquire Target Devices command क्रम host adapters with
	   firmware version 4.25 or later, or the Inquire Installed Devices
	   ID 0 to 7 command क्रम older host adapters.  This is necessary to
	   क्रमce Synchronous Transfer Negotiation so that the Inquire Setup
	   Inक्रमmation and Inquire Synchronous Period commands will वापस
	   valid data.  The Inquire Target Devices command is preferable to
	   Inquire Installed Devices ID 0 to 7 since it only probes Logical
	   Unit 0 of each Target Device.
	 */
	अगर (म_भेद(adapter->fw_ver, "4.25") >= 0) अणु

		/*
		   Issue a Inquire Target Devices command. Inquire Target
		   Devices only tests Logical Unit 0 of each Target Device
		   unlike the Inquire Installed Devices commands which test
		   Logical Units 0 - 7.  Two bytes are वापसed, where byte
		   0 bit 0 set indicates that Target Device 0 exists, and so on.
		 */

		अगर (blogic_cmd(adapter, BLOGIC_INQ_DEV, शून्य, 0,
					&installed_devs, माप(installed_devs))
		    != माप(installed_devs))
			वापस blogic_failure(adapter, "INQUIRE TARGET DEVICES");
		क्रम (tgt_id = 0; tgt_id < adapter->maxdev; tgt_id++)
			adapter->tgt_flags[tgt_id].tgt_exists =
				(installed_devs & (1 << tgt_id) ? true : false);
	पूर्ण अन्यथा अणु

		/*
		   Issue an Inquire Installed Devices command. For each
		   Target Device, a byte is वापसed where bit 0 set
		   indicates that Logical Unit 0 * exists, bit 1 set
		   indicates that Logical Unit 1 exists, and so on.
		 */

		अगर (blogic_cmd(adapter, BLOGIC_INQ_DEV0TO7, शून्य, 0,
				&installed_devs0to7, माप(installed_devs0to7))
		    != माप(installed_devs0to7))
			वापस blogic_failure(adapter,
					"INQUIRE INSTALLED DEVICES ID 0 TO 7");
		क्रम (tgt_id = 0; tgt_id < 8; tgt_id++)
			adapter->tgt_flags[tgt_id].tgt_exists =
				installed_devs0to7[tgt_id] != 0;
	पूर्ण
	/*
	   Issue the Inquire Setup Inक्रमmation command.
	 */
	req_replylen = माप(setupinfo);
	अगर (blogic_cmd(adapter, BLOGIC_INQ_SETUPINFO, &req_replylen,
			माप(req_replylen), &setupinfo, माप(setupinfo))
	    != माप(setupinfo))
		वापस blogic_failure(adapter, "INQUIRE SETUP INFORMATION");
	क्रम (tgt_id = 0; tgt_id < adapter->maxdev; tgt_id++)
		adapter->sync_offset[tgt_id] = (tgt_id < 8 ? setupinfo.sync0to7[tgt_id].offset : setupinfo.sync8to15[tgt_id - 8].offset);
	अगर (म_भेद(adapter->fw_ver, "5.06L") >= 0)
		क्रम (tgt_id = 0; tgt_id < adapter->maxdev; tgt_id++)
			adapter->tgt_flags[tgt_id].wide_active = (tgt_id < 8 ? (setupinfo.wide_tx_active0to7 & (1 << tgt_id) ? true : false) : (setupinfo.wide_tx_active8to15 & (1 << (tgt_id - 8)) ? true : false));
	/*
	   Issue the Inquire Synchronous Period command.
	 */
	अगर (adapter->fw_ver[0] >= '3') अणु

		/* Issue a Inquire Synchronous Period command. For each
		   Target Device, a byte is वापसed which represents the
		   Synchronous Transfer Period in units of 10 nanoseconds.
		 */

		req_replylen = माप(sync_period);
		अगर (blogic_cmd(adapter, BLOGIC_INQ_SYNC_PERIOD, &req_replylen,
				माप(req_replylen), &sync_period,
				माप(sync_period)) != माप(sync_period))
			वापस blogic_failure(adapter,
					"INQUIRE SYNCHRONOUS PERIOD");
		क्रम (tgt_id = 0; tgt_id < adapter->maxdev; tgt_id++)
			adapter->sync_period[tgt_id] = sync_period[tgt_id];
	पूर्ण अन्यथा
		क्रम (tgt_id = 0; tgt_id < adapter->maxdev; tgt_id++)
			अगर (setupinfo.sync0to7[tgt_id].offset > 0)
				adapter->sync_period[tgt_id] = 20 + 5 * setupinfo.sync0to7[tgt_id].tx_period;
	/*
	   Indicate the Target Device Inquiry completed successfully.
	 */
	वापस true;
पूर्ण

/*
  blogic_inithostकाष्ठा initializes the fields in the SCSI Host
  काष्ठाure.  The base, io_port, n_io_ports, irq, and dma_channel fields in the
  SCSI Host काष्ठाure are पूर्णांकentionally left uninitialized, as this driver
  handles acquisition and release of these resources explicitly, as well as
  ensuring exclusive access to the Host Adapter hardware and data काष्ठाures
  through explicit acquisition and release of the Host Adapter's Lock.
*/

अटल व्योम __init blogic_inithostकाष्ठा(काष्ठा blogic_adapter *adapter,
		काष्ठा Scsi_Host *host)
अणु
	host->max_id = adapter->maxdev;
	host->max_lun = adapter->maxlun;
	host->max_channel = 0;
	host->unique_id = adapter->io_addr;
	host->this_id = adapter->scsi_id;
	host->can_queue = adapter->drvr_qdepth;
	host->sg_tablesize = adapter->drvr_sglimit;
	host->cmd_per_lun = adapter->untag_qdepth;
पूर्ण

/*
  blogic_slaveconfig will actually set the queue depth on inभागidual
  scsi devices as they are permanently added to the device chain.  We
  shamelessly rip off the SelectQueueDepths code to make this work mostly
  like it used to.  Since we करोn't get called once at the end of the scan
  but instead get called क्रम each device, we have to करो things a bit
  dअगरferently.
*/
अटल पूर्णांक blogic_slaveconfig(काष्ठा scsi_device *dev)
अणु
	काष्ठा blogic_adapter *adapter =
		(काष्ठा blogic_adapter *) dev->host->hostdata;
	पूर्णांक tgt_id = dev->id;
	पूर्णांक qdepth = adapter->qdepth[tgt_id];

	अगर (adapter->tgt_flags[tgt_id].tagq_ok &&
			(adapter->tagq_ok & (1 << tgt_id))) अणु
		अगर (qdepth == 0)
			qdepth = BLOGIC_MAX_AUTO_TAG_DEPTH;
		adapter->qdepth[tgt_id] = qdepth;
		scsi_change_queue_depth(dev, qdepth);
	पूर्ण अन्यथा अणु
		adapter->tagq_ok &= ~(1 << tgt_id);
		qdepth = adapter->untag_qdepth;
		adapter->qdepth[tgt_id] = qdepth;
		scsi_change_queue_depth(dev, qdepth);
	पूर्ण
	qdepth = 0;
	क्रम (tgt_id = 0; tgt_id < adapter->maxdev; tgt_id++)
		अगर (adapter->tgt_flags[tgt_id].tgt_exists)
			qdepth += adapter->qdepth[tgt_id];
	अगर (qdepth > adapter->alloc_ccbs)
		blogic_create_addlccbs(adapter, qdepth - adapter->alloc_ccbs,
				false);
	वापस 0;
पूर्ण

/*
  blogic_init probes क्रम BusLogic Host Adapters at the standard
  I/O Addresses where they may be located, initializing, रेजिस्टरing, and
  reporting the configuration of each BusLogic Host Adapter it finds.  It
  वापसs the number of BusLogic Host Adapters successfully initialized and
  रेजिस्टरed.
*/

अटल पूर्णांक __init blogic_init(व्योम)
अणु
	पूर्णांक adapter_count = 0, drvr_optindex = 0, probeindex;
	काष्ठा blogic_adapter *adapter;
	पूर्णांक ret = 0;

#अगर_घोषित MODULE
	अगर (BusLogic)
		blogic_setup(BusLogic);
#पूर्ण_अगर

	अगर (blogic_probe_options.noprobe)
		वापस -ENODEV;
	blogic_probeinfo_list =
	    kसुस्मृति(BLOGIC_MAX_ADAPTERS, माप(काष्ठा blogic_probeinfo),
			    GFP_KERNEL);
	अगर (blogic_probeinfo_list == शून्य) अणु
		blogic_err("BusLogic: Unable to allocate Probe Info List\n",
				शून्य);
		वापस -ENOMEM;
	पूर्ण

	adapter = kzalloc(माप(काष्ठा blogic_adapter), GFP_KERNEL);
	अगर (adapter == शून्य) अणु
		kमुक्त(blogic_probeinfo_list);
		blogic_err("BusLogic: Unable to allocate Prototype Host Adapter\n", शून्य);
		वापस -ENOMEM;
	पूर्ण

#अगर_घोषित MODULE
	अगर (BusLogic != शून्य)
		blogic_setup(BusLogic);
#पूर्ण_अगर
	blogic_init_probeinfo_list(adapter);
	क्रम (probeindex = 0; probeindex < blogic_probeinfo_count; probeindex++) अणु
		काष्ठा blogic_probeinfo *probeinfo =
			&blogic_probeinfo_list[probeindex];
		काष्ठा blogic_adapter *myadapter = adapter;
		काष्ठा Scsi_Host *host;

		अगर (probeinfo->io_addr == 0)
			जारी;
		स_रखो(myadapter, 0, माप(काष्ठा blogic_adapter));
		myadapter->adapter_type = probeinfo->adapter_type;
		myadapter->adapter_bus_type = probeinfo->adapter_bus_type;
		myadapter->io_addr = probeinfo->io_addr;
		myadapter->pci_addr = probeinfo->pci_addr;
		myadapter->bus = probeinfo->bus;
		myadapter->dev = probeinfo->dev;
		myadapter->pci_device = probeinfo->pci_device;
		myadapter->irq_ch = probeinfo->irq_ch;
		myadapter->addr_count =
			blogic_adapter_addr_count[myadapter->adapter_type];

		/*
		   Make sure region is मुक्त prior to probing.
		 */
		अगर (!request_region(myadapter->io_addr, myadapter->addr_count,
					"BusLogic"))
			जारी;
		/*
		   Probe the Host Adapter. If unsuccessful, पात further
		   initialization.
		 */
		अगर (!blogic_probe(myadapter)) अणु
			release_region(myadapter->io_addr,
					myadapter->addr_count);
			जारी;
		पूर्ण
		/*
		   Hard Reset the Host Adapter.  If unsuccessful, पात further
		   initialization.
		 */
		अगर (!blogic_hwreset(myadapter, true)) अणु
			release_region(myadapter->io_addr,
					myadapter->addr_count);
			जारी;
		पूर्ण
		/*
		   Check the Host Adapter.  If unsuccessful, पात further
		   initialization.
		 */
		अगर (!blogic_checkadapter(myadapter)) अणु
			release_region(myadapter->io_addr,
					myadapter->addr_count);
			जारी;
		पूर्ण
		/*
		   Initialize the Driver Options field अगर provided.
		 */
		अगर (drvr_optindex < blogic_drvr_options_count)
			myadapter->drvr_opts =
				&blogic_drvr_options[drvr_optindex++];
		/*
		   Announce the Driver Version and Date, Author's Name,
		   Copyright Notice, and Electronic Mail Address.
		 */
		blogic_announce_drvr(myadapter);
		/*
		   Register the SCSI Host काष्ठाure.
		 */

		host = scsi_host_alloc(&blogic_ढाँचा,
				माप(काष्ठा blogic_adapter));
		अगर (host == शून्य) अणु
			release_region(myadapter->io_addr,
					myadapter->addr_count);
			जारी;
		पूर्ण
		myadapter = (काष्ठा blogic_adapter *) host->hostdata;
		स_नकल(myadapter, adapter, माप(काष्ठा blogic_adapter));
		myadapter->scsi_host = host;
		myadapter->host_no = host->host_no;
		/*
		   Add Host Adapter to the end of the list of रेजिस्टरed
		   BusLogic Host Adapters.
		 */
		list_add_tail(&myadapter->host_list, &blogic_host_list);

		/*
		   Read the Host Adapter Configuration, Configure the Host
		   Adapter, Acquire the System Resources necessary to use
		   the Host Adapter, then Create the Initial CCBs, Initialize
		   the Host Adapter, and finally perक्रमm Target Device
		   Inquiry. From this poपूर्णांक onward, any failure will be
		   assumed to be due to a problem with the Host Adapter,
		   rather than due to having mistakenly identअगरied this port
		   as beदीर्घing to a BusLogic Host Adapter. The I/O Address
		   range will not be released, thereby preventing it from
		   being incorrectly identअगरied as any other type of Host
		   Adapter.
		 */
		अगर (blogic_rdconfig(myadapter) &&
		    blogic_reportconfig(myadapter) &&
		    blogic_getres(myadapter) &&
		    blogic_create_initccbs(myadapter) &&
		    blogic_initadapter(myadapter) &&
		    blogic_inquiry(myadapter)) अणु
			/*
			   Initialization has been completed successfully.
			   Release and re-रेजिस्टर usage of the I/O Address
			   range so that the Model Name of the Host Adapter
			   will appear, and initialize the SCSI Host काष्ठाure.
			 */
			release_region(myadapter->io_addr,
				       myadapter->addr_count);
			अगर (!request_region(myadapter->io_addr,
					    myadapter->addr_count,
					    myadapter->full_model)) अणु
				prपूर्णांकk(KERN_WARNING
					"BusLogic: Release and re-register of "
					"port 0x%04lx failed \n",
					(अचिन्हित दीर्घ)myadapter->io_addr);
				blogic_destroy_ccbs(myadapter);
				blogic_relres(myadapter);
				list_del(&myadapter->host_list);
				scsi_host_put(host);
				ret = -ENOMEM;
			पूर्ण अन्यथा अणु
				blogic_inithostकाष्ठा(myadapter,
								 host);
				अगर (scsi_add_host(host, myadapter->pci_device
						? &myadapter->pci_device->dev
						  : शून्य)) अणु
					prपूर्णांकk(KERN_WARNING
					       "BusLogic: scsi_add_host()"
					       "failed!\n");
					blogic_destroy_ccbs(myadapter);
					blogic_relres(myadapter);
					list_del(&myadapter->host_list);
					scsi_host_put(host);
					ret = -ENODEV;
				पूर्ण अन्यथा अणु
					scsi_scan_host(host);
					adapter_count++;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			   An error occurred during Host Adapter Configuration
			   Querying, Host Adapter Configuration, Resource
			   Acquisition, CCB Creation, Host Adapter
			   Initialization, or Target Device Inquiry, so
			   हटाओ Host Adapter from the list of रेजिस्टरed
			   BusLogic Host Adapters, destroy the CCBs, Release
			   the System Resources, and Unरेजिस्टर the SCSI
			   Host.
			 */
			blogic_destroy_ccbs(myadapter);
			blogic_relres(myadapter);
			list_del(&myadapter->host_list);
			scsi_host_put(host);
			ret = -ENODEV;
		पूर्ण
	पूर्ण
	kमुक्त(adapter);
	kमुक्त(blogic_probeinfo_list);
	blogic_probeinfo_list = शून्य;
	वापस ret;
पूर्ण


/*
  blogic_deladapter releases all resources previously acquired to
  support a specअगरic Host Adapter, including the I/O Address range, and
  unरेजिस्टरs the BusLogic Host Adapter.
*/

अटल पूर्णांक __निकास blogic_deladapter(काष्ठा blogic_adapter *adapter)
अणु
	काष्ठा Scsi_Host *host = adapter->scsi_host;

	scsi_हटाओ_host(host);

	/*
	   FlashPoपूर्णांक Host Adapters must first be released by the FlashPoपूर्णांक
	   SCCB Manager.
	 */
	अगर (blogic_flashpoपूर्णांक_type(adapter))
		FlashPoपूर्णांक_ReleaseHostAdapter(adapter->cardhandle);
	/*
	   Destroy the CCBs and release any प्रणाली resources acquired to
	   support Host Adapter.
	 */
	blogic_destroy_ccbs(adapter);
	blogic_relres(adapter);
	/*
	   Release usage of the I/O Address range.
	 */
	release_region(adapter->io_addr, adapter->addr_count);
	/*
	   Remove Host Adapter from the list of रेजिस्टरed BusLogic
	   Host Adapters.
	 */
	list_del(&adapter->host_list);

	scsi_host_put(host);
	वापस 0;
पूर्ण


/*
  blogic_qcompleted_ccb queues CCB क्रम completion processing.
*/

अटल व्योम blogic_qcompleted_ccb(काष्ठा blogic_ccb *ccb)
अणु
	काष्ठा blogic_adapter *adapter = ccb->adapter;

	ccb->status = BLOGIC_CCB_COMPLETE;
	ccb->next = शून्य;
	अगर (adapter->firstccb == शून्य) अणु
		adapter->firstccb = ccb;
		adapter->lastccb = ccb;
	पूर्ण अन्यथा अणु
		adapter->lastccb->next = ccb;
		adapter->lastccb = ccb;
	पूर्ण
	adapter->active_cmds[ccb->tgt_id]--;
पूर्ण


/*
  blogic_resultcode computes a SCSI Subप्रणाली Result Code from
  the Host Adapter Status and Target Device Status.
*/

अटल पूर्णांक blogic_resultcode(काष्ठा blogic_adapter *adapter,
		क्रमागत blogic_adapter_status adapter_status,
		क्रमागत blogic_tgt_status tgt_status)
अणु
	पूर्णांक hoststatus;

	चयन (adapter_status) अणु
	हाल BLOGIC_CMD_CMPLT_NORMAL:
	हाल BLOGIC_LINK_CMD_CMPLT:
	हाल BLOGIC_LINK_CMD_CMPLT_FLAG:
		hoststatus = DID_OK;
		अवरोध;
	हाल BLOGIC_SELECT_TIMEOUT:
		hoststatus = DID_TIME_OUT;
		अवरोध;
	हाल BLOGIC_INVALID_OUTBOX_CODE:
	हाल BLOGIC_INVALID_CMD_CODE:
	हाल BLOGIC_BAD_CMD_PARAM:
		blogic_warn("BusLogic Driver Protocol Error 0x%02X\n",
				adapter, adapter_status);
		fallthrough;
	हाल BLOGIC_DATA_UNDERRUN:
	हाल BLOGIC_DATA_OVERRUN:
	हाल BLOGIC_NOEXPECT_BUSFREE:
	हाल BLOGIC_LINKCCB_BADLUN:
	हाल BLOGIC_AUTOREQSENSE_FAIL:
	हाल BLOGIC_TAGQUEUE_REJECT:
	हाल BLOGIC_BAD_MSG_RCVD:
	हाल BLOGIC_HW_FAIL:
	हाल BLOGIC_BAD_RECONNECT:
	हाल BLOGIC_ABRT_QUEUE:
	हाल BLOGIC_ADAPTER_SW_ERROR:
	हाल BLOGIC_HW_TIMEOUT:
	हाल BLOGIC_PARITY_ERR:
		hoststatus = DID_ERROR;
		अवरोध;
	हाल BLOGIC_INVALID_BUSPHASE:
	हाल BLOGIC_NORESPONSE_TO_ATN:
	हाल BLOGIC_HW_RESET:
	हाल BLOGIC_RST_FROM_OTHERDEV:
	हाल BLOGIC_HW_BDR:
		hoststatus = DID_RESET;
		अवरोध;
	शेष:
		blogic_warn("Unknown Host Adapter Status 0x%02X\n", adapter,
				adapter_status);
		hoststatus = DID_ERROR;
		अवरोध;
	पूर्ण
	वापस (hoststatus << 16) | tgt_status;
पूर्ण


/*
  blogic_scan_inbox scans the Incoming Mailboxes saving any
  Incoming Mailbox entries क्रम completion processing.
*/

अटल व्योम blogic_scan_inbox(काष्ठा blogic_adapter *adapter)
अणु
	/*
	   Scan through the Incoming Mailboxes in Strict Round Robin
	   fashion, saving any completed CCBs क्रम further processing. It
	   is essential that क्रम each CCB and SCSI Command issued, command
	   completion processing is perक्रमmed exactly once.  Thereक्रमe,
	   only Incoming Mailboxes with completion code Command Completed
	   Without Error, Command Completed With Error, or Command Aborted
	   At Host Request are saved क्रम completion processing. When an
	   Incoming Mailbox has a completion code of Aborted Command Not
	   Found, the CCB had alपढ़ोy completed or been पातed beक्रमe the
	   current Abort request was processed, and so completion processing
	   has alपढ़ोy occurred and no further action should be taken.
	 */
	काष्ठा blogic_inbox *next_inbox = adapter->next_inbox;
	क्रमागत blogic_cmplt_code comp_code;

	जबतक ((comp_code = next_inbox->comp_code) != BLOGIC_INBOX_FREE) अणु
		/*
		   We are only allowed to करो this because we limit our
		   architectures we run on to machines where bus_to_virt(
		   actually works.  There *needs* to be a dma_addr_to_virt()
		   in the new PCI DMA mapping पूर्णांकerface to replace
		   bus_to_virt() or अन्यथा this code is going to become very
		   innefficient.
		 */
		काष्ठा blogic_ccb *ccb =
			(काष्ठा blogic_ccb *) bus_to_virt(next_inbox->ccb);
		अगर (comp_code != BLOGIC_CMD_NOTFOUND) अणु
			अगर (ccb->status == BLOGIC_CCB_ACTIVE ||
					ccb->status == BLOGIC_CCB_RESET) अणु
				/*
				   Save the Completion Code क्रम this CCB and
				   queue the CCB क्रम completion processing.
				 */
				ccb->comp_code = comp_code;
				blogic_qcompleted_ccb(ccb);
			पूर्ण अन्यथा अणु
				/*
				   If a CCB ever appears in an Incoming Mailbox
				   and is not marked as status Active or Reset,
				   then there is most likely a bug in
				   the Host Adapter firmware.
				 */
				blogic_warn("Illegal CCB #%ld status %d in Incoming Mailbox\n", adapter, ccb->serial, ccb->status);
			पूर्ण
		पूर्ण
		next_inbox->comp_code = BLOGIC_INBOX_FREE;
		अगर (++next_inbox > adapter->last_inbox)
			next_inbox = adapter->first_inbox;
	पूर्ण
	adapter->next_inbox = next_inbox;
पूर्ण


/*
  blogic_process_ccbs iterates over the completed CCBs क्रम Host
  Adapter setting the SCSI Command Result Codes, deallocating the CCBs, and
  calling the SCSI Subप्रणाली Completion Routines.  The Host Adapter's Lock
  should alपढ़ोy have been acquired by the caller.
*/

अटल व्योम blogic_process_ccbs(काष्ठा blogic_adapter *adapter)
अणु
	अगर (adapter->processing_ccbs)
		वापस;
	adapter->processing_ccbs = true;
	जबतक (adapter->firstccb != शून्य) अणु
		काष्ठा blogic_ccb *ccb = adapter->firstccb;
		काष्ठा scsi_cmnd *command = ccb->command;
		adapter->firstccb = ccb->next;
		अगर (adapter->firstccb == शून्य)
			adapter->lastccb = शून्य;
		/*
		   Process the Completed CCB.
		 */
		अगर (ccb->opcode == BLOGIC_BDR) अणु
			पूर्णांक tgt_id = ccb->tgt_id;

			blogic_warn("Bus Device Reset CCB #%ld to Target %d Completed\n", adapter, ccb->serial, tgt_id);
			blogic_inc_count(&adapter->tgt_stats[tgt_id].bdr_करोne);
			adapter->tgt_flags[tgt_id].tagq_active = false;
			adapter->cmds_since_rst[tgt_id] = 0;
			adapter->last_resetकरोne[tgt_id] = jअगरfies;
			/*
			   Place CCB back on the Host Adapter's मुक्त list.
			 */
			blogic_dealloc_ccb(ccb, 1);
#अगर 0			/* this needs to be reकरोne dअगरferent क्रम new EH */
			/*
			   Bus Device Reset CCBs have the command field
			   non-शून्य only when a Bus Device Reset was requested
			   क्रम a command that did not have a currently active
			   CCB in the Host Adapter (i.e., a Synchronous Bus
			   Device Reset), and hence would not have its
			   Completion Routine called otherwise.
			 */
			जबतक (command != शून्य) अणु
				काष्ठा scsi_cmnd *nxt_cmd =
					command->reset_chain;
				command->reset_chain = शून्य;
				command->result = DID_RESET << 16;
				command->scsi_करोne(command);
				command = nxt_cmd;
			पूर्ण
#पूर्ण_अगर
			/*
			   Iterate over the CCBs क्रम this Host Adapter
			   perक्रमming completion processing क्रम any CCBs
			   marked as Reset क्रम this Target.
			 */
			क्रम (ccb = adapter->all_ccbs; ccb != शून्य;
					ccb = ccb->next_all)
				अगर (ccb->status == BLOGIC_CCB_RESET &&
						ccb->tgt_id == tgt_id) अणु
					command = ccb->command;
					blogic_dealloc_ccb(ccb, 1);
					adapter->active_cmds[tgt_id]--;
					command->result = DID_RESET << 16;
					command->scsi_करोne(command);
				पूर्ण
			adapter->bdr_pend[tgt_id] = शून्य;
		पूर्ण अन्यथा अणु
			/*
			   Translate the Completion Code, Host Adapter Status,
			   and Target Device Status पूर्णांकo a SCSI Subप्रणाली
			   Result Code.
			 */
			चयन (ccb->comp_code) अणु
			हाल BLOGIC_INBOX_FREE:
			हाल BLOGIC_CMD_NOTFOUND:
			हाल BLOGIC_INVALID_CCB:
				blogic_warn("CCB #%ld to Target %d Impossible State\n", adapter, ccb->serial, ccb->tgt_id);
				अवरोध;
			हाल BLOGIC_CMD_COMPLETE_GOOD:
				adapter->tgt_stats[ccb->tgt_id]
				    .cmds_complete++;
				adapter->tgt_flags[ccb->tgt_id]
				    .cmd_good = true;
				command->result = DID_OK << 16;
				अवरोध;
			हाल BLOGIC_CMD_ABORT_BY_HOST:
				blogic_warn("CCB #%ld to Target %d Aborted\n",
					adapter, ccb->serial, ccb->tgt_id);
				blogic_inc_count(&adapter->tgt_stats[ccb->tgt_id].पातs_करोne);
				command->result = DID_ABORT << 16;
				अवरोध;
			हाल BLOGIC_CMD_COMPLETE_ERROR:
				command->result = blogic_resultcode(adapter,
					ccb->adapter_status, ccb->tgt_status);
				अगर (ccb->adapter_status != BLOGIC_SELECT_TIMEOUT) अणु
					adapter->tgt_stats[ccb->tgt_id]
					    .cmds_complete++;
					अगर (blogic_global_options.trace_err) अणु
						पूर्णांक i;
						blogic_notice("CCB #%ld Target %d: Result %X Host "
								"Adapter Status %02X Target Status %02X\n", adapter, ccb->serial, ccb->tgt_id, command->result, ccb->adapter_status, ccb->tgt_status);
						blogic_notice("CDB   ", adapter);
						क्रम (i = 0; i < ccb->cdblen; i++)
							blogic_notice(" %02X", adapter, ccb->cdb[i]);
						blogic_notice("\n", adapter);
						blogic_notice("Sense ", adapter);
						क्रम (i = 0; i < ccb->sense_datalen; i++)
							blogic_notice(" %02X", adapter, command->sense_buffer[i]);
						blogic_notice("\n", adapter);
					पूर्ण
				पूर्ण
				अवरोध;
			पूर्ण
			/*
			   When an INQUIRY command completes normally, save the
			   CmdQue (Tagged Queuing Supported) and WBus16 (16 Bit
			   Wide Data Transfers Supported) bits.
			 */
			अगर (ccb->cdb[0] == INQUIRY && ccb->cdb[1] == 0 &&
				ccb->adapter_status == BLOGIC_CMD_CMPLT_NORMAL) अणु
				काष्ठा blogic_tgt_flags *tgt_flags =
					&adapter->tgt_flags[ccb->tgt_id];
				काष्ठा scsi_inquiry *inquiry =
					(काष्ठा scsi_inquiry *) scsi_sglist(command);
				tgt_flags->tgt_exists = true;
				tgt_flags->tagq_ok = inquiry->CmdQue;
				tgt_flags->wide_ok = inquiry->WBus16;
			पूर्ण
			/*
			   Place CCB back on the Host Adapter's मुक्त list.
			 */
			blogic_dealloc_ccb(ccb, 1);
			/*
			   Call the SCSI Command Completion Routine.
			 */
			command->scsi_करोne(command);
		पूर्ण
	पूर्ण
	adapter->processing_ccbs = false;
पूर्ण


/*
  blogic_पूर्णांकhandler handles hardware पूर्णांकerrupts from BusLogic Host
  Adapters.
*/

अटल irqवापस_t blogic_पूर्णांकhandler(पूर्णांक irq_ch, व्योम *devid)
अणु
	काष्ठा blogic_adapter *adapter = (काष्ठा blogic_adapter *) devid;
	अचिन्हित दीर्घ processor_flag;
	/*
	   Acquire exclusive access to Host Adapter.
	 */
	spin_lock_irqsave(adapter->scsi_host->host_lock, processor_flag);
	/*
	   Handle Interrupts appropriately क्रम each Host Adapter type.
	 */
	अगर (blogic_multimaster_type(adapter)) अणु
		जोड़ blogic_पूर्णांक_reg पूर्णांकreg;
		/*
		   Read the Host Adapter Interrupt Register.
		 */
		पूर्णांकreg.all = blogic_rdपूर्णांक(adapter);
		अगर (पूर्णांकreg.ir.पूर्णांक_valid) अणु
			/*
			   Acknowledge the पूर्णांकerrupt and reset the Host Adapter
			   Interrupt Register.
			 */
			blogic_पूर्णांकreset(adapter);
			/*
			   Process valid External SCSI Bus Reset and Incoming
			   Mailbox Loaded Interrupts. Command Complete
			   Interrupts are noted, and Outgoing Mailbox Available
			   Interrupts are ignored, as they are never enabled.
			 */
			अगर (पूर्णांकreg.ir.ext_busreset)
				adapter->adapter_extreset = true;
			अन्यथा अगर (पूर्णांकreg.ir.mailin_loaded)
				blogic_scan_inbox(adapter);
			अन्यथा अगर (पूर्णांकreg.ir.cmd_complete)
				adapter->adapter_cmd_complete = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		   Check अगर there is a pending पूर्णांकerrupt क्रम this Host Adapter.
		 */
		अगर (FlashPoपूर्णांक_InterruptPending(adapter->cardhandle))
			चयन (FlashPoपूर्णांक_HandleInterrupt(adapter->cardhandle)) अणु
			हाल FPOINT_NORMAL_INT:
				अवरोध;
			हाल FPOINT_EXT_RESET:
				adapter->adapter_extreset = true;
				अवरोध;
			हाल FPOINT_INTERN_ERR:
				blogic_warn("Internal FlashPoint Error detected - Resetting Host Adapter\n", adapter);
				adapter->adapter_पूर्णांकern_err = true;
				अवरोध;
			पूर्ण
	पूर्ण
	/*
	   Process any completed CCBs.
	 */
	अगर (adapter->firstccb != शून्य)
		blogic_process_ccbs(adapter);
	/*
	   Reset the Host Adapter अगर requested.
	 */
	अगर (adapter->adapter_extreset) अणु
		blogic_warn("Resetting %s due to External SCSI Bus Reset\n", adapter, adapter->full_model);
		blogic_inc_count(&adapter->ext_resets);
		blogic_resetadapter(adapter, false);
		adapter->adapter_extreset = false;
	पूर्ण अन्यथा अगर (adapter->adapter_पूर्णांकern_err) अणु
		blogic_warn("Resetting %s due to Host Adapter Internal Error\n", adapter, adapter->full_model);
		blogic_inc_count(&adapter->adapter_पूर्णांकern_errors);
		blogic_resetadapter(adapter, true);
		adapter->adapter_पूर्णांकern_err = false;
	पूर्ण
	/*
	   Release exclusive access to Host Adapter.
	 */
	spin_unlock_irqrestore(adapter->scsi_host->host_lock, processor_flag);
	वापस IRQ_HANDLED;
पूर्ण


/*
  blogic_ग_लिखो_outbox places CCB and Action Code पूर्णांकo an Outgoing
  Mailbox क्रम execution by Host Adapter.  The Host Adapter's Lock should
  alपढ़ोy have been acquired by the caller.
*/

अटल bool blogic_ग_लिखो_outbox(काष्ठा blogic_adapter *adapter,
		क्रमागत blogic_action action, काष्ठा blogic_ccb *ccb)
अणु
	काष्ठा blogic_outbox *next_outbox;

	next_outbox = adapter->next_outbox;
	अगर (next_outbox->action == BLOGIC_OUTBOX_FREE) अणु
		ccb->status = BLOGIC_CCB_ACTIVE;
		/*
		   The CCB field must be written beक्रमe the Action Code field
		   since the Host Adapter is operating asynchronously and the
		   locking code करोes not protect against simultaneous access
		   by the Host Adapter.
		 */
		next_outbox->ccb = ccb->dma_handle;
		next_outbox->action = action;
		blogic_execmbox(adapter);
		अगर (++next_outbox > adapter->last_outbox)
			next_outbox = adapter->first_outbox;
		adapter->next_outbox = next_outbox;
		अगर (action == BLOGIC_MBOX_START) अणु
			adapter->active_cmds[ccb->tgt_id]++;
			अगर (ccb->opcode != BLOGIC_BDR)
				adapter->tgt_stats[ccb->tgt_id].cmds_tried++;
		पूर्ण
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* Error Handling (EH) support */

अटल पूर्णांक blogic_hostreset(काष्ठा scsi_cmnd *SCpnt)
अणु
	काष्ठा blogic_adapter *adapter =
		(काष्ठा blogic_adapter *) SCpnt->device->host->hostdata;

	अचिन्हित पूर्णांक id = SCpnt->device->id;
	काष्ठा blogic_tgt_stats *stats = &adapter->tgt_stats[id];
	पूर्णांक rc;

	spin_lock_irq(SCpnt->device->host->host_lock);

	blogic_inc_count(&stats->adapter_reset_req);

	rc = blogic_resetadapter(adapter, false);
	spin_unlock_irq(SCpnt->device->host->host_lock);
	वापस rc;
पूर्ण

/*
  blogic_qcmd creates a CCB क्रम Command and places it पूर्णांकo an
  Outgoing Mailbox क्रम execution by the associated Host Adapter.
*/

अटल पूर्णांक blogic_qcmd_lck(काष्ठा scsi_cmnd *command,
		व्योम (*comp_cb) (काष्ठा scsi_cmnd *))
अणु
	काष्ठा blogic_adapter *adapter =
		(काष्ठा blogic_adapter *) command->device->host->hostdata;
	काष्ठा blogic_tgt_flags *tgt_flags =
		&adapter->tgt_flags[command->device->id];
	काष्ठा blogic_tgt_stats *tgt_stats = adapter->tgt_stats;
	अचिन्हित अक्षर *cdb = command->cmnd;
	पूर्णांक cdblen = command->cmd_len;
	पूर्णांक tgt_id = command->device->id;
	पूर्णांक lun = command->device->lun;
	पूर्णांक buflen = scsi_bufflen(command);
	पूर्णांक count;
	काष्ठा blogic_ccb *ccb;
	dma_addr_t sense_buf;

	/*
	   SCSI REQUEST_SENSE commands will be executed स्वतःmatically by the
	   Host Adapter क्रम any errors, so they should not be executed
	   explicitly unless the Sense Data is zero indicating that no error
	   occurred.
	 */
	अगर (cdb[0] == REQUEST_SENSE && command->sense_buffer[0] != 0) अणु
		command->result = DID_OK << 16;
		comp_cb(command);
		वापस 0;
	पूर्ण
	/*
	   Allocate a CCB from the Host Adapter's मुक्त list. In the unlikely
	   event that there are none available and memory allocation fails,
	   रुको 1 second and try again. If that fails, the Host Adapter is
	   probably hung so संकेत an error as a Host Adapter Hard Reset
	   should be initiated soon.
	 */
	ccb = blogic_alloc_ccb(adapter);
	अगर (ccb == शून्य) अणु
		spin_unlock_irq(adapter->scsi_host->host_lock);
		blogic_delay(1);
		spin_lock_irq(adapter->scsi_host->host_lock);
		ccb = blogic_alloc_ccb(adapter);
		अगर (ccb == शून्य) अणु
			command->result = DID_ERROR << 16;
			comp_cb(command);
			वापस 0;
		पूर्ण
	पूर्ण

	/*
	   Initialize the fields in the BusLogic Command Control Block (CCB).
	 */
	count = scsi_dma_map(command);
	BUG_ON(count < 0);
	अगर (count) अणु
		काष्ठा scatterlist *sg;
		पूर्णांक i;

		ccb->opcode = BLOGIC_INITIATOR_CCB_SG;
		ccb->datalen = count * माप(काष्ठा blogic_sg_seg);
		अगर (blogic_multimaster_type(adapter))
			ccb->data = (अचिन्हित पूर्णांक) ccb->dma_handle +
					((अचिन्हित दीर्घ) &ccb->sglist -
					(अचिन्हित दीर्घ) ccb);
		अन्यथा
			ccb->data = virt_to_32bit_virt(ccb->sglist);

		scsi_क्रम_each_sg(command, sg, count, i) अणु
			ccb->sglist[i].segbytes = sg_dma_len(sg);
			ccb->sglist[i].segdata = sg_dma_address(sg);
		पूर्ण
	पूर्ण अन्यथा अगर (!count) अणु
		ccb->opcode = BLOGIC_INITIATOR_CCB;
		ccb->datalen = buflen;
		ccb->data = 0;
	पूर्ण

	चयन (cdb[0]) अणु
	हाल READ_6:
	हाल READ_10:
		ccb->datadir = BLOGIC_DATAIN_CHECKED;
		tgt_stats[tgt_id].पढ़ो_cmds++;
		blogic_addcount(&tgt_stats[tgt_id].bytesपढ़ो, buflen);
		blogic_incszbucket(tgt_stats[tgt_id].पढ़ो_sz_buckets, buflen);
		अवरोध;
	हाल WRITE_6:
	हाल WRITE_10:
		ccb->datadir = BLOGIC_DATAOUT_CHECKED;
		tgt_stats[tgt_id].ग_लिखो_cmds++;
		blogic_addcount(&tgt_stats[tgt_id].byteswritten, buflen);
		blogic_incszbucket(tgt_stats[tgt_id].ग_लिखो_sz_buckets, buflen);
		अवरोध;
	शेष:
		ccb->datadir = BLOGIC_UNCHECKED_TX;
		अवरोध;
	पूर्ण
	ccb->cdblen = cdblen;
	ccb->adapter_status = 0;
	ccb->tgt_status = 0;
	ccb->tgt_id = tgt_id;
	ccb->lun = lun;
	ccb->tag_enable = false;
	ccb->legacytag_enable = false;
	/*
	   BusLogic recommends that after a Reset the first couple of
	   commands that are sent to a Target Device be sent in a non
	   Tagged Queue fashion so that the Host Adapter and Target Device
	   can establish Synchronous and Wide Transfer beक्रमe Queue Tag
	   messages can पूर्णांकerfere with the Synchronous and Wide Negotiation
	   messages.  By रुकोing to enable Tagged Queuing until after the
	   first BLOGIC_MAX_TAG_DEPTH commands have been queued, it is
	   assured that after a Reset any pending commands are requeued
	   beक्रमe Tagged Queuing is enabled and that the Tagged Queuing
	   message will not occur जबतक the partition table is being prपूर्णांकed.
	   In addition, some devices करो not properly handle the transition
	   from non-tagged to tagged commands, so it is necessary to रुको
	   until there are no pending commands क्रम a target device
	   beक्रमe queuing tagged commands.
	 */
	अगर (adapter->cmds_since_rst[tgt_id]++ >= BLOGIC_MAX_TAG_DEPTH &&
			!tgt_flags->tagq_active &&
			adapter->active_cmds[tgt_id] == 0
			&& tgt_flags->tagq_ok &&
			(adapter->tagq_ok & (1 << tgt_id))) अणु
		tgt_flags->tagq_active = true;
		blogic_notice("Tagged Queuing now active for Target %d\n",
					adapter, tgt_id);
	पूर्ण
	अगर (tgt_flags->tagq_active) अणु
		क्रमागत blogic_queuetag queuetag = BLOGIC_SIMPLETAG;
		/*
		   When using Tagged Queuing with Simple Queue Tags, it
		   appears that disk drive controllers करो not guarantee that
		   a queued command will not reमुख्य in a disconnected state
		   indefinitely अगर commands that पढ़ो or ग_लिखो nearer the
		   head position जारी to arrive without पूर्णांकerruption.
		   Thereक्रमe, क्रम each Target Device this driver keeps track
		   of the last समय either the queue was empty or an Ordered
		   Queue Tag was issued. If more than 4 seconds (one fअगरth
		   of the 20 second disk समयout) have elapsed since this
		   last sequence poपूर्णांक, this command will be issued with an
		   Ordered Queue Tag rather than a Simple Queue Tag, which
		   क्रमces the Target Device to complete all previously
		   queued commands beक्रमe this command may be executed.
		 */
		अगर (adapter->active_cmds[tgt_id] == 0)
			adapter->last_seqpoपूर्णांक[tgt_id] = jअगरfies;
		अन्यथा अगर (समय_after(jअगरfies,
				adapter->last_seqpoपूर्णांक[tgt_id] + 4 * HZ)) अणु
			adapter->last_seqpoपूर्णांक[tgt_id] = jअगरfies;
			queuetag = BLOGIC_ORDEREDTAG;
		पूर्ण
		अगर (adapter->ext_lun) अणु
			ccb->tag_enable = true;
			ccb->queuetag = queuetag;
		पूर्ण अन्यथा अणु
			ccb->legacytag_enable = true;
			ccb->legacy_tag = queuetag;
		पूर्ण
	पूर्ण
	स_नकल(ccb->cdb, cdb, cdblen);
	ccb->sense_datalen = SCSI_SENSE_BUFFERSIZE;
	ccb->command = command;
	sense_buf = dma_map_single(&adapter->pci_device->dev,
				command->sense_buffer, ccb->sense_datalen,
				DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&adapter->pci_device->dev, sense_buf)) अणु
		blogic_err("DMA mapping for sense data buffer failed\n",
				adapter);
		blogic_dealloc_ccb(ccb, 0);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण
	ccb->sensedata = sense_buf;
	command->scsi_करोne = comp_cb;
	अगर (blogic_multimaster_type(adapter)) अणु
		/*
		   Place the CCB in an Outgoing Mailbox. The higher levels
		   of the SCSI Subप्रणाली should not attempt to queue more
		   commands than can be placed in Outgoing Mailboxes, so
		   there should always be one मुक्त.  In the unlikely event
		   that there are none available, रुको 1 second and try
		   again. If that fails, the Host Adapter is probably hung
		   so संकेत an error as a Host Adapter Hard Reset should
		   be initiated soon.
		 */
		अगर (!blogic_ग_लिखो_outbox(adapter, BLOGIC_MBOX_START, ccb)) अणु
			spin_unlock_irq(adapter->scsi_host->host_lock);
			blogic_warn("Unable to write Outgoing Mailbox - Pausing for 1 second\n", adapter);
			blogic_delay(1);
			spin_lock_irq(adapter->scsi_host->host_lock);
			अगर (!blogic_ग_लिखो_outbox(adapter, BLOGIC_MBOX_START,
						ccb)) अणु
				blogic_warn("Still unable to write Outgoing Mailbox - Host Adapter Dead?\n", adapter);
				blogic_dealloc_ccb(ccb, 1);
				command->result = DID_ERROR << 16;
				command->scsi_करोne(command);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		   Call the FlashPoपूर्णांक SCCB Manager to start execution of
		   the CCB.
		 */
		ccb->status = BLOGIC_CCB_ACTIVE;
		adapter->active_cmds[tgt_id]++;
		tgt_stats[tgt_id].cmds_tried++;
		FlashPoपूर्णांक_StartCCB(adapter->cardhandle, ccb);
		/*
		   The Command may have alपढ़ोy completed and
		   blogic_qcompleted_ccb been called, or it may still be
		   pending.
		 */
		अगर (ccb->status == BLOGIC_CCB_COMPLETE)
			blogic_process_ccbs(adapter);
	पूर्ण
	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(blogic_qcmd)

#अगर 0
/*
  blogic_पात पातs Command अगर possible.
*/

अटल पूर्णांक blogic_पात(काष्ठा scsi_cmnd *command)
अणु
	काष्ठा blogic_adapter *adapter =
		(काष्ठा blogic_adapter *) command->device->host->hostdata;

	पूर्णांक tgt_id = command->device->id;
	काष्ठा blogic_ccb *ccb;
	blogic_inc_count(&adapter->tgt_stats[tgt_id].पातs_request);

	/*
	   Attempt to find an Active CCB क्रम this Command. If no Active
	   CCB क्रम this Command is found, then no Abort is necessary.
	 */
	क्रम (ccb = adapter->all_ccbs; ccb != शून्य; ccb = ccb->next_all)
		अगर (ccb->command == command)
			अवरोध;
	अगर (ccb == शून्य) अणु
		blogic_warn("Unable to Abort Command to Target %d - No CCB Found\n", adapter, tgt_id);
		वापस SUCCESS;
	पूर्ण अन्यथा अगर (ccb->status == BLOGIC_CCB_COMPLETE) अणु
		blogic_warn("Unable to Abort Command to Target %d - CCB Completed\n", adapter, tgt_id);
		वापस SUCCESS;
	पूर्ण अन्यथा अगर (ccb->status == BLOGIC_CCB_RESET) अणु
		blogic_warn("Unable to Abort Command to Target %d - CCB Reset\n", adapter, tgt_id);
		वापस SUCCESS;
	पूर्ण
	अगर (blogic_multimaster_type(adapter)) अणु
		/*
		   Attempt to Abort this CCB.  MultiMaster Firmware versions
		   prior to 5.xx करो not generate Abort Tag messages, but only
		   generate the non-tagged Abort message.  Since non-tagged
		   commands are not sent by the Host Adapter until the queue
		   of outstanding tagged commands has completed, and the
		   Abort message is treated as a non-tagged command, it is
		   effectively impossible to पात commands when Tagged
		   Queuing is active. Firmware version 5.xx करोes generate
		   Abort Tag messages, so it is possible to पात commands
		   when Tagged Queuing is active.
		 */
		अगर (adapter->tgt_flags[tgt_id].tagq_active &&
				adapter->fw_ver[0] < '5') अणु
			blogic_warn("Unable to Abort CCB #%ld to Target %d - Abort Tag Not Supported\n", adapter, ccb->serial, tgt_id);
			वापस FAILURE;
		पूर्ण अन्यथा अगर (blogic_ग_लिखो_outbox(adapter, BLOGIC_MBOX_ABORT,
					ccb)) अणु
			blogic_warn("Aborting CCB #%ld to Target %d\n",
					adapter, ccb->serial, tgt_id);
			blogic_inc_count(&adapter->tgt_stats[tgt_id].पातs_tried);
			वापस SUCCESS;
		पूर्ण अन्यथा अणु
			blogic_warn("Unable to Abort CCB #%ld to Target %d - No Outgoing Mailboxes\n", adapter, ccb->serial, tgt_id);
			वापस FAILURE;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		   Call the FlashPoपूर्णांक SCCB Manager to पात execution of
		   the CCB.
		 */
		blogic_warn("Aborting CCB #%ld to Target %d\n", adapter,
				ccb->serial, tgt_id);
		blogic_inc_count(&adapter->tgt_stats[tgt_id].पातs_tried);
		FlashPoपूर्णांक_AbortCCB(adapter->cardhandle, ccb);
		/*
		   The Abort may have alपढ़ोy been completed and
		   blogic_qcompleted_ccb been called, or it
		   may still be pending.
		 */
		अगर (ccb->status == BLOGIC_CCB_COMPLETE)
			blogic_process_ccbs(adapter);
		वापस SUCCESS;
	पूर्ण
	वापस SUCCESS;
पूर्ण

#पूर्ण_अगर
/*
  blogic_resetadapter resets Host Adapter अगर possible, marking all
  currently executing SCSI Commands as having been Reset.
*/

अटल पूर्णांक blogic_resetadapter(काष्ठा blogic_adapter *adapter, bool hard_reset)
अणु
	काष्ठा blogic_ccb *ccb;
	पूर्णांक tgt_id;

	/*
	 * Attempt to Reset and Reinitialize the Host Adapter.
	 */

	अगर (!(blogic_hwreset(adapter, hard_reset) &&
				blogic_initadapter(adapter))) अणु
		blogic_err("Resetting %s Failed\n", adapter,
						adapter->full_model);
		वापस FAILURE;
	पूर्ण

	/*
	 * Deallocate all currently executing CCBs.
	 */

	क्रम (ccb = adapter->all_ccbs; ccb != शून्य; ccb = ccb->next_all)
		अगर (ccb->status == BLOGIC_CCB_ACTIVE)
			blogic_dealloc_ccb(ccb, 1);
	/*
	 * Wait a few seconds between the Host Adapter Hard Reset which
	 * initiates a SCSI Bus Reset and issuing any SCSI Commands.  Some
	 * SCSI devices get confused अगर they receive SCSI Commands too soon
	 * after a SCSI Bus Reset.
	 */

	अगर (hard_reset) अणु
		spin_unlock_irq(adapter->scsi_host->host_lock);
		blogic_delay(adapter->bus_settle_समय);
		spin_lock_irq(adapter->scsi_host->host_lock);
	पूर्ण

	क्रम (tgt_id = 0; tgt_id < adapter->maxdev; tgt_id++) अणु
		adapter->last_resettried[tgt_id] = jअगरfies;
		adapter->last_resetकरोne[tgt_id] = jअगरfies;
	पूर्ण
	वापस SUCCESS;
पूर्ण

/*
  blogic_diskparam वापसs the Heads/Sectors/Cylinders BIOS Disk
  Parameters क्रम Disk.  The शेष disk geometry is 64 heads, 32 sectors, and
  the appropriate number of cylinders so as not to exceed drive capacity.  In
  order क्रम disks equal to or larger than 1 GB to be addressable by the BIOS
  without exceeding the BIOS limitation of 1024 cylinders, Extended Translation
  may be enabled in AutoSCSI on FlashPoपूर्णांक Host Adapters and on "W" and "C"
  series MultiMaster Host Adapters, or by a dip चयन setting on "S" and "A"
  series MultiMaster Host Adapters.  With Extended Translation enabled, drives
  between 1 GB inclusive and 2 GB exclusive are given a disk geometry of 128
  heads and 32 sectors, and drives above 2 GB inclusive are given a disk
  geometry of 255 heads and 63 sectors.  However, अगर the BIOS detects that the
  Extended Translation setting करोes not match the geometry in the partition
  table, then the translation inferred from the partition table will be used by
  the BIOS, and a warning may be displayed.
*/

अटल पूर्णांक blogic_diskparam(काष्ठा scsi_device *sdev, काष्ठा block_device *dev,
		sector_t capacity, पूर्णांक *params)
अणु
	काष्ठा blogic_adapter *adapter =
				(काष्ठा blogic_adapter *) sdev->host->hostdata;
	काष्ठा bios_diskparam *diskparam = (काष्ठा bios_diskparam *) params;
	अचिन्हित अक्षर *buf;

	अगर (adapter->ext_trans_enable && capacity >= 2 * 1024 * 1024 /* 1 GB in 512 byte sectors */) अणु
		अगर (capacity >= 4 * 1024 * 1024 /* 2 GB in 512 byte sectors */) अणु
			diskparam->heads = 255;
			diskparam->sectors = 63;
		पूर्ण अन्यथा अणु
			diskparam->heads = 128;
			diskparam->sectors = 32;
		पूर्ण
	पूर्ण अन्यथा अणु
		diskparam->heads = 64;
		diskparam->sectors = 32;
	पूर्ण
	diskparam->cylinders = (अचिन्हित दीर्घ) capacity / (diskparam->heads * diskparam->sectors);
	buf = scsi_bios_ptable(dev);
	अगर (buf == शून्य)
		वापस 0;
	/*
	   If the boot sector partition table flag is valid, search क्रम
	   a partition table entry whose end_head matches one of the
	   standard BusLogic geometry translations (64/32, 128/32, or 255/63).
	 */
	अगर (*(अचिन्हित लघु *) (buf + 64) == MSDOS_LABEL_MAGIC) अणु
		काष्ठा msकरोs_partition *part1_entry =
				(काष्ठा msकरोs_partition *)buf;
		काष्ठा msकरोs_partition *part_entry = part1_entry;
		पूर्णांक saved_cyl = diskparam->cylinders, part_no;
		अचिन्हित अक्षर part_end_head = 0, part_end_sector = 0;

		क्रम (part_no = 0; part_no < 4; part_no++) अणु
			part_end_head = part_entry->end_head;
			part_end_sector = part_entry->end_sector & 0x3F;
			अगर (part_end_head == 64 - 1) अणु
				diskparam->heads = 64;
				diskparam->sectors = 32;
				अवरोध;
			पूर्ण अन्यथा अगर (part_end_head == 128 - 1) अणु
				diskparam->heads = 128;
				diskparam->sectors = 32;
				अवरोध;
			पूर्ण अन्यथा अगर (part_end_head == 255 - 1) अणु
				diskparam->heads = 255;
				diskparam->sectors = 63;
				अवरोध;
			पूर्ण
			part_entry++;
		पूर्ण
		अगर (part_no == 4) अणु
			part_end_head = part1_entry->end_head;
			part_end_sector = part1_entry->end_sector & 0x3F;
		पूर्ण
		diskparam->cylinders = (अचिन्हित दीर्घ) capacity / (diskparam->heads * diskparam->sectors);
		अगर (part_no < 4 && part_end_sector == diskparam->sectors) अणु
			अगर (diskparam->cylinders != saved_cyl)
				blogic_warn("Adopting Geometry %d/%d from Partition Table\n", adapter, diskparam->heads, diskparam->sectors);
		पूर्ण अन्यथा अगर (part_end_head > 0 || part_end_sector > 0) अणु
			blogic_warn("Warning: Partition Table appears to have Geometry %d/%d which is\n", adapter, part_end_head + 1, part_end_sector);
			blogic_warn("not compatible with current BusLogic Host Adapter Geometry %d/%d\n", adapter, diskparam->heads, diskparam->sectors);
		पूर्ण
	पूर्ण
	kमुक्त(buf);
	वापस 0;
पूर्ण


/*
  BugLogic_ProcDirectoryInfo implements /proc/scsi/BusLogic/<N>.
*/

अटल पूर्णांक blogic_ग_लिखो_info(काष्ठा Scsi_Host *shost, अक्षर *procbuf,
				पूर्णांक bytes_avail)
अणु
	काष्ठा blogic_adapter *adapter =
				(काष्ठा blogic_adapter *) shost->hostdata;
	काष्ठा blogic_tgt_stats *tgt_stats;

	tgt_stats = adapter->tgt_stats;
	adapter->ext_resets = 0;
	adapter->adapter_पूर्णांकern_errors = 0;
	स_रखो(tgt_stats, 0, BLOGIC_MAXDEV * माप(काष्ठा blogic_tgt_stats));
	वापस 0;
पूर्ण

अटल पूर्णांक blogic_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *shost)
अणु
	काष्ठा blogic_adapter *adapter = (काष्ठा blogic_adapter *) shost->hostdata;
	काष्ठा blogic_tgt_stats *tgt_stats;
	पूर्णांक tgt;

	tgt_stats = adapter->tgt_stats;
	seq_ग_लिखो(m, adapter->msgbuf, adapter->msgbuflen);
	seq_म_लिखो(m, "\न\
Current Driver Queue Depth:	%d\न\
Currently Allocated CCBs:	%d\न", adapter->drvr_qdepth, adapter->alloc_ccbs);
	seq_माला_दो(m, "\न\न\
			   DATA TRANSFER STATISTICS\न\
\न\
Target	Tagged Queuing	Queue Depth  Active  Attempted	Completed\न\
======	==============	===========  ======  =========	=========\न");
	क्रम (tgt = 0; tgt < adapter->maxdev; tgt++) अणु
		काष्ठा blogic_tgt_flags *tgt_flags = &adapter->tgt_flags[tgt];
		अगर (!tgt_flags->tgt_exists)
			जारी;
		seq_म_लिखो(m, "  %2d	%s", tgt, (tgt_flags->tagq_ok ? (tgt_flags->tagq_active ? "    Active" : (adapter->tagq_ok & (1 << tgt)
																				    ? "  Permitted" : "   Disabled"))
									  : "Not Supported"));
		seq_म_लिखो(m,
				  "	    %3d       %3u    %9u	%9u\n", adapter->qdepth[tgt], adapter->active_cmds[tgt], tgt_stats[tgt].cmds_tried, tgt_stats[tgt].cmds_complete);
	पूर्ण
	seq_माला_दो(m, "\न\
Target  Read Commands  Write Commands   Total Bytes Read    Total Bytes Written\न\
======  =============  ==============  ===================  ===================\न");
	क्रम (tgt = 0; tgt < adapter->maxdev; tgt++) अणु
		काष्ठा blogic_tgt_flags *tgt_flags = &adapter->tgt_flags[tgt];
		अगर (!tgt_flags->tgt_exists)
			जारी;
		seq_म_लिखो(m, "  %2d	  %9u	 %9u", tgt, tgt_stats[tgt].पढ़ो_cmds, tgt_stats[tgt].ग_लिखो_cmds);
		अगर (tgt_stats[tgt].bytesपढ़ो.billions > 0)
			seq_म_लिखो(m, "     %9u%09u", tgt_stats[tgt].bytesपढ़ो.billions, tgt_stats[tgt].bytesपढ़ो.units);
		अन्यथा
			seq_म_लिखो(m, "		%9u", tgt_stats[tgt].bytesपढ़ो.units);
		अगर (tgt_stats[tgt].byteswritten.billions > 0)
			seq_म_लिखो(m, "   %9u%09u\n", tgt_stats[tgt].byteswritten.billions, tgt_stats[tgt].byteswritten.units);
		अन्यथा
			seq_म_लिखो(m, "	     %9u\n", tgt_stats[tgt].byteswritten.units);
	पूर्ण
	seq_माला_दो(m, "\न\
Target  Command    0-1KB      1-2KB      2-4KB      4-8KB     8-16KB\न\
======  =======  =========  =========  =========  =========  =========\न");
	क्रम (tgt = 0; tgt < adapter->maxdev; tgt++) अणु
		काष्ठा blogic_tgt_flags *tgt_flags = &adapter->tgt_flags[tgt];
		अगर (!tgt_flags->tgt_exists)
			जारी;
		seq_म_लिखो(m,
			    "  %2d	 Read	 %9u  %9u  %9u  %9u  %9u\n", tgt,
			    tgt_stats[tgt].पढ़ो_sz_buckets[0],
			    tgt_stats[tgt].पढ़ो_sz_buckets[1], tgt_stats[tgt].पढ़ो_sz_buckets[2], tgt_stats[tgt].पढ़ो_sz_buckets[3], tgt_stats[tgt].पढ़ो_sz_buckets[4]);
		seq_म_लिखो(m,
			    "  %2d	 Write	 %9u  %9u  %9u  %9u  %9u\n", tgt,
			    tgt_stats[tgt].ग_लिखो_sz_buckets[0],
			    tgt_stats[tgt].ग_लिखो_sz_buckets[1], tgt_stats[tgt].ग_लिखो_sz_buckets[2], tgt_stats[tgt].ग_लिखो_sz_buckets[3], tgt_stats[tgt].ग_लिखो_sz_buckets[4]);
	पूर्ण
	seq_माला_दो(m, "\न\
Target  Command   16-32KB    32-64KB   64-128KB   128-256KB   256KB+\न\
======  =======  =========  =========  =========  =========  =========\न");
	क्रम (tgt = 0; tgt < adapter->maxdev; tgt++) अणु
		काष्ठा blogic_tgt_flags *tgt_flags = &adapter->tgt_flags[tgt];
		अगर (!tgt_flags->tgt_exists)
			जारी;
		seq_म_लिखो(m,
			    "  %2d	 Read	 %9u  %9u  %9u  %9u  %9u\n", tgt,
			    tgt_stats[tgt].पढ़ो_sz_buckets[5],
			    tgt_stats[tgt].पढ़ो_sz_buckets[6], tgt_stats[tgt].पढ़ो_sz_buckets[7], tgt_stats[tgt].पढ़ो_sz_buckets[8], tgt_stats[tgt].पढ़ो_sz_buckets[9]);
		seq_म_लिखो(m,
			    "  %2d	 Write	 %9u  %9u  %9u  %9u  %9u\n", tgt,
			    tgt_stats[tgt].ग_लिखो_sz_buckets[5],
			    tgt_stats[tgt].ग_लिखो_sz_buckets[6], tgt_stats[tgt].ग_लिखो_sz_buckets[7], tgt_stats[tgt].ग_लिखो_sz_buckets[8], tgt_stats[tgt].ग_लिखो_sz_buckets[9]);
	पूर्ण
	seq_माला_दो(m, "\न\न\
			   ERROR RECOVERY STATISTICS\न\
\न\
	  Command Aborts      Bus Device Resets	  Host Adapter Resets\न\
Target	Requested Completed  Requested Completed  Requested Completed\न\
  ID	\\\\\\\\ Attempted ////  \\\\\\\\ Attempted ////  \\\\\\\\ Attempted ////\न\
======	 ===== ===== =====    ===== ===== =====	   ===== ===== =====\न");
	क्रम (tgt = 0; tgt < adapter->maxdev; tgt++) अणु
		काष्ठा blogic_tgt_flags *tgt_flags = &adapter->tgt_flags[tgt];
		अगर (!tgt_flags->tgt_exists)
			जारी;
		seq_म_लिखो(m, "  %2d	 %5d %5d %5d    %5d %5d %5d	   %5d %5d %5d\n",
			   tgt, tgt_stats[tgt].पातs_request,
			   tgt_stats[tgt].पातs_tried,
			   tgt_stats[tgt].पातs_करोne,
			   tgt_stats[tgt].bdr_request,
			   tgt_stats[tgt].bdr_tried,
			   tgt_stats[tgt].bdr_करोne,
			   tgt_stats[tgt].adapter_reset_req,
			   tgt_stats[tgt].adapter_reset_attempt,
			   tgt_stats[tgt].adapter_reset_करोne);
	पूर्ण
	seq_म_लिखो(m, "\nExternal Host Adapter Resets: %d\n", adapter->ext_resets);
	seq_म_लिखो(m, "Host Adapter Internal Errors: %d\n", adapter->adapter_पूर्णांकern_errors);
	वापस 0;
पूर्ण


/*
  blogic_msg prपूर्णांकs Driver Messages.
*/
__म_लिखो(2, 4)
अटल व्योम blogic_msg(क्रमागत blogic_msglevel msglevel, अक्षर *fmt,
			काष्ठा blogic_adapter *adapter, ...)
अणु
	अटल अक्षर buf[BLOGIC_LINEBUF_SIZE];
	अटल bool begin = true;
	बहु_सूची args;
	पूर्णांक len = 0;

	बहु_शुरू(args, adapter);
	len = भम_लिखो(buf, fmt, args);
	बहु_पूर्ण(args);
	अगर (msglevel == BLOGIC_ANNOUNCE_LEVEL) अणु
		अटल पूर्णांक msglines = 0;
		म_नकल(&adapter->msgbuf[adapter->msgbuflen], buf);
		adapter->msgbuflen += len;
		अगर (++msglines <= 2)
			prपूर्णांकk("%sscsi: %s", blogic_msglevelmap[msglevel], buf);
	पूर्ण अन्यथा अगर (msglevel == BLOGIC_INFO_LEVEL) अणु
		म_नकल(&adapter->msgbuf[adapter->msgbuflen], buf);
		adapter->msgbuflen += len;
		अगर (begin) अणु
			अगर (buf[0] != '\n' || len > 1)
				prपूर्णांकk("%sscsi%d: %s", blogic_msglevelmap[msglevel], adapter->host_no, buf);
		पूर्ण अन्यथा
			prपूर्णांकk("%s", buf);
	पूर्ण अन्यथा अणु
		अगर (begin) अणु
			अगर (adapter != शून्य && adapter->adapter_initd)
				prपूर्णांकk("%sscsi%d: %s", blogic_msglevelmap[msglevel], adapter->host_no, buf);
			अन्यथा
				prपूर्णांकk("%s%s", blogic_msglevelmap[msglevel], buf);
		पूर्ण अन्यथा
			prपूर्णांकk("%s", buf);
	पूर्ण
	begin = (buf[len - 1] == '\n');
पूर्ण


/*
  blogic_parse parses an inभागidual option keyword.  It वापसs true
  and updates the poपूर्णांकer अगर the keyword is recognized and false otherwise.
*/

अटल bool __init blogic_parse(अक्षर **str, अक्षर *keyword)
अणु
	अक्षर *poपूर्णांकer = *str;
	जबतक (*keyword != '\0') अणु
		अक्षर strch = *poपूर्णांकer++;
		अक्षर keywordch = *keyword++;
		अगर (strch >= 'A' && strch <= 'Z')
			strch += 'a' - 'Z';
		अगर (keywordch >= 'A' && keywordch <= 'Z')
			keywordch += 'a' - 'Z';
		अगर (strch != keywordch)
			वापस false;
	पूर्ण
	*str = poपूर्णांकer;
	वापस true;
पूर्ण


/*
  blogic_parseopts handles processing of BusLogic Driver Options
  specअगरications.

  BusLogic Driver Options may be specअगरied either via the Linux Kernel Command
  Line or via the Loadable Kernel Module Installation Facility.  Driver Options
  क्रम multiple host adapters may be specअगरied either by separating the option
  strings by a semicolon, or by specअगरying multiple "BusLogic=" strings on the
  command line.  Inभागidual option specअगरications क्रम a single host adapter are
  separated by commas.  The Probing and Debugging Options apply to all host
  adapters whereas the reमुख्यing options apply inभागidually only to the
  selected host adapter.

  The BusLogic Driver Probing Options are described in
  <file:Documentation/scsi/BusLogic.rst>.
*/

अटल पूर्णांक __init blogic_parseopts(अक्षर *options)
अणु
	जबतक (true) अणु
		काष्ठा blogic_drvr_options *drvr_opts =
			&blogic_drvr_options[blogic_drvr_options_count++];
		पूर्णांक tgt_id;

		स_रखो(drvr_opts, 0, माप(काष्ठा blogic_drvr_options));
		जबतक (*options != '\0' && *options != ';') अणु
			अगर (blogic_parse(&options, "NoProbePCI"))
				blogic_probe_options.noprobe_pci = true;
			अन्यथा अगर (blogic_parse(&options, "NoProbe"))
				blogic_probe_options.noprobe = true;
			अन्यथा अगर (blogic_parse(&options, "NoSortPCI"))
				blogic_probe_options.nosort_pci = true;
			अन्यथा अगर (blogic_parse(&options, "MultiMasterFirst"))
				blogic_probe_options.multimaster_first = true;
			अन्यथा अगर (blogic_parse(&options, "FlashPointFirst"))
				blogic_probe_options.flashpoपूर्णांक_first = true;
			/* Tagged Queuing Options. */
			अन्यथा अगर (blogic_parse(&options, "QueueDepth:[") ||
					blogic_parse(&options, "QD:[")) अणु
				क्रम (tgt_id = 0; tgt_id < BLOGIC_MAXDEV; tgt_id++) अणु
					अचिन्हित लघु qdepth = simple_म_से_अदीर्घ(options, &options, 0);
					अगर (qdepth > BLOGIC_MAX_TAG_DEPTH) अणु
						blogic_err("BusLogic: Invalid Driver Options (invalid Queue Depth %d)\n", शून्य, qdepth);
						वापस 0;
					पूर्ण
					drvr_opts->qdepth[tgt_id] = qdepth;
					अगर (*options == ',')
						options++;
					अन्यथा अगर (*options == ']')
						अवरोध;
					अन्यथा अणु
						blogic_err("BusLogic: Invalid Driver Options (',' or ']' expected at '%s')\n", शून्य, options);
						वापस 0;
					पूर्ण
				पूर्ण
				अगर (*options != ']') अणु
					blogic_err("BusLogic: Invalid Driver Options (']' expected at '%s')\n", शून्य, options);
					वापस 0;
				पूर्ण अन्यथा
					options++;
			पूर्ण अन्यथा अगर (blogic_parse(&options, "QueueDepth:") || blogic_parse(&options, "QD:")) अणु
				अचिन्हित लघु qdepth = simple_म_से_अदीर्घ(options, &options, 0);
				अगर (qdepth == 0 ||
						qdepth > BLOGIC_MAX_TAG_DEPTH) अणु
					blogic_err("BusLogic: Invalid Driver Options (invalid Queue Depth %d)\n", शून्य, qdepth);
					वापस 0;
				पूर्ण
				drvr_opts->common_qdepth = qdepth;
				क्रम (tgt_id = 0; tgt_id < BLOGIC_MAXDEV; tgt_id++)
					drvr_opts->qdepth[tgt_id] = qdepth;
			पूर्ण अन्यथा अगर (blogic_parse(&options, "TaggedQueuing:") ||
					blogic_parse(&options, "TQ:")) अणु
				अगर (blogic_parse(&options, "Default")) अणु
					drvr_opts->tagq_ok = 0x0000;
					drvr_opts->tagq_ok_mask = 0x0000;
				पूर्ण अन्यथा अगर (blogic_parse(&options, "Enable")) अणु
					drvr_opts->tagq_ok = 0xFFFF;
					drvr_opts->tagq_ok_mask = 0xFFFF;
				पूर्ण अन्यथा अगर (blogic_parse(&options, "Disable")) अणु
					drvr_opts->tagq_ok = 0x0000;
					drvr_opts->tagq_ok_mask = 0xFFFF;
				पूर्ण अन्यथा अणु
					अचिन्हित लघु tgt_bit;
					क्रम (tgt_id = 0, tgt_bit = 1;
						tgt_id < BLOGIC_MAXDEV;
						tgt_id++, tgt_bit <<= 1)
						चयन (*options++) अणु
						हाल 'Y':
							drvr_opts->tagq_ok |= tgt_bit;
							drvr_opts->tagq_ok_mask |= tgt_bit;
							अवरोध;
						हाल 'N':
							drvr_opts->tagq_ok &= ~tgt_bit;
							drvr_opts->tagq_ok_mask |= tgt_bit;
							अवरोध;
						हाल 'X':
							अवरोध;
						शेष:
							options--;
							tgt_id = BLOGIC_MAXDEV;
							अवरोध;
						पूर्ण
				पूर्ण
			पूर्ण
			/* Miscellaneous Options. */
			अन्यथा अगर (blogic_parse(&options, "BusSettleTime:") ||
					blogic_parse(&options, "BST:")) अणु
				अचिन्हित लघु bus_settle_समय =
					simple_म_से_अदीर्घ(options, &options, 0);
				अगर (bus_settle_समय > 5 * 60) अणु
					blogic_err("BusLogic: Invalid Driver Options (invalid Bus Settle Time %d)\n", शून्य, bus_settle_समय);
					वापस 0;
				पूर्ण
				drvr_opts->bus_settle_समय = bus_settle_समय;
			पूर्ण अन्यथा अगर (blogic_parse(&options,
						"InhibitTargetInquiry"))
				drvr_opts->stop_tgt_inquiry = true;
			/* Debugging Options. */
			अन्यथा अगर (blogic_parse(&options, "TraceProbe"))
				blogic_global_options.trace_probe = true;
			अन्यथा अगर (blogic_parse(&options, "TraceHardwareReset"))
				blogic_global_options.trace_hw_reset = true;
			अन्यथा अगर (blogic_parse(&options, "TraceConfiguration"))
				blogic_global_options.trace_config = true;
			अन्यथा अगर (blogic_parse(&options, "TraceErrors"))
				blogic_global_options.trace_err = true;
			अन्यथा अगर (blogic_parse(&options, "Debug")) अणु
				blogic_global_options.trace_probe = true;
				blogic_global_options.trace_hw_reset = true;
				blogic_global_options.trace_config = true;
				blogic_global_options.trace_err = true;
			पूर्ण
			अगर (*options == ',')
				options++;
			अन्यथा अगर (*options != ';' && *options != '\0') अणु
				blogic_err("BusLogic: Unexpected Driver Option '%s' ignored\n", शून्य, options);
				*options = '\0';
			पूर्ण
		पूर्ण
		अगर (!(blogic_drvr_options_count == 0 ||
			blogic_probeinfo_count == 0 ||
			blogic_drvr_options_count == blogic_probeinfo_count)) अणु
			blogic_err("BusLogic: Invalid Driver Options (all or no I/O Addresses must be specified)\n", शून्य);
			वापस 0;
		पूर्ण
		/*
		   Tagged Queuing is disabled when the Queue Depth is 1 since queuing
		   multiple commands is not possible.
		 */
		क्रम (tgt_id = 0; tgt_id < BLOGIC_MAXDEV; tgt_id++)
			अगर (drvr_opts->qdepth[tgt_id] == 1) अणु
				अचिन्हित लघु tgt_bit = 1 << tgt_id;
				drvr_opts->tagq_ok &= ~tgt_bit;
				drvr_opts->tagq_ok_mask |= tgt_bit;
			पूर्ण
		अगर (*options == ';')
			options++;
		अगर (*options == '\0')
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/*
  Get it all started
*/

अटल काष्ठा scsi_host_ढाँचा blogic_ढाँचा = अणु
	.module = THIS_MODULE,
	.proc_name = "BusLogic",
	.ग_लिखो_info = blogic_ग_लिखो_info,
	.show_info = blogic_show_info,
	.name = "BusLogic",
	.info = blogic_drvr_info,
	.queuecommand = blogic_qcmd,
	.slave_configure = blogic_slaveconfig,
	.bios_param = blogic_diskparam,
	.eh_host_reset_handler = blogic_hostreset,
#अगर 0
	.eh_पात_handler = blogic_पात,
#पूर्ण_अगर
	.max_sectors = 128,
पूर्ण;

/*
  blogic_setup handles processing of Kernel Command Line Arguments.
*/

अटल पूर्णांक __init blogic_setup(अक्षर *str)
अणु
	पूर्णांक पूर्णांकs[3];

	(व्योम) get_options(str, ARRAY_SIZE(पूर्णांकs), पूर्णांकs);

	अगर (पूर्णांकs[0] != 0) अणु
		blogic_err("BusLogic: Obsolete Command Line Entry Format Ignored\n", शून्य);
		वापस 0;
	पूर्ण
	अगर (str == शून्य || *str == '\0')
		वापस 0;
	वापस blogic_parseopts(str);
पूर्ण

/*
 * Exit function.  Deletes all hosts associated with this driver.
 */

अटल व्योम __निकास blogic_निकास(व्योम)
अणु
	काष्ठा blogic_adapter *ha, *next;

	list_क्रम_each_entry_safe(ha, next, &blogic_host_list, host_list)
		blogic_deladapter(ha);
पूर्ण

__setup("BusLogic=", blogic_setup);

#अगर_घोषित MODULE
/*अटल काष्ठा pci_device_id blogic_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_BUSLOGIC, PCI_DEVICE_ID_BUSLOGIC_MULTIMASTER,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणु PCI_VENDOR_ID_BUSLOGIC, PCI_DEVICE_ID_BUSLOGIC_MULTIMASTER_NC,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणु PCI_VENDOR_ID_BUSLOGIC, PCI_DEVICE_ID_BUSLOGIC_FLASHPOINT,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणु पूर्ण
पूर्ण;*/
अटल स्थिर काष्ठा pci_device_id blogic_pci_tbl[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_BUSLOGIC, PCI_DEVICE_ID_BUSLOGIC_MULTIMASTER)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BUSLOGIC, PCI_DEVICE_ID_BUSLOGIC_MULTIMASTER_NC)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BUSLOGIC, PCI_DEVICE_ID_BUSLOGIC_FLASHPOINT)पूर्ण,
	अणु0, पूर्ण,
पूर्ण;
#पूर्ण_अगर
MODULE_DEVICE_TABLE(pci, blogic_pci_tbl);

module_init(blogic_init);
module_निकास(blogic_निकास);
