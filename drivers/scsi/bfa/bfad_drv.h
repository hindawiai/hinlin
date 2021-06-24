<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014- QLogic Corporation.
 * All rights reserved
 * www.qlogic.com
 *
 * Linux driver क्रम QLogic BR-series Fibre Channel Host Bus Adapter.
 */

/*
 * Contains base driver definitions.
 */

/*
 *  bfa_drv.h Linux driver data काष्ठाures.
 */

#अगर_अघोषित __BFAD_DRV_H__
#घोषणा __BFAD_DRV_H__

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/idr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/cdev.h>
#समावेश <linux/fs.h>
#समावेश <linux/delay.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/bitops.h>
#समावेश <linux/aer.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_transport_fc.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_bsg_fc.h>
#समावेश <scsi/scsi_devinfo.h>

#समावेश "bfa_modules.h"
#समावेश "bfa_fcs.h"
#समावेश "bfa_defs_fcs.h"

#समावेश "bfa_plog.h"
#समावेश "bfa_cs.h"

#घोषणा BFAD_DRIVER_NAME	"bfa"
#अगर_घोषित BFA_DRIVER_VERSION
#घोषणा BFAD_DRIVER_VERSION    BFA_DRIVER_VERSION
#अन्यथा
#घोषणा BFAD_DRIVER_VERSION    "3.2.25.1"
#पूर्ण_अगर

#घोषणा BFAD_PROTO_NAME FCPI_NAME
#घोषणा BFAD_IRQ_FLAGS IRQF_SHARED

#अगर_अघोषित FC_PORTSPEED_8GBIT
#घोषणा FC_PORTSPEED_8GBIT 0x10
#पूर्ण_अगर

/*
 * BFAD flags
 */
#घोषणा BFAD_MSIX_ON				0x00000001
#घोषणा BFAD_HAL_INIT_DONE			0x00000002
#घोषणा BFAD_DRV_INIT_DONE			0x00000004
#घोषणा BFAD_CFG_PPORT_DONE			0x00000008
#घोषणा BFAD_HAL_START_DONE			0x00000010
#घोषणा BFAD_PORT_ONLINE			0x00000020
#घोषणा BFAD_RPORT_ONLINE			0x00000040
#घोषणा BFAD_FCS_INIT_DONE			0x00000080
#घोषणा BFAD_HAL_INIT_FAIL			0x00000100
#घोषणा BFAD_FC4_PROBE_DONE			0x00000200
#घोषणा BFAD_PORT_DELETE			0x00000001
#घोषणा BFAD_INTX_ON				0x00000400
#घोषणा BFAD_EEH_BUSY				0x00000800
#घोषणा BFAD_EEH_PCI_CHANNEL_IO_PERM_FAILURE	0x00001000
/*
 * BFAD related definition
 */
#घोषणा SCSI_SCAN_DELAY		HZ
#घोषणा BFAD_STOP_TIMEOUT	30
#घोषणा BFAD_SUSPEND_TIMEOUT	BFAD_STOP_TIMEOUT

/*
 * BFAD configuration parameter शेष values
 */
#घोषणा BFAD_LUN_QUEUE_DEPTH	32
#घोषणा BFAD_IO_MAX_SGE		SG_ALL
#घोषणा BFAD_MIN_SECTORS	128 /* 64k   */
#घोषणा BFAD_MAX_SECTORS	0xFFFF  /* 32 MB */

#घोषणा bfad_isr_t irq_handler_t

#घोषणा MAX_MSIX_ENTRY 22

काष्ठा bfad_msix_s अणु
	काष्ठा bfad_s *bfad;
	काष्ठा msix_entry msix;
	अक्षर name[32];
पूर्ण;

/*
 * Only append to the क्रमागतs defined here to aव्योम any versioning
 * needed between trace utility and driver version
 */
क्रमागत अणु
	BFA_TRC_LDRV_BFAD		= 1,
	BFA_TRC_LDRV_IM			= 2,
	BFA_TRC_LDRV_BSG		= 3,
