<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FORE200E_H
#घोषणा _FORE200E_H

#अगर_घोषित __KERNEL__

/* rx buffer sizes */

#घोषणा SMALL_BUFFER_SIZE    384     /* size of small buffers (multiple of 48 (PCA) and 64 (SBA) bytes) */
#घोषणा LARGE_BUFFER_SIZE    4032    /* size of large buffers (multiple of 48 (PCA) and 64 (SBA) bytes) */


#घोषणा RBD_BLK_SIZE	     32      /* nbr of supplied rx buffers per rbd */


#घोषणा MAX_PDU_SIZE	     65535   /* maximum PDU size supported by AALs */


#घोषणा BUFFER_S1_SIZE       SMALL_BUFFER_SIZE    /* size of small buffers, scheme 1 */
#घोषणा BUFFER_L1_SIZE       LARGE_BUFFER_SIZE    /* size of large buffers, scheme 1 */

#घोषणा BUFFER_S2_SIZE       SMALL_BUFFER_SIZE    /* size of small buffers, scheme 2 */
#घोषणा BUFFER_L2_SIZE       LARGE_BUFFER_SIZE    /* size of large buffers, scheme 2 */

#घोषणा BUFFER_S1_NBR        (RBD_BLK_SIZE * 6)
#घोषणा BUFFER_L1_NBR        (RBD_BLK_SIZE * 4)

#घोषणा BUFFER_S2_NBR        (RBD_BLK_SIZE * 6)
#घोषणा BUFFER_L2_NBR        (RBD_BLK_SIZE * 4)


#घोषणा QUEUE_SIZE_CMD       16	     /* command queue capacity       */
#घोषणा QUEUE_SIZE_RX	     64	     /* receive queue capacity       */
#घोषणा QUEUE_SIZE_TX	     256     /* transmit queue capacity      */
#घोषणा QUEUE_SIZE_BS        32	     /* buffer supply queue capacity */

#घोषणा FORE200E_VPI_BITS     0
#घोषणा FORE200E_VCI_BITS    10
#घोषणा NBR_CONNECT          (1 << (FORE200E_VPI_BITS + FORE200E_VCI_BITS)) /* number of connections */


#घोषणा TSD_FIXED            2
#घोषणा TSD_EXTENSION        0
#घोषणा TSD_NBR              (TSD_FIXED + TSD_EXTENSION)


/* the cp starts putting a received PDU पूर्णांकo one *small* buffer,
   then it uses a number of *large* buffers क्रम the trailing data. 
   we compute here the total number of receive segment descriptors 
   required to hold the largest possible PDU */

#घोषणा RSD_REQUIRED  (((MAX_PDU_SIZE - SMALL_BUFFER_SIZE + LARGE_BUFFER_SIZE) / LARGE_BUFFER_SIZE) + 1)

#घोषणा RSD_FIXED     3

/* RSD_REQUIRED receive segment descriptors are enough to describe a max-sized PDU,
   but we have to keep the size of the receive PDU descriptor multiple of 32 bytes,
   so we add one extra RSD to RSD_EXTENSION 
   (WARNING: THIS MAY CHANGE IF BUFFER SIZES ARE MODIFIED) */

#घोषणा RSD_EXTENSION  ((RSD_REQUIRED - RSD_FIXED) + 1)
#घोषणा RSD_NBR         (RSD_FIXED + RSD_EXTENSION)


#घोषणा FORE200E_DEV(d)          ((काष्ठा क्रमe200e*)((d)->dev_data))
#घोषणा FORE200E_VCC(d)          ((काष्ठा क्रमe200e_vcc*)((d)->dev_data))

/* bitfields endian games */

#अगर defined(__LITTLE_ENDIAN_BITFIELD)
#घोषणा BITFIELD2(b1, b2)                    b1; b2;
#घोषणा BITFIELD3(b1, b2, b3)                b1; b2; b3;
#घोषणा BITFIELD4(b1, b2, b3, b4)            b1; b2; b3; b4;
#घोषणा BITFIELD5(b1, b2, b3, b4, b5)        b1; b2; b3; b4; b5;
#घोषणा BITFIELD6(b1, b2, b3, b4, b5, b6)    b1; b2; b3; b4; b5; b6;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
#घोषणा BITFIELD2(b1, b2)                                    b2; b1;
#घोषणा BITFIELD3(b1, b2, b3)                            b3; b2; b1;
#घोषणा BITFIELD4(b1, b2, b3, b4)                    b4; b3; b2; b1;
#घोषणा BITFIELD5(b1, b2, b3, b4, b5)            b5; b4; b3; b2; b1;
#घोषणा BITFIELD6(b1, b2, b3, b4, b5, b6)    b6; b5; b4; b3; b2; b1;
#अन्यथा
#त्रुटि unknown bitfield endianess
#पूर्ण_अगर

 
/* ATM cell header (minus HEC byte) */

प्रकार काष्ठा aपंचांग_header अणु
    BITFIELD5( 
        u32 clp :  1,    /* cell loss priority         */
        u32 plt :  3,    /* payload type               */
        u32 vci : 16,    /* भव channel identअगरier */
        u32 vpi :  8,    /* भव path identअगरier    */
        u32 gfc :  4     /* generic flow control       */
   )
पूर्ण aपंचांग_header_t;


/* ATM adaptation layer id */

प्रकार क्रमागत क्रमe200e_aal अणु
    FORE200E_AAL0  = 0,
    FORE200E_AAL34 = 4,
    FORE200E_AAL5  = 5,
पूर्ण क्रमe200e_aal_t;


/* transmit PDU descriptor specअगरication */

प्रकार काष्ठा tpd_spec अणु
    BITFIELD4(
        u32               length : 16,    /* total PDU length            */
        u32               nseg   :  8,    /* number of transmit segments */
        क्रमागत क्रमe200e_aal aal    :  4,    /* adaptation layer            */
        u32               पूर्णांकr   :  4     /* पूर्णांकerrupt requested         */
    )
