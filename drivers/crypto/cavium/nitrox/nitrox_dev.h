<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NITROX_DEV_H
#घोषणा __NITROX_DEV_H

#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/अगर.h>

#घोषणा VERSION_LEN 32
/* Maximum queues in PF mode */
#घोषणा MAX_PF_QUEUES	64
/* Maximum device queues */
#घोषणा MAX_DEV_QUEUES (MAX_PF_QUEUES)
/* Maximum UCD Blocks */
#घोषणा CNN55XX_MAX_UCD_BLOCKS	8

/**
 * काष्ठा nitrox_cmdq - NITROX command queue
 * @cmd_qlock: command queue lock
 * @resp_qlock: response queue lock
 * @backlog_qlock: backlog queue lock
 * @ndev: NITROX device
 * @response_head: submitted request list
 * @backlog_head: backlog queue
 * @dbell_csr_addr: करोorbell रेजिस्टर address क्रम this queue
 * @compl_cnt_csr_addr: completion count रेजिस्टर address of the slc port
 * @base: command queue base address
 * @dma: dma address of the base
 * @pending_count: request pending at device
 * @backlog_count: backlog request count
 * @ग_लिखो_idx: next ग_लिखो index क्रम the command
 * @instr_size: command size
 * @qno: command queue number
 * @qsize: command queue size
 * @unalign_base: unaligned base address
 * @unalign_dma: unaligned dma address
 */
काष्ठा nitrox_cmdq अणु
	spinlock_t cmd_qlock;
	spinlock_t resp_qlock;
	spinlock_t backlog_qlock;

	काष्ठा nitrox_device *ndev;
	काष्ठा list_head response_head;
	काष्ठा list_head backlog_head;

	u8 __iomem *dbell_csr_addr;
	u8 __iomem *compl_cnt_csr_addr;
	u8 *base;
	dma_addr_t dma;

	काष्ठा work_काष्ठा backlog_qflush;

	atomic_t pending_count;
	atomic_t backlog_count;

	पूर्णांक ग_लिखो_idx;
	u8 instr_size;
	u8 qno;
	u32 qsize;

	u8 *unalign_base;
	dma_addr_t unalign_dma;
पूर्ण;

/**
 * काष्ठा nitrox_hw - NITROX hardware inक्रमmation
 * @partname: partname ex: CNN55xxx-xxx
 * @fw_name: firmware version
 * @freq: NITROX frequency
 * @venकरोr_id: venकरोr ID
 * @device_id: device ID
 * @revision_id: revision ID
 * @se_cores: number of symmetric cores
 * @ae_cores: number of asymmetric cores
 * @zip_cores: number of zip cores
 */
काष्ठा nitrox_hw अणु
	अक्षर partname[IFNAMSIZ * 2];
	अक्षर fw_name[CNN55XX_MAX_UCD_BLOCKS][VERSION_LEN];

	पूर्णांक freq;
	u16 venकरोr_id;
	u16 device_id;
	u8 revision_id;

	u8 se_cores;
	u8 ae_cores;
	u8 zip_cores;
पूर्ण;

काष्ठा nitrox_stats अणु
	atomic64_t posted;
	atomic64_t completed;
	atomic64_t dropped;
पूर्ण;

#घोषणा IRQ_NAMESZ	32

काष्ठा nitrox_q_vector अणु
	अक्षर name[IRQ_NAMESZ];
	bool valid;
	पूर्णांक ring;
	काष्ठा tasklet_काष्ठा resp_tasklet;
	जोड़ अणु
		काष्ठा nitrox_cmdq *cmdq;
		काष्ठा nitrox_device *ndev;
	पूर्ण;
पूर्ण;

क्रमागत mcode_type अणु
	MCODE_TYPE_INVALID,
	MCODE_TYPE_AE,
	MCODE_TYPE_SE_SSL,
	MCODE_TYPE_SE_IPSEC,
पूर्ण;

/**
 * mbox_msg - Mailbox message data
 * @type: message type
 * @opcode: message opcode
 * @data: message data
 */
जोड़ mbox_msg अणु
	u64 value;
	काष्ठा अणु
		u64 type: 2;
		u64 opcode: 6;
		u64 data: 58;
	पूर्ण;
	काष्ठा अणु
		u64 type: 2;
		u64 opcode: 6;
		u64 chipid: 8;
		u64 vfid: 8;
	पूर्ण id;
	काष्ठा अणु
		u64 type: 2;
		u64 opcode: 6;
		u64 count: 4;
		u64 info: 40;
		u64 next_se_grp: 3;
		u64 next_ae_grp: 3;
	पूर्ण mcode_info;
पूर्ण;

/**
 * nitrox_vfdev - NITROX VF device instance in PF
 * @state: VF device state
 * @vfno: VF number
 * @nr_queues: number of queues enabled in VF
 * @ring: ring to communicate with VF
 * @msg: Mailbox message data from VF
 * @mbx_resp: Mailbox counters
 */
काष्ठा nitrox_vfdev अणु
	atomic_t state;
	पूर्णांक vfno;
	पूर्णांक nr_queues;
	पूर्णांक ring;
	जोड़ mbox_msg msg;
	atomic64_t mbx_resp;
