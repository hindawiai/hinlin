<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Marvell 88SE64xx/88SE94xx मुख्य function head file
 *
 * Copyright 2007 Red Hat, Inc.
 * Copyright 2008 Marvell. <kewei@marvell.com>
 * Copyright 2009-2011 Marvell. <yuxiangl@marvell.com>
*/

#अगर_अघोषित _MV_SAS_H_
#घोषणा _MV_SAS_H_

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/types.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <scsi/libsas.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/sas_ata.h>
#समावेश "mv_defs.h"

#घोषणा DRV_NAME		"mvsas"
#घोषणा DRV_VERSION		"0.8.16"
#घोषणा MVS_ID_NOT_MAPPED	0x7f
#घोषणा WIDE_PORT_MAX_PHY		4
#घोषणा mv_prपूर्णांकk(fmt, arg ...)	\
	prपूर्णांकk(KERN_DEBUG"%s %d:" fmt, __खाता__, __LINE__, ## arg)
#अगर_घोषित MV_DEBUG
#घोषणा mv_dprपूर्णांकk(क्रमmat, arg...)	\
	prपूर्णांकk(KERN_DEBUG"%s %d:" क्रमmat, __खाता__, __LINE__, ## arg)
#अन्यथा
#घोषणा mv_dprपूर्णांकk(क्रमmat, arg...) no_prपूर्णांकk(क्रमmat, ## arg)
#पूर्ण_अगर
#घोषणा MV_MAX_U32			0xffffffff

बाह्य पूर्णांक पूर्णांकerrupt_coalescing;
बाह्य काष्ठा mvs_tgt_initiator mvs_tgt;
बाह्य काष्ठा mvs_info *tgt_mvi;
बाह्य स्थिर काष्ठा mvs_dispatch mvs_64xx_dispatch;
बाह्य स्थिर काष्ठा mvs_dispatch mvs_94xx_dispatch;

#घोषणा bit(n) ((u64)1 << n)

#घोषणा क्रम_each_phy(__lseq_mask, __mc, __lseq)			\
	क्रम ((__mc) = (__lseq_mask), (__lseq) = 0;		\
					(__mc) != 0 ;		\
					(++__lseq), (__mc) >>= 1)

#घोषणा MVS_PHY_ID (1U << sas_phy->id)
#घोषणा MV_INIT_DELAYED_WORK(w, f, d)	INIT_DELAYED_WORK(w, f)
#घोषणा UNASSOC_D2H_FIS(id)		\
	((व्योम *) mvi->rx_fis + 0x100 * id)
#घोषणा SATA_RECEIVED_FIS_LIST(reg_set)	\
	((व्योम *) mvi->rx_fis + mvi->chip->fis_offs + 0x100 * reg_set)
#घोषणा SATA_RECEIVED_SDB_FIS(reg_set)	\
	(SATA_RECEIVED_FIS_LIST(reg_set) + 0x58)
#घोषणा SATA_RECEIVED_D2H_FIS(reg_set)	\
	(SATA_RECEIVED_FIS_LIST(reg_set) + 0x40)
#घोषणा SATA_RECEIVED_PIO_FIS(reg_set)	\
	(SATA_RECEIVED_FIS_LIST(reg_set) + 0x20)
#घोषणा SATA_RECEIVED_DMA_FIS(reg_set)	\
	(SATA_RECEIVED_FIS_LIST(reg_set) + 0x00)

क्रमागत dev_status अणु
	MVS_DEV_NORMAL = 0x0,
	MVS_DEV_EH	= 0x1,
पूर्ण;

क्रमागत dev_reset अणु
	MVS_SOFT_RESET	= 0,
	MVS_HARD_RESET	= 1,
	MVS_PHY_TUNE	= 2,
पूर्ण;

काष्ठा mvs_info;
काष्ठा mvs_prv_info;

काष्ठा mvs_dispatch अणु
	अक्षर *name;
	पूर्णांक (*chip_init)(काष्ठा mvs_info *mvi);
	पूर्णांक (*spi_init)(काष्ठा mvs_info *mvi);
	पूर्णांक (*chip_ioremap)(काष्ठा mvs_info *mvi);
	व्योम (*chip_iounmap)(काष्ठा mvs_info *mvi);
	irqवापस_t (*isr)(काष्ठा mvs_info *mvi, पूर्णांक irq, u32 stat);
	u32 (*isr_status)(काष्ठा mvs_info *mvi, पूर्णांक irq);
	व्योम (*पूर्णांकerrupt_enable)(काष्ठा mvs_info *mvi);
	व्योम (*पूर्णांकerrupt_disable)(काष्ठा mvs_info *mvi);

	u32 (*पढ़ो_phy_ctl)(काष्ठा mvs_info *mvi, u32 port);
	व्योम (*ग_लिखो_phy_ctl)(काष्ठा mvs_info *mvi, u32 port, u32 val);

	u32 (*पढ़ो_port_cfg_data)(काष्ठा mvs_info *mvi, u32 port);
	व्योम (*ग_लिखो_port_cfg_data)(काष्ठा mvs_info *mvi, u32 port, u32 val);
	व्योम (*ग_लिखो_port_cfg_addr)(काष्ठा mvs_info *mvi, u32 port, u32 addr);

	u32 (*पढ़ो_port_vsr_data)(काष्ठा mvs_info *mvi, u32 port);
	व्योम (*ग_लिखो_port_vsr_data)(काष्ठा mvs_info *mvi, u32 port, u32 val);
	व्योम (*ग_लिखो_port_vsr_addr)(काष्ठा mvs_info *mvi, u32 port, u32 addr);

	u32 (*पढ़ो_port_irq_stat)(काष्ठा mvs_info *mvi, u32 port);
	व्योम (*ग_लिखो_port_irq_stat)(काष्ठा mvs_info *mvi, u32 port, u32 val);

	u32 (*पढ़ो_port_irq_mask)(काष्ठा mvs_info *mvi, u32 port);
	व्योम (*ग_लिखो_port_irq_mask)(काष्ठा mvs_info *mvi, u32 port, u32 val);

	व्योम (*command_active)(काष्ठा mvs_info *mvi, u32 slot_idx);
	व्योम (*clear_srs_irq)(काष्ठा mvs_info *mvi, u8 reg_set, u8 clear_all);
	व्योम (*issue_stop)(काष्ठा mvs_info *mvi, क्रमागत mvs_port_type type,
				u32 tfs);
	व्योम (*start_delivery)(काष्ठा mvs_info *mvi, u32 tx);
	u32 (*rx_update)(काष्ठा mvs_info *mvi);
	व्योम (*पूर्णांक_full)(काष्ठा mvs_info *mvi);
	u8 (*assign_reg_set)(काष्ठा mvs_info *mvi, u8 *tfs);
	व्योम (*मुक्त_reg_set)(काष्ठा mvs_info *mvi, u8 *tfs);
	u32 (*prd_size)(व्योम);
	u32 (*prd_count)(व्योम);
	व्योम (*make_prd)(काष्ठा scatterlist *scatter, पूर्णांक nr, व्योम *prd);
	व्योम (*detect_porttype)(काष्ठा mvs_info *mvi, पूर्णांक i);
	पूर्णांक (*oob_करोne)(काष्ठा mvs_info *mvi, पूर्णांक i);
	व्योम (*fix_phy_info)(काष्ठा mvs_info *mvi, पूर्णांक i,
				काष्ठा sas_identअगरy_frame *id);
	व्योम (*phy_work_around)(काष्ठा mvs_info *mvi, पूर्णांक i);
	व्योम (*phy_set_link_rate)(काष्ठा mvs_info *mvi, u32 phy_id,
				काष्ठा sas_phy_linkrates *rates);
	u32 (*phy_max_link_rate)(व्योम);
	व्योम (*phy_disable)(काष्ठा mvs_info *mvi, u32 phy_id);
	व्योम (*phy_enable)(काष्ठा mvs_info *mvi, u32 phy_id);
	व्योम (*phy_reset)(काष्ठा mvs_info *mvi, u32 phy_id, पूर्णांक hard);
	व्योम (*stp_reset)(काष्ठा mvs_info *mvi, u32 phy_id);
	व्योम (*clear_active_cmds)(काष्ठा mvs_info *mvi);
	u32 (*spi_पढ़ो_data)(काष्ठा mvs_info *mvi);
	व्योम (*spi_ग_लिखो_data)(काष्ठा mvs_info *mvi, u32 data);
	पूर्णांक (*spi_buildcmd)(काष्ठा mvs_info *mvi,
						u32      *dwCmd,
						u8       cmd,
						u8       पढ़ो,
						u8       length,
						u32      addr
						);
	पूर्णांक (*spi_issuecmd)(काष्ठा mvs_info *mvi, u32 cmd);
	पूर्णांक (*spi_रुकोdataपढ़ोy)(काष्ठा mvs_info *mvi, u32 समयout);
	व्योम (*dma_fix)(काष्ठा mvs_info *mvi, u32 phy_mask,
				पूर्णांक buf_len, पूर्णांक from, व्योम *prd);
	व्योम (*tune_पूर्णांकerrupt)(काष्ठा mvs_info *mvi, u32 समय);
	व्योम (*non_spec_ncq_error)(काष्ठा mvs_info *mvi);
	पूर्णांक (*gpio_ग_लिखो)(काष्ठा mvs_prv_info *mvs_prv, u8 reg_type,
			u8 reg_index, u8 reg_count, u8 *ग_लिखो_data);

पूर्ण;

काष्ठा mvs_chip_info अणु
	u32 		n_host;
	u32 		n_phy;
	u32 		fis_offs;
	u32 		fis_count;
	u32 		srs_sz;
	u32		sg_width;
	u32 		slot_width;
	स्थिर काष्ठा mvs_dispatch *dispatch;
पूर्ण;
#घोषणा MVS_MAX_SG		(1U << mvi->chip->sg_width)
#घोषणा MVS_CHIP_SLOT_SZ	(1U << mvi->chip->slot_width)
#घोषणा MVS_RX_FISL_SZ		\
	(mvi->chip->fis_offs + (mvi->chip->fis_count * 0x100))
#घोषणा MVS_CHIP_DISP		(mvi->chip->dispatch)

काष्ठा mvs_err_info अणु
	__le32			flags;
	__le32			flags2;
पूर्ण;

काष्ठा mvs_cmd_hdr अणु
	__le32			flags;	/* PRD tbl len; SAS, SATA ctl */
	__le32			lens;	/* cmd, max resp frame len */
	__le32			tags;	/* targ port xfer tag; tag */
	__le32			data_len;	/* data xfer len */
	__le64			cmd_tbl;  	/* command table address */
	__le64			खोलो_frame;	/* खोलो addr frame address */
	__le64			status_buf;	/* status buffer address */
	__le64			prd_tbl;		/* PRD tbl address */
	__le32			reserved[4];
पूर्ण;

काष्ठा mvs_port अणु
	काष्ठा asd_sas_port	sas_port;
	u8			port_attached;
	u8			wide_port_phymap;
	काष्ठा list_head	list;
पूर्ण;

काष्ठा mvs_phy अणु
	काष्ठा mvs_info 		*mvi;
	काष्ठा mvs_port		*port;
	काष्ठा asd_sas_phy	sas_phy;
	काष्ठा sas_identअगरy	identअगरy;
	काष्ठा scsi_device	*sdev;
	काष्ठा समयr_list समयr;
	u64		dev_sas_addr;
	u64		att_dev_sas_addr;
	u32		att_dev_info;
	u32		dev_info;
	u32		phy_type;
	u32		phy_status;
	u32		irq_status;
	u32		frame_rcvd_size;
	u8		frame_rcvd[32];
	u8		phy_attached;
	u8		phy_mode;
	u8		reserved[2];
	u32		phy_event;
	क्रमागत sas_linkrate	minimum_linkrate;
	क्रमागत sas_linkrate	maximum_linkrate;
पूर्ण;

काष्ठा mvs_device अणु
	काष्ठा list_head		dev_entry;
	क्रमागत sas_device_type dev_type;
	काष्ठा mvs_info *mvi_info;
	काष्ठा करोमुख्य_device *sas_device;
	u32 attached_phy;
	u32 device_id;
	u32 running_req;
	u8 taskfileset;
	u8 dev_status;
	u16 reserved;
पूर्ण;

/* Generate  PHY tunning parameters */
काष्ठा phy_tuning अणु
	/* 1 bit,  transmitter emphasis enable	*/
	u8	trans_emp_en:1;
	/* 4 bits, transmitter emphasis amplitude */
	u8	trans_emp_amp:4;
	/* 3 bits, reserved space */
	u8	Reserved_2bit_1:3;
	/* 5 bits, transmitter amplitude */
	u8	trans_amp:5;
	/* 2 bits, transmitter amplitude adjust */
	u8	trans_amp_adj:2;
	/* 1 bit, reserved space */
	u8	resv_2bit_2:1;
	/* 2 bytes, reserved space */
	u8	reserved[2];
पूर्ण;

काष्ठा ffe_control अणु
	/* 4 bits,  FFE Capacitor Select  (value range 0~F)  */
	u8 ffe_cap_sel:4;
	/* 3 bits,  FFE Resistor Select (value range 0~7) */
	u8 ffe_rss_sel:3;
	/* 1 bit reserve*/
	u8 reserved:1;
पूर्ण;

/*
 * HBA_Info_Page is saved in Flash/NVRAM, total 256 bytes.
 * The data area is valid only Signature="MRVL".
 * If any member fills with 0xFF, the member is invalid.
 */
काष्ठा hba_info_page अणु
	/* Dword 0 */
	/* 4 bytes, काष्ठाure signature,should be "MRVL" at first initial */
	u8 signature[4];

	/* Dword 1-13 */
	u32 reserved1[13];

	/* Dword 14-29 */
	/* 64 bytes, SAS address क्रम each port */
	u64 sas_addr[8];

	/* Dword 30-31 */
	/* 8 bytes क्रम vanir 8 port PHY FFE seeting
	 * BIT 0~3 : FFE Capacitor select(value range 0~F)
	 * BIT 4~6 : FFE Resistor select(value range 0~7)
	 * BIT 7: reserve.
	 */

	काष्ठा ffe_control  ffe_ctl[8];
	/* Dword 32 -43 */
	u32 reserved2[12];

	/* Dword 44-45 */
	/* 8 bytes,  0:  1.5G, 1: 3.0G, should be 0x01 at first initial */
	u8 phy_rate[8];

	/* Dword 46-53 */
	/* 32 bytes, PHY tuning parameters क्रम each PHY*/
	काष्ठा phy_tuning   phy_tuning[8];

	/* Dword 54-63 */
	u32 reserved3[10];
पूर्ण;	/* total 256 bytes */

काष्ठा mvs_slot_info अणु
	काष्ठा list_head entry;
	जोड़ अणु
		काष्ठा sas_task *task;
		व्योम *tdata;
	पूर्ण;
	u32 n_elem;
	u32 tx;
	u32 slot_tag;

	/* DMA buffer क्रम storing cmd tbl, खोलो addr frame, status buffer,
	 * and PRD table
	 */
	व्योम *buf;
	dma_addr_t buf_dma;
	व्योम *response;
	काष्ठा mvs_port *port;
	काष्ठा mvs_device	*device;
	व्योम *खोलो_frame;
पूर्ण;

काष्ठा mvs_info अणु
	अचिन्हित दीर्घ flags;

	/* host-wide lock */
	spinlock_t lock;

	/* our device */
	काष्ठा pci_dev *pdev;
	काष्ठा device *dev;

	/* enhanced mode रेजिस्टरs */
	व्योम __iomem *regs;

	/* peripheral or soc रेजिस्टरs */
	व्योम __iomem *regs_ex;
	u8 sas_addr[SAS_ADDR_SIZE];

	/* SCSI/SAS glue */
	काष्ठा sas_ha_काष्ठा *sas;
	काष्ठा Scsi_Host *shost;

	/* TX (delivery) DMA ring */
	__le32 *tx;
	dma_addr_t tx_dma;

	/* cached next-producer idx */
	u32 tx_prod;

	/* RX (completion) DMA ring */
	__le32	*rx;
	dma_addr_t rx_dma;

	/* RX consumer idx */
	u32 rx_cons;

	/* RX'd FIS area */
	__le32 *rx_fis;
	dma_addr_t rx_fis_dma;

	/* DMA command header slots */
	काष्ठा mvs_cmd_hdr *slot;
	dma_addr_t slot_dma;

	u32 chip_id;
	स्थिर काष्ठा mvs_chip_info *chip;

	पूर्णांक tags_num;
	अचिन्हित दीर्घ *tags;
	/* further per-slot inक्रमmation */
	काष्ठा mvs_phy phy[MVS_MAX_PHYS];
	काष्ठा mvs_port port[MVS_MAX_PHYS];
	u32 id;
	u64 sata_reg_set;
	काष्ठा list_head *hba_list;
	काष्ठा list_head soc_entry;
	काष्ठा list_head wq_list;
	अचिन्हित दीर्घ instance;
	u16 flashid;
	u32 flashsize;
	u32 flashsectSize;

	व्योम *adकरोn;
	काष्ठा hba_info_page hba_info_param;
	काष्ठा mvs_device	devices[MVS_MAX_DEVICES];
	व्योम *bulk_buffer;
	dma_addr_t bulk_buffer_dma;
	व्योम *bulk_buffer1;
	dma_addr_t bulk_buffer_dma1;
#घोषणा TRASH_BUCKET_SIZE    	0x20000
	व्योम *dma_pool;
	काष्ठा mvs_slot_info slot_info[];
पूर्ण;

काष्ठा mvs_prv_infoअणु
	u8 n_host;
	u8 n_phy;
	u8 scan_finished;
	u8 reserve;
	काष्ठा mvs_info *mvi[2];
	काष्ठा tasklet_काष्ठा mv_tasklet;
पूर्ण;

काष्ठा mvs_wq अणु
	काष्ठा delayed_work work_q;
	काष्ठा mvs_info *mvi;
	व्योम *data;
	पूर्णांक handler;
	काष्ठा list_head entry;
पूर्ण;

काष्ठा mvs_task_exec_info अणु
	काष्ठा sas_task *task;
	काष्ठा mvs_cmd_hdr *hdr;
	काष्ठा mvs_port *port;
	u32 tag;
	पूर्णांक n_elem;
पूर्ण;

/******************** function prototype *********************/
व्योम mvs_get_sas_addr(व्योम *buf, u32 buflen);
व्योम mvs_tag_clear(काष्ठा mvs_info *mvi, u32 tag);
व्योम mvs_tag_मुक्त(काष्ठा mvs_info *mvi, u32 tag);
व्योम mvs_tag_set(काष्ठा mvs_info *mvi, अचिन्हित पूर्णांक tag);
पूर्णांक mvs_tag_alloc(काष्ठा mvs_info *mvi, u32 *tag_out);
व्योम mvs_tag_init(काष्ठा mvs_info *mvi);
व्योम mvs_iounmap(व्योम __iomem *regs);
पूर्णांक mvs_ioremap(काष्ठा mvs_info *mvi, पूर्णांक bar, पूर्णांक bar_ex);
व्योम mvs_phys_reset(काष्ठा mvs_info *mvi, u32 phy_mask, पूर्णांक hard);
पूर्णांक mvs_phy_control(काष्ठा asd_sas_phy *sas_phy, क्रमागत phy_func func,
			व्योम *funcdata);
व्योम mvs_set_sas_addr(काष्ठा mvs_info *mvi, पूर्णांक port_id, u32 off_lo,
		      u32 off_hi, u64 sas_addr);
व्योम mvs_scan_start(काष्ठा Scsi_Host *shost);
पूर्णांक mvs_scan_finished(काष्ठा Scsi_Host *shost, अचिन्हित दीर्घ समय);
पूर्णांक mvs_queue_command(काष्ठा sas_task *task, gfp_t gfp_flags);
पूर्णांक mvs_पात_task(काष्ठा sas_task *task);
पूर्णांक mvs_पात_task_set(काष्ठा करोमुख्य_device *dev, u8 *lun);
पूर्णांक mvs_clear_aca(काष्ठा करोमुख्य_device *dev, u8 *lun);
पूर्णांक mvs_clear_task_set(काष्ठा करोमुख्य_device *dev, u8 * lun);
व्योम mvs_port_क्रमmed(काष्ठा asd_sas_phy *sas_phy);
व्योम mvs_port_deक्रमmed(काष्ठा asd_sas_phy *sas_phy);
पूर्णांक mvs_dev_found(काष्ठा करोमुख्य_device *dev);
व्योम mvs_dev_gone(काष्ठा करोमुख्य_device *dev);
पूर्णांक mvs_lu_reset(काष्ठा करोमुख्य_device *dev, u8 *lun);
पूर्णांक mvs_slot_complete(काष्ठा mvs_info *mvi, u32 rx_desc, u32 flags);
पूर्णांक mvs_I_T_nexus_reset(काष्ठा करोमुख्य_device *dev);
पूर्णांक mvs_query_task(काष्ठा sas_task *task);
व्योम mvs_release_task(काष्ठा mvs_info *mvi,
			काष्ठा करोमुख्य_device *dev);
व्योम mvs_करो_release_task(काष्ठा mvs_info *mvi, पूर्णांक phy_no,
			काष्ठा करोमुख्य_device *dev);
व्योम mvs_पूर्णांक_port(काष्ठा mvs_info *mvi, पूर्णांक phy_no, u32 events);
व्योम mvs_update_phyinfo(काष्ठा mvs_info *mvi, पूर्णांक i, पूर्णांक get_st);
पूर्णांक mvs_पूर्णांक_rx(काष्ठा mvs_info *mvi, bool self_clear);
काष्ठा mvs_device *mvs_find_dev_by_reg_set(काष्ठा mvs_info *mvi, u8 reg_set);
पूर्णांक mvs_gpio_ग_लिखो(काष्ठा sas_ha_काष्ठा *, u8 reg_type, u8 reg_index,
			u8 reg_count, u8 *ग_लिखो_data);
#पूर्ण_अगर