पूर्ण tpd_spec_t;


/* transmit PDU rate control */

प्रकार काष्ठा tpd_rate
अणु
    BITFIELD2( 
        u32 idle_cells : 16,    /* number of idle cells to insert   */
        u32 data_cells : 16     /* number of data cells to transmit */
    )
पूर्ण tpd_rate_t;


/* transmit segment descriptor */

प्रकार काष्ठा tsd अणु
    u32 buffer;    /* transmit buffer DMA address */
    u32 length;    /* number of bytes in buffer   */
पूर्ण tsd_t;


/* transmit PDU descriptor */

प्रकार काष्ठा tpd अणु
    काष्ठा aपंचांग_header aपंचांग_header;        /* ATM header minus HEC byte    */
    काष्ठा tpd_spec   spec;              /* tpd specअगरication            */
    काष्ठा tpd_rate   rate;              /* tpd rate control             */
    u32               pad;               /* reserved                     */
    काष्ठा tsd        tsd[ TSD_NBR ];    /* transmit segment descriptors */
पूर्ण tpd_t;


/* receive segment descriptor */

प्रकार काष्ठा rsd अणु
    u32 handle;    /* host supplied receive buffer handle */
    u32 length;    /* number of bytes in buffer           */
पूर्ण rsd_t;


/* receive PDU descriptor */

प्रकार काष्ठा rpd अणु
    काष्ठा aपंचांग_header aपंचांग_header;        /* ATM header minus HEC byte   */
    u32               nseg;              /* number of receive segments  */
    काष्ठा rsd        rsd[ RSD_NBR ];    /* receive segment descriptors */
पूर्ण rpd_t;


/* buffer scheme */

प्रकार क्रमागत buffer_scheme अणु
    BUFFER_SCHEME_ONE,
    BUFFER_SCHEME_TWO,
    BUFFER_SCHEME_NBR    /* always last */
पूर्ण buffer_scheme_t;


/* buffer magnitude */

प्रकार क्रमागत buffer_magn अणु
    BUFFER_MAGN_SMALL,
    BUFFER_MAGN_LARGE,
    BUFFER_MAGN_NBR    /* always last */
पूर्ण buffer_magn_t;


/* receive buffer descriptor */

प्रकार काष्ठा rbd अणु
    u32 handle;          /* host supplied handle            */
    u32 buffer_haddr;    /* host DMA address of host buffer */
पूर्ण rbd_t;


/* receive buffer descriptor block */

प्रकार काष्ठा rbd_block अणु
    काष्ठा rbd rbd[ RBD_BLK_SIZE ];    /* receive buffer descriptor */
पूर्ण rbd_block_t;


/* tpd DMA address */

प्रकार काष्ठा tpd_haddr अणु
    BITFIELD3( 
        u32 size  :  4,    /* tpd size expressed in 32 byte blocks     */
        u32 pad   :  1,    /* reserved                                 */
        u32 haddr : 27     /* tpd DMA addr aligned on 32 byte boundary */
    )
पूर्ण tpd_haddr_t;

#घोषणा TPD_HADDR_SHIFT 5  /* addr aligned on 32 byte boundary */

/* cp resident transmit queue entry */

प्रकार काष्ठा cp_txq_entry अणु
    काष्ठा tpd_haddr tpd_haddr;       /* host DMA address of tpd                */
    u32              status_haddr;    /* host DMA address of completion status  */
पूर्ण cp_txq_entry_t;


/* cp resident receive queue entry */

प्रकार काष्ठा cp_rxq_entry अणु
    u32 rpd_haddr;       /* host DMA address of rpd                */
    u32 status_haddr;    /* host DMA address of completion status  */
पूर्ण cp_rxq_entry_t;


/* cp resident buffer supply queue entry */

प्रकार काष्ठा cp_bsq_entry अणु
    u32 rbd_block_haddr;    /* host DMA address of rbd block          */
    u32 status_haddr;       /* host DMA address of completion status  */
पूर्ण cp_bsq_entry_t;


/* completion status */

प्रकार अस्थिर क्रमागत status अणु
    STATUS_PENDING  = (1<<0),    /* initial status (written by host)  */
    STATUS_COMPLETE = (1<<1),    /* completion status (written by cp) */
    STATUS_FREE     = (1<<2),    /* initial status (written by host)  */
    STATUS_ERROR    = (1<<3)     /* completion status (written by cp) */
पूर्ण status_t;


/* cp operation code */

प्रकार क्रमागत opcode अणु
    OPCODE_INITIALIZE = 1,          /* initialize board                       */
    OPCODE_ACTIVATE_VCIN,           /* activate incoming VCI                  */
    OPCODE_ACTIVATE_VCOUT,          /* activate outgoing VCI                  */
    OPCODE_DEACTIVATE_VCIN,         /* deactivate incoming VCI                */
    OPCODE_DEACTIVATE_VCOUT,        /* deactivate incoing VCI                 */
    OPCODE_GET_STATS,               /* get board statistics                   */
    OPCODE_SET_OC3,                 /* set OC-3 रेजिस्टरs                     */
    OPCODE_GET_OC3,                 /* get OC-3 रेजिस्टरs                     */
    OPCODE_RESET_STATS,             /* reset board statistics                 */
    OPCODE_GET_PROM,                /* get expansion PROM data (PCI specअगरic) */
    OPCODE_SET_VPI_BITS,            /* set x bits of those decoded by the
				       firmware to be low order bits from
				       the VPI field of the ATM cell header   */
    OPCODE_REQUEST_INTR = (1<<7)    /* request पूर्णांकerrupt                      */
पूर्ण opcode_t;


/* भव path / भव channel identअगरiers */

