<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_VIO_H
#घोषणा _SPARC64_VIO_H

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/समयr.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/list.h>
#समावेश <linux/log2.h>

#समावेश <यंत्र/ldc.h>
#समावेश <यंत्र/mdesc.h>

काष्ठा vio_msg_tag अणु
	u8			type;
#घोषणा VIO_TYPE_CTRL		0x01
#घोषणा VIO_TYPE_DATA		0x02
#घोषणा VIO_TYPE_ERR		0x04

	u8			stype;
#घोषणा VIO_SUBTYPE_INFO	0x01
#घोषणा VIO_SUBTYPE_ACK		0x02
#घोषणा VIO_SUBTYPE_NACK	0x04

	u16			stype_env;
#घोषणा VIO_VER_INFO		0x0001
#घोषणा VIO_ATTR_INFO		0x0002
#घोषणा VIO_DRING_REG		0x0003
#घोषणा VIO_DRING_UNREG		0x0004
#घोषणा VIO_RDX			0x0005
#घोषणा VIO_PKT_DATA		0x0040
#घोषणा VIO_DESC_DATA		0x0041
#घोषणा VIO_DRING_DATA		0x0042
#घोषणा VNET_MCAST_INFO		0x0101

	u32		sid;
पूर्ण;

काष्ठा vio_rdx अणु
	काष्ठा vio_msg_tag	tag;
	u64			resv[6];
पूर्ण;

काष्ठा vio_ver_info अणु
	काष्ठा vio_msg_tag	tag;
	u16			major;
	u16			minor;
	u8			dev_class;
#घोषणा VDEV_NETWORK		0x01
#घोषणा VDEV_NETWORK_SWITCH	0x02
#घोषणा VDEV_DISK		0x03
#घोषणा VDEV_DISK_SERVER	0x04
#घोषणा VDEV_CONSOLE_CON	0x05

	u8			resv1[3];
	u64			resv2[5];
पूर्ण;

काष्ठा vio_dring_रेजिस्टर अणु
	काष्ठा vio_msg_tag	tag;
	u64			dring_ident;
	u32			num_descr;
	u32			descr_size;
	u16			options;
#घोषणा VIO_TX_DRING		0x0001
#घोषणा VIO_RX_DRING		0x0002
#घोषणा VIO_RX_DRING_DATA	0x0004
	u16			resv;
	u32			num_cookies;
	काष्ठा ldc_trans_cookie	cookies[0];
पूर्ण;

काष्ठा vio_dring_unरेजिस्टर अणु
	काष्ठा vio_msg_tag	tag;
	u64			dring_ident;
	u64			resv[5];
पूर्ण;

/* Data transfer modes */
#घोषणा VIO_PKT_MODE		0x01 /* Packet based transfer	*/
#घोषणा VIO_DESC_MODE		0x02 /* In-band descriptors	*/
#घोषणा VIO_DRING_MODE		0x03 /* Descriptor rings	*/
/* in vers >= 1.2, VIO_DRING_MODE is 0x04 and transfer mode is a biपंचांगask */
#घोषणा VIO_NEW_DRING_MODE	0x04

काष्ठा vio_dring_data अणु
	काष्ठा vio_msg_tag	tag;
	u64			seq;
	u64			dring_ident;
	u32			start_idx;
	u32			end_idx;
	u8			state;
#घोषणा VIO_DRING_ACTIVE	0x01
#घोषणा VIO_DRING_STOPPED	0x02

	u8			__pad1;
	u16			__pad2;
	u32			__pad3;
	u64			__par4[2];
पूर्ण;

काष्ठा vio_dring_hdr अणु
	u8			state;
#घोषणा VIO_DESC_FREE		0x01
#घोषणा VIO_DESC_READY		0x02
#घोषणा VIO_DESC_ACCEPTED	0x03
#घोषणा VIO_DESC_DONE		0x04
	u8			ack;
#घोषणा VIO_ACK_ENABLE		0x01
#घोषणा VIO_ACK_DISABLE		0x00

	u16			__pad1;
	u32			__pad2;
पूर्ण;

/* VIO disk specअगरic काष्ठाures and defines */
काष्ठा vio_disk_attr_info अणु
	काष्ठा vio_msg_tag	tag;
	u8			xfer_mode;
	u8			vdisk_type;
