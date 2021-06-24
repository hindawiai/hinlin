<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2018-2020 Broadcom.
 */

#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/firmware.h>
#समावेश <linux/fs.h>
#समावेश <linux/idr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kref.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_regs.h>
#समावेश <uapi/linux/misc/bcm_vk.h>

#समावेश "bcm_vk.h"

#घोषणा PCI_DEVICE_ID_VALKYRIE	0x5e87
#घोषणा PCI_DEVICE_ID_VIPER	0x5e88

अटल DEFINE_IDA(bcm_vk_ida);

क्रमागत soc_idx अणु
	VALKYRIE_A0 = 0,
	VALKYRIE_B0,
	VIPER,
	VK_IDX_INVALID
पूर्ण;

क्रमागत img_idx अणु
	IMG_PRI = 0,
	IMG_SEC,
	IMG_PER_TYPE_MAX
पूर्ण;

काष्ठा load_image_entry अणु
	स्थिर u32 image_type;
	स्थिर अक्षर *image_name[IMG_PER_TYPE_MAX];
पूर्ण;

#घोषणा NUM_BOOT_STAGES 2
/* शेष firmware images names */
अटल स्थिर काष्ठा load_image_entry image_tab[][NUM_BOOT_STAGES] = अणु
	[VALKYRIE_A0] = अणु
		अणुVK_IMAGE_TYPE_BOOT1, अणु"vk_a0-boot1.bin", "vk-boot1.bin"पूर्णपूर्ण,
		अणुVK_IMAGE_TYPE_BOOT2, अणु"vk_a0-boot2.bin", "vk-boot2.bin"पूर्णपूर्ण
	पूर्ण,
	[VALKYRIE_B0] = अणु
		अणुVK_IMAGE_TYPE_BOOT1, अणु"vk_b0-boot1.bin", "vk-boot1.bin"पूर्णपूर्ण,
		अणुVK_IMAGE_TYPE_BOOT2, अणु"vk_b0-boot2.bin", "vk-boot2.bin"पूर्णपूर्ण
	पूर्ण,

	[VIPER] = अणु
		अणुVK_IMAGE_TYPE_BOOT1, अणु"vp-boot1.bin", ""पूर्णपूर्ण,
		अणुVK_IMAGE_TYPE_BOOT2, अणु"vp-boot2.bin", ""पूर्णपूर्ण
	पूर्ण,
पूर्ण;

/* Location of memory base addresses of पूर्णांकerest in BAR1 */
/* Load Boot1 to start of ITCM */
#घोषणा BAR1_CODEPUSH_BASE_BOOT1	0x100000

/* Allow minimum 1s क्रम Load Image समयout responses */
#घोषणा LOAD_IMAGE_TIMEOUT_MS		(1 * MSEC_PER_SEC)

/* Image startup समयouts */
#घोषणा BOOT1_STARTUP_TIMEOUT_MS	(5 * MSEC_PER_SEC)
#घोषणा BOOT2_STARTUP_TIMEOUT_MS	(10 * MSEC_PER_SEC)

/* 1ms रुको क्रम checking the transfer complete status */
#घोषणा TXFR_COMPLETE_TIMEOUT_MS	1

/* MSIX usages */
#घोषणा VK_MSIX_MSGQ_MAX		3
#घोषणा VK_MSIX_NOTF_MAX		1
#घोषणा VK_MSIX_TTY_MAX			BCM_VK_NUM_TTY
#घोषणा VK_MSIX_IRQ_MAX			(VK_MSIX_MSGQ_MAX + VK_MSIX_NOTF_MAX + \
					 VK_MSIX_TTY_MAX)
#घोषणा VK_MSIX_IRQ_MIN_REQ             (VK_MSIX_MSGQ_MAX + VK_MSIX_NOTF_MAX)

/* Number of bits set in DMA mask*/
#घोषणा BCM_VK_DMA_BITS			64

/* Ucode boot रुको समय */
#घोषणा BCM_VK_UCODE_BOOT_US            (100 * USEC_PER_MSEC)
/* 50% margin */
#घोषणा BCM_VK_UCODE_BOOT_MAX_US        ((BCM_VK_UCODE_BOOT_US * 3) >> 1)

/* deinit समय क्रम the card os after receiving करोorbell */
#घोषणा BCM_VK_DEINIT_TIME_MS		(2 * MSEC_PER_SEC)

/*
 * module parameters
 */
अटल bool स्वतः_load = true;
module_param(स्वतः_load, bool, 0444);
MODULE_PARM_DESC(स्वतः_load,
		 "Load images automatically at PCIe probe time.\n");
अटल uपूर्णांक nr_scratch_pages = VK_BAR1_SCRATCH_DEF_NR_PAGES;
module_param(nr_scratch_pages, uपूर्णांक, 0444);
MODULE_PARM_DESC(nr_scratch_pages,
		 "Number of pre allocated DMAable coherent pages.\n");
अटल uपूर्णांक nr_ib_sgl_blk = BCM_VK_DEF_IB_SGL_BLK_LEN;
module_param(nr_ib_sgl_blk, uपूर्णांक, 0444);
MODULE_PARM_DESC(nr_ib_sgl_blk,
		 "Number of in-band msg blks for short SGL.\n");

/*
 * alerts that could be generated from peer
 */
स्थिर काष्ठा bcm_vk_entry bcm_vk_peer_err[BCM_VK_PEER_ERR_NUM] = अणु
	अणुERR_LOG_UECC, ERR_LOG_UECC, "uecc"पूर्ण,
	अणुERR_LOG_SSIM_BUSY, ERR_LOG_SSIM_BUSY, "ssim_busy"पूर्ण,
	अणुERR_LOG_AFBC_BUSY, ERR_LOG_AFBC_BUSY, "afbc_busy"पूर्ण,
	अणुERR_LOG_HIGH_TEMP_ERR, ERR_LOG_HIGH_TEMP_ERR, "high_temp"पूर्ण,
	अणुERR_LOG_WDOG_TIMEOUT, ERR_LOG_WDOG_TIMEOUT, "wdog_timeout"पूर्ण,
	अणुERR_LOG_SYS_FAULT, ERR_LOG_SYS_FAULT, "sys_fault"पूर्ण,
	अणुERR_LOG_RAMDUMP, ERR_LOG_RAMDUMP, "ramdump"पूर्ण,
	अणुERR_LOG_COP_WDOG_TIMEOUT, ERR_LOG_COP_WDOG_TIMEOUT,
	 "cop_wdog_timeout"पूर्ण,
	अणुERR_LOG_MEM_ALLOC_FAIL, ERR_LOG_MEM_ALLOC_FAIL, "malloc_fail warn"पूर्ण,
	अणुERR_LOG_LOW_TEMP_WARN, ERR_LOG_LOW_TEMP_WARN, "low_temp warn"पूर्ण,
	अणुERR_LOG_ECC, ERR_LOG_ECC, "ecc"पूर्ण,
	अणुERR_LOG_IPC_DWN, ERR_LOG_IPC_DWN, "ipc_down"पूर्ण,
पूर्ण;

/* alerts detected by the host */
स्थिर काष्ठा bcm_vk_entry bcm_vk_host_err[BCM_VK_HOST_ERR_NUM] = अणु
	अणुERR_LOG_HOST_PCIE_DWN, ERR_LOG_HOST_PCIE_DWN, "PCIe_down"पूर्ण,
	अणुERR_LOG_HOST_HB_FAIL, ERR_LOG_HOST_HB_FAIL, "hb_fail"पूर्ण,
	अणुERR_LOG_HOST_INTF_V_FAIL, ERR_LOG_HOST_INTF_V_FAIL, "intf_ver_fail"पूर्ण,
पूर्ण;

irqवापस_t bcm_vk_notf_irqhandler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा bcm_vk *vk = dev_id;

	अगर (!bcm_vk_drv_access_ok(vk)) अणु
		dev_err(&vk->pdev->dev,
			"Interrupt %d received when msgq not inited\n", irq);
		जाओ skip_schedule_work;
	पूर्ण

	/* अगर notअगरication is not pending, set bit and schedule work */
	अगर (test_and_set_bit(BCM_VK_WQ_NOTF_PEND, vk->wq_offload) == 0)
		queue_work(vk->wq_thपढ़ो, &vk->wq_work);