प्रकार काष्ठा vpvc अणु
    BITFIELD3(
        u32 vci : 16,    /* भव channel identअगरier */
        u32 vpi :  8,    /* भव path identअगरier    */
        u32 pad :  8     /* reserved                   */
    )
पूर्ण vpvc_t;


/* activate VC command opcode */

प्रकार काष्ठा activate_opcode अणु
    BITFIELD4( 
        क्रमागत opcode        opcode : 8,    /* cp opcode        */
        क्रमागत क्रमe200e_aal  aal    : 8,    /* adaptation layer */
        क्रमागत buffer_scheme scheme : 8,    /* buffer scheme    */
        u32  pad                  : 8     /* reserved         */
   )
पूर्ण activate_opcode_t;


/* activate VC command block */

प्रकार काष्ठा activate_block अणु
    काष्ठा activate_opcode  opcode;    /* activate VC command opcode */
    काष्ठा vpvc             vpvc;      /* VPI/VCI                    */
    u32                     mtu;       /* क्रम AAL0 only              */

पूर्ण activate_block_t;


/* deactivate VC command opcode */

प्रकार काष्ठा deactivate_opcode अणु
    BITFIELD2(
        क्रमागत opcode opcode :  8,    /* cp opcode */
        u32         pad    : 24     /* reserved  */
    )
पूर्ण deactivate_opcode_t;


/* deactivate VC command block */

प्रकार काष्ठा deactivate_block अणु
    काष्ठा deactivate_opcode opcode;    /* deactivate VC command opcode */
    काष्ठा vpvc              vpvc;      /* VPI/VCI                      */
पूर्ण deactivate_block_t;


/* OC-3 रेजिस्टरs */

प्रकार काष्ठा oc3_regs अणु
    u32 reg[ 128 ];    /* see the PMC Sierra PC5346 S/UNI-155-Lite
			  Saturn User Network Interface करोcumentation
			  क्रम a description of the OC-3 chip रेजिस्टरs */
पूर्ण oc3_regs_t;


/* set/get OC-3 regs command opcode */

प्रकार काष्ठा oc3_opcode अणु
    BITFIELD4(
        क्रमागत opcode opcode : 8,    /* cp opcode                           */
	u32         reg    : 8,    /* रेजिस्टर index                      */
	u32         value  : 8,    /* रेजिस्टर value                      */
	u32         mask   : 8     /* रेजिस्टर mask that specअगरies which
				      bits of the रेजिस्टर value field
				      are signअगरicant                     */
    )
पूर्ण oc3_opcode_t;


/* set/get OC-3 regs command block */

प्रकार काष्ठा oc3_block अणु
    काष्ठा oc3_opcode opcode;        /* set/get OC-3 regs command opcode     */
    u32               regs_haddr;    /* host DMA address of OC-3 regs buffer */
पूर्ण oc3_block_t;


/* physical encoding statistics */

प्रकार काष्ठा stats_phy अणु
    __be32 crc_header_errors;    /* cells received with bad header CRC */
    __be32 framing_errors;       /* cells received with bad framing    */
    __be32 pad[ 2 ];             /* i960 padding                       */
पूर्ण stats_phy_t;


/* OC-3 statistics */

प्रकार काष्ठा stats_oc3 अणु
    __be32 section_bip8_errors;    /* section 8 bit पूर्णांकerleaved parity    */
    __be32 path_bip8_errors;       /* path 8 bit पूर्णांकerleaved parity       */
    __be32 line_bip24_errors;      /* line 24 bit पूर्णांकerleaved parity      */
    __be32 line_febe_errors;       /* line far end block errors           */
    __be32 path_febe_errors;       /* path far end block errors           */
    __be32 corr_hcs_errors;        /* correctable header check sequence   */
    __be32 ucorr_hcs_errors;       /* uncorrectable header check sequence */
    __be32 pad[ 1 ];               /* i960 padding                        */
पूर्ण stats_oc3_t;


/* ATM statistics */

प्रकार काष्ठा stats_aपंचांग अणु
    __be32	cells_transmitted;    /* cells transmitted                 */
    __be32	cells_received;       /* cells received                    */
    __be32	vpi_bad_range;        /* cell drops: VPI out of range      */
    __be32	vpi_no_conn;          /* cell drops: no connection क्रम VPI */
    __be32	vci_bad_range;        /* cell drops: VCI out of range      */
    __be32	vci_no_conn;          /* cell drops: no connection क्रम VCI */
    __be32	pad[ 2 ];             /* i960 padding                      */
पूर्ण stats_aपंचांग_t;

/* AAL0 statistics */

प्रकार काष्ठा stats_aal0 अणु
    __be32	cells_transmitted;    /* cells transmitted */
    __be32	cells_received;       /* cells received    */
    __be32	cells_dropped;        /* cells dropped     */
    __be32	pad[ 1 ];             /* i960 padding      */
पूर्ण stats_aal0_t;


/* AAL3/4 statistics */

प्रकार काष्ठा stats_aal34 अणु
    __be32	cells_transmitted;         /* cells transmitted from segmented PDUs */
    __be32	cells_received;            /* cells reassembled पूर्णांकo PDUs           */
    __be32	cells_crc_errors;          /* payload CRC error count               */
    __be32	cells_protocol_errors;     /* SAR or CS layer protocol errors       */
    __be32	cells_dropped;             /* cells dropped: partial reassembly     */
    __be32	cspdus_transmitted;        /* CS PDUs transmitted                   */
    __be32	cspdus_received;           /* CS PDUs received                      */
    __be32	cspdus_protocol_errors;    /* CS layer protocol errors              */
    __be32	cspdus_dropped;            /* reassembled PDUs drop'd (in cells)    */
    __be32	pad[ 3 ];                  /* i960 padding                          */
पूर्ण stats_aal34_t;


/* AAL5 statistics */