#घोषणा VD_DISK_TYPE_SLICE	0x01 /* Slice in block device	*/
#घोषणा VD_DISK_TYPE_DISK	0x02 /* Entire block device	*/
	u8			vdisk_mtype;		/* v1.1 */
#घोषणा VD_MEDIA_TYPE_FIXED	0x01 /* Fixed device */
#घोषणा VD_MEDIA_TYPE_CD	0x02 /* CD Device    */
#घोषणा VD_MEDIA_TYPE_DVD	0x03 /* DVD Device   */
	u8			resv1;
	u32			vdisk_block_size;
	u64			operations;
	u64			vdisk_size;		/* v1.1 */
	u64			max_xfer_size;
	u32			phys_block_size;	/* v1.2 */
	u32			resv2;
	u64			resv3[1];
पूर्ण;

काष्ठा vio_disk_desc अणु
	काष्ठा vio_dring_hdr	hdr;
	u64			req_id;
	u8			operation;
#घोषणा VD_OP_BREAD		0x01 /* Block पढ़ो			*/
#घोषणा VD_OP_BWRITE		0x02 /* Block ग_लिखो			*/
#घोषणा VD_OP_FLUSH		0x03 /* Flush disk contents		*/
#घोषणा VD_OP_GET_WCE		0x04 /* Get ग_लिखो-cache status		*/
#घोषणा VD_OP_SET_WCE		0x05 /* Enable/disable ग_लिखो-cache	*/
#घोषणा VD_OP_GET_VTOC		0x06 /* Get VTOC			*/
#घोषणा VD_OP_SET_VTOC		0x07 /* Set VTOC			*/
#घोषणा VD_OP_GET_DISKGEOM	0x08 /* Get disk geometry		*/
#घोषणा VD_OP_SET_DISKGEOM	0x09 /* Set disk geometry		*/
#घोषणा VD_OP_SCSICMD		0x0a /* SCSI control command		*/
#घोषणा VD_OP_GET_DEVID		0x0b /* Get device ID			*/
#घोषणा VD_OP_GET_EFI		0x0c /* Get EFI				*/
#घोषणा VD_OP_SET_EFI		0x0d /* Set EFI				*/
	u8			slice;
	u16			resv1;
	u32			status;
	u64			offset;
	u64			size;
	u32			ncookies;
	u32			resv2;
	काष्ठा ldc_trans_cookie	cookies[0];
पूर्ण;

#घोषणा VIO_DISK_VNAME_LEN	8
#घोषणा VIO_DISK_ALABEL_LEN	128
#घोषणा VIO_DISK_NUM_PART	8

काष्ठा vio_disk_vtoc अणु
	u8			volume_name[VIO_DISK_VNAME_LEN];
	u16			sector_size;
	u16			num_partitions;
	u8			ascii_label[VIO_DISK_ALABEL_LEN];
	काष्ठा अणु
		u16		id;
		u16		perm_flags;
		u32		resv;
		u64		start_block;
		u64		num_blocks;
	पूर्ण partitions[VIO_DISK_NUM_PART];
पूर्ण;

काष्ठा vio_disk_geom अणु
	u16			num_cyl; /* Num data cylinders		*/
	u16			alt_cyl; /* Num alternate cylinders	*/
	u16			beg_cyl; /* Cyl off of fixed head area	*/
	u16			num_hd;  /* Num heads			*/
	u16			num_sec; /* Num sectors			*/
	u16			अगरact;   /* Interleave factor		*/
	u16			apc;     /* Alts per cylinder (SCSI)	*/
	u16			rpm;	 /* Revolutions per minute	*/
	u16			phy_cyl; /* Num physical cylinders	*/
	u16			wr_skip; /* Num sects to skip, ग_लिखोs	*/
	u16			rd_skip; /* Num sects to skip, ग_लिखोs	*/
पूर्ण;

काष्ठा vio_disk_devid अणु
	u16			resv;
	u16			type;
	u32			len;
	अक्षर			id[0];
पूर्ण;

काष्ठा vio_disk_efi अणु
	u64			lba;
	u64			len;
	अक्षर			data[0];
पूर्ण;