पूर्ण;

क्रमागत bfad_port_pvb_type अणु
	BFAD_PORT_PHYS_BASE = 0,
	BFAD_PORT_PHYS_VPORT = 1,
	BFAD_PORT_VF_BASE = 2,
	BFAD_PORT_VF_VPORT = 3,
पूर्ण;

/*
 * PORT data काष्ठाure
 */
काष्ठा bfad_port_s अणु
	काष्ठा list_head list_entry;
	काष्ठा bfad_s	*bfad;
	काष्ठा bfa_fcs_lport_s *fcs_port;
	u32	roles;
	s32		flags;
	u32	supported_fc4s;
	क्रमागत bfad_port_pvb_type pvb_type;
	काष्ठा bfad_im_port_s *im_port;	/* IM specअगरic data */
	/* port debugfs specअगरic data */
	काष्ठा dentry *port_debugfs_root;
पूर्ण;

/*
 * VPORT data काष्ठाure
 */
काष्ठा bfad_vport_s अणु
	काष्ठा bfad_port_s     drv_port;
	काष्ठा bfa_fcs_vport_s fcs_vport;
	काष्ठा completion *comp_del;
	काष्ठा list_head list_entry;
पूर्ण;

/*
 * VF data काष्ठाure
 */
काष्ठा bfad_vf_s अणु
	bfa_fcs_vf_t    fcs_vf;
	काष्ठा bfad_port_s    base_port;	/* base port क्रम vf */
	काष्ठा bfad_s   *bfad;
पूर्ण;

काष्ठा bfad_cfg_param_s अणु
	u32	rport_del_समयout;
	u32	ioc_queue_depth;
	u32	lun_queue_depth;
	u32	io_max_sge;
	u32	binding_method;
पूर्ण;

जोड़ bfad_पंचांगp_buf अणु
	/* From काष्ठा bfa_adapter_attr_s */
	अक्षर		manufacturer[BFA_ADAPTER_MFG_NAME_LEN];
	अक्षर		serial_num[BFA_ADAPTER_SERIAL_NUM_LEN];
	अक्षर		model[BFA_ADAPTER_MODEL_NAME_LEN];
	अक्षर		fw_ver[BFA_VERSION_LEN];
	अक्षर		optrom_ver[BFA_VERSION_LEN];

	/* From काष्ठा bfa_ioc_pci_attr_s */
	u8		chip_rev[BFA_IOC_CHIP_REV_LEN];  /*  chip revision */

	wwn_t		wwn[BFA_FCS_MAX_LPORTS];
पूर्ण;

/*
 * BFAD (PCI function) data काष्ठाure
 */
काष्ठा bfad_s अणु
	bfa_sm_t	sm;	/* state machine */
	काष्ठा list_head list_entry;
	काष्ठा bfa_s	bfa;
	काष्ठा bfa_fcs_s bfa_fcs;
	काष्ठा pci_dev *pcidev;
	स्थिर अक्षर *pci_name;
	काष्ठा bfa_pcidev_s hal_pcidev;
	काष्ठा bfa_ioc_pci_attr_s pci_attr;
	व्योम __iomem   *pci_bar0_kva;
	व्योम __iomem   *pci_bar2_kva;
	काष्ठा completion comp;
	काष्ठा completion suspend;
	काष्ठा completion enable_comp;
	काष्ठा completion disable_comp;
	bfa_boolean_t   disable_active;
	काष्ठा bfad_port_s     pport;	/* physical port of the BFAD */
	काष्ठा bfa_meminfo_s meminfo;
	काष्ठा bfa_iocfc_cfg_s   ioc_cfg;
	u32	inst_no;	/* BFAD instance number */
	u32	bfad_flags;
	spinlock_t      bfad_lock;
	काष्ठा task_काष्ठा *bfad_tsk;
	काष्ठा bfad_cfg_param_s cfg_data;
	काष्ठा bfad_msix_s msix_tab[MAX_MSIX_ENTRY];
	पूर्णांक		nvec;
	अक्षर	adapter_name[BFA_ADAPTER_SYM_NAME_LEN];
	अक्षर	port_name[BFA_ADAPTER_SYM_NAME_LEN];
	काष्ठा समयr_list hal_पंचांगo;
	अचिन्हित दीर्घ   hs_start;
	काष्ठा bfad_im_s *im;		/* IM specअगरic data */
	काष्ठा bfa_trc_mod_s  *trcmod;
	काष्ठा bfa_plog_s      plog_buf;
	पूर्णांक		ref_count;
	जोड़ bfad_पंचांगp_buf पंचांगp_buf;
	काष्ठा fc_host_statistics link_stats;
	काष्ठा list_head pbc_vport_list;
	/* debugfs specअगरic data */
	अक्षर *regdata;
	u32 reglen;
	काष्ठा dentry *bfad_dentry_files[5];
	काष्ठा list_head	मुक्त_aen_q;
	काष्ठा list_head	active_aen_q;
	काष्ठा bfa_aen_entry_s	aen_list[BFA_AEN_MAX_ENTRY];
	spinlock_t		bfad_aen_spinlock;
	काष्ठा list_head	vport_list;