पूर्ण;

/**
 * काष्ठा nitrox_iov - SR-IOV inक्रमmation
 * @num_vfs: number of VF(s) enabled
 * @max_vf_queues: Maximum number of queues allowed क्रम VF
 * @vfdev: VF(s) devices
 * @pf2vf_wq: workqueue क्रम PF2VF communication
 * @msix: MSI-X entry क्रम PF in SR-IOV हाल
 */
काष्ठा nitrox_iov अणु
	पूर्णांक num_vfs;
	पूर्णांक max_vf_queues;
	काष्ठा nitrox_vfdev *vfdev;
	काष्ठा workqueue_काष्ठा *pf2vf_wq;
	काष्ठा msix_entry msix;
पूर्ण;

/*
 * NITROX Device states
 */
क्रमागत ndev_state अणु
	__NDEV_NOT_READY,
	__NDEV_READY,
	__NDEV_IN_RESET,
पूर्ण;

/* NITROX support modes क्रम VF(s) */
क्रमागत vf_mode अणु
	__NDEV_MODE_PF,
	__NDEV_MODE_VF16,
	__NDEV_MODE_VF32,
	__NDEV_MODE_VF64,
	__NDEV_MODE_VF128,
पूर्ण;

#घोषणा __NDEV_SRIOV_BIT 0

/* command queue size */
#घोषणा DEFAULT_CMD_QLEN 2048
/* command समयout in milliseconds */
#घोषणा CMD_TIMEOUT 2000

#घोषणा DEV(ndev) ((काष्ठा device *)(&(ndev)->pdev->dev))

#घोषणा NITROX_CSR_ADDR(ndev, offset) \
	((ndev)->bar_addr + (offset))

/**
 * काष्ठा nitrox_device - NITROX Device Inक्रमmation.
 * @list: poपूर्णांकer to linked list of devices
 * @bar_addr: iomap address
 * @pdev: PCI device inक्रमmation
 * @state: NITROX device state
 * @flags: flags to indicate device the features
 * @समयout: Request समयout in jअगरfies
 * @refcnt: Device usage count
 * @idx: device index (0..N)
 * @node: NUMA node id attached
 * @qlen: Command queue length
 * @nr_queues: Number of command queues
 * @mode: Device mode PF/VF
 * @ctx_pool: DMA pool क्रम crypto context
 * @pkt_inq: Packet input rings
 * @aqmq: AQM command queues
 * @qvec: MSI-X queue vectors inक्रमmation
 * @iov: SR-IOV inक्रमmatin
 * @num_vecs: number of MSI-X vectors
 * @stats: request statistics
 * @hw: hardware inक्रमmation
 * @debugfs_dir: debugfs directory
 */
काष्ठा nitrox_device अणु
	काष्ठा list_head list;

	u8 __iomem *bar_addr;
	काष्ठा pci_dev *pdev;

	atomic_t state;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ समयout;
	refcount_t refcnt;

	u8 idx;
	पूर्णांक node;
	u16 qlen;
	u16 nr_queues;
	क्रमागत vf_mode mode;

	काष्ठा dma_pool *ctx_pool;
	काष्ठा nitrox_cmdq *pkt_inq;
	काष्ठा nitrox_cmdq *aqmq[MAX_DEV_QUEUES] ____cacheline_aligned_in_smp;

	काष्ठा nitrox_q_vector *qvec;
	काष्ठा nitrox_iov iov;
	पूर्णांक num_vecs;

	काष्ठा nitrox_stats stats;
	काष्ठा nitrox_hw hw;
#अगर IS_ENABLED(CONFIG_DEBUG_FS)
	काष्ठा dentry *debugfs_dir;
#पूर्ण_अगर
पूर्ण;

/**
 * nitrox_पढ़ो_csr - Read from device रेजिस्टर
 * @ndev: NITROX device
 * @offset: offset of the रेजिस्टर to पढ़ो
 *
 * Returns: value पढ़ो
 */
अटल अंतरभूत u64 nitrox_पढ़ो_csr(काष्ठा nitrox_device *ndev, u64 offset)
अणु
	वापस पढ़ोq(ndev->bar_addr + offset);
पूर्ण

/**
 * nitrox_ग_लिखो_csr - Write to device रेजिस्टर
 * @ndev: NITROX device
 * @offset: offset of the रेजिस्टर to ग_लिखो
 * @value: value to ग_लिखो
 */
अटल अंतरभूत व्योम nitrox_ग_लिखो_csr(काष्ठा nitrox_device *ndev, u64 offset,
				    u64 value)
अणु
	ग_लिखोq(value, (ndev->bar_addr + offset));
पूर्ण

अटल अंतरभूत bool nitrox_पढ़ोy(काष्ठा nitrox_device *ndev)
अणु
	वापस atomic_पढ़ो(&ndev->state) == __NDEV_READY;
पूर्ण

अटल अंतरभूत bool nitrox_vfdev_पढ़ोy(काष्ठा nitrox_vfdev *vfdev)
अणु
	वापस atomic_पढ़ो(&vfdev->state) == __NDEV_READY;
पूर्ण

#पूर्ण_अगर /* __NITROX_DEV_H */