skip_schedule_work:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bcm_vk_पूर्णांकf_ver_chk(काष्ठा bcm_vk *vk)
अणु
	काष्ठा device *dev = &vk->pdev->dev;
	u32 reg;
	u16 major, minor;
	पूर्णांक ret = 0;

	/* पढ़ो पूर्णांकerface रेजिस्टर */
	reg = vkपढ़ो32(vk, BAR_0, BAR_INTF_VER);
	major = (reg >> BAR_INTF_VER_MAJOR_SHIFT) & BAR_INTF_VER_MASK;
	minor = reg & BAR_INTF_VER_MASK;

	/*
	 * अगर major number is 0, it is pre-release and it would be allowed
	 * to जारी, अन्यथा, check versions accordingly
	 */
	अगर (!major) अणु
		dev_warn(dev, "Pre-release major.minor=%d.%d - drv %d.%d\n",
			 major, minor, SEMANTIC_MAJOR, SEMANTIC_MINOR);
	पूर्ण अन्यथा अगर (major != SEMANTIC_MAJOR) अणु
		dev_err(dev,
			"Intf major.minor=%d.%d rejected - drv %d.%d\n",
			major, minor, SEMANTIC_MAJOR, SEMANTIC_MINOR);
		bcm_vk_set_host_alert(vk, ERR_LOG_HOST_INTF_V_FAIL);
		ret = -EPFNOSUPPORT;
	पूर्ण अन्यथा अणु
		dev_dbg(dev,
			"Intf major.minor=%d.%d passed - drv %d.%d\n",
			major, minor, SEMANTIC_MAJOR, SEMANTIC_MINOR);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम bcm_vk_log_notf(काष्ठा bcm_vk *vk,
			    काष्ठा bcm_vk_alert *alert,
			    काष्ठा bcm_vk_entry स्थिर *entry_tab,
			    स्थिर u32 table_size)
अणु
	u32 i;
	u32 masked_val, latched_val;
	काष्ठा bcm_vk_entry स्थिर *entry;
	u32 reg;
	u16 ecc_mem_err, uecc_mem_err;
	काष्ठा device *dev = &vk->pdev->dev;

	क्रम (i = 0; i < table_size; i++) अणु
		entry = &entry_tab[i];
		masked_val = entry->mask & alert->notfs;
		latched_val = entry->mask & alert->flags;

		अगर (masked_val == ERR_LOG_UECC) अणु
			/*
			 * अगर there is dअगरference between stored cnt and it
			 * is greater than threshold, log it.
			 */
			reg = vkपढ़ो32(vk, BAR_0, BAR_CARD_ERR_MEM);
			BCM_VK_EXTRACT_FIELD(uecc_mem_err, reg,
					     BCM_VK_MEM_ERR_FIELD_MASK,
					     BCM_VK_UECC_MEM_ERR_SHIFT);
			अगर ((uecc_mem_err != vk->alert_cnts.uecc) &&
			    (uecc_mem_err >= BCM_VK_UECC_THRESHOLD))
				dev_info(dev,
					 "ALERT! %s.%d uecc RAISED - ErrCnt %d\n",
					 DRV_MODULE_NAME, vk->devid,
					 uecc_mem_err);
			vk->alert_cnts.uecc = uecc_mem_err;
		पूर्ण अन्यथा अगर (masked_val == ERR_LOG_ECC) अणु
			reg = vkपढ़ो32(vk, BAR_0, BAR_CARD_ERR_MEM);
			BCM_VK_EXTRACT_FIELD(ecc_mem_err, reg,
					     BCM_VK_MEM_ERR_FIELD_MASK,
					     BCM_VK_ECC_MEM_ERR_SHIFT);
			अगर ((ecc_mem_err != vk->alert_cnts.ecc) &&
			    (ecc_mem_err >= BCM_VK_ECC_THRESHOLD))
				dev_info(dev, "ALERT! %s.%d ecc RAISED - ErrCnt %d\n",
					 DRV_MODULE_NAME, vk->devid,
					 ecc_mem_err);
			vk->alert_cnts.ecc = ecc_mem_err;
		पूर्ण अन्यथा अगर (masked_val != latched_val) अणु
			/* prपूर्णांक a log as info */
			dev_info(dev, "ALERT! %s.%d %s %s\n",
				 DRV_MODULE_NAME, vk->devid, entry->str,
				 masked_val ? "RAISED" : "CLEARED");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bcm_vk_dump_peer_log(काष्ठा bcm_vk *vk)
अणु
	काष्ठा bcm_vk_peer_log log;
	काष्ठा bcm_vk_peer_log *log_info = &vk->peerlog_info;
	अक्षर loc_buf[BCM_VK_PEER_LOG_LINE_MAX];
	पूर्णांक cnt;
	काष्ठा device *dev = &vk->pdev->dev;
	अचिन्हित पूर्णांक data_offset;

	स_नकल_fromio(&log, vk->bar[BAR_2] + vk->peerlog_off, माप(log));

	dev_dbg(dev, "Peer PANIC: Size 0x%x(0x%x), [Rd Wr] = [%d %d]\n",
		log.buf_size, log.mask, log.rd_idx, log.wr_idx);

	अगर (!log_info->buf_size) अणु
		dev_err(dev, "Peer log dump disabled - skipped!\n");
		वापस;
	पूर्ण

	/* perक्रमm range checking क्रम rd/wr idx */
	अगर ((log.rd_idx > log_info->mask) ||
	    (log.wr_idx > log_info->mask) ||
	    (log.buf_size != log_info->buf_size) ||
	    (log.mask != log_info->mask)) अणु
		dev_err(dev,
			"Corrupted Ptrs: Size 0x%x(0x%x) Mask 0x%x(0x%x) [Rd Wr] = [%d %d], skip log dump.\n",
			log_info->buf_size, log.buf_size,
			log_info->mask, log.mask,
			log.rd_idx, log.wr_idx);
		वापस;
	पूर्ण

	cnt = 0;
	data_offset = vk->peerlog_off + माप(काष्ठा bcm_vk_peer_log);
	loc_buf[BCM_VK_PEER_LOG_LINE_MAX - 1] = '\0';
	जबतक (log.rd_idx != log.wr_idx) अणु
		loc_buf[cnt] = vkपढ़ो8(vk, BAR_2, data_offset + log.rd_idx);

		अगर ((loc_buf[cnt] == '\0') ||
		    (cnt == (BCM_VK_PEER_LOG_LINE_MAX - 1))) अणु
			dev_err(dev, "%s", loc_buf);
			cnt = 0;
		पूर्ण अन्यथा अणु
			cnt++;
		पूर्ण
		log.rd_idx = (log.rd_idx + 1) & log.mask;
	पूर्ण
	/* update rd idx at the end */
	vkग_लिखो32(vk, log.rd_idx, BAR_2,
		  vk->peerlog_off + दुरत्व(काष्ठा bcm_vk_peer_log, rd_idx));
पूर्ण

व्योम bcm_vk_handle_notf(काष्ठा bcm_vk *vk)
अणु
	u32 reg;
	काष्ठा bcm_vk_alert alert;
	bool पूर्णांकf_करोwn;
	अचिन्हित दीर्घ flags;

	/* handle peer alerts and then locally detected ones */
	reg = vkपढ़ो32(vk, BAR_0, BAR_CARD_ERR_LOG);
	पूर्णांकf_करोwn = BCM_VK_INTF_IS_DOWN(reg);
	अगर (!पूर्णांकf_करोwn) अणु
		vk->peer_alert.notfs = reg;
		bcm_vk_log_notf(vk, &vk->peer_alert, bcm_vk_peer_err,
				ARRAY_SIZE(bcm_vk_peer_err));
		vk->peer_alert.flags = vk->peer_alert.notfs;
	पूर्ण अन्यथा अणु
		/* turn off access */
		bcm_vk_blk_drv_access(vk);
	पूर्ण

	/* check and make copy of alert with lock and then मुक्त lock */
	spin_lock_irqsave(&vk->host_alert_lock, flags);
	अगर (पूर्णांकf_करोwn)
		vk->host_alert.notfs |= ERR_LOG_HOST_PCIE_DWN;

	alert = vk->host_alert;
	vk->host_alert.flags = vk->host_alert.notfs;
	spin_unlock_irqrestore(&vk->host_alert_lock, flags);

	/* call display with copy */
	bcm_vk_log_notf(vk, &alert, bcm_vk_host_err,
			ARRAY_SIZE(bcm_vk_host_err));

	/*
	 * If it is a sys fault or heartbeat समयout, we would like extract
	 * log msg from the card so that we would know what is the last fault
	 */
	अगर (!पूर्णांकf_करोwn &&
	    ((vk->host_alert.flags & ERR_LOG_HOST_HB_FAIL) ||
	     (vk->peer_alert.flags & ERR_LOG_SYS_FAULT)))
		bcm_vk_dump_peer_log(vk);
पूर्ण

अटल अंतरभूत पूर्णांक bcm_vk_रुको(काष्ठा bcm_vk *vk, क्रमागत pci_barno bar,
			      u64 offset, u32 mask, u32 value,
			      अचिन्हित दीर्घ समयout_ms)
अणु
	काष्ठा device *dev = &vk->pdev->dev;
	अचिन्हित दीर्घ start_समय;
	अचिन्हित दीर्घ समयout;
	u32 rd_val, boot_status;

	start_समय = jअगरfies;
	समयout = start_समय + msecs_to_jअगरfies(समयout_ms);

	करो अणु
		rd_val = vkपढ़ो32(vk, bar, offset);
		dev_dbg(dev, "BAR%d Offset=0x%llx: 0x%x\n",
			bar, offset, rd_val);

		/* check क्रम any boot err condition */
		boot_status = vkपढ़ो32(vk, BAR_0, BAR_BOOT_STATUS);
		अगर (boot_status & BOOT_ERR_MASK) अणु
			dev_err(dev, "Boot Err 0x%x, progress 0x%x after %d ms\n",
				(boot_status & BOOT_ERR_MASK) >> BOOT_ERR_SHIFT,
				boot_status & BOOT_PROG_MASK,
				jअगरfies_to_msecs(jअगरfies - start_समय));
			वापस -EFAULT;
		पूर्ण

		अगर (समय_after(jअगरfies, समयout))
			वापस -ETIMEDOUT;

		cpu_relax();
		cond_resched();
	पूर्ण जबतक ((rd_val & mask) != value);

	वापस 0;