पूर्ण;

/* BFAD state machine events */
क्रमागत bfad_sm_event अणु
	BFAD_E_CREATE			= 1,
	BFAD_E_KTHREAD_CREATE_FAILED	= 2,
	BFAD_E_INIT			= 3,
	BFAD_E_INIT_SUCCESS		= 4,
	BFAD_E_HAL_INIT_FAILED		= 5,
	BFAD_E_INIT_FAILED		= 6,
	BFAD_E_FCS_EXIT_COMP		= 7,
	BFAD_E_EXIT_COMP		= 8,
	BFAD_E_STOP			= 9
पूर्ण;

/*
 * RPORT data काष्ठाure
 */
काष्ठा bfad_rport_s अणु
	काष्ठा bfa_fcs_rport_s fcs_rport;
पूर्ण;

काष्ठा bfad_buf_info अणु
	व्योम		*virt;
	dma_addr_t      phys;
	u32	size;
पूर्ण;

काष्ठा bfad_fcxp अणु
	काष्ठा bfad_port_s    *port;
	काष्ठा bfa_rport_s *bfa_rport;
	bfa_status_t    req_status;
	u16	tag;
	u16	rsp_len;
	u16	rsp_maxlen;
	u8		use_ireqbuf;
	u8		use_irspbuf;
	u32	num_req_sgles;
	u32	num_rsp_sgles;
	काष्ठा fchs_s	fchs;
	व्योम		*reqbuf_info;
	व्योम		*rspbuf_info;
	काष्ठा bfa_sge_s  *req_sge;
	काष्ठा bfa_sge_s  *rsp_sge;
	fcxp_send_cb_t  send_cbfn;
	व्योम		*send_cbarg;
	व्योम		*bfa_fcxp;
	काष्ठा completion comp;
पूर्ण;

काष्ठा bfad_hal_comp अणु
	bfa_status_t    status;
	काष्ठा completion comp;
पूर्ण;