/* VIO net specअगरic काष्ठाures and defines */
काष्ठा vio_net_attr_info अणु
	काष्ठा vio_msg_tag	tag;
	u8			xfer_mode;
	u8			addr_type;
#घोषणा VNET_ADDR_ETHERMAC	0x01
	u16			ack_freq;
	u8			plnk_updt;
#घोषणा PHYSLINK_UPDATE_NONE		0x00
#घोषणा PHYSLINK_UPDATE_STATE		0x01
#घोषणा PHYSLINK_UPDATE_STATE_ACK	0x02
#घोषणा PHYSLINK_UPDATE_STATE_NACK	0x03
	u8			options;
	u16			resv1;
	u64			addr;
	u64			mtu;
	u16			cflags;
#घोषणा VNET_LSO_IPV4_CAPAB		0x0001
	u16			ipv4_lso_maxlen;
	u32			resv2;
	u64			resv3[2];
पूर्ण;

#घोषणा VNET_NUM_MCAST		7

काष्ठा vio_net_mcast_info अणु
	काष्ठा vio_msg_tag	tag;
	u8			set;
	u8			count;
	u8			mcast_addr[VNET_NUM_MCAST * 6];
	u32			resv;
पूर्ण;

काष्ठा vio_net_desc अणु
	काष्ठा vio_dring_hdr	hdr;
	u32			size;
	u32			ncookies;
	काष्ठा ldc_trans_cookie	cookies[0];
पूर्ण;

काष्ठा vio_net_dext अणु
	u8		flags;
#घोषणा VNET_PKT_HASH			0x01
#घोषणा	VNET_PKT_HCK_IPV4_HDRCKSUM	0x02
#घोषणा	VNET_PKT_HCK_FULLCKSUM		0x04
#घोषणा	VNET_PKT_IPV4_LSO		0x08
#घोषणा	VNET_PKT_HCK_IPV4_HDRCKSUM_OK	0x10
#घोषणा	VNET_PKT_HCK_FULLCKSUM_OK	0x20

	u8		vnet_hashval;
	u16		ipv4_lso_mss;
	u32		resv3;
पूर्ण;

अटल अंतरभूत काष्ठा vio_net_dext *vio_net_ext(काष्ठा vio_net_desc *desc)
अणु
	वापस (काष्ठा vio_net_dext *)&desc->cookies[2];
पूर्ण

#घोषणा VIO_MAX_RING_COOKIES	24

काष्ठा vio_dring_state अणु
	u64			ident;
	व्योम			*base;
	u64			snd_nxt;
	u64			rcv_nxt;
	u32			entry_size;
	u32			num_entries;
	u32			prod;
	u32			cons;
	u32			pending;
	पूर्णांक			ncookies;
	काष्ठा ldc_trans_cookie	cookies[VIO_MAX_RING_COOKIES];
पूर्ण;

#घोषणा VIO_TAG_SIZE		((पूर्णांक)माप(काष्ठा vio_msg_tag))
#घोषणा VIO_VCC_MTU_SIZE	(LDC_PACKET_SIZE - VIO_TAG_SIZE)

काष्ठा vio_vcc अणु
	काष्ठा vio_msg_tag	tag;
	अक्षर			data[VIO_VCC_MTU_SIZE];
पूर्ण;

अटल अंतरभूत व्योम *vio_dring_cur(काष्ठा vio_dring_state *dr)
अणु
	वापस dr->base + (dr->entry_size * dr->prod);
पूर्ण

अटल अंतरभूत व्योम *vio_dring_entry(काष्ठा vio_dring_state *dr,
				    अचिन्हित पूर्णांक index)
अणु
	वापस dr->base + (dr->entry_size * index);
पूर्ण

अटल अंतरभूत u32 vio_dring_avail(काष्ठा vio_dring_state *dr,
				  अचिन्हित पूर्णांक ring_size)
अणु
	वापस (dr->pending -
		((dr->prod - dr->cons) & (ring_size - 1)) - 1);
पूर्ण

अटल अंतरभूत u32 vio_dring_next(काष्ठा vio_dring_state *dr, u32 index)
अणु
	अगर (++index == dr->num_entries)
		index = 0;
	वापस index;
पूर्ण

