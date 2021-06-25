<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित FS_ENET_H
#घोषणा FS_ENET_H

#समावेश <linux/mii.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/phy.h>
#समावेश <linux/dma-mapping.h>

#समावेश <linux/fs_enet_pd.h>
#समावेश <यंत्र/fs_pd.h>

#अगर_घोषित CONFIG_CPM1
#समावेश <यंत्र/cpm1.h>
#पूर्ण_अगर

#अगर defined(CONFIG_FS_ENET_HAS_FEC)
#समावेश <यंत्र/cpm.h>

#अगर defined(CONFIG_FS_ENET_MPC5121_FEC)
/* MPC5121 FEC has dअगरferent रेजिस्टर layout */
काष्ठा fec अणु
	u32 fec_reserved0;
	u32 fec_ievent;			/* Interrupt event reg */
	u32 fec_imask;			/* Interrupt mask reg */
	u32 fec_reserved1;
	u32 fec_r_des_active;		/* Receive descriptor reg */
	u32 fec_x_des_active;		/* Transmit descriptor reg */
	u32 fec_reserved2[3];
	u32 fec_ecntrl;			/* Ethernet control reg */
	u32 fec_reserved3[6];
	u32 fec_mii_data;		/* MII manage frame reg */
	u32 fec_mii_speed;		/* MII speed control reg */
	u32 fec_reserved4[7];
	u32 fec_mib_ctrlstat;		/* MIB control/status reg */
	u32 fec_reserved5[7];
	u32 fec_r_cntrl;		/* Receive control reg */
	u32 fec_reserved6[15];
	u32 fec_x_cntrl;		/* Transmit Control reg */
	u32 fec_reserved7[7];
	u32 fec_addr_low;		/* Low 32bits MAC address */
	u32 fec_addr_high;		/* High 16bits MAC address */
	u32 fec_opd;			/* Opcode + Pause duration */
	u32 fec_reserved8[10];
	u32 fec_hash_table_high;	/* High 32bits hash table */
	u32 fec_hash_table_low;		/* Low 32bits hash table */
	u32 fec_grp_hash_table_high;	/* High 32bits hash table */
	u32 fec_grp_hash_table_low;	/* Low 32bits hash table */
	u32 fec_reserved9[7];
	u32 fec_x_wmrk;			/* FIFO transmit water mark */
	u32 fec_reserved10;
	u32 fec_r_bound;		/* FIFO receive bound reg */
	u32 fec_r_fstart;		/* FIFO receive start reg */
	u32 fec_reserved11[11];
	u32 fec_r_des_start;		/* Receive descriptor ring */
	u32 fec_x_des_start;		/* Transmit descriptor ring */
	u32 fec_r_buff_size;		/* Maximum receive buff size */
	u32 fec_reserved12[26];
	u32 fec_dma_control;		/* DMA Endian and other ctrl */
पूर्ण;
#पूर्ण_अगर

काष्ठा fec_info अणु
	काष्ठा fec __iomem *fecp;
	u32 mii_speed;
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPM2
#समावेश <यंत्र/cpm2.h>
#पूर्ण_अगर

/* hw driver ops */
काष्ठा fs_ops अणु
	पूर्णांक (*setup_data)(काष्ठा net_device *dev);
	पूर्णांक (*allocate_bd)(काष्ठा net_device *dev);
	व्योम (*मुक्त_bd)(काष्ठा net_device *dev);
	व्योम (*cleanup_data)(काष्ठा net_device *dev);
	व्योम (*set_multicast_list)(काष्ठा net_device *dev);
	व्योम (*adjust_link)(काष्ठा net_device *dev);
	व्योम (*restart)(काष्ठा net_device *dev);
	व्योम (*stop)(काष्ठा net_device *dev);
	व्योम (*napi_clear_event)(काष्ठा net_device *dev);
	व्योम (*napi_enable)(काष्ठा net_device *dev);
	व्योम (*napi_disable)(काष्ठा net_device *dev);
	व्योम (*rx_bd_करोne)(काष्ठा net_device *dev);
	व्योम (*tx_kickstart)(काष्ठा net_device *dev);
	u32 (*get_पूर्णांक_events)(काष्ठा net_device *dev);
	व्योम (*clear_पूर्णांक_events)(काष्ठा net_device *dev, u32 पूर्णांक_events);
	व्योम (*ev_error)(काष्ठा net_device *dev, u32 पूर्णांक_events);
	पूर्णांक (*get_regs)(काष्ठा net_device *dev, व्योम *p, पूर्णांक *sizep);
	पूर्णांक (*get_regs_len)(काष्ठा net_device *dev);
	व्योम (*tx_restart)(काष्ठा net_device *dev);