#घोषणा BFA_LOG(level, bfad, mask, fmt, arg...)				\
करो अणु									\
	अगर (((mask) == 4) || (level[1] <= '4'))				\
		dev_prपूर्णांकk(level, &((bfad)->pcidev)->dev, fmt, ##arg);	\
पूर्ण जबतक (0)

bfa_status_t	bfad_vport_create(काष्ठा bfad_s *bfad, u16 vf_id,
				  काष्ठा bfa_lport_cfg_s *port_cfg,
				  काष्ठा device *dev);
bfa_status_t	bfad_vf_create(काष्ठा bfad_s *bfad, u16 vf_id,
			       काष्ठा bfa_lport_cfg_s *port_cfg);
bfa_status_t	bfad_cfg_pport(काष्ठा bfad_s *bfad, क्रमागत bfa_lport_role role);
bfa_status_t	bfad_drv_init(काष्ठा bfad_s *bfad);
bfa_status_t	bfad_start_ops(काष्ठा bfad_s *bfad);
व्योम		bfad_drv_start(काष्ठा bfad_s *bfad);
व्योम		bfad_uncfg_pport(काष्ठा bfad_s *bfad);
व्योम		bfad_stop(काष्ठा bfad_s *bfad);
व्योम		bfad_fcs_stop(काष्ठा bfad_s *bfad);
व्योम		bfad_हटाओ_पूर्णांकr(काष्ठा bfad_s *bfad);
व्योम		bfad_hal_mem_release(काष्ठा bfad_s *bfad);
व्योम		bfad_hcb_comp(व्योम *arg, bfa_status_t status);

पूर्णांक		bfad_setup_पूर्णांकr(काष्ठा bfad_s *bfad);
व्योम		bfad_हटाओ_पूर्णांकr(काष्ठा bfad_s *bfad);
व्योम		bfad_update_hal_cfg(काष्ठा bfa_iocfc_cfg_s *bfa_cfg);
bfa_status_t	bfad_hal_mem_alloc(काष्ठा bfad_s *bfad);
व्योम		bfad_bfa_पंचांगo(काष्ठा समयr_list *t);
व्योम		bfad_init_समयr(काष्ठा bfad_s *bfad);
पूर्णांक		bfad_pci_init(काष्ठा pci_dev *pdev, काष्ठा bfad_s *bfad);
व्योम		bfad_pci_uninit(काष्ठा pci_dev *pdev, काष्ठा bfad_s *bfad);
व्योम		bfad_drv_uninit(काष्ठा bfad_s *bfad);
पूर्णांक		bfad_worker(व्योम *ptr);
व्योम		bfad_debugfs_init(काष्ठा bfad_port_s *port);
व्योम		bfad_debugfs_निकास(काष्ठा bfad_port_s *port);

व्योम bfad_pci_हटाओ(काष्ठा pci_dev *pdev);
पूर्णांक bfad_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *pid);
व्योम bfad_rport_online_रुको(काष्ठा bfad_s *bfad);
पूर्णांक bfad_get_linkup_delay(काष्ठा bfad_s *bfad);
पूर्णांक bfad_install_msix_handler(काष्ठा bfad_s *bfad);

बाह्य काष्ठा idr bfad_im_port_index;
बाह्य काष्ठा pci_device_id bfad_id_table[];
बाह्य काष्ठा list_head bfad_list;
बाह्य अक्षर	*os_name;
बाह्य अक्षर	*os_patch;
बाह्य अक्षर	*host_name;
बाह्य पूर्णांक	num_rports;
बाह्य पूर्णांक	num_ios;
बाह्य पूर्णांक	num_पंचांगs;
बाह्य पूर्णांक	num_fcxps;
बाह्य पूर्णांक	num_ufbufs;
बाह्य पूर्णांक	reqq_size;
बाह्य पूर्णांक	rspq_size;
बाह्य पूर्णांक	num_sgpgs;
बाह्य पूर्णांक      rport_del_समयout;
बाह्य पूर्णांक      bfa_lun_queue_depth;
बाह्य पूर्णांक      bfa_io_max_sge;
बाह्य पूर्णांक      bfa_log_level;
बाह्य पूर्णांक      ioc_स्वतः_recover;
बाह्य पूर्णांक      bfa_linkup_delay;
बाह्य पूर्णांक      msix_disable_cb;
बाह्य पूर्णांक      msix_disable_ct;
बाह्य पूर्णांक      fdmi_enable;
बाह्य पूर्णांक      supported_fc4s;
बाह्य पूर्णांक	pcie_max_पढ़ो_reqsz;
बाह्य पूर्णांक	max_xfer_size;
बाह्य पूर्णांक bfa_debugfs_enable;
बाह्य काष्ठा mutex bfad_mutex;

#पूर्ण_अगर /* __BFAD_DRV_H__ */