पूर्ण

अटल व्योम bcm_vk_get_card_info(काष्ठा bcm_vk *vk)
अणु
	काष्ठा device *dev = &vk->pdev->dev;
	u32 offset;
	पूर्णांक i;
	u8 *dst;
	काष्ठा bcm_vk_card_info *info = &vk->card_info;

	/* first पढ़ो the offset from spare रेजिस्टर */
	offset = vkपढ़ो32(vk, BAR_0, BAR_CARD_STATIC_INFO);
	offset &= (pci_resource_len(vk->pdev, BAR_2 * 2) - 1);

	/* based on the offset, पढ़ो info to पूर्णांकernal card info काष्ठाure */
	dst = (u8 *)info;
	क्रम (i = 0; i < माप(*info); i++)
		*dst++ = vkपढ़ो8(vk, BAR_2, offset++);

#घोषणा CARD_INFO_LOG_FMT "version   : %x\n" \
			  "os_tag    : %s\n" \
			  "cmpt_tag  : %s\n" \
			  "cpu_freq  : %d MHz\n" \
			  "cpu_scale : %d full, %d lowest\n" \
			  "ddr_freq  : %d MHz\n" \
			  "ddr_size  : %d MB\n" \
			  "video_freq: %d MHz\n"
	dev_dbg(dev, CARD_INFO_LOG_FMT, info->version, info->os_tag,
		info->cmpt_tag, info->cpu_freq_mhz, info->cpu_scale[0],
		info->cpu_scale[MAX_OPP - 1], info->ddr_freq_mhz,
		info->ddr_size_MB, info->video_core_freq_mhz);

	/*
	 * get the peer log poपूर्णांकer, only need the offset, and get record
	 * of the log buffer inक्रमmation which would be used क्रम checking
	 * beक्रमe dump, in हाल the BAR2 memory has been corrupted.
	 */
	vk->peerlog_off = offset;
	स_नकल_fromio(&vk->peerlog_info, vk->bar[BAR_2] + vk->peerlog_off,
		      माप(vk->peerlog_info));

	/*
	 * Do a range checking and अगर out of bound, the record will be zeroed
	 * which guarantees that nothing would be dumped.  In other words,
	 * peer dump is disabled.
	 */
	अगर ((vk->peerlog_info.buf_size > BCM_VK_PEER_LOG_BUF_MAX) ||
	    (vk->peerlog_info.mask != (vk->peerlog_info.buf_size - 1)) ||
	    (vk->peerlog_info.rd_idx > vk->peerlog_info.mask) ||
	    (vk->peerlog_info.wr_idx > vk->peerlog_info.mask)) अणु
		dev_err(dev, "Peer log disabled - range error: Size 0x%x(0x%x), [Rd Wr] = [%d %d]\n",
			vk->peerlog_info.buf_size,
			vk->peerlog_info.mask,
			vk->peerlog_info.rd_idx,
			vk->peerlog_info.wr_idx);
		स_रखो(&vk->peerlog_info, 0, माप(vk->peerlog_info));
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "Peer log: Size 0x%x(0x%x), [Rd Wr] = [%d %d]\n",
			vk->peerlog_info.buf_size,
			vk->peerlog_info.mask,
			vk->peerlog_info.rd_idx,
			vk->peerlog_info.wr_idx);
	पूर्ण
पूर्ण

अटल व्योम bcm_vk_get_proc_mon_info(काष्ठा bcm_vk *vk)
अणु
	काष्ठा device *dev = &vk->pdev->dev;
	काष्ठा bcm_vk_proc_mon_info *mon = &vk->proc_mon_info;
	u32 num, entry_size, offset, buf_size;
	u8 *dst;

	/* calculate offset which is based on peerlog offset */
	buf_size = vkपढ़ो32(vk, BAR_2,
			    vk->peerlog_off
			    + दुरत्व(काष्ठा bcm_vk_peer_log, buf_size));
	offset = vk->peerlog_off + माप(काष्ठा bcm_vk_peer_log)
		 + buf_size;

	/* first पढ़ो the num and entry size */
	num = vkपढ़ो32(vk, BAR_2, offset);
	entry_size = vkपढ़ो32(vk, BAR_2, offset + माप(num));

	/* check क्रम max allowed */
	अगर (num > BCM_VK_PROC_MON_MAX) अणु
		dev_err(dev, "Processing monitoring entry %d exceeds max %d\n",
			num, BCM_VK_PROC_MON_MAX);
		वापस;
	पूर्ण
	mon->num = num;
	mon->entry_size = entry_size;

	vk->proc_mon_off = offset;

	/* पढ़ो it once that will capture those अटल info */
	dst = (u8 *)&mon->entries[0];
	offset += माप(num) + माप(entry_size);
	स_नकल_fromio(dst, vk->bar[BAR_2] + offset, num * entry_size);
पूर्ण

अटल पूर्णांक bcm_vk_sync_card_info(काष्ठा bcm_vk *vk)
अणु
	u32 rdy_marker = vkपढ़ो32(vk, BAR_1, VK_BAR1_MSGQ_DEF_RDY);

	/* check क्रम marker, but allow diags mode to skip sync */
	अगर (!bcm_vk_msgq_marker_valid(vk))
		वापस (rdy_marker == VK_BAR1_DIAG_RDY_MARKER ? 0 : -EINVAL);

	/*
	 * Write करोwn scratch addr which is used क्रम DMA. For
	 * चिन्हित part, BAR1 is accessible only after boot2 has come
	 * up
	 */
	अगर (vk->tdma_addr) अणु
		vkग_लिखो32(vk, (u64)vk->tdma_addr >> 32, BAR_1,
			  VK_BAR1_SCRATCH_OFF_HI);
		vkग_लिखो32(vk, (u32)vk->tdma_addr, BAR_1,
			  VK_BAR1_SCRATCH_OFF_LO);
		vkग_लिखो32(vk, nr_scratch_pages * PAGE_SIZE, BAR_1,
			  VK_BAR1_SCRATCH_SZ_ADDR);
	पूर्ण

	/* get अटल card info, only need to पढ़ो once */
	bcm_vk_get_card_info(vk);

	/* get the proc mon info once */
	bcm_vk_get_proc_mon_info(vk);

	वापस 0;
पूर्ण

व्योम bcm_vk_blk_drv_access(काष्ठा bcm_vk *vk)
अणु
	पूर्णांक i;

	/*
	 * समाप्त all the apps except क्रम the process that is resetting.
	 * If not called during reset, reset_pid will be 0, and all will be
	 * समाप्तed.
	 */
	spin_lock(&vk->ctx_lock);

	/* set msgq_inited to 0 so that all rd/wr will be blocked */
	atomic_set(&vk->msgq_inited, 0);

	क्रम (i = 0; i < VK_PID_HT_SZ; i++) अणु
		काष्ठा bcm_vk_ctx *ctx;

		list_क्रम_each_entry(ctx, &vk->pid_ht[i].head, node) अणु
			अगर (ctx->pid != vk->reset_pid) अणु
				dev_dbg(&vk->pdev->dev,
					"Send kill signal to pid %d\n",
					ctx->pid);
				समाप्त_pid(find_vpid(ctx->pid), SIGKILL, 1);
			पूर्ण
		पूर्ण
	पूर्ण
	bcm_vk_tty_terminate_tty_user(vk);
	spin_unlock(&vk->ctx_lock);
पूर्ण

अटल व्योम bcm_vk_buf_notअगरy(काष्ठा bcm_vk *vk, व्योम *bufp,
			      dma_addr_t host_buf_addr, u32 buf_size)
अणु
	/* update the dma address to the card */
	vkग_लिखो32(vk, (u64)host_buf_addr >> 32, BAR_1,
		  VK_BAR1_DMA_BUF_OFF_HI);
	vkग_लिखो32(vk, (u32)host_buf_addr, BAR_1,
		  VK_BAR1_DMA_BUF_OFF_LO);
	vkग_लिखो32(vk, buf_size, BAR_1, VK_BAR1_DMA_BUF_SZ);
पूर्ण

अटल पूर्णांक bcm_vk_load_image_by_type(काष्ठा bcm_vk *vk, u32 load_type,
				     स्थिर अक्षर *filename)