प्रकार काष्ठा stats_aal5 अणु
    __be32	cells_transmitted;         /* cells transmitted from segmented SDUs */
    __be32	cells_received;		   /* cells reassembled पूर्णांकo SDUs           */
    __be32	cells_dropped;		   /* reassembled PDUs dropped (in cells)   */
    __be32	congestion_experienced;    /* CRC error and length wrong            */
    __be32	cspdus_transmitted;        /* CS PDUs transmitted                   */
    __be32	cspdus_received;           /* CS PDUs received                      */
    __be32	cspdus_crc_errors;         /* CS PDUs CRC errors                    */
    __be32	cspdus_protocol_errors;    /* CS layer protocol errors              */
    __be32	cspdus_dropped;            /* reassembled PDUs dropped              */
    __be32	pad[ 3 ];                  /* i960 padding                          */
पूर्ण stats_aal5_t;


/* auxiliary statistics */

प्रकार काष्ठा stats_aux अणु
    __be32	small_b1_failed;     /* receive BD allocation failures  */
    __be32	large_b1_failed;     /* receive BD allocation failures  */
    __be32	small_b2_failed;     /* receive BD allocation failures  */
    __be32	large_b2_failed;     /* receive BD allocation failures  */
    __be32	rpd_alloc_failed;    /* receive PDU allocation failures */
    __be32	receive_carrier;     /* no carrier = 0, carrier = 1     */
    __be32	pad[ 2 ];            /* i960 padding                    */
पूर्ण stats_aux_t;


/* whole statistics buffer */

प्रकार काष्ठा stats अणु
    काष्ठा stats_phy   phy;      /* physical encoding statistics */
    काष्ठा stats_oc3   oc3;      /* OC-3 statistics              */
    काष्ठा stats_aपंचांग   aपंचांग;      /* ATM statistics               */
    काष्ठा stats_aal0  aal0;     /* AAL0 statistics              */
    काष्ठा stats_aal34 aal34;    /* AAL3/4 statistics            */
    काष्ठा stats_aal5  aal5;     /* AAL5 statistics              */
    काष्ठा stats_aux   aux;      /* auxiliary statistics         */
पूर्ण stats_t;


/* get statistics command opcode */

प्रकार काष्ठा stats_opcode अणु
    BITFIELD2(
        क्रमागत opcode opcode :  8,    /* cp opcode */
        u32         pad    : 24     /* reserved  */
    )
पूर्ण stats_opcode_t;


/* get statistics command block */

प्रकार काष्ठा stats_block अणु
    काष्ठा stats_opcode opcode;         /* get statistics command opcode    */
    u32                 stats_haddr;    /* host DMA address of stats buffer */
पूर्ण stats_block_t;


/* expansion PROM data (PCI specअगरic) */

प्रकार काष्ठा prom_data अणु
    u32 hw_revision;      /* hardware revision   */
    u32 serial_number;    /* board serial number */
    u8  mac_addr[ 8 ];    /* board MAC address   */
पूर्ण prom_data_t;


/* get expansion PROM data command opcode */

प्रकार काष्ठा prom_opcode अणु
    BITFIELD2(
        क्रमागत opcode opcode :  8,    /* cp opcode */
        u32         pad    : 24     /* reserved  */
    )
पूर्ण prom_opcode_t;


/* get expansion PROM data command block */

प्रकार काष्ठा prom_block अणु
    काष्ठा prom_opcode opcode;        /* get PROM data command opcode    */
    u32                prom_haddr;    /* host DMA address of PROM buffer */
पूर्ण prom_block_t;


/* cp command */

प्रकार जोड़ cmd अणु
    क्रमागत   opcode           opcode;           /* operation code          */
    काष्ठा activate_block   activate_block;   /* activate VC             */
    काष्ठा deactivate_block deactivate_block; /* deactivate VC           */
    काष्ठा stats_block      stats_block;      /* get statistics          */
    काष्ठा prom_block       prom_block;       /* get expansion PROM data */
    काष्ठा oc3_block        oc3_block;        /* get/set OC-3 रेजिस्टरs  */
    u32                     pad[ 4 ];         /* i960 padding            */
पूर्ण cmd_t;


/* cp resident command queue */

प्रकार काष्ठा cp_cmdq_entry अणु
    जोड़ cmd cmd;             /* command                               */
    u32       status_haddr;    /* host DMA address of completion status */
    u32       pad[ 3 ];        /* i960 padding                          */
पूर्ण cp_cmdq_entry_t;


/* host resident transmit queue entry */

प्रकार काष्ठा host_txq_entry अणु
    काष्ठा cp_txq_entry __iomem *cp_entry;    /* addr of cp resident tx queue entry       */
    क्रमागत   status*          status;      /* addr of host resident status             */
    काष्ठा tpd*             tpd;         /* addr of transmit PDU descriptor          */
    u32                     tpd_dma;     /* DMA address of tpd                       */
    काष्ठा sk_buff*         skb;         /* related skb                              */
    व्योम*                   data;        /* copy of misaligned data                  */
    अचिन्हित दीर्घ           incarn;      /* vc_map incarnation when submitted क्रम tx */
    काष्ठा क्रमe200e_vc_map* vc_map;

पूर्ण host_txq_entry_t;


/* host resident receive queue entry */

प्रकार काष्ठा host_rxq_entry अणु
    काष्ठा cp_rxq_entry __iomem *cp_entry;    /* addr of cp resident rx queue entry */
    क्रमागत   status*       status;      /* addr of host resident status       */
    काष्ठा rpd*          rpd;         /* addr of receive PDU descriptor     */
    u32                  rpd_dma;     /* DMA address of rpd                 */
पूर्ण host_rxq_entry_t;


/* host resident buffer supply queue entry */

