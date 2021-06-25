<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Linux MegaRAID driver क्रम SAS based RAID controllers
 *
 *  Copyright (c) 2003-2013  LSI Corporation
 *  Copyright (c) 2013-2016  Avago Technologies
 *  Copyright (c) 2016-2018  Broadcom Inc.
 *
 *  Authors: Broadcom Inc.
 *           Sreenivas Bagalkote
 *           Sumant Patro
 *           Bo Yang
 *           Adam Radक्रमd
 *           Kashyap Desai <kashyap.desai@broadcom.com>
 *           Sumit Saxena <sumit.saxena@broadcom.com>
 *
 *  Send feedback to: megaraidlinux.pdl@broadcom.com
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/list.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/uपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/fs.h>
#समावेश <linux/compat.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/mutex.h>
#समावेश <linux/poll.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/irq_poll.h>
#समावेश <linux/blk-mq-pci.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश "megaraid_sas_fusion.h"
#समावेश "megaraid_sas.h"

/*
 * Number of sectors per IO command
 * Will be set in megasas_init_mfi अगर user करोes not provide
 */
अटल अचिन्हित पूर्णांक max_sectors;
module_param_named(max_sectors, max_sectors, पूर्णांक, 0444);
MODULE_PARM_DESC(max_sectors,
	"Maximum number of sectors per IO command");

अटल पूर्णांक msix_disable;
module_param(msix_disable, पूर्णांक, 0444);
MODULE_PARM_DESC(msix_disable, "Disable MSI-X interrupt handling. Default: 0");

अटल अचिन्हित पूर्णांक msix_vectors;
module_param(msix_vectors, पूर्णांक, 0444);
MODULE_PARM_DESC(msix_vectors, "MSI-X max vector count. Default: Set by FW");

अटल पूर्णांक allow_vf_ioctls;
module_param(allow_vf_ioctls, पूर्णांक, 0444);
MODULE_PARM_DESC(allow_vf_ioctls, "Allow ioctls in SR-IOV VF mode. Default: 0");

अटल अचिन्हित पूर्णांक throttlequeuedepth = MEGASAS_THROTTLE_QUEUE_DEPTH;
module_param(throttlequeuedepth, पूर्णांक, 0444);
MODULE_PARM_DESC(throttlequeuedepth,
	"Adapter queue depth when throttled due to I/O timeout. Default: 16");

अचिन्हित पूर्णांक resetरुकोसमय = MEGASAS_RESET_WAIT_TIME;
module_param(resetरुकोसमय, पूर्णांक, 0444);
MODULE_PARM_DESC(resetरुकोसमय, "Wait time in (1-180s) after I/O timeout before resetting adapter. Default: 180s");

अटल पूर्णांक smp_affinity_enable = 1;
module_param(smp_affinity_enable, पूर्णांक, 0444);
MODULE_PARM_DESC(smp_affinity_enable, "SMP affinity feature enable/disable Default: enable(1)");

अटल पूर्णांक rdpq_enable = 1;
module_param(rdpq_enable, पूर्णांक, 0444);
MODULE_PARM_DESC(rdpq_enable, "Allocate reply queue in chunks for large queue depth enable/disable Default: enable(1)");

अचिन्हित पूर्णांक dual_qdepth_disable;
module_param(dual_qdepth_disable, पूर्णांक, 0444);
MODULE_PARM_DESC(dual_qdepth_disable, "Disable dual queue depth feature. Default: 0");

अटल अचिन्हित पूर्णांक scmd_समयout = MEGASAS_DEFAULT_CMD_TIMEOUT;
module_param(scmd_समयout, पूर्णांक, 0444);
MODULE_PARM_DESC(scmd_समयout, "scsi command timeout (10-90s), default 90s. See megasas_reset_timer.");

पूर्णांक perf_mode = -1;
module_param(perf_mode, पूर्णांक, 0444);
MODULE_PARM_DESC(perf_mode, "Performance mode (only for Aero adapters), options:\n\t\t"
		"0 - balanced: High iops and low latency queues are allocated &\n\t\t"
		"interrupt coalescing is enabled only on high iops queues\n\t\t"
		"1 - iops: High iops queues are not allocated &\n\t\t"
		"interrupt coalescing is enabled on all queues\n\t\t"
		"2 - latency: High iops queues are not allocated &\n\t\t"
		"interrupt coalescing is disabled on all queues\n\t\t"
		"default mode is 'balanced'"
		);

पूर्णांक event_log_level = MFI_EVT_CLASS_CRITICAL;
module_param(event_log_level, पूर्णांक, 0644);
MODULE_PARM_DESC(event_log_level, "Asynchronous event logging level- range is: -2(CLASS_DEBUG) to 4(CLASS_DEAD), Default: 2(CLASS_CRITICAL)");

अचिन्हित पूर्णांक enable_sdev_max_qd;
module_param(enable_sdev_max_qd, पूर्णांक, 0444);
MODULE_PARM_DESC(enable_sdev_max_qd, "Enable sdev max qd as can_queue. Default: 0");

पूर्णांक poll_queues;
module_param(poll_queues, पूर्णांक, 0444);
MODULE_PARM_DESC(poll_queues, "Number of queues to be use for io_uring poll mode.\n\t\t"
		"This parameter is effective only if host_tagset_enable=1 &\n\t\t"
		"It is not applicable for MFI_SERIES. &\n\t\t"
		"Driver will work in latency mode. &\n\t\t"
		"High iops queues are not allocated &\n\t\t"
		);

पूर्णांक host_tagset_enable = 1;
module_param(host_tagset_enable, पूर्णांक, 0444);
MODULE_PARM_DESC(host_tagset_enable, "Shared host tagset enable/disable Default: enable(1)");

MODULE_LICENSE("GPL");
MODULE_VERSION(MEGASAS_VERSION);
MODULE_AUTHOR("megaraidlinux.pdl@broadcom.com");
MODULE_DESCRIPTION("Broadcom MegaRAID SAS Driver");

पूर्णांक megasas_transition_to_पढ़ोy(काष्ठा megasas_instance *instance, पूर्णांक ocr);
अटल पूर्णांक megasas_get_pd_list(काष्ठा megasas_instance *instance);
अटल पूर्णांक megasas_ld_list_query(काष्ठा megasas_instance *instance,
				 u8 query_type);
अटल पूर्णांक megasas_issue_init_mfi(काष्ठा megasas_instance *instance);
अटल पूर्णांक megasas_रेजिस्टर_aen(काष्ठा megasas_instance *instance,
				u32 seq_num, u32 class_locale_word);
अटल व्योम megasas_get_pd_info(काष्ठा megasas_instance *instance,
				काष्ठा scsi_device *sdev);

/*
 * PCI ID table क्रम all supported controllers
 */
अटल काष्ठा pci_device_id megasas_pci_table[] = अणु

	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_SAS1064R)पूर्ण,
	/* xscale IOP */
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_SAS1078R)पूर्ण,
	/* ppc IOP */
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_SAS1078DE)पूर्ण,
	/* ppc IOP */
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_SAS1078GEN2)पूर्ण,
	/* gen2*/
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_SAS0079GEN2)पूर्ण,
	/* gen2*/
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_SAS0073SKINNY)पूर्ण,
	/* skinny*/
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_SAS0071SKINNY)पूर्ण,
	/* skinny*/
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_VERDE_ZCR)पूर्ण,
	/* xscale IOP, vega */
	अणुPCI_DEVICE(PCI_VENDOR_ID_DELL, PCI_DEVICE_ID_DELL_PERC5)पूर्ण,
	/* xscale IOP */
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_FUSION)पूर्ण,
	/* Fusion */
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_PLASMA)पूर्ण,
	/* Plयंत्रa */
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_INVADER)पूर्ण,
	/* Invader */
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_FURY)पूर्ण,
	/* Fury */
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_INTRUDER)पूर्ण,
	/* Intruder */
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_INTRUDER_24)पूर्ण,
	/* Intruder 24 port*/
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_CUTLASS_52)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_CUTLASS_53)पूर्ण,
	/* VENTURA */
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_VENTURA)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_CRUSADER)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_HARPOON)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_TOMCAT)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_VENTURA_4PORT)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_CRUSADER_4PORT)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_AERO_10E1)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_AERO_10E2)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_AERO_10E5)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_AERO_10E6)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_AERO_10E0)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_AERO_10E3)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_AERO_10E4)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_AERO_10E7)पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, megasas_pci_table);

अटल पूर्णांक megasas_mgmt_majorno;
काष्ठा megasas_mgmt_info megasas_mgmt_info;
अटल काष्ठा fasync_काष्ठा *megasas_async_queue;
अटल DEFINE_MUTEX(megasas_async_queue_mutex);

अटल पूर्णांक megasas_poll_रुको_aen;
अटल DECLARE_WAIT_QUEUE_HEAD(megasas_poll_रुको);
अटल u32 support_poll_क्रम_event;
u32 megasas_dbg_lvl;
अटल u32 support_device_change;
अटल bool support_nvme_encapsulation;
अटल bool support_pci_lane_margining;

/* define lock क्रम aen poll */
अटल spinlock_t poll_aen_lock;

बाह्य काष्ठा dentry *megasas_debugfs_root;
बाह्य पूर्णांक megasas_blk_mq_poll(काष्ठा Scsi_Host *shost, अचिन्हित पूर्णांक queue_num);

व्योम
megasas_complete_cmd(काष्ठा megasas_instance *instance, काष्ठा megasas_cmd *cmd,
		     u8 alt_status);
अटल u32
megasas_पढ़ो_fw_status_reg_gen2(काष्ठा megasas_instance *instance);
अटल पूर्णांक
megasas_adp_reset_gen2(काष्ठा megasas_instance *instance,
		       काष्ठा megasas_रेजिस्टर_set __iomem *reg_set);
अटल irqवापस_t megasas_isr(पूर्णांक irq, व्योम *devp);
अटल u32
megasas_init_adapter_mfi(काष्ठा megasas_instance *instance);
u32
megasas_build_and_issue_cmd(काष्ठा megasas_instance *instance,
			    काष्ठा scsi_cmnd *scmd);
अटल व्योम megasas_complete_cmd_dpc(अचिन्हित दीर्घ instance_addr);
पूर्णांक
रुको_and_poll(काष्ठा megasas_instance *instance, काष्ठा megasas_cmd *cmd,
	पूर्णांक seconds);
व्योम megasas_fusion_ocr_wq(काष्ठा work_काष्ठा *work);
अटल पूर्णांक megasas_get_ld_vf_affiliation(काष्ठा megasas_instance *instance,
					 पूर्णांक initial);
अटल पूर्णांक
megasas_set_dma_mask(काष्ठा megasas_instance *instance);
अटल पूर्णांक
megasas_alloc_ctrl_mem(काष्ठा megasas_instance *instance);
अटल अंतरभूत व्योम
megasas_मुक्त_ctrl_mem(काष्ठा megasas_instance *instance);
अटल अंतरभूत पूर्णांक
megasas_alloc_ctrl_dma_buffers(काष्ठा megasas_instance *instance);
अटल अंतरभूत व्योम
megasas_मुक्त_ctrl_dma_buffers(काष्ठा megasas_instance *instance);
अटल अंतरभूत व्योम
megasas_init_ctrl_params(काष्ठा megasas_instance *instance);

u32 megasas_पढ़ोl(काष्ठा megasas_instance *instance,
		  स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u32 i = 0, ret_val;
	/*
	 * Due to a HW errata in Aero controllers, पढ़ोs to certain
	 * Fusion रेजिस्टरs could पूर्णांकermittently वापस all zeroes.
	 * This behavior is transient in nature and subsequent पढ़ोs will
	 * वापस valid value. As a workaround in driver, retry पढ़ोl क्रम
	 * upto three बार until a non-zero value is पढ़ो.
	 */
	अगर (instance->adapter_type == AERO_SERIES) अणु
		करो अणु
			ret_val = पढ़ोl(addr);
			i++;
		पूर्ण जबतक (ret_val == 0 && i < 3);
		वापस ret_val;
	पूर्ण अन्यथा अणु
		वापस पढ़ोl(addr);
	पूर्ण
पूर्ण

/**
 * megasas_set_dma_settings -	Populate DMA address, length and flags क्रम DCMDs
 * @instance:			Adapter soft state
 * @dcmd:			DCMD frame inside MFI command
 * @dma_addr:			DMA address of buffer to be passed to FW
 * @dma_len:			Length of DMA buffer to be passed to FW
 * @वापस:			व्योम
 */
व्योम megasas_set_dma_settings(काष्ठा megasas_instance *instance,
			      काष्ठा megasas_dcmd_frame *dcmd,
			      dma_addr_t dma_addr, u32 dma_len)
अणु
	अगर (instance->consistent_mask_64bit) अणु
		dcmd->sgl.sge64[0].phys_addr = cpu_to_le64(dma_addr);
		dcmd->sgl.sge64[0].length = cpu_to_le32(dma_len);
		dcmd->flags = cpu_to_le16(dcmd->flags | MFI_FRAME_SGL64);

	पूर्ण अन्यथा अणु
		dcmd->sgl.sge32[0].phys_addr =
				cpu_to_le32(lower_32_bits(dma_addr));
		dcmd->sgl.sge32[0].length = cpu_to_le32(dma_len);
		dcmd->flags = cpu_to_le16(dcmd->flags);
	पूर्ण
पूर्ण

अटल व्योम
megasas_issue_dcmd(काष्ठा megasas_instance *instance, काष्ठा megasas_cmd *cmd)
अणु
	instance->instancet->fire_cmd(instance,
		cmd->frame_phys_addr, 0, instance->reg_set);
	वापस;
पूर्ण

/**
 * megasas_get_cmd -	Get a command from the मुक्त pool
 * @instance:		Adapter soft state
 *
 * Returns a मुक्त command from the pool
 */
काष्ठा megasas_cmd *megasas_get_cmd(काष्ठा megasas_instance
						  *instance)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा megasas_cmd *cmd = शून्य;

	spin_lock_irqsave(&instance->mfi_pool_lock, flags);

	अगर (!list_empty(&instance->cmd_pool)) अणु
		cmd = list_entry((&instance->cmd_pool)->next,
				 काष्ठा megasas_cmd, list);
		list_del_init(&cmd->list);
	पूर्ण अन्यथा अणु
		dev_err(&instance->pdev->dev, "Command pool empty!\n");
	पूर्ण

	spin_unlock_irqrestore(&instance->mfi_pool_lock, flags);
	वापस cmd;
पूर्ण

/**
 * megasas_वापस_cmd -	Return a cmd to मुक्त command pool
 * @instance:		Adapter soft state
 * @cmd:		Command packet to be वापसed to मुक्त command pool
 */
व्योम
megasas_वापस_cmd(काष्ठा megasas_instance *instance, काष्ठा megasas_cmd *cmd)
अणु
	अचिन्हित दीर्घ flags;
	u32 blk_tags;
	काष्ठा megasas_cmd_fusion *cmd_fusion;
	काष्ठा fusion_context *fusion = instance->ctrl_context;

	/* This flag is used only क्रम fusion adapter.
	 * Wait क्रम Interrupt क्रम Polled mode DCMD
	 */
	अगर (cmd->flags & DRV_DCMD_POLLED_MODE)
		वापस;

	spin_lock_irqsave(&instance->mfi_pool_lock, flags);

	अगर (fusion) अणु
		blk_tags = instance->max_scsi_cmds + cmd->index;
		cmd_fusion = fusion->cmd_list[blk_tags];
		megasas_वापस_cmd_fusion(instance, cmd_fusion);
	पूर्ण
	cmd->scmd = शून्य;
	cmd->frame_count = 0;
	cmd->flags = 0;
	स_रखो(cmd->frame, 0, instance->mfi_frame_size);
	cmd->frame->io.context = cpu_to_le32(cmd->index);
	अगर (!fusion && reset_devices)
		cmd->frame->hdr.cmd = MFI_CMD_INVALID;
	list_add(&cmd->list, (&instance->cmd_pool)->next);

	spin_unlock_irqrestore(&instance->mfi_pool_lock, flags);

पूर्ण

अटल स्थिर अक्षर *
क्रमmat_बारtamp(uपूर्णांक32_t बारtamp)
अणु
	अटल अक्षर buffer[32];

	अगर ((बारtamp & 0xff000000) == 0xff000000)
		snम_लिखो(buffer, माप(buffer), "boot + %us", बारtamp &
		0x00ffffff);
	अन्यथा
		snम_लिखो(buffer, माप(buffer), "%us", बारtamp);
	वापस buffer;
पूर्ण

अटल स्थिर अक्षर *
क्रमmat_class(पूर्णांक8_t class)
अणु
	अटल अक्षर buffer[6];

	चयन (class) अणु
	हाल MFI_EVT_CLASS_DEBUG:
		वापस "debug";
	हाल MFI_EVT_CLASS_PROGRESS:
		वापस "progress";
	हाल MFI_EVT_CLASS_INFO:
		वापस "info";
	हाल MFI_EVT_CLASS_WARNING:
		वापस "WARN";
	हाल MFI_EVT_CLASS_CRITICAL:
		वापस "CRIT";
	हाल MFI_EVT_CLASS_FATAL:
		वापस "FATAL";
	हाल MFI_EVT_CLASS_DEAD:
		वापस "DEAD";
	शेष:
		snम_लिखो(buffer, माप(buffer), "%d", class);
		वापस buffer;
	पूर्ण
पूर्ण

/**
  * megasas_decode_evt: Decode FW AEN event and prपूर्णांक critical event
  * क्रम inक्रमmation.
  * @instance:			Adapter soft state
  */
अटल व्योम
megasas_decode_evt(काष्ठा megasas_instance *instance)
अणु
	काष्ठा megasas_evt_detail *evt_detail = instance->evt_detail;
	जोड़ megasas_evt_class_locale class_locale;
	class_locale.word = le32_to_cpu(evt_detail->cl.word);

	अगर ((event_log_level < MFI_EVT_CLASS_DEBUG) ||
	    (event_log_level > MFI_EVT_CLASS_DEAD)) अणु
		prपूर्णांकk(KERN_WARNING "megaraid_sas: provided event log level is out of range, setting it to default 2(CLASS_CRITICAL), permissible range is: -2 to 4\n");
		event_log_level = MFI_EVT_CLASS_CRITICAL;
	पूर्ण

	अगर (class_locale.members.class >= event_log_level)
		dev_info(&instance->pdev->dev, "%d (%s/0x%04x/%s) - %s\n",
			le32_to_cpu(evt_detail->seq_num),
			क्रमmat_बारtamp(le32_to_cpu(evt_detail->समय_stamp)),
			(class_locale.members.locale),
			क्रमmat_class(class_locale.members.class),
			evt_detail->description);
पूर्ण

/*
 * The following functions are defined क्रम xscale
 * (deviceid : 1064R, PERC5) controllers
 */

/**
 * megasas_enable_पूर्णांकr_xscale -	Enables पूर्णांकerrupts
 * @instance:	Adapter soft state
 */
अटल अंतरभूत व्योम
megasas_enable_पूर्णांकr_xscale(काष्ठा megasas_instance *instance)
अणु
	काष्ठा megasas_रेजिस्टर_set __iomem *regs;

	regs = instance->reg_set;
	ग_लिखोl(0, &(regs)->outbound_पूर्णांकr_mask);

	/* Dummy पढ़ोl to क्रमce pci flush */
	पढ़ोl(&regs->outbound_पूर्णांकr_mask);
पूर्ण

/**
 * megasas_disable_पूर्णांकr_xscale -Disables पूर्णांकerrupt
 * @instance:	Adapter soft state
 */
अटल अंतरभूत व्योम
megasas_disable_पूर्णांकr_xscale(काष्ठा megasas_instance *instance)
अणु
	काष्ठा megasas_रेजिस्टर_set __iomem *regs;
	u32 mask = 0x1f;

	regs = instance->reg_set;
	ग_लिखोl(mask, &regs->outbound_पूर्णांकr_mask);
	/* Dummy पढ़ोl to क्रमce pci flush */
	पढ़ोl(&regs->outbound_पूर्णांकr_mask);
पूर्ण

/**
 * megasas_पढ़ो_fw_status_reg_xscale - वापसs the current FW status value
 * @instance:	Adapter soft state
 */
अटल u32
megasas_पढ़ो_fw_status_reg_xscale(काष्ठा megasas_instance *instance)
अणु
	वापस पढ़ोl(&instance->reg_set->outbound_msg_0);
पूर्ण
/**
 * megasas_clear_पूर्णांकr_xscale -	Check & clear पूर्णांकerrupt
 * @instance:	Adapter soft state
 */
अटल पूर्णांक
megasas_clear_पूर्णांकr_xscale(काष्ठा megasas_instance *instance)
अणु
	u32 status;
	u32 mfiStatus = 0;
	काष्ठा megasas_रेजिस्टर_set __iomem *regs;
	regs = instance->reg_set;

	/*
	 * Check अगर it is our पूर्णांकerrupt
	 */
	status = पढ़ोl(&regs->outbound_पूर्णांकr_status);

	अगर (status & MFI_OB_INTR_STATUS_MASK)
		mfiStatus = MFI_INTR_FLAG_REPLY_MESSAGE;
	अगर (status & MFI_XSCALE_OMR0_CHANGE_INTERRUPT)
		mfiStatus |= MFI_INTR_FLAG_FIRMWARE_STATE_CHANGE;

	/*
	 * Clear the पूर्णांकerrupt by writing back the same value
	 */
	अगर (mfiStatus)
		ग_लिखोl(status, &regs->outbound_पूर्णांकr_status);

	/* Dummy पढ़ोl to क्रमce pci flush */
	पढ़ोl(&regs->outbound_पूर्णांकr_status);

	वापस mfiStatus;
पूर्ण

/**
 * megasas_fire_cmd_xscale -	Sends command to the FW
 * @instance:		Adapter soft state
 * @frame_phys_addr :	Physical address of cmd
 * @frame_count :	Number of frames क्रम the command
 * @regs :		MFI रेजिस्टर set
 */
अटल अंतरभूत व्योम
megasas_fire_cmd_xscale(काष्ठा megasas_instance *instance,
		dma_addr_t frame_phys_addr,
		u32 frame_count,
		काष्ठा megasas_रेजिस्टर_set __iomem *regs)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&instance->hba_lock, flags);
	ग_लिखोl((frame_phys_addr >> 3)|(frame_count),
	       &(regs)->inbound_queue_port);
	spin_unlock_irqrestore(&instance->hba_lock, flags);
पूर्ण

/**
 * megasas_adp_reset_xscale -  For controller reset
 * @instance:	Adapter soft state
 * @regs:	MFI रेजिस्टर set
 */
अटल पूर्णांक
megasas_adp_reset_xscale(काष्ठा megasas_instance *instance,
	काष्ठा megasas_रेजिस्टर_set __iomem *regs)
अणु
	u32 i;
	u32 pcidata;

	ग_लिखोl(MFI_ADP_RESET, &regs->inbound_करोorbell);

	क्रम (i = 0; i < 3; i++)
		msleep(1000); /* sleep क्रम 3 secs */
	pcidata  = 0;
	pci_पढ़ो_config_dword(instance->pdev, MFI_1068_PCSR_OFFSET, &pcidata);
	dev_notice(&instance->pdev->dev, "pcidata = %x\n", pcidata);
	अगर (pcidata & 0x2) अणु
		dev_notice(&instance->pdev->dev, "mfi 1068 offset read=%x\n", pcidata);
		pcidata &= ~0x2;
		pci_ग_लिखो_config_dword(instance->pdev,
				MFI_1068_PCSR_OFFSET, pcidata);

		क्रम (i = 0; i < 2; i++)
			msleep(1000); /* need to रुको 2 secs again */

		pcidata  = 0;
		pci_पढ़ो_config_dword(instance->pdev,
				MFI_1068_FW_HANDSHAKE_OFFSET, &pcidata);
		dev_notice(&instance->pdev->dev, "1068 offset handshake read=%x\n", pcidata);
		अगर ((pcidata & 0xffff0000) == MFI_1068_FW_READY) अणु
			dev_notice(&instance->pdev->dev, "1068 offset pcidt=%x\n", pcidata);
			pcidata = 0;
			pci_ग_लिखो_config_dword(instance->pdev,
				MFI_1068_FW_HANDSHAKE_OFFSET, pcidata);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * megasas_check_reset_xscale -	For controller reset check
 * @instance:	Adapter soft state
 * @regs:	MFI रेजिस्टर set
 */
अटल पूर्णांक
megasas_check_reset_xscale(काष्ठा megasas_instance *instance,
		काष्ठा megasas_रेजिस्टर_set __iomem *regs)
अणु
	अगर ((atomic_पढ़ो(&instance->adprecovery) != MEGASAS_HBA_OPERATIONAL) &&
	    (le32_to_cpu(*instance->consumer) ==
		MEGASAS_ADPRESET_INPROG_SIGN))
		वापस 1;
	वापस 0;
पूर्ण

अटल काष्ठा megasas_instance_ढाँचा megasas_instance_ढाँचा_xscale = अणु

	.fire_cmd = megasas_fire_cmd_xscale,
	.enable_पूर्णांकr = megasas_enable_पूर्णांकr_xscale,
	.disable_पूर्णांकr = megasas_disable_पूर्णांकr_xscale,
	.clear_पूर्णांकr = megasas_clear_पूर्णांकr_xscale,
	.पढ़ो_fw_status_reg = megasas_पढ़ो_fw_status_reg_xscale,
	.adp_reset = megasas_adp_reset_xscale,
	.check_reset = megasas_check_reset_xscale,
	.service_isr = megasas_isr,
	.tasklet = megasas_complete_cmd_dpc,
	.init_adapter = megasas_init_adapter_mfi,
	.build_and_issue_cmd = megasas_build_and_issue_cmd,
	.issue_dcmd = megasas_issue_dcmd,
पूर्ण;

/*
 * This is the end of set of functions & definitions specअगरic
 * to xscale (deviceid : 1064R, PERC5) controllers
 */

/*
 * The following functions are defined क्रम ppc (deviceid : 0x60)
 * controllers
 */

/**
 * megasas_enable_पूर्णांकr_ppc -	Enables पूर्णांकerrupts
 * @instance:	Adapter soft state
 */
अटल अंतरभूत व्योम
megasas_enable_पूर्णांकr_ppc(काष्ठा megasas_instance *instance)
अणु
	काष्ठा megasas_रेजिस्टर_set __iomem *regs;

	regs = instance->reg_set;
	ग_लिखोl(0xFFFFFFFF, &(regs)->outbound_करोorbell_clear);

	ग_लिखोl(~0x80000000, &(regs)->outbound_पूर्णांकr_mask);

	/* Dummy पढ़ोl to क्रमce pci flush */
	पढ़ोl(&regs->outbound_पूर्णांकr_mask);
पूर्ण

/**
 * megasas_disable_पूर्णांकr_ppc -	Disable पूर्णांकerrupt
 * @instance:	Adapter soft state
 */
अटल अंतरभूत व्योम
megasas_disable_पूर्णांकr_ppc(काष्ठा megasas_instance *instance)
अणु
	काष्ठा megasas_रेजिस्टर_set __iomem *regs;
	u32 mask = 0xFFFFFFFF;

	regs = instance->reg_set;
	ग_लिखोl(mask, &regs->outbound_पूर्णांकr_mask);
	/* Dummy पढ़ोl to क्रमce pci flush */
	पढ़ोl(&regs->outbound_पूर्णांकr_mask);
पूर्ण

/**
 * megasas_पढ़ो_fw_status_reg_ppc - वापसs the current FW status value
 * @instance:	Adapter soft state
 */
अटल u32
megasas_पढ़ो_fw_status_reg_ppc(काष्ठा megasas_instance *instance)
अणु
	वापस पढ़ोl(&instance->reg_set->outbound_scratch_pad_0);
पूर्ण

/**
 * megasas_clear_पूर्णांकr_ppc -	Check & clear पूर्णांकerrupt
 * @instance:	Adapter soft state
 */
अटल पूर्णांक
megasas_clear_पूर्णांकr_ppc(काष्ठा megasas_instance *instance)
अणु
	u32 status, mfiStatus = 0;
	काष्ठा megasas_रेजिस्टर_set __iomem *regs;
	regs = instance->reg_set;

	/*
	 * Check अगर it is our पूर्णांकerrupt
	 */
	status = पढ़ोl(&regs->outbound_पूर्णांकr_status);

	अगर (status & MFI_REPLY_1078_MESSAGE_INTERRUPT)
		mfiStatus = MFI_INTR_FLAG_REPLY_MESSAGE;

	अगर (status & MFI_G2_OUTBOUND_DOORBELL_CHANGE_INTERRUPT)
		mfiStatus |= MFI_INTR_FLAG_FIRMWARE_STATE_CHANGE;

	/*
	 * Clear the पूर्णांकerrupt by writing back the same value
	 */
	ग_लिखोl(status, &regs->outbound_करोorbell_clear);

	/* Dummy पढ़ोl to क्रमce pci flush */
	पढ़ोl(&regs->outbound_करोorbell_clear);

	वापस mfiStatus;
पूर्ण

/**
 * megasas_fire_cmd_ppc -	Sends command to the FW
 * @instance:		Adapter soft state
 * @frame_phys_addr:	Physical address of cmd
 * @frame_count:	Number of frames क्रम the command
 * @regs:		MFI रेजिस्टर set
 */
अटल अंतरभूत व्योम
megasas_fire_cmd_ppc(काष्ठा megasas_instance *instance,
		dma_addr_t frame_phys_addr,
		u32 frame_count,
		काष्ठा megasas_रेजिस्टर_set __iomem *regs)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&instance->hba_lock, flags);
	ग_लिखोl((frame_phys_addr | (frame_count<<1))|1,
			&(regs)->inbound_queue_port);
	spin_unlock_irqrestore(&instance->hba_lock, flags);
पूर्ण

/**
 * megasas_check_reset_ppc -	For controller reset check
 * @instance:	Adapter soft state
 * @regs:	MFI रेजिस्टर set
 */
अटल पूर्णांक
megasas_check_reset_ppc(काष्ठा megasas_instance *instance,
			काष्ठा megasas_रेजिस्टर_set __iomem *regs)
अणु
	अगर (atomic_पढ़ो(&instance->adprecovery) != MEGASAS_HBA_OPERATIONAL)
		वापस 1;

	वापस 0;
पूर्ण

अटल काष्ठा megasas_instance_ढाँचा megasas_instance_ढाँचा_ppc = अणु

	.fire_cmd = megasas_fire_cmd_ppc,
	.enable_पूर्णांकr = megasas_enable_पूर्णांकr_ppc,
	.disable_पूर्णांकr = megasas_disable_पूर्णांकr_ppc,
	.clear_पूर्णांकr = megasas_clear_पूर्णांकr_ppc,
	.पढ़ो_fw_status_reg = megasas_पढ़ो_fw_status_reg_ppc,
	.adp_reset = megasas_adp_reset_xscale,
	.check_reset = megasas_check_reset_ppc,
	.service_isr = megasas_isr,
	.tasklet = megasas_complete_cmd_dpc,
	.init_adapter = megasas_init_adapter_mfi,
	.build_and_issue_cmd = megasas_build_and_issue_cmd,
	.issue_dcmd = megasas_issue_dcmd,
पूर्ण;

/**
 * megasas_enable_पूर्णांकr_skinny -	Enables पूर्णांकerrupts
 * @instance:	Adapter soft state
 */
अटल अंतरभूत व्योम
megasas_enable_पूर्णांकr_skinny(काष्ठा megasas_instance *instance)
अणु
	काष्ठा megasas_रेजिस्टर_set __iomem *regs;

	regs = instance->reg_set;
	ग_लिखोl(0xFFFFFFFF, &(regs)->outbound_पूर्णांकr_mask);

	ग_लिखोl(~MFI_SKINNY_ENABLE_INTERRUPT_MASK, &(regs)->outbound_पूर्णांकr_mask);

	/* Dummy पढ़ोl to क्रमce pci flush */
	पढ़ोl(&regs->outbound_पूर्णांकr_mask);
पूर्ण

/**
 * megasas_disable_पूर्णांकr_skinny -	Disables पूर्णांकerrupt
 * @instance:	Adapter soft state
 */
अटल अंतरभूत व्योम
megasas_disable_पूर्णांकr_skinny(काष्ठा megasas_instance *instance)
अणु
	काष्ठा megasas_रेजिस्टर_set __iomem *regs;
	u32 mask = 0xFFFFFFFF;

	regs = instance->reg_set;
	ग_लिखोl(mask, &regs->outbound_पूर्णांकr_mask);
	/* Dummy पढ़ोl to क्रमce pci flush */
	पढ़ोl(&regs->outbound_पूर्णांकr_mask);
पूर्ण

/**
 * megasas_पढ़ो_fw_status_reg_skinny - वापसs the current FW status value
 * @instance:	Adapter soft state
 */
अटल u32
megasas_पढ़ो_fw_status_reg_skinny(काष्ठा megasas_instance *instance)
अणु
	वापस पढ़ोl(&instance->reg_set->outbound_scratch_pad_0);
पूर्ण

/**
 * megasas_clear_पूर्णांकr_skinny -	Check & clear पूर्णांकerrupt
 * @instance:	Adapter soft state
 */
अटल पूर्णांक
megasas_clear_पूर्णांकr_skinny(काष्ठा megasas_instance *instance)
अणु
	u32 status;
	u32 mfiStatus = 0;
	काष्ठा megasas_रेजिस्टर_set __iomem *regs;
	regs = instance->reg_set;

	/*
	 * Check अगर it is our पूर्णांकerrupt
	 */
	status = पढ़ोl(&regs->outbound_पूर्णांकr_status);

	अगर (!(status & MFI_SKINNY_ENABLE_INTERRUPT_MASK)) अणु
		वापस 0;
	पूर्ण

	/*
	 * Check अगर it is our पूर्णांकerrupt
	 */
	अगर ((megasas_पढ़ो_fw_status_reg_skinny(instance) & MFI_STATE_MASK) ==
	    MFI_STATE_FAULT) अणु
		mfiStatus = MFI_INTR_FLAG_FIRMWARE_STATE_CHANGE;
	पूर्ण अन्यथा
		mfiStatus = MFI_INTR_FLAG_REPLY_MESSAGE;

	/*
	 * Clear the पूर्णांकerrupt by writing back the same value
	 */
	ग_लिखोl(status, &regs->outbound_पूर्णांकr_status);

	/*
	 * dummy पढ़ो to flush PCI
	 */
	पढ़ोl(&regs->outbound_पूर्णांकr_status);

	वापस mfiStatus;
पूर्ण

/**
 * megasas_fire_cmd_skinny -	Sends command to the FW
 * @instance:		Adapter soft state
 * @frame_phys_addr:	Physical address of cmd
 * @frame_count:	Number of frames क्रम the command
 * @regs:		MFI रेजिस्टर set
 */
अटल अंतरभूत व्योम
megasas_fire_cmd_skinny(काष्ठा megasas_instance *instance,
			dma_addr_t frame_phys_addr,
			u32 frame_count,
			काष्ठा megasas_रेजिस्टर_set __iomem *regs)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&instance->hba_lock, flags);
	ग_लिखोl(upper_32_bits(frame_phys_addr),
	       &(regs)->inbound_high_queue_port);
	ग_लिखोl((lower_32_bits(frame_phys_addr) | (frame_count<<1))|1,
	       &(regs)->inbound_low_queue_port);
	spin_unlock_irqrestore(&instance->hba_lock, flags);
पूर्ण

/**
 * megasas_check_reset_skinny -	For controller reset check
 * @instance:	Adapter soft state
 * @regs:	MFI रेजिस्टर set
 */
अटल पूर्णांक
megasas_check_reset_skinny(काष्ठा megasas_instance *instance,
				काष्ठा megasas_रेजिस्टर_set __iomem *regs)
अणु
	अगर (atomic_पढ़ो(&instance->adprecovery) != MEGASAS_HBA_OPERATIONAL)
		वापस 1;

	वापस 0;
पूर्ण

अटल काष्ठा megasas_instance_ढाँचा megasas_instance_ढाँचा_skinny = अणु

	.fire_cmd = megasas_fire_cmd_skinny,
	.enable_पूर्णांकr = megasas_enable_पूर्णांकr_skinny,
	.disable_पूर्णांकr = megasas_disable_पूर्णांकr_skinny,
	.clear_पूर्णांकr = megasas_clear_पूर्णांकr_skinny,
	.पढ़ो_fw_status_reg = megasas_पढ़ो_fw_status_reg_skinny,
	.adp_reset = megasas_adp_reset_gen2,
	.check_reset = megasas_check_reset_skinny,
	.service_isr = megasas_isr,
	.tasklet = megasas_complete_cmd_dpc,
	.init_adapter = megasas_init_adapter_mfi,
	.build_and_issue_cmd = megasas_build_and_issue_cmd,
	.issue_dcmd = megasas_issue_dcmd,
पूर्ण;


/*
 * The following functions are defined क्रम gen2 (deviceid : 0x78 0x79)
 * controllers
 */

/**
 * megasas_enable_पूर्णांकr_gen2 -  Enables पूर्णांकerrupts
 * @instance:	Adapter soft state
 */
अटल अंतरभूत व्योम
megasas_enable_पूर्णांकr_gen2(काष्ठा megasas_instance *instance)
अणु
	काष्ठा megasas_रेजिस्टर_set __iomem *regs;

	regs = instance->reg_set;
	ग_लिखोl(0xFFFFFFFF, &(regs)->outbound_करोorbell_clear);

	/* ग_लिखो ~0x00000005 (4 & 1) to the पूर्णांकr mask*/
	ग_लिखोl(~MFI_GEN2_ENABLE_INTERRUPT_MASK, &(regs)->outbound_पूर्णांकr_mask);

	/* Dummy पढ़ोl to क्रमce pci flush */
	पढ़ोl(&regs->outbound_पूर्णांकr_mask);
पूर्ण

/**
 * megasas_disable_पूर्णांकr_gen2 - Disables पूर्णांकerrupt
 * @instance:	Adapter soft state
 */
अटल अंतरभूत व्योम
megasas_disable_पूर्णांकr_gen2(काष्ठा megasas_instance *instance)
अणु
	काष्ठा megasas_रेजिस्टर_set __iomem *regs;
	u32 mask = 0xFFFFFFFF;

	regs = instance->reg_set;
	ग_लिखोl(mask, &regs->outbound_पूर्णांकr_mask);
	/* Dummy पढ़ोl to क्रमce pci flush */
	पढ़ोl(&regs->outbound_पूर्णांकr_mask);
पूर्ण

/**
 * megasas_पढ़ो_fw_status_reg_gen2 - वापसs the current FW status value
 * @instance:	Adapter soft state
 */
अटल u32
megasas_पढ़ो_fw_status_reg_gen2(काष्ठा megasas_instance *instance)
अणु
	वापस पढ़ोl(&instance->reg_set->outbound_scratch_pad_0);
पूर्ण

/**
 * megasas_clear_पूर्णांकr_gen2 -      Check & clear पूर्णांकerrupt
 * @instance:	Adapter soft state
 */
अटल पूर्णांक
megasas_clear_पूर्णांकr_gen2(काष्ठा megasas_instance *instance)
अणु
	u32 status;
	u32 mfiStatus = 0;
	काष्ठा megasas_रेजिस्टर_set __iomem *regs;
	regs = instance->reg_set;

	/*
	 * Check अगर it is our पूर्णांकerrupt
	 */
	status = पढ़ोl(&regs->outbound_पूर्णांकr_status);

	अगर (status & MFI_INTR_FLAG_REPLY_MESSAGE) अणु
		mfiStatus = MFI_INTR_FLAG_REPLY_MESSAGE;
	पूर्ण
	अगर (status & MFI_G2_OUTBOUND_DOORBELL_CHANGE_INTERRUPT) अणु
		mfiStatus |= MFI_INTR_FLAG_FIRMWARE_STATE_CHANGE;
	पूर्ण

	/*
	 * Clear the पूर्णांकerrupt by writing back the same value
	 */
	अगर (mfiStatus)
		ग_लिखोl(status, &regs->outbound_करोorbell_clear);

	/* Dummy पढ़ोl to क्रमce pci flush */
	पढ़ोl(&regs->outbound_पूर्णांकr_status);

	वापस mfiStatus;
पूर्ण

/**
 * megasas_fire_cmd_gen2 -     Sends command to the FW
 * @instance:		Adapter soft state
 * @frame_phys_addr:	Physical address of cmd
 * @frame_count:	Number of frames क्रम the command
 * @regs:		MFI रेजिस्टर set
 */
अटल अंतरभूत व्योम
megasas_fire_cmd_gen2(काष्ठा megasas_instance *instance,
			dma_addr_t frame_phys_addr,
			u32 frame_count,
			काष्ठा megasas_रेजिस्टर_set __iomem *regs)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&instance->hba_lock, flags);
	ग_लिखोl((frame_phys_addr | (frame_count<<1))|1,
			&(regs)->inbound_queue_port);
	spin_unlock_irqrestore(&instance->hba_lock, flags);
पूर्ण

/**
 * megasas_adp_reset_gen2 -	For controller reset
 * @instance:	Adapter soft state
 * @reg_set:	MFI रेजिस्टर set
 */
अटल पूर्णांक
megasas_adp_reset_gen2(काष्ठा megasas_instance *instance,
			काष्ठा megasas_रेजिस्टर_set __iomem *reg_set)
अणु
	u32 retry = 0 ;
	u32 HostDiag;
	u32 __iomem *seq_offset = &reg_set->seq_offset;
	u32 __iomem *hostdiag_offset = &reg_set->host_diag;

	अगर (instance->instancet == &megasas_instance_ढाँचा_skinny) अणु
		seq_offset = &reg_set->fusion_seq_offset;
		hostdiag_offset = &reg_set->fusion_host_diag;
	पूर्ण

	ग_लिखोl(0, seq_offset);
	ग_लिखोl(4, seq_offset);
	ग_लिखोl(0xb, seq_offset);
	ग_लिखोl(2, seq_offset);
	ग_लिखोl(7, seq_offset);
	ग_लिखोl(0xd, seq_offset);

	msleep(1000);

	HostDiag = (u32)पढ़ोl(hostdiag_offset);

	जबतक (!(HostDiag & DIAG_WRITE_ENABLE)) अणु
		msleep(100);
		HostDiag = (u32)पढ़ोl(hostdiag_offset);
		dev_notice(&instance->pdev->dev, "RESETGEN2: retry=%x, hostdiag=%x\n",
					retry, HostDiag);

		अगर (retry++ >= 100)
			वापस 1;

	पूर्ण

	dev_notice(&instance->pdev->dev, "ADP_RESET_GEN2: HostDiag=%x\n", HostDiag);

	ग_लिखोl((HostDiag | DIAG_RESET_ADAPTER), hostdiag_offset);

	ssleep(10);

	HostDiag = (u32)पढ़ोl(hostdiag_offset);
	जबतक (HostDiag & DIAG_RESET_ADAPTER) अणु
		msleep(100);
		HostDiag = (u32)पढ़ोl(hostdiag_offset);
		dev_notice(&instance->pdev->dev, "RESET_GEN2: retry=%x, hostdiag=%x\n",
				retry, HostDiag);

		अगर (retry++ >= 1000)
			वापस 1;

	पूर्ण
	वापस 0;
पूर्ण

/**
 * megasas_check_reset_gen2 -	For controller reset check
 * @instance:	Adapter soft state
 * @regs:	MFI रेजिस्टर set
 */
अटल पूर्णांक
megasas_check_reset_gen2(काष्ठा megasas_instance *instance,
		काष्ठा megasas_रेजिस्टर_set __iomem *regs)
अणु
	अगर (atomic_पढ़ो(&instance->adprecovery) != MEGASAS_HBA_OPERATIONAL)
		वापस 1;

	वापस 0;
पूर्ण

अटल काष्ठा megasas_instance_ढाँचा megasas_instance_ढाँचा_gen2 = अणु

	.fire_cmd = megasas_fire_cmd_gen2,
	.enable_पूर्णांकr = megasas_enable_पूर्णांकr_gen2,
	.disable_पूर्णांकr = megasas_disable_पूर्णांकr_gen2,
	.clear_पूर्णांकr = megasas_clear_पूर्णांकr_gen2,
	.पढ़ो_fw_status_reg = megasas_पढ़ो_fw_status_reg_gen2,
	.adp_reset = megasas_adp_reset_gen2,
	.check_reset = megasas_check_reset_gen2,
	.service_isr = megasas_isr,
	.tasklet = megasas_complete_cmd_dpc,
	.init_adapter = megasas_init_adapter_mfi,
	.build_and_issue_cmd = megasas_build_and_issue_cmd,
	.issue_dcmd = megasas_issue_dcmd,
पूर्ण;

/*
 * This is the end of set of functions & definitions
 * specअगरic to gen2 (deviceid : 0x78, 0x79) controllers
 */

/*
 * Template added क्रम TB (Fusion)
 */
बाह्य काष्ठा megasas_instance_ढाँचा megasas_instance_ढाँचा_fusion;

/**
 * megasas_issue_polled -	Issues a polling command
 * @instance:			Adapter soft state
 * @cmd:			Command packet to be issued
 *
 * For polling, MFI requires the cmd_status to be set to MFI_STAT_INVALID_STATUS beक्रमe posting.
 */
पूर्णांक
megasas_issue_polled(काष्ठा megasas_instance *instance, काष्ठा megasas_cmd *cmd)
अणु
	काष्ठा megasas_header *frame_hdr = &cmd->frame->hdr;

	frame_hdr->cmd_status = MFI_STAT_INVALID_STATUS;
	frame_hdr->flags |= cpu_to_le16(MFI_FRAME_DONT_POST_IN_REPLY_QUEUE);

	अगर (atomic_पढ़ो(&instance->adprecovery) == MEGASAS_HW_CRITICAL_ERROR) अणु
		dev_err(&instance->pdev->dev, "Failed from %s %d\n",
			__func__, __LINE__);
		वापस DCMD_INIT;
	पूर्ण

	instance->instancet->issue_dcmd(instance, cmd);

	वापस रुको_and_poll(instance, cmd, instance->requestorId ?
			MEGASAS_ROUTINE_WAIT_TIME_VF : MFI_IO_TIMEOUT_SECS);
पूर्ण

/**
 * megasas_issue_blocked_cmd -	Synchronous wrapper around regular FW cmds
 * @instance:			Adapter soft state
 * @cmd:			Command to be issued
 * @समयout:			Timeout in seconds
 *
 * This function रुकोs on an event क्रम the command to be वापसed from ISR.
 * Max रुको समय is MEGASAS_INTERNAL_CMD_WAIT_TIME secs
 * Used to issue ioctl commands.
 */
पूर्णांक
megasas_issue_blocked_cmd(काष्ठा megasas_instance *instance,
			  काष्ठा megasas_cmd *cmd, पूर्णांक समयout)
अणु
	पूर्णांक ret = 0;
	cmd->cmd_status_drv = DCMD_INIT;

	अगर (atomic_पढ़ो(&instance->adprecovery) == MEGASAS_HW_CRITICAL_ERROR) अणु
		dev_err(&instance->pdev->dev, "Failed from %s %d\n",
			__func__, __LINE__);
		वापस DCMD_INIT;
	पूर्ण

	instance->instancet->issue_dcmd(instance, cmd);

	अगर (समयout) अणु
		ret = रुको_event_समयout(instance->पूर्णांक_cmd_रुको_q,
		cmd->cmd_status_drv != DCMD_INIT, समयout * HZ);
		अगर (!ret) अणु
			dev_err(&instance->pdev->dev,
				"DCMD(opcode: 0x%x) is timed out, func:%s\n",
				cmd->frame->dcmd.opcode, __func__);
			वापस DCMD_TIMEOUT;
		पूर्ण
	पूर्ण अन्यथा
		रुको_event(instance->पूर्णांक_cmd_रुको_q,
				cmd->cmd_status_drv != DCMD_INIT);

	वापस cmd->cmd_status_drv;
पूर्ण

/**
 * megasas_issue_blocked_पात_cmd -	Aborts previously issued cmd
 * @instance:				Adapter soft state
 * @cmd_to_पात:			Previously issued cmd to be पातed
 * @समयout:				Timeout in seconds
 *
 * MFI firmware can पात previously issued AEN comamnd (स्वतःmatic event
 * notअगरication). The megasas_issue_blocked_पात_cmd() issues such पात
 * cmd and रुकोs क्रम वापस status.
 * Max रुको समय is MEGASAS_INTERNAL_CMD_WAIT_TIME secs
 */
अटल पूर्णांक
megasas_issue_blocked_पात_cmd(काष्ठा megasas_instance *instance,
				काष्ठा megasas_cmd *cmd_to_पात, पूर्णांक समयout)
अणु
	काष्ठा megasas_cmd *cmd;
	काष्ठा megasas_पात_frame *पात_fr;
	पूर्णांक ret = 0;
	u32 opcode;

	cmd = megasas_get_cmd(instance);

	अगर (!cmd)
		वापस -1;

	पात_fr = &cmd->frame->पात;

	/*
	 * Prepare and issue the पात frame
	 */
	पात_fr->cmd = MFI_CMD_ABORT;
	पात_fr->cmd_status = MFI_STAT_INVALID_STATUS;
	पात_fr->flags = cpu_to_le16(0);
	पात_fr->पात_context = cpu_to_le32(cmd_to_पात->index);
	पात_fr->पात_mfi_phys_addr_lo =
		cpu_to_le32(lower_32_bits(cmd_to_पात->frame_phys_addr));
	पात_fr->पात_mfi_phys_addr_hi =
		cpu_to_le32(upper_32_bits(cmd_to_पात->frame_phys_addr));

	cmd->sync_cmd = 1;
	cmd->cmd_status_drv = DCMD_INIT;

	अगर (atomic_पढ़ो(&instance->adprecovery) == MEGASAS_HW_CRITICAL_ERROR) अणु
		dev_err(&instance->pdev->dev, "Failed from %s %d\n",
			__func__, __LINE__);
		वापस DCMD_INIT;
	पूर्ण

	instance->instancet->issue_dcmd(instance, cmd);

	अगर (समयout) अणु
		ret = रुको_event_समयout(instance->पात_cmd_रुको_q,
		cmd->cmd_status_drv != DCMD_INIT, समयout * HZ);
		अगर (!ret) अणु
			opcode = cmd_to_पात->frame->dcmd.opcode;
			dev_err(&instance->pdev->dev,
				"Abort(to be aborted DCMD opcode: 0x%x) is timed out func:%s\n",
				opcode,  __func__);
			वापस DCMD_TIMEOUT;
		पूर्ण
	पूर्ण अन्यथा
		रुको_event(instance->पात_cmd_रुको_q,
		cmd->cmd_status_drv != DCMD_INIT);

	cmd->sync_cmd = 0;

	megasas_वापस_cmd(instance, cmd);
	वापस cmd->cmd_status_drv;
पूर्ण

/**
 * megasas_make_sgl32 -	Prepares 32-bit SGL
 * @instance:		Adapter soft state
 * @scp:		SCSI command from the mid-layer
 * @mfi_sgl:		SGL to be filled in
 *
 * If successful, this function वापसs the number of SG elements. Otherwise,
 * it वापसes -1.
 */
अटल पूर्णांक
megasas_make_sgl32(काष्ठा megasas_instance *instance, काष्ठा scsi_cmnd *scp,
		   जोड़ megasas_sgl *mfi_sgl)
अणु
	पूर्णांक i;
	पूर्णांक sge_count;
	काष्ठा scatterlist *os_sgl;

	sge_count = scsi_dma_map(scp);
	BUG_ON(sge_count < 0);

	अगर (sge_count) अणु
		scsi_क्रम_each_sg(scp, os_sgl, sge_count, i) अणु
			mfi_sgl->sge32[i].length = cpu_to_le32(sg_dma_len(os_sgl));
			mfi_sgl->sge32[i].phys_addr = cpu_to_le32(sg_dma_address(os_sgl));
		पूर्ण
	पूर्ण
	वापस sge_count;
पूर्ण

/**
 * megasas_make_sgl64 -	Prepares 64-bit SGL
 * @instance:		Adapter soft state
 * @scp:		SCSI command from the mid-layer
 * @mfi_sgl:		SGL to be filled in
 *
 * If successful, this function वापसs the number of SG elements. Otherwise,
 * it वापसes -1.
 */
अटल पूर्णांक
megasas_make_sgl64(काष्ठा megasas_instance *instance, काष्ठा scsi_cmnd *scp,
		   जोड़ megasas_sgl *mfi_sgl)
अणु
	पूर्णांक i;
	पूर्णांक sge_count;
	काष्ठा scatterlist *os_sgl;

	sge_count = scsi_dma_map(scp);
	BUG_ON(sge_count < 0);

	अगर (sge_count) अणु
		scsi_क्रम_each_sg(scp, os_sgl, sge_count, i) अणु
			mfi_sgl->sge64[i].length = cpu_to_le32(sg_dma_len(os_sgl));
			mfi_sgl->sge64[i].phys_addr = cpu_to_le64(sg_dma_address(os_sgl));
		पूर्ण
	पूर्ण
	वापस sge_count;
पूर्ण

/**
 * megasas_make_sgl_skinny - Prepares IEEE SGL
 * @instance:           Adapter soft state
 * @scp:                SCSI command from the mid-layer
 * @mfi_sgl:            SGL to be filled in
 *
 * If successful, this function वापसs the number of SG elements. Otherwise,
 * it वापसes -1.
 */
अटल पूर्णांक
megasas_make_sgl_skinny(काष्ठा megasas_instance *instance,
		काष्ठा scsi_cmnd *scp, जोड़ megasas_sgl *mfi_sgl)
अणु
	पूर्णांक i;
	पूर्णांक sge_count;
	काष्ठा scatterlist *os_sgl;

	sge_count = scsi_dma_map(scp);

	अगर (sge_count) अणु
		scsi_क्रम_each_sg(scp, os_sgl, sge_count, i) अणु
			mfi_sgl->sge_skinny[i].length =
				cpu_to_le32(sg_dma_len(os_sgl));
			mfi_sgl->sge_skinny[i].phys_addr =
				cpu_to_le64(sg_dma_address(os_sgl));
			mfi_sgl->sge_skinny[i].flag = cpu_to_le32(0);
		पूर्ण
	पूर्ण
	वापस sge_count;
पूर्ण

 /**
 * megasas_get_frame_count - Computes the number of frames
 * @frame_type		: type of frame- io or pthru frame
 * @sge_count		: number of sg elements
 *
 * Returns the number of frames required क्रम numnber of sge's (sge_count)
 */

अटल u32 megasas_get_frame_count(काष्ठा megasas_instance *instance,
			u8 sge_count, u8 frame_type)
अणु
	पूर्णांक num_cnt;
	पूर्णांक sge_bytes;
	u32 sge_sz;
	u32 frame_count = 0;

	sge_sz = (IS_DMA64) ? माप(काष्ठा megasas_sge64) :
	    माप(काष्ठा megasas_sge32);

	अगर (instance->flag_ieee) अणु
		sge_sz = माप(काष्ठा megasas_sge_skinny);
	पूर्ण

	/*
	 * Main frame can contain 2 SGEs क्रम 64-bit SGLs and
	 * 3 SGEs क्रम 32-bit SGLs क्रम ldio &
	 * 1 SGEs क्रम 64-bit SGLs and
	 * 2 SGEs क्रम 32-bit SGLs क्रम pthru frame
	 */
	अगर (unlikely(frame_type == PTHRU_FRAME)) अणु
		अगर (instance->flag_ieee == 1) अणु
			num_cnt = sge_count - 1;
		पूर्ण अन्यथा अगर (IS_DMA64)
			num_cnt = sge_count - 1;
		अन्यथा
			num_cnt = sge_count - 2;
	पूर्ण अन्यथा अणु
		अगर (instance->flag_ieee == 1) अणु
			num_cnt = sge_count - 1;
		पूर्ण अन्यथा अगर (IS_DMA64)
			num_cnt = sge_count - 2;
		अन्यथा
			num_cnt = sge_count - 3;
	पूर्ण

	अगर (num_cnt > 0) अणु
		sge_bytes = sge_sz * num_cnt;

		frame_count = (sge_bytes / MEGAMFI_FRAME_SIZE) +
		    ((sge_bytes % MEGAMFI_FRAME_SIZE) ? 1 : 0) ;
	पूर्ण
	/* Main frame */
	frame_count += 1;

	अगर (frame_count > 7)
		frame_count = 8;
	वापस frame_count;
पूर्ण

/**
 * megasas_build_dcdb -	Prepares a direct cdb (DCDB) command
 * @instance:		Adapter soft state
 * @scp:		SCSI command
 * @cmd:		Command to be prepared in
 *
 * This function prepares CDB commands. These are typcially pass-through
 * commands to the devices.
 */
अटल पूर्णांक
megasas_build_dcdb(काष्ठा megasas_instance *instance, काष्ठा scsi_cmnd *scp,
		   काष्ठा megasas_cmd *cmd)
अणु
	u32 is_logical;
	u32 device_id;
	u16 flags = 0;
	काष्ठा megasas_pthru_frame *pthru;

	is_logical = MEGASAS_IS_LOGICAL(scp->device);
	device_id = MEGASAS_DEV_INDEX(scp);
	pthru = (काष्ठा megasas_pthru_frame *)cmd->frame;

	अगर (scp->sc_data_direction == DMA_TO_DEVICE)
		flags = MFI_FRAME_सूची_WRITE;
	अन्यथा अगर (scp->sc_data_direction == DMA_FROM_DEVICE)
		flags = MFI_FRAME_सूची_READ;
	अन्यथा अगर (scp->sc_data_direction == DMA_NONE)
		flags = MFI_FRAME_सूची_NONE;

	अगर (instance->flag_ieee == 1) अणु
		flags |= MFI_FRAME_IEEE;
	पूर्ण

	/*
	 * Prepare the DCDB frame
	 */
	pthru->cmd = (is_logical) ? MFI_CMD_LD_SCSI_IO : MFI_CMD_PD_SCSI_IO;
	pthru->cmd_status = 0x0;
	pthru->scsi_status = 0x0;
	pthru->target_id = device_id;
	pthru->lun = scp->device->lun;
	pthru->cdb_len = scp->cmd_len;
	pthru->समयout = 0;
	pthru->pad_0 = 0;
	pthru->flags = cpu_to_le16(flags);
	pthru->data_xfer_len = cpu_to_le32(scsi_bufflen(scp));

	स_नकल(pthru->cdb, scp->cmnd, scp->cmd_len);

	/*
	 * If the command is क्रम the tape device, set the
	 * pthru समयout to the os layer समयout value.
	 */
	अगर (scp->device->type == TYPE_TAPE) अणु
		अगर ((scp->request->समयout / HZ) > 0xFFFF)
			pthru->समयout = cpu_to_le16(0xFFFF);
		अन्यथा
			pthru->समयout = cpu_to_le16(scp->request->समयout / HZ);
	पूर्ण

	/*
	 * Conकाष्ठा SGL
	 */
	अगर (instance->flag_ieee == 1) अणु
		pthru->flags |= cpu_to_le16(MFI_FRAME_SGL64);
		pthru->sge_count = megasas_make_sgl_skinny(instance, scp,
						      &pthru->sgl);
	पूर्ण अन्यथा अगर (IS_DMA64) अणु
		pthru->flags |= cpu_to_le16(MFI_FRAME_SGL64);
		pthru->sge_count = megasas_make_sgl64(instance, scp,
						      &pthru->sgl);
	पूर्ण अन्यथा
		pthru->sge_count = megasas_make_sgl32(instance, scp,
						      &pthru->sgl);

	अगर (pthru->sge_count > instance->max_num_sge) अणु
		dev_err(&instance->pdev->dev, "DCDB too many SGE NUM=%x\n",
			pthru->sge_count);
		वापस 0;
	पूर्ण

	/*
	 * Sense info specअगरic
	 */
	pthru->sense_len = SCSI_SENSE_BUFFERSIZE;
	pthru->sense_buf_phys_addr_hi =
		cpu_to_le32(upper_32_bits(cmd->sense_phys_addr));
	pthru->sense_buf_phys_addr_lo =
		cpu_to_le32(lower_32_bits(cmd->sense_phys_addr));

	/*
	 * Compute the total number of frames this command consumes. FW uses
	 * this number to pull sufficient number of frames from host memory.
	 */
	cmd->frame_count = megasas_get_frame_count(instance, pthru->sge_count,
							PTHRU_FRAME);

	वापस cmd->frame_count;
पूर्ण

/**
 * megasas_build_ldio -	Prepares IOs to logical devices
 * @instance:		Adapter soft state
 * @scp:		SCSI command
 * @cmd:		Command to be prepared
 *
 * Frames (and accompanying SGLs) क्रम regular SCSI IOs use this function.
 */
अटल पूर्णांक
megasas_build_ldio(काष्ठा megasas_instance *instance, काष्ठा scsi_cmnd *scp,
		   काष्ठा megasas_cmd *cmd)
अणु
	u32 device_id;
	u8 sc = scp->cmnd[0];
	u16 flags = 0;
	काष्ठा megasas_io_frame *ldio;

	device_id = MEGASAS_DEV_INDEX(scp);
	ldio = (काष्ठा megasas_io_frame *)cmd->frame;

	अगर (scp->sc_data_direction == DMA_TO_DEVICE)
		flags = MFI_FRAME_सूची_WRITE;
	अन्यथा अगर (scp->sc_data_direction == DMA_FROM_DEVICE)
		flags = MFI_FRAME_सूची_READ;

	अगर (instance->flag_ieee == 1) अणु
		flags |= MFI_FRAME_IEEE;
	पूर्ण

	/*
	 * Prepare the Logical IO frame: 2nd bit is zero क्रम all पढ़ो cmds
	 */
	ldio->cmd = (sc & 0x02) ? MFI_CMD_LD_WRITE : MFI_CMD_LD_READ;
	ldio->cmd_status = 0x0;
	ldio->scsi_status = 0x0;
	ldio->target_id = device_id;
	ldio->समयout = 0;
	ldio->reserved_0 = 0;
	ldio->pad_0 = 0;
	ldio->flags = cpu_to_le16(flags);
	ldio->start_lba_hi = 0;
	ldio->access_byte = (scp->cmd_len != 6) ? scp->cmnd[1] : 0;

	/*
	 * 6-byte READ(0x08) or WRITE(0x0A) cdb
	 */
	अगर (scp->cmd_len == 6) अणु
		ldio->lba_count = cpu_to_le32((u32) scp->cmnd[4]);
		ldio->start_lba_lo = cpu_to_le32(((u32) scp->cmnd[1] << 16) |
						 ((u32) scp->cmnd[2] << 8) |
						 (u32) scp->cmnd[3]);

		ldio->start_lba_lo &= cpu_to_le32(0x1FFFFF);
	पूर्ण

	/*
	 * 10-byte READ(0x28) or WRITE(0x2A) cdb
	 */
	अन्यथा अगर (scp->cmd_len == 10) अणु
		ldio->lba_count = cpu_to_le32((u32) scp->cmnd[8] |
					      ((u32) scp->cmnd[7] << 8));
		ldio->start_lba_lo = cpu_to_le32(((u32) scp->cmnd[2] << 24) |
						 ((u32) scp->cmnd[3] << 16) |
						 ((u32) scp->cmnd[4] << 8) |
						 (u32) scp->cmnd[5]);
	पूर्ण

	/*
	 * 12-byte READ(0xA8) or WRITE(0xAA) cdb
	 */
	अन्यथा अगर (scp->cmd_len == 12) अणु
		ldio->lba_count = cpu_to_le32(((u32) scp->cmnd[6] << 24) |
					      ((u32) scp->cmnd[7] << 16) |
					      ((u32) scp->cmnd[8] << 8) |
					      (u32) scp->cmnd[9]);

		ldio->start_lba_lo = cpu_to_le32(((u32) scp->cmnd[2] << 24) |
						 ((u32) scp->cmnd[3] << 16) |
						 ((u32) scp->cmnd[4] << 8) |
						 (u32) scp->cmnd[5]);
	पूर्ण

	/*
	 * 16-byte READ(0x88) or WRITE(0x8A) cdb
	 */
	अन्यथा अगर (scp->cmd_len == 16) अणु
		ldio->lba_count = cpu_to_le32(((u32) scp->cmnd[10] << 24) |
					      ((u32) scp->cmnd[11] << 16) |
					      ((u32) scp->cmnd[12] << 8) |
					      (u32) scp->cmnd[13]);

		ldio->start_lba_lo = cpu_to_le32(((u32) scp->cmnd[6] << 24) |
						 ((u32) scp->cmnd[7] << 16) |
						 ((u32) scp->cmnd[8] << 8) |
						 (u32) scp->cmnd[9]);

		ldio->start_lba_hi = cpu_to_le32(((u32) scp->cmnd[2] << 24) |
						 ((u32) scp->cmnd[3] << 16) |
						 ((u32) scp->cmnd[4] << 8) |
						 (u32) scp->cmnd[5]);

	पूर्ण

	/*
	 * Conकाष्ठा SGL
	 */
	अगर (instance->flag_ieee) अणु
		ldio->flags |= cpu_to_le16(MFI_FRAME_SGL64);
		ldio->sge_count = megasas_make_sgl_skinny(instance, scp,
					      &ldio->sgl);
	पूर्ण अन्यथा अगर (IS_DMA64) अणु
		ldio->flags |= cpu_to_le16(MFI_FRAME_SGL64);
		ldio->sge_count = megasas_make_sgl64(instance, scp, &ldio->sgl);
	पूर्ण अन्यथा
		ldio->sge_count = megasas_make_sgl32(instance, scp, &ldio->sgl);

	अगर (ldio->sge_count > instance->max_num_sge) अणु
		dev_err(&instance->pdev->dev, "build_ld_io: sge_count = %x\n",
			ldio->sge_count);
		वापस 0;
	पूर्ण

	/*
	 * Sense info specअगरic
	 */
	ldio->sense_len = SCSI_SENSE_BUFFERSIZE;
	ldio->sense_buf_phys_addr_hi = 0;
	ldio->sense_buf_phys_addr_lo = cpu_to_le32(cmd->sense_phys_addr);

	/*
	 * Compute the total number of frames this command consumes. FW uses
	 * this number to pull sufficient number of frames from host memory.
	 */
	cmd->frame_count = megasas_get_frame_count(instance,
			ldio->sge_count, IO_FRAME);

	वापस cmd->frame_count;
पूर्ण

/**
 * megasas_cmd_type -		Checks अगर the cmd is क्रम logical drive/sysPD
 *				and whether it's RW or non RW
 * @cmd:			SCSI command
 *
 */
अंतरभूत पूर्णांक megasas_cmd_type(काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक ret;

	चयन (cmd->cmnd[0]) अणु
	हाल READ_10:
	हाल WRITE_10:
	हाल READ_12:
	हाल WRITE_12:
	हाल READ_6:
	हाल WRITE_6:
	हाल READ_16:
	हाल WRITE_16:
		ret = (MEGASAS_IS_LOGICAL(cmd->device)) ?
			READ_WRITE_LDIO : READ_WRITE_SYSPDIO;
		अवरोध;
	शेष:
		ret = (MEGASAS_IS_LOGICAL(cmd->device)) ?
			NON_READ_WRITE_LDIO : NON_READ_WRITE_SYSPDIO;
	पूर्ण
	वापस ret;
पूर्ण

 /**
 * megasas_dump_pending_frames -	Dumps the frame address of all pending cmds
 *					in FW
 * @instance:				Adapter soft state
 */
अटल अंतरभूत व्योम
megasas_dump_pending_frames(काष्ठा megasas_instance *instance)
अणु
	काष्ठा megasas_cmd *cmd;
	पूर्णांक i,n;
	जोड़ megasas_sgl *mfi_sgl;
	काष्ठा megasas_io_frame *ldio;
	काष्ठा megasas_pthru_frame *pthru;
	u32 sgcount;
	u16 max_cmd = instance->max_fw_cmds;

	dev_err(&instance->pdev->dev, "[%d]: Dumping Frame Phys Address of all pending cmds in FW\n",instance->host->host_no);
	dev_err(&instance->pdev->dev, "[%d]: Total OS Pending cmds : %d\n",instance->host->host_no,atomic_पढ़ो(&instance->fw_outstanding));
	अगर (IS_DMA64)
		dev_err(&instance->pdev->dev, "[%d]: 64 bit SGLs were sent to FW\n",instance->host->host_no);
	अन्यथा
		dev_err(&instance->pdev->dev, "[%d]: 32 bit SGLs were sent to FW\n",instance->host->host_no);

	dev_err(&instance->pdev->dev, "[%d]: Pending OS cmds in FW : \n",instance->host->host_no);
	क्रम (i = 0; i < max_cmd; i++) अणु
		cmd = instance->cmd_list[i];
		अगर (!cmd->scmd)
			जारी;
		dev_err(&instance->pdev->dev, "[%d]: Frame addr :0x%08lx : ",instance->host->host_no,(अचिन्हित दीर्घ)cmd->frame_phys_addr);
		अगर (megasas_cmd_type(cmd->scmd) == READ_WRITE_LDIO) अणु
			ldio = (काष्ठा megasas_io_frame *)cmd->frame;
			mfi_sgl = &ldio->sgl;
			sgcount = ldio->sge_count;
			dev_err(&instance->pdev->dev, "[%d]: frame count : 0x%x, Cmd : 0x%x, Tgt id : 0x%x,"
			" lba lo : 0x%x, lba_hi : 0x%x, sense_buf addr : 0x%x,sge count : 0x%x\n",
			instance->host->host_no, cmd->frame_count, ldio->cmd, ldio->target_id,
			le32_to_cpu(ldio->start_lba_lo), le32_to_cpu(ldio->start_lba_hi),
			le32_to_cpu(ldio->sense_buf_phys_addr_lo), sgcount);
		पूर्ण अन्यथा अणु
			pthru = (काष्ठा megasas_pthru_frame *) cmd->frame;
			mfi_sgl = &pthru->sgl;
			sgcount = pthru->sge_count;
			dev_err(&instance->pdev->dev, "[%d]: frame count : 0x%x, Cmd : 0x%x, Tgt id : 0x%x, "
			"lun : 0x%x, cdb_len : 0x%x, data xfer len : 0x%x, sense_buf addr : 0x%x,sge count : 0x%x\n",
			instance->host->host_no, cmd->frame_count, pthru->cmd, pthru->target_id,
			pthru->lun, pthru->cdb_len, le32_to_cpu(pthru->data_xfer_len),
			le32_to_cpu(pthru->sense_buf_phys_addr_lo), sgcount);
		पूर्ण
		अगर (megasas_dbg_lvl & MEGASAS_DBG_LVL) अणु
			क्रम (n = 0; n < sgcount; n++) अणु
				अगर (IS_DMA64)
					dev_err(&instance->pdev->dev, "sgl len : 0x%x, sgl addr : 0x%llx\n",
						le32_to_cpu(mfi_sgl->sge64[n].length),
						le64_to_cpu(mfi_sgl->sge64[n].phys_addr));
				अन्यथा
					dev_err(&instance->pdev->dev, "sgl len : 0x%x, sgl addr : 0x%x\n",
						le32_to_cpu(mfi_sgl->sge32[n].length),
						le32_to_cpu(mfi_sgl->sge32[n].phys_addr));
			पूर्ण
		पूर्ण
	पूर्ण /*क्रम max_cmd*/
	dev_err(&instance->pdev->dev, "[%d]: Pending Internal cmds in FW : \n",instance->host->host_no);
	क्रम (i = 0; i < max_cmd; i++) अणु

		cmd = instance->cmd_list[i];

		अगर (cmd->sync_cmd == 1)
			dev_err(&instance->pdev->dev, "0x%08lx : ", (अचिन्हित दीर्घ)cmd->frame_phys_addr);
	पूर्ण
	dev_err(&instance->pdev->dev, "[%d]: Dumping Done\n\n",instance->host->host_no);
पूर्ण

u32
megasas_build_and_issue_cmd(काष्ठा megasas_instance *instance,
			    काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा megasas_cmd *cmd;
	u32 frame_count;

	cmd = megasas_get_cmd(instance);
	अगर (!cmd)
		वापस SCSI_MLQUEUE_HOST_BUSY;

	/*
	 * Logical drive command
	 */
	अगर (megasas_cmd_type(scmd) == READ_WRITE_LDIO)
		frame_count = megasas_build_ldio(instance, scmd, cmd);
	अन्यथा
		frame_count = megasas_build_dcdb(instance, scmd, cmd);

	अगर (!frame_count)
		जाओ out_वापस_cmd;

	cmd->scmd = scmd;
	scmd->SCp.ptr = (अक्षर *)cmd;

	/*
	 * Issue the command to the FW
	 */
	atomic_inc(&instance->fw_outstanding);

	instance->instancet->fire_cmd(instance, cmd->frame_phys_addr,
				cmd->frame_count-1, instance->reg_set);

	वापस 0;
out_वापस_cmd:
	megasas_वापस_cmd(instance, cmd);
	वापस SCSI_MLQUEUE_HOST_BUSY;
पूर्ण


/**
 * megasas_queue_command -	Queue entry poपूर्णांक
 * @shost:			adapter SCSI host
 * @scmd:			SCSI command to be queued
 */
अटल पूर्णांक
megasas_queue_command(काष्ठा Scsi_Host *shost, काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा megasas_instance *instance;
	काष्ठा MR_PRIV_DEVICE *mr_device_priv_data;

	instance = (काष्ठा megasas_instance *)
	    scmd->device->host->hostdata;

	अगर (instance->unload == 1) अणु
		scmd->result = DID_NO_CONNECT << 16;
		scmd->scsi_करोne(scmd);
		वापस 0;
	पूर्ण

	अगर (instance->issuepend_करोne == 0)
		वापस SCSI_MLQUEUE_HOST_BUSY;


	/* Check क्रम an mpio path and adjust behavior */
	अगर (atomic_पढ़ो(&instance->adprecovery) == MEGASAS_ADPRESET_SM_INFAULT) अणु
		अगर (megasas_check_mpio_paths(instance, scmd) ==
		    (DID_REQUEUE << 16)) अणु
			वापस SCSI_MLQUEUE_HOST_BUSY;
		पूर्ण अन्यथा अणु
			scmd->result = DID_NO_CONNECT << 16;
			scmd->scsi_करोne(scmd);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (atomic_पढ़ो(&instance->adprecovery) == MEGASAS_HW_CRITICAL_ERROR) अणु
		scmd->result = DID_NO_CONNECT << 16;
		scmd->scsi_करोne(scmd);
		वापस 0;
	पूर्ण

	mr_device_priv_data = scmd->device->hostdata;
	अगर (!mr_device_priv_data) अणु
		scmd->result = DID_NO_CONNECT << 16;
		scmd->scsi_करोne(scmd);
		वापस 0;
	पूर्ण

	अगर (atomic_पढ़ो(&instance->adprecovery) != MEGASAS_HBA_OPERATIONAL)
		वापस SCSI_MLQUEUE_HOST_BUSY;

	अगर (mr_device_priv_data->पंचांग_busy)
		वापस SCSI_MLQUEUE_DEVICE_BUSY;


	scmd->result = 0;

	अगर (MEGASAS_IS_LOGICAL(scmd->device) &&
	    (scmd->device->id >= instance->fw_supported_vd_count ||
		scmd->device->lun)) अणु
		scmd->result = DID_BAD_TARGET << 16;
		जाओ out_करोne;
	पूर्ण

	अगर ((scmd->cmnd[0] == SYNCHRONIZE_CACHE) &&
	    MEGASAS_IS_LOGICAL(scmd->device) &&
	    (!instance->fw_sync_cache_support)) अणु
		scmd->result = DID_OK << 16;
		जाओ out_करोne;
	पूर्ण

	वापस instance->instancet->build_and_issue_cmd(instance, scmd);

 out_करोne:
	scmd->scsi_करोne(scmd);
	वापस 0;
पूर्ण

अटल काष्ठा megasas_instance *megasas_lookup_instance(u16 host_no)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < megasas_mgmt_info.max_index; i++) अणु

		अगर ((megasas_mgmt_info.instance[i]) &&
		    (megasas_mgmt_info.instance[i]->host->host_no == host_no))
			वापस megasas_mgmt_info.instance[i];
	पूर्ण

	वापस शून्य;
पूर्ण

/*
* megasas_set_dynamic_target_properties -
* Device property set by driver may not be अटल and it is required to be
* updated after OCR
*
* set पंचांग_capable.
* set dma alignment (only क्रम eedp protection enable vd).
*
* @sdev: OS provided scsi device
*
* Returns व्योम
*/
व्योम megasas_set_dynamic_target_properties(काष्ठा scsi_device *sdev,
					   bool is_target_prop)
अणु
	u16 pd_index = 0, ld;
	u32 device_id;
	काष्ठा megasas_instance *instance;
	काष्ठा fusion_context *fusion;
	काष्ठा MR_PRIV_DEVICE *mr_device_priv_data;
	काष्ठा MR_PD_CFG_SEQ_NUM_SYNC *pd_sync;
	काष्ठा MR_LD_RAID *raid;
	काष्ठा MR_DRV_RAID_MAP_ALL *local_map_ptr;

	instance = megasas_lookup_instance(sdev->host->host_no);
	fusion = instance->ctrl_context;
	mr_device_priv_data = sdev->hostdata;

	अगर (!fusion || !mr_device_priv_data)
		वापस;

	अगर (MEGASAS_IS_LOGICAL(sdev)) अणु
		device_id = ((sdev->channel % 2) * MEGASAS_MAX_DEV_PER_CHANNEL)
					+ sdev->id;
		local_map_ptr = fusion->ld_drv_map[(instance->map_id & 1)];
		ld = MR_TargetIdToLdGet(device_id, local_map_ptr);
		अगर (ld >= instance->fw_supported_vd_count)
			वापस;
		raid = MR_LdRaidGet(ld, local_map_ptr);

		अगर (raid->capability.ldPiMode == MR_PROT_INFO_TYPE_CONTROLLER)
		blk_queue_update_dma_alignment(sdev->request_queue, 0x7);

		mr_device_priv_data->is_पंचांग_capable =
			raid->capability.पंचांगCapable;

		अगर (!raid->flags.isEPD)
			sdev->no_ग_लिखो_same = 1;

	पूर्ण अन्यथा अगर (instance->use_seqnum_jbod_fp) अणु
		pd_index = (sdev->channel * MEGASAS_MAX_DEV_PER_CHANNEL) +
			sdev->id;
		pd_sync = (व्योम *)fusion->pd_seq_sync
				[(instance->pd_seq_map_id - 1) & 1];
		mr_device_priv_data->is_पंचांग_capable =
			pd_sync->seq[pd_index].capability.पंचांगCapable;
	पूर्ण

	अगर (is_target_prop && instance->tgt_prop->reset_पंचांगo) अणु
		/*
		 * If FW provides a target reset समयout value, driver will use
		 * it. If not set, fallback to शेष values.
		 */
		mr_device_priv_data->target_reset_पंचांगo =
			min_t(u8, instance->max_reset_पंचांगo,
			      instance->tgt_prop->reset_पंचांगo);
		mr_device_priv_data->task_पात_पंचांगo = instance->task_पात_पंचांगo;
	पूर्ण अन्यथा अणु
		mr_device_priv_data->target_reset_पंचांगo =
						MEGASAS_DEFAULT_TM_TIMEOUT;
		mr_device_priv_data->task_पात_पंचांगo =
						MEGASAS_DEFAULT_TM_TIMEOUT;
	पूर्ण
पूर्ण

/*
 * megasas_set_nvme_device_properties -
 * set nomerges=2
 * set भव page boundary = 4K (current mr_nvme_pg_size is 4K).
 * set maximum io transfer = MDTS of NVME device provided by MR firmware.
 *
 * MR firmware provides value in KB. Caller of this function converts
 * kb पूर्णांकo bytes.
 *
 * e.a MDTS=5 means 2^5 * nvme page size. (In हाल of 4K page size,
 * MR firmware provides value 128 as (32 * 4K) = 128K.
 *
 * @sdev:				scsi device
 * @max_io_size:				maximum io transfer size
 *
 */
अटल अंतरभूत व्योम
megasas_set_nvme_device_properties(काष्ठा scsi_device *sdev, u32 max_io_size)
अणु
	काष्ठा megasas_instance *instance;
	u32 mr_nvme_pg_size;

	instance = (काष्ठा megasas_instance *)sdev->host->hostdata;
	mr_nvme_pg_size = max_t(u32, instance->nvme_page_size,
				MR_DEFAULT_NVME_PAGE_SIZE);

	blk_queue_max_hw_sectors(sdev->request_queue, (max_io_size / 512));

	blk_queue_flag_set(QUEUE_FLAG_NOMERGES, sdev->request_queue);
	blk_queue_virt_boundary(sdev->request_queue, mr_nvme_pg_size - 1);
पूर्ण

/*
 * megasas_set_fw_assisted_qd -
 * set device queue depth to can_queue
 * set device queue depth to fw assisted qd
 *
 * @sdev:				scsi device
 * @is_target_prop			true, अगर fw provided target properties.
 */
अटल व्योम megasas_set_fw_assisted_qd(काष्ठा scsi_device *sdev,
						 bool is_target_prop)
अणु
	u8 पूर्णांकerface_type;
	u32 device_qd = MEGASAS_DEFAULT_CMD_PER_LUN;
	u32 tgt_device_qd;
	काष्ठा megasas_instance *instance;
	काष्ठा MR_PRIV_DEVICE *mr_device_priv_data;

	instance = megasas_lookup_instance(sdev->host->host_no);
	mr_device_priv_data = sdev->hostdata;
	पूर्णांकerface_type  = mr_device_priv_data->पूर्णांकerface_type;

	चयन (पूर्णांकerface_type) अणु
	हाल SAS_PD:
		device_qd = MEGASAS_SAS_QD;
		अवरोध;
	हाल SATA_PD:
		device_qd = MEGASAS_SATA_QD;
		अवरोध;
	हाल NVME_PD:
		device_qd = MEGASAS_NVME_QD;
		अवरोध;
	पूर्ण

	अगर (is_target_prop) अणु
		tgt_device_qd = le32_to_cpu(instance->tgt_prop->device_qdepth);
		अगर (tgt_device_qd)
			device_qd = min(instance->host->can_queue,
					(पूर्णांक)tgt_device_qd);
	पूर्ण

	अगर (instance->enable_sdev_max_qd && पूर्णांकerface_type != UNKNOWN_DRIVE)
		device_qd = instance->host->can_queue;

	scsi_change_queue_depth(sdev, device_qd);
पूर्ण

/*
 * megasas_set_अटल_target_properties -
 * Device property set by driver are अटल and it is not required to be
 * updated after OCR.
 *
 * set io समयout
 * set device queue depth
 * set nvme device properties. see - megasas_set_nvme_device_properties
 *
 * @sdev:				scsi device
 * @is_target_prop			true, अगर fw provided target properties.
 */
अटल व्योम megasas_set_अटल_target_properties(काष्ठा scsi_device *sdev,
						 bool is_target_prop)
अणु
	u32 max_io_size_kb = MR_DEFAULT_NVME_MDTS_KB;
	काष्ठा megasas_instance *instance;

	instance = megasas_lookup_instance(sdev->host->host_no);

	/*
	 * The RAID firmware may require extended समयouts.
	 */
	blk_queue_rq_समयout(sdev->request_queue, scmd_समयout * HZ);

	/* max_io_size_kb will be set to non zero क्रम
	 * nvme based vd and syspd.
	 */
	अगर (is_target_prop)
		max_io_size_kb = le32_to_cpu(instance->tgt_prop->max_io_size_kb);

	अगर (instance->nvme_page_size && max_io_size_kb)
		megasas_set_nvme_device_properties(sdev, (max_io_size_kb << 10));

	megasas_set_fw_assisted_qd(sdev, is_target_prop);
पूर्ण


अटल पूर्णांक megasas_slave_configure(काष्ठा scsi_device *sdev)
अणु
	u16 pd_index = 0;
	काष्ठा megasas_instance *instance;
	पूर्णांक ret_target_prop = DCMD_FAILED;
	bool is_target_prop = false;

	instance = megasas_lookup_instance(sdev->host->host_no);
	अगर (instance->pd_list_not_supported) अणु
		अगर (!MEGASAS_IS_LOGICAL(sdev) && sdev->type == TYPE_DISK) अणु
			pd_index = (sdev->channel * MEGASAS_MAX_DEV_PER_CHANNEL) +
				sdev->id;
			अगर (instance->pd_list[pd_index].driveState !=
				MR_PD_STATE_SYSTEM)
				वापस -ENXIO;
		पूर्ण
	पूर्ण

	mutex_lock(&instance->reset_mutex);
	/* Send DCMD to Firmware and cache the inक्रमmation */
	अगर ((instance->pd_info) && !MEGASAS_IS_LOGICAL(sdev))
		megasas_get_pd_info(instance, sdev);

	/* Some ventura firmware may not have instance->nvme_page_size set.
	 * Do not send MR_DCMD_DRV_GET_TARGET_PROP
	 */
	अगर ((instance->tgt_prop) && (instance->nvme_page_size))
		ret_target_prop = megasas_get_target_prop(instance, sdev);

	is_target_prop = (ret_target_prop == DCMD_SUCCESS) ? true : false;
	megasas_set_अटल_target_properties(sdev, is_target_prop);

	/* This sdev property may change post OCR */
	megasas_set_dynamic_target_properties(sdev, is_target_prop);

	mutex_unlock(&instance->reset_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक megasas_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	u16 pd_index = 0;
	काष्ठा megasas_instance *instance ;
	काष्ठा MR_PRIV_DEVICE *mr_device_priv_data;

	instance = megasas_lookup_instance(sdev->host->host_no);
	अगर (!MEGASAS_IS_LOGICAL(sdev)) अणु
		/*
		 * Open the OS scan to the SYSTEM PD
		 */
		pd_index =
			(sdev->channel * MEGASAS_MAX_DEV_PER_CHANNEL) +
			sdev->id;
		अगर ((instance->pd_list_not_supported ||
			instance->pd_list[pd_index].driveState ==
			MR_PD_STATE_SYSTEM)) अणु
			जाओ scan_target;
		पूर्ण
		वापस -ENXIO;
	पूर्ण

scan_target:
	mr_device_priv_data = kzalloc(माप(*mr_device_priv_data),
					GFP_KERNEL);
	अगर (!mr_device_priv_data)
		वापस -ENOMEM;
	sdev->hostdata = mr_device_priv_data;

	atomic_set(&mr_device_priv_data->r1_ldio_hपूर्णांक,
		   instance->r1_ldio_hपूर्णांक_शेष);
	वापस 0;
पूर्ण

अटल व्योम megasas_slave_destroy(काष्ठा scsi_device *sdev)
अणु
	kमुक्त(sdev->hostdata);
	sdev->hostdata = शून्य;
पूर्ण

/*
* megasas_complete_outstanding_ioctls - Complete outstanding ioctls after a
*                                       समाप्त adapter
* @instance:				Adapter soft state
*
*/
अटल व्योम megasas_complete_outstanding_ioctls(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक i;
	काष्ठा megasas_cmd *cmd_mfi;
	काष्ठा megasas_cmd_fusion *cmd_fusion;
	काष्ठा fusion_context *fusion = instance->ctrl_context;

	/* Find all outstanding ioctls */
	अगर (fusion) अणु
		क्रम (i = 0; i < instance->max_fw_cmds; i++) अणु
			cmd_fusion = fusion->cmd_list[i];
			अगर (cmd_fusion->sync_cmd_idx != (u32)अच_दीर्घ_उच्च) अणु
				cmd_mfi = instance->cmd_list[cmd_fusion->sync_cmd_idx];
				अगर (cmd_mfi->sync_cmd &&
				    (cmd_mfi->frame->hdr.cmd != MFI_CMD_ABORT)) अणु
					cmd_mfi->frame->hdr.cmd_status =
							MFI_STAT_WRONG_STATE;
					megasas_complete_cmd(instance,
							     cmd_mfi, DID_OK);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < instance->max_fw_cmds; i++) अणु
			cmd_mfi = instance->cmd_list[i];
			अगर (cmd_mfi->sync_cmd && cmd_mfi->frame->hdr.cmd !=
				MFI_CMD_ABORT)
				megasas_complete_cmd(instance, cmd_mfi, DID_OK);
		पूर्ण
	पूर्ण
पूर्ण


व्योम megaraid_sas_समाप्त_hba(काष्ठा megasas_instance *instance)
अणु
	अगर (atomic_पढ़ो(&instance->adprecovery) == MEGASAS_HW_CRITICAL_ERROR) अणु
		dev_warn(&instance->pdev->dev,
			 "Adapter already dead, skipping kill HBA\n");
		वापस;
	पूर्ण

	/* Set critical error to block I/O & ioctls in हाल caller didn't */
	atomic_set(&instance->adprecovery, MEGASAS_HW_CRITICAL_ERROR);
	/* Wait 1 second to ensure IO or ioctls in build have posted */
	msleep(1000);
	अगर ((instance->pdev->device == PCI_DEVICE_ID_LSI_SAS0073SKINNY) ||
		(instance->pdev->device == PCI_DEVICE_ID_LSI_SAS0071SKINNY) ||
		(instance->adapter_type != MFI_SERIES)) अणु
		अगर (!instance->requestorId) अणु
			ग_लिखोl(MFI_STOP_ADP, &instance->reg_set->करोorbell);
			/* Flush */
			पढ़ोl(&instance->reg_set->करोorbell);
		पूर्ण
		अगर (instance->requestorId && instance->peerIsPresent)
			स_रखो(instance->ld_ids, 0xff, MEGASAS_MAX_LD_IDS);
	पूर्ण अन्यथा अणु
		ग_लिखोl(MFI_STOP_ADP,
			&instance->reg_set->inbound_करोorbell);
	पूर्ण
	/* Complete outstanding ioctls when adapter is समाप्तed */
	megasas_complete_outstanding_ioctls(instance);
पूर्ण

 /**
  * megasas_check_and_restore_queue_depth - Check अगर queue depth needs to be
  *					restored to max value
  * @instance:			Adapter soft state
  *
  */
व्योम
megasas_check_and_restore_queue_depth(काष्ठा megasas_instance *instance)
अणु
	अचिन्हित दीर्घ flags;

	अगर (instance->flag & MEGASAS_FW_BUSY
	    && समय_after(jअगरfies, instance->last_समय + 5 * HZ)
	    && atomic_पढ़ो(&instance->fw_outstanding) <
	    instance->throttlequeuedepth + 1) अणु

		spin_lock_irqsave(instance->host->host_lock, flags);
		instance->flag &= ~MEGASAS_FW_BUSY;

		instance->host->can_queue = instance->cur_can_queue;
		spin_unlock_irqrestore(instance->host->host_lock, flags);
	पूर्ण
पूर्ण

/**
 * megasas_complete_cmd_dpc	 -	Returns FW's controller काष्ठाure
 * @instance_addr:			Address of adapter soft state
 *
 * Tasklet to complete cmds
 */
अटल व्योम megasas_complete_cmd_dpc(अचिन्हित दीर्घ instance_addr)
अणु
	u32 producer;
	u32 consumer;
	u32 context;
	काष्ठा megasas_cmd *cmd;
	काष्ठा megasas_instance *instance =
				(काष्ठा megasas_instance *)instance_addr;
	अचिन्हित दीर्घ flags;

	/* If we have alपढ़ोy declared adapter dead, करोnot complete cmds */
	अगर (atomic_पढ़ो(&instance->adprecovery) == MEGASAS_HW_CRITICAL_ERROR)
		वापस;

	spin_lock_irqsave(&instance->completion_lock, flags);

	producer = le32_to_cpu(*instance->producer);
	consumer = le32_to_cpu(*instance->consumer);

	जबतक (consumer != producer) अणु
		context = le32_to_cpu(instance->reply_queue[consumer]);
		अगर (context >= instance->max_fw_cmds) अणु
			dev_err(&instance->pdev->dev, "Unexpected context value %x\n",
				context);
			BUG();
		पूर्ण

		cmd = instance->cmd_list[context];

		megasas_complete_cmd(instance, cmd, DID_OK);

		consumer++;
		अगर (consumer == (instance->max_fw_cmds + 1)) अणु
			consumer = 0;
		पूर्ण
	पूर्ण

	*instance->consumer = cpu_to_le32(producer);

	spin_unlock_irqrestore(&instance->completion_lock, flags);

	/*
	 * Check अगर we can restore can_queue
	 */
	megasas_check_and_restore_queue_depth(instance);
पूर्ण

अटल व्योम megasas_sriov_heartbeat_handler(काष्ठा समयr_list *t);

/**
 * megasas_start_समयr - Initializes sriov heartbeat समयr object
 * @instance:		Adapter soft state
 *
 */
व्योम megasas_start_समयr(काष्ठा megasas_instance *instance)
अणु
	काष्ठा समयr_list *समयr = &instance->sriov_heartbeat_समयr;

	समयr_setup(समयr, megasas_sriov_heartbeat_handler, 0);
	समयr->expires = jअगरfies + MEGASAS_SRIOV_HEARTBEAT_INTERVAL_VF;
	add_समयr(समयr);
पूर्ण

अटल व्योम
megasas_पूर्णांकernal_reset_defer_cmds(काष्ठा megasas_instance *instance);

अटल व्योम
process_fw_state_change_wq(काष्ठा work_काष्ठा *work);

अटल व्योम megasas_करो_ocr(काष्ठा megasas_instance *instance)
अणु
	अगर ((instance->pdev->device == PCI_DEVICE_ID_LSI_SAS1064R) ||
	(instance->pdev->device == PCI_DEVICE_ID_DELL_PERC5) ||
	(instance->pdev->device == PCI_DEVICE_ID_LSI_VERDE_ZCR)) अणु
		*instance->consumer = cpu_to_le32(MEGASAS_ADPRESET_INPROG_SIGN);
	पूर्ण
	instance->instancet->disable_पूर्णांकr(instance);
	atomic_set(&instance->adprecovery, MEGASAS_ADPRESET_SM_INFAULT);
	instance->issuepend_करोne = 0;

	atomic_set(&instance->fw_outstanding, 0);
	megasas_पूर्णांकernal_reset_defer_cmds(instance);
	process_fw_state_change_wq(&instance->work_init);
पूर्ण

अटल पूर्णांक megasas_get_ld_vf_affiliation_111(काष्ठा megasas_instance *instance,
					    पूर्णांक initial)
अणु
	काष्ठा megasas_cmd *cmd;
	काष्ठा megasas_dcmd_frame *dcmd;
	काष्ठा MR_LD_VF_AFFILIATION_111 *new_affiliation_111 = शून्य;
	dma_addr_t new_affiliation_111_h;
	पूर्णांक ld, retval = 0;
	u8 thisVf;

	cmd = megasas_get_cmd(instance);

	अगर (!cmd) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "megasas_get_ld_vf_affiliation_111:"
		       "Failed to get cmd for scsi%d\n",
			instance->host->host_no);
		वापस -ENOMEM;
	पूर्ण

	dcmd = &cmd->frame->dcmd;

	अगर (!instance->vf_affiliation_111) अणु
		dev_warn(&instance->pdev->dev, "SR-IOV: Couldn't get LD/VF "
		       "affiliation for scsi%d\n", instance->host->host_no);
		megasas_वापस_cmd(instance, cmd);
		वापस -ENOMEM;
	पूर्ण

	अगर (initial)
			स_रखो(instance->vf_affiliation_111, 0,
			       माप(काष्ठा MR_LD_VF_AFFILIATION_111));
	अन्यथा अणु
		new_affiliation_111 =
			dma_alloc_coherent(&instance->pdev->dev,
					   माप(काष्ठा MR_LD_VF_AFFILIATION_111),
					   &new_affiliation_111_h, GFP_KERNEL);
		अगर (!new_affiliation_111) अणु
			dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "SR-IOV: Couldn't allocate "
			       "memory for new affiliation for scsi%d\n",
			       instance->host->host_no);
			megasas_वापस_cmd(instance, cmd);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	स_रखो(dcmd->mbox.b, 0, MFI_MBOX_SIZE);

	dcmd->cmd = MFI_CMD_DCMD;
	dcmd->cmd_status = MFI_STAT_INVALID_STATUS;
	dcmd->sge_count = 1;
	dcmd->flags = cpu_to_le16(MFI_FRAME_सूची_BOTH);
	dcmd->समयout = 0;
	dcmd->pad_0 = 0;
	dcmd->data_xfer_len =
		cpu_to_le32(माप(काष्ठा MR_LD_VF_AFFILIATION_111));
	dcmd->opcode = cpu_to_le32(MR_DCMD_LD_VF_MAP_GET_ALL_LDS_111);

	अगर (initial)
		dcmd->sgl.sge32[0].phys_addr =
			cpu_to_le32(instance->vf_affiliation_111_h);
	अन्यथा
		dcmd->sgl.sge32[0].phys_addr =
			cpu_to_le32(new_affiliation_111_h);

	dcmd->sgl.sge32[0].length = cpu_to_le32(
		माप(काष्ठा MR_LD_VF_AFFILIATION_111));

	dev_warn(&instance->pdev->dev, "SR-IOV: Getting LD/VF affiliation for "
	       "scsi%d\n", instance->host->host_no);

	अगर (megasas_issue_blocked_cmd(instance, cmd, 0) != DCMD_SUCCESS) अणु
		dev_warn(&instance->pdev->dev, "SR-IOV: LD/VF affiliation DCMD"
		       " failed with status 0x%x for scsi%d\n",
		       dcmd->cmd_status, instance->host->host_no);
		retval = 1; /* Do a scan अगर we couldn't get affiliation */
		जाओ out;
	पूर्ण

	अगर (!initial) अणु
		thisVf = new_affiliation_111->thisVf;
		क्रम (ld = 0 ; ld < new_affiliation_111->vdCount; ld++)
			अगर (instance->vf_affiliation_111->map[ld].policy[thisVf] !=
			    new_affiliation_111->map[ld].policy[thisVf]) अणु
				dev_warn(&instance->pdev->dev, "SR-IOV: "
				       "Got new LD/VF affiliation for scsi%d\n",
				       instance->host->host_no);
				स_नकल(instance->vf_affiliation_111,
				       new_affiliation_111,
				       माप(काष्ठा MR_LD_VF_AFFILIATION_111));
				retval = 1;
				जाओ out;
			पूर्ण
	पूर्ण
out:
	अगर (new_affiliation_111) अणु
		dma_मुक्त_coherent(&instance->pdev->dev,
				    माप(काष्ठा MR_LD_VF_AFFILIATION_111),
				    new_affiliation_111,
				    new_affiliation_111_h);
	पूर्ण

	megasas_वापस_cmd(instance, cmd);

	वापस retval;
पूर्ण

अटल पूर्णांक megasas_get_ld_vf_affiliation_12(काष्ठा megasas_instance *instance,
					    पूर्णांक initial)
अणु
	काष्ठा megasas_cmd *cmd;
	काष्ठा megasas_dcmd_frame *dcmd;
	काष्ठा MR_LD_VF_AFFILIATION *new_affiliation = शून्य;
	काष्ठा MR_LD_VF_MAP *newmap = शून्य, *savedmap = शून्य;
	dma_addr_t new_affiliation_h;
	पूर्णांक i, j, retval = 0, found = 0, करोscan = 0;
	u8 thisVf;

	cmd = megasas_get_cmd(instance);

	अगर (!cmd) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "megasas_get_ld_vf_affiliation12: "
		       "Failed to get cmd for scsi%d\n",
		       instance->host->host_no);
		वापस -ENOMEM;
	पूर्ण

	dcmd = &cmd->frame->dcmd;

	अगर (!instance->vf_affiliation) अणु
		dev_warn(&instance->pdev->dev, "SR-IOV: Couldn't get LD/VF "
		       "affiliation for scsi%d\n", instance->host->host_no);
		megasas_वापस_cmd(instance, cmd);
		वापस -ENOMEM;
	पूर्ण

	अगर (initial)
		स_रखो(instance->vf_affiliation, 0, (MAX_LOGICAL_DRIVES + 1) *
		       माप(काष्ठा MR_LD_VF_AFFILIATION));
	अन्यथा अणु
		new_affiliation =
			dma_alloc_coherent(&instance->pdev->dev,
					   (MAX_LOGICAL_DRIVES + 1) * माप(काष्ठा MR_LD_VF_AFFILIATION),
					   &new_affiliation_h, GFP_KERNEL);
		अगर (!new_affiliation) अणु
			dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "SR-IOV: Couldn't allocate "
			       "memory for new affiliation for scsi%d\n",
			       instance->host->host_no);
			megasas_वापस_cmd(instance, cmd);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	स_रखो(dcmd->mbox.b, 0, MFI_MBOX_SIZE);

	dcmd->cmd = MFI_CMD_DCMD;
	dcmd->cmd_status = MFI_STAT_INVALID_STATUS;
	dcmd->sge_count = 1;
	dcmd->flags = cpu_to_le16(MFI_FRAME_सूची_BOTH);
	dcmd->समयout = 0;
	dcmd->pad_0 = 0;
	dcmd->data_xfer_len = cpu_to_le32((MAX_LOGICAL_DRIVES + 1) *
		माप(काष्ठा MR_LD_VF_AFFILIATION));
	dcmd->opcode = cpu_to_le32(MR_DCMD_LD_VF_MAP_GET_ALL_LDS);

	अगर (initial)
		dcmd->sgl.sge32[0].phys_addr =
			cpu_to_le32(instance->vf_affiliation_h);
	अन्यथा
		dcmd->sgl.sge32[0].phys_addr =
			cpu_to_le32(new_affiliation_h);

	dcmd->sgl.sge32[0].length = cpu_to_le32((MAX_LOGICAL_DRIVES + 1) *
		माप(काष्ठा MR_LD_VF_AFFILIATION));

	dev_warn(&instance->pdev->dev, "SR-IOV: Getting LD/VF affiliation for "
	       "scsi%d\n", instance->host->host_no);


	अगर (megasas_issue_blocked_cmd(instance, cmd, 0) != DCMD_SUCCESS) अणु
		dev_warn(&instance->pdev->dev, "SR-IOV: LD/VF affiliation DCMD"
		       " failed with status 0x%x for scsi%d\n",
		       dcmd->cmd_status, instance->host->host_no);
		retval = 1; /* Do a scan अगर we couldn't get affiliation */
		जाओ out;
	पूर्ण

	अगर (!initial) अणु
		अगर (!new_affiliation->ldCount) अणु
			dev_warn(&instance->pdev->dev, "SR-IOV: Got new LD/VF "
			       "affiliation for passive path for scsi%d\n",
			       instance->host->host_no);
			retval = 1;
			जाओ out;
		पूर्ण
		newmap = new_affiliation->map;
		savedmap = instance->vf_affiliation->map;
		thisVf = new_affiliation->thisVf;
		क्रम (i = 0 ; i < new_affiliation->ldCount; i++) अणु
			found = 0;
			क्रम (j = 0; j < instance->vf_affiliation->ldCount;
			     j++) अणु
				अगर (newmap->ref.targetId ==
				    savedmap->ref.targetId) अणु
					found = 1;
					अगर (newmap->policy[thisVf] !=
					    savedmap->policy[thisVf]) अणु
						करोscan = 1;
						जाओ out;
					पूर्ण
				पूर्ण
				savedmap = (काष्ठा MR_LD_VF_MAP *)
					((अचिन्हित अक्षर *)savedmap +
					 savedmap->size);
			पूर्ण
			अगर (!found && newmap->policy[thisVf] !=
			    MR_LD_ACCESS_HIDDEN) अणु
				करोscan = 1;
				जाओ out;
			पूर्ण
			newmap = (काष्ठा MR_LD_VF_MAP *)
				((अचिन्हित अक्षर *)newmap + newmap->size);
		पूर्ण

		newmap = new_affiliation->map;
		savedmap = instance->vf_affiliation->map;

		क्रम (i = 0 ; i < instance->vf_affiliation->ldCount; i++) अणु
			found = 0;
			क्रम (j = 0 ; j < new_affiliation->ldCount; j++) अणु
				अगर (savedmap->ref.targetId ==
				    newmap->ref.targetId) अणु
					found = 1;
					अगर (savedmap->policy[thisVf] !=
					    newmap->policy[thisVf]) अणु
						करोscan = 1;
						जाओ out;
					पूर्ण
				पूर्ण
				newmap = (काष्ठा MR_LD_VF_MAP *)
					((अचिन्हित अक्षर *)newmap +
					 newmap->size);
			पूर्ण
			अगर (!found && savedmap->policy[thisVf] !=
			    MR_LD_ACCESS_HIDDEN) अणु
				करोscan = 1;
				जाओ out;
			पूर्ण
			savedmap = (काष्ठा MR_LD_VF_MAP *)
				((अचिन्हित अक्षर *)savedmap +
				 savedmap->size);
		पूर्ण
	पूर्ण
out:
	अगर (करोscan) अणु
		dev_warn(&instance->pdev->dev, "SR-IOV: Got new LD/VF "
		       "affiliation for scsi%d\n", instance->host->host_no);
		स_नकल(instance->vf_affiliation, new_affiliation,
		       new_affiliation->size);
		retval = 1;
	पूर्ण

	अगर (new_affiliation)
		dma_मुक्त_coherent(&instance->pdev->dev,
				    (MAX_LOGICAL_DRIVES + 1) *
				    माप(काष्ठा MR_LD_VF_AFFILIATION),
				    new_affiliation, new_affiliation_h);
	megasas_वापस_cmd(instance, cmd);

	वापस retval;
पूर्ण

/* This function will get the current SR-IOV LD/VF affiliation */
अटल पूर्णांक megasas_get_ld_vf_affiliation(काष्ठा megasas_instance *instance,
	पूर्णांक initial)
अणु
	पूर्णांक retval;

	अगर (instance->Plयंत्रaFW111)
		retval = megasas_get_ld_vf_affiliation_111(instance, initial);
	अन्यथा
		retval = megasas_get_ld_vf_affiliation_12(instance, initial);
	वापस retval;
पूर्ण

/* This function will tell FW to start the SR-IOV heartbeat */
पूर्णांक megasas_sriov_start_heartbeat(काष्ठा megasas_instance *instance,
					 पूर्णांक initial)
अणु
	काष्ठा megasas_cmd *cmd;
	काष्ठा megasas_dcmd_frame *dcmd;
	पूर्णांक retval = 0;

	cmd = megasas_get_cmd(instance);

	अगर (!cmd) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "megasas_sriov_start_heartbeat: "
		       "Failed to get cmd for scsi%d\n",
		       instance->host->host_no);
		वापस -ENOMEM;
	पूर्ण

	dcmd = &cmd->frame->dcmd;

	अगर (initial) अणु
		instance->hb_host_mem =
			dma_alloc_coherent(&instance->pdev->dev,
					   माप(काष्ठा MR_CTRL_HB_HOST_MEM),
					   &instance->hb_host_mem_h,
					   GFP_KERNEL);
		अगर (!instance->hb_host_mem) अणु
			dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "SR-IOV: Couldn't allocate"
			       " memory for heartbeat host memory for scsi%d\n",
			       instance->host->host_no);
			retval = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण

	स_रखो(dcmd->mbox.b, 0, MFI_MBOX_SIZE);

	dcmd->mbox.s[0] = cpu_to_le16(माप(काष्ठा MR_CTRL_HB_HOST_MEM));
	dcmd->cmd = MFI_CMD_DCMD;
	dcmd->cmd_status = MFI_STAT_INVALID_STATUS;
	dcmd->sge_count = 1;
	dcmd->flags = cpu_to_le16(MFI_FRAME_सूची_BOTH);
	dcmd->समयout = 0;
	dcmd->pad_0 = 0;
	dcmd->data_xfer_len = cpu_to_le32(माप(काष्ठा MR_CTRL_HB_HOST_MEM));
	dcmd->opcode = cpu_to_le32(MR_DCMD_CTRL_SHARED_HOST_MEM_ALLOC);

	megasas_set_dma_settings(instance, dcmd, instance->hb_host_mem_h,
				 माप(काष्ठा MR_CTRL_HB_HOST_MEM));

	dev_warn(&instance->pdev->dev, "SR-IOV: Starting heartbeat for scsi%d\n",
	       instance->host->host_no);

	अगर ((instance->adapter_type != MFI_SERIES) &&
	    !instance->mask_पूर्णांकerrupts)
		retval = megasas_issue_blocked_cmd(instance, cmd,
			MEGASAS_ROUTINE_WAIT_TIME_VF);
	अन्यथा
		retval = megasas_issue_polled(instance, cmd);

	अगर (retval) अणु
		dev_warn(&instance->pdev->dev, "SR-IOV: MR_DCMD_CTRL_SHARED_HOST"
			"_MEM_ALLOC DCMD %s for scsi%d\n",
			(dcmd->cmd_status == MFI_STAT_INVALID_STATUS) ?
			"timed out" : "failed", instance->host->host_no);
		retval = 1;
	पूर्ण

out:
	megasas_वापस_cmd(instance, cmd);

	वापस retval;
पूर्ण

/* Handler क्रम SR-IOV heartbeat */
अटल व्योम megasas_sriov_heartbeat_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा megasas_instance *instance =
		from_समयr(instance, t, sriov_heartbeat_समयr);

	अगर (instance->hb_host_mem->HB.fwCounter !=
	    instance->hb_host_mem->HB.driverCounter) अणु
		instance->hb_host_mem->HB.driverCounter =
			instance->hb_host_mem->HB.fwCounter;
		mod_समयr(&instance->sriov_heartbeat_समयr,
			  jअगरfies + MEGASAS_SRIOV_HEARTBEAT_INTERVAL_VF);
	पूर्ण अन्यथा अणु
		dev_warn(&instance->pdev->dev, "SR-IOV: Heartbeat never "
		       "completed for scsi%d\n", instance->host->host_no);
		schedule_work(&instance->work_init);
	पूर्ण
पूर्ण

/**
 * megasas_रुको_क्रम_outstanding -	Wait क्रम all outstanding cmds
 * @instance:				Adapter soft state
 *
 * This function रुकोs क्रम up to MEGASAS_RESET_WAIT_TIME seconds क्रम FW to
 * complete all its outstanding commands. Returns error अगर one or more IOs
 * are pending after this समय period. It also marks the controller dead.
 */
अटल पूर्णांक megasas_रुको_क्रम_outstanding(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक i, sl, outstanding;
	u32 reset_index;
	u32 रुको_समय = MEGASAS_RESET_WAIT_TIME;
	अचिन्हित दीर्घ flags;
	काष्ठा list_head clist_local;
	काष्ठा megasas_cmd *reset_cmd;
	u32 fw_state;

	अगर (atomic_पढ़ो(&instance->adprecovery) == MEGASAS_HW_CRITICAL_ERROR) अणु
		dev_info(&instance->pdev->dev, "%s:%d HBA is killed.\n",
		__func__, __LINE__);
		वापस FAILED;
	पूर्ण

	अगर (atomic_पढ़ो(&instance->adprecovery) != MEGASAS_HBA_OPERATIONAL) अणु

		INIT_LIST_HEAD(&clist_local);
		spin_lock_irqsave(&instance->hba_lock, flags);
		list_splice_init(&instance->पूर्णांकernal_reset_pending_q,
				&clist_local);
		spin_unlock_irqrestore(&instance->hba_lock, flags);

		dev_notice(&instance->pdev->dev, "HBA reset wait ...\n");
		क्रम (i = 0; i < रुको_समय; i++) अणु
			msleep(1000);
			अगर (atomic_पढ़ो(&instance->adprecovery) == MEGASAS_HBA_OPERATIONAL)
				अवरोध;
		पूर्ण

		अगर (atomic_पढ़ो(&instance->adprecovery) != MEGASAS_HBA_OPERATIONAL) अणु
			dev_notice(&instance->pdev->dev, "reset: Stopping HBA.\n");
			atomic_set(&instance->adprecovery, MEGASAS_HW_CRITICAL_ERROR);
			वापस FAILED;
		पूर्ण

		reset_index = 0;
		जबतक (!list_empty(&clist_local)) अणु
			reset_cmd = list_entry((&clist_local)->next,
						काष्ठा megasas_cmd, list);
			list_del_init(&reset_cmd->list);
			अगर (reset_cmd->scmd) अणु
				reset_cmd->scmd->result = DID_REQUEUE << 16;
				dev_notice(&instance->pdev->dev, "%d:%p reset [%02x]\n",
					reset_index, reset_cmd,
					reset_cmd->scmd->cmnd[0]);

				reset_cmd->scmd->scsi_करोne(reset_cmd->scmd);
				megasas_वापस_cmd(instance, reset_cmd);
			पूर्ण अन्यथा अगर (reset_cmd->sync_cmd) अणु
				dev_notice(&instance->pdev->dev, "%p synch cmds"
						"reset queue\n",
						reset_cmd);

				reset_cmd->cmd_status_drv = DCMD_INIT;
				instance->instancet->fire_cmd(instance,
						reset_cmd->frame_phys_addr,
						0, instance->reg_set);
			पूर्ण अन्यथा अणु
				dev_notice(&instance->pdev->dev, "%p unexpected"
					"cmds lst\n",
					reset_cmd);
			पूर्ण
			reset_index++;
		पूर्ण

		वापस SUCCESS;
	पूर्ण

	क्रम (i = 0; i < resetरुकोसमय; i++) अणु
		outstanding = atomic_पढ़ो(&instance->fw_outstanding);

		अगर (!outstanding)
			अवरोध;

		अगर (!(i % MEGASAS_RESET_NOTICE_INTERVAL)) अणु
			dev_notice(&instance->pdev->dev, "[%2d]waiting for %d "
			       "commands to complete\n",i,outstanding);
			/*
			 * Call cmd completion routine. Cmd to be
			 * be completed directly without depending on isr.
			 */
			megasas_complete_cmd_dpc((अचिन्हित दीर्घ)instance);
		पूर्ण

		msleep(1000);
	पूर्ण

	i = 0;
	outstanding = atomic_पढ़ो(&instance->fw_outstanding);
	fw_state = instance->instancet->पढ़ो_fw_status_reg(instance) & MFI_STATE_MASK;

	अगर ((!outstanding && (fw_state == MFI_STATE_OPERATIONAL)))
		जाओ no_outstanding;

	अगर (instance->disableOnlineCtrlReset)
		जाओ समाप्त_hba_and_failed;
	करो अणु
		अगर ((fw_state == MFI_STATE_FAULT) || atomic_पढ़ो(&instance->fw_outstanding)) अणु
			dev_info(&instance->pdev->dev,
				"%s:%d waiting_for_outstanding: before issue OCR. FW state = 0x%x, outstanding 0x%x\n",
				__func__, __LINE__, fw_state, atomic_पढ़ो(&instance->fw_outstanding));
			अगर (i == 3)
				जाओ समाप्त_hba_and_failed;
			megasas_करो_ocr(instance);

			अगर (atomic_पढ़ो(&instance->adprecovery) == MEGASAS_HW_CRITICAL_ERROR) अणु
				dev_info(&instance->pdev->dev, "%s:%d OCR failed and HBA is killed.\n",
				__func__, __LINE__);
				वापस FAILED;
			पूर्ण
			dev_info(&instance->pdev->dev, "%s:%d waiting_for_outstanding: after issue OCR.\n",
				__func__, __LINE__);

			क्रम (sl = 0; sl < 10; sl++)
				msleep(500);

			outstanding = atomic_पढ़ो(&instance->fw_outstanding);

			fw_state = instance->instancet->पढ़ो_fw_status_reg(instance) & MFI_STATE_MASK;
			अगर ((!outstanding && (fw_state == MFI_STATE_OPERATIONAL)))
				जाओ no_outstanding;
		पूर्ण
		i++;
	पूर्ण जबतक (i <= 3);

no_outstanding:

	dev_info(&instance->pdev->dev, "%s:%d no more pending commands remain after reset handling.\n",
		__func__, __LINE__);
	वापस SUCCESS;

समाप्त_hba_and_failed:

	/* Reset not supported, समाप्त adapter */
	dev_info(&instance->pdev->dev, "%s:%d killing adapter scsi%d"
		" disableOnlineCtrlReset %d fw_outstanding %d \n",
		__func__, __LINE__, instance->host->host_no, instance->disableOnlineCtrlReset,
		atomic_पढ़ो(&instance->fw_outstanding));
	megasas_dump_pending_frames(instance);
	megaraid_sas_समाप्त_hba(instance);

	वापस FAILED;
पूर्ण

/**
 * megasas_generic_reset -	Generic reset routine
 * @scmd:			Mid-layer SCSI command
 *
 * This routine implements a generic reset handler क्रम device, bus and host
 * reset requests. Device, bus and host specअगरic reset handlers can use this
 * function after they करो their specअगरic tasks.
 */
अटल पूर्णांक megasas_generic_reset(काष्ठा scsi_cmnd *scmd)
अणु
	पूर्णांक ret_val;
	काष्ठा megasas_instance *instance;

	instance = (काष्ठा megasas_instance *)scmd->device->host->hostdata;

	scmd_prपूर्णांकk(KERN_NOTICE, scmd, "megasas: RESET cmd=%x retries=%x\n",
		 scmd->cmnd[0], scmd->retries);

	अगर (atomic_पढ़ो(&instance->adprecovery) == MEGASAS_HW_CRITICAL_ERROR) अणु
		dev_err(&instance->pdev->dev, "cannot recover from previous reset failures\n");
		वापस FAILED;
	पूर्ण

	ret_val = megasas_रुको_क्रम_outstanding(instance);
	अगर (ret_val == SUCCESS)
		dev_notice(&instance->pdev->dev, "reset successful\n");
	अन्यथा
		dev_err(&instance->pdev->dev, "failed to do reset\n");

	वापस ret_val;
पूर्ण

/**
 * megasas_reset_समयr - quiesce the adapter अगर required
 * @scmd:		scsi cmnd
 *
 * Sets the FW busy flag and reduces the host->can_queue अगर the
 * cmd has not been completed within the समयout period.
 */
अटल क्रमागत
blk_eh_समयr_वापस megasas_reset_समयr(काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा megasas_instance *instance;
	अचिन्हित दीर्घ flags;

	अगर (समय_after(jअगरfies, scmd->jअगरfies_at_alloc +
				(scmd_समयout * 2) * HZ)) अणु
		वापस BLK_EH_DONE;
	पूर्ण

	instance = (काष्ठा megasas_instance *)scmd->device->host->hostdata;
	अगर (!(instance->flag & MEGASAS_FW_BUSY)) अणु
		/* FW is busy, throttle IO */
		spin_lock_irqsave(instance->host->host_lock, flags);

		instance->host->can_queue = instance->throttlequeuedepth;
		instance->last_समय = jअगरfies;
		instance->flag |= MEGASAS_FW_BUSY;

		spin_unlock_irqrestore(instance->host->host_lock, flags);
	पूर्ण
	वापस BLK_EH_RESET_TIMER;
पूर्ण

/**
 * megasas_dump -	This function will prपूर्णांक hexdump of provided buffer.
 * @buf:		Buffer to be dumped
 * @sz:		Size in bytes
 * @क्रमmat:		Dअगरferent क्रमmats of dumping e.g. क्रमmat=n will
 *			cause only 'n' 32 bit words to be dumped in a single
 *			line.
 */
अंतरभूत व्योम
megasas_dump(व्योम *buf, पूर्णांक sz, पूर्णांक क्रमmat)
अणु
	पूर्णांक i;
	__le32 *buf_loc = (__le32 *)buf;

	क्रम (i = 0; i < (sz / माप(__le32)); i++) अणु
		अगर ((i % क्रमmat) == 0) अणु
			अगर (i != 0)
				prपूर्णांकk(KERN_CONT "\n");
			prपूर्णांकk(KERN_CONT "%08x: ", (i * 4));
		पूर्ण
		prपूर्णांकk(KERN_CONT "%08x ", le32_to_cpu(buf_loc[i]));
	पूर्ण
	prपूर्णांकk(KERN_CONT "\n");
पूर्ण

/**
 * megasas_dump_reg_set -	This function will prपूर्णांक hexdump of रेजिस्टर set
 * @reg_set:	Register set to be dumped
 */
अंतरभूत व्योम
megasas_dump_reg_set(व्योम __iomem *reg_set)
अणु
	अचिन्हित पूर्णांक i, sz = 256;
	u32 __iomem *reg = (u32 __iomem *)reg_set;

	क्रम (i = 0; i < (sz / माप(u32)); i++)
		prपूर्णांकk("%08x: %08x\n", (i * 4), पढ़ोl(&reg[i]));
पूर्ण

/**
 * megasas_dump_fusion_io -	This function will prपूर्णांक key details
 *				of SCSI IO
 * @scmd:			SCSI command poपूर्णांकer of SCSI IO
 */
व्योम
megasas_dump_fusion_io(काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा megasas_cmd_fusion *cmd;
	जोड़ MEGASAS_REQUEST_DESCRIPTOR_UNION *req_desc;
	काष्ठा megasas_instance *instance;

	cmd = (काष्ठा megasas_cmd_fusion *)scmd->SCp.ptr;
	instance = (काष्ठा megasas_instance *)scmd->device->host->hostdata;

	scmd_prपूर्णांकk(KERN_INFO, scmd,
		    "scmd: (0x%p)  retries: 0x%x  allowed: 0x%x\n",
		    scmd, scmd->retries, scmd->allowed);
	scsi_prपूर्णांक_command(scmd);

	अगर (cmd) अणु
		req_desc = (जोड़ MEGASAS_REQUEST_DESCRIPTOR_UNION *)cmd->request_desc;
		scmd_prपूर्णांकk(KERN_INFO, scmd, "Request descriptor details:\n");
		scmd_prपूर्णांकk(KERN_INFO, scmd,
			    "RequestFlags:0x%x  MSIxIndex:0x%x  SMID:0x%x  LMID:0x%x  DevHandle:0x%x\n",
			    req_desc->SCSIIO.RequestFlags,
			    req_desc->SCSIIO.MSIxIndex, req_desc->SCSIIO.SMID,
			    req_desc->SCSIIO.LMID, req_desc->SCSIIO.DevHandle);

		prपूर्णांकk(KERN_INFO "IO request frame:\n");
		megasas_dump(cmd->io_request,
			     MEGA_MPI2_RAID_DEFAULT_IO_FRAME_SIZE, 8);
		prपूर्णांकk(KERN_INFO "Chain frame:\n");
		megasas_dump(cmd->sg_frame,
			     instance->max_chain_frame_sz, 8);
	पूर्ण

पूर्ण

/*
 * megasas_dump_sys_regs - This function will dump प्रणाली रेजिस्टरs through
 *			    sysfs.
 * @reg_set:		    Poपूर्णांकer to System रेजिस्टर set.
 * @buf:		    Buffer to which output is to be written.
 * @वापस:		    Number of bytes written to buffer.
 */
अटल अंतरभूत sमाप_प्रकार
megasas_dump_sys_regs(व्योम __iomem *reg_set, अक्षर *buf)
अणु
	अचिन्हित पूर्णांक i, sz = 256;
	पूर्णांक bytes_wrote = 0;
	अक्षर *loc = (अक्षर *)buf;
	u32 __iomem *reg = (u32 __iomem *)reg_set;

	क्रम (i = 0; i < sz / माप(u32); i++) अणु
		bytes_wrote += scnम_लिखो(loc + bytes_wrote,
					 PAGE_SIZE - bytes_wrote,
					 "%08x: %08x\n", (i * 4),
					 पढ़ोl(&reg[i]));
	पूर्ण
	वापस bytes_wrote;
पूर्ण

/**
 * megasas_reset_bus_host -	Bus & host reset handler entry poपूर्णांक
 * @scmd:			Mid-layer SCSI command
 */
अटल पूर्णांक megasas_reset_bus_host(काष्ठा scsi_cmnd *scmd)
अणु
	पूर्णांक ret;
	काष्ठा megasas_instance *instance;

	instance = (काष्ठा megasas_instance *)scmd->device->host->hostdata;

	scmd_prपूर्णांकk(KERN_INFO, scmd,
		"OCR is requested due to IO timeout!!\n");

	scmd_prपूर्णांकk(KERN_INFO, scmd,
		"SCSI host state: %d  SCSI host busy: %d  FW outstanding: %d\n",
		scmd->device->host->shost_state,
		scsi_host_busy(scmd->device->host),
		atomic_पढ़ो(&instance->fw_outstanding));
	/*
	 * First रुको क्रम all commands to complete
	 */
	अगर (instance->adapter_type == MFI_SERIES) अणु
		ret = megasas_generic_reset(scmd);
	पूर्ण अन्यथा अणु
		megasas_dump_fusion_io(scmd);
		ret = megasas_reset_fusion(scmd->device->host,
				SCSIIO_TIMEOUT_OCR);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * megasas_task_पात - Issues task पात request to firmware
 *			(supported only क्रम fusion adapters)
 * @scmd:		SCSI command poपूर्णांकer
 */
अटल पूर्णांक megasas_task_पात(काष्ठा scsi_cmnd *scmd)
अणु
	पूर्णांक ret;
	काष्ठा megasas_instance *instance;

	instance = (काष्ठा megasas_instance *)scmd->device->host->hostdata;

	अगर (instance->adapter_type != MFI_SERIES)
		ret = megasas_task_पात_fusion(scmd);
	अन्यथा अणु
		sdev_prपूर्णांकk(KERN_NOTICE, scmd->device, "TASK ABORT not supported\n");
		ret = FAILED;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * megasas_reset_target:  Issues target reset request to firmware
 *                        (supported only क्रम fusion adapters)
 * @scmd:                 SCSI command poपूर्णांकer
 */
अटल पूर्णांक megasas_reset_target(काष्ठा scsi_cmnd *scmd)
अणु
	पूर्णांक ret;
	काष्ठा megasas_instance *instance;

	instance = (काष्ठा megasas_instance *)scmd->device->host->hostdata;

	अगर (instance->adapter_type != MFI_SERIES)
		ret = megasas_reset_target_fusion(scmd);
	अन्यथा अणु
		sdev_prपूर्णांकk(KERN_NOTICE, scmd->device, "TARGET RESET not supported\n");
		ret = FAILED;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * megasas_bios_param - Returns disk geometry क्रम a disk
 * @sdev:		device handle
 * @bdev:		block device
 * @capacity:		drive capacity
 * @geom:		geometry parameters
 */
अटल पूर्णांक
megasas_bios_param(काष्ठा scsi_device *sdev, काष्ठा block_device *bdev,
		 sector_t capacity, पूर्णांक geom[])
अणु
	पूर्णांक heads;
	पूर्णांक sectors;
	sector_t cylinders;
	अचिन्हित दीर्घ पंचांगp;

	/* Default heads (64) & sectors (32) */
	heads = 64;
	sectors = 32;

	पंचांगp = heads * sectors;
	cylinders = capacity;

	sector_भाग(cylinders, पंचांगp);

	/*
	 * Handle extended translation size क्रम logical drives > 1Gb
	 */

	अगर (capacity >= 0x200000) अणु
		heads = 255;
		sectors = 63;
		पंचांगp = heads*sectors;
		cylinders = capacity;
		sector_भाग(cylinders, पंचांगp);
	पूर्ण

	geom[0] = heads;
	geom[1] = sectors;
	geom[2] = cylinders;

	वापस 0;
पूर्ण

अटल पूर्णांक megasas_map_queues(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा megasas_instance *instance;
	पूर्णांक qoff = 0, offset;
	काष्ठा blk_mq_queue_map *map;

	instance = (काष्ठा megasas_instance *)shost->hostdata;

	अगर (shost->nr_hw_queues == 1)
		वापस 0;

	offset = instance->low_latency_index_start;

	/* Setup Default hctx */
	map = &shost->tag_set.map[HCTX_TYPE_DEFAULT];
	map->nr_queues = instance->msix_vectors - offset;
	map->queue_offset = 0;
	blk_mq_pci_map_queues(map, instance->pdev, offset);
	qoff += map->nr_queues;
	offset += map->nr_queues;

	/* Setup Poll hctx */
	map = &shost->tag_set.map[HCTX_TYPE_POLL];
	map->nr_queues = instance->iopoll_q_count;
	अगर (map->nr_queues) अणु
		/*
		 * The poll queue(s) करोesn't have an IRQ (and hence IRQ
		 * affinity), so use the regular blk-mq cpu mapping
		 */
		map->queue_offset = qoff;
		blk_mq_map_queues(map);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम megasas_aen_polling(काष्ठा work_काष्ठा *work);

/**
 * megasas_service_aen -	Processes an event notअगरication
 * @instance:			Adapter soft state
 * @cmd:			AEN command completed by the ISR
 *
 * For AEN, driver sends a command करोwn to FW that is held by the FW till an
 * event occurs. When an event of पूर्णांकerest occurs, FW completes the command
 * that it was previously holding.
 *
 * This routines sends SIGIO संकेत to processes that have रेजिस्टरed with the
 * driver क्रम AEN.
 */
अटल व्योम
megasas_service_aen(काष्ठा megasas_instance *instance, काष्ठा megasas_cmd *cmd)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * Don't संकेत app अगर it is just an पातed previously रेजिस्टरed aen
	 */
	अगर ((!cmd->पात_aen) && (instance->unload == 0)) अणु
		spin_lock_irqsave(&poll_aen_lock, flags);
		megasas_poll_रुको_aen = 1;
		spin_unlock_irqrestore(&poll_aen_lock, flags);
		wake_up(&megasas_poll_रुको);
		समाप्त_fasync(&megasas_async_queue, SIGIO, POLL_IN);
	पूर्ण
	अन्यथा
		cmd->पात_aen = 0;

	instance->aen_cmd = शून्य;

	megasas_वापस_cmd(instance, cmd);

	अगर ((instance->unload == 0) &&
		((instance->issuepend_करोne == 1))) अणु
		काष्ठा megasas_aen_event *ev;

		ev = kzalloc(माप(*ev), GFP_ATOMIC);
		अगर (!ev) अणु
			dev_err(&instance->pdev->dev, "megasas_service_aen: out of memory\n");
		पूर्ण अन्यथा अणु
			ev->instance = instance;
			instance->ev = ev;
			INIT_DELAYED_WORK(&ev->hotplug_work,
					  megasas_aen_polling);
			schedule_delayed_work(&ev->hotplug_work, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल sमाप_प्रकार
fw_crash_buffer_store(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा megasas_instance *instance =
		(काष्ठा megasas_instance *) shost->hostdata;
	पूर्णांक val = 0;
	अचिन्हित दीर्घ flags;

	अगर (kstrtoपूर्णांक(buf, 0, &val) != 0)
		वापस -EINVAL;

	spin_lock_irqsave(&instance->crashdump_lock, flags);
	instance->fw_crash_buffer_offset = val;
	spin_unlock_irqrestore(&instance->crashdump_lock, flags);
	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार
fw_crash_buffer_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा megasas_instance *instance =
		(काष्ठा megasas_instance *) shost->hostdata;
	u32 size;
	अचिन्हित दीर्घ dmachunk = CRASH_DMA_BUF_SIZE;
	अचिन्हित दीर्घ chunk_left_bytes;
	अचिन्हित दीर्घ src_addr;
	अचिन्हित दीर्घ flags;
	u32 buff_offset;

	spin_lock_irqsave(&instance->crashdump_lock, flags);
	buff_offset = instance->fw_crash_buffer_offset;
	अगर (!instance->crash_dump_buf &&
		!((instance->fw_crash_state == AVAILABLE) ||
		(instance->fw_crash_state == COPYING))) अणु
		dev_err(&instance->pdev->dev,
			"Firmware crash dump is not available\n");
		spin_unlock_irqrestore(&instance->crashdump_lock, flags);
		वापस -EINVAL;
	पूर्ण

	अगर (buff_offset > (instance->fw_crash_buffer_size * dmachunk)) अणु
		dev_err(&instance->pdev->dev,
			"Firmware crash dump offset is out of range\n");
		spin_unlock_irqrestore(&instance->crashdump_lock, flags);
		वापस 0;
	पूर्ण

	size = (instance->fw_crash_buffer_size * dmachunk) - buff_offset;
	chunk_left_bytes = dmachunk - (buff_offset % dmachunk);
	size = (size > chunk_left_bytes) ? chunk_left_bytes : size;
	size = (size >= PAGE_SIZE) ? (PAGE_SIZE - 1) : size;

	src_addr = (अचिन्हित दीर्घ)instance->crash_buf[buff_offset / dmachunk] +
		(buff_offset % dmachunk);
	स_नकल(buf, (व्योम *)src_addr, size);
	spin_unlock_irqrestore(&instance->crashdump_lock, flags);

	वापस size;
पूर्ण

अटल sमाप_प्रकार
fw_crash_buffer_size_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा megasas_instance *instance =
		(काष्ठा megasas_instance *) shost->hostdata;

	वापस snम_लिखो(buf, PAGE_SIZE, "%ld\n", (अचिन्हित दीर्घ)
		((instance->fw_crash_buffer_size) * 1024 * 1024)/PAGE_SIZE);
पूर्ण

अटल sमाप_प्रकार
fw_crash_state_store(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा megasas_instance *instance =
		(काष्ठा megasas_instance *) shost->hostdata;
	पूर्णांक val = 0;
	अचिन्हित दीर्घ flags;

	अगर (kstrtoपूर्णांक(buf, 0, &val) != 0)
		वापस -EINVAL;

	अगर ((val <= AVAILABLE || val > COPY_ERROR)) अणु
		dev_err(&instance->pdev->dev, "application updates invalid "
			"firmware crash state\n");
		वापस -EINVAL;
	पूर्ण

	instance->fw_crash_state = val;

	अगर ((val == COPIED) || (val == COPY_ERROR)) अणु
		spin_lock_irqsave(&instance->crashdump_lock, flags);
		megasas_मुक्त_host_crash_buffer(instance);
		spin_unlock_irqrestore(&instance->crashdump_lock, flags);
		अगर (val == COPY_ERROR)
			dev_info(&instance->pdev->dev, "application failed to "
				"copy Firmware crash dump\n");
		अन्यथा
			dev_info(&instance->pdev->dev, "Firmware crash dump "
				"copied successfully\n");
	पूर्ण
	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार
fw_crash_state_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा megasas_instance *instance =
		(काष्ठा megasas_instance *) shost->hostdata;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", instance->fw_crash_state);
पूर्ण

अटल sमाप_प्रकार
page_size_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%ld\n", (अचिन्हित दीर्घ)PAGE_SIZE - 1);
पूर्ण

अटल sमाप_प्रकार
ldio_outstanding_show(काष्ठा device *cdev, काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा megasas_instance *instance = (काष्ठा megasas_instance *)shost->hostdata;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", atomic_पढ़ो(&instance->ldio_outstanding));
पूर्ण

अटल sमाप_प्रकार
fw_cmds_outstanding_show(काष्ठा device *cdev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा megasas_instance *instance = (काष्ठा megasas_instance *)shost->hostdata;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", atomic_पढ़ो(&instance->fw_outstanding));
पूर्ण

अटल sमाप_प्रकार
enable_sdev_max_qd_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा megasas_instance *instance = (काष्ठा megasas_instance *)shost->hostdata;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", instance->enable_sdev_max_qd);
पूर्ण

अटल sमाप_प्रकार
enable_sdev_max_qd_store(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा megasas_instance *instance = (काष्ठा megasas_instance *)shost->hostdata;
	u32 val = 0;
	bool is_target_prop;
	पूर्णांक ret_target_prop = DCMD_FAILED;
	काष्ठा scsi_device *sdev;

	अगर (kstrtou32(buf, 0, &val) != 0) अणु
		pr_err("megasas: could not set enable_sdev_max_qd\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&instance->reset_mutex);
	अगर (val)
		instance->enable_sdev_max_qd = true;
	अन्यथा
		instance->enable_sdev_max_qd = false;

	shost_क्रम_each_device(sdev, shost) अणु
		ret_target_prop = megasas_get_target_prop(instance, sdev);
		is_target_prop = (ret_target_prop == DCMD_SUCCESS) ? true : false;
		megasas_set_fw_assisted_qd(sdev, is_target_prop);
	पूर्ण
	mutex_unlock(&instance->reset_mutex);

	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार
dump_प्रणाली_regs_show(काष्ठा device *cdev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा megasas_instance *instance =
			(काष्ठा megasas_instance *)shost->hostdata;

	वापस megasas_dump_sys_regs(instance->reg_set, buf);
पूर्ण

अटल sमाप_प्रकार
raid_map_id_show(काष्ठा device *cdev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा megasas_instance *instance =
			(काष्ठा megasas_instance *)shost->hostdata;

	वापस snम_लिखो(buf, PAGE_SIZE, "%ld\n",
			(अचिन्हित दीर्घ)instance->map_id);
पूर्ण

अटल DEVICE_ATTR_RW(fw_crash_buffer);
अटल DEVICE_ATTR_RO(fw_crash_buffer_size);
अटल DEVICE_ATTR_RW(fw_crash_state);
अटल DEVICE_ATTR_RO(page_size);
अटल DEVICE_ATTR_RO(ldio_outstanding);
अटल DEVICE_ATTR_RO(fw_cmds_outstanding);
अटल DEVICE_ATTR_RW(enable_sdev_max_qd);
अटल DEVICE_ATTR_RO(dump_प्रणाली_regs);
अटल DEVICE_ATTR_RO(raid_map_id);

अटल काष्ठा device_attribute *megaraid_host_attrs[] = अणु
	&dev_attr_fw_crash_buffer_size,
	&dev_attr_fw_crash_buffer,
	&dev_attr_fw_crash_state,
	&dev_attr_page_size,
	&dev_attr_ldio_outstanding,
	&dev_attr_fw_cmds_outstanding,
	&dev_attr_enable_sdev_max_qd,
	&dev_attr_dump_प्रणाली_regs,
	&dev_attr_raid_map_id,
	शून्य,
पूर्ण;

/*
 * Scsi host ढाँचा क्रम megaraid_sas driver
 */
अटल काष्ठा scsi_host_ढाँचा megasas_ढाँचा = अणु

	.module = THIS_MODULE,
	.name = "Avago SAS based MegaRAID driver",
	.proc_name = "megaraid_sas",
	.slave_configure = megasas_slave_configure,
	.slave_alloc = megasas_slave_alloc,
	.slave_destroy = megasas_slave_destroy,
	.queuecommand = megasas_queue_command,
	.eh_target_reset_handler = megasas_reset_target,
	.eh_पात_handler = megasas_task_पात,
	.eh_host_reset_handler = megasas_reset_bus_host,
	.eh_समयd_out = megasas_reset_समयr,
	.shost_attrs = megaraid_host_attrs,
	.bios_param = megasas_bios_param,
	.map_queues = megasas_map_queues,
	.mq_poll = megasas_blk_mq_poll,
	.change_queue_depth = scsi_change_queue_depth,
	.max_segment_size = 0xffffffff,
पूर्ण;

/**
 * megasas_complete_पूर्णांक_cmd -	Completes an पूर्णांकernal command
 * @instance:			Adapter soft state
 * @cmd:			Command to be completed
 *
 * The megasas_issue_blocked_cmd() function रुकोs क्रम a command to complete
 * after it issues a command. This function wakes up that रुकोing routine by
 * calling wake_up() on the रुको queue.
 */
अटल व्योम
megasas_complete_पूर्णांक_cmd(काष्ठा megasas_instance *instance,
			 काष्ठा megasas_cmd *cmd)
अणु
	अगर (cmd->cmd_status_drv == DCMD_INIT)
		cmd->cmd_status_drv =
		(cmd->frame->io.cmd_status == MFI_STAT_OK) ?
		DCMD_SUCCESS : DCMD_FAILED;

	wake_up(&instance->पूर्णांक_cmd_रुको_q);
पूर्ण

/**
 * megasas_complete_पात -	Completes पातing a command
 * @instance:			Adapter soft state
 * @cmd:			Cmd that was issued to पात another cmd
 *
 * The megasas_issue_blocked_पात_cmd() function रुकोs on पात_cmd_रुको_q
 * after it issues an पात on a previously issued command. This function
 * wakes up all functions रुकोing on the same रुको queue.
 */
अटल व्योम
megasas_complete_पात(काष्ठा megasas_instance *instance,
		       काष्ठा megasas_cmd *cmd)
अणु
	अगर (cmd->sync_cmd) अणु
		cmd->sync_cmd = 0;
		cmd->cmd_status_drv = DCMD_SUCCESS;
		wake_up(&instance->पात_cmd_रुको_q);
	पूर्ण
पूर्ण

/**
 * megasas_complete_cmd -	Completes a command
 * @instance:			Adapter soft state
 * @cmd:			Command to be completed
 * @alt_status:			If non-zero, use this value as status to
 *				SCSI mid-layer instead of the value वापसed
 *				by the FW. This should be used अगर caller wants
 *				an alternate status (as in the हाल of पातed
 *				commands)
 */
व्योम
megasas_complete_cmd(काष्ठा megasas_instance *instance, काष्ठा megasas_cmd *cmd,
		     u8 alt_status)
अणु
	पूर्णांक exception = 0;
	काष्ठा megasas_header *hdr = &cmd->frame->hdr;
	अचिन्हित दीर्घ flags;
	काष्ठा fusion_context *fusion = instance->ctrl_context;
	u32 opcode, status;

	/* flag क्रम the retry reset */
	cmd->retry_क्रम_fw_reset = 0;

	अगर (cmd->scmd)
		cmd->scmd->SCp.ptr = शून्य;

	चयन (hdr->cmd) अणु
	हाल MFI_CMD_INVALID:
		/* Some older 1068 controller FW may keep a pended
		   MR_DCMD_CTRL_EVENT_GET_INFO left over from the मुख्य kernel
		   when booting the kdump kernel.  Ignore this command to
		   prevent a kernel panic on shutकरोwn of the kdump kernel. */
		dev_warn(&instance->pdev->dev, "MFI_CMD_INVALID command "
		       "completed\n");
		dev_warn(&instance->pdev->dev, "If you have a controller "
		       "other than PERC5, please upgrade your firmware\n");
		अवरोध;
	हाल MFI_CMD_PD_SCSI_IO:
	हाल MFI_CMD_LD_SCSI_IO:

		/*
		 * MFI_CMD_PD_SCSI_IO and MFI_CMD_LD_SCSI_IO could have been
		 * issued either through an IO path or an IOCTL path. If it
		 * was via IOCTL, we will send it to पूर्णांकernal completion.
		 */
		अगर (cmd->sync_cmd) अणु
			cmd->sync_cmd = 0;
			megasas_complete_पूर्णांक_cmd(instance, cmd);
			अवरोध;
		पूर्ण
		fallthrough;

	हाल MFI_CMD_LD_READ:
	हाल MFI_CMD_LD_WRITE:

		अगर (alt_status) अणु
			cmd->scmd->result = alt_status << 16;
			exception = 1;
		पूर्ण

		अगर (exception) अणु

			atomic_dec(&instance->fw_outstanding);

			scsi_dma_unmap(cmd->scmd);
			cmd->scmd->scsi_करोne(cmd->scmd);
			megasas_वापस_cmd(instance, cmd);

			अवरोध;
		पूर्ण

		चयन (hdr->cmd_status) अणु

		हाल MFI_STAT_OK:
			cmd->scmd->result = DID_OK << 16;
			अवरोध;

		हाल MFI_STAT_SCSI_IO_FAILED:
		हाल MFI_STAT_LD_INIT_IN_PROGRESS:
			cmd->scmd->result =
			    (DID_ERROR << 16) | hdr->scsi_status;
			अवरोध;

		हाल MFI_STAT_SCSI_DONE_WITH_ERROR:

			cmd->scmd->result = (DID_OK << 16) | hdr->scsi_status;

			अगर (hdr->scsi_status == SAM_STAT_CHECK_CONDITION) अणु
				स_रखो(cmd->scmd->sense_buffer, 0,
				       SCSI_SENSE_BUFFERSIZE);
				स_नकल(cmd->scmd->sense_buffer, cmd->sense,
				       hdr->sense_len);

				cmd->scmd->result |= DRIVER_SENSE << 24;
			पूर्ण

			अवरोध;

		हाल MFI_STAT_LD_OFFLINE:
		हाल MFI_STAT_DEVICE_NOT_FOUND:
			cmd->scmd->result = DID_BAD_TARGET << 16;
			अवरोध;

		शेष:
			dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "MFI FW status %#x\n",
			       hdr->cmd_status);
			cmd->scmd->result = DID_ERROR << 16;
			अवरोध;
		पूर्ण

		atomic_dec(&instance->fw_outstanding);

		scsi_dma_unmap(cmd->scmd);
		cmd->scmd->scsi_करोne(cmd->scmd);
		megasas_वापस_cmd(instance, cmd);

		अवरोध;

	हाल MFI_CMD_SMP:
	हाल MFI_CMD_STP:
	हाल MFI_CMD_NVME:
	हाल MFI_CMD_TOOLBOX:
		megasas_complete_पूर्णांक_cmd(instance, cmd);
		अवरोध;

	हाल MFI_CMD_DCMD:
		opcode = le32_to_cpu(cmd->frame->dcmd.opcode);
		/* Check क्रम LD map update */
		अगर ((opcode == MR_DCMD_LD_MAP_GET_INFO)
			&& (cmd->frame->dcmd.mbox.b[1] == 1)) अणु
			fusion->fast_path_io = 0;
			spin_lock_irqsave(instance->host->host_lock, flags);
			status = cmd->frame->hdr.cmd_status;
			instance->map_update_cmd = शून्य;
			अगर (status != MFI_STAT_OK) अणु
				अगर (status != MFI_STAT_NOT_FOUND)
					dev_warn(&instance->pdev->dev, "map syncfailed, status = 0x%x\n",
					       cmd->frame->hdr.cmd_status);
				अन्यथा अणु
					megasas_वापस_cmd(instance, cmd);
					spin_unlock_irqrestore(
						instance->host->host_lock,
						flags);
					अवरोध;
				पूर्ण
			पूर्ण

			megasas_वापस_cmd(instance, cmd);

			/*
			 * Set fast path IO to ZERO.
			 * Validate Map will set proper value.
			 * Meanजबतक all IOs will go as LD IO.
			 */
			अगर (status == MFI_STAT_OK &&
			    (MR_ValidateMapInfo(instance, (instance->map_id + 1)))) अणु
				instance->map_id++;
				fusion->fast_path_io = 1;
			पूर्ण अन्यथा अणु
				fusion->fast_path_io = 0;
			पूर्ण

			megasas_sync_map_info(instance);
			spin_unlock_irqrestore(instance->host->host_lock,
					       flags);
			अवरोध;
		पूर्ण
		अगर (opcode == MR_DCMD_CTRL_EVENT_GET_INFO ||
		    opcode == MR_DCMD_CTRL_EVENT_GET) अणु
			spin_lock_irqsave(&poll_aen_lock, flags);
			megasas_poll_रुको_aen = 0;
			spin_unlock_irqrestore(&poll_aen_lock, flags);
		पूर्ण

		/* FW has an updated PD sequence */
		अगर ((opcode == MR_DCMD_SYSTEM_PD_MAP_GET_INFO) &&
			(cmd->frame->dcmd.mbox.b[0] == 1)) अणु

			spin_lock_irqsave(instance->host->host_lock, flags);
			status = cmd->frame->hdr.cmd_status;
			instance->jbod_seq_cmd = शून्य;
			megasas_वापस_cmd(instance, cmd);

			अगर (status == MFI_STAT_OK) अणु
				instance->pd_seq_map_id++;
				/* Re-रेजिस्टर a pd sync seq num cmd */
				अगर (megasas_sync_pd_seq_num(instance, true))
					instance->use_seqnum_jbod_fp = false;
			पूर्ण अन्यथा
				instance->use_seqnum_jbod_fp = false;

			spin_unlock_irqrestore(instance->host->host_lock, flags);
			अवरोध;
		पूर्ण

		/*
		 * See अगर got an event notअगरication
		 */
		अगर (opcode == MR_DCMD_CTRL_EVENT_WAIT)
			megasas_service_aen(instance, cmd);
		अन्यथा
			megasas_complete_पूर्णांक_cmd(instance, cmd);

		अवरोध;

	हाल MFI_CMD_ABORT:
		/*
		 * Cmd issued to पात another cmd वापसed
		 */
		megasas_complete_पात(instance, cmd);
		अवरोध;

	शेष:
		dev_info(&instance->pdev->dev, "Unknown command completed! [0x%X]\n",
		       hdr->cmd);
		megasas_complete_पूर्णांक_cmd(instance, cmd);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * megasas_issue_pending_cmds_again -	issue all pending cmds
 *					in FW again because of the fw reset
 * @instance:				Adapter soft state
 */
अटल अंतरभूत व्योम
megasas_issue_pending_cmds_again(काष्ठा megasas_instance *instance)
अणु
	काष्ठा megasas_cmd *cmd;
	काष्ठा list_head clist_local;
	जोड़ megasas_evt_class_locale class_locale;
	अचिन्हित दीर्घ flags;
	u32 seq_num;

	INIT_LIST_HEAD(&clist_local);
	spin_lock_irqsave(&instance->hba_lock, flags);
	list_splice_init(&instance->पूर्णांकernal_reset_pending_q, &clist_local);
	spin_unlock_irqrestore(&instance->hba_lock, flags);

	जबतक (!list_empty(&clist_local)) अणु
		cmd = list_entry((&clist_local)->next,
					काष्ठा megasas_cmd, list);
		list_del_init(&cmd->list);

		अगर (cmd->sync_cmd || cmd->scmd) अणु
			dev_notice(&instance->pdev->dev, "command %p, %p:%d"
				"detected to be pending while HBA reset\n",
					cmd, cmd->scmd, cmd->sync_cmd);

			cmd->retry_क्रम_fw_reset++;

			अगर (cmd->retry_क्रम_fw_reset == 3) अणु
				dev_notice(&instance->pdev->dev, "cmd %p, %p:%d"
					"was tried multiple times during reset."
					"Shutting down the HBA\n",
					cmd, cmd->scmd, cmd->sync_cmd);
				instance->instancet->disable_पूर्णांकr(instance);
				atomic_set(&instance->fw_reset_no_pci_access, 1);
				megaraid_sas_समाप्त_hba(instance);
				वापस;
			पूर्ण
		पूर्ण

		अगर (cmd->sync_cmd == 1) अणु
			अगर (cmd->scmd) अणु
				dev_notice(&instance->pdev->dev, "unexpected"
					"cmd attached to internal command!\n");
			पूर्ण
			dev_notice(&instance->pdev->dev, "%p synchronous cmd"
						"on the internal reset queue,"
						"issue it again.\n", cmd);
			cmd->cmd_status_drv = DCMD_INIT;
			instance->instancet->fire_cmd(instance,
							cmd->frame_phys_addr,
							0, instance->reg_set);
		पूर्ण अन्यथा अगर (cmd->scmd) अणु
			dev_notice(&instance->pdev->dev, "%p scsi cmd [%02x]"
			"detected on the internal queue, issue again.\n",
			cmd, cmd->scmd->cmnd[0]);

			atomic_inc(&instance->fw_outstanding);
			instance->instancet->fire_cmd(instance,
					cmd->frame_phys_addr,
					cmd->frame_count-1, instance->reg_set);
		पूर्ण अन्यथा अणु
			dev_notice(&instance->pdev->dev, "%p unexpected cmd on the"
				"internal reset defer list while re-issue!!\n",
				cmd);
		पूर्ण
	पूर्ण

	अगर (instance->aen_cmd) अणु
		dev_notice(&instance->pdev->dev, "aen_cmd in def process\n");
		megasas_वापस_cmd(instance, instance->aen_cmd);

		instance->aen_cmd = शून्य;
	पूर्ण

	/*
	 * Initiate AEN (Asynchronous Event Notअगरication)
	 */
	seq_num = instance->last_seq_num;
	class_locale.members.reserved = 0;
	class_locale.members.locale = MR_EVT_LOCALE_ALL;
	class_locale.members.class = MR_EVT_CLASS_DEBUG;

	megasas_रेजिस्टर_aen(instance, seq_num, class_locale.word);
पूर्ण

/*
 * Move the पूर्णांकernal reset pending commands to a deferred queue.
 *
 * We move the commands pending at पूर्णांकernal reset समय to a
 * pending queue. This queue would be flushed after successful
 * completion of the पूर्णांकernal reset sequence. अगर the पूर्णांकernal reset
 * did not complete in समय, the kernel reset handler would flush
 * these commands.
 */
अटल व्योम
megasas_पूर्णांकernal_reset_defer_cmds(काष्ठा megasas_instance *instance)
अणु
	काष्ठा megasas_cmd *cmd;
	पूर्णांक i;
	u16 max_cmd = instance->max_fw_cmds;
	u32 defer_index;
	अचिन्हित दीर्घ flags;

	defer_index = 0;
	spin_lock_irqsave(&instance->mfi_pool_lock, flags);
	क्रम (i = 0; i < max_cmd; i++) अणु
		cmd = instance->cmd_list[i];
		अगर (cmd->sync_cmd == 1 || cmd->scmd) अणु
			dev_notice(&instance->pdev->dev, "moving cmd[%d]:%p:%d:%p"
					"on the defer queue as internal\n",
				defer_index, cmd, cmd->sync_cmd, cmd->scmd);

			अगर (!list_empty(&cmd->list)) अणु
				dev_notice(&instance->pdev->dev, "ERROR while"
					" moving this cmd:%p, %d %p, it was"
					"discovered on some list?\n",
					cmd, cmd->sync_cmd, cmd->scmd);

				list_del_init(&cmd->list);
			पूर्ण
			defer_index++;
			list_add_tail(&cmd->list,
				&instance->पूर्णांकernal_reset_pending_q);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&instance->mfi_pool_lock, flags);
पूर्ण


अटल व्योम
process_fw_state_change_wq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा megasas_instance *instance =
		container_of(work, काष्ठा megasas_instance, work_init);
	u32 रुको;
	अचिन्हित दीर्घ flags;

    अगर (atomic_पढ़ो(&instance->adprecovery) != MEGASAS_ADPRESET_SM_INFAULT) अणु
		dev_notice(&instance->pdev->dev, "error, recovery st %x\n",
				atomic_पढ़ो(&instance->adprecovery));
		वापस ;
	पूर्ण

	अगर (atomic_पढ़ो(&instance->adprecovery) == MEGASAS_ADPRESET_SM_INFAULT) अणु
		dev_notice(&instance->pdev->dev, "FW detected to be in fault"
					"state, restarting it...\n");

		instance->instancet->disable_पूर्णांकr(instance);
		atomic_set(&instance->fw_outstanding, 0);

		atomic_set(&instance->fw_reset_no_pci_access, 1);
		instance->instancet->adp_reset(instance, instance->reg_set);
		atomic_set(&instance->fw_reset_no_pci_access, 0);

		dev_notice(&instance->pdev->dev, "FW restarted successfully,"
					"initiating next stage...\n");

		dev_notice(&instance->pdev->dev, "HBA recovery state machine,"
					"state 2 starting...\n");

		/* रुकोing क्रम about 20 second beक्रमe start the second init */
		क्रम (रुको = 0; रुको < 30; रुको++) अणु
			msleep(1000);
		पूर्ण

		अगर (megasas_transition_to_पढ़ोy(instance, 1)) अणु
			dev_notice(&instance->pdev->dev, "adapter not ready\n");

			atomic_set(&instance->fw_reset_no_pci_access, 1);
			megaraid_sas_समाप्त_hba(instance);
			वापस ;
		पूर्ण

		अगर ((instance->pdev->device == PCI_DEVICE_ID_LSI_SAS1064R) ||
			(instance->pdev->device == PCI_DEVICE_ID_DELL_PERC5) ||
			(instance->pdev->device == PCI_DEVICE_ID_LSI_VERDE_ZCR)
			) अणु
			*instance->consumer = *instance->producer;
		पूर्ण अन्यथा अणु
			*instance->consumer = 0;
			*instance->producer = 0;
		पूर्ण

		megasas_issue_init_mfi(instance);

		spin_lock_irqsave(&instance->hba_lock, flags);
		atomic_set(&instance->adprecovery, MEGASAS_HBA_OPERATIONAL);
		spin_unlock_irqrestore(&instance->hba_lock, flags);
		instance->instancet->enable_पूर्णांकr(instance);

		megasas_issue_pending_cmds_again(instance);
		instance->issuepend_करोne = 1;
	पूर्ण
पूर्ण

/**
 * megasas_deplete_reply_queue -	Processes all completed commands
 * @instance:				Adapter soft state
 * @alt_status:				Alternate status to be वापसed to
 *					SCSI mid-layer instead of the status
 *					वापसed by the FW
 * Note: this must be called with hba lock held
 */
अटल पूर्णांक
megasas_deplete_reply_queue(काष्ठा megasas_instance *instance,
					u8 alt_status)
अणु
	u32 mfiStatus;
	u32 fw_state;

	अगर ((mfiStatus = instance->instancet->check_reset(instance,
					instance->reg_set)) == 1) अणु
		वापस IRQ_HANDLED;
	पूर्ण

	mfiStatus = instance->instancet->clear_पूर्णांकr(instance);
	अगर (mfiStatus == 0) अणु
		/* Hardware may not set outbound_पूर्णांकr_status in MSI-X mode */
		अगर (!instance->msix_vectors)
			वापस IRQ_NONE;
	पूर्ण

	instance->mfiStatus = mfiStatus;

	अगर ((mfiStatus & MFI_INTR_FLAG_FIRMWARE_STATE_CHANGE)) अणु
		fw_state = instance->instancet->पढ़ो_fw_status_reg(
				instance) & MFI_STATE_MASK;

		अगर (fw_state != MFI_STATE_FAULT) अणु
			dev_notice(&instance->pdev->dev, "fw state:%x\n",
						fw_state);
		पूर्ण

		अगर ((fw_state == MFI_STATE_FAULT) &&
				(instance->disableOnlineCtrlReset == 0)) अणु
			dev_notice(&instance->pdev->dev, "wait adp restart\n");

			अगर ((instance->pdev->device ==
					PCI_DEVICE_ID_LSI_SAS1064R) ||
				(instance->pdev->device ==
					PCI_DEVICE_ID_DELL_PERC5) ||
				(instance->pdev->device ==
					PCI_DEVICE_ID_LSI_VERDE_ZCR)) अणु

				*instance->consumer =
					cpu_to_le32(MEGASAS_ADPRESET_INPROG_SIGN);
			पूर्ण


			instance->instancet->disable_पूर्णांकr(instance);
			atomic_set(&instance->adprecovery, MEGASAS_ADPRESET_SM_INFAULT);
			instance->issuepend_करोne = 0;

			atomic_set(&instance->fw_outstanding, 0);
			megasas_पूर्णांकernal_reset_defer_cmds(instance);

			dev_notice(&instance->pdev->dev, "fwState=%x, stage:%d\n",
					fw_state, atomic_पढ़ो(&instance->adprecovery));

			schedule_work(&instance->work_init);
			वापस IRQ_HANDLED;

		पूर्ण अन्यथा अणु
			dev_notice(&instance->pdev->dev, "fwstate:%x, dis_OCR=%x\n",
				fw_state, instance->disableOnlineCtrlReset);
		पूर्ण
	पूर्ण

	tasklet_schedule(&instance->isr_tasklet);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * megasas_isr - isr entry poपूर्णांक
 * @irq:	IRQ number
 * @devp:	IRQ context address
 */
अटल irqवापस_t megasas_isr(पूर्णांक irq, व्योम *devp)
अणु
	काष्ठा megasas_irq_context *irq_context = devp;
	काष्ठा megasas_instance *instance = irq_context->instance;
	अचिन्हित दीर्घ flags;
	irqवापस_t rc;

	अगर (atomic_पढ़ो(&instance->fw_reset_no_pci_access))
		वापस IRQ_HANDLED;

	spin_lock_irqsave(&instance->hba_lock, flags);
	rc = megasas_deplete_reply_queue(instance, DID_OK);
	spin_unlock_irqrestore(&instance->hba_lock, flags);

	वापस rc;
पूर्ण

/**
 * megasas_transition_to_पढ़ोy -	Move the FW to READY state
 * @instance:				Adapter soft state
 * @ocr:				Adapter reset state
 *
 * During the initialization, FW passes can potentially be in any one of
 * several possible states. If the FW in operational, रुकोing-क्रम-handshake
 * states, driver must take steps to bring it to पढ़ोy state. Otherwise, it
 * has to रुको क्रम the पढ़ोy state.
 */
पूर्णांक
megasas_transition_to_पढ़ोy(काष्ठा megasas_instance *instance, पूर्णांक ocr)
अणु
	पूर्णांक i;
	u8 max_रुको;
	u32 fw_state;
	u32 असल_state, curr_असल_state;

	असल_state = instance->instancet->पढ़ो_fw_status_reg(instance);
	fw_state = असल_state & MFI_STATE_MASK;

	अगर (fw_state != MFI_STATE_READY)
		dev_info(&instance->pdev->dev, "Waiting for FW to come to ready"
		       " state\n");

	जबतक (fw_state != MFI_STATE_READY) अणु

		चयन (fw_state) अणु

		हाल MFI_STATE_FAULT:
			dev_prपूर्णांकk(KERN_ERR, &instance->pdev->dev,
				   "FW in FAULT state, Fault code:0x%x subcode:0x%x func:%s\n",
				   असल_state & MFI_STATE_FAULT_CODE,
				   असल_state & MFI_STATE_FAULT_SUBCODE, __func__);
			अगर (ocr) अणु
				max_रुको = MEGASAS_RESET_WAIT_TIME;
				अवरोध;
			पूर्ण अन्यथा अणु
				dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "System Register set:\n");
				megasas_dump_reg_set(instance->reg_set);
				वापस -ENODEV;
			पूर्ण

		हाल MFI_STATE_WAIT_HANDSHAKE:
			/*
			 * Set the CLR bit in inbound करोorbell
			 */
			अगर ((instance->pdev->device ==
				PCI_DEVICE_ID_LSI_SAS0073SKINNY) ||
				(instance->pdev->device ==
				 PCI_DEVICE_ID_LSI_SAS0071SKINNY) ||
				(instance->adapter_type != MFI_SERIES))
				ग_लिखोl(
				  MFI_INIT_CLEAR_HANDSHAKE|MFI_INIT_HOTPLUG,
				  &instance->reg_set->करोorbell);
			अन्यथा
				ग_लिखोl(
				    MFI_INIT_CLEAR_HANDSHAKE|MFI_INIT_HOTPLUG,
					&instance->reg_set->inbound_करोorbell);

			max_रुको = MEGASAS_RESET_WAIT_TIME;
			अवरोध;

		हाल MFI_STATE_BOOT_MESSAGE_PENDING:
			अगर ((instance->pdev->device ==
			     PCI_DEVICE_ID_LSI_SAS0073SKINNY) ||
				(instance->pdev->device ==
				 PCI_DEVICE_ID_LSI_SAS0071SKINNY) ||
				(instance->adapter_type != MFI_SERIES))
				ग_लिखोl(MFI_INIT_HOTPLUG,
				       &instance->reg_set->करोorbell);
			अन्यथा
				ग_लिखोl(MFI_INIT_HOTPLUG,
					&instance->reg_set->inbound_करोorbell);

			max_रुको = MEGASAS_RESET_WAIT_TIME;
			अवरोध;

		हाल MFI_STATE_OPERATIONAL:
			/*
			 * Bring it to READY state; assuming max रुको 10 secs
			 */
			instance->instancet->disable_पूर्णांकr(instance);
			अगर ((instance->pdev->device ==
				PCI_DEVICE_ID_LSI_SAS0073SKINNY) ||
				(instance->pdev->device ==
				PCI_DEVICE_ID_LSI_SAS0071SKINNY)  ||
				(instance->adapter_type != MFI_SERIES)) अणु
				ग_लिखोl(MFI_RESET_FLAGS,
					&instance->reg_set->करोorbell);

				अगर (instance->adapter_type != MFI_SERIES) अणु
					क्रम (i = 0; i < (10 * 1000); i += 20) अणु
						अगर (megasas_पढ़ोl(
							    instance,
							    &instance->
							    reg_set->
							    करोorbell) & 1)
							msleep(20);
						अन्यथा
							अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा
				ग_लिखोl(MFI_RESET_FLAGS,
					&instance->reg_set->inbound_करोorbell);

			max_रुको = MEGASAS_RESET_WAIT_TIME;
			अवरोध;

		हाल MFI_STATE_UNDEFINED:
			/*
			 * This state should not last क्रम more than 2 seconds
			 */
			max_रुको = MEGASAS_RESET_WAIT_TIME;
			अवरोध;

		हाल MFI_STATE_BB_INIT:
			max_रुको = MEGASAS_RESET_WAIT_TIME;
			अवरोध;

		हाल MFI_STATE_FW_INIT:
			max_रुको = MEGASAS_RESET_WAIT_TIME;
			अवरोध;

		हाल MFI_STATE_FW_INIT_2:
			max_रुको = MEGASAS_RESET_WAIT_TIME;
			अवरोध;

		हाल MFI_STATE_DEVICE_SCAN:
			max_रुको = MEGASAS_RESET_WAIT_TIME;
			अवरोध;

		हाल MFI_STATE_FLUSH_CACHE:
			max_रुको = MEGASAS_RESET_WAIT_TIME;
			अवरोध;

		शेष:
			dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "Unknown state 0x%x\n",
			       fw_state);
			dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "System Register set:\n");
			megasas_dump_reg_set(instance->reg_set);
			वापस -ENODEV;
		पूर्ण

		/*
		 * The cur_state should not last क्रम more than max_रुको secs
		 */
		क्रम (i = 0; i < max_रुको * 50; i++) अणु
			curr_असल_state = instance->instancet->
				पढ़ो_fw_status_reg(instance);

			अगर (असल_state == curr_असल_state) अणु
				msleep(20);
			पूर्ण अन्यथा
				अवरोध;
		पूर्ण

		/*
		 * Return error अगर fw_state hasn't changed after max_रुको
		 */
		अगर (curr_असल_state == असल_state) अणु
			dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "FW state [%d] hasn't changed "
			       "in %d secs\n", fw_state, max_रुको);
			dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "System Register set:\n");
			megasas_dump_reg_set(instance->reg_set);
			वापस -ENODEV;
		पूर्ण

		असल_state = curr_असल_state;
		fw_state = curr_असल_state & MFI_STATE_MASK;
	पूर्ण
	dev_info(&instance->pdev->dev, "FW now in Ready state\n");

	वापस 0;
पूर्ण

/**
 * megasas_tearकरोwn_frame_pool -	Destroy the cmd frame DMA pool
 * @instance:				Adapter soft state
 */
अटल व्योम megasas_tearकरोwn_frame_pool(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक i;
	u16 max_cmd = instance->max_mfi_cmds;
	काष्ठा megasas_cmd *cmd;

	अगर (!instance->frame_dma_pool)
		वापस;

	/*
	 * Return all frames to pool
	 */
	क्रम (i = 0; i < max_cmd; i++) अणु

		cmd = instance->cmd_list[i];

		अगर (cmd->frame)
			dma_pool_मुक्त(instance->frame_dma_pool, cmd->frame,
				      cmd->frame_phys_addr);

		अगर (cmd->sense)
			dma_pool_मुक्त(instance->sense_dma_pool, cmd->sense,
				      cmd->sense_phys_addr);
	पूर्ण

	/*
	 * Now destroy the pool itself
	 */
	dma_pool_destroy(instance->frame_dma_pool);
	dma_pool_destroy(instance->sense_dma_pool);

	instance->frame_dma_pool = शून्य;
	instance->sense_dma_pool = शून्य;
पूर्ण

/**
 * megasas_create_frame_pool -	Creates DMA pool क्रम cmd frames
 * @instance:			Adapter soft state
 *
 * Each command packet has an embedded DMA memory buffer that is used क्रम
 * filling MFI frame and the SG list that immediately follows the frame. This
 * function creates those DMA memory buffers क्रम each command packet by using
 * PCI pool facility.
 */
अटल पूर्णांक megasas_create_frame_pool(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक i;
	u16 max_cmd;
	u32 frame_count;
	काष्ठा megasas_cmd *cmd;

	max_cmd = instance->max_mfi_cmds;

	/*
	 * For MFI controllers.
	 * max_num_sge = 60
	 * max_sge_sz  = 16 byte (माप megasas_sge_skinny)
	 * Total 960 byte (15 MFI frame of 64 byte)
	 *
	 * Fusion adapter require only 3 extra frame.
	 * max_num_sge = 16 (defined as MAX_IOCTL_SGE)
	 * max_sge_sz  = 12 byte (माप  megasas_sge64)
	 * Total 192 byte (3 MFI frame of 64 byte)
	 */
	frame_count = (instance->adapter_type == MFI_SERIES) ?
			(15 + 1) : (3 + 1);
	instance->mfi_frame_size = MEGAMFI_FRAME_SIZE * frame_count;
	/*
	 * Use DMA pool facility provided by PCI layer
	 */
	instance->frame_dma_pool = dma_pool_create("megasas frame pool",
					&instance->pdev->dev,
					instance->mfi_frame_size, 256, 0);

	अगर (!instance->frame_dma_pool) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "failed to setup frame pool\n");
		वापस -ENOMEM;
	पूर्ण

	instance->sense_dma_pool = dma_pool_create("megasas sense pool",
						   &instance->pdev->dev, 128,
						   4, 0);

	अगर (!instance->sense_dma_pool) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "failed to setup sense pool\n");

		dma_pool_destroy(instance->frame_dma_pool);
		instance->frame_dma_pool = शून्य;

		वापस -ENOMEM;
	पूर्ण

	/*
	 * Allocate and attach a frame to each of the commands in cmd_list.
	 * By making cmd->index as the context instead of the &cmd, we can
	 * always use 32bit context regardless of the architecture
	 */
	क्रम (i = 0; i < max_cmd; i++) अणु

		cmd = instance->cmd_list[i];

		cmd->frame = dma_pool_zalloc(instance->frame_dma_pool,
					    GFP_KERNEL, &cmd->frame_phys_addr);

		cmd->sense = dma_pool_alloc(instance->sense_dma_pool,
					    GFP_KERNEL, &cmd->sense_phys_addr);

		/*
		 * megasas_tearकरोwn_frame_pool() takes care of मुक्तing
		 * whatever has been allocated
		 */
		अगर (!cmd->frame || !cmd->sense) अणु
			dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "dma_pool_alloc failed\n");
			megasas_tearकरोwn_frame_pool(instance);
			वापस -ENOMEM;
		पूर्ण

		cmd->frame->io.context = cpu_to_le32(cmd->index);
		cmd->frame->io.pad_0 = 0;
		अगर ((instance->adapter_type == MFI_SERIES) && reset_devices)
			cmd->frame->hdr.cmd = MFI_CMD_INVALID;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * megasas_मुक्त_cmds -	Free all the cmds in the मुक्त cmd pool
 * @instance:		Adapter soft state
 */
व्योम megasas_मुक्त_cmds(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक i;

	/* First मुक्त the MFI frame pool */
	megasas_tearकरोwn_frame_pool(instance);

	/* Free all the commands in the cmd_list */
	क्रम (i = 0; i < instance->max_mfi_cmds; i++)

		kमुक्त(instance->cmd_list[i]);

	/* Free the cmd_list buffer itself */
	kमुक्त(instance->cmd_list);
	instance->cmd_list = शून्य;

	INIT_LIST_HEAD(&instance->cmd_pool);
पूर्ण

/**
 * megasas_alloc_cmds -	Allocates the command packets
 * @instance:		Adapter soft state
 *
 * Each command that is issued to the FW, whether IO commands from the OS or
 * पूर्णांकernal commands like IOCTLs, are wrapped in local data काष्ठाure called
 * megasas_cmd. The frame embedded in this megasas_cmd is actually issued to
 * the FW.
 *
 * Each frame has a 32-bit field called context (tag). This context is used
 * to get back the megasas_cmd from the frame when a frame माला_लो completed in
 * the ISR. Typically the address of the megasas_cmd itself would be used as
 * the context. But we wanted to keep the dअगरferences between 32 and 64 bit
 * प्रणालीs to the mininum. We always use 32 bit पूर्णांकegers क्रम the context. In
 * this driver, the 32 bit values are the indices पूर्णांकo an array cmd_list.
 * This array is used only to look up the megasas_cmd given the context. The
 * मुक्त commands themselves are मुख्यtained in a linked list called cmd_pool.
 */
पूर्णांक megasas_alloc_cmds(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक i;
	पूर्णांक j;
	u16 max_cmd;
	काष्ठा megasas_cmd *cmd;

	max_cmd = instance->max_mfi_cmds;

	/*
	 * instance->cmd_list is an array of काष्ठा megasas_cmd poपूर्णांकers.
	 * Allocate the dynamic array first and then allocate inभागidual
	 * commands.
	 */
	instance->cmd_list = kसुस्मृति(max_cmd, माप(काष्ठा megasas_cmd*), GFP_KERNEL);

	अगर (!instance->cmd_list) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "out of memory\n");
		वापस -ENOMEM;
	पूर्ण

	स_रखो(instance->cmd_list, 0, माप(काष्ठा megasas_cmd *) *max_cmd);

	क्रम (i = 0; i < max_cmd; i++) अणु
		instance->cmd_list[i] = kदो_स्मृति(माप(काष्ठा megasas_cmd),
						GFP_KERNEL);

		अगर (!instance->cmd_list[i]) अणु

			क्रम (j = 0; j < i; j++)
				kमुक्त(instance->cmd_list[j]);

			kमुक्त(instance->cmd_list);
			instance->cmd_list = शून्य;

			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < max_cmd; i++) अणु
		cmd = instance->cmd_list[i];
		स_रखो(cmd, 0, माप(काष्ठा megasas_cmd));
		cmd->index = i;
		cmd->scmd = शून्य;
		cmd->instance = instance;

		list_add_tail(&cmd->list, &instance->cmd_pool);
	पूर्ण

	/*
	 * Create a frame pool and assign one frame to each cmd
	 */
	अगर (megasas_create_frame_pool(instance)) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "Error creating frame DMA pool\n");
		megasas_मुक्त_cmds(instance);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * dcmd_समयout_ocr_possible -	Check अगर OCR is possible based on Driver/FW state.
 * @instance:				Adapter soft state
 *
 * Return 0 क्रम only Fusion adapter, अगर driver load/unload is not in progress
 * or FW is not under OCR.
 */
अंतरभूत पूर्णांक
dcmd_समयout_ocr_possible(काष्ठा megasas_instance *instance) अणु

	अगर (instance->adapter_type == MFI_SERIES)
		वापस KILL_ADAPTER;
	अन्यथा अगर (instance->unload ||
			test_bit(MEGASAS_FUSION_OCR_NOT_POSSIBLE,
				 &instance->reset_flags))
		वापस IGNORE_TIMEOUT;
	अन्यथा
		वापस INITIATE_OCR;
पूर्ण

अटल व्योम
megasas_get_pd_info(काष्ठा megasas_instance *instance, काष्ठा scsi_device *sdev)
अणु
	पूर्णांक ret;
	काष्ठा megasas_cmd *cmd;
	काष्ठा megasas_dcmd_frame *dcmd;

	काष्ठा MR_PRIV_DEVICE *mr_device_priv_data;
	u16 device_id = 0;

	device_id = (sdev->channel * MEGASAS_MAX_DEV_PER_CHANNEL) + sdev->id;
	cmd = megasas_get_cmd(instance);

	अगर (!cmd) अणु
		dev_err(&instance->pdev->dev, "Failed to get cmd %s\n", __func__);
		वापस;
	पूर्ण

	dcmd = &cmd->frame->dcmd;

	स_रखो(instance->pd_info, 0, माप(*instance->pd_info));
	स_रखो(dcmd->mbox.b, 0, MFI_MBOX_SIZE);

	dcmd->mbox.s[0] = cpu_to_le16(device_id);
	dcmd->cmd = MFI_CMD_DCMD;
	dcmd->cmd_status = 0xFF;
	dcmd->sge_count = 1;
	dcmd->flags = MFI_FRAME_सूची_READ;
	dcmd->समयout = 0;
	dcmd->pad_0 = 0;
	dcmd->data_xfer_len = cpu_to_le32(माप(काष्ठा MR_PD_INFO));
	dcmd->opcode = cpu_to_le32(MR_DCMD_PD_GET_INFO);

	megasas_set_dma_settings(instance, dcmd, instance->pd_info_h,
				 माप(काष्ठा MR_PD_INFO));

	अगर ((instance->adapter_type != MFI_SERIES) &&
	    !instance->mask_पूर्णांकerrupts)
		ret = megasas_issue_blocked_cmd(instance, cmd, MFI_IO_TIMEOUT_SECS);
	अन्यथा
		ret = megasas_issue_polled(instance, cmd);

	चयन (ret) अणु
	हाल DCMD_SUCCESS:
		mr_device_priv_data = sdev->hostdata;
		le16_to_cpus((u16 *)&instance->pd_info->state.ddf.pdType);
		mr_device_priv_data->पूर्णांकerface_type =
				instance->pd_info->state.ddf.pdType.पूर्णांकf;
		अवरोध;

	हाल DCMD_TIMEOUT:

		चयन (dcmd_समयout_ocr_possible(instance)) अणु
		हाल INITIATE_OCR:
			cmd->flags |= DRV_DCMD_SKIP_REFIRE;
			mutex_unlock(&instance->reset_mutex);
			megasas_reset_fusion(instance->host,
				MFI_IO_TIMEOUT_OCR);
			mutex_lock(&instance->reset_mutex);
			अवरोध;
		हाल KILL_ADAPTER:
			megaraid_sas_समाप्त_hba(instance);
			अवरोध;
		हाल IGNORE_TIMEOUT:
			dev_info(&instance->pdev->dev, "Ignore DCMD timeout: %s %d\n",
				__func__, __LINE__);
			अवरोध;
		पूर्ण

		अवरोध;
	पूर्ण

	अगर (ret != DCMD_TIMEOUT)
		megasas_वापस_cmd(instance, cmd);

	वापस;
पूर्ण
/*
 * megasas_get_pd_list_info -	Returns FW's pd_list काष्ठाure
 * @instance:				Adapter soft state
 * @pd_list:				pd_list काष्ठाure
 *
 * Issues an पूर्णांकernal command (DCMD) to get the FW's controller PD
 * list काष्ठाure.  This inक्रमmation is मुख्यly used to find out SYSTEM
 * supported by the FW.
 */
अटल पूर्णांक
megasas_get_pd_list(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक ret = 0, pd_index = 0;
	काष्ठा megasas_cmd *cmd;
	काष्ठा megasas_dcmd_frame *dcmd;
	काष्ठा MR_PD_LIST *ci;
	काष्ठा MR_PD_ADDRESS *pd_addr;

	अगर (instance->pd_list_not_supported) अणु
		dev_info(&instance->pdev->dev, "MR_DCMD_PD_LIST_QUERY "
		"not supported by firmware\n");
		वापस ret;
	पूर्ण

	ci = instance->pd_list_buf;

	cmd = megasas_get_cmd(instance);

	अगर (!cmd) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "(get_pd_list): Failed to get cmd\n");
		वापस -ENOMEM;
	पूर्ण

	dcmd = &cmd->frame->dcmd;

	स_रखो(ci, 0, माप(*ci));
	स_रखो(dcmd->mbox.b, 0, MFI_MBOX_SIZE);

	dcmd->mbox.b[0] = MR_PD_QUERY_TYPE_EXPOSED_TO_HOST;
	dcmd->mbox.b[1] = 0;
	dcmd->cmd = MFI_CMD_DCMD;
	dcmd->cmd_status = MFI_STAT_INVALID_STATUS;
	dcmd->sge_count = 1;
	dcmd->flags = MFI_FRAME_सूची_READ;
	dcmd->समयout = 0;
	dcmd->pad_0 = 0;
	dcmd->data_xfer_len = cpu_to_le32(MEGASAS_MAX_PD * माप(काष्ठा MR_PD_LIST));
	dcmd->opcode = cpu_to_le32(MR_DCMD_PD_LIST_QUERY);

	megasas_set_dma_settings(instance, dcmd, instance->pd_list_buf_h,
				 (MEGASAS_MAX_PD * माप(काष्ठा MR_PD_LIST)));

	अगर ((instance->adapter_type != MFI_SERIES) &&
	    !instance->mask_पूर्णांकerrupts)
		ret = megasas_issue_blocked_cmd(instance, cmd,
			MFI_IO_TIMEOUT_SECS);
	अन्यथा
		ret = megasas_issue_polled(instance, cmd);

	चयन (ret) अणु
	हाल DCMD_FAILED:
		dev_info(&instance->pdev->dev, "MR_DCMD_PD_LIST_QUERY "
			"failed/not supported by firmware\n");

		अगर (instance->adapter_type != MFI_SERIES)
			megaraid_sas_समाप्त_hba(instance);
		अन्यथा
			instance->pd_list_not_supported = 1;
		अवरोध;
	हाल DCMD_TIMEOUT:

		चयन (dcmd_समयout_ocr_possible(instance)) अणु
		हाल INITIATE_OCR:
			cmd->flags |= DRV_DCMD_SKIP_REFIRE;
			/*
			 * DCMD failed from AEN path.
			 * AEN path alपढ़ोy hold reset_mutex to aव्योम PCI access
			 * जबतक OCR is in progress.
			 */
			mutex_unlock(&instance->reset_mutex);
			megasas_reset_fusion(instance->host,
						MFI_IO_TIMEOUT_OCR);
			mutex_lock(&instance->reset_mutex);
			अवरोध;
		हाल KILL_ADAPTER:
			megaraid_sas_समाप्त_hba(instance);
			अवरोध;
		हाल IGNORE_TIMEOUT:
			dev_info(&instance->pdev->dev, "Ignore DCMD timeout: %s %d \n",
				__func__, __LINE__);
			अवरोध;
		पूर्ण

		अवरोध;

	हाल DCMD_SUCCESS:
		pd_addr = ci->addr;
		अगर (megasas_dbg_lvl & LD_PD_DEBUG)
			dev_info(&instance->pdev->dev, "%s, sysPD count: 0x%x\n",
				 __func__, le32_to_cpu(ci->count));

		अगर ((le32_to_cpu(ci->count) >
			(MEGASAS_MAX_PD_CHANNELS * MEGASAS_MAX_DEV_PER_CHANNEL)))
			अवरोध;

		स_रखो(instance->local_pd_list, 0,
				MEGASAS_MAX_PD * माप(काष्ठा megasas_pd_list));

		क्रम (pd_index = 0; pd_index < le32_to_cpu(ci->count); pd_index++) अणु
			instance->local_pd_list[le16_to_cpu(pd_addr->deviceId)].tid	=
					le16_to_cpu(pd_addr->deviceId);
			instance->local_pd_list[le16_to_cpu(pd_addr->deviceId)].driveType	=
					pd_addr->scsiDevType;
			instance->local_pd_list[le16_to_cpu(pd_addr->deviceId)].driveState	=
					MR_PD_STATE_SYSTEM;
			अगर (megasas_dbg_lvl & LD_PD_DEBUG)
				dev_info(&instance->pdev->dev,
					 "PD%d: targetID: 0x%03x deviceType:0x%x\n",
					 pd_index, le16_to_cpu(pd_addr->deviceId),
					 pd_addr->scsiDevType);
			pd_addr++;
		पूर्ण

		स_नकल(instance->pd_list, instance->local_pd_list,
			माप(instance->pd_list));
		अवरोध;

	पूर्ण

	अगर (ret != DCMD_TIMEOUT)
		megasas_वापस_cmd(instance, cmd);

	वापस ret;
पूर्ण

/*
 * megasas_get_ld_list_info -	Returns FW's ld_list काष्ठाure
 * @instance:				Adapter soft state
 * @ld_list:				ld_list काष्ठाure
 *
 * Issues an पूर्णांकernal command (DCMD) to get the FW's controller PD
 * list काष्ठाure.  This inक्रमmation is मुख्यly used to find out SYSTEM
 * supported by the FW.
 */
अटल पूर्णांक
megasas_get_ld_list(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक ret = 0, ld_index = 0, ids = 0;
	काष्ठा megasas_cmd *cmd;
	काष्ठा megasas_dcmd_frame *dcmd;
	काष्ठा MR_LD_LIST *ci;
	dma_addr_t ci_h = 0;
	u32 ld_count;

	ci = instance->ld_list_buf;
	ci_h = instance->ld_list_buf_h;

	cmd = megasas_get_cmd(instance);

	अगर (!cmd) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "megasas_get_ld_list: Failed to get cmd\n");
		वापस -ENOMEM;
	पूर्ण

	dcmd = &cmd->frame->dcmd;

	स_रखो(ci, 0, माप(*ci));
	स_रखो(dcmd->mbox.b, 0, MFI_MBOX_SIZE);

	अगर (instance->supporपंचांगax256vd)
		dcmd->mbox.b[0] = 1;
	dcmd->cmd = MFI_CMD_DCMD;
	dcmd->cmd_status = MFI_STAT_INVALID_STATUS;
	dcmd->sge_count = 1;
	dcmd->flags = MFI_FRAME_सूची_READ;
	dcmd->समयout = 0;
	dcmd->data_xfer_len = cpu_to_le32(माप(काष्ठा MR_LD_LIST));
	dcmd->opcode = cpu_to_le32(MR_DCMD_LD_GET_LIST);
	dcmd->pad_0  = 0;

	megasas_set_dma_settings(instance, dcmd, ci_h,
				 माप(काष्ठा MR_LD_LIST));

	अगर ((instance->adapter_type != MFI_SERIES) &&
	    !instance->mask_पूर्णांकerrupts)
		ret = megasas_issue_blocked_cmd(instance, cmd,
			MFI_IO_TIMEOUT_SECS);
	अन्यथा
		ret = megasas_issue_polled(instance, cmd);

	ld_count = le32_to_cpu(ci->ldCount);

	चयन (ret) अणु
	हाल DCMD_FAILED:
		megaraid_sas_समाप्त_hba(instance);
		अवरोध;
	हाल DCMD_TIMEOUT:

		चयन (dcmd_समयout_ocr_possible(instance)) अणु
		हाल INITIATE_OCR:
			cmd->flags |= DRV_DCMD_SKIP_REFIRE;
			/*
			 * DCMD failed from AEN path.
			 * AEN path alपढ़ोy hold reset_mutex to aव्योम PCI access
			 * जबतक OCR is in progress.
			 */
			mutex_unlock(&instance->reset_mutex);
			megasas_reset_fusion(instance->host,
						MFI_IO_TIMEOUT_OCR);
			mutex_lock(&instance->reset_mutex);
			अवरोध;
		हाल KILL_ADAPTER:
			megaraid_sas_समाप्त_hba(instance);
			अवरोध;
		हाल IGNORE_TIMEOUT:
			dev_info(&instance->pdev->dev, "Ignore DCMD timeout: %s %d\n",
				__func__, __LINE__);
			अवरोध;
		पूर्ण

		अवरोध;

	हाल DCMD_SUCCESS:
		अगर (megasas_dbg_lvl & LD_PD_DEBUG)
			dev_info(&instance->pdev->dev, "%s, LD count: 0x%x\n",
				 __func__, ld_count);

		अगर (ld_count > instance->fw_supported_vd_count)
			अवरोध;

		स_रखो(instance->ld_ids, 0xff, MAX_LOGICAL_DRIVES_EXT);

		क्रम (ld_index = 0; ld_index < ld_count; ld_index++) अणु
			अगर (ci->ldList[ld_index].state != 0) अणु
				ids = ci->ldList[ld_index].ref.targetId;
				instance->ld_ids[ids] = ci->ldList[ld_index].ref.targetId;
				अगर (megasas_dbg_lvl & LD_PD_DEBUG)
					dev_info(&instance->pdev->dev,
						 "LD%d: targetID: 0x%03x\n",
						 ld_index, ids);
			पूर्ण
		पूर्ण

		अवरोध;
	पूर्ण

	अगर (ret != DCMD_TIMEOUT)
		megasas_वापस_cmd(instance, cmd);

	वापस ret;
पूर्ण

/**
 * megasas_ld_list_query -	Returns FW's ld_list काष्ठाure
 * @instance:				Adapter soft state
 * @query_type:				ld_list काष्ठाure type
 *
 * Issues an पूर्णांकernal command (DCMD) to get the FW's controller PD
 * list काष्ठाure.  This inक्रमmation is मुख्यly used to find out SYSTEM
 * supported by the FW.
 */
अटल पूर्णांक
megasas_ld_list_query(काष्ठा megasas_instance *instance, u8 query_type)
अणु
	पूर्णांक ret = 0, ld_index = 0, ids = 0;
	काष्ठा megasas_cmd *cmd;
	काष्ठा megasas_dcmd_frame *dcmd;
	काष्ठा MR_LD_TARGETID_LIST *ci;
	dma_addr_t ci_h = 0;
	u32 tgtid_count;

	ci = instance->ld_targetid_list_buf;
	ci_h = instance->ld_targetid_list_buf_h;

	cmd = megasas_get_cmd(instance);

	अगर (!cmd) अणु
		dev_warn(&instance->pdev->dev,
		         "megasas_ld_list_query: Failed to get cmd\n");
		वापस -ENOMEM;
	पूर्ण

	dcmd = &cmd->frame->dcmd;

	स_रखो(ci, 0, माप(*ci));
	स_रखो(dcmd->mbox.b, 0, MFI_MBOX_SIZE);

	dcmd->mbox.b[0] = query_type;
	अगर (instance->supporपंचांगax256vd)
		dcmd->mbox.b[2] = 1;

	dcmd->cmd = MFI_CMD_DCMD;
	dcmd->cmd_status = MFI_STAT_INVALID_STATUS;
	dcmd->sge_count = 1;
	dcmd->flags = MFI_FRAME_सूची_READ;
	dcmd->समयout = 0;
	dcmd->data_xfer_len = cpu_to_le32(माप(काष्ठा MR_LD_TARGETID_LIST));
	dcmd->opcode = cpu_to_le32(MR_DCMD_LD_LIST_QUERY);
	dcmd->pad_0  = 0;

	megasas_set_dma_settings(instance, dcmd, ci_h,
				 माप(काष्ठा MR_LD_TARGETID_LIST));

	अगर ((instance->adapter_type != MFI_SERIES) &&
	    !instance->mask_पूर्णांकerrupts)
		ret = megasas_issue_blocked_cmd(instance, cmd, MFI_IO_TIMEOUT_SECS);
	अन्यथा
		ret = megasas_issue_polled(instance, cmd);

	चयन (ret) अणु
	हाल DCMD_FAILED:
		dev_info(&instance->pdev->dev,
			"DCMD not supported by firmware - %s %d\n",
				__func__, __LINE__);
		ret = megasas_get_ld_list(instance);
		अवरोध;
	हाल DCMD_TIMEOUT:
		चयन (dcmd_समयout_ocr_possible(instance)) अणु
		हाल INITIATE_OCR:
			cmd->flags |= DRV_DCMD_SKIP_REFIRE;
			/*
			 * DCMD failed from AEN path.
			 * AEN path alपढ़ोy hold reset_mutex to aव्योम PCI access
			 * जबतक OCR is in progress.
			 */
			mutex_unlock(&instance->reset_mutex);
			megasas_reset_fusion(instance->host,
						MFI_IO_TIMEOUT_OCR);
			mutex_lock(&instance->reset_mutex);
			अवरोध;
		हाल KILL_ADAPTER:
			megaraid_sas_समाप्त_hba(instance);
			अवरोध;
		हाल IGNORE_TIMEOUT:
			dev_info(&instance->pdev->dev, "Ignore DCMD timeout: %s %d\n",
				__func__, __LINE__);
			अवरोध;
		पूर्ण

		अवरोध;
	हाल DCMD_SUCCESS:
		tgtid_count = le32_to_cpu(ci->count);

		अगर (megasas_dbg_lvl & LD_PD_DEBUG)
			dev_info(&instance->pdev->dev, "%s, LD count: 0x%x\n",
				 __func__, tgtid_count);

		अगर ((tgtid_count > (instance->fw_supported_vd_count)))
			अवरोध;

		स_रखो(instance->ld_ids, 0xff, MEGASAS_MAX_LD_IDS);
		क्रम (ld_index = 0; ld_index < tgtid_count; ld_index++) अणु
			ids = ci->targetId[ld_index];
			instance->ld_ids[ids] = ci->targetId[ld_index];
			अगर (megasas_dbg_lvl & LD_PD_DEBUG)
				dev_info(&instance->pdev->dev, "LD%d: targetID: 0x%03x\n",
					 ld_index, ci->targetId[ld_index]);
		पूर्ण

		अवरोध;
	पूर्ण

	अगर (ret != DCMD_TIMEOUT)
		megasas_वापस_cmd(instance, cmd);

	वापस ret;
पूर्ण

/**
 * megasas_host_device_list_query
 * dcmd.opcode            - MR_DCMD_CTRL_DEVICE_LIST_GET
 * dcmd.mbox              - reserved
 * dcmd.sge IN            - ptr to वापस MR_HOST_DEVICE_LIST काष्ठाure
 * Desc:    This DCMD will वापस the combined device list
 * Status:  MFI_STAT_OK - List वापसed successfully
 *          MFI_STAT_INVALID_CMD - Firmware support क्रम the feature has been
 *                                 disabled
 * @instance:			Adapter soft state
 * @is_probe:			Driver probe check
 * Return:			0 अगर DCMD succeeded
 *				 non-zero अगर failed
 */
अटल पूर्णांक
megasas_host_device_list_query(काष्ठा megasas_instance *instance,
			       bool is_probe)
अणु
	पूर्णांक ret, i, target_id;
	काष्ठा megasas_cmd *cmd;
	काष्ठा megasas_dcmd_frame *dcmd;
	काष्ठा MR_HOST_DEVICE_LIST *ci;
	u32 count;
	dma_addr_t ci_h;

	ci = instance->host_device_list_buf;
	ci_h = instance->host_device_list_buf_h;

	cmd = megasas_get_cmd(instance);

	अगर (!cmd) अणु
		dev_warn(&instance->pdev->dev,
			 "%s: failed to get cmd\n",
			 __func__);
		वापस -ENOMEM;
	पूर्ण

	dcmd = &cmd->frame->dcmd;

	स_रखो(ci, 0, माप(*ci));
	स_रखो(dcmd->mbox.b, 0, MFI_MBOX_SIZE);

	dcmd->mbox.b[0] = is_probe ? 0 : 1;
	dcmd->cmd = MFI_CMD_DCMD;
	dcmd->cmd_status = MFI_STAT_INVALID_STATUS;
	dcmd->sge_count = 1;
	dcmd->flags = MFI_FRAME_सूची_READ;
	dcmd->समयout = 0;
	dcmd->pad_0 = 0;
	dcmd->data_xfer_len = cpu_to_le32(HOST_DEVICE_LIST_SZ);
	dcmd->opcode = cpu_to_le32(MR_DCMD_CTRL_DEVICE_LIST_GET);

	megasas_set_dma_settings(instance, dcmd, ci_h, HOST_DEVICE_LIST_SZ);

	अगर (!instance->mask_पूर्णांकerrupts) अणु
		ret = megasas_issue_blocked_cmd(instance, cmd,
						MFI_IO_TIMEOUT_SECS);
	पूर्ण अन्यथा अणु
		ret = megasas_issue_polled(instance, cmd);
		cmd->flags |= DRV_DCMD_SKIP_REFIRE;
	पूर्ण

	चयन (ret) अणु
	हाल DCMD_SUCCESS:
		/* Fill the पूर्णांकernal pd_list and ld_ids array based on
		 * targetIds वापसed by FW
		 */
		count = le32_to_cpu(ci->count);

		अगर (count > (MEGASAS_MAX_PD + MAX_LOGICAL_DRIVES_EXT))
			अवरोध;

		अगर (megasas_dbg_lvl & LD_PD_DEBUG)
			dev_info(&instance->pdev->dev, "%s, Device count: 0x%x\n",
				 __func__, count);

		स_रखो(instance->local_pd_list, 0,
		       MEGASAS_MAX_PD * माप(काष्ठा megasas_pd_list));
		स_रखो(instance->ld_ids, 0xff, MAX_LOGICAL_DRIVES_EXT);
		क्रम (i = 0; i < count; i++) अणु
			target_id = le16_to_cpu(ci->host_device_list[i].target_id);
			अगर (ci->host_device_list[i].flags.u.bits.is_sys_pd) अणु
				instance->local_pd_list[target_id].tid = target_id;
				instance->local_pd_list[target_id].driveType =
						ci->host_device_list[i].scsi_type;
				instance->local_pd_list[target_id].driveState =
						MR_PD_STATE_SYSTEM;
				अगर (megasas_dbg_lvl & LD_PD_DEBUG)
					dev_info(&instance->pdev->dev,
						 "Device %d: PD targetID: 0x%03x deviceType:0x%x\n",
						 i, target_id, ci->host_device_list[i].scsi_type);
			पूर्ण अन्यथा अणु
				instance->ld_ids[target_id] = target_id;
				अगर (megasas_dbg_lvl & LD_PD_DEBUG)
					dev_info(&instance->pdev->dev,
						 "Device %d: LD targetID: 0x%03x\n",
						 i, target_id);
			पूर्ण
		पूर्ण

		स_नकल(instance->pd_list, instance->local_pd_list,
		       माप(instance->pd_list));
		अवरोध;

	हाल DCMD_TIMEOUT:
		चयन (dcmd_समयout_ocr_possible(instance)) अणु
		हाल INITIATE_OCR:
			cmd->flags |= DRV_DCMD_SKIP_REFIRE;
			mutex_unlock(&instance->reset_mutex);
			megasas_reset_fusion(instance->host,
				MFI_IO_TIMEOUT_OCR);
			mutex_lock(&instance->reset_mutex);
			अवरोध;
		हाल KILL_ADAPTER:
			megaraid_sas_समाप्त_hba(instance);
			अवरोध;
		हाल IGNORE_TIMEOUT:
			dev_info(&instance->pdev->dev, "Ignore DCMD timeout: %s %d\n",
				 __func__, __LINE__);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल DCMD_FAILED:
		dev_err(&instance->pdev->dev,
			"%s: MR_DCMD_CTRL_DEVICE_LIST_GET failed\n",
			__func__);
		अवरोध;
	पूर्ण

	अगर (ret != DCMD_TIMEOUT)
		megasas_वापस_cmd(instance, cmd);

	वापस ret;
पूर्ण

/*
 * megasas_update_ext_vd_details : Update details w.r.t Extended VD
 * instance			 : Controller's instance
*/
अटल व्योम megasas_update_ext_vd_details(काष्ठा megasas_instance *instance)
अणु
	काष्ठा fusion_context *fusion;
	u32 ventura_map_sz = 0;

	fusion = instance->ctrl_context;
	/* For MFI based controllers वापस dummy success */
	अगर (!fusion)
		वापस;

	instance->supporपंचांगax256vd =
		instance->ctrl_info_buf->adapterOperations3.supportMaxExtLDs;
	/* Below is additional check to address future FW enhancement */
	अगर (instance->ctrl_info_buf->max_lds > 64)
		instance->supporपंचांगax256vd = 1;

	instance->drv_supported_vd_count = MEGASAS_MAX_LD_CHANNELS
					* MEGASAS_MAX_DEV_PER_CHANNEL;
	instance->drv_supported_pd_count = MEGASAS_MAX_PD_CHANNELS
					* MEGASAS_MAX_DEV_PER_CHANNEL;
	अगर (instance->supporपंचांगax256vd) अणु
		instance->fw_supported_vd_count = MAX_LOGICAL_DRIVES_EXT;
		instance->fw_supported_pd_count = MAX_PHYSICAL_DEVICES;
	पूर्ण अन्यथा अणु
		instance->fw_supported_vd_count = MAX_LOGICAL_DRIVES;
		instance->fw_supported_pd_count = MAX_PHYSICAL_DEVICES;
	पूर्ण

	dev_info(&instance->pdev->dev,
		"FW provided supportMaxExtLDs: %d\tmax_lds: %d\n",
		instance->ctrl_info_buf->adapterOperations3.supportMaxExtLDs ? 1 : 0,
		instance->ctrl_info_buf->max_lds);

	अगर (instance->max_raid_mapsize) अणु
		ventura_map_sz = instance->max_raid_mapsize *
						MR_MIN_MAP_SIZE; /* 64k */
		fusion->current_map_sz = ventura_map_sz;
		fusion->max_map_sz = ventura_map_sz;
	पूर्ण अन्यथा अणु
		fusion->old_map_sz =  माप(काष्ठा MR_FW_RAID_MAP) +
					(माप(काष्ठा MR_LD_SPAN_MAP) *
					(instance->fw_supported_vd_count - 1));
		fusion->new_map_sz =  माप(काष्ठा MR_FW_RAID_MAP_EXT);

		fusion->max_map_sz =
			max(fusion->old_map_sz, fusion->new_map_sz);

		अगर (instance->supporपंचांगax256vd)
			fusion->current_map_sz = fusion->new_map_sz;
		अन्यथा
			fusion->current_map_sz = fusion->old_map_sz;
	पूर्ण
	/* irrespective of FW raid maps, driver raid map is स्थिरant */
	fusion->drv_map_sz = माप(काष्ठा MR_DRV_RAID_MAP_ALL);
पूर्ण

/*
 * dcmd.opcode                - MR_DCMD_CTRL_SNAPDUMP_GET_PROPERTIES
 * dcmd.hdr.length            - number of bytes to पढ़ो
 * dcmd.sge                   - Ptr to MR_SNAPDUMP_PROPERTIES
 * Desc:			 Fill in snapdump properties
 * Status:			 MFI_STAT_OK- Command successful
 */
व्योम megasas_get_snapdump_properties(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक ret = 0;
	काष्ठा megasas_cmd *cmd;
	काष्ठा megasas_dcmd_frame *dcmd;
	काष्ठा MR_SNAPDUMP_PROPERTIES *ci;
	dma_addr_t ci_h = 0;

	ci = instance->snapdump_prop;
	ci_h = instance->snapdump_prop_h;

	अगर (!ci)
		वापस;

	cmd = megasas_get_cmd(instance);

	अगर (!cmd) अणु
		dev_dbg(&instance->pdev->dev, "Failed to get a free cmd\n");
		वापस;
	पूर्ण

	dcmd = &cmd->frame->dcmd;

	स_रखो(ci, 0, माप(*ci));
	स_रखो(dcmd->mbox.b, 0, MFI_MBOX_SIZE);

	dcmd->cmd = MFI_CMD_DCMD;
	dcmd->cmd_status = MFI_STAT_INVALID_STATUS;
	dcmd->sge_count = 1;
	dcmd->flags = MFI_FRAME_सूची_READ;
	dcmd->समयout = 0;
	dcmd->pad_0 = 0;
	dcmd->data_xfer_len = cpu_to_le32(माप(काष्ठा MR_SNAPDUMP_PROPERTIES));
	dcmd->opcode = cpu_to_le32(MR_DCMD_CTRL_SNAPDUMP_GET_PROPERTIES);

	megasas_set_dma_settings(instance, dcmd, ci_h,
				 माप(काष्ठा MR_SNAPDUMP_PROPERTIES));

	अगर (!instance->mask_पूर्णांकerrupts) अणु
		ret = megasas_issue_blocked_cmd(instance, cmd,
						MFI_IO_TIMEOUT_SECS);
	पूर्ण अन्यथा अणु
		ret = megasas_issue_polled(instance, cmd);
		cmd->flags |= DRV_DCMD_SKIP_REFIRE;
	पूर्ण

	चयन (ret) अणु
	हाल DCMD_SUCCESS:
		instance->snapdump_रुको_समय =
			min_t(u8, ci->trigger_min_num_sec_beक्रमe_ocr,
				MEGASAS_MAX_SNAP_DUMP_WAIT_TIME);
		अवरोध;

	हाल DCMD_TIMEOUT:
		चयन (dcmd_समयout_ocr_possible(instance)) अणु
		हाल INITIATE_OCR:
			cmd->flags |= DRV_DCMD_SKIP_REFIRE;
			mutex_unlock(&instance->reset_mutex);
			megasas_reset_fusion(instance->host,
				MFI_IO_TIMEOUT_OCR);
			mutex_lock(&instance->reset_mutex);
			अवरोध;
		हाल KILL_ADAPTER:
			megaraid_sas_समाप्त_hba(instance);
			अवरोध;
		हाल IGNORE_TIMEOUT:
			dev_info(&instance->pdev->dev, "Ignore DCMD timeout: %s %d\n",
				__func__, __LINE__);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret != DCMD_TIMEOUT)
		megasas_वापस_cmd(instance, cmd);
पूर्ण

/**
 * megasas_get_ctrl_info -	Returns FW's controller काष्ठाure
 * @instance:				Adapter soft state
 *
 * Issues an पूर्णांकernal command (DCMD) to get the FW's controller काष्ठाure.
 * This inक्रमmation is मुख्यly used to find out the maximum IO transfer per
 * command supported by the FW.
 */
पूर्णांक
megasas_get_ctrl_info(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक ret = 0;
	काष्ठा megasas_cmd *cmd;
	काष्ठा megasas_dcmd_frame *dcmd;
	काष्ठा megasas_ctrl_info *ci;
	dma_addr_t ci_h = 0;

	ci = instance->ctrl_info_buf;
	ci_h = instance->ctrl_info_buf_h;

	cmd = megasas_get_cmd(instance);

	अगर (!cmd) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "Failed to get a free cmd\n");
		वापस -ENOMEM;
	पूर्ण

	dcmd = &cmd->frame->dcmd;

	स_रखो(ci, 0, माप(*ci));
	स_रखो(dcmd->mbox.b, 0, MFI_MBOX_SIZE);

	dcmd->cmd = MFI_CMD_DCMD;
	dcmd->cmd_status = MFI_STAT_INVALID_STATUS;
	dcmd->sge_count = 1;
	dcmd->flags = MFI_FRAME_सूची_READ;
	dcmd->समयout = 0;
	dcmd->pad_0 = 0;
	dcmd->data_xfer_len = cpu_to_le32(माप(काष्ठा megasas_ctrl_info));
	dcmd->opcode = cpu_to_le32(MR_DCMD_CTRL_GET_INFO);
	dcmd->mbox.b[0] = 1;

	megasas_set_dma_settings(instance, dcmd, ci_h,
				 माप(काष्ठा megasas_ctrl_info));

	अगर ((instance->adapter_type != MFI_SERIES) &&
	    !instance->mask_पूर्णांकerrupts) अणु
		ret = megasas_issue_blocked_cmd(instance, cmd, MFI_IO_TIMEOUT_SECS);
	पूर्ण अन्यथा अणु
		ret = megasas_issue_polled(instance, cmd);
		cmd->flags |= DRV_DCMD_SKIP_REFIRE;
	पूर्ण

	चयन (ret) अणु
	हाल DCMD_SUCCESS:
		/* Save required controller inक्रमmation in
		 * CPU endianness क्रमmat.
		 */
		le32_to_cpus((u32 *)&ci->properties.OnOffProperties);
		le16_to_cpus((u16 *)&ci->properties.on_off_properties2);
		le32_to_cpus((u32 *)&ci->adapterOperations2);
		le32_to_cpus((u32 *)&ci->adapterOperations3);
		le16_to_cpus((u16 *)&ci->adapter_operations4);
		le32_to_cpus((u32 *)&ci->adapter_operations5);

		/* Update the latest Ext VD info.
		 * From Init path, store current firmware details.
		 * From OCR path, detect any firmware properties changes.
		 * in हाल of Firmware upgrade without प्रणाली reboot.
		 */
		megasas_update_ext_vd_details(instance);
		instance->support_seqnum_jbod_fp =
			ci->adapterOperations3.useSeqNumJbodFP;
		instance->support_morethan256jbod =
			ci->adapter_operations4.support_pd_map_target_id;
		instance->support_nvme_passthru =
			ci->adapter_operations4.support_nvme_passthru;
		instance->support_pci_lane_margining =
			ci->adapter_operations5.support_pci_lane_margining;
		instance->task_पात_पंचांगo = ci->TaskAbortTO;
		instance->max_reset_पंचांगo = ci->MaxResetTO;

		/*Check whether controller is iMR or MR */
		instance->is_imr = (ci->memory_size ? 0 : 1);

		instance->snapdump_रुको_समय =
			(ci->properties.on_off_properties2.enable_snap_dump ?
			 MEGASAS_DEFAULT_SNAP_DUMP_WAIT_TIME : 0);

		instance->enable_fw_dev_list =
			ci->properties.on_off_properties2.enable_fw_dev_list;

		dev_info(&instance->pdev->dev,
			"controller type\t: %s(%dMB)\n",
			instance->is_imr ? "iMR" : "MR",
			le16_to_cpu(ci->memory_size));

		instance->disableOnlineCtrlReset =
			ci->properties.OnOffProperties.disableOnlineCtrlReset;
		instance->secure_jbod_support =
			ci->adapterOperations3.supportSecurityonJBOD;
		dev_info(&instance->pdev->dev, "Online Controller Reset(OCR)\t: %s\n",
			instance->disableOnlineCtrlReset ? "Disabled" : "Enabled");
		dev_info(&instance->pdev->dev, "Secure JBOD support\t: %s\n",
			instance->secure_jbod_support ? "Yes" : "No");
		dev_info(&instance->pdev->dev, "NVMe passthru support\t: %s\n",
			 instance->support_nvme_passthru ? "Yes" : "No");
		dev_info(&instance->pdev->dev,
			 "FW provided TM TaskAbort/Reset timeout\t: %d secs/%d secs\n",
			 instance->task_पात_पंचांगo, instance->max_reset_पंचांगo);
		dev_info(&instance->pdev->dev, "JBOD sequence map support\t: %s\n",
			 instance->support_seqnum_jbod_fp ? "Yes" : "No");
		dev_info(&instance->pdev->dev, "PCI Lane Margining support\t: %s\n",
			 instance->support_pci_lane_margining ? "Yes" : "No");

		अवरोध;

	हाल DCMD_TIMEOUT:
		चयन (dcmd_समयout_ocr_possible(instance)) अणु
		हाल INITIATE_OCR:
			cmd->flags |= DRV_DCMD_SKIP_REFIRE;
			mutex_unlock(&instance->reset_mutex);
			megasas_reset_fusion(instance->host,
				MFI_IO_TIMEOUT_OCR);
			mutex_lock(&instance->reset_mutex);
			अवरोध;
		हाल KILL_ADAPTER:
			megaraid_sas_समाप्त_hba(instance);
			अवरोध;
		हाल IGNORE_TIMEOUT:
			dev_info(&instance->pdev->dev, "Ignore DCMD timeout: %s %d\n",
				__func__, __LINE__);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल DCMD_FAILED:
		megaraid_sas_समाप्त_hba(instance);
		अवरोध;

	पूर्ण

	अगर (ret != DCMD_TIMEOUT)
		megasas_वापस_cmd(instance, cmd);

	वापस ret;
पूर्ण

/*
 * megasas_set_crash_dump_params -	Sends address of crash dump DMA buffer
 *					to firmware
 *
 * @instance:				Adapter soft state
 * @crash_buf_state		-	tell FW to turn ON/OFF crash dump feature
					MR_CRASH_BUF_TURN_OFF = 0
					MR_CRASH_BUF_TURN_ON = 1
 * @वापस 0 on success non-zero on failure.
 * Issues an पूर्णांकernal command (DCMD) to set parameters क्रम crash dump feature.
 * Driver will send address of crash dump DMA buffer and set mbox to tell FW
 * that driver supports crash dump feature. This DCMD will be sent only अगर
 * crash dump feature is supported by the FW.
 *
 */
पूर्णांक megasas_set_crash_dump_params(काष्ठा megasas_instance *instance,
	u8 crash_buf_state)
अणु
	पूर्णांक ret = 0;
	काष्ठा megasas_cmd *cmd;
	काष्ठा megasas_dcmd_frame *dcmd;

	cmd = megasas_get_cmd(instance);

	अगर (!cmd) अणु
		dev_err(&instance->pdev->dev, "Failed to get a free cmd\n");
		वापस -ENOMEM;
	पूर्ण


	dcmd = &cmd->frame->dcmd;

	स_रखो(dcmd->mbox.b, 0, MFI_MBOX_SIZE);
	dcmd->mbox.b[0] = crash_buf_state;
	dcmd->cmd = MFI_CMD_DCMD;
	dcmd->cmd_status = MFI_STAT_INVALID_STATUS;
	dcmd->sge_count = 1;
	dcmd->flags = MFI_FRAME_सूची_NONE;
	dcmd->समयout = 0;
	dcmd->pad_0 = 0;
	dcmd->data_xfer_len = cpu_to_le32(CRASH_DMA_BUF_SIZE);
	dcmd->opcode = cpu_to_le32(MR_DCMD_CTRL_SET_CRASH_DUMP_PARAMS);

	megasas_set_dma_settings(instance, dcmd, instance->crash_dump_h,
				 CRASH_DMA_BUF_SIZE);

	अगर ((instance->adapter_type != MFI_SERIES) &&
	    !instance->mask_पूर्णांकerrupts)
		ret = megasas_issue_blocked_cmd(instance, cmd, MFI_IO_TIMEOUT_SECS);
	अन्यथा
		ret = megasas_issue_polled(instance, cmd);

	अगर (ret == DCMD_TIMEOUT) अणु
		चयन (dcmd_समयout_ocr_possible(instance)) अणु
		हाल INITIATE_OCR:
			cmd->flags |= DRV_DCMD_SKIP_REFIRE;
			megasas_reset_fusion(instance->host,
					MFI_IO_TIMEOUT_OCR);
			अवरोध;
		हाल KILL_ADAPTER:
			megaraid_sas_समाप्त_hba(instance);
			अवरोध;
		हाल IGNORE_TIMEOUT:
			dev_info(&instance->pdev->dev, "Ignore DCMD timeout: %s %d\n",
				__func__, __LINE__);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		megasas_वापस_cmd(instance, cmd);

	वापस ret;
पूर्ण

/**
 * megasas_issue_init_mfi -	Initializes the FW
 * @instance:		Adapter soft state
 *
 * Issues the INIT MFI cmd
 */
अटल पूर्णांक
megasas_issue_init_mfi(काष्ठा megasas_instance *instance)
अणु
	__le32 context;
	काष्ठा megasas_cmd *cmd;
	काष्ठा megasas_init_frame *init_frame;
	काष्ठा megasas_init_queue_info *initq_info;
	dma_addr_t init_frame_h;
	dma_addr_t initq_info_h;

	/*
	 * Prepare a init frame. Note the init frame poपूर्णांकs to queue info
	 * काष्ठाure. Each frame has SGL allocated after first 64 bytes. For
	 * this frame - since we करोn't need any SGL - we use SGL's space as
	 * queue info काष्ठाure
	 *
	 * We will not get a शून्य command below. We just created the pool.
	 */
	cmd = megasas_get_cmd(instance);

	init_frame = (काष्ठा megasas_init_frame *)cmd->frame;
	initq_info = (काष्ठा megasas_init_queue_info *)
		((अचिन्हित दीर्घ)init_frame + 64);

	init_frame_h = cmd->frame_phys_addr;
	initq_info_h = init_frame_h + 64;

	context = init_frame->context;
	स_रखो(init_frame, 0, MEGAMFI_FRAME_SIZE);
	स_रखो(initq_info, 0, माप(काष्ठा megasas_init_queue_info));
	init_frame->context = context;

	initq_info->reply_queue_entries = cpu_to_le32(instance->max_fw_cmds + 1);
	initq_info->reply_queue_start_phys_addr_lo = cpu_to_le32(instance->reply_queue_h);

	initq_info->producer_index_phys_addr_lo = cpu_to_le32(instance->producer_h);
	initq_info->consumer_index_phys_addr_lo = cpu_to_le32(instance->consumer_h);

	init_frame->cmd = MFI_CMD_INIT;
	init_frame->cmd_status = MFI_STAT_INVALID_STATUS;
	init_frame->queue_info_new_phys_addr_lo =
		cpu_to_le32(lower_32_bits(initq_info_h));
	init_frame->queue_info_new_phys_addr_hi =
		cpu_to_le32(upper_32_bits(initq_info_h));

	init_frame->data_xfer_len = cpu_to_le32(माप(काष्ठा megasas_init_queue_info));

	/*
	 * disable the पूर्णांकr beक्रमe firing the init frame to FW
	 */
	instance->instancet->disable_पूर्णांकr(instance);

	/*
	 * Issue the init frame in polled mode
	 */

	अगर (megasas_issue_polled(instance, cmd)) अणु
		dev_err(&instance->pdev->dev, "Failed to init firmware\n");
		megasas_वापस_cmd(instance, cmd);
		जाओ fail_fw_init;
	पूर्ण

	megasas_वापस_cmd(instance, cmd);

	वापस 0;

fail_fw_init:
	वापस -EINVAL;
पूर्ण

अटल u32
megasas_init_adapter_mfi(काष्ठा megasas_instance *instance)
अणु
	u32 context_sz;
	u32 reply_q_sz;

	/*
	 * Get various operational parameters from status रेजिस्टर
	 */
	instance->max_fw_cmds = instance->instancet->पढ़ो_fw_status_reg(instance) & 0x00FFFF;
	/*
	 * Reduce the max supported cmds by 1. This is to ensure that the
	 * reply_q_sz (1 more than the max cmd that driver may send)
	 * करोes not exceed max cmds that the FW can support
	 */
	instance->max_fw_cmds = instance->max_fw_cmds-1;
	instance->max_mfi_cmds = instance->max_fw_cmds;
	instance->max_num_sge = (instance->instancet->पढ़ो_fw_status_reg(instance) & 0xFF0000) >>
					0x10;
	/*
	 * For MFI skinny adapters, MEGASAS_SKINNY_INT_CMDS commands
	 * are reserved क्रम IOCTL + driver's पूर्णांकernal DCMDs.
	 */
	अगर ((instance->pdev->device == PCI_DEVICE_ID_LSI_SAS0073SKINNY) ||
		(instance->pdev->device == PCI_DEVICE_ID_LSI_SAS0071SKINNY)) अणु
		instance->max_scsi_cmds = (instance->max_fw_cmds -
			MEGASAS_SKINNY_INT_CMDS);
		sema_init(&instance->ioctl_sem, MEGASAS_SKINNY_INT_CMDS);
	पूर्ण अन्यथा अणु
		instance->max_scsi_cmds = (instance->max_fw_cmds -
			MEGASAS_INT_CMDS);
		sema_init(&instance->ioctl_sem, (MEGASAS_MFI_IOCTL_CMDS));
	पूर्ण

	instance->cur_can_queue = instance->max_scsi_cmds;
	/*
	 * Create a pool of commands
	 */
	अगर (megasas_alloc_cmds(instance))
		जाओ fail_alloc_cmds;

	/*
	 * Allocate memory क्रम reply queue. Length of reply queue should
	 * be _one_ more than the maximum commands handled by the firmware.
	 *
	 * Note: When FW completes commands, it places corresponding contex
	 * values in this circular reply queue. This circular queue is a fairly
	 * typical producer-consumer queue. FW is the producer (of completed
	 * commands) and the driver is the consumer.
	 */
	context_sz = माप(u32);
	reply_q_sz = context_sz * (instance->max_fw_cmds + 1);

	instance->reply_queue = dma_alloc_coherent(&instance->pdev->dev,
			reply_q_sz, &instance->reply_queue_h, GFP_KERNEL);

	अगर (!instance->reply_queue) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "Out of DMA mem for reply queue\n");
		जाओ fail_reply_queue;
	पूर्ण

	अगर (megasas_issue_init_mfi(instance))
		जाओ fail_fw_init;

	अगर (megasas_get_ctrl_info(instance)) अणु
		dev_err(&instance->pdev->dev, "(%d): Could get controller info "
			"Fail from %s %d\n", instance->unique_id,
			__func__, __LINE__);
		जाओ fail_fw_init;
	पूर्ण

	instance->fw_support_ieee = 0;
	instance->fw_support_ieee =
		(instance->instancet->पढ़ो_fw_status_reg(instance) &
		0x04000000);

	dev_notice(&instance->pdev->dev, "megasas_init_mfi: fw_support_ieee=%d",
			instance->fw_support_ieee);

	अगर (instance->fw_support_ieee)
		instance->flag_ieee = 1;

	वापस 0;

fail_fw_init:

	dma_मुक्त_coherent(&instance->pdev->dev, reply_q_sz,
			    instance->reply_queue, instance->reply_queue_h);
fail_reply_queue:
	megasas_मुक्त_cmds(instance);

fail_alloc_cmds:
	वापस 1;
पूर्ण

अटल
व्योम megasas_setup_irq_poll(काष्ठा megasas_instance *instance)
अणु
	काष्ठा megasas_irq_context *irq_ctx;
	u32 count, i;

	count = instance->msix_vectors > 0 ? instance->msix_vectors : 1;

	/* Initialize IRQ poll */
	क्रम (i = 0; i < count; i++) अणु
		irq_ctx = &instance->irq_context[i];
		irq_ctx->os_irq = pci_irq_vector(instance->pdev, i);
		irq_ctx->irq_poll_scheduled = false;
		irq_poll_init(&irq_ctx->irqpoll,
			      instance->threshold_reply_count,
			      megasas_irqpoll);
	पूर्ण
पूर्ण

/*
 * megasas_setup_irqs_ioapic -		रेजिस्टर legacy पूर्णांकerrupts.
 * @instance:				Adapter soft state
 *
 * Do not enable पूर्णांकerrupt, only setup ISRs.
 *
 * Return 0 on success.
 */
अटल पूर्णांक
megasas_setup_irqs_ioapic(काष्ठा megasas_instance *instance)
अणु
	काष्ठा pci_dev *pdev;

	pdev = instance->pdev;
	instance->irq_context[0].instance = instance;
	instance->irq_context[0].MSIxIndex = 0;
	snम_लिखो(instance->irq_context->name, MEGASAS_MSIX_NAME_LEN, "%s%u",
		"megasas", instance->host->host_no);
	अगर (request_irq(pci_irq_vector(pdev, 0),
			instance->instancet->service_isr, IRQF_SHARED,
			instance->irq_context->name, &instance->irq_context[0])) अणु
		dev_err(&instance->pdev->dev,
				"Failed to register IRQ from %s %d\n",
				__func__, __LINE__);
		वापस -1;
	पूर्ण
	instance->perf_mode = MR_LATENCY_PERF_MODE;
	instance->low_latency_index_start = 0;
	वापस 0;
पूर्ण

/**
 * megasas_setup_irqs_msix -		रेजिस्टर MSI-x पूर्णांकerrupts.
 * @instance:				Adapter soft state
 * @is_probe:				Driver probe check
 *
 * Do not enable पूर्णांकerrupt, only setup ISRs.
 *
 * Return 0 on success.
 */
अटल पूर्णांक
megasas_setup_irqs_msix(काष्ठा megasas_instance *instance, u8 is_probe)
अणु
	पूर्णांक i, j;
	काष्ठा pci_dev *pdev;

	pdev = instance->pdev;

	/* Try MSI-x */
	क्रम (i = 0; i < instance->msix_vectors; i++) अणु
		instance->irq_context[i].instance = instance;
		instance->irq_context[i].MSIxIndex = i;
		snम_लिखो(instance->irq_context[i].name, MEGASAS_MSIX_NAME_LEN, "%s%u-msix%u",
			"megasas", instance->host->host_no, i);
		अगर (request_irq(pci_irq_vector(pdev, i),
			instance->instancet->service_isr, 0, instance->irq_context[i].name,
			&instance->irq_context[i])) अणु
			dev_err(&instance->pdev->dev,
				"Failed to register IRQ for vector %d.\n", i);
			क्रम (j = 0; j < i; j++) अणु
				अगर (j < instance->low_latency_index_start)
					irq_set_affinity_hपूर्णांक(
						pci_irq_vector(pdev, j), शून्य);
				मुक्त_irq(pci_irq_vector(pdev, j),
					 &instance->irq_context[j]);
			पूर्ण
			/* Retry irq रेजिस्टर क्रम IO_APIC*/
			instance->msix_vectors = 0;
			instance->msix_load_balance = false;
			अगर (is_probe) अणु
				pci_मुक्त_irq_vectors(instance->pdev);
				वापस megasas_setup_irqs_ioapic(instance);
			पूर्ण अन्यथा अणु
				वापस -1;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * megasas_destroy_irqs-		unरेजिस्टर पूर्णांकerrupts.
 * @instance:				Adapter soft state
 * वापस:				व्योम
 */
अटल व्योम
megasas_destroy_irqs(काष्ठा megasas_instance *instance) अणु

	पूर्णांक i;
	पूर्णांक count;
	काष्ठा megasas_irq_context *irq_ctx;

	count = instance->msix_vectors > 0 ? instance->msix_vectors : 1;
	अगर (instance->adapter_type != MFI_SERIES) अणु
		क्रम (i = 0; i < count; i++) अणु
			irq_ctx = &instance->irq_context[i];
			irq_poll_disable(&irq_ctx->irqpoll);
		पूर्ण
	पूर्ण

	अगर (instance->msix_vectors)
		क्रम (i = 0; i < instance->msix_vectors; i++) अणु
			अगर (i < instance->low_latency_index_start)
				irq_set_affinity_hपूर्णांक(
				    pci_irq_vector(instance->pdev, i), शून्य);
			मुक्त_irq(pci_irq_vector(instance->pdev, i),
				 &instance->irq_context[i]);
		पूर्ण
	अन्यथा
		मुक्त_irq(pci_irq_vector(instance->pdev, 0),
			 &instance->irq_context[0]);
पूर्ण

/**
 * megasas_setup_jbod_map -	setup jbod map क्रम FP seq_number.
 * @instance:				Adapter soft state
 *
 * Return 0 on success.
 */
व्योम
megasas_setup_jbod_map(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक i;
	काष्ठा fusion_context *fusion = instance->ctrl_context;
	u32 pd_seq_map_sz;

	pd_seq_map_sz = माप(काष्ठा MR_PD_CFG_SEQ_NUM_SYNC) +
		(माप(काष्ठा MR_PD_CFG_SEQ) * (MAX_PHYSICAL_DEVICES - 1));

	instance->use_seqnum_jbod_fp =
		instance->support_seqnum_jbod_fp;
	अगर (reset_devices || !fusion ||
		!instance->support_seqnum_jbod_fp) अणु
		dev_info(&instance->pdev->dev,
			"JBOD sequence map is disabled %s %d\n",
			__func__, __LINE__);
		instance->use_seqnum_jbod_fp = false;
		वापस;
	पूर्ण

	अगर (fusion->pd_seq_sync[0])
		जाओ skip_alloc;

	क्रम (i = 0; i < JBOD_MAPS_COUNT; i++) अणु
		fusion->pd_seq_sync[i] = dma_alloc_coherent
			(&instance->pdev->dev, pd_seq_map_sz,
			&fusion->pd_seq_phys[i], GFP_KERNEL);
		अगर (!fusion->pd_seq_sync[i]) अणु
			dev_err(&instance->pdev->dev,
				"Failed to allocate memory from %s %d\n",
				__func__, __LINE__);
			अगर (i == 1) अणु
				dma_मुक्त_coherent(&instance->pdev->dev,
					pd_seq_map_sz, fusion->pd_seq_sync[0],
					fusion->pd_seq_phys[0]);
				fusion->pd_seq_sync[0] = शून्य;
			पूर्ण
			instance->use_seqnum_jbod_fp = false;
			वापस;
		पूर्ण
	पूर्ण

skip_alloc:
	अगर (!megasas_sync_pd_seq_num(instance, false) &&
		!megasas_sync_pd_seq_num(instance, true))
		instance->use_seqnum_jbod_fp = true;
	अन्यथा
		instance->use_seqnum_jbod_fp = false;
पूर्ण

अटल व्योम megasas_setup_reply_map(काष्ठा megasas_instance *instance)
अणु
	स्थिर काष्ठा cpumask *mask;
	अचिन्हित पूर्णांक queue, cpu, low_latency_index_start;

	low_latency_index_start = instance->low_latency_index_start;

	क्रम (queue = low_latency_index_start; queue < instance->msix_vectors; queue++) अणु
		mask = pci_irq_get_affinity(instance->pdev, queue);
		अगर (!mask)
			जाओ fallback;

		क्रम_each_cpu(cpu, mask)
			instance->reply_map[cpu] = queue;
	पूर्ण
	वापस;

fallback:
	queue = low_latency_index_start;
	क्रम_each_possible_cpu(cpu) अणु
		instance->reply_map[cpu] = queue;
		अगर (queue == (instance->msix_vectors - 1))
			queue = low_latency_index_start;
		अन्यथा
			queue++;
	पूर्ण
पूर्ण

/**
 * megasas_get_device_list -	Get the PD and LD device list from FW.
 * @instance:			Adapter soft state
 * @वापस:			Success or failure
 *
 * Issue DCMDs to Firmware to get the PD and LD list.
 * Based on the FW support, driver sends the HOST_DEVICE_LIST or combination
 * of PD_LIST/LD_LIST_QUERY DCMDs to get the device list.
 */
अटल
पूर्णांक megasas_get_device_list(काष्ठा megasas_instance *instance)
अणु
	स_रखो(instance->pd_list, 0,
	       (MEGASAS_MAX_PD * माप(काष्ठा megasas_pd_list)));
	स_रखो(instance->ld_ids, 0xff, MEGASAS_MAX_LD_IDS);

	अगर (instance->enable_fw_dev_list) अणु
		अगर (megasas_host_device_list_query(instance, true))
			वापस FAILED;
	पूर्ण अन्यथा अणु
		अगर (megasas_get_pd_list(instance) < 0) अणु
			dev_err(&instance->pdev->dev, "failed to get PD list\n");
			वापस FAILED;
		पूर्ण

		अगर (megasas_ld_list_query(instance,
					  MR_LD_QUERY_TYPE_EXPOSED_TO_HOST)) अणु
			dev_err(&instance->pdev->dev, "failed to get LD list\n");
			वापस FAILED;
		पूर्ण
	पूर्ण

	वापस SUCCESS;
पूर्ण

/**
 * megasas_set_high_iops_queue_affinity_hपूर्णांक -	Set affinity hपूर्णांक क्रम high IOPS queues
 * @instance:					Adapter soft state
 * वापस:					व्योम
 */
अटल अंतरभूत व्योम
megasas_set_high_iops_queue_affinity_hपूर्णांक(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक i;
	पूर्णांक local_numa_node;

	अगर (instance->perf_mode == MR_BALANCED_PERF_MODE) अणु
		local_numa_node = dev_to_node(&instance->pdev->dev);

		क्रम (i = 0; i < instance->low_latency_index_start; i++)
			irq_set_affinity_hपूर्णांक(pci_irq_vector(instance->pdev, i),
				cpumask_of_node(local_numa_node));
	पूर्ण
पूर्ण

अटल पूर्णांक
__megasas_alloc_irq_vectors(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक i, irq_flags;
	काष्ठा irq_affinity desc = अणु .pre_vectors = instance->low_latency_index_start पूर्ण;
	काष्ठा irq_affinity *descp = &desc;

	irq_flags = PCI_IRQ_MSIX;

	अगर (instance->smp_affinity_enable)
		irq_flags |= PCI_IRQ_AFFINITY | PCI_IRQ_ALL_TYPES;
	अन्यथा
		descp = शून्य;

	/* Do not allocate msix vectors क्रम poll_queues.
	 * msix_vectors is always within a range of FW supported reply queue.
	 */
	i = pci_alloc_irq_vectors_affinity(instance->pdev,
		instance->low_latency_index_start,
		instance->msix_vectors - instance->iopoll_q_count, irq_flags, descp);

	वापस i;
पूर्ण

/**
 * megasas_alloc_irq_vectors -	Allocate IRQ vectors/enable MSI-x vectors
 * @instance:			Adapter soft state
 * वापस:			व्योम
 */
अटल व्योम
megasas_alloc_irq_vectors(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक num_msix_req;

	instance->iopoll_q_count = 0;
	अगर ((instance->adapter_type != MFI_SERIES) &&
		poll_queues) अणु

		instance->perf_mode = MR_LATENCY_PERF_MODE;
		instance->low_latency_index_start = 1;

		/* reserve क्रम शेष and non-mananged pre-vector. */
		अगर (instance->msix_vectors > (poll_queues + 2))
			instance->iopoll_q_count = poll_queues;
		अन्यथा
			instance->iopoll_q_count = 0;

		num_msix_req = num_online_cpus() + instance->low_latency_index_start;
		instance->msix_vectors = min(num_msix_req,
				instance->msix_vectors);

	पूर्ण

	i = __megasas_alloc_irq_vectors(instance);

	अगर (((instance->perf_mode == MR_BALANCED_PERF_MODE)
		|| instance->iopoll_q_count) &&
	    (i != (instance->msix_vectors - instance->iopoll_q_count))) अणु
		अगर (instance->msix_vectors)
			pci_मुक्त_irq_vectors(instance->pdev);
		/* Disable Balanced IOPS mode and try पुनः_स्मृति vectors */
		instance->perf_mode = MR_LATENCY_PERF_MODE;
		instance->low_latency_index_start = 1;
		num_msix_req = num_online_cpus() + instance->low_latency_index_start;

		instance->msix_vectors = min(num_msix_req,
				instance->msix_vectors);

		instance->iopoll_q_count = 0;
		i = __megasas_alloc_irq_vectors(instance);

	पूर्ण

	dev_info(&instance->pdev->dev,
		"requested/available msix %d/%d poll_queue %d\n",
			instance->msix_vectors - instance->iopoll_q_count,
			i, instance->iopoll_q_count);

	अगर (i > 0)
		instance->msix_vectors = i;
	अन्यथा
		instance->msix_vectors = 0;

	अगर (instance->smp_affinity_enable)
		megasas_set_high_iops_queue_affinity_hपूर्णांक(instance);
पूर्ण

/**
 * megasas_init_fw -	Initializes the FW
 * @instance:		Adapter soft state
 *
 * This is the मुख्य function क्रम initializing firmware
 */

अटल पूर्णांक megasas_init_fw(काष्ठा megasas_instance *instance)
अणु
	u32 max_sectors_1;
	u32 max_sectors_2, पंचांगp_sectors, msix_enable;
	u32 scratch_pad_1, scratch_pad_2, scratch_pad_3, status_reg;
	resource_माप_प्रकार base_addr;
	व्योम *base_addr_phys;
	काष्ठा megasas_ctrl_info *ctrl_info = शून्य;
	अचिन्हित दीर्घ bar_list;
	पूर्णांक i, j, loop;
	काष्ठा IOV_111 *iovPtr;
	काष्ठा fusion_context *fusion;
	bool पूर्णांकr_coalescing;
	अचिन्हित पूर्णांक num_msix_req;
	u16 lnksta, speed;

	fusion = instance->ctrl_context;

	/* Find first memory bar */
	bar_list = pci_select_bars(instance->pdev, IORESOURCE_MEM);
	instance->bar = find_first_bit(&bar_list, BITS_PER_LONG);
	अगर (pci_request_selected_regions(instance->pdev, 1<<instance->bar,
					 "megasas: LSI")) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "IO memory region busy!\n");
		वापस -EBUSY;
	पूर्ण

	base_addr = pci_resource_start(instance->pdev, instance->bar);
	instance->reg_set = ioremap(base_addr, 8192);

	अगर (!instance->reg_set) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "Failed to map IO mem\n");
		जाओ fail_ioremap;
	पूर्ण

	base_addr_phys = &base_addr;
	dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev,
		   "BAR:0x%lx  BAR's base_addr(phys):%pa  mapped virt_addr:0x%p\n",
		   instance->bar, base_addr_phys, instance->reg_set);

	अगर (instance->adapter_type != MFI_SERIES)
		instance->instancet = &megasas_instance_ढाँचा_fusion;
	अन्यथा अणु
		चयन (instance->pdev->device) अणु
		हाल PCI_DEVICE_ID_LSI_SAS1078R:
		हाल PCI_DEVICE_ID_LSI_SAS1078DE:
			instance->instancet = &megasas_instance_ढाँचा_ppc;
			अवरोध;
		हाल PCI_DEVICE_ID_LSI_SAS1078GEN2:
		हाल PCI_DEVICE_ID_LSI_SAS0079GEN2:
			instance->instancet = &megasas_instance_ढाँचा_gen2;
			अवरोध;
		हाल PCI_DEVICE_ID_LSI_SAS0073SKINNY:
		हाल PCI_DEVICE_ID_LSI_SAS0071SKINNY:
			instance->instancet = &megasas_instance_ढाँचा_skinny;
			अवरोध;
		हाल PCI_DEVICE_ID_LSI_SAS1064R:
		हाल PCI_DEVICE_ID_DELL_PERC5:
		शेष:
			instance->instancet = &megasas_instance_ढाँचा_xscale;
			instance->pd_list_not_supported = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (megasas_transition_to_पढ़ोy(instance, 0)) अणु
		dev_info(&instance->pdev->dev,
			 "Failed to transition controller to ready from %s!\n",
			 __func__);
		अगर (instance->adapter_type != MFI_SERIES) अणु
			status_reg = instance->instancet->पढ़ो_fw_status_reg(
					instance);
			अगर (status_reg & MFI_RESET_ADAPTER) अणु
				अगर (megasas_adp_reset_रुको_क्रम_पढ़ोy
					(instance, true, 0) == FAILED)
					जाओ fail_पढ़ोy_state;
			पूर्ण अन्यथा अणु
				जाओ fail_पढ़ोy_state;
			पूर्ण
		पूर्ण अन्यथा अणु
			atomic_set(&instance->fw_reset_no_pci_access, 1);
			instance->instancet->adp_reset
				(instance, instance->reg_set);
			atomic_set(&instance->fw_reset_no_pci_access, 0);

			/*रुकोing क्रम about 30 second beक्रमe retry*/
			ssleep(30);

			अगर (megasas_transition_to_पढ़ोy(instance, 0))
				जाओ fail_पढ़ोy_state;
		पूर्ण

		dev_info(&instance->pdev->dev,
			 "FW restarted successfully from %s!\n",
			 __func__);
	पूर्ण

	megasas_init_ctrl_params(instance);

	अगर (megasas_set_dma_mask(instance))
		जाओ fail_पढ़ोy_state;

	अगर (megasas_alloc_ctrl_mem(instance))
		जाओ fail_alloc_dma_buf;

	अगर (megasas_alloc_ctrl_dma_buffers(instance))
		जाओ fail_alloc_dma_buf;

	fusion = instance->ctrl_context;

	अगर (instance->adapter_type >= VENTURA_SERIES) अणु
		scratch_pad_2 =
			megasas_पढ़ोl(instance,
				      &instance->reg_set->outbound_scratch_pad_2);
		instance->max_raid_mapsize = ((scratch_pad_2 >>
			MR_MAX_RAID_MAP_SIZE_OFFSET_SHIFT) &
			MR_MAX_RAID_MAP_SIZE_MASK);
	पूर्ण

	instance->enable_sdev_max_qd = enable_sdev_max_qd;

	चयन (instance->adapter_type) अणु
	हाल VENTURA_SERIES:
		fusion->pcie_bw_limitation = true;
		अवरोध;
	हाल AERO_SERIES:
		fusion->r56_भाग_offload = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Check अगर MSI-X is supported जबतक in पढ़ोy state */
	msix_enable = (instance->instancet->पढ़ो_fw_status_reg(instance) &
		       0x4000000) >> 0x1a;
	अगर (msix_enable && !msix_disable) अणु

		scratch_pad_1 = megasas_पढ़ोl
			(instance, &instance->reg_set->outbound_scratch_pad_1);
		/* Check max MSI-X vectors */
		अगर (fusion) अणु
			अगर (instance->adapter_type == THUNDERBOLT_SERIES) अणु
				/* Thunderbolt Series*/
				instance->msix_vectors = (scratch_pad_1
					& MR_MAX_REPLY_QUEUES_OFFSET) + 1;
			पूर्ण अन्यथा अणु
				instance->msix_vectors = ((scratch_pad_1
					& MR_MAX_REPLY_QUEUES_EXT_OFFSET)
					>> MR_MAX_REPLY_QUEUES_EXT_OFFSET_SHIFT) + 1;

				/*
				 * For Invader series, > 8 MSI-x vectors
				 * supported by FW/HW implies combined
				 * reply queue mode is enabled.
				 * For Ventura series, > 16 MSI-x vectors
				 * supported by FW/HW implies combined
				 * reply queue mode is enabled.
				 */
				चयन (instance->adapter_type) अणु
				हाल INVADER_SERIES:
					अगर (instance->msix_vectors > 8)
						instance->msix_combined = true;
					अवरोध;
				हाल AERO_SERIES:
				हाल VENTURA_SERIES:
					अगर (instance->msix_vectors > 16)
						instance->msix_combined = true;
					अवरोध;
				पूर्ण

				अगर (rdpq_enable)
					instance->is_rdpq = (scratch_pad_1 & MR_RDPQ_MODE_OFFSET) ?
								1 : 0;

				अगर (instance->adapter_type >= INVADER_SERIES &&
				    !instance->msix_combined) अणु
					instance->msix_load_balance = true;
					instance->smp_affinity_enable = false;
				पूर्ण

				/* Save 1-15 reply post index address to local memory
				 * Index 0 is alपढ़ोy saved from reg offset
				 * MPI2_REPLY_POST_HOST_INDEX_OFFSET
				 */
				क्रम (loop = 1; loop < MR_MAX_MSIX_REG_ARRAY; loop++) अणु
					instance->reply_post_host_index_addr[loop] =
						(u32 __iomem *)
						((u8 __iomem *)instance->reg_set +
						MPI2_SUP_REPLY_POST_HOST_INDEX_OFFSET
						+ (loop * 0x10));
				पूर्ण
			पूर्ण

			dev_info(&instance->pdev->dev,
				 "firmware supports msix\t: (%d)",
				 instance->msix_vectors);
			अगर (msix_vectors)
				instance->msix_vectors = min(msix_vectors,
					instance->msix_vectors);
		पूर्ण अन्यथा /* MFI adapters */
			instance->msix_vectors = 1;


		/*
		 * For Aero (अगर some conditions are met), driver will configure a
		 * few additional reply queues with पूर्णांकerrupt coalescing enabled.
		 * These queues with पूर्णांकerrupt coalescing enabled are called
		 * High IOPS queues and rest of reply queues (based on number of
		 * logical CPUs) are termed as Low latency queues.
		 *
		 * Total Number of reply queues = High IOPS queues + low latency queues
		 *
		 * For rest of fusion adapters, 1 additional reply queue will be
		 * reserved क्रम management commands, rest of reply queues
		 * (based on number of logical CPUs) will be used क्रम IOs and
		 * referenced as IO queues.
		 * Total Number of reply queues = 1 + IO queues
		 *
		 * MFI adapters supports single MSI-x so single reply queue
		 * will be used क्रम IO and management commands.
		 */

		पूर्णांकr_coalescing = (scratch_pad_1 & MR_INTR_COALESCING_SUPPORT_OFFSET) ?
								true : false;
		अगर (पूर्णांकr_coalescing &&
			(num_online_cpus() >= MR_HIGH_IOPS_QUEUE_COUNT) &&
			(instance->msix_vectors == MEGASAS_MAX_MSIX_QUEUES))
			instance->perf_mode = MR_BALANCED_PERF_MODE;
		अन्यथा
			instance->perf_mode = MR_LATENCY_PERF_MODE;


		अगर (instance->adapter_type == AERO_SERIES) अणु
			pcie_capability_पढ़ो_word(instance->pdev, PCI_EXP_LNKSTA, &lnksta);
			speed = lnksta & PCI_EXP_LNKSTA_CLS;

			/*
			 * For Aero, अगर PCIe link speed is <16 GT/s, then driver should operate
			 * in latency perf mode and enable R1 PCI bandwidth algorithm
			 */
			अगर (speed < 0x4) अणु
				instance->perf_mode = MR_LATENCY_PERF_MODE;
				fusion->pcie_bw_limitation = true;
			पूर्ण

			/*
			 * Perक्रमmance mode settings provided through module parameter-perf_mode will
			 * take affect only क्रम:
			 * 1. Aero family of adapters.
			 * 2. When user sets module parameter- perf_mode in range of 0-2.
			 */
			अगर ((perf_mode >= MR_BALANCED_PERF_MODE) &&
				(perf_mode <= MR_LATENCY_PERF_MODE))
				instance->perf_mode = perf_mode;
			/*
			 * If पूर्णांकr coalescing is not supported by controller FW, then IOPS
			 * and Balanced modes are not feasible.
			 */
			अगर (!पूर्णांकr_coalescing)
				instance->perf_mode = MR_LATENCY_PERF_MODE;

		पूर्ण

		अगर (instance->perf_mode == MR_BALANCED_PERF_MODE)
			instance->low_latency_index_start =
				MR_HIGH_IOPS_QUEUE_COUNT;
		अन्यथा
			instance->low_latency_index_start = 1;

		num_msix_req = num_online_cpus() + instance->low_latency_index_start;

		instance->msix_vectors = min(num_msix_req,
				instance->msix_vectors);

		megasas_alloc_irq_vectors(instance);
		अगर (!instance->msix_vectors)
			instance->msix_load_balance = false;
	पूर्ण
	/*
	 * MSI-X host index 0 is common क्रम all adapter.
	 * It is used क्रम all MPT based Adapters.
	 */
	अगर (instance->msix_combined) अणु
		instance->reply_post_host_index_addr[0] =
				(u32 *)((u8 *)instance->reg_set +
				MPI2_SUP_REPLY_POST_HOST_INDEX_OFFSET);
	पूर्ण अन्यथा अणु
		instance->reply_post_host_index_addr[0] =
			(u32 *)((u8 *)instance->reg_set +
			MPI2_REPLY_POST_HOST_INDEX_OFFSET);
	पूर्ण

	अगर (!instance->msix_vectors) अणु
		i = pci_alloc_irq_vectors(instance->pdev, 1, 1, PCI_IRQ_LEGACY);
		अगर (i < 0)
			जाओ fail_init_adapter;
	पूर्ण

	megasas_setup_reply_map(instance);

	dev_info(&instance->pdev->dev,
		"current msix/online cpus\t: (%d/%d)\n",
		instance->msix_vectors, (अचिन्हित पूर्णांक)num_online_cpus());
	dev_info(&instance->pdev->dev,
		"RDPQ mode\t: (%s)\n", instance->is_rdpq ? "enabled" : "disabled");

	tasklet_init(&instance->isr_tasklet, instance->instancet->tasklet,
		(अचिन्हित दीर्घ)instance);

	/*
	 * Below are शेष value क्रम legacy Firmware.
	 * non-fusion based controllers
	 */
	instance->fw_supported_vd_count = MAX_LOGICAL_DRIVES;
	instance->fw_supported_pd_count = MAX_PHYSICAL_DEVICES;
	/* Get operational params, sge flags, send init cmd to controller */
	अगर (instance->instancet->init_adapter(instance))
		जाओ fail_init_adapter;

	अगर (instance->adapter_type >= VENTURA_SERIES) अणु
		scratch_pad_3 =
			megasas_पढ़ोl(instance,
				      &instance->reg_set->outbound_scratch_pad_3);
		अगर ((scratch_pad_3 & MR_NVME_PAGE_SIZE_MASK) >=
			MR_DEFAULT_NVME_PAGE_SHIFT)
			instance->nvme_page_size =
				(1 << (scratch_pad_3 & MR_NVME_PAGE_SIZE_MASK));

		dev_info(&instance->pdev->dev,
			 "NVME page size\t: (%d)\n", instance->nvme_page_size);
	पूर्ण

	अगर (instance->msix_vectors ?
		megasas_setup_irqs_msix(instance, 1) :
		megasas_setup_irqs_ioapic(instance))
		जाओ fail_init_adapter;

	अगर (instance->adapter_type != MFI_SERIES)
		megasas_setup_irq_poll(instance);

	instance->instancet->enable_पूर्णांकr(instance);

	dev_info(&instance->pdev->dev, "INIT adapter done\n");

	megasas_setup_jbod_map(instance);

	अगर (megasas_get_device_list(instance) != SUCCESS) अणु
		dev_err(&instance->pdev->dev,
			"%s: megasas_get_device_list failed\n",
			__func__);
		जाओ fail_get_ld_pd_list;
	पूर्ण

	/* stream detection initialization */
	अगर (instance->adapter_type >= VENTURA_SERIES) अणु
		fusion->stream_detect_by_ld =
			kसुस्मृति(MAX_LOGICAL_DRIVES_EXT,
				माप(काष्ठा LD_STREAM_DETECT *),
				GFP_KERNEL);
		अगर (!fusion->stream_detect_by_ld) अणु
			dev_err(&instance->pdev->dev,
				"unable to allocate stream detection for pool of LDs\n");
			जाओ fail_get_ld_pd_list;
		पूर्ण
		क्रम (i = 0; i < MAX_LOGICAL_DRIVES_EXT; ++i) अणु
			fusion->stream_detect_by_ld[i] =
				kzalloc(माप(काष्ठा LD_STREAM_DETECT),
				GFP_KERNEL);
			अगर (!fusion->stream_detect_by_ld[i]) अणु
				dev_err(&instance->pdev->dev,
					"unable to allocate stream detect by LD\n ");
				क्रम (j = 0; j < i; ++j)
					kमुक्त(fusion->stream_detect_by_ld[j]);
				kमुक्त(fusion->stream_detect_by_ld);
				fusion->stream_detect_by_ld = शून्य;
				जाओ fail_get_ld_pd_list;
			पूर्ण
			fusion->stream_detect_by_ld[i]->mru_bit_map
				= MR_STREAM_BITMAP;
		पूर्ण
	पूर्ण

	/*
	 * Compute the max allowed sectors per IO: The controller info has two
	 * limits on max sectors. Driver should use the minimum of these two.
	 *
	 * 1 << stripe_sz_ops.min = max sectors per strip
	 *
	 * Note that older firmwares ( < FW ver 30) didn't report inक्रमmation
	 * to calculate max_sectors_1. So the number ended up as zero always.
	 */
	पंचांगp_sectors = 0;
	ctrl_info = instance->ctrl_info_buf;

	max_sectors_1 = (1 << ctrl_info->stripe_sz_ops.min) *
		le16_to_cpu(ctrl_info->max_strips_per_io);
	max_sectors_2 = le32_to_cpu(ctrl_info->max_request_size);

	पंचांगp_sectors = min_t(u32, max_sectors_1, max_sectors_2);

	instance->peerIsPresent = ctrl_info->cluster.peerIsPresent;
	instance->passive = ctrl_info->cluster.passive;
	स_नकल(instance->clusterId, ctrl_info->clusterId, माप(instance->clusterId));
	instance->UnevenSpanSupport =
		ctrl_info->adapterOperations2.supportUnevenSpans;
	अगर (instance->UnevenSpanSupport) अणु
		काष्ठा fusion_context *fusion = instance->ctrl_context;
		अगर (MR_ValidateMapInfo(instance, instance->map_id))
			fusion->fast_path_io = 1;
		अन्यथा
			fusion->fast_path_io = 0;

	पूर्ण
	अगर (ctrl_info->host_पूर्णांकerface.SRIOV) अणु
		instance->requestorId = ctrl_info->iov.requestorId;
		अगर (instance->pdev->device == PCI_DEVICE_ID_LSI_PLASMA) अणु
			अगर (!ctrl_info->adapterOperations2.activePassive)
			    instance->Plयंत्रaFW111 = 1;

			dev_info(&instance->pdev->dev, "SR-IOV: firmware type: %s\n",
			    instance->Plयंत्रaFW111 ? "1.11" : "new");

			अगर (instance->Plयंत्रaFW111) अणु
			    iovPtr = (काष्ठा IOV_111 *)
				((अचिन्हित अक्षर *)ctrl_info + IOV_111_OFFSET);
			    instance->requestorId = iovPtr->requestorId;
			पूर्ण
		पूर्ण
		dev_info(&instance->pdev->dev, "SRIOV: VF requestorId %d\n",
			instance->requestorId);
	पूर्ण

	instance->crash_dump_fw_support =
		ctrl_info->adapterOperations3.supportCrashDump;
	instance->crash_dump_drv_support =
		(instance->crash_dump_fw_support &&
		instance->crash_dump_buf);
	अगर (instance->crash_dump_drv_support)
		megasas_set_crash_dump_params(instance,
			MR_CRASH_BUF_TURN_OFF);

	अन्यथा अणु
		अगर (instance->crash_dump_buf)
			dma_मुक्त_coherent(&instance->pdev->dev,
				CRASH_DMA_BUF_SIZE,
				instance->crash_dump_buf,
				instance->crash_dump_h);
		instance->crash_dump_buf = शून्य;
	पूर्ण

	अगर (instance->snapdump_रुको_समय) अणु
		megasas_get_snapdump_properties(instance);
		dev_info(&instance->pdev->dev, "Snap dump wait time\t: %d\n",
			 instance->snapdump_रुको_समय);
	पूर्ण

	dev_info(&instance->pdev->dev,
		"pci id\t\t: (0x%04x)/(0x%04x)/(0x%04x)/(0x%04x)\n",
		le16_to_cpu(ctrl_info->pci.venकरोr_id),
		le16_to_cpu(ctrl_info->pci.device_id),
		le16_to_cpu(ctrl_info->pci.sub_venकरोr_id),
		le16_to_cpu(ctrl_info->pci.sub_device_id));
	dev_info(&instance->pdev->dev, "unevenspan support	: %s\n",
		instance->UnevenSpanSupport ? "yes" : "no");
	dev_info(&instance->pdev->dev, "firmware crash dump	: %s\n",
		instance->crash_dump_drv_support ? "yes" : "no");
	dev_info(&instance->pdev->dev, "JBOD sequence map	: %s\n",
		instance->use_seqnum_jbod_fp ? "enabled" : "disabled");

	instance->max_sectors_per_req = instance->max_num_sge *
						SGE_BUFFER_SIZE / 512;
	अगर (पंचांगp_sectors && (instance->max_sectors_per_req > पंचांगp_sectors))
		instance->max_sectors_per_req = पंचांगp_sectors;

	/* Check क्रम valid throttlequeuedepth module parameter */
	अगर (throttlequeuedepth &&
			throttlequeuedepth <= instance->max_scsi_cmds)
		instance->throttlequeuedepth = throttlequeuedepth;
	अन्यथा
		instance->throttlequeuedepth =
				MEGASAS_THROTTLE_QUEUE_DEPTH;

	अगर ((resetरुकोसमय < 1) ||
	    (resetरुकोसमय > MEGASAS_RESET_WAIT_TIME))
		resetरुकोसमय = MEGASAS_RESET_WAIT_TIME;

	अगर ((scmd_समयout < 10) || (scmd_समयout > MEGASAS_DEFAULT_CMD_TIMEOUT))
		scmd_समयout = MEGASAS_DEFAULT_CMD_TIMEOUT;

	/* Launch SR-IOV heartbeat समयr */
	अगर (instance->requestorId) अणु
		अगर (!megasas_sriov_start_heartbeat(instance, 1)) अणु
			megasas_start_समयr(instance);
		पूर्ण अन्यथा अणु
			instance->skip_heartbeat_समयr_del = 1;
			जाओ fail_get_ld_pd_list;
		पूर्ण
	पूर्ण

	/*
	 * Create and start watchकरोg thपढ़ो which will monitor
	 * controller state every 1 sec and trigger OCR when
	 * it enters fault state
	 */
	अगर (instance->adapter_type != MFI_SERIES)
		अगर (megasas_fusion_start_watchकरोg(instance) != SUCCESS)
			जाओ fail_start_watchकरोg;

	वापस 0;

fail_start_watchकरोg:
	अगर (instance->requestorId && !instance->skip_heartbeat_समयr_del)
		del_समयr_sync(&instance->sriov_heartbeat_समयr);
fail_get_ld_pd_list:
	instance->instancet->disable_पूर्णांकr(instance);
	megasas_destroy_irqs(instance);
fail_init_adapter:
	अगर (instance->msix_vectors)
		pci_मुक्त_irq_vectors(instance->pdev);
	instance->msix_vectors = 0;
fail_alloc_dma_buf:
	megasas_मुक्त_ctrl_dma_buffers(instance);
	megasas_मुक्त_ctrl_mem(instance);
fail_पढ़ोy_state:
	iounmap(instance->reg_set);

fail_ioremap:
	pci_release_selected_regions(instance->pdev, 1<<instance->bar);

	dev_err(&instance->pdev->dev, "Failed from %s %d\n",
		__func__, __LINE__);
	वापस -EINVAL;
पूर्ण

/**
 * megasas_release_mfi -	Reverses the FW initialization
 * @instance:			Adapter soft state
 */
अटल व्योम megasas_release_mfi(काष्ठा megasas_instance *instance)
अणु
	u32 reply_q_sz = माप(u32) *(instance->max_mfi_cmds + 1);

	अगर (instance->reply_queue)
		dma_मुक्त_coherent(&instance->pdev->dev, reply_q_sz,
			    instance->reply_queue, instance->reply_queue_h);

	megasas_मुक्त_cmds(instance);

	iounmap(instance->reg_set);

	pci_release_selected_regions(instance->pdev, 1<<instance->bar);
पूर्ण

/**
 * megasas_get_seq_num -	Gets latest event sequence numbers
 * @instance:			Adapter soft state
 * @eli:			FW event log sequence numbers inक्रमmation
 *
 * FW मुख्यtains a log of all events in a non-अस्थिर area. Upper layers would
 * usually find out the latest sequence number of the events, the seq number at
 * the boot etc. They would "read" all the events below the latest seq number
 * by issuing a direct fw cmd (DCMD). For the future events (beyond latest seq
 * number), they would subsribe to AEN (asynchronous event notअगरication) and
 * रुको क्रम the events to happen.
 */
अटल पूर्णांक
megasas_get_seq_num(काष्ठा megasas_instance *instance,
		    काष्ठा megasas_evt_log_info *eli)
अणु
	काष्ठा megasas_cmd *cmd;
	काष्ठा megasas_dcmd_frame *dcmd;
	काष्ठा megasas_evt_log_info *el_info;
	dma_addr_t el_info_h = 0;
	पूर्णांक ret;

	cmd = megasas_get_cmd(instance);

	अगर (!cmd) अणु
		वापस -ENOMEM;
	पूर्ण

	dcmd = &cmd->frame->dcmd;
	el_info = dma_alloc_coherent(&instance->pdev->dev,
				     माप(काष्ठा megasas_evt_log_info),
				     &el_info_h, GFP_KERNEL);
	अगर (!el_info) अणु
		megasas_वापस_cmd(instance, cmd);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(dcmd->mbox.b, 0, MFI_MBOX_SIZE);

	dcmd->cmd = MFI_CMD_DCMD;
	dcmd->cmd_status = 0x0;
	dcmd->sge_count = 1;
	dcmd->flags = MFI_FRAME_सूची_READ;
	dcmd->समयout = 0;
	dcmd->pad_0 = 0;
	dcmd->data_xfer_len = cpu_to_le32(माप(काष्ठा megasas_evt_log_info));
	dcmd->opcode = cpu_to_le32(MR_DCMD_CTRL_EVENT_GET_INFO);

	megasas_set_dma_settings(instance, dcmd, el_info_h,
				 माप(काष्ठा megasas_evt_log_info));

	ret = megasas_issue_blocked_cmd(instance, cmd, MFI_IO_TIMEOUT_SECS);
	अगर (ret != DCMD_SUCCESS) अणु
		dev_err(&instance->pdev->dev, "Failed from %s %d\n",
			__func__, __LINE__);
		जाओ dcmd_failed;
	पूर्ण

	/*
	 * Copy the data back पूर्णांकo callers buffer
	 */
	eli->newest_seq_num = el_info->newest_seq_num;
	eli->oldest_seq_num = el_info->oldest_seq_num;
	eli->clear_seq_num = el_info->clear_seq_num;
	eli->shutकरोwn_seq_num = el_info->shutकरोwn_seq_num;
	eli->boot_seq_num = el_info->boot_seq_num;

dcmd_failed:
	dma_मुक्त_coherent(&instance->pdev->dev,
			माप(काष्ठा megasas_evt_log_info),
			el_info, el_info_h);

	megasas_वापस_cmd(instance, cmd);

	वापस ret;
पूर्ण

/**
 * megasas_रेजिस्टर_aen -	Registers क्रम asynchronous event notअगरication
 * @instance:			Adapter soft state
 * @seq_num:			The starting sequence number
 * @class_locale_word:		Class of the event
 *
 * This function subscribes क्रम AEN क्रम events beyond the @seq_num. It requests
 * to be notअगरied अगर and only अगर the event is of type @class_locale
 */
अटल पूर्णांक
megasas_रेजिस्टर_aen(काष्ठा megasas_instance *instance, u32 seq_num,
		     u32 class_locale_word)
अणु
	पूर्णांक ret_val;
	काष्ठा megasas_cmd *cmd;
	काष्ठा megasas_dcmd_frame *dcmd;
	जोड़ megasas_evt_class_locale curr_aen;
	जोड़ megasas_evt_class_locale prev_aen;

	/*
	 * If there an AEN pending alपढ़ोy (aen_cmd), check अगर the
	 * class_locale of that pending AEN is inclusive of the new
	 * AEN request we currently have. If it is, then we करोn't have
	 * to करो anything. In other words, whichever events the current
	 * AEN request is subscribing to, have alपढ़ोy been subscribed
	 * to.
	 *
	 * If the old_cmd is _not_ inclusive, then we have to पात
	 * that command, क्रमm a class_locale that is superset of both
	 * old and current and re-issue to the FW
	 */

	curr_aen.word = class_locale_word;

	अगर (instance->aen_cmd) अणु

		prev_aen.word =
			le32_to_cpu(instance->aen_cmd->frame->dcmd.mbox.w[1]);

		अगर ((curr_aen.members.class < MFI_EVT_CLASS_DEBUG) ||
		    (curr_aen.members.class > MFI_EVT_CLASS_DEAD)) अणु
			dev_info(&instance->pdev->dev,
				 "%s %d out of range class %d send by application\n",
				 __func__, __LINE__, curr_aen.members.class);
			वापस 0;
		पूर्ण

		/*
		 * A class whose क्रमागत value is smaller is inclusive of all
		 * higher values. If a PROGRESS (= -1) was previously
		 * रेजिस्टरed, then a new registration requests क्रम higher
		 * classes need not be sent to FW. They are स्वतःmatically
		 * included.
		 *
		 * Locale numbers करोn't have such hierarchy. They are biपंचांगap
		 * values
		 */
		अगर ((prev_aen.members.class <= curr_aen.members.class) &&
		    !((prev_aen.members.locale & curr_aen.members.locale) ^
		      curr_aen.members.locale)) अणु
			/*
			 * Previously issued event registration includes
			 * current request. Nothing to करो.
			 */
			वापस 0;
		पूर्ण अन्यथा अणु
			curr_aen.members.locale |= prev_aen.members.locale;

			अगर (prev_aen.members.class < curr_aen.members.class)
				curr_aen.members.class = prev_aen.members.class;

			instance->aen_cmd->पात_aen = 1;
			ret_val = megasas_issue_blocked_पात_cmd(instance,
								  instance->
								  aen_cmd, 30);

			अगर (ret_val) अणु
				dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "Failed to abort "
				       "previous AEN command\n");
				वापस ret_val;
			पूर्ण
		पूर्ण
	पूर्ण

	cmd = megasas_get_cmd(instance);

	अगर (!cmd)
		वापस -ENOMEM;

	dcmd = &cmd->frame->dcmd;

	स_रखो(instance->evt_detail, 0, माप(काष्ठा megasas_evt_detail));

	/*
	 * Prepare DCMD क्रम aen registration
	 */
	स_रखो(dcmd->mbox.b, 0, MFI_MBOX_SIZE);

	dcmd->cmd = MFI_CMD_DCMD;
	dcmd->cmd_status = 0x0;
	dcmd->sge_count = 1;
	dcmd->flags = MFI_FRAME_सूची_READ;
	dcmd->समयout = 0;
	dcmd->pad_0 = 0;
	dcmd->data_xfer_len = cpu_to_le32(माप(काष्ठा megasas_evt_detail));
	dcmd->opcode = cpu_to_le32(MR_DCMD_CTRL_EVENT_WAIT);
	dcmd->mbox.w[0] = cpu_to_le32(seq_num);
	instance->last_seq_num = seq_num;
	dcmd->mbox.w[1] = cpu_to_le32(curr_aen.word);

	megasas_set_dma_settings(instance, dcmd, instance->evt_detail_h,
				 माप(काष्ठा megasas_evt_detail));

	अगर (instance->aen_cmd != शून्य) अणु
		megasas_वापस_cmd(instance, cmd);
		वापस 0;
	पूर्ण

	/*
	 * Store reference to the cmd used to रेजिस्टर क्रम AEN. When an
	 * application wants us to रेजिस्टर क्रम AEN, we have to पात this
	 * cmd and re-रेजिस्टर with a new EVENT LOCALE supplied by that app
	 */
	instance->aen_cmd = cmd;

	/*
	 * Issue the aen registration frame
	 */
	instance->instancet->issue_dcmd(instance, cmd);

	वापस 0;
पूर्ण

/* megasas_get_target_prop - Send DCMD with below details to firmware.
 *
 * This DCMD will fetch few properties of LD/प्रणाली PD defined
 * in MR_TARGET_DEV_PROPERTIES. eg. Queue Depth, MDTS value.
 *
 * DCMD send by drivers whenever new target is added to the OS.
 *
 * dcmd.opcode         - MR_DCMD_DEV_GET_TARGET_PROP
 * dcmd.mbox.b[0]      - DCMD is to be fired क्रम LD or प्रणाली PD.
 *                       0 = प्रणाली PD, 1 = LD.
 * dcmd.mbox.s[1]      - TargetID क्रम LD/प्रणाली PD.
 * dcmd.sge IN         - Poपूर्णांकer to वापस MR_TARGET_DEV_PROPERTIES.
 *
 * @instance:		Adapter soft state
 * @sdev:		OS provided scsi device
 *
 * Returns 0 on success non-zero on failure.
 */
पूर्णांक
megasas_get_target_prop(काष्ठा megasas_instance *instance,
			काष्ठा scsi_device *sdev)
अणु
	पूर्णांक ret;
	काष्ठा megasas_cmd *cmd;
	काष्ठा megasas_dcmd_frame *dcmd;
	u16 targetId = ((sdev->channel % 2) * MEGASAS_MAX_DEV_PER_CHANNEL) +
			sdev->id;

	cmd = megasas_get_cmd(instance);

	अगर (!cmd) अणु
		dev_err(&instance->pdev->dev,
			"Failed to get cmd %s\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	dcmd = &cmd->frame->dcmd;

	स_रखो(instance->tgt_prop, 0, माप(*instance->tgt_prop));
	स_रखो(dcmd->mbox.b, 0, MFI_MBOX_SIZE);
	dcmd->mbox.b[0] = MEGASAS_IS_LOGICAL(sdev);

	dcmd->mbox.s[1] = cpu_to_le16(targetId);
	dcmd->cmd = MFI_CMD_DCMD;
	dcmd->cmd_status = 0xFF;
	dcmd->sge_count = 1;
	dcmd->flags = MFI_FRAME_सूची_READ;
	dcmd->समयout = 0;
	dcmd->pad_0 = 0;
	dcmd->data_xfer_len =
		cpu_to_le32(माप(काष्ठा MR_TARGET_PROPERTIES));
	dcmd->opcode = cpu_to_le32(MR_DCMD_DRV_GET_TARGET_PROP);

	megasas_set_dma_settings(instance, dcmd, instance->tgt_prop_h,
				 माप(काष्ठा MR_TARGET_PROPERTIES));

	अगर ((instance->adapter_type != MFI_SERIES) &&
	    !instance->mask_पूर्णांकerrupts)
		ret = megasas_issue_blocked_cmd(instance,
						cmd, MFI_IO_TIMEOUT_SECS);
	अन्यथा
		ret = megasas_issue_polled(instance, cmd);

	चयन (ret) अणु
	हाल DCMD_TIMEOUT:
		चयन (dcmd_समयout_ocr_possible(instance)) अणु
		हाल INITIATE_OCR:
			cmd->flags |= DRV_DCMD_SKIP_REFIRE;
			mutex_unlock(&instance->reset_mutex);
			megasas_reset_fusion(instance->host,
					     MFI_IO_TIMEOUT_OCR);
			mutex_lock(&instance->reset_mutex);
			अवरोध;
		हाल KILL_ADAPTER:
			megaraid_sas_समाप्त_hba(instance);
			अवरोध;
		हाल IGNORE_TIMEOUT:
			dev_info(&instance->pdev->dev,
				 "Ignore DCMD timeout: %s %d\n",
				 __func__, __LINE__);
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		megasas_वापस_cmd(instance, cmd);
	पूर्ण
	अगर (ret != DCMD_SUCCESS)
		dev_err(&instance->pdev->dev,
			"return from %s %d return value %d\n",
			__func__, __LINE__, ret);

	वापस ret;
पूर्ण

/**
 * megasas_start_aen -	Subscribes to AEN during driver load समय
 * @instance:		Adapter soft state
 */
अटल पूर्णांक megasas_start_aen(काष्ठा megasas_instance *instance)
अणु
	काष्ठा megasas_evt_log_info eli;
	जोड़ megasas_evt_class_locale class_locale;

	/*
	 * Get the latest sequence number from FW
	 */
	स_रखो(&eli, 0, माप(eli));

	अगर (megasas_get_seq_num(instance, &eli))
		वापस -1;

	/*
	 * Register AEN with FW क्रम latest sequence number plus 1
	 */
	class_locale.members.reserved = 0;
	class_locale.members.locale = MR_EVT_LOCALE_ALL;
	class_locale.members.class = MR_EVT_CLASS_DEBUG;

	वापस megasas_रेजिस्टर_aen(instance,
			le32_to_cpu(eli.newest_seq_num) + 1,
			class_locale.word);
पूर्ण

/**
 * megasas_io_attach -	Attaches this driver to SCSI mid-layer
 * @instance:		Adapter soft state
 */
अटल पूर्णांक megasas_io_attach(काष्ठा megasas_instance *instance)
अणु
	काष्ठा Scsi_Host *host = instance->host;

	/*
	 * Export parameters required by SCSI mid-layer
	 */
	host->unique_id = instance->unique_id;
	host->can_queue = instance->max_scsi_cmds;
	host->this_id = instance->init_id;
	host->sg_tablesize = instance->max_num_sge;

	अगर (instance->fw_support_ieee)
		instance->max_sectors_per_req = MEGASAS_MAX_SECTORS_IEEE;

	/*
	 * Check अगर the module parameter value क्रम max_sectors can be used
	 */
	अगर (max_sectors && max_sectors < instance->max_sectors_per_req)
		instance->max_sectors_per_req = max_sectors;
	अन्यथा अणु
		अगर (max_sectors) अणु
			अगर (((instance->pdev->device ==
				PCI_DEVICE_ID_LSI_SAS1078GEN2) ||
				(instance->pdev->device ==
				PCI_DEVICE_ID_LSI_SAS0079GEN2)) &&
				(max_sectors <= MEGASAS_MAX_SECTORS)) अणु
				instance->max_sectors_per_req = max_sectors;
			पूर्ण अन्यथा अणु
			dev_info(&instance->pdev->dev, "max_sectors should be > 0"
				"and <= %d (or < 1MB for GEN2 controller)\n",
				instance->max_sectors_per_req);
			पूर्ण
		पूर्ण
	पूर्ण

	host->max_sectors = instance->max_sectors_per_req;
	host->cmd_per_lun = MEGASAS_DEFAULT_CMD_PER_LUN;
	host->max_channel = MEGASAS_MAX_CHANNELS - 1;
	host->max_id = MEGASAS_MAX_DEV_PER_CHANNEL;
	host->max_lun = MEGASAS_MAX_LUN;
	host->max_cmd_len = 16;

	/* Use shared host tagset only क्रम fusion adaptors
	 * अगर there are managed पूर्णांकerrupts (smp affinity enabled हाल).
	 * Single msix_vectors in kdump, so shared host tag is also disabled.
	 */

	host->host_tagset = 0;
	host->nr_hw_queues = 1;

	अगर ((instance->adapter_type != MFI_SERIES) &&
		(instance->msix_vectors > instance->low_latency_index_start) &&
		host_tagset_enable &&
		instance->smp_affinity_enable) अणु
		host->host_tagset = 1;
		host->nr_hw_queues = instance->msix_vectors -
			instance->low_latency_index_start + instance->iopoll_q_count;
		अगर (instance->iopoll_q_count)
			host->nr_maps = 3;
	पूर्ण अन्यथा अणु
		instance->iopoll_q_count = 0;
	पूर्ण

	dev_info(&instance->pdev->dev,
		"Max firmware commands: %d shared with default "
		"hw_queues = %d poll_queues %d\n", instance->max_fw_cmds,
		host->nr_hw_queues - instance->iopoll_q_count,
		instance->iopoll_q_count);
	/*
	 * Notअगरy the mid-layer about the new controller
	 */
	अगर (scsi_add_host(host, &instance->pdev->dev)) अणु
		dev_err(&instance->pdev->dev,
			"Failed to add host from %s %d\n",
			__func__, __LINE__);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * megasas_set_dma_mask -	Set DMA mask क्रम supported controllers
 *
 * @instance:		Adapter soft state
 * Description:
 *
 * For Ventura, driver/FW will operate in 63bit DMA addresses.
 *
 * For invader-
 *	By शेष, driver/FW will operate in 32bit DMA addresses
 *	क्रम consistent DMA mapping but अगर 32 bit consistent
 *	DMA mask fails, driver will try with 63 bit consistent
 *	mask provided FW is true 63bit DMA capable
 *
 * For older controllers(Thunderbolt and MFI based adapters)-
 *	driver/FW will operate in 32 bit consistent DMA addresses.
 */
अटल पूर्णांक
megasas_set_dma_mask(काष्ठा megasas_instance *instance)
अणु
	u64 consistent_mask;
	काष्ठा pci_dev *pdev;
	u32 scratch_pad_1;

	pdev = instance->pdev;
	consistent_mask = (instance->adapter_type >= VENTURA_SERIES) ?
				DMA_BIT_MASK(63) : DMA_BIT_MASK(32);

	अगर (IS_DMA64) अणु
		अगर (dma_set_mask(&pdev->dev, DMA_BIT_MASK(63)) &&
		    dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32)))
			जाओ fail_set_dma_mask;

		अगर ((*pdev->dev.dma_mask == DMA_BIT_MASK(63)) &&
		    (dma_set_coherent_mask(&pdev->dev, consistent_mask) &&
		     dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32)))) अणु
			/*
			 * If 32 bit DMA mask fails, then try क्रम 64 bit mask
			 * क्रम FW capable of handling 64 bit DMA.
			 */
			scratch_pad_1 = megasas_पढ़ोl
				(instance, &instance->reg_set->outbound_scratch_pad_1);

			अगर (!(scratch_pad_1 & MR_CAN_HANDLE_64_BIT_DMA_OFFSET))
				जाओ fail_set_dma_mask;
			अन्यथा अगर (dma_set_mask_and_coherent(&pdev->dev,
							   DMA_BIT_MASK(63)))
				जाओ fail_set_dma_mask;
		पूर्ण
	पूर्ण अन्यथा अगर (dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32)))
		जाओ fail_set_dma_mask;

	अगर (pdev->dev.coherent_dma_mask == DMA_BIT_MASK(32))
		instance->consistent_mask_64bit = false;
	अन्यथा
		instance->consistent_mask_64bit = true;

	dev_info(&pdev->dev, "%s bit DMA mask and %s bit consistent mask\n",
		 ((*pdev->dev.dma_mask == DMA_BIT_MASK(63)) ? "63" : "32"),
		 (instance->consistent_mask_64bit ? "63" : "32"));

	वापस 0;

fail_set_dma_mask:
	dev_err(&pdev->dev, "Failed to set DMA mask\n");
	वापस -1;

पूर्ण

/*
 * megasas_set_adapter_type -	Set adapter type.
 *				Supported controllers can be भागided in
 *				dअगरferent categories-
 *					क्रमागत MR_ADAPTER_TYPE अणु
 *						MFI_SERIES = 1,
 *						THUNDERBOLT_SERIES = 2,
 *						INVADER_SERIES = 3,
 *						VENTURA_SERIES = 4,
 *						AERO_SERIES = 5,
 *					पूर्ण;
 * @instance:			Adapter soft state
 * वापस:			व्योम
 */
अटल अंतरभूत व्योम megasas_set_adapter_type(काष्ठा megasas_instance *instance)
अणु
	अगर ((instance->pdev->venकरोr == PCI_VENDOR_ID_DELL) &&
	    (instance->pdev->device == PCI_DEVICE_ID_DELL_PERC5)) अणु
		instance->adapter_type = MFI_SERIES;
	पूर्ण अन्यथा अणु
		चयन (instance->pdev->device) अणु
		हाल PCI_DEVICE_ID_LSI_AERO_10E1:
		हाल PCI_DEVICE_ID_LSI_AERO_10E2:
		हाल PCI_DEVICE_ID_LSI_AERO_10E5:
		हाल PCI_DEVICE_ID_LSI_AERO_10E6:
			instance->adapter_type = AERO_SERIES;
			अवरोध;
		हाल PCI_DEVICE_ID_LSI_VENTURA:
		हाल PCI_DEVICE_ID_LSI_CRUSADER:
		हाल PCI_DEVICE_ID_LSI_HARPOON:
		हाल PCI_DEVICE_ID_LSI_TOMCAT:
		हाल PCI_DEVICE_ID_LSI_VENTURA_4PORT:
		हाल PCI_DEVICE_ID_LSI_CRUSADER_4PORT:
			instance->adapter_type = VENTURA_SERIES;
			अवरोध;
		हाल PCI_DEVICE_ID_LSI_FUSION:
		हाल PCI_DEVICE_ID_LSI_PLASMA:
			instance->adapter_type = THUNDERBOLT_SERIES;
			अवरोध;
		हाल PCI_DEVICE_ID_LSI_INVADER:
		हाल PCI_DEVICE_ID_LSI_INTRUDER:
		हाल PCI_DEVICE_ID_LSI_INTRUDER_24:
		हाल PCI_DEVICE_ID_LSI_CUTLASS_52:
		हाल PCI_DEVICE_ID_LSI_CUTLASS_53:
		हाल PCI_DEVICE_ID_LSI_FURY:
			instance->adapter_type = INVADER_SERIES;
			अवरोध;
		शेष: /* For all other supported controllers */
			instance->adapter_type = MFI_SERIES;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक megasas_alloc_mfi_ctrl_mem(काष्ठा megasas_instance *instance)
अणु
	instance->producer = dma_alloc_coherent(&instance->pdev->dev,
			माप(u32), &instance->producer_h, GFP_KERNEL);
	instance->consumer = dma_alloc_coherent(&instance->pdev->dev,
			माप(u32), &instance->consumer_h, GFP_KERNEL);

	अगर (!instance->producer || !instance->consumer) अणु
		dev_err(&instance->pdev->dev,
			"Failed to allocate memory for producer, consumer\n");
		वापस -1;
	पूर्ण

	*instance->producer = 0;
	*instance->consumer = 0;
	वापस 0;
पूर्ण

/**
 * megasas_alloc_ctrl_mem -	Allocate per controller memory क्रम core data
 *				काष्ठाures which are not common across MFI
 *				adapters and fusion adapters.
 *				For MFI based adapters, allocate producer and
 *				consumer buffers. For fusion adapters, allocate
 *				memory क्रम fusion context.
 * @instance:			Adapter soft state
 * वापस:			0 क्रम SUCCESS
 */
अटल पूर्णांक megasas_alloc_ctrl_mem(काष्ठा megasas_instance *instance)
अणु
	instance->reply_map = kसुस्मृति(nr_cpu_ids, माप(अचिन्हित पूर्णांक),
				      GFP_KERNEL);
	अगर (!instance->reply_map)
		वापस -ENOMEM;

	चयन (instance->adapter_type) अणु
	हाल MFI_SERIES:
		अगर (megasas_alloc_mfi_ctrl_mem(instance))
			जाओ fail;
		अवरोध;
	हाल AERO_SERIES:
	हाल VENTURA_SERIES:
	हाल THUNDERBOLT_SERIES:
	हाल INVADER_SERIES:
		अगर (megasas_alloc_fusion_context(instance))
			जाओ fail;
		अवरोध;
	पूर्ण

	वापस 0;
 fail:
	kमुक्त(instance->reply_map);
	instance->reply_map = शून्य;
	वापस -ENOMEM;
पूर्ण

/*
 * megasas_मुक्त_ctrl_mem -	Free fusion context क्रम fusion adapters and
 *				producer, consumer buffers क्रम MFI adapters
 *
 * @instance -			Adapter soft instance
 *
 */
अटल अंतरभूत व्योम megasas_मुक्त_ctrl_mem(काष्ठा megasas_instance *instance)
अणु
	kमुक्त(instance->reply_map);
	अगर (instance->adapter_type == MFI_SERIES) अणु
		अगर (instance->producer)
			dma_मुक्त_coherent(&instance->pdev->dev, माप(u32),
					    instance->producer,
					    instance->producer_h);
		अगर (instance->consumer)
			dma_मुक्त_coherent(&instance->pdev->dev, माप(u32),
					    instance->consumer,
					    instance->consumer_h);
	पूर्ण अन्यथा अणु
		megasas_मुक्त_fusion_context(instance);
	पूर्ण
पूर्ण

/**
 * megasas_alloc_ctrl_dma_buffers -	Allocate consistent DMA buffers during
 *					driver load समय
 *
 * @instance:				Adapter soft instance
 *
 * @वापस:				O क्रम SUCCESS
 */
अटल अंतरभूत
पूर्णांक megasas_alloc_ctrl_dma_buffers(काष्ठा megasas_instance *instance)
अणु
	काष्ठा pci_dev *pdev = instance->pdev;
	काष्ठा fusion_context *fusion = instance->ctrl_context;

	instance->evt_detail = dma_alloc_coherent(&pdev->dev,
			माप(काष्ठा megasas_evt_detail),
			&instance->evt_detail_h, GFP_KERNEL);

	अगर (!instance->evt_detail) अणु
		dev_err(&instance->pdev->dev,
			"Failed to allocate event detail buffer\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (fusion) अणु
		fusion->ioc_init_request =
			dma_alloc_coherent(&pdev->dev,
					   माप(काष्ठा MPI2_IOC_INIT_REQUEST),
					   &fusion->ioc_init_request_phys,
					   GFP_KERNEL);

		अगर (!fusion->ioc_init_request) अणु
			dev_err(&pdev->dev,
				"Failed to allocate PD list buffer\n");
			वापस -ENOMEM;
		पूर्ण

		instance->snapdump_prop = dma_alloc_coherent(&pdev->dev,
				माप(काष्ठा MR_SNAPDUMP_PROPERTIES),
				&instance->snapdump_prop_h, GFP_KERNEL);

		अगर (!instance->snapdump_prop)
			dev_err(&pdev->dev,
				"Failed to allocate snapdump properties buffer\n");

		instance->host_device_list_buf = dma_alloc_coherent(&pdev->dev,
							HOST_DEVICE_LIST_SZ,
							&instance->host_device_list_buf_h,
							GFP_KERNEL);

		अगर (!instance->host_device_list_buf) अणु
			dev_err(&pdev->dev,
				"Failed to allocate targetid list buffer\n");
			वापस -ENOMEM;
		पूर्ण

	पूर्ण

	instance->pd_list_buf =
		dma_alloc_coherent(&pdev->dev,
				     MEGASAS_MAX_PD * माप(काष्ठा MR_PD_LIST),
				     &instance->pd_list_buf_h, GFP_KERNEL);

	अगर (!instance->pd_list_buf) अणु
		dev_err(&pdev->dev, "Failed to allocate PD list buffer\n");
		वापस -ENOMEM;
	पूर्ण

	instance->ctrl_info_buf =
		dma_alloc_coherent(&pdev->dev,
				     माप(काष्ठा megasas_ctrl_info),
				     &instance->ctrl_info_buf_h, GFP_KERNEL);

	अगर (!instance->ctrl_info_buf) अणु
		dev_err(&pdev->dev,
			"Failed to allocate controller info buffer\n");
		वापस -ENOMEM;
	पूर्ण

	instance->ld_list_buf =
		dma_alloc_coherent(&pdev->dev,
				     माप(काष्ठा MR_LD_LIST),
				     &instance->ld_list_buf_h, GFP_KERNEL);

	अगर (!instance->ld_list_buf) अणु
		dev_err(&pdev->dev, "Failed to allocate LD list buffer\n");
		वापस -ENOMEM;
	पूर्ण

	instance->ld_targetid_list_buf =
		dma_alloc_coherent(&pdev->dev,
				माप(काष्ठा MR_LD_TARGETID_LIST),
				&instance->ld_targetid_list_buf_h, GFP_KERNEL);

	अगर (!instance->ld_targetid_list_buf) अणु
		dev_err(&pdev->dev,
			"Failed to allocate LD targetid list buffer\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (!reset_devices) अणु
		instance->प्रणाली_info_buf =
			dma_alloc_coherent(&pdev->dev,
					माप(काष्ठा MR_DRV_SYSTEM_INFO),
					&instance->प्रणाली_info_h, GFP_KERNEL);
		instance->pd_info =
			dma_alloc_coherent(&pdev->dev,
					माप(काष्ठा MR_PD_INFO),
					&instance->pd_info_h, GFP_KERNEL);
		instance->tgt_prop =
			dma_alloc_coherent(&pdev->dev,
					माप(काष्ठा MR_TARGET_PROPERTIES),
					&instance->tgt_prop_h, GFP_KERNEL);
		instance->crash_dump_buf =
			dma_alloc_coherent(&pdev->dev, CRASH_DMA_BUF_SIZE,
					&instance->crash_dump_h, GFP_KERNEL);

		अगर (!instance->प्रणाली_info_buf)
			dev_err(&instance->pdev->dev,
				"Failed to allocate system info buffer\n");

		अगर (!instance->pd_info)
			dev_err(&instance->pdev->dev,
				"Failed to allocate pd_info buffer\n");

		अगर (!instance->tgt_prop)
			dev_err(&instance->pdev->dev,
				"Failed to allocate tgt_prop buffer\n");

		अगर (!instance->crash_dump_buf)
			dev_err(&instance->pdev->dev,
				"Failed to allocate crash dump buffer\n");
	पूर्ण

	वापस 0;
पूर्ण

/*
 * megasas_मुक्त_ctrl_dma_buffers -	Free consistent DMA buffers allocated
 *					during driver load समय
 *
 * @instance-				Adapter soft instance
 *
 */
अटल अंतरभूत
व्योम megasas_मुक्त_ctrl_dma_buffers(काष्ठा megasas_instance *instance)
अणु
	काष्ठा pci_dev *pdev = instance->pdev;
	काष्ठा fusion_context *fusion = instance->ctrl_context;

	अगर (instance->evt_detail)
		dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा megasas_evt_detail),
				    instance->evt_detail,
				    instance->evt_detail_h);

	अगर (fusion && fusion->ioc_init_request)
		dma_मुक्त_coherent(&pdev->dev,
				  माप(काष्ठा MPI2_IOC_INIT_REQUEST),
				  fusion->ioc_init_request,
				  fusion->ioc_init_request_phys);

	अगर (instance->pd_list_buf)
		dma_मुक्त_coherent(&pdev->dev,
				    MEGASAS_MAX_PD * माप(काष्ठा MR_PD_LIST),
				    instance->pd_list_buf,
				    instance->pd_list_buf_h);

	अगर (instance->ld_list_buf)
		dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा MR_LD_LIST),
				    instance->ld_list_buf,
				    instance->ld_list_buf_h);

	अगर (instance->ld_targetid_list_buf)
		dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा MR_LD_TARGETID_LIST),
				    instance->ld_targetid_list_buf,
				    instance->ld_targetid_list_buf_h);

	अगर (instance->ctrl_info_buf)
		dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा megasas_ctrl_info),
				    instance->ctrl_info_buf,
				    instance->ctrl_info_buf_h);

	अगर (instance->प्रणाली_info_buf)
		dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा MR_DRV_SYSTEM_INFO),
				    instance->प्रणाली_info_buf,
				    instance->प्रणाली_info_h);

	अगर (instance->pd_info)
		dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा MR_PD_INFO),
				    instance->pd_info, instance->pd_info_h);

	अगर (instance->tgt_prop)
		dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा MR_TARGET_PROPERTIES),
				    instance->tgt_prop, instance->tgt_prop_h);

	अगर (instance->crash_dump_buf)
		dma_मुक्त_coherent(&pdev->dev, CRASH_DMA_BUF_SIZE,
				    instance->crash_dump_buf,
				    instance->crash_dump_h);

	अगर (instance->snapdump_prop)
		dma_मुक्त_coherent(&pdev->dev,
				  माप(काष्ठा MR_SNAPDUMP_PROPERTIES),
				  instance->snapdump_prop,
				  instance->snapdump_prop_h);

	अगर (instance->host_device_list_buf)
		dma_मुक्त_coherent(&pdev->dev,
				  HOST_DEVICE_LIST_SZ,
				  instance->host_device_list_buf,
				  instance->host_device_list_buf_h);

पूर्ण

/*
 * megasas_init_ctrl_params -		Initialize controller's instance
 *					parameters beक्रमe FW init
 * @instance -				Adapter soft instance
 * @वापस -				व्योम
 */
अटल अंतरभूत व्योम megasas_init_ctrl_params(काष्ठा megasas_instance *instance)
अणु
	instance->fw_crash_state = UNAVAILABLE;

	megasas_poll_रुको_aen = 0;
	instance->issuepend_करोne = 1;
	atomic_set(&instance->adprecovery, MEGASAS_HBA_OPERATIONAL);

	/*
	 * Initialize locks and queues
	 */
	INIT_LIST_HEAD(&instance->cmd_pool);
	INIT_LIST_HEAD(&instance->पूर्णांकernal_reset_pending_q);

	atomic_set(&instance->fw_outstanding, 0);
	atomic64_set(&instance->total_io_count, 0);

	init_रुकोqueue_head(&instance->पूर्णांक_cmd_रुको_q);
	init_रुकोqueue_head(&instance->पात_cmd_रुको_q);

	spin_lock_init(&instance->crashdump_lock);
	spin_lock_init(&instance->mfi_pool_lock);
	spin_lock_init(&instance->hba_lock);
	spin_lock_init(&instance->stream_lock);
	spin_lock_init(&instance->completion_lock);

	mutex_init(&instance->reset_mutex);

	अगर ((instance->pdev->device == PCI_DEVICE_ID_LSI_SAS0073SKINNY) ||
	    (instance->pdev->device == PCI_DEVICE_ID_LSI_SAS0071SKINNY))
		instance->flag_ieee = 1;

	megasas_dbg_lvl = 0;
	instance->flag = 0;
	instance->unload = 1;
	instance->last_समय = 0;
	instance->disableOnlineCtrlReset = 1;
	instance->UnevenSpanSupport = 0;
	instance->smp_affinity_enable = smp_affinity_enable ? true : false;
	instance->msix_load_balance = false;

	अगर (instance->adapter_type != MFI_SERIES)
		INIT_WORK(&instance->work_init, megasas_fusion_ocr_wq);
	अन्यथा
		INIT_WORK(&instance->work_init, process_fw_state_change_wq);
पूर्ण

/**
 * megasas_probe_one -	PCI hotplug entry poपूर्णांक
 * @pdev:		PCI device काष्ठाure
 * @id:			PCI ids of supported hotplugged adapter
 */
अटल पूर्णांक megasas_probe_one(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक rval, pos;
	काष्ठा Scsi_Host *host;
	काष्ठा megasas_instance *instance;
	u16 control = 0;

	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_LSI_AERO_10E0:
	हाल PCI_DEVICE_ID_LSI_AERO_10E3:
	हाल PCI_DEVICE_ID_LSI_AERO_10E4:
	हाल PCI_DEVICE_ID_LSI_AERO_10E7:
		dev_err(&pdev->dev, "Adapter is in non secure mode\n");
		वापस 1;
	हाल PCI_DEVICE_ID_LSI_AERO_10E1:
	हाल PCI_DEVICE_ID_LSI_AERO_10E5:
		dev_info(&pdev->dev, "Adapter is in configurable secure mode\n");
		अवरोध;
	पूर्ण

	/* Reset MSI-X in the kdump kernel */
	अगर (reset_devices) अणु
		pos = pci_find_capability(pdev, PCI_CAP_ID_MSIX);
		अगर (pos) अणु
			pci_पढ़ो_config_word(pdev, pos + PCI_MSIX_FLAGS,
					     &control);
			अगर (control & PCI_MSIX_FLAGS_ENABLE) अणु
				dev_info(&pdev->dev, "resetting MSI-X\n");
				pci_ग_लिखो_config_word(pdev,
						      pos + PCI_MSIX_FLAGS,
						      control &
						      ~PCI_MSIX_FLAGS_ENABLE);
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * PCI prepping: enable device set bus mastering and dma mask
	 */
	rval = pci_enable_device_mem(pdev);

	अगर (rval) अणु
		वापस rval;
	पूर्ण

	pci_set_master(pdev);

	host = scsi_host_alloc(&megasas_ढाँचा,
			       माप(काष्ठा megasas_instance));

	अगर (!host) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &pdev->dev, "scsi_host_alloc failed\n");
		जाओ fail_alloc_instance;
	पूर्ण

	instance = (काष्ठा megasas_instance *)host->hostdata;
	स_रखो(instance, 0, माप(*instance));
	atomic_set(&instance->fw_reset_no_pci_access, 0);

	/*
	 * Initialize PCI related and misc parameters
	 */
	instance->pdev = pdev;
	instance->host = host;
	instance->unique_id = pdev->bus->number << 8 | pdev->devfn;
	instance->init_id = MEGASAS_DEFAULT_INIT_ID;

	megasas_set_adapter_type(instance);

	/*
	 * Initialize MFI Firmware
	 */
	अगर (megasas_init_fw(instance))
		जाओ fail_init_mfi;

	अगर (instance->requestorId) अणु
		अगर (instance->Plयंत्रaFW111) अणु
			instance->vf_affiliation_111 =
				dma_alloc_coherent(&pdev->dev,
					माप(काष्ठा MR_LD_VF_AFFILIATION_111),
					&instance->vf_affiliation_111_h,
					GFP_KERNEL);
			अगर (!instance->vf_affiliation_111)
				dev_warn(&pdev->dev, "Can't allocate "
				       "memory for VF affiliation buffer\n");
		पूर्ण अन्यथा अणु
			instance->vf_affiliation =
				dma_alloc_coherent(&pdev->dev,
					(MAX_LOGICAL_DRIVES + 1) *
					माप(काष्ठा MR_LD_VF_AFFILIATION),
					&instance->vf_affiliation_h,
					GFP_KERNEL);
			अगर (!instance->vf_affiliation)
				dev_warn(&pdev->dev, "Can't allocate "
				       "memory for VF affiliation buffer\n");
		पूर्ण
	पूर्ण

	/*
	 * Store instance in PCI softstate
	 */
	pci_set_drvdata(pdev, instance);

	/*
	 * Add this controller to megasas_mgmt_info काष्ठाure so that it
	 * can be exported to management applications
	 */
	megasas_mgmt_info.count++;
	megasas_mgmt_info.instance[megasas_mgmt_info.max_index] = instance;
	megasas_mgmt_info.max_index++;

	/*
	 * Register with SCSI mid-layer
	 */
	अगर (megasas_io_attach(instance))
		जाओ fail_io_attach;

	instance->unload = 0;
	/*
	 * Trigger SCSI to scan our drives
	 */
	अगर (!instance->enable_fw_dev_list ||
	    (instance->host_device_list_buf->count > 0))
		scsi_scan_host(host);

	/*
	 * Initiate AEN (Asynchronous Event Notअगरication)
	 */
	अगर (megasas_start_aen(instance)) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &pdev->dev, "start aen failed\n");
		जाओ fail_start_aen;
	पूर्ण

	megasas_setup_debugfs(instance);

	/* Get current SR-IOV LD/VF affiliation */
	अगर (instance->requestorId)
		megasas_get_ld_vf_affiliation(instance, 1);

	वापस 0;

fail_start_aen:
fail_io_attach:
	megasas_mgmt_info.count--;
	megasas_mgmt_info.max_index--;
	megasas_mgmt_info.instance[megasas_mgmt_info.max_index] = शून्य;

	instance->instancet->disable_पूर्णांकr(instance);
	megasas_destroy_irqs(instance);

	अगर (instance->adapter_type != MFI_SERIES)
		megasas_release_fusion(instance);
	अन्यथा
		megasas_release_mfi(instance);
	अगर (instance->msix_vectors)
		pci_मुक्त_irq_vectors(instance->pdev);
fail_init_mfi:
	scsi_host_put(host);
fail_alloc_instance:
	pci_disable_device(pdev);

	वापस -ENODEV;
पूर्ण

/**
 * megasas_flush_cache -	Requests FW to flush all its caches
 * @instance:			Adapter soft state
 */
अटल व्योम megasas_flush_cache(काष्ठा megasas_instance *instance)
अणु
	काष्ठा megasas_cmd *cmd;
	काष्ठा megasas_dcmd_frame *dcmd;

	अगर (atomic_पढ़ो(&instance->adprecovery) == MEGASAS_HW_CRITICAL_ERROR)
		वापस;

	cmd = megasas_get_cmd(instance);

	अगर (!cmd)
		वापस;

	dcmd = &cmd->frame->dcmd;

	स_रखो(dcmd->mbox.b, 0, MFI_MBOX_SIZE);

	dcmd->cmd = MFI_CMD_DCMD;
	dcmd->cmd_status = 0x0;
	dcmd->sge_count = 0;
	dcmd->flags = cpu_to_le16(MFI_FRAME_सूची_NONE);
	dcmd->समयout = 0;
	dcmd->pad_0 = 0;
	dcmd->data_xfer_len = 0;
	dcmd->opcode = cpu_to_le32(MR_DCMD_CTRL_CACHE_FLUSH);
	dcmd->mbox.b[0] = MR_FLUSH_CTRL_CACHE | MR_FLUSH_DISK_CACHE;

	अगर (megasas_issue_blocked_cmd(instance, cmd, MFI_IO_TIMEOUT_SECS)
			!= DCMD_SUCCESS) अणु
		dev_err(&instance->pdev->dev,
			"return from %s %d\n", __func__, __LINE__);
		वापस;
	पूर्ण

	megasas_वापस_cmd(instance, cmd);
पूर्ण

/**
 * megasas_shutकरोwn_controller -	Inकाष्ठाs FW to shutकरोwn the controller
 * @instance:				Adapter soft state
 * @opcode:				Shutकरोwn/Hibernate
 */
अटल व्योम megasas_shutकरोwn_controller(काष्ठा megasas_instance *instance,
					u32 opcode)
अणु
	काष्ठा megasas_cmd *cmd;
	काष्ठा megasas_dcmd_frame *dcmd;

	अगर (atomic_पढ़ो(&instance->adprecovery) == MEGASAS_HW_CRITICAL_ERROR)
		वापस;

	cmd = megasas_get_cmd(instance);

	अगर (!cmd)
		वापस;

	अगर (instance->aen_cmd)
		megasas_issue_blocked_पात_cmd(instance,
			instance->aen_cmd, MFI_IO_TIMEOUT_SECS);
	अगर (instance->map_update_cmd)
		megasas_issue_blocked_पात_cmd(instance,
			instance->map_update_cmd, MFI_IO_TIMEOUT_SECS);
	अगर (instance->jbod_seq_cmd)
		megasas_issue_blocked_पात_cmd(instance,
			instance->jbod_seq_cmd, MFI_IO_TIMEOUT_SECS);

	dcmd = &cmd->frame->dcmd;

	स_रखो(dcmd->mbox.b, 0, MFI_MBOX_SIZE);

	dcmd->cmd = MFI_CMD_DCMD;
	dcmd->cmd_status = 0x0;
	dcmd->sge_count = 0;
	dcmd->flags = cpu_to_le16(MFI_FRAME_सूची_NONE);
	dcmd->समयout = 0;
	dcmd->pad_0 = 0;
	dcmd->data_xfer_len = 0;
	dcmd->opcode = cpu_to_le32(opcode);

	अगर (megasas_issue_blocked_cmd(instance, cmd, MFI_IO_TIMEOUT_SECS)
			!= DCMD_SUCCESS) अणु
		dev_err(&instance->pdev->dev,
			"return from %s %d\n", __func__, __LINE__);
		वापस;
	पूर्ण

	megasas_वापस_cmd(instance, cmd);
पूर्ण

/**
 * megasas_suspend -	driver suspend entry poपूर्णांक
 * @dev:		Device काष्ठाure
 */
अटल पूर्णांक __maybe_unused
megasas_suspend(काष्ठा device *dev)
अणु
	काष्ठा megasas_instance *instance;

	instance = dev_get_drvdata(dev);

	अगर (!instance)
		वापस 0;

	instance->unload = 1;

	dev_info(dev, "%s is called\n", __func__);

	/* Shutकरोwn SR-IOV heartbeat समयr */
	अगर (instance->requestorId && !instance->skip_heartbeat_समयr_del)
		del_समयr_sync(&instance->sriov_heartbeat_समयr);

	/* Stop the FW fault detection watchकरोg */
	अगर (instance->adapter_type != MFI_SERIES)
		megasas_fusion_stop_watchकरोg(instance);

	megasas_flush_cache(instance);
	megasas_shutकरोwn_controller(instance, MR_DCMD_HIBERNATE_SHUTDOWN);

	/* cancel the delayed work अगर this work still in queue */
	अगर (instance->ev != शून्य) अणु
		काष्ठा megasas_aen_event *ev = instance->ev;
		cancel_delayed_work_sync(&ev->hotplug_work);
		instance->ev = शून्य;
	पूर्ण

	tasklet_समाप्त(&instance->isr_tasklet);

	pci_set_drvdata(instance->pdev, instance);
	instance->instancet->disable_पूर्णांकr(instance);

	megasas_destroy_irqs(instance);

	अगर (instance->msix_vectors)
		pci_मुक्त_irq_vectors(instance->pdev);

	वापस 0;
पूर्ण

/**
 * megasas_resume-      driver resume entry poपूर्णांक
 * @dev:		Device काष्ठाure
 */
अटल पूर्णांक __maybe_unused
megasas_resume(काष्ठा device *dev)
अणु
	पूर्णांक rval;
	काष्ठा Scsi_Host *host;
	काष्ठा megasas_instance *instance;
	u32 status_reg;

	instance = dev_get_drvdata(dev);

	अगर (!instance)
		वापस 0;

	host = instance->host;

	dev_info(dev, "%s is called\n", __func__);

	/*
	 * We expect the FW state to be READY
	 */

	अगर (megasas_transition_to_पढ़ोy(instance, 0)) अणु
		dev_info(&instance->pdev->dev,
			 "Failed to transition controller to ready from %s!\n",
			 __func__);
		अगर (instance->adapter_type != MFI_SERIES) अणु
			status_reg =
				instance->instancet->पढ़ो_fw_status_reg(instance);
			अगर (!(status_reg & MFI_RESET_ADAPTER) ||
				((megasas_adp_reset_रुको_क्रम_पढ़ोy
				(instance, true, 0)) == FAILED))
				जाओ fail_पढ़ोy_state;
		पूर्ण अन्यथा अणु
			atomic_set(&instance->fw_reset_no_pci_access, 1);
			instance->instancet->adp_reset
				(instance, instance->reg_set);
			atomic_set(&instance->fw_reset_no_pci_access, 0);

			/* रुकोing क्रम about 30 seconds beक्रमe retry */
			ssleep(30);

			अगर (megasas_transition_to_पढ़ोy(instance, 0))
				जाओ fail_पढ़ोy_state;
		पूर्ण

		dev_info(&instance->pdev->dev,
			 "FW restarted successfully from %s!\n",
			 __func__);
	पूर्ण
	अगर (megasas_set_dma_mask(instance))
		जाओ fail_set_dma_mask;

	/*
	 * Initialize MFI Firmware
	 */

	atomic_set(&instance->fw_outstanding, 0);
	atomic_set(&instance->ldio_outstanding, 0);

	/* Now re-enable MSI-X */
	अगर (instance->msix_vectors)
		megasas_alloc_irq_vectors(instance);

	अगर (!instance->msix_vectors) अणु
		rval = pci_alloc_irq_vectors(instance->pdev, 1, 1,
					     PCI_IRQ_LEGACY);
		अगर (rval < 0)
			जाओ fail_reenable_msix;
	पूर्ण

	megasas_setup_reply_map(instance);

	अगर (instance->adapter_type != MFI_SERIES) अणु
		megasas_reset_reply_desc(instance);
		अगर (megasas_ioc_init_fusion(instance)) अणु
			megasas_मुक्त_cmds(instance);
			megasas_मुक्त_cmds_fusion(instance);
			जाओ fail_init_mfi;
		पूर्ण
		अगर (!megasas_get_map_info(instance))
			megasas_sync_map_info(instance);
	पूर्ण अन्यथा अणु
		*instance->producer = 0;
		*instance->consumer = 0;
		अगर (megasas_issue_init_mfi(instance))
			जाओ fail_init_mfi;
	पूर्ण

	अगर (megasas_get_ctrl_info(instance) != DCMD_SUCCESS)
		जाओ fail_init_mfi;

	tasklet_init(&instance->isr_tasklet, instance->instancet->tasklet,
		     (अचिन्हित दीर्घ)instance);

	अगर (instance->msix_vectors ?
			megasas_setup_irqs_msix(instance, 0) :
			megasas_setup_irqs_ioapic(instance))
		जाओ fail_init_mfi;

	अगर (instance->adapter_type != MFI_SERIES)
		megasas_setup_irq_poll(instance);

	/* Re-launch SR-IOV heartbeat समयr */
	अगर (instance->requestorId) अणु
		अगर (!megasas_sriov_start_heartbeat(instance, 0))
			megasas_start_समयr(instance);
		अन्यथा अणु
			instance->skip_heartbeat_समयr_del = 1;
			जाओ fail_init_mfi;
		पूर्ण
	पूर्ण

	instance->instancet->enable_पूर्णांकr(instance);
	megasas_setup_jbod_map(instance);
	instance->unload = 0;

	/*
	 * Initiate AEN (Asynchronous Event Notअगरication)
	 */
	अगर (megasas_start_aen(instance))
		dev_err(&instance->pdev->dev, "Start AEN failed\n");

	/* Re-launch FW fault watchकरोg */
	अगर (instance->adapter_type != MFI_SERIES)
		अगर (megasas_fusion_start_watchकरोg(instance) != SUCCESS)
			जाओ fail_start_watchकरोg;

	वापस 0;

fail_start_watchकरोg:
	अगर (instance->requestorId && !instance->skip_heartbeat_समयr_del)
		del_समयr_sync(&instance->sriov_heartbeat_समयr);
fail_init_mfi:
	megasas_मुक्त_ctrl_dma_buffers(instance);
	megasas_मुक्त_ctrl_mem(instance);
	scsi_host_put(host);

fail_reenable_msix:
fail_set_dma_mask:
fail_पढ़ोy_state:

	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक
megasas_रुको_क्रम_adapter_operational(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक रुको_समय = MEGASAS_RESET_WAIT_TIME * 2;
	पूर्णांक i;
	u8 adp_state;

	क्रम (i = 0; i < रुको_समय; i++) अणु
		adp_state = atomic_पढ़ो(&instance->adprecovery);
		अगर ((adp_state == MEGASAS_HBA_OPERATIONAL) ||
		    (adp_state == MEGASAS_HW_CRITICAL_ERROR))
			अवरोध;

		अगर (!(i % MEGASAS_RESET_NOTICE_INTERVAL))
			dev_notice(&instance->pdev->dev, "waiting for controller reset to finish\n");

		msleep(1000);
	पूर्ण

	अगर (adp_state != MEGASAS_HBA_OPERATIONAL) अणु
		dev_info(&instance->pdev->dev,
			 "%s HBA failed to become operational, adp_state %d\n",
			 __func__, adp_state);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * megasas_detach_one -	PCI hot"un"plug entry poपूर्णांक
 * @pdev:		PCI device काष्ठाure
 */
अटल व्योम megasas_detach_one(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;
	काष्ठा Scsi_Host *host;
	काष्ठा megasas_instance *instance;
	काष्ठा fusion_context *fusion;
	u32 pd_seq_map_sz;

	instance = pci_get_drvdata(pdev);

	अगर (!instance)
		वापस;

	host = instance->host;
	fusion = instance->ctrl_context;

	/* Shutकरोwn SR-IOV heartbeat समयr */
	अगर (instance->requestorId && !instance->skip_heartbeat_समयr_del)
		del_समयr_sync(&instance->sriov_heartbeat_समयr);

	/* Stop the FW fault detection watchकरोg */
	अगर (instance->adapter_type != MFI_SERIES)
		megasas_fusion_stop_watchकरोg(instance);

	अगर (instance->fw_crash_state != UNAVAILABLE)
		megasas_मुक्त_host_crash_buffer(instance);
	scsi_हटाओ_host(instance->host);
	instance->unload = 1;

	अगर (megasas_रुको_क्रम_adapter_operational(instance))
		जाओ skip_firing_dcmds;

	megasas_flush_cache(instance);
	megasas_shutकरोwn_controller(instance, MR_DCMD_CTRL_SHUTDOWN);

skip_firing_dcmds:
	/* cancel the delayed work अगर this work still in queue*/
	अगर (instance->ev != शून्य) अणु
		काष्ठा megasas_aen_event *ev = instance->ev;
		cancel_delayed_work_sync(&ev->hotplug_work);
		instance->ev = शून्य;
	पूर्ण

	/* cancel all रुको events */
	wake_up_all(&instance->पूर्णांक_cmd_रुको_q);

	tasklet_समाप्त(&instance->isr_tasklet);

	/*
	 * Take the instance off the instance array. Note that we will not
	 * decrement the max_index. We let this array be sparse array
	 */
	क्रम (i = 0; i < megasas_mgmt_info.max_index; i++) अणु
		अगर (megasas_mgmt_info.instance[i] == instance) अणु
			megasas_mgmt_info.count--;
			megasas_mgmt_info.instance[i] = शून्य;

			अवरोध;
		पूर्ण
	पूर्ण

	instance->instancet->disable_पूर्णांकr(instance);

	megasas_destroy_irqs(instance);

	अगर (instance->msix_vectors)
		pci_मुक्त_irq_vectors(instance->pdev);

	अगर (instance->adapter_type >= VENTURA_SERIES) अणु
		क्रम (i = 0; i < MAX_LOGICAL_DRIVES_EXT; ++i)
			kमुक्त(fusion->stream_detect_by_ld[i]);
		kमुक्त(fusion->stream_detect_by_ld);
		fusion->stream_detect_by_ld = शून्य;
	पूर्ण


	अगर (instance->adapter_type != MFI_SERIES) अणु
		megasas_release_fusion(instance);
			pd_seq_map_sz = माप(काष्ठा MR_PD_CFG_SEQ_NUM_SYNC) +
				(माप(काष्ठा MR_PD_CFG_SEQ) *
					(MAX_PHYSICAL_DEVICES - 1));
		क्रम (i = 0; i < 2 ; i++) अणु
			अगर (fusion->ld_map[i])
				dma_मुक्त_coherent(&instance->pdev->dev,
						  fusion->max_map_sz,
						  fusion->ld_map[i],
						  fusion->ld_map_phys[i]);
			अगर (fusion->ld_drv_map[i]) अणु
				अगर (is_vदो_स्मृति_addr(fusion->ld_drv_map[i]))
					vमुक्त(fusion->ld_drv_map[i]);
				अन्यथा
					मुक्त_pages((uदीर्घ)fusion->ld_drv_map[i],
						   fusion->drv_map_pages);
			पूर्ण

			अगर (fusion->pd_seq_sync[i])
				dma_मुक्त_coherent(&instance->pdev->dev,
					pd_seq_map_sz,
					fusion->pd_seq_sync[i],
					fusion->pd_seq_phys[i]);
		पूर्ण
	पूर्ण अन्यथा अणु
		megasas_release_mfi(instance);
	पूर्ण

	अगर (instance->vf_affiliation)
		dma_मुक्त_coherent(&pdev->dev, (MAX_LOGICAL_DRIVES + 1) *
				    माप(काष्ठा MR_LD_VF_AFFILIATION),
				    instance->vf_affiliation,
				    instance->vf_affiliation_h);

	अगर (instance->vf_affiliation_111)
		dma_मुक्त_coherent(&pdev->dev,
				    माप(काष्ठा MR_LD_VF_AFFILIATION_111),
				    instance->vf_affiliation_111,
				    instance->vf_affiliation_111_h);

	अगर (instance->hb_host_mem)
		dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा MR_CTRL_HB_HOST_MEM),
				    instance->hb_host_mem,
				    instance->hb_host_mem_h);

	megasas_मुक्त_ctrl_dma_buffers(instance);

	megasas_मुक्त_ctrl_mem(instance);

	megasas_destroy_debugfs(instance);

	scsi_host_put(host);

	pci_disable_device(pdev);
पूर्ण

/**
 * megasas_shutकरोwn -	Shutकरोwn entry poपूर्णांक
 * @pdev:		PCI device काष्ठाure
 */
अटल व्योम megasas_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा megasas_instance *instance = pci_get_drvdata(pdev);

	अगर (!instance)
		वापस;

	instance->unload = 1;

	अगर (megasas_रुको_क्रम_adapter_operational(instance))
		जाओ skip_firing_dcmds;

	megasas_flush_cache(instance);
	megasas_shutकरोwn_controller(instance, MR_DCMD_CTRL_SHUTDOWN);

skip_firing_dcmds:
	instance->instancet->disable_पूर्णांकr(instance);
	megasas_destroy_irqs(instance);

	अगर (instance->msix_vectors)
		pci_मुक्त_irq_vectors(instance->pdev);
पूर्ण

/*
 * megasas_mgmt_खोलो -	अक्षर node "open" entry poपूर्णांक
 * @inode:	अक्षर node inode
 * @filep:	अक्षर node file
 */
अटल पूर्णांक megasas_mgmt_खोलो(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	/*
	 * Allow only those users with admin rights
	 */
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	वापस 0;
पूर्ण

/*
 * megasas_mgmt_fasync -	Async notअगरier registration from applications
 * @fd:		अक्षर node file descriptor number
 * @filep:	अक्षर node file
 * @mode:	notअगरier on/off
 *
 * This function adds the calling process to a driver global queue. When an
 * event occurs, SIGIO will be sent to all processes in this queue.
 */
अटल पूर्णांक megasas_mgmt_fasync(पूर्णांक fd, काष्ठा file *filep, पूर्णांक mode)
अणु
	पूर्णांक rc;

	mutex_lock(&megasas_async_queue_mutex);

	rc = fasync_helper(fd, filep, mode, &megasas_async_queue);

	mutex_unlock(&megasas_async_queue_mutex);

	अगर (rc >= 0) अणु
		/* For sanity check when we get ioctl */
		filep->निजी_data = filep;
		वापस 0;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "megasas: fasync_helper failed [%d]\n", rc);

	वापस rc;
पूर्ण

/*
 * megasas_mgmt_poll -  अक्षर node "poll" entry poपूर्णांक
 * @filep:	अक्षर node file
 * @रुको:	Events to poll क्रम
 */
अटल __poll_t megasas_mgmt_poll(काष्ठा file *file, poll_table *रुको)
अणु
	__poll_t mask;
	अचिन्हित दीर्घ flags;

	poll_रुको(file, &megasas_poll_रुको, रुको);
	spin_lock_irqsave(&poll_aen_lock, flags);
	अगर (megasas_poll_रुको_aen)
		mask = (EPOLLIN | EPOLLRDNORM);
	अन्यथा
		mask = 0;
	megasas_poll_रुको_aen = 0;
	spin_unlock_irqrestore(&poll_aen_lock, flags);
	वापस mask;
पूर्ण

/*
 * megasas_set_crash_dump_params_ioctl:
 *		Send CRASH_DUMP_MODE DCMD to all controllers
 * @cmd:	MFI command frame
 */

अटल पूर्णांक megasas_set_crash_dump_params_ioctl(काष्ठा megasas_cmd *cmd)
अणु
	काष्ठा megasas_instance *local_instance;
	पूर्णांक i, error = 0;
	पूर्णांक crash_support;

	crash_support = cmd->frame->dcmd.mbox.w[0];

	क्रम (i = 0; i < megasas_mgmt_info.max_index; i++) अणु
		local_instance = megasas_mgmt_info.instance[i];
		अगर (local_instance && local_instance->crash_dump_drv_support) अणु
			अगर ((atomic_पढ़ो(&local_instance->adprecovery) ==
				MEGASAS_HBA_OPERATIONAL) &&
				!megasas_set_crash_dump_params(local_instance,
					crash_support)) अणु
				local_instance->crash_dump_app_support =
					crash_support;
				dev_info(&local_instance->pdev->dev,
					"Application firmware crash "
					"dump mode set success\n");
				error = 0;
			पूर्ण अन्यथा अणु
				dev_info(&local_instance->pdev->dev,
					"Application firmware crash "
					"dump mode set failed\n");
				error = -1;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस error;
पूर्ण

/**
 * megasas_mgmt_fw_ioctl -	Issues management ioctls to FW
 * @instance:			Adapter soft state
 * @user_ioc:			User's ioctl packet
 * @ioc:			ioctl packet
 */
अटल पूर्णांक
megasas_mgmt_fw_ioctl(काष्ठा megasas_instance *instance,
		      काष्ठा megasas_iocpacket __user * user_ioc,
		      काष्ठा megasas_iocpacket *ioc)
अणु
	काष्ठा megasas_sge64 *kern_sge64 = शून्य;
	काष्ठा megasas_sge32 *kern_sge32 = शून्य;
	काष्ठा megasas_cmd *cmd;
	व्योम *kbuff_arr[MAX_IOCTL_SGE];
	dma_addr_t buf_handle = 0;
	पूर्णांक error = 0, i;
	व्योम *sense = शून्य;
	dma_addr_t sense_handle;
	व्योम *sense_ptr;
	u32 opcode = 0;
	पूर्णांक ret = DCMD_SUCCESS;

	स_रखो(kbuff_arr, 0, माप(kbuff_arr));

	अगर (ioc->sge_count > MAX_IOCTL_SGE) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "SGE count [%d] >  max limit [%d]\n",
		       ioc->sge_count, MAX_IOCTL_SGE);
		वापस -EINVAL;
	पूर्ण

	अगर ((ioc->frame.hdr.cmd >= MFI_CMD_OP_COUNT) ||
	    ((ioc->frame.hdr.cmd == MFI_CMD_NVME) &&
	    !instance->support_nvme_passthru) ||
	    ((ioc->frame.hdr.cmd == MFI_CMD_TOOLBOX) &&
	    !instance->support_pci_lane_margining)) अणु
		dev_err(&instance->pdev->dev,
			"Received invalid ioctl command 0x%x\n",
			ioc->frame.hdr.cmd);
		वापस -ENOTSUPP;
	पूर्ण

	cmd = megasas_get_cmd(instance);
	अगर (!cmd) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "Failed to get a cmd packet\n");
		वापस -ENOMEM;
	पूर्ण

	/*
	 * User's IOCTL packet has 2 frames (maximum). Copy those two
	 * frames पूर्णांकo our cmd's frames. cmd->frame's context will get
	 * overwritten when we copy from user's frames. So set that value
	 * alone separately
	 */
	स_नकल(cmd->frame, ioc->frame.raw, 2 * MEGAMFI_FRAME_SIZE);
	cmd->frame->hdr.context = cpu_to_le32(cmd->index);
	cmd->frame->hdr.pad_0 = 0;

	cmd->frame->hdr.flags &= (~MFI_FRAME_IEEE);

	अगर (instance->consistent_mask_64bit)
		cmd->frame->hdr.flags |= cpu_to_le16((MFI_FRAME_SGL64 |
				       MFI_FRAME_SENSE64));
	अन्यथा
		cmd->frame->hdr.flags &= cpu_to_le16(~(MFI_FRAME_SGL64 |
					       MFI_FRAME_SENSE64));

	अगर (cmd->frame->hdr.cmd == MFI_CMD_DCMD)
		opcode = le32_to_cpu(cmd->frame->dcmd.opcode);

	अगर (opcode == MR_DCMD_CTRL_SHUTDOWN) अणु
		mutex_lock(&instance->reset_mutex);
		अगर (megasas_get_ctrl_info(instance) != DCMD_SUCCESS) अणु
			megasas_वापस_cmd(instance, cmd);
			mutex_unlock(&instance->reset_mutex);
			वापस -1;
		पूर्ण
		mutex_unlock(&instance->reset_mutex);
	पूर्ण

	अगर (opcode == MR_DRIVER_SET_APP_CRASHDUMP_MODE) अणु
		error = megasas_set_crash_dump_params_ioctl(cmd);
		megasas_वापस_cmd(instance, cmd);
		वापस error;
	पूर्ण

	/*
	 * The management पूर्णांकerface between applications and the fw uses
	 * MFI frames. E.g, RAID configuration changes, LD property changes
	 * etc are accomplishes through dअगरferent kinds of MFI frames. The
	 * driver needs to care only about substituting user buffers with
	 * kernel buffers in SGLs. The location of SGL is embedded in the
	 * काष्ठा iocpacket itself.
	 */
	अगर (instance->consistent_mask_64bit)
		kern_sge64 = (काष्ठा megasas_sge64 *)
			((अचिन्हित दीर्घ)cmd->frame + ioc->sgl_off);
	अन्यथा
		kern_sge32 = (काष्ठा megasas_sge32 *)
			((अचिन्हित दीर्घ)cmd->frame + ioc->sgl_off);

	/*
	 * For each user buffer, create a mirror buffer and copy in
	 */
	क्रम (i = 0; i < ioc->sge_count; i++) अणु
		अगर (!ioc->sgl[i].iov_len)
			जारी;

		kbuff_arr[i] = dma_alloc_coherent(&instance->pdev->dev,
						    ioc->sgl[i].iov_len,
						    &buf_handle, GFP_KERNEL);
		अगर (!kbuff_arr[i]) अणु
			dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "Failed to alloc "
			       "kernel SGL buffer for IOCTL\n");
			error = -ENOMEM;
			जाओ out;
		पूर्ण

		/*
		 * We करोn't change the dma_coherent_mask, so
		 * dma_alloc_coherent only वापसs 32bit addresses
		 */
		अगर (instance->consistent_mask_64bit) अणु
			kern_sge64[i].phys_addr = cpu_to_le64(buf_handle);
			kern_sge64[i].length = cpu_to_le32(ioc->sgl[i].iov_len);
		पूर्ण अन्यथा अणु
			kern_sge32[i].phys_addr = cpu_to_le32(buf_handle);
			kern_sge32[i].length = cpu_to_le32(ioc->sgl[i].iov_len);
		पूर्ण

		/*
		 * We created a kernel buffer corresponding to the
		 * user buffer. Now copy in from the user buffer
		 */
		अगर (copy_from_user(kbuff_arr[i], ioc->sgl[i].iov_base,
				   (u32) (ioc->sgl[i].iov_len))) अणु
			error = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (ioc->sense_len) अणु
		/* make sure the poपूर्णांकer is part of the frame */
		अगर (ioc->sense_off >
		    (माप(जोड़ megasas_frame) - माप(__le64))) अणु
			error = -EINVAL;
			जाओ out;
		पूर्ण

		sense = dma_alloc_coherent(&instance->pdev->dev, ioc->sense_len,
					     &sense_handle, GFP_KERNEL);
		अगर (!sense) अणु
			error = -ENOMEM;
			जाओ out;
		पूर्ण

		/* always store 64 bits regardless of addressing */
		sense_ptr = (व्योम *)cmd->frame + ioc->sense_off;
		put_unaligned_le64(sense_handle, sense_ptr);
	पूर्ण

	/*
	 * Set the sync_cmd flag so that the ISR knows not to complete this
	 * cmd to the SCSI mid-layer
	 */
	cmd->sync_cmd = 1;

	ret = megasas_issue_blocked_cmd(instance, cmd, 0);
	चयन (ret) अणु
	हाल DCMD_INIT:
	हाल DCMD_BUSY:
		cmd->sync_cmd = 0;
		dev_err(&instance->pdev->dev,
			"return -EBUSY from %s %d cmd 0x%x opcode 0x%x cmd->cmd_status_drv 0x%x\n",
			 __func__, __LINE__, cmd->frame->hdr.cmd, opcode,
			 cmd->cmd_status_drv);
		error = -EBUSY;
		जाओ out;
	पूर्ण

	cmd->sync_cmd = 0;

	अगर (instance->unload == 1) अणु
		dev_info(&instance->pdev->dev, "Driver unload is in progress "
			"don't submit data to application\n");
		जाओ out;
	पूर्ण
	/*
	 * copy out the kernel buffers to user buffers
	 */
	क्रम (i = 0; i < ioc->sge_count; i++) अणु
		अगर (copy_to_user(ioc->sgl[i].iov_base, kbuff_arr[i],
				 ioc->sgl[i].iov_len)) अणु
			error = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * copy out the sense
	 */
	अगर (ioc->sense_len) अणु
		व्योम __user *uptr;
		/*
		 * sense_ptr poपूर्णांकs to the location that has the user
		 * sense buffer address
		 */
		sense_ptr = (व्योम *)ioc->frame.raw + ioc->sense_off;
		अगर (in_compat_syscall())
			uptr = compat_ptr(get_unaligned((compat_uptr_t *)
							sense_ptr));
		अन्यथा
			uptr = get_unaligned((व्योम __user **)sense_ptr);

		अगर (copy_to_user(uptr, sense, ioc->sense_len)) अणु
			dev_err(&instance->pdev->dev, "Failed to copy out to user "
					"sense data\n");
			error = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * copy the status codes वापसed by the fw
	 */
	अगर (copy_to_user(&user_ioc->frame.hdr.cmd_status,
			 &cmd->frame->hdr.cmd_status, माप(u8))) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "Error copying out cmd_status\n");
		error = -EFAULT;
	पूर्ण

out:
	अगर (sense) अणु
		dma_मुक्त_coherent(&instance->pdev->dev, ioc->sense_len,
				    sense, sense_handle);
	पूर्ण

	क्रम (i = 0; i < ioc->sge_count; i++) अणु
		अगर (kbuff_arr[i]) अणु
			अगर (instance->consistent_mask_64bit)
				dma_मुक्त_coherent(&instance->pdev->dev,
					le32_to_cpu(kern_sge64[i].length),
					kbuff_arr[i],
					le64_to_cpu(kern_sge64[i].phys_addr));
			अन्यथा
				dma_मुक्त_coherent(&instance->pdev->dev,
					le32_to_cpu(kern_sge32[i].length),
					kbuff_arr[i],
					le32_to_cpu(kern_sge32[i].phys_addr));
			kbuff_arr[i] = शून्य;
		पूर्ण
	पूर्ण

	megasas_वापस_cmd(instance, cmd);
	वापस error;
पूर्ण

अटल काष्ठा megasas_iocpacket *
megasas_compat_iocpacket_get_user(व्योम __user *arg)
अणु
	काष्ठा megasas_iocpacket *ioc;
	काष्ठा compat_megasas_iocpacket __user *cioc = arg;
	माप_प्रकार size;
	पूर्णांक err = -EFAULT;
	पूर्णांक i;

	ioc = kzalloc(माप(*ioc), GFP_KERNEL);
	अगर (!ioc)
		वापस ERR_PTR(-ENOMEM);
	size = दुरत्व(काष्ठा megasas_iocpacket, frame) + माप(ioc->frame);
	अगर (copy_from_user(ioc, arg, size))
		जाओ out;

	क्रम (i = 0; i < MAX_IOCTL_SGE; i++) अणु
		compat_uptr_t iov_base;

		अगर (get_user(iov_base, &cioc->sgl[i].iov_base) ||
		    get_user(ioc->sgl[i].iov_len, &cioc->sgl[i].iov_len))
			जाओ out;

		ioc->sgl[i].iov_base = compat_ptr(iov_base);
	पूर्ण

	वापस ioc;
out:
	kमुक्त(ioc);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक megasas_mgmt_ioctl_fw(काष्ठा file *file, अचिन्हित दीर्घ arg)
अणु
	काष्ठा megasas_iocpacket __user *user_ioc =
	    (काष्ठा megasas_iocpacket __user *)arg;
	काष्ठा megasas_iocpacket *ioc;
	काष्ठा megasas_instance *instance;
	पूर्णांक error;

	अगर (in_compat_syscall())
		ioc = megasas_compat_iocpacket_get_user(user_ioc);
	अन्यथा
		ioc = memdup_user(user_ioc, माप(काष्ठा megasas_iocpacket));

	अगर (IS_ERR(ioc))
		वापस PTR_ERR(ioc);

	instance = megasas_lookup_instance(ioc->host_no);
	अगर (!instance) अणु
		error = -ENODEV;
		जाओ out_kमुक्त_ioc;
	पूर्ण

	/* Block ioctls in VF mode */
	अगर (instance->requestorId && !allow_vf_ioctls) अणु
		error = -ENODEV;
		जाओ out_kमुक्त_ioc;
	पूर्ण

	अगर (atomic_पढ़ो(&instance->adprecovery) == MEGASAS_HW_CRITICAL_ERROR) अणु
		dev_err(&instance->pdev->dev, "Controller in crit error\n");
		error = -ENODEV;
		जाओ out_kमुक्त_ioc;
	पूर्ण

	अगर (instance->unload == 1) अणु
		error = -ENODEV;
		जाओ out_kमुक्त_ioc;
	पूर्ण

	अगर (करोwn_पूर्णांकerruptible(&instance->ioctl_sem)) अणु
		error = -ERESTARTSYS;
		जाओ out_kमुक्त_ioc;
	पूर्ण

	अगर  (megasas_रुको_क्रम_adapter_operational(instance)) अणु
		error = -ENODEV;
		जाओ out_up;
	पूर्ण

	error = megasas_mgmt_fw_ioctl(instance, user_ioc, ioc);
out_up:
	up(&instance->ioctl_sem);

out_kमुक्त_ioc:
	kमुक्त(ioc);
	वापस error;
पूर्ण

अटल पूर्णांक megasas_mgmt_ioctl_aen(काष्ठा file *file, अचिन्हित दीर्घ arg)
अणु
	काष्ठा megasas_instance *instance;
	काष्ठा megasas_aen aen;
	पूर्णांक error;

	अगर (file->निजी_data != file) अणु
		prपूर्णांकk(KERN_DEBUG "megasas: fasync_helper was not "
		       "called first\n");
		वापस -EINVAL;
	पूर्ण

	अगर (copy_from_user(&aen, (व्योम __user *)arg, माप(aen)))
		वापस -EFAULT;

	instance = megasas_lookup_instance(aen.host_no);

	अगर (!instance)
		वापस -ENODEV;

	अगर (atomic_पढ़ो(&instance->adprecovery) == MEGASAS_HW_CRITICAL_ERROR) अणु
		वापस -ENODEV;
	पूर्ण

	अगर (instance->unload == 1) अणु
		वापस -ENODEV;
	पूर्ण

	अगर  (megasas_रुको_क्रम_adapter_operational(instance))
		वापस -ENODEV;

	mutex_lock(&instance->reset_mutex);
	error = megasas_रेजिस्टर_aen(instance, aen.seq_num,
				     aen.class_locale_word);
	mutex_unlock(&instance->reset_mutex);
	वापस error;
पूर्ण

/**
 * megasas_mgmt_ioctl -	अक्षर node ioctl entry poपूर्णांक
 * @file:	अक्षर device file poपूर्णांकer
 * @cmd:	ioctl command
 * @arg:	ioctl command arguments address
 */
अटल दीर्घ
megasas_mgmt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल MEGASAS_IOC_FIRMWARE:
		वापस megasas_mgmt_ioctl_fw(file, arg);

	हाल MEGASAS_IOC_GET_AEN:
		वापस megasas_mgmt_ioctl_aen(file, arg);
	पूर्ण

	वापस -ENOTTY;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ
megasas_mgmt_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			  अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल MEGASAS_IOC_FIRMWARE32:
		वापस megasas_mgmt_ioctl_fw(file, arg);
	हाल MEGASAS_IOC_GET_AEN:
		वापस megasas_mgmt_ioctl_aen(file, arg);
	पूर्ण

	वापस -ENOTTY;
पूर्ण
#पूर्ण_अगर

/*
 * File operations काष्ठाure क्रम management पूर्णांकerface
 */
अटल स्थिर काष्ठा file_operations megasas_mgmt_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = megasas_mgmt_खोलो,
	.fasync = megasas_mgmt_fasync,
	.unlocked_ioctl = megasas_mgmt_ioctl,
	.poll = megasas_mgmt_poll,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = megasas_mgmt_compat_ioctl,
#पूर्ण_अगर
	.llseek = noop_llseek,
पूर्ण;

अटल SIMPLE_DEV_PM_OPS(megasas_pm_ops, megasas_suspend, megasas_resume);

/*
 * PCI hotplug support registration काष्ठाure
 */
अटल काष्ठा pci_driver megasas_pci_driver = अणु

	.name = "megaraid_sas",
	.id_table = megasas_pci_table,
	.probe = megasas_probe_one,
	.हटाओ = megasas_detach_one,
	.driver.pm = &megasas_pm_ops,
	.shutकरोwn = megasas_shutकरोwn,
पूर्ण;

/*
 * Sysfs driver attributes
 */
अटल sमाप_प्रकार version_show(काष्ठा device_driver *dd, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, म_माप(MEGASAS_VERSION) + 2, "%s\n",
			MEGASAS_VERSION);
पूर्ण
अटल DRIVER_ATTR_RO(version);

अटल sमाप_प्रकार release_date_show(काष्ठा device_driver *dd, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, म_माप(MEGASAS_RELDATE) + 2, "%s\n",
		MEGASAS_RELDATE);
पूर्ण
अटल DRIVER_ATTR_RO(release_date);

अटल sमाप_प्रकार support_poll_क्रम_event_show(काष्ठा device_driver *dd, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", support_poll_क्रम_event);
पूर्ण
अटल DRIVER_ATTR_RO(support_poll_क्रम_event);

अटल sमाप_प्रकार support_device_change_show(काष्ठा device_driver *dd, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", support_device_change);
पूर्ण
अटल DRIVER_ATTR_RO(support_device_change);

अटल sमाप_प्रकार dbg_lvl_show(काष्ठा device_driver *dd, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", megasas_dbg_lvl);
पूर्ण

अटल sमाप_प्रकार dbg_lvl_store(काष्ठा device_driver *dd, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	पूर्णांक retval = count;

	अगर (माला_पूछो(buf, "%u", &megasas_dbg_lvl) < 1) अणु
		prपूर्णांकk(KERN_ERR "megasas: could not set dbg_lvl\n");
		retval = -EINVAL;
	पूर्ण
	वापस retval;
पूर्ण
अटल DRIVER_ATTR_RW(dbg_lvl);

अटल sमाप_प्रकार
support_nvme_encapsulation_show(काष्ठा device_driver *dd, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", support_nvme_encapsulation);
पूर्ण

अटल DRIVER_ATTR_RO(support_nvme_encapsulation);

अटल sमाप_प्रकार
support_pci_lane_margining_show(काष्ठा device_driver *dd, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", support_pci_lane_margining);
पूर्ण

अटल DRIVER_ATTR_RO(support_pci_lane_margining);

अटल अंतरभूत व्योम megasas_हटाओ_scsi_device(काष्ठा scsi_device *sdev)
अणु
	sdev_prपूर्णांकk(KERN_INFO, sdev, "SCSI device is removed\n");
	scsi_हटाओ_device(sdev);
	scsi_device_put(sdev);
पूर्ण

/**
 * megasas_update_device_list -	Update the PD and LD device list from FW
 *				after an AEN event notअगरication
 * @instance:			Adapter soft state
 * @event_type:			Indicates type of event (PD or LD event)
 *
 * @वापस:			Success or failure
 *
 * Issue DCMDs to Firmware to update the पूर्णांकernal device list in driver.
 * Based on the FW support, driver sends the HOST_DEVICE_LIST or combination
 * of PD_LIST/LD_LIST_QUERY DCMDs to get the device list.
 */
अटल
पूर्णांक megasas_update_device_list(काष्ठा megasas_instance *instance,
			       पूर्णांक event_type)
अणु
	पूर्णांक dcmd_ret = DCMD_SUCCESS;

	अगर (instance->enable_fw_dev_list) अणु
		dcmd_ret = megasas_host_device_list_query(instance, false);
		अगर (dcmd_ret != DCMD_SUCCESS)
			जाओ out;
	पूर्ण अन्यथा अणु
		अगर (event_type & SCAN_PD_CHANNEL) अणु
			dcmd_ret = megasas_get_pd_list(instance);

			अगर (dcmd_ret != DCMD_SUCCESS)
				जाओ out;
		पूर्ण

		अगर (event_type & SCAN_VD_CHANNEL) अणु
			अगर (!instance->requestorId ||
			    (instance->requestorId &&
			     megasas_get_ld_vf_affiliation(instance, 0))) अणु
				dcmd_ret = megasas_ld_list_query(instance,
						MR_LD_QUERY_TYPE_EXPOSED_TO_HOST);
				अगर (dcmd_ret != DCMD_SUCCESS)
					जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	वापस dcmd_ret;
पूर्ण

/**
 * megasas_add_हटाओ_devices -	Add/हटाओ devices to SCSI mid-layer
 *				after an AEN event notअगरication
 * @instance:			Adapter soft state
 * @scan_type:			Indicates type of devices (PD/LD) to add
 * @वापस			व्योम
 */
अटल
व्योम megasas_add_हटाओ_devices(काष्ठा megasas_instance *instance,
				पूर्णांक scan_type)
अणु
	पूर्णांक i, j;
	u16 pd_index = 0;
	u16 ld_index = 0;
	u16 channel = 0, id = 0;
	काष्ठा Scsi_Host *host;
	काष्ठा scsi_device *sdev1;
	काष्ठा MR_HOST_DEVICE_LIST *targetid_list = शून्य;
	काष्ठा MR_HOST_DEVICE_LIST_ENTRY *targetid_entry = शून्य;

	host = instance->host;

	अगर (instance->enable_fw_dev_list) अणु
		targetid_list = instance->host_device_list_buf;
		क्रम (i = 0; i < targetid_list->count; i++) अणु
			targetid_entry = &targetid_list->host_device_list[i];
			अगर (targetid_entry->flags.u.bits.is_sys_pd) अणु
				channel = le16_to_cpu(targetid_entry->target_id) /
						MEGASAS_MAX_DEV_PER_CHANNEL;
				id = le16_to_cpu(targetid_entry->target_id) %
						MEGASAS_MAX_DEV_PER_CHANNEL;
			पूर्ण अन्यथा अणु
				channel = MEGASAS_MAX_PD_CHANNELS +
					  (le16_to_cpu(targetid_entry->target_id) /
					   MEGASAS_MAX_DEV_PER_CHANNEL);
				id = le16_to_cpu(targetid_entry->target_id) %
						MEGASAS_MAX_DEV_PER_CHANNEL;
			पूर्ण
			sdev1 = scsi_device_lookup(host, channel, id, 0);
			अगर (!sdev1) अणु
				scsi_add_device(host, channel, id, 0);
			पूर्ण अन्यथा अणु
				scsi_device_put(sdev1);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (scan_type & SCAN_PD_CHANNEL) अणु
		क्रम (i = 0; i < MEGASAS_MAX_PD_CHANNELS; i++) अणु
			क्रम (j = 0; j < MEGASAS_MAX_DEV_PER_CHANNEL; j++) अणु
				pd_index = i * MEGASAS_MAX_DEV_PER_CHANNEL + j;
				sdev1 = scsi_device_lookup(host, i, j, 0);
				अगर (instance->pd_list[pd_index].driveState ==
							MR_PD_STATE_SYSTEM) अणु
					अगर (!sdev1)
						scsi_add_device(host, i, j, 0);
					अन्यथा
						scsi_device_put(sdev1);
				पूर्ण अन्यथा अणु
					अगर (sdev1)
						megasas_हटाओ_scsi_device(sdev1);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (scan_type & SCAN_VD_CHANNEL) अणु
		क्रम (i = 0; i < MEGASAS_MAX_LD_CHANNELS; i++) अणु
			क्रम (j = 0; j < MEGASAS_MAX_DEV_PER_CHANNEL; j++) अणु
				ld_index = (i * MEGASAS_MAX_DEV_PER_CHANNEL) + j;
				sdev1 = scsi_device_lookup(host,
						MEGASAS_MAX_PD_CHANNELS + i, j, 0);
				अगर (instance->ld_ids[ld_index] != 0xff) अणु
					अगर (!sdev1)
						scsi_add_device(host, MEGASAS_MAX_PD_CHANNELS + i, j, 0);
					अन्यथा
						scsi_device_put(sdev1);
				पूर्ण अन्यथा अणु
					अगर (sdev1)
						megasas_हटाओ_scsi_device(sdev1);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

पूर्ण

अटल व्योम
megasas_aen_polling(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा megasas_aen_event *ev =
		container_of(work, काष्ठा megasas_aen_event, hotplug_work.work);
	काष्ठा megasas_instance *instance = ev->instance;
	जोड़ megasas_evt_class_locale class_locale;
	पूर्णांक event_type = 0;
	u32 seq_num;
	पूर्णांक error;
	u8  dcmd_ret = DCMD_SUCCESS;

	अगर (!instance) अणु
		prपूर्णांकk(KERN_ERR "invalid instance!\n");
		kमुक्त(ev);
		वापस;
	पूर्ण

	/* Don't run the event workqueue thपढ़ो अगर OCR is running */
	mutex_lock(&instance->reset_mutex);

	instance->ev = शून्य;
	अगर (instance->evt_detail) अणु
		megasas_decode_evt(instance);

		चयन (le32_to_cpu(instance->evt_detail->code)) अणु

		हाल MR_EVT_PD_INSERTED:
		हाल MR_EVT_PD_REMOVED:
			event_type = SCAN_PD_CHANNEL;
			अवरोध;

		हाल MR_EVT_LD_OFFLINE:
		हाल MR_EVT_CFG_CLEARED:
		हाल MR_EVT_LD_DELETED:
		हाल MR_EVT_LD_CREATED:
			event_type = SCAN_VD_CHANNEL;
			अवरोध;

		हाल MR_EVT_CTRL_HOST_BUS_SCAN_REQUESTED:
		हाल MR_EVT_FOREIGN_CFG_IMPORTED:
		हाल MR_EVT_LD_STATE_CHANGE:
			event_type = SCAN_PD_CHANNEL | SCAN_VD_CHANNEL;
			dev_info(&instance->pdev->dev, "scanning for scsi%d...\n",
				instance->host->host_no);
			अवरोध;

		हाल MR_EVT_CTRL_PROP_CHANGED:
			dcmd_ret = megasas_get_ctrl_info(instance);
			अगर (dcmd_ret == DCMD_SUCCESS &&
			    instance->snapdump_रुको_समय) अणु
				megasas_get_snapdump_properties(instance);
				dev_info(&instance->pdev->dev,
					 "Snap dump wait time\t: %d\n",
					 instance->snapdump_रुको_समय);
			पूर्ण
			अवरोध;
		शेष:
			event_type = 0;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&instance->pdev->dev, "invalid evt_detail!\n");
		mutex_unlock(&instance->reset_mutex);
		kमुक्त(ev);
		वापस;
	पूर्ण

	अगर (event_type)
		dcmd_ret = megasas_update_device_list(instance, event_type);

	mutex_unlock(&instance->reset_mutex);

	अगर (event_type && dcmd_ret == DCMD_SUCCESS)
		megasas_add_हटाओ_devices(instance, event_type);

	अगर (dcmd_ret == DCMD_SUCCESS)
		seq_num = le32_to_cpu(instance->evt_detail->seq_num) + 1;
	अन्यथा
		seq_num = instance->last_seq_num;

	/* Register AEN with FW क्रम latest sequence number plus 1 */
	class_locale.members.reserved = 0;
	class_locale.members.locale = MR_EVT_LOCALE_ALL;
	class_locale.members.class = MR_EVT_CLASS_DEBUG;

	अगर (instance->aen_cmd != शून्य) अणु
		kमुक्त(ev);
		वापस;
	पूर्ण

	mutex_lock(&instance->reset_mutex);
	error = megasas_रेजिस्टर_aen(instance, seq_num,
					class_locale.word);
	अगर (error)
		dev_err(&instance->pdev->dev,
			"register aen failed error %x\n", error);

	mutex_unlock(&instance->reset_mutex);
	kमुक्त(ev);
पूर्ण

/**
 * megasas_init - Driver load entry poपूर्णांक
 */
अटल पूर्णांक __init megasas_init(व्योम)
अणु
	पूर्णांक rval;

	/*
	 * Booted in kdump kernel, minimize memory footprपूर्णांकs by
	 * disabling few features
	 */
	अगर (reset_devices) अणु
		msix_vectors = 1;
		rdpq_enable = 0;
		dual_qdepth_disable = 1;
		poll_queues = 0;
	पूर्ण

	/*
	 * Announce driver version and other inक्रमmation
	 */
	pr_info("megasas: %s\n", MEGASAS_VERSION);

	spin_lock_init(&poll_aen_lock);

	support_poll_क्रम_event = 2;
	support_device_change = 1;
	support_nvme_encapsulation = true;
	support_pci_lane_margining = true;

	स_रखो(&megasas_mgmt_info, 0, माप(megasas_mgmt_info));

	/*
	 * Register अक्षरacter device node
	 */
	rval = रेजिस्टर_chrdev(0, "megaraid_sas_ioctl", &megasas_mgmt_fops);

	अगर (rval < 0) अणु
		prपूर्णांकk(KERN_DEBUG "megasas: failed to open device node\n");
		वापस rval;
	पूर्ण

	megasas_mgmt_majorno = rval;

	megasas_init_debugfs();

	/*
	 * Register ourselves as PCI hotplug module
	 */
	rval = pci_रेजिस्टर_driver(&megasas_pci_driver);

	अगर (rval) अणु
		prपूर्णांकk(KERN_DEBUG "megasas: PCI hotplug registration failed \n");
		जाओ err_pcidrv;
	पूर्ण

	अगर ((event_log_level < MFI_EVT_CLASS_DEBUG) ||
	    (event_log_level > MFI_EVT_CLASS_DEAD)) अणु
		pr_warn("megaraid_sas: provided event log level is out of range, setting it to default 2(CLASS_CRITICAL), permissible range is: -2 to 4\n");
		event_log_level = MFI_EVT_CLASS_CRITICAL;
	पूर्ण

	rval = driver_create_file(&megasas_pci_driver.driver,
				  &driver_attr_version);
	अगर (rval)
		जाओ err_dcf_attr_ver;

	rval = driver_create_file(&megasas_pci_driver.driver,
				  &driver_attr_release_date);
	अगर (rval)
		जाओ err_dcf_rel_date;

	rval = driver_create_file(&megasas_pci_driver.driver,
				&driver_attr_support_poll_क्रम_event);
	अगर (rval)
		जाओ err_dcf_support_poll_क्रम_event;

	rval = driver_create_file(&megasas_pci_driver.driver,
				  &driver_attr_dbg_lvl);
	अगर (rval)
		जाओ err_dcf_dbg_lvl;
	rval = driver_create_file(&megasas_pci_driver.driver,
				&driver_attr_support_device_change);
	अगर (rval)
		जाओ err_dcf_support_device_change;

	rval = driver_create_file(&megasas_pci_driver.driver,
				  &driver_attr_support_nvme_encapsulation);
	अगर (rval)
		जाओ err_dcf_support_nvme_encapsulation;

	rval = driver_create_file(&megasas_pci_driver.driver,
				  &driver_attr_support_pci_lane_margining);
	अगर (rval)
		जाओ err_dcf_support_pci_lane_margining;

	वापस rval;

err_dcf_support_pci_lane_margining:
	driver_हटाओ_file(&megasas_pci_driver.driver,
			   &driver_attr_support_nvme_encapsulation);

err_dcf_support_nvme_encapsulation:
	driver_हटाओ_file(&megasas_pci_driver.driver,
			   &driver_attr_support_device_change);

err_dcf_support_device_change:
	driver_हटाओ_file(&megasas_pci_driver.driver,
			   &driver_attr_dbg_lvl);
err_dcf_dbg_lvl:
	driver_हटाओ_file(&megasas_pci_driver.driver,
			&driver_attr_support_poll_क्रम_event);
err_dcf_support_poll_क्रम_event:
	driver_हटाओ_file(&megasas_pci_driver.driver,
			   &driver_attr_release_date);
err_dcf_rel_date:
	driver_हटाओ_file(&megasas_pci_driver.driver, &driver_attr_version);
err_dcf_attr_ver:
	pci_unरेजिस्टर_driver(&megasas_pci_driver);
err_pcidrv:
	megasas_निकास_debugfs();
	unरेजिस्टर_chrdev(megasas_mgmt_majorno, "megaraid_sas_ioctl");
	वापस rval;
पूर्ण

/**
 * megasas_निकास - Driver unload entry poपूर्णांक
 */
अटल व्योम __निकास megasas_निकास(व्योम)
अणु
	driver_हटाओ_file(&megasas_pci_driver.driver,
			   &driver_attr_dbg_lvl);
	driver_हटाओ_file(&megasas_pci_driver.driver,
			&driver_attr_support_poll_क्रम_event);
	driver_हटाओ_file(&megasas_pci_driver.driver,
			&driver_attr_support_device_change);
	driver_हटाओ_file(&megasas_pci_driver.driver,
			   &driver_attr_release_date);
	driver_हटाओ_file(&megasas_pci_driver.driver, &driver_attr_version);
	driver_हटाओ_file(&megasas_pci_driver.driver,
			   &driver_attr_support_nvme_encapsulation);
	driver_हटाओ_file(&megasas_pci_driver.driver,
			   &driver_attr_support_pci_lane_margining);

	pci_unरेजिस्टर_driver(&megasas_pci_driver);
	megasas_निकास_debugfs();
	unरेजिस्टर_chrdev(megasas_mgmt_majorno, "megaraid_sas_ioctl");
पूर्ण

module_init(megasas_init);
module_निकास(megasas_निकास);