अणु
	काष्ठा device *dev = &vk->pdev->dev;
	स्थिर काष्ठा firmware *fw = शून्य;
	व्योम *bufp = शून्य;
	माप_प्रकार max_buf, offset;
	पूर्णांक ret;
	u64 offset_codepush;
	u32 codepush;
	u32 value;
	dma_addr_t boot_dma_addr;
	bool is_stdalone;

	अगर (load_type == VK_IMAGE_TYPE_BOOT1) अणु
		/*
		 * After POR, enable VK soft BOOTSRC so bootrom करो not clear
		 * the pushed image (the TCM memories).
		 */
		value = vkपढ़ो32(vk, BAR_0, BAR_BOOTSRC_SELECT);
		value |= BOOTSRC_SOFT_ENABLE;
		vkग_लिखो32(vk, value, BAR_0, BAR_BOOTSRC_SELECT);

		codepush = CODEPUSH_BOOTSTART + CODEPUSH_BOOT1_ENTRY;
		offset_codepush = BAR_CODEPUSH_SBL;

		/* Write a 1 to request SRAM खोलो bit */
		vkग_लिखो32(vk, CODEPUSH_BOOTSTART, BAR_0, offset_codepush);

		/* Wait क्रम VK to respond */
		ret = bcm_vk_रुको(vk, BAR_0, BAR_BOOT_STATUS, SRAM_OPEN,
				  SRAM_OPEN, LOAD_IMAGE_TIMEOUT_MS);
		अगर (ret < 0) अणु
			dev_err(dev, "boot1 wait SRAM err - ret(%d)\n", ret);
			जाओ err_buf_out;
		पूर्ण

		max_buf = SZ_256K;
		bufp = dma_alloc_coherent(dev,
					  max_buf,
					  &boot_dma_addr, GFP_KERNEL);
		अगर (!bufp) अणु
			dev_err(dev, "Error allocating 0x%zx\n", max_buf);
			ret = -ENOMEM;
			जाओ err_buf_out;
		पूर्ण
	पूर्ण अन्यथा अगर (load_type == VK_IMAGE_TYPE_BOOT2) अणु
		codepush = CODEPUSH_BOOT2_ENTRY;
		offset_codepush = BAR_CODEPUSH_SBI;

		/* Wait क्रम VK to respond */
		ret = bcm_vk_रुको(vk, BAR_0, BAR_BOOT_STATUS, DDR_OPEN,
				  DDR_OPEN, LOAD_IMAGE_TIMEOUT_MS);
		अगर (ret < 0) अणु
			dev_err(dev, "boot2 wait DDR open error - ret(%d)\n",
				ret);
			जाओ err_buf_out;
		पूर्ण

		max_buf = SZ_4M;
		bufp = dma_alloc_coherent(dev,
					  max_buf,
					  &boot_dma_addr, GFP_KERNEL);
		अगर (!bufp) अणु
			dev_err(dev, "Error allocating 0x%zx\n", max_buf);
			ret = -ENOMEM;
			जाओ err_buf_out;
		पूर्ण

		bcm_vk_buf_notअगरy(vk, bufp, boot_dma_addr, max_buf);
	पूर्ण अन्यथा अणु
		dev_err(dev, "Error invalid image type 0x%x\n", load_type);
		ret = -EINVAL;
		जाओ err_buf_out;
	पूर्ण

	offset = 0;
	ret = request_partial_firmware_पूर्णांकo_buf(&fw, filename, dev,
						bufp, max_buf, offset);
	अगर (ret) अणु
		dev_err(dev, "Error %d requesting firmware file: %s\n",
			ret, filename);
		जाओ err_firmware_out;
	पूर्ण
	dev_dbg(dev, "size=0x%zx\n", fw->size);
	अगर (load_type == VK_IMAGE_TYPE_BOOT1)
		स_नकल_toio(vk->bar[BAR_1] + BAR1_CODEPUSH_BASE_BOOT1,
			    bufp,
			    fw->size);

	dev_dbg(dev, "Signaling 0x%x to 0x%llx\n", codepush, offset_codepush);
	vkग_लिखो32(vk, codepush, BAR_0, offset_codepush);

	अगर (load_type == VK_IMAGE_TYPE_BOOT1) अणु
		u32 boot_status;

		/* रुको until करोne */
		ret = bcm_vk_रुको(vk, BAR_0, BAR_BOOT_STATUS,
				  BOOT1_RUNNING,
				  BOOT1_RUNNING,
				  BOOT1_STARTUP_TIMEOUT_MS);

		boot_status = vkपढ़ो32(vk, BAR_0, BAR_BOOT_STATUS);
		is_stdalone = !BCM_VK_INTF_IS_DOWN(boot_status) &&
			      (boot_status & BOOT_STDALONE_RUNNING);
		अगर (ret && !is_stdalone) अणु
			dev_err(dev,
				"Timeout %ld ms waiting for boot1 to come up - ret(%d)\n",
				BOOT1_STARTUP_TIMEOUT_MS, ret);
			जाओ err_firmware_out;
		पूर्ण अन्यथा अगर (is_stdalone) अणु
			u32 reg;

			reg = vkपढ़ो32(vk, BAR_0, BAR_BOOT1_STDALONE_PROGRESS);
			अगर ((reg & BOOT1_STDALONE_PROGRESS_MASK) ==
				     BOOT1_STDALONE_SUCCESS) अणु
				dev_info(dev, "Boot1 standalone success\n");
				ret = 0;
			पूर्ण अन्यथा अणु
				dev_err(dev, "Timeout %ld ms - Boot1 standalone failure\n",
					BOOT1_STARTUP_TIMEOUT_MS);
				ret = -EINVAL;
				जाओ err_firmware_out;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (load_type == VK_IMAGE_TYPE_BOOT2) अणु
		अचिन्हित दीर्घ समयout;

		समयout = jअगरfies + msecs_to_jअगरfies(LOAD_IMAGE_TIMEOUT_MS);

		/* To send more data to VK than max_buf allowed at a समय */
		करो अणु
			/*
			 * Check क्रम ack from card. when Ack is received,
			 * it means all the data is received by card.
			 * Exit the loop after ack is received.
			 */
			ret = bcm_vk_रुको(vk, BAR_0, BAR_BOOT_STATUS,
					  FW_LOADER_ACK_RCVD_ALL_DATA,
					  FW_LOADER_ACK_RCVD_ALL_DATA,
					  TXFR_COMPLETE_TIMEOUT_MS);
			अगर (ret == 0) अणु
				dev_dbg(dev, "Exit boot2 download\n");
				अवरोध;
			पूर्ण अन्यथा अगर (ret == -EFAULT) अणु
				dev_err(dev, "Error detected during ACK waiting");
				जाओ err_firmware_out;
			पूर्ण

			/* निकास the loop, अगर there is no response from card */
			अगर (समय_after(jअगरfies, समयout)) अणु
				dev_err(dev, "Error. No reply from card\n");
				ret = -ETIMEDOUT;
				जाओ err_firmware_out;
			पूर्ण

			/* Wait क्रम VK to खोलो BAR space to copy new data */
			ret = bcm_vk_रुको(vk, BAR_0, offset_codepush,
					  codepush, 0,
					  TXFR_COMPLETE_TIMEOUT_MS);
			अगर (ret == 0) अणु
				offset += max_buf;
				ret = request_partial_firmware_पूर्णांकo_buf
						(&fw,
						 filename,
						 dev, bufp,
						 max_buf,
						 offset);
				अगर (ret) अणु
					dev_err(dev,
						"Error %d requesting firmware file: %s offset: 0x%zx\n",
						ret, filename, offset);
					जाओ err_firmware_out;
				पूर्ण
				dev_dbg(dev, "size=0x%zx\n", fw->size);
				dev_dbg(dev, "Signaling 0x%x to 0x%llx\n",
					codepush, offset_codepush);
				vkग_लिखो32(vk, codepush, BAR_0, offset_codepush);
				/* reload समयout after every codepush */
				समयout = jअगरfies +
				    msecs_to_jअगरfies(LOAD_IMAGE_TIMEOUT_MS);
			पूर्ण अन्यथा अगर (ret == -EFAULT) अणु
				dev_err(dev, "Error detected waiting for transfer\n");
				जाओ err_firmware_out;
			पूर्ण
		पूर्ण जबतक (1);

		/* रुको क्रम fw status bits to indicate app पढ़ोy */
		ret = bcm_vk_रुको(vk, BAR_0, VK_BAR_FWSTS,
				  VK_FWSTS_READY,
				  VK_FWSTS_READY,
				  BOOT2_STARTUP_TIMEOUT_MS);
		अगर (ret < 0) अणु
			dev_err(dev, "Boot2 not ready - ret(%d)\n", ret);
			जाओ err_firmware_out;
		पूर्ण

		is_stdalone = vkपढ़ो32(vk, BAR_0, BAR_BOOT_STATUS) &
			      BOOT_STDALONE_RUNNING;
		अगर (!is_stdalone) अणु
			ret = bcm_vk_पूर्णांकf_ver_chk(vk);
			अगर (ret) अणु
				dev_err(dev, "failure in intf version check\n");
				जाओ err_firmware_out;
			पूर्ण

			/*
			 * Next, initialize Message Q अगर we are loading boot2.
			 * Do a क्रमce sync
			 */
			ret = bcm_vk_sync_msgq(vk, true);
			अगर (ret) अणु
				dev_err(dev, "Boot2 Error reading comm msg Q info\n");
				ret = -EIO;
				जाओ err_firmware_out;
			पूर्ण

			/* sync & channel other info */
			ret = bcm_vk_sync_card_info(vk);
			अगर (ret) अणु
				dev_err(dev, "Syncing Card Info failure\n");
				जाओ err_firmware_out;
			पूर्ण
		पूर्ण
	पूर्ण