पूर्ण;

काष्ठा phy_info अणु
	अचिन्हित पूर्णांक id;
	स्थिर अक्षर *name;
	व्योम (*startup) (काष्ठा net_device * dev);
	व्योम (*shutकरोwn) (काष्ठा net_device * dev);
	व्योम (*ack_पूर्णांक) (काष्ठा net_device * dev);
पूर्ण;

/* The FEC stores dest/src/type, data, and checksum क्रम receive packets.
 */
#घोषणा MAX_MTU 1508		/* Allow fullsized pppoe packets over VLAN */
#घोषणा MIN_MTU 46		/* this is data size */
#घोषणा CRC_LEN 4

#घोषणा PKT_MAXBUF_SIZE		(MAX_MTU+ETH_HLEN+CRC_LEN)
#घोषणा PKT_MINBUF_SIZE		(MIN_MTU+ETH_HLEN+CRC_LEN)

/* Must be a multiple of 32 (to cover both FEC & FCC) */
#घोषणा PKT_MAXBLR_SIZE		((PKT_MAXBUF_SIZE + 31) & ~31)
/* This is needed so that invalidate_xxx wont invalidate too much */
#घोषणा ENET_RX_ALIGN  16
#घोषणा ENET_RX_FRSIZE L1_CACHE_ALIGN(PKT_MAXBUF_SIZE + ENET_RX_ALIGN - 1)

काष्ठा fs_enet_निजी अणु
	काष्ठा napi_काष्ठा napi;
	काष्ठा device *dev;	/* poपूर्णांकer back to the device (must be initialized first) */
	काष्ठा net_device *ndev;
	spinlock_t lock;	/* during all ops except TX pckt processing */
	spinlock_t tx_lock;	/* during fs_start_xmit and fs_tx         */
	काष्ठा fs_platक्रमm_info *fpi;
	काष्ठा work_काष्ठा समयout_work;
	स्थिर काष्ठा fs_ops *ops;
	पूर्णांक rx_ring, tx_ring;
	dma_addr_t ring_mem_addr;
	व्योम __iomem *ring_base;
	काष्ठा sk_buff **rx_skbuff;
	काष्ठा sk_buff **tx_skbuff;
	अक्षर *mapped_as_page;
	cbd_t __iomem *rx_bd_base;	/* Address of Rx and Tx buffers.    */
	cbd_t __iomem *tx_bd_base;
	cbd_t __iomem *dirty_tx;	/* ring entries to be मुक्त()ed.     */
	cbd_t __iomem *cur_rx;
	cbd_t __iomem *cur_tx;
	पूर्णांक tx_मुक्त;
	स्थिर काष्ठा phy_info *phy;
	u32 msg_enable;
	काष्ठा mii_अगर_info mii_अगर;
	अचिन्हित पूर्णांक last_mii_status;
	पूर्णांक पूर्णांकerrupt;

	पूर्णांक oldduplex, oldspeed, oldlink;	/* current settings */

	/* event masks */
	u32 ev_napi;		/* mask of NAPI events */
	u32 ev;			/* event mask          */
	u32 ev_err;		/* error event mask       */

	u16 bd_rx_empty;	/* mask of BD rx empty	  */
	u16 bd_rx_err;		/* mask of BD rx errors   */

	जोड़ अणु
		काष्ठा अणु
			पूर्णांक idx;		/* FEC1 = 0, FEC2 = 1  */
			व्योम __iomem *fecp;	/* hw रेजिस्टरs        */
			u32 hthi, htlo;		/* state क्रम multicast */
		पूर्ण fec;

		काष्ठा अणु
			पूर्णांक idx;		/* FCC1-3 = 0-2	       */
			व्योम __iomem *fccp;	/* hw रेजिस्टरs	       */
			व्योम __iomem *ep;	/* parameter ram       */
			व्योम __iomem *fcccp;	/* hw रेजिस्टरs cont.  */
			व्योम __iomem *mem;	/* FCC DPRAM */
			u32 gaddrh, gaddrl;	/* group address       */
		पूर्ण fcc;

		काष्ठा अणु
			पूर्णांक idx;		/* FEC1 = 0, FEC2 = 1  */
			व्योम __iomem *sccp;	/* hw रेजिस्टरs        */
			व्योम __iomem *ep;	/* parameter ram       */
			u32 hthi, htlo;		/* state क्रम multicast */
		पूर्ण scc;

	पूर्ण;