प्रकार काष्ठा host_bsq_entry अणु
    काष्ठा cp_bsq_entry __iomem *cp_entry;         /* addr of cp resident buffer supply queue entry */
    क्रमागत   status*       status;           /* addr of host resident status                  */
    काष्ठा rbd_block*    rbd_block;        /* addr of receive buffer descriptor block       */
    u32                  rbd_block_dma;    /* DMA address od rdb                            */
पूर्ण host_bsq_entry_t;


/* host resident command queue entry */

प्रकार काष्ठा host_cmdq_entry अणु
    काष्ठा cp_cmdq_entry __iomem *cp_entry;    /* addr of cp resident cmd queue entry */
    क्रमागत status *status;	       /* addr of host resident status        */
पूर्ण host_cmdq_entry_t;


/* chunk of memory */

प्रकार काष्ठा chunk अणु
    व्योम* alloc_addr;    /* base address of allocated chunk */
    व्योम* align_addr;    /* base address of aligned chunk   */
    dma_addr_t dma_addr; /* DMA address of aligned chunk    */
    पूर्णांक   direction;     /* direction of DMA mapping        */
    u32   alloc_size;    /* length of allocated chunk       */
    u32   align_size;    /* length of aligned chunk         */
पूर्ण chunk_t;

#घोषणा dma_size align_size             /* DMA useable size */


/* host resident receive buffer */

प्रकार काष्ठा buffer अणु
    काष्ठा buffer*       next;        /* next receive buffer     */
    क्रमागत   buffer_scheme scheme;      /* buffer scheme           */
    क्रमागत   buffer_magn   magn;        /* buffer magnitude        */
    काष्ठा chunk         data;        /* data buffer             */
#अगर_घोषित FORE200E_BSQ_DEBUG
    अचिन्हित दीर्घ        index;       /* buffer # in queue       */
    पूर्णांक                  supplied;    /* 'buffer supplied' flag  */
#पूर्ण_अगर
पूर्ण buffer_t;


#अगर (BITS_PER_LONG == 32)
#घोषणा FORE200E_BUF2HDL(buffer)    ((u32)(buffer))
#घोषणा FORE200E_HDL2BUF(handle)    ((काष्ठा buffer*)(handle))
#अन्यथा   /* deal with 64 bit poपूर्णांकers */
#घोषणा FORE200E_BUF2HDL(buffer)    ((u32)((u64)(buffer)))
#घोषणा FORE200E_HDL2BUF(handle)    ((काष्ठा buffer*)(((u64)(handle)) | PAGE_OFFSET))
#पूर्ण_अगर


/* host resident command queue */

प्रकार काष्ठा host_cmdq अणु
    काष्ठा host_cmdq_entry host_entry[ QUEUE_SIZE_CMD ];    /* host resident cmd queue entries        */
    पूर्णांक                    head;                            /* head of cmd queue                      */
    काष्ठा chunk           status;                          /* array of completion status      */
पूर्ण host_cmdq_t;


/* host resident transmit queue */

प्रकार काष्ठा host_txq अणु
    काष्ठा host_txq_entry host_entry[ QUEUE_SIZE_TX ];    /* host resident tx queue entries         */
    पूर्णांक                   head;                           /* head of tx queue                       */
    पूर्णांक                   tail;                           /* tail of tx queue                       */
    काष्ठा chunk          tpd;                            /* array of tpds                          */
    काष्ठा chunk          status;                         /* arry of completion status              */
    पूर्णांक                   txing;                          /* number of pending PDUs in tx queue     */
पूर्ण host_txq_t;


/* host resident receive queue */

प्रकार काष्ठा host_rxq अणु
    काष्ठा host_rxq_entry  host_entry[ QUEUE_SIZE_RX ];    /* host resident rx queue entries         */
    पूर्णांक                    head;                           /* head of rx queue                       */
    काष्ठा chunk           rpd;                            /* array of rpds                          */
    काष्ठा chunk           status;                         /* array of completion status             */
पूर्ण host_rxq_t;


/* host resident buffer supply queues */

प्रकार काष्ठा host_bsq अणु
    काष्ठा host_bsq_entry host_entry[ QUEUE_SIZE_BS ];    /* host resident buffer supply queue entries */
    पूर्णांक                   head;                           /* head of buffer supply queue               */
    काष्ठा chunk          rbd_block;                      /* array of rbds                             */
    काष्ठा chunk          status;                         /* array of completion status                */
    काष्ठा buffer*        buffer;                         /* array of rx buffers                       */
    काष्ठा buffer*        मुक्तbuf;                        /* list of मुक्त rx buffers                   */
    अस्थिर पूर्णांक          मुक्तbuf_count;                  /* count of मुक्त rx buffers                  */
पूर्ण host_bsq_t;


/* header of the firmware image */

प्रकार काष्ठा fw_header अणु
    __le32 magic;           /* magic number                               */
    __le32 version;         /* firmware version id                        */
    __le32 load_offset;     /* fw load offset in board memory             */
    __le32 start_offset;    /* fw execution start address in board memory */
पूर्ण fw_header_t;

#घोषणा FW_HEADER_MAGIC  0x65726f66    /* 'fore' */


/* receive buffer supply queues scheme specअगरication */

प्रकार काष्ठा bs_spec अणु
    u32	queue_length;      /* queue capacity                     */
    u32	buffer_size;	   /* host buffer size			 */
    u32	pool_size;	   /* number of rbds			 */
    u32	supply_blksize;    /* num of rbds in I/O block (multiple
			      of 4 between 4 and 124 inclusive)	 */
पूर्ण bs_spec_t;


/* initialization command block (one-समय command, not in cmd queue) */