err_firmware_out:
	release_firmware(fw);

err_buf_out:
	अगर (bufp)
		dma_मुक्त_coherent(dev, max_buf, bufp, boot_dma_addr);

	वापस ret;
पूर्ण

अटल u32 bcm_vk_next_boot_image(काष्ठा bcm_vk *vk)
अणु
	u32 boot_status;
	u32 fw_status;
	u32 load_type = 0;  /* शेष क्रम unknown */

	boot_status = vkपढ़ो32(vk, BAR_0, BAR_BOOT_STATUS);
	fw_status = vkपढ़ो32(vk, BAR_0, VK_BAR_FWSTS);

	अगर (!BCM_VK_INTF_IS_DOWN(boot_status) && (boot_status & SRAM_OPEN))
		load_type = VK_IMAGE_TYPE_BOOT1;
	अन्यथा अगर (boot_status == BOOT1_RUNNING)
		load_type = VK_IMAGE_TYPE_BOOT2;

	/* Log status so that we know dअगरferent stages */
	dev_info(&vk->pdev->dev,
		 "boot-status value for next image: 0x%x : fw-status 0x%x\n",
		 boot_status, fw_status);

	वापस load_type;
पूर्ण

अटल क्रमागत soc_idx get_soc_idx(काष्ठा bcm_vk *vk)
अणु
	काष्ठा pci_dev *pdev = vk->pdev;
	क्रमागत soc_idx idx = VK_IDX_INVALID;
	u32 rev;
	अटल क्रमागत soc_idx स्थिर vk_soc_tab[] = अणु VALKYRIE_A0, VALKYRIE_B0 पूर्ण;

	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_VALKYRIE:
		/* get the chip id to decide sub-class */
		rev = MAJOR_SOC_REV(vkपढ़ो32(vk, BAR_0, BAR_CHIP_ID));
		अगर (rev < ARRAY_SIZE(vk_soc_tab)) अणु
			idx = vk_soc_tab[rev];
		पूर्ण अन्यथा अणु
			/* Default to A0 firmware क्रम all other chip revs */
			idx = VALKYRIE_A0;
			dev_warn(&pdev->dev,
				 "Rev %d not in image lookup table, default to idx=%d\n",
				 rev, idx);
		पूर्ण
		अवरोध;

	हाल PCI_DEVICE_ID_VIPER:
		idx = VIPER;
		अवरोध;

	शेष:
		dev_err(&pdev->dev, "no images for 0x%x\n", pdev->device);
	पूर्ण
	वापस idx;
पूर्ण

अटल स्थिर अक्षर *get_load_fw_name(काष्ठा bcm_vk *vk,
				    स्थिर काष्ठा load_image_entry *entry)
अणु
	स्थिर काष्ठा firmware *fw;
	काष्ठा device *dev = &vk->pdev->dev;
	पूर्णांक ret;
	अचिन्हित दीर्घ dummy;
	पूर्णांक i;

	क्रम (i = 0; i < IMG_PER_TYPE_MAX; i++) अणु
		fw = शून्य;
		ret = request_partial_firmware_पूर्णांकo_buf(&fw,
							entry->image_name[i],
							dev, &dummy,
							माप(dummy),
							0);
		release_firmware(fw);
		अगर (!ret)
			वापस entry->image_name[i];
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक bcm_vk_स्वतः_load_all_images(काष्ठा bcm_vk *vk)
अणु
	पूर्णांक i, ret = -1;
	क्रमागत soc_idx idx;
	काष्ठा device *dev = &vk->pdev->dev;
	u32 curr_type;
	स्थिर अक्षर *curr_name;

	idx = get_soc_idx(vk);
	अगर (idx == VK_IDX_INVALID)
		जाओ स्वतः_load_all_निकास;

	/* log a message to know the relative loading order */
	dev_dbg(dev, "Load All for device %d\n", vk->devid);

	क्रम (i = 0; i < NUM_BOOT_STAGES; i++) अणु
		curr_type = image_tab[idx][i].image_type;
		अगर (bcm_vk_next_boot_image(vk) == curr_type) अणु
			curr_name = get_load_fw_name(vk, &image_tab[idx][i]);
			अगर (!curr_name) अणु
				dev_err(dev, "No suitable firmware exists for type %d",
					curr_type);
				ret = -ENOENT;
				जाओ स्वतः_load_all_निकास;
			पूर्ण
			ret = bcm_vk_load_image_by_type(vk, curr_type,
							curr_name);
			dev_info(dev, "Auto load %s, ret %d\n",
				 curr_name, ret);

			अगर (ret) अणु
				dev_err(dev, "Error loading default %s\n",
					curr_name);
				जाओ स्वतः_load_all_निकास;
			पूर्ण
		पूर्ण
	पूर्ण

स्वतः_load_all_निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक bcm_vk_trigger_स्वतःload(काष्ठा bcm_vk *vk)
अणु
	अगर (test_and_set_bit(BCM_VK_WQ_DWNLD_PEND, vk->wq_offload) != 0)
		वापस -EPERM;

	set_bit(BCM_VK_WQ_DWNLD_AUTO, vk->wq_offload);
	queue_work(vk->wq_thपढ़ो, &vk->wq_work);

	वापस 0;
पूर्ण

/*
 * deferred work queue क्रम draining and स्वतः करोwnload.
 */
अटल व्योम bcm_vk_wq_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bcm_vk *vk = container_of(work, काष्ठा bcm_vk, wq_work);
	काष्ठा device *dev = &vk->pdev->dev;
	s32 ret;

	/* check wq offload bit map to perक्रमm various operations */
	अगर (test_bit(BCM_VK_WQ_NOTF_PEND, vk->wq_offload)) अणु
		/* clear bit right the way क्रम notअगरication */
		clear_bit(BCM_VK_WQ_NOTF_PEND, vk->wq_offload);
		bcm_vk_handle_notf(vk);
	पूर्ण
	अगर (test_bit(BCM_VK_WQ_DWNLD_AUTO, vk->wq_offload)) अणु
		bcm_vk_स्वतः_load_all_images(vk);

		/*
		 * at the end of operation, clear AUTO bit and pending
		 * bit
		 */
		clear_bit(BCM_VK_WQ_DWNLD_AUTO, vk->wq_offload);
		clear_bit(BCM_VK_WQ_DWNLD_PEND, vk->wq_offload);
	पूर्ण

	/* next, try to drain */
	ret = bcm_to_h_msg_dequeue(vk);

	अगर (ret == 0)
		dev_dbg(dev, "Spurious trigger for workqueue\n");
	अन्यथा अगर (ret < 0)
		bcm_vk_blk_drv_access(vk);
पूर्ण

अटल दीर्घ bcm_vk_load_image(काष्ठा bcm_vk *vk,
			      स्थिर काष्ठा vk_image __user *arg)
अणु
	काष्ठा device *dev = &vk->pdev->dev;
	स्थिर अक्षर *image_name;
	काष्ठा vk_image image;
	u32 next_loadable;
	क्रमागत soc_idx idx;
	पूर्णांक image_idx;
	पूर्णांक ret = -EPERM;

	अगर (copy_from_user(&image, arg, माप(image)))
		वापस -EACCES;

	अगर ((image.type != VK_IMAGE_TYPE_BOOT1) &&
	    (image.type != VK_IMAGE_TYPE_BOOT2)) अणु
		dev_err(dev, "invalid image.type %u\n", image.type);
		वापस ret;
	पूर्ण

	next_loadable = bcm_vk_next_boot_image(vk);
	अगर (next_loadable != image.type) अणु
		dev_err(dev, "Next expected image %u, Loading %u\n",
			next_loadable, image.type);
		वापस ret;
	पूर्ण

	/*
	 * अगर something is pending करोwnload alपढ़ोy.  This could only happen
	 * क्रम now when the driver is being loaded, or अगर someone has issued
	 * another करोwnload command in another shell.
	 */
	अगर (test_and_set_bit(BCM_VK_WQ_DWNLD_PEND, vk->wq_offload) != 0) अणु
		dev_err(dev, "Download operation already pending.\n");
		वापस ret;
	पूर्ण

	image_name = image.filename;
	अगर (image_name[0] == '\0') अणु
		/* Use शेष image name अगर शून्य */
		idx = get_soc_idx(vk);
		अगर (idx == VK_IDX_INVALID)
			जाओ err_idx;

		/* Image idx starts with boot1 */
		image_idx = image.type - VK_IMAGE_TYPE_BOOT1;
		image_name = get_load_fw_name(vk, &image_tab[idx][image_idx]);
		अगर (!image_name) अणु
			dev_err(dev, "No suitable image found for type %d",
				image.type);
			ret = -ENOENT;
			जाओ err_idx;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Ensure filename is शून्य terminated */
		image.filename[माप(image.filename) - 1] = '\0';
	पूर्ण
	ret = bcm_vk_load_image_by_type(vk, image.type, image_name);
	dev_info(dev, "Load %s, ret %d\n", image_name, ret);