अटल अंतरभूत u32 vio_dring_prev(काष्ठा vio_dring_state *dr, u32 index)
अणु
	अगर (index == 0)
		वापस dr->num_entries - 1;
	अन्यथा
		वापस index - 1;
पूर्ण

#घोषणा VIO_MAX_TYPE_LEN	32
#घोषणा VIO_MAX_NAME_LEN	32
#घोषणा VIO_MAX_COMPAT_LEN	64

काष्ठा vio_dev अणु
	u64			mp;
	काष्ठा device_node	*dp;

	अक्षर			node_name[VIO_MAX_NAME_LEN];
	अक्षर			type[VIO_MAX_TYPE_LEN];
	अक्षर			compat[VIO_MAX_COMPAT_LEN];
	पूर्णांक			compat_len;

	u64			dev_no;

	अचिन्हित दीर्घ		port_id;
	अचिन्हित दीर्घ		channel_id;

	अचिन्हित पूर्णांक		tx_irq;
	अचिन्हित पूर्णांक		rx_irq;
	u64			rx_ino;
	u64			tx_ino;

	/* Handle to the root of "channel-devices" sub-tree in MDESC */
	u64			cdev_handle;

	/* MD specअगरic data used to identअगरy the vdev in MD */
	जोड़ md_node_info	md_node_info;

	काष्ठा device		dev;
पूर्ण;

काष्ठा vio_driver अणु
	स्थिर अक्षर			*name;
	काष्ठा list_head		node;
	स्थिर काष्ठा vio_device_id	*id_table;
	पूर्णांक (*probe)(काष्ठा vio_dev *dev, स्थिर काष्ठा vio_device_id *id);
	पूर्णांक (*हटाओ)(काष्ठा vio_dev *dev);
	व्योम (*shutकरोwn)(काष्ठा vio_dev *dev);
	अचिन्हित दीर्घ			driver_data;
	काष्ठा device_driver		driver;
	bool				no_irq;
पूर्ण;

काष्ठा vio_version अणु
	u16		major;
	u16		minor;
पूर्ण;

काष्ठा vio_driver_state;
काष्ठा vio_driver_ops अणु
	पूर्णांक	(*send_attr)(काष्ठा vio_driver_state *vio);
	पूर्णांक	(*handle_attr)(काष्ठा vio_driver_state *vio, व्योम *pkt);
	व्योम	(*handshake_complete)(काष्ठा vio_driver_state *vio);
पूर्ण;

काष्ठा vio_completion अणु
	काष्ठा completion	com;
	पूर्णांक			err;
	पूर्णांक			रुकोing_क्रम;
पूर्ण;

काष्ठा vio_driver_state अणु
	/* Protects VIO handshake and, optionally, driver निजी state.  */
	spinlock_t		lock;

	काष्ठा ldc_channel	*lp;

	u32			_peer_sid;
	u32			_local_sid;
	काष्ठा vio_dring_state	drings[2];
#घोषणा VIO_DRIVER_TX_RING	0
#घोषणा VIO_DRIVER_RX_RING	1

	u8			hs_state;
#घोषणा VIO_HS_INVALID		0x00
#घोषणा VIO_HS_GOTVERS		0x01
#घोषणा VIO_HS_GOT_ATTR		0x04
#घोषणा VIO_HS_SENT_DREG	0x08
#घोषणा VIO_HS_SENT_RDX		0x10
#घोषणा VIO_HS_GOT_RDX_ACK	0x20
#घोषणा VIO_HS_GOT_RDX		0x40
#घोषणा VIO_HS_SENT_RDX_ACK	0x80
#घोषणा VIO_HS_COMPLETE		(VIO_HS_GOT_RDX_ACK | VIO_HS_SENT_RDX_ACK)

	u8			dev_class;

	u8			dr_state;
#घोषणा VIO_DR_STATE_TXREG	0x01
#घोषणा VIO_DR_STATE_RXREG	0x02
#घोषणा VIO_DR_STATE_TXREQ	0x10
#घोषणा VIO_DR_STATE_RXREQ	0x20

	u8			debug;