पूर्ण;

/***************************************************************************/

व्योम fs_init_bds(काष्ठा net_device *dev);
व्योम fs_cleanup_bds(काष्ठा net_device *dev);

/***************************************************************************/

#घोषणा DRV_MODULE_NAME		"fs_enet"
#घोषणा PFX DRV_MODULE_NAME	": "

/***************************************************************************/

पूर्णांक fs_enet_platक्रमm_init(व्योम);
व्योम fs_enet_platक्रमm_cleanup(व्योम);

/***************************************************************************/
/* buffer descriptor access macros */

/* access macros */
#अगर defined(CONFIG_CPM1)
/* क्रम a a CPM1 __raw_xxx's are sufficient */
#घोषणा __cbd_out32(addr, x)	__raw_ग_लिखोl(x, addr)
#घोषणा __cbd_out16(addr, x)	__raw_ग_लिखोw(x, addr)
#घोषणा __cbd_in32(addr)	__raw_पढ़ोl(addr)
#घोषणा __cbd_in16(addr)	__raw_पढ़ोw(addr)
#अन्यथा
/* क्रम others play it safe */
#घोषणा __cbd_out32(addr, x)	out_be32(addr, x)
#घोषणा __cbd_out16(addr, x)	out_be16(addr, x)
#घोषणा __cbd_in32(addr)	in_be32(addr)
#घोषणा __cbd_in16(addr)	in_be16(addr)
#पूर्ण_अगर

/* ग_लिखो */
#घोषणा CBDW_SC(_cbd, _sc) 		__cbd_out16(&(_cbd)->cbd_sc, (_sc))
#घोषणा CBDW_DATLEN(_cbd, _datlen)	__cbd_out16(&(_cbd)->cbd_datlen, (_datlen))
#घोषणा CBDW_BUFADDR(_cbd, _bufaddr)	__cbd_out32(&(_cbd)->cbd_bufaddr, (_bufaddr))

/* पढ़ो */
#घोषणा CBDR_SC(_cbd) 			__cbd_in16(&(_cbd)->cbd_sc)
#घोषणा CBDR_DATLEN(_cbd)		__cbd_in16(&(_cbd)->cbd_datlen)
#घोषणा CBDR_BUFADDR(_cbd)		__cbd_in32(&(_cbd)->cbd_bufaddr)

/* set bits */
#घोषणा CBDS_SC(_cbd, _sc) 		CBDW_SC(_cbd, CBDR_SC(_cbd) | (_sc))

/* clear bits */
#घोषणा CBDC_SC(_cbd, _sc) 		CBDW_SC(_cbd, CBDR_SC(_cbd) & ~(_sc))

/*******************************************************************/

बाह्य स्थिर काष्ठा fs_ops fs_fec_ops;
बाह्य स्थिर काष्ठा fs_ops fs_fcc_ops;
बाह्य स्थिर काष्ठा fs_ops fs_scc_ops;

/*******************************************************************/

#पूर्ण_अगर