प्रकार काष्ठा init_block अणु
    क्रमागत opcode  opcode;               /* initialize command             */
    क्रमागत status	 status;	       /* related status word            */
    u32          receive_threshold;    /* not used                       */
    u32          num_connect;          /* ATM connections                */
    u32          cmd_queue_len;        /* length of command queue        */
    u32          tx_queue_len;         /* length of transmit queue       */
    u32          rx_queue_len;         /* length of receive queue        */
    u32          rsd_extension;        /* number of extra 32 byte blocks */
    u32          tsd_extension;        /* number of extra 32 byte blocks */
    u32          conless_vpvc;         /* not used                       */
    u32          pad[ 2 ];             /* क्रमce quad alignment           */
    काष्ठा bs_spec bs_spec[ BUFFER_SCHEME_NBR ][ BUFFER_MAGN_NBR ];      /* buffer supply queues spec */
पूर्ण init_block_t;


प्रकार क्रमागत media_type अणु
    MEDIA_TYPE_CAT5_UTP  = 0x06,    /* unshielded twisted pair */
    MEDIA_TYPE_MM_OC3_ST = 0x16,    /* multimode fiber ST      */
    MEDIA_TYPE_MM_OC3_SC = 0x26,    /* multimode fiber SC      */
    MEDIA_TYPE_SM_OC3_ST = 0x36,    /* single-mode fiber ST    */
    MEDIA_TYPE_SM_OC3_SC = 0x46     /* single-mode fiber SC    */
पूर्ण media_type_t;

#घोषणा FORE200E_MEDIA_INDEX(media_type)   ((media_type)>>4)


/* cp resident queues */

प्रकार काष्ठा cp_queues अणु
    u32	              cp_cmdq;         /* command queue                      */
    u32	              cp_txq;          /* transmit queue                     */
    u32	              cp_rxq;          /* receive queue                      */
    u32               cp_bsq[ BUFFER_SCHEME_NBR ][ BUFFER_MAGN_NBR ];        /* buffer supply queues */
    u32	              imask;             /* 1 enables cp to host पूर्णांकerrupts  */
    u32	              istat;             /* 1 क्रम पूर्णांकerrupt posted           */
    u32	              heap_base;         /* offset क्रमm beginning of ram     */
    u32	              heap_size;         /* space available क्रम queues       */
    u32	              hlogger;           /* non zero क्रम host logging        */
    u32               heartbeat;         /* cp heartbeat                     */
    u32	              fw_release;        /* firmware version                 */
    u32	              mon960_release;    /* i960 monitor version             */
    u32	              tq_plen;           /* transmit throughput measurements */
    /* make sure the init block reमुख्यs on a quad word boundary              */
    काष्ठा init_block init;              /* one समय cmd, not in cmd queue   */
    क्रमागत   media_type media_type;        /* media type id                    */
    u32               oc3_revision;      /* OC-3 revision number             */
पूर्ण cp_queues_t;


/* boot status */

प्रकार क्रमागत boot_status अणु
    BSTAT_COLD_START    = (u32) 0xc01dc01d,    /* cold start              */
    BSTAT_SELFTEST_OK   = (u32) 0x02201958,    /* self-test ok            */
    BSTAT_SELFTEST_FAIL = (u32) 0xadbadbad,    /* self-test failed        */
    BSTAT_CP_RUNNING    = (u32) 0xce11feed,    /* cp is running           */
    BSTAT_MON_TOO_BIG   = (u32) 0x10aded00     /* i960 monitor is too big */
पूर्ण boot_status_t;


/* software UART */

प्रकार काष्ठा soft_uart अणु
    u32 send;    /* ग_लिखो रेजिस्टर */
    u32 recv;    /* पढ़ो रेजिस्टर  */
पूर्ण soft_uart_t;

#घोषणा FORE200E_CP_MONITOR_UART_FREE     0x00000000
#घोषणा FORE200E_CP_MONITOR_UART_AVAIL    0x01000000


/* i960 monitor */

प्रकार काष्ठा cp_monitor अणु
    काष्ठा soft_uart    soft_uart;      /* software UART           */
    क्रमागत boot_status	bstat;          /* boot status             */
    u32			app_base;       /* application base offset */
    u32			mon_version;    /* i960 monitor version    */
पूर्ण cp_monitor_t;


/* device state */

प्रकार क्रमागत क्रमe200e_state अणु
    FORE200E_STATE_BLANK,         /* initial state                     */
    FORE200E_STATE_REGISTER,      /* device रेजिस्टरed                 */
    FORE200E_STATE_CONFIGURE,     /* bus पूर्णांकerface configured          */
    FORE200E_STATE_MAP,           /* board space mapped in host memory */
    FORE200E_STATE_RESET,         /* board resetted                    */
    FORE200E_STATE_START_FW,      /* firmware started                  */
    FORE200E_STATE_INITIALIZE,    /* initialize command successful     */
    FORE200E_STATE_INIT_CMDQ,     /* command queue initialized         */
    FORE200E_STATE_INIT_TXQ,      /* transmit queue initialized        */
    FORE200E_STATE_INIT_RXQ,      /* receive queue initialized         */
    FORE200E_STATE_INIT_BSQ,      /* buffer supply queue initialized   */
    FORE200E_STATE_ALLOC_BUF,     /* receive buffers allocated         */
    FORE200E_STATE_IRQ,           /* host पूर्णांकerrupt requested          */
    FORE200E_STATE_COMPLETE       /* initialization completed          */
पूर्ण क्रमe200e_state;


/* PCA-200E रेजिस्टरs */

प्रकार काष्ठा क्रमe200e_pca_regs अणु
    अस्थिर u32 __iomem * hcr;    /* address of host control रेजिस्टर        */
    अस्थिर u32 __iomem * imr;    /* address of host पूर्णांकerrupt mask रेजिस्टर */
    अस्थिर u32 __iomem * psr;    /* address of PCI specअगरic रेजिस्टर        */
पूर्ण क्रमe200e_pca_regs_t;


/* SBA-200E रेजिस्टरs */

प्रकार काष्ठा क्रमe200e_sba_regs अणु
    u32 __iomem *hcr;    /* address of host control रेजिस्टर              */
    u32 __iomem *bsr;    /* address of burst transfer size रेजिस्टर       */
    u32 __iomem *isr;    /* address of पूर्णांकerrupt level selection रेजिस्टर */