#घोषणा VIO_DEBUG_HS		0x01
#घोषणा VIO_DEBUG_DATA		0x02

	व्योम			*desc_buf;
	अचिन्हित पूर्णांक		desc_buf_len;

	काष्ठा vio_completion	*cmp;

	काष्ठा vio_dev		*vdev;

	काष्ठा समयr_list	समयr;

	काष्ठा vio_version	ver;

	काष्ठा vio_version	*ver_table;
	पूर्णांक			ver_table_entries;

	अक्षर			*name;

	काष्ठा vio_driver_ops	*ops;
पूर्ण;

अटल अंतरभूत bool vio_version_beक्रमe(काष्ठा vio_driver_state *vio,
				      u16 major, u16 minor)
अणु
	u32 have = (u32)vio->ver.major << 16 | vio->ver.minor;
	u32 want = (u32)major << 16 | minor;

	वापस have < want;
पूर्ण

अटल अंतरभूत bool vio_version_after(काष्ठा vio_driver_state *vio,
				      u16 major, u16 minor)
अणु
	u32 have = (u32)vio->ver.major << 16 | vio->ver.minor;
	u32 want = (u32)major << 16 | minor;

	वापस have > want;
पूर्ण

अटल अंतरभूत bool vio_version_after_eq(काष्ठा vio_driver_state *vio,
					u16 major, u16 minor)
अणु
	u32 have = (u32)vio->ver.major << 16 | vio->ver.minor;
	u32 want = (u32)major << 16 | minor;

	वापस have >= want;
पूर्ण

#घोषणा viodbg(TYPE, f, a...) \
करो अणु	अगर (vio->debug & VIO_DEBUG_##TYPE) \
		prपूर्णांकk(KERN_INFO "vio: ID[%lu] " f, \
		       vio->vdev->channel_id, ## a); \
पूर्ण जबतक (0)

पूर्णांक __vio_रेजिस्टर_driver(काष्ठा vio_driver *drv, काष्ठा module *owner,
				 स्थिर अक्षर *mod_name);
/*
 * vio_रेजिस्टर_driver must be a macro so that KBUILD_MODNAME can be expanded
 */
#घोषणा vio_रेजिस्टर_driver(driver)		\
	__vio_रेजिस्टर_driver(driver, THIS_MODULE, KBUILD_MODNAME)
व्योम vio_unरेजिस्टर_driver(काष्ठा vio_driver *drv);

अटल अंतरभूत काष्ठा vio_driver *to_vio_driver(काष्ठा device_driver *drv)
अणु
	वापस container_of(drv, काष्ठा vio_driver, driver);
पूर्ण

अटल अंतरभूत काष्ठा vio_dev *to_vio_dev(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा vio_dev, dev);
पूर्ण

पूर्णांक vio_ldc_send(काष्ठा vio_driver_state *vio, व्योम *data, पूर्णांक len);
व्योम vio_link_state_change(काष्ठा vio_driver_state *vio, पूर्णांक event);
व्योम vio_conn_reset(काष्ठा vio_driver_state *vio);
पूर्णांक vio_control_pkt_engine(काष्ठा vio_driver_state *vio, व्योम *pkt);
पूर्णांक vio_validate_sid(काष्ठा vio_driver_state *vio,
		     काष्ठा vio_msg_tag *tp);
u32 vio_send_sid(काष्ठा vio_driver_state *vio);
पूर्णांक vio_ldc_alloc(काष्ठा vio_driver_state *vio,
		  काष्ठा ldc_channel_config *base_cfg, व्योम *event_arg);
व्योम vio_ldc_मुक्त(काष्ठा vio_driver_state *vio);
पूर्णांक vio_driver_init(काष्ठा vio_driver_state *vio, काष्ठा vio_dev *vdev,
		    u8 dev_class, काष्ठा vio_version *ver_table,
		    पूर्णांक ver_table_size, काष्ठा vio_driver_ops *ops,
		    अक्षर *name);

व्योम vio_port_up(काष्ठा vio_driver_state *vio);
पूर्णांक vio_set_पूर्णांकr(अचिन्हित दीर्घ dev_ino, पूर्णांक state);
u64 vio_vdev_node(काष्ठा mdesc_handle *hp, काष्ठा vio_dev *vdev);

#पूर्ण_अगर /* _SPARC64_VIO_H */
