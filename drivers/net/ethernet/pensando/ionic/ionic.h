<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2017 - 2019 Pensanकरो Systems, Inc */

#अगर_अघोषित _IONIC_H_
#घोषणा _IONIC_H_

काष्ठा ionic_lअगर;

#समावेश "ionic_if.h"
#समावेश "ionic_dev.h"
#समावेश "ionic_devlink.h"

#घोषणा IONIC_DRV_NAME		"ionic"
#घोषणा IONIC_DRV_DESCRIPTION	"Pensando Ethernet NIC Driver"

#घोषणा PCI_VENDOR_ID_PENSANDO			0x1dd8

#घोषणा PCI_DEVICE_ID_PENSANDO_IONIC_ETH_PF	0x1002
#घोषणा PCI_DEVICE_ID_PENSANDO_IONIC_ETH_VF	0x1003

#घोषणा DEVCMD_TIMEOUT  10

#घोषणा IONIC_PHC_UPDATE_NS	10000000000	    /* 10s in nanoseconds */
#घोषणा NORMAL_PPB		1000000000	    /* one billion parts per billion */
#घोषणा SCALED_PPM		(1000000ull << 16)  /* 2^16 million parts per 2^16 million */

काष्ठा ionic_vf अणु
	u16	 index;
	u8	 macaddr[6];
	__le32	 maxrate;
	__le16	 vlanid;
	u8	 spoofchk;
	u8	 trusted;
	u8	 linkstate;
	dma_addr_t       stats_pa;
	काष्ठा ionic_lअगर_stats stats;
पूर्ण;

काष्ठा ionic अणु
	काष्ठा pci_dev *pdev;
	काष्ठा device *dev;
	काष्ठा devlink_port dl_port;
	काष्ठा ionic_dev idev;
	काष्ठा mutex dev_cmd_lock;	/* lock क्रम dev_cmd operations */
	काष्ठा dentry *dentry;
	काष्ठा ionic_dev_bar bars[IONIC_BARS_MAX];
	अचिन्हित पूर्णांक num_bars;
	काष्ठा ionic_identity ident;
	काष्ठा ionic_lअगर *lअगर;
	अचिन्हित पूर्णांक nnqs_per_lअगर;
	अचिन्हित पूर्णांक neqs_per_lअगर;
	अचिन्हित पूर्णांक ntxqs_per_lअगर;
	अचिन्हित पूर्णांक nrxqs_per_lअगर;
	अचिन्हित पूर्णांक nपूर्णांकrs;
	DECLARE_BITMAP(पूर्णांकrs, IONIC_INTR_CTRL_REGS_MAX);
	काष्ठा work_काष्ठा nb_work;
	काष्ठा notअगरier_block nb;
	काष्ठा rw_semaphore vf_op_lock;	/* lock क्रम VF operations */
	काष्ठा ionic_vf *vfs;
	पूर्णांक num_vfs;
	काष्ठा समयr_list watchकरोg_समयr;
	पूर्णांक watchकरोg_period;
पूर्ण;

काष्ठा ionic_admin_ctx अणु
	काष्ठा completion work;
	जोड़ ionic_adminq_cmd cmd;
	जोड़ ionic_adminq_comp comp;
पूर्ण;

पूर्णांक ionic_adminq_post(काष्ठा ionic_lअगर *lअगर, काष्ठा ionic_admin_ctx *ctx);
पूर्णांक ionic_adminq_रुको(काष्ठा ionic_lअगर *lअगर, काष्ठा ionic_admin_ctx *ctx, पूर्णांक err);
पूर्णांक ionic_adminq_post_रुको(काष्ठा ionic_lअगर *lअगर, काष्ठा ionic_admin_ctx *ctx);
पूर्णांक ionic_dev_cmd_रुको(काष्ठा ionic *ionic, अचिन्हित दीर्घ max_रुको);
पूर्णांक ionic_set_dma_mask(काष्ठा ionic *ionic);
पूर्णांक ionic_setup(काष्ठा ionic *ionic);

पूर्णांक ionic_identअगरy(काष्ठा ionic *ionic);
पूर्णांक ionic_init(काष्ठा ionic *ionic);
पूर्णांक ionic_reset(काष्ठा ionic *ionic);

पूर्णांक ionic_port_identअगरy(काष्ठा ionic *ionic);
पूर्णांक ionic_port_init(काष्ठा ionic *ionic);
पूर्णांक ionic_port_reset(काष्ठा ionic *ionic);

#पूर्ण_अगर /* _IONIC_H_ */