पूर्ण क्रमe200e_sba_regs_t;


/* model-specअगरic रेजिस्टरs */

प्रकार जोड़ क्रमe200e_regs अणु
    काष्ठा क्रमe200e_pca_regs pca;    /* PCA-200E रेजिस्टरs */
    काष्ठा क्रमe200e_sba_regs sba;    /* SBA-200E रेजिस्टरs */
पूर्ण क्रमe200e_regs;


काष्ठा क्रमe200e;

/* bus-dependent data */

प्रकार काष्ठा क्रमe200e_bus अणु
    अक्षर*                model_name;          /* board model name                       */
    अक्षर*                proc_name;           /* board name under /proc/aपंचांग             */
    पूर्णांक                  descr_alignment;     /* tpd/rpd/rbd DMA alignment requirement  */
    पूर्णांक                  buffer_alignment;    /* rx buffers DMA alignment requirement   */
    पूर्णांक                  status_alignment;    /* status words DMA alignment requirement */
    u32                  (*पढ़ो)(अस्थिर u32 __iomem *);
    व्योम                 (*ग_लिखो)(u32, अस्थिर u32 __iomem *);
    पूर्णांक                  (*configure)(काष्ठा क्रमe200e*); 
    पूर्णांक                  (*map)(काष्ठा क्रमe200e*); 
    व्योम                 (*reset)(काष्ठा क्रमe200e*);
    पूर्णांक                  (*prom_पढ़ो)(काष्ठा क्रमe200e*, काष्ठा prom_data*);
    व्योम                 (*unmap)(काष्ठा क्रमe200e*);
    व्योम                 (*irq_enable)(काष्ठा क्रमe200e*);
    पूर्णांक                  (*irq_check)(काष्ठा क्रमe200e*);
    व्योम                 (*irq_ack)(काष्ठा क्रमe200e*);
    पूर्णांक                  (*proc_पढ़ो)(काष्ठा क्रमe200e*, अक्षर*);
पूर्ण क्रमe200e_bus_t;

/* vc mapping */

प्रकार काष्ठा क्रमe200e_vc_map अणु
    काष्ठा aपंचांग_vcc* vcc;       /* vcc entry              */
    अचिन्हित दीर्घ   incarn;    /* vcc incarnation number */
पूर्ण क्रमe200e_vc_map_t;

#घोषणा FORE200E_VC_MAP(क्रमe200e, vpi, vci)  \
        (& (क्रमe200e)->vc_map[ ((vpi) << FORE200E_VCI_BITS) | (vci) ])


/* per-device data */

प्रकार काष्ठा क्रमe200e अणु
    काष्ठा       list_head     entry;                  /* next device                        */
    स्थिर काष्ठा क्रमe200e_bus* bus;                    /* bus-dependent code and data        */
    जोड़        क्रमe200e_regs regs;                   /* bus-dependent रेजिस्टरs            */
    काष्ठा       aपंचांग_dev*      aपंचांग_dev;                /* ATM device                         */

    क्रमागत क्रमe200e_state        state;                  /* device state                       */

    अक्षर                       name[16];               /* device name                        */
    काष्ठा device	       *dev;
    पूर्णांक                        irq;                    /* irq number                         */
    अचिन्हित दीर्घ              phys_base;              /* physical base address              */
    व्योम __iomem *             virt_base;              /* भव base address               */
    
    अचिन्हित अक्षर              esi[ ESI_LEN ];         /* end प्रणाली identअगरier              */

    काष्ठा cp_monitor __iomem *         cp_monitor;    /* i960 monitor address               */
    काष्ठा cp_queues __iomem *          cp_queues;              /* cp resident queues                 */
    काष्ठा host_cmdq           host_cmdq;              /* host resident cmd queue            */
    काष्ठा host_txq            host_txq;               /* host resident tx queue             */
    काष्ठा host_rxq            host_rxq;               /* host resident rx queue             */
                                                       /* host resident buffer supply queues */
    काष्ठा host_bsq            host_bsq[ BUFFER_SCHEME_NBR ][ BUFFER_MAGN_NBR ];       

    u32                        available_cell_rate;    /* reमुख्यing pseuकरो-CBR bw on link    */

    पूर्णांक                        loop_mode;              /* S/UNI loopback mode                */

    काष्ठा stats*              stats;                  /* last snapshot of the stats         */
    
    काष्ठा mutex               rate_mtx;               /* protects rate reservation ops      */
    spinlock_t                 q_lock;                 /* protects queue ops                 */
#अगर_घोषित FORE200E_USE_TASKLET
    काष्ठा tasklet_काष्ठा      tx_tasklet;             /* perक्रमms tx पूर्णांकerrupt work         */
    काष्ठा tasklet_काष्ठा      rx_tasklet;             /* perक्रमms rx पूर्णांकerrupt work         */
#पूर्ण_अगर
    अचिन्हित दीर्घ              tx_sat;                 /* tx queue saturation count          */

    अचिन्हित दीर्घ              incarn_count;
    काष्ठा क्रमe200e_vc_map     vc_map[ NBR_CONNECT ];  /* vc mapping                         */
पूर्ण क्रमe200e_t;


/* per-vcc data */

प्रकार काष्ठा क्रमe200e_vcc अणु
    क्रमागत buffer_scheme     scheme;             /* rx buffer scheme                   */
    काष्ठा tpd_rate        rate;               /* tx rate control data               */
    पूर्णांक                    rx_min_pdu;         /* size of smallest PDU received      */
    पूर्णांक                    rx_max_pdu;         /* size of largest PDU received       */
    पूर्णांक                    tx_min_pdu;         /* size of smallest PDU transmitted   */
    पूर्णांक                    tx_max_pdu;         /* size of largest PDU transmitted    */
    अचिन्हित दीर्घ          tx_pdu;             /* nbr of tx pdus                     */
    अचिन्हित दीर्घ          rx_pdu;             /* nbr of rx pdus                     */