err_idx:
	clear_bit(BCM_VK_WQ_DWNLD_PEND, vk->wq_offload);

	वापस ret;
पूर्ण

अटल पूर्णांक bcm_vk_reset_successful(काष्ठा bcm_vk *vk)
अणु
	काष्ठा device *dev = &vk->pdev->dev;
	u32 fw_status, reset_reason;
	पूर्णांक ret = -EAGAIN;

	/*
	 * Reset could be triggered when the card in several state:
	 *   i)   in bootROM
	 *   ii)  after boot1
	 *   iii) boot2 running
	 *
	 * i) & ii) - no status bits will be updated.  If vkboot1
	 * runs स्वतःmatically after reset, it  will update the reason
	 * to be unknown reason
	 * iii) - reboot reason match + deinit करोne.
	 */
	fw_status = vkपढ़ो32(vk, BAR_0, VK_BAR_FWSTS);
	/* immediate निकास अगर पूर्णांकerface goes करोwn */
	अगर (BCM_VK_INTF_IS_DOWN(fw_status)) अणु
		dev_err(dev, "PCIe Intf Down!\n");
		जाओ reset_निकास;
	पूर्ण

	reset_reason = (fw_status & VK_FWSTS_RESET_REASON_MASK);
	अगर ((reset_reason == VK_FWSTS_RESET_MBOX_DB) ||
	    (reset_reason == VK_FWSTS_RESET_UNKNOWN))
		ret = 0;

	/*
	 * अगर some of the deinit bits are set, but करोne
	 * bit is not, this is a failure अगर triggered जबतक boot2 is running
	 */
	अगर ((fw_status & VK_FWSTS_DEINIT_TRIGGERED) &&
	    !(fw_status & VK_FWSTS_RESET_DONE))
		ret = -EAGAIN;

reset_निकास:
	dev_dbg(dev, "FW status = 0x%x ret %d\n", fw_status, ret);

	वापस ret;
पूर्ण

अटल व्योम bcm_to_v_reset_करोorbell(काष्ठा bcm_vk *vk, u32 db_val)
अणु
	vkग_लिखो32(vk, db_val, BAR_0, VK_BAR0_RESET_DB_BASE);
पूर्ण

अटल पूर्णांक bcm_vk_trigger_reset(काष्ठा bcm_vk *vk)
अणु
	u32 i;
	u32 value, boot_status;
	bool is_stdalone, is_boot2;
	अटल स्थिर u32 bar0_reg_clr_list[] = अणु BAR_OS_UPTIME,
						 BAR_INTF_VER,
						 BAR_CARD_VOLTAGE,
						 BAR_CARD_TEMPERATURE,
						 BAR_CARD_PWR_AND_THRE पूर्ण;

	/* clean up beक्रमe pressing the करोor bell */
	bcm_vk_drain_msg_on_reset(vk);
	vkग_लिखो32(vk, 0, BAR_1, VK_BAR1_MSGQ_DEF_RDY);
	/* make tag '\0' terminated */
	vkग_लिखो32(vk, 0, BAR_1, VK_BAR1_BOOT1_VER_TAG);

	क्रम (i = 0; i < VK_BAR1_DAUTH_MAX; i++) अणु
		vkग_लिखो32(vk, 0, BAR_1, VK_BAR1_DAUTH_STORE_ADDR(i));
		vkग_लिखो32(vk, 0, BAR_1, VK_BAR1_DAUTH_VALID_ADDR(i));
	पूर्ण
	क्रम (i = 0; i < VK_BAR1_SOTP_REVID_MAX; i++)
		vkग_लिखो32(vk, 0, BAR_1, VK_BAR1_SOTP_REVID_ADDR(i));

	स_रखो(&vk->card_info, 0, माप(vk->card_info));
	स_रखो(&vk->peerlog_info, 0, माप(vk->peerlog_info));
	स_रखो(&vk->proc_mon_info, 0, माप(vk->proc_mon_info));
	स_रखो(&vk->alert_cnts, 0, माप(vk->alert_cnts));

	/*
	 * When boot request fails, the CODE_PUSH_OFFSET stays persistent.
	 * Allowing us to debug the failure. When we call reset,
	 * we should clear CODE_PUSH_OFFSET so ROM करोes not execute
	 * boot again (and fails again) and instead रुकोs क्रम a new
	 * codepush.  And, अगर previous boot has encountered error, need
	 * to clear the entry values
	 */
	boot_status = vkपढ़ो32(vk, BAR_0, BAR_BOOT_STATUS);
	अगर (boot_status & BOOT_ERR_MASK) अणु
		dev_info(&vk->pdev->dev,
			 "Card in boot error 0x%x, clear CODEPUSH val\n",
			 boot_status);
		value = 0;
	पूर्ण अन्यथा अणु
		value = vkपढ़ो32(vk, BAR_0, BAR_CODEPUSH_SBL);
		value &= CODEPUSH_MASK;
	पूर्ण
	vkग_लिखो32(vk, value, BAR_0, BAR_CODEPUSH_SBL);

	/* special reset handling */
	is_stdalone = boot_status & BOOT_STDALONE_RUNNING;
	is_boot2 = (boot_status & BOOT_STATE_MASK) == BOOT2_RUNNING;
	अगर (vk->peer_alert.flags & ERR_LOG_RAMDUMP) अणु
		/*
		 * अगर card is in ramdump mode, it is hitting an error.  Don't
		 * reset the reboot reason as it will contain valid info that
		 * is important - simply use special reset
		 */
		vkग_लिखो32(vk, VK_BAR0_RESET_RAMPDUMP, BAR_0, VK_BAR_FWSTS);
		वापस VK_BAR0_RESET_RAMPDUMP;
	पूर्ण अन्यथा अगर (is_stdalone && !is_boot2) अणु
		dev_info(&vk->pdev->dev, "Hard reset on Standalone mode");
		bcm_to_v_reset_करोorbell(vk, VK_BAR0_RESET_DB_HARD);
		वापस VK_BAR0_RESET_DB_HARD;
	पूर्ण

	/* reset fw_status with proper reason, and press db */
	vkग_लिखो32(vk, VK_FWSTS_RESET_MBOX_DB, BAR_0, VK_BAR_FWSTS);
	bcm_to_v_reset_करोorbell(vk, VK_BAR0_RESET_DB_SOFT);

	/* clear other necessary रेजिस्टरs and alert records */
	क्रम (i = 0; i < ARRAY_SIZE(bar0_reg_clr_list); i++)
		vkग_लिखो32(vk, 0, BAR_0, bar0_reg_clr_list[i]);
	स_रखो(&vk->host_alert, 0, माप(vk->host_alert));
	स_रखो(&vk->peer_alert, 0, माप(vk->peer_alert));
	/* clear 4096 bits of biपंचांगap */
	biपंचांगap_clear(vk->bmap, 0, VK_MSG_ID_BITMAP_SIZE);

	वापस 0;
पूर्ण

अटल दीर्घ bcm_vk_reset(काष्ठा bcm_vk *vk, काष्ठा vk_reset __user *arg)
अणु
	काष्ठा device *dev = &vk->pdev->dev;
	काष्ठा vk_reset reset;
	पूर्णांक ret = 0;
	u32 ramdump_reset;
	पूर्णांक special_reset;

	अगर (copy_from_user(&reset, arg, माप(काष्ठा vk_reset)))
		वापस -EFAULT;

	/* check अगर any करोwnload is in-progress, अगर so वापस error */
	अगर (test_and_set_bit(BCM_VK_WQ_DWNLD_PEND, vk->wq_offload) != 0) अणु
		dev_err(dev, "Download operation pending - skip reset.\n");
		वापस -EPERM;
	पूर्ण

	ramdump_reset = vk->peer_alert.flags & ERR_LOG_RAMDUMP;
	dev_info(dev, "Issue Reset %s\n",
		 ramdump_reset ? "in ramdump mode" : "");

	/*
	 * The following is the sequence of reset:
	 * - send card level graceful shut करोwn
	 * - रुको enough समय क्रम VK to handle its business, stopping DMA etc
	 * - समाप्त host apps
	 * - Trigger पूर्णांकerrupt with DB
	 */
	bcm_vk_send_shutकरोwn_msg(vk, VK_SHUTDOWN_GRACEFUL, 0, 0);

	spin_lock(&vk->ctx_lock);
	अगर (!vk->reset_pid) अणु
		vk->reset_pid = task_pid_nr(current);
	पूर्ण अन्यथा अणु
		dev_err(dev, "Reset already launched by process pid %d\n",
			vk->reset_pid);
		ret = -EACCES;
	पूर्ण
	spin_unlock(&vk->ctx_lock);
	अगर (ret)
		जाओ err_निकास;

	bcm_vk_blk_drv_access(vk);
	special_reset = bcm_vk_trigger_reset(vk);

	/*
	 * Wait enough समय क्रम card os to deinit
	 * and populate the reset reason.
	 */
	msleep(BCM_VK_DEINIT_TIME_MS);

	अगर (special_reset) अणु
		/* अगर it is special ramdump reset, वापस the type to user */
		reset.arg2 = special_reset;
		अगर (copy_to_user(arg, &reset, माप(reset)))
			ret = -EFAULT;
	पूर्ण अन्यथा अणु
		ret = bcm_vk_reset_successful(vk);
	पूर्ण

err_निकास:
	clear_bit(BCM_VK_WQ_DWNLD_PEND, vk->wq_offload);
	वापस ret;
पूर्ण

अटल पूर्णांक bcm_vk_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा bcm_vk_ctx *ctx = file->निजी_data;
	काष्ठा bcm_vk *vk = container_of(ctx->miscdev, काष्ठा bcm_vk, miscdev);
	अचिन्हित दीर्घ pg_size;

	/* only BAR2 is mmap possible, which is bar num 4 due to 64bit */
#घोषणा VK_MMAPABLE_BAR 4

	pg_size = ((pci_resource_len(vk->pdev, VK_MMAPABLE_BAR) - 1)
		    >> PAGE_SHIFT) + 1;
	अगर (vma->vm_pgoff + vma_pages(vma) > pg_size)
		वापस -EINVAL;

	vma->vm_pgoff += (pci_resource_start(vk->pdev, VK_MMAPABLE_BAR)
			  >> PAGE_SHIFT);
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	वापस io_remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
				  vma->vm_end - vma->vm_start,
				  vma->vm_page_prot);
पूर्ण

अटल दीर्घ bcm_vk_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	दीर्घ ret = -EINVAL;
	काष्ठा bcm_vk_ctx *ctx = file->निजी_data;
	काष्ठा bcm_vk *vk = container_of(ctx->miscdev, काष्ठा bcm_vk, miscdev);
	व्योम __user *argp = (व्योम __user *)arg;

	dev_dbg(&vk->pdev->dev,
		"ioctl, cmd=0x%02x, arg=0x%02lx\n",
		cmd, arg);

	mutex_lock(&vk->mutex);

	चयन (cmd) अणु
	हाल VK_IOCTL_LOAD_IMAGE:
		ret = bcm_vk_load_image(vk, argp);
		अवरोध;

	हाल VK_IOCTL_RESET:
		ret = bcm_vk_reset(vk, argp);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	mutex_unlock(&vk->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations bcm_vk_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = bcm_vk_खोलो,
	.पढ़ो = bcm_vk_पढ़ो,
	.ग_लिखो = bcm_vk_ग_लिखो,
	.poll = bcm_vk_poll,
	.release = bcm_vk_release,
	.mmap = bcm_vk_mmap,
	.unlocked_ioctl = bcm_vk_ioctl,
पूर्ण;

अटल पूर्णांक bcm_vk_on_panic(काष्ठा notअगरier_block *nb,
			   अचिन्हित दीर्घ e, व्योम *p)
अणु
	काष्ठा bcm_vk *vk = container_of(nb, काष्ठा bcm_vk, panic_nb);

	bcm_to_v_reset_करोorbell(vk, VK_BAR0_RESET_DB_HARD);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_vk_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक err;
	पूर्णांक i;
	पूर्णांक id;
	पूर्णांक irq;
	अक्षर name[20];
	काष्ठा bcm_vk *vk;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा miscdevice *misc_device;
	u32 boot_status;

	/* allocate vk काष्ठाure which is tied to kref क्रम मुक्तing */
	vk = kzalloc(माप(*vk), GFP_KERNEL);
	अगर (!vk)
		वापस -ENOMEM;

	kref_init(&vk->kref);
	अगर (nr_ib_sgl_blk > BCM_VK_IB_SGL_BLK_MAX) अणु
		dev_warn(dev, "Inband SGL blk %d limited to max %d\n",
			 nr_ib_sgl_blk, BCM_VK_IB_SGL_BLK_MAX);
		nr_ib_sgl_blk = BCM_VK_IB_SGL_BLK_MAX;
	पूर्ण
	vk->ib_sgl_size = nr_ib_sgl_blk * VK_MSGQ_BLK_SIZE;
	mutex_init(&vk->mutex);

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(dev, "Cannot enable PCI device\n");
		जाओ err_मुक्त_निकास;
	पूर्ण
	vk->pdev = pci_dev_get(pdev);

	err = pci_request_regions(pdev, DRV_MODULE_NAME);
	अगर (err) अणु
		dev_err(dev, "Cannot obtain PCI resources\n");
		जाओ err_disable_pdev;
	पूर्ण

	/* make sure DMA is good */
	err = dma_set_mask_and_coherent(&pdev->dev,
					DMA_BIT_MASK(BCM_VK_DMA_BITS));
	अगर (err) अणु
		dev_err(dev, "failed to set DMA mask\n");
		जाओ err_disable_pdev;
	पूर्ण

	/* The tdma is a scratch area क्रम some DMA testings. */
	अगर (nr_scratch_pages) अणु
		vk->tdma_vaddr = dma_alloc_coherent
					(dev,
					 nr_scratch_pages * PAGE_SIZE,
					 &vk->tdma_addr, GFP_KERNEL);
		अगर (!vk->tdma_vaddr) अणु
			err = -ENOMEM;
			जाओ err_disable_pdev;
		पूर्ण
	पूर्ण

	pci_set_master(pdev);
	pci_set_drvdata(pdev, vk);

	irq = pci_alloc_irq_vectors(pdev,
				    1,
				    VK_MSIX_IRQ_MAX,
				    PCI_IRQ_MSI | PCI_IRQ_MSIX);

	अगर (irq < VK_MSIX_IRQ_MIN_REQ) अणु
		dev_err(dev, "failed to get min %d MSIX interrupts, irq(%d)\n",
			VK_MSIX_IRQ_MIN_REQ, irq);
		err = (irq >= 0) ? -EINVAL : irq;
		जाओ err_disable_pdev;
	पूर्ण

	अगर (irq != VK_MSIX_IRQ_MAX)
		dev_warn(dev, "Number of IRQs %d allocated - requested(%d).\n",
			 irq, VK_MSIX_IRQ_MAX);

	क्रम (i = 0; i < MAX_BAR; i++) अणु
		/* multiple by 2 क्रम 64 bit BAR mapping */
		vk->bar[i] = pci_ioremap_bar(pdev, i * 2);
		अगर (!vk->bar[i]) अणु
			dev_err(dev, "failed to remap BAR%d\n", i);
			err = -ENOMEM;
			जाओ err_iounmap;
		पूर्ण
	पूर्ण

	क्रम (vk->num_irqs = 0;
	     vk->num_irqs < VK_MSIX_MSGQ_MAX;
	     vk->num_irqs++) अणु
		err = devm_request_irq(dev, pci_irq_vector(pdev, vk->num_irqs),
				       bcm_vk_msgq_irqhandler,
				       IRQF_SHARED, DRV_MODULE_NAME, vk);
		अगर (err) अणु
			dev_err(dev, "failed to request msgq IRQ %d for MSIX %d\n",
				pdev->irq + vk->num_irqs, vk->num_irqs + 1);
			जाओ err_irq;
		पूर्ण
	पूर्ण
	/* one irq क्रम notअगरication from VK */
	err = devm_request_irq(dev, pci_irq_vector(pdev, vk->num_irqs),
			       bcm_vk_notf_irqhandler,
			       IRQF_SHARED, DRV_MODULE_NAME, vk);
	अगर (err) अणु
		dev_err(dev, "failed to request notf IRQ %d for MSIX %d\n",
			pdev->irq + vk->num_irqs, vk->num_irqs + 1);
		जाओ err_irq;
	पूर्ण
	vk->num_irqs++;

	क्रम (i = 0;
	     (i < VK_MSIX_TTY_MAX) && (vk->num_irqs < irq);
	     i++, vk->num_irqs++) अणु
		err = devm_request_irq(dev, pci_irq_vector(pdev, vk->num_irqs),
				       bcm_vk_tty_irqhandler,
				       IRQF_SHARED, DRV_MODULE_NAME, vk);
		अगर (err) अणु
			dev_err(dev, "failed request tty IRQ %d for MSIX %d\n",
				pdev->irq + vk->num_irqs, vk->num_irqs + 1);
			जाओ err_irq;
		पूर्ण
		bcm_vk_tty_set_irq_enabled(vk, i);
	पूर्ण

	id = ida_simple_get(&bcm_vk_ida, 0, 0, GFP_KERNEL);
	अगर (id < 0) अणु
		err = id;
		dev_err(dev, "unable to get id\n");
		जाओ err_irq;
	पूर्ण

	vk->devid = id;
	snम_लिखो(name, माप(name), DRV_MODULE_NAME ".%d", id);
	misc_device = &vk->miscdev;
	misc_device->minor = MISC_DYNAMIC_MINOR;
	misc_device->name = kstrdup(name, GFP_KERNEL);
	अगर (!misc_device->name) अणु
		err = -ENOMEM;
		जाओ err_ida_हटाओ;
	पूर्ण
	misc_device->fops = &bcm_vk_fops,

	err = misc_रेजिस्टर(misc_device);
	अगर (err) अणु
		dev_err(dev, "failed to register device\n");
		जाओ err_kमुक्त_name;
	पूर्ण

	INIT_WORK(&vk->wq_work, bcm_vk_wq_handler);

	/* create dedicated workqueue */
	vk->wq_thपढ़ो = create_singlethपढ़ो_workqueue(name);
	अगर (!vk->wq_thपढ़ो) अणु
		dev_err(dev, "Fail to create workqueue thread\n");
		err = -ENOMEM;
		जाओ err_misc_deरेजिस्टर;
	पूर्ण

	err = bcm_vk_msg_init(vk);
	अगर (err) अणु
		dev_err(dev, "failed to init msg queue info\n");
		जाओ err_destroy_workqueue;
	पूर्ण

	/* sync other info */
	bcm_vk_sync_card_info(vk);

	/* रेजिस्टर क्रम panic notअगरier */
	vk->panic_nb.notअगरier_call = bcm_vk_on_panic;
	err = atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
					     &vk->panic_nb);
	अगर (err) अणु
		dev_err(dev, "Fail to register panic notifier\n");
		जाओ err_destroy_workqueue;
	पूर्ण

	snम_लिखो(name, माप(name), KBUILD_MODNAME ".%d_ttyVK", id);
	err = bcm_vk_tty_init(vk, name);
	अगर (err)
		जाओ err_unरेजिस्टर_panic_notअगरier;

	/*
	 * lets trigger an स्वतः करोwnload.  We करोn't want to करो it serially here
	 * because at probing समय, it is not supposed to block क्रम a दीर्घ समय.
	 */
	boot_status = vkपढ़ो32(vk, BAR_0, BAR_BOOT_STATUS);
	अगर (स्वतः_load) अणु
		अगर ((boot_status & BOOT_STATE_MASK) == BROM_RUNNING) अणु
			err = bcm_vk_trigger_स्वतःload(vk);
			अगर (err)
				जाओ err_bcm_vk_tty_निकास;
		पूर्ण अन्यथा अणु
			dev_err(dev,
				"Auto-load skipped - BROM not in proper state (0x%x)\n",
				boot_status);
		पूर्ण
	पूर्ण

	/* enable hb */
	bcm_vk_hb_init(vk);

	dev_dbg(dev, "BCM-VK:%u created\n", id);

	वापस 0;