पूर्ण क्रमe200e_vcc_t;



/* 200E-series common memory layout */

#घोषणा FORE200E_CP_MONITOR_OFFSET	0x00000400    /* i960 monitor पूर्णांकerface */
#घोषणा FORE200E_CP_QUEUES_OFFSET	0x00004d40    /* cp resident queues     */


/* PCA-200E memory layout */

#घोषणा PCA200E_IOSPACE_LENGTH	        0x00200000

#घोषणा PCA200E_HCR_OFFSET		0x00100000    /* board control रेजिस्टर */
#घोषणा PCA200E_IMR_OFFSET		0x00100004    /* host IRQ mask रेजिस्टर */
#घोषणा PCA200E_PSR_OFFSET		0x00100008    /* PCI specअगरic रेजिस्टर  */


/* PCA-200E host control रेजिस्टर */

#घोषणा PCA200E_HCR_RESET     (1<<0)    /* पढ़ो / ग_लिखो */
#घोषणा PCA200E_HCR_HOLD_LOCK (1<<1)    /* पढ़ो / ग_लिखो */
#घोषणा PCA200E_HCR_I960FAIL  (1<<2)    /* पढ़ो         */
#घोषणा PCA200E_HCR_INTRB     (1<<2)    /* ग_लिखो        */
#घोषणा PCA200E_HCR_HOLD_ACK  (1<<3)    /* पढ़ो         */
#घोषणा PCA200E_HCR_INTRA     (1<<3)    /* ग_लिखो        */
#घोषणा PCA200E_HCR_OUTFULL   (1<<4)    /* पढ़ो         */
#घोषणा PCA200E_HCR_CLRINTR   (1<<4)    /* ग_लिखो        */
#घोषणा PCA200E_HCR_ESPHOLD   (1<<5)    /* पढ़ो         */
#घोषणा PCA200E_HCR_INFULL    (1<<6)    /* पढ़ो         */
#घोषणा PCA200E_HCR_TESTMODE  (1<<7)    /* पढ़ो         */


/* PCA-200E PCI bus पूर्णांकerface regs (offsets in PCI config space) */

#घोषणा PCA200E_PCI_LATENCY      0x40    /* maximum slave latenty            */
#घोषणा PCA200E_PCI_MASTER_CTRL  0x41    /* master control                   */
#घोषणा PCA200E_PCI_THRESHOLD    0x42    /* burst / continuous req threshold  */

/* PBI master control रेजिस्टर */

#घोषणा PCA200E_CTRL_DIS_CACHE_RD      (1<<0)    /* disable cache-line पढ़ोs                         */
#घोषणा PCA200E_CTRL_DIS_WRT_INVAL     (1<<1)    /* disable ग_लिखोs and invalidates                   */
#घोषणा PCA200E_CTRL_2_CACHE_WRT_INVAL (1<<2)    /* require 2 cache-lines क्रम ग_लिखोs and invalidates */
#घोषणा PCA200E_CTRL_IGN_LAT_TIMER     (1<<3)    /* ignore the latency समयr                         */
#घोषणा PCA200E_CTRL_ENA_CONT_REQ_MODE (1<<4)    /* enable continuous request mode                   */
#घोषणा PCA200E_CTRL_LARGE_PCI_BURSTS  (1<<5)    /* क्रमce large PCI bus bursts                       */
#घोषणा PCA200E_CTRL_CONVERT_ENDIAN    (1<<6)    /* convert endianess of slave RAM accesses          */



#घोषणा SBA200E_PROM_NAME  "FORE,sba-200e"    /* device name in खोलोprom tree */


/* size of SBA-200E रेजिस्टरs */

#घोषणा SBA200E_HCR_LENGTH        4
#घोषणा SBA200E_BSR_LENGTH        4
#घोषणा SBA200E_ISR_LENGTH        4
#घोषणा SBA200E_RAM_LENGTH  0x40000


/* SBA-200E SBUS burst transfer size रेजिस्टर */

#घोषणा SBA200E_BSR_BURST4   0x04
#घोषणा SBA200E_BSR_BURST8   0x08
#घोषणा SBA200E_BSR_BURST16  0x10


/* SBA-200E host control रेजिस्टर */

#घोषणा SBA200E_HCR_RESET        (1<<0)    /* पढ़ो / ग_लिखो (sticky) */
#घोषणा SBA200E_HCR_HOLD_LOCK    (1<<1)    /* पढ़ो / ग_लिखो (sticky) */
#घोषणा SBA200E_HCR_I960FAIL     (1<<2)    /* पढ़ो                  */
#घोषणा SBA200E_HCR_I960SETINTR  (1<<2)    /* ग_लिखो                 */
#घोषणा SBA200E_HCR_OUTFULL      (1<<3)    /* पढ़ो                  */
#घोषणा SBA200E_HCR_INTR_CLR     (1<<3)    /* ग_लिखो                 */
#घोषणा SBA200E_HCR_INTR_ENA     (1<<4)    /* पढ़ो / ग_लिखो (sticky) */
#घोषणा SBA200E_HCR_ESPHOLD      (1<<5)    /* पढ़ो                  */
#घोषणा SBA200E_HCR_INFULL       (1<<6)    /* पढ़ो                  */
#घोषणा SBA200E_HCR_TESTMODE     (1<<7)    /* पढ़ो                  */
#घोषणा SBA200E_HCR_INTR_REQ     (1<<8)    /* पढ़ो                  */

#घोषणा SBA200E_HCR_STICKY       (SBA200E_HCR_RESET | SBA200E_HCR_HOLD_LOCK | SBA200E_HCR_INTR_ENA)


#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _FORE200E_H */