err_bcm_vk_tty_निकास:
	bcm_vk_tty_निकास(vk);

err_unरेजिस्टर_panic_notअगरier:
	atomic_notअगरier_chain_unरेजिस्टर(&panic_notअगरier_list,
					 &vk->panic_nb);

err_destroy_workqueue:
	destroy_workqueue(vk->wq_thपढ़ो);

err_misc_deरेजिस्टर:
	misc_deरेजिस्टर(misc_device);

err_kमुक्त_name:
	kमुक्त(misc_device->name);
	misc_device->name = शून्य;

err_ida_हटाओ:
	ida_simple_हटाओ(&bcm_vk_ida, id);

err_irq:
	क्रम (i = 0; i < vk->num_irqs; i++)
		devm_मुक्त_irq(dev, pci_irq_vector(pdev, i), vk);

	pci_disable_msix(pdev);
	pci_disable_msi(pdev);

err_iounmap:
	क्रम (i = 0; i < MAX_BAR; i++) अणु
		अगर (vk->bar[i])
			pci_iounmap(pdev, vk->bar[i]);
	पूर्ण
	pci_release_regions(pdev);

err_disable_pdev:
	अगर (vk->tdma_vaddr)
		dma_मुक्त_coherent(&pdev->dev, nr_scratch_pages * PAGE_SIZE,
				  vk->tdma_vaddr, vk->tdma_addr);

	pci_मुक्त_irq_vectors(pdev);
	pci_disable_device(pdev);
	pci_dev_put(pdev);

err_मुक्त_निकास:
	kमुक्त(vk);

	वापस err;
पूर्ण

व्योम bcm_vk_release_data(काष्ठा kref *kref)
अणु
	काष्ठा bcm_vk *vk = container_of(kref, काष्ठा bcm_vk, kref);
	काष्ठा pci_dev *pdev = vk->pdev;

	dev_dbg(&pdev->dev, "BCM-VK:%d release data 0x%p\n", vk->devid, vk);
	pci_dev_put(pdev);
	kमुक्त(vk);
पूर्ण

अटल व्योम bcm_vk_हटाओ(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;
	काष्ठा bcm_vk *vk = pci_get_drvdata(pdev);
	काष्ठा miscdevice *misc_device = &vk->miscdev;

	bcm_vk_hb_deinit(vk);

	/*
	 * Trigger a reset to card and रुको enough समय क्रम UCODE to rerun,
	 * which re-initialize the card पूर्णांकo its शेष state.
	 * This ensures when driver is re-क्रमागतerated it will start from
	 * a completely clean state.
	 */
	bcm_vk_trigger_reset(vk);
	usleep_range(BCM_VK_UCODE_BOOT_US, BCM_VK_UCODE_BOOT_MAX_US);

	/* unरेजिस्टर panic notअगरier */
	atomic_notअगरier_chain_unरेजिस्टर(&panic_notअगरier_list,
					 &vk->panic_nb);

	bcm_vk_msg_हटाओ(vk);
	bcm_vk_tty_निकास(vk);

	अगर (vk->tdma_vaddr)
		dma_मुक्त_coherent(&pdev->dev, nr_scratch_pages * PAGE_SIZE,
				  vk->tdma_vaddr, vk->tdma_addr);

	/* हटाओ अगर name is set which means misc dev रेजिस्टरed */
	अगर (misc_device->name) अणु
		misc_deरेजिस्टर(misc_device);
		kमुक्त(misc_device->name);
		ida_simple_हटाओ(&bcm_vk_ida, vk->devid);
	पूर्ण
	क्रम (i = 0; i < vk->num_irqs; i++)
		devm_मुक्त_irq(&pdev->dev, pci_irq_vector(pdev, i), vk);

	pci_disable_msix(pdev);
	pci_disable_msi(pdev);

	cancel_work_sync(&vk->wq_work);
	destroy_workqueue(vk->wq_thपढ़ो);
	bcm_vk_tty_wq_निकास(vk);

	क्रम (i = 0; i < MAX_BAR; i++) अणु
		अगर (vk->bar[i])
			pci_iounmap(pdev, vk->bar[i]);
	पूर्ण

	dev_dbg(&pdev->dev, "BCM-VK:%d released\n", vk->devid);

	pci_release_regions(pdev);
	pci_मुक्त_irq_vectors(pdev);
	pci_disable_device(pdev);

	kref_put(&vk->kref, bcm_vk_release_data);
पूर्ण

अटल व्योम bcm_vk_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा bcm_vk *vk = pci_get_drvdata(pdev);
	u32 reg, boot_stat;

	reg = vkपढ़ो32(vk, BAR_0, BAR_BOOT_STATUS);
	boot_stat = reg & BOOT_STATE_MASK;

	अगर (boot_stat == BOOT1_RUNNING) अणु
		/* simply trigger a reset पूर्णांकerrupt to park it */
		bcm_vk_trigger_reset(vk);
	पूर्ण अन्यथा अगर (boot_stat == BROM_NOT_RUN) अणु
		पूर्णांक err;
		u16 lnksta;

		/*
		 * The boot status only reflects boot condition since last reset
		 * As ucode will run only once to configure pcie, अगर multiple
		 * resets happen, we lost track अगर ucode has run or not.
		 * Here, पढ़ो the current link speed and use that to
		 * sync up the bootstatus properly so that on reboot-back-up,
		 * it has the proper state to start with स्वतःload
		 */
		err = pcie_capability_पढ़ो_word(pdev, PCI_EXP_LNKSTA, &lnksta);
		अगर (!err &&
		    (lnksta & PCI_EXP_LNKSTA_CLS) != PCI_EXP_LNKSTA_CLS_2_5GB) अणु
			reg |= BROM_STATUS_COMPLETE;
			vkग_लिखो32(vk, reg, BAR_0, BAR_BOOT_STATUS);
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pci_device_id bcm_vk_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_VALKYRIE), पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_VIPER), पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, bcm_vk_ids);

अटल काष्ठा pci_driver pci_driver = अणु
	.name     = DRV_MODULE_NAME,
	.id_table = bcm_vk_ids,
	.probe    = bcm_vk_probe,
	.हटाओ   = bcm_vk_हटाओ,
	.shutकरोwn = bcm_vk_shutकरोwn,
पूर्ण;
module_pci_driver(pci_driver);

MODULE_DESCRIPTION("Broadcom VK Host Driver");
MODULE_AUTHOR("Scott Branden <scott.branden@broadcom.com>");
MODULE_LICENSE("GPL v2");
MODULE_VERSION("1.0");
