<शैली गुरु>
/******************************************************************************
             Device driver क्रम Interphase ATM PCI adapter cards 
                    Author: Peter Wang  <pwang@iphase.com>            
                   Interphase Corporation  <www.iphase.com>           
                               Version: 1.0   
               iphase.h:  This is the header file क्रम iphase.c. 
*******************************************************************************
      
      This software may be used and distributed according to the terms
      of the GNU General Public License (GPL), incorporated herein by reference.
      Drivers based on this skeleton fall under the GPL and must retain
      the authorship (implicit copyright) notice.

      This program is distributed in the hope that it will be useful, but
      WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
      General Public License क्रम more details.
      
      Modअगरied from an incomplete driver क्रम Interphase 5575 1KVC 1M card which 
      was originally written by Monalisa Agrawal at UNH. Now this driver 
      supports a variety of varients of Interphase ATM PCI (i)Chip adapter 
      card family (See www.iphase.com/products/ClassSheet.cfm?ClassID=ATM) 
      in terms of PHY type, the size of control memory and the size of 
      packet memory. The following are the change log and history:
     
          Bugfix the Mona's UBR driver.
          Modअगरy the basic memory allocation and dma logic.
          Port the driver to the latest kernel from 2.0.46.
          Complete the ABR logic of the driver, and added the ABR work-
              around क्रम the hardware anormalies.
          Add the CBR support.
	  Add the flow control logic to the driver to allow rate-limit VC.
          Add 4K VC support to the board with 512K control memory.
          Add the support of all the variants of the Interphase ATM PCI 
          (i)Chip adapter cards including x575 (155M OC3 and UTP155), x525
          (25M UTP25) and x531 (DS3 and E3).
          Add SMP support.

      Support and updates available at: ftp://ftp.iphase.com/pub/aपंचांग

*******************************************************************************/
  
#अगर_अघोषित IPHASE_H  
#घोषणा IPHASE_H  


/************************ IADBG DEFINE *********************************/
/* IADebugFlag Bit Map */ 
#घोषणा IF_IADBG_INIT_ADAPTER   0x00000001        // init adapter info
#घोषणा IF_IADBG_TX             0x00000002        // debug TX
#घोषणा IF_IADBG_RX             0x00000004        // debug RX
#घोषणा IF_IADBG_QUERY_INFO     0x00000008        // debug Request call
#घोषणा IF_IADBG_SHUTDOWN       0x00000010        // debug shutकरोwn event
#घोषणा IF_IADBG_INTR           0x00000020        // debug पूर्णांकerrupt DPC
#घोषणा IF_IADBG_TXPKT          0x00000040  	  // debug TX PKT
#घोषणा IF_IADBG_RXPKT          0x00000080  	  // debug RX PKT
#घोषणा IF_IADBG_ERR            0x00000100        // debug प्रणाली error
#घोषणा IF_IADBG_EVENT          0x00000200        // debug event
#घोषणा IF_IADBG_DIS_INTR       0x00001000        // debug disable पूर्णांकerrupt
#घोषणा IF_IADBG_EN_INTR        0x00002000        // debug enable पूर्णांकerrupt
#घोषणा IF_IADBG_LOUD           0x00004000        // debugging info
#घोषणा IF_IADBG_VERY_LOUD      0x00008000        // excessive debugging info
#घोषणा IF_IADBG_CBR            0x00100000  	  //
#घोषणा IF_IADBG_UBR            0x00200000  	  //
#घोषणा IF_IADBG_ABR            0x00400000        //
#घोषणा IF_IADBG_DESC           0x01000000        //
#घोषणा IF_IADBG_SUNI_STAT      0x02000000        // suni statistics
#घोषणा IF_IADBG_RESET          0x04000000        

#घोषणा IF_IADBG(f) अगर (IADebugFlag & (f))

#अगर_घोषित  CONFIG_ATM_IA_DEBUG   /* Debug build */

#घोषणा IF_LOUD(A) IF_IADBG(IF_IADBG_LOUD) अणु A पूर्ण
#घोषणा IF_ERR(A) IF_IADBG(IF_IADBG_ERR) अणु A पूर्ण
#घोषणा IF_VERY_LOUD(A) IF_IADBG( IF_IADBG_VERY_LOUD ) अणु A पूर्ण

#घोषणा IF_INIT_ADAPTER(A) IF_IADBG( IF_IADBG_INIT_ADAPTER ) अणु A पूर्ण
#घोषणा IF_INIT(A) IF_IADBG( IF_IADBG_INIT_ADAPTER ) अणु A पूर्ण
#घोषणा IF_SUNI_STAT(A) IF_IADBG( IF_IADBG_SUNI_STAT ) अणु A पूर्ण
#घोषणा IF_QUERY_INFO(A) IF_IADBG( IF_IADBG_QUERY_INFO ) अणु A पूर्ण
#घोषणा IF_COPY_OVER(A) IF_IADBG( IF_IADBG_COPY_OVER ) अणु A पूर्ण

#घोषणा IF_INTR(A) IF_IADBG( IF_IADBG_INTR ) अणु A पूर्ण
#घोषणा IF_DIS_INTR(A) IF_IADBG( IF_IADBG_DIS_INTR ) अणु A पूर्ण
#घोषणा IF_EN_INTR(A) IF_IADBG( IF_IADBG_EN_INTR ) अणु A पूर्ण

#घोषणा IF_TX(A) IF_IADBG( IF_IADBG_TX ) अणु A पूर्ण
#घोषणा IF_RX(A) IF_IADBG( IF_IADBG_RX ) अणु A पूर्ण
#घोषणा IF_TXPKT(A) IF_IADBG( IF_IADBG_TXPKT ) अणु A पूर्ण
#घोषणा IF_RXPKT(A) IF_IADBG( IF_IADBG_RXPKT ) अणु A पूर्ण

#घोषणा IF_SHUTDOWN(A) IF_IADBG(IF_IADBG_SHUTDOWN) अणु A पूर्ण
#घोषणा IF_CBR(A) IF_IADBG( IF_IADBG_CBR ) अणु A पूर्ण
#घोषणा IF_UBR(A) IF_IADBG( IF_IADBG_UBR ) अणु A पूर्ण
#घोषणा IF_ABR(A) IF_IADBG( IF_IADBG_ABR ) अणु A पूर्ण
#घोषणा IF_EVENT(A) IF_IADBG( IF_IADBG_EVENT) अणु A पूर्ण

#अन्यथा /* मुक्त build */
#घोषणा IF_LOUD(A)
#घोषणा IF_VERY_LOUD(A)
#घोषणा IF_INIT_ADAPTER(A)
#घोषणा IF_INIT(A)
#घोषणा IF_SUNI_STAT(A)
#घोषणा IF_PVC_CHKPKT(A)
#घोषणा IF_QUERY_INFO(A)
#घोषणा IF_COPY_OVER(A)
#घोषणा IF_HANG(A)
#घोषणा IF_INTR(A)
#घोषणा IF_DIS_INTR(A)
#घोषणा IF_EN_INTR(A)
#घोषणा IF_TX(A)
#घोषणा IF_RX(A)
#घोषणा IF_TXDEBUG(A)
#घोषणा IF_VC(A)
#घोषणा IF_ERR(A) 
#घोषणा IF_CBR(A)
#घोषणा IF_UBR(A)
#घोषणा IF_ABR(A)
#घोषणा IF_SHUTDOWN(A)
#घोषणा DbgPrपूर्णांक(A)
#घोषणा IF_EVENT(A)
#घोषणा IF_TXPKT(A) 
#घोषणा IF_RXPKT(A)
#पूर्ण_अगर /* CONFIG_ATM_IA_DEBUG */ 

#घोषणा है_छाप(a) ((a >=' ')&&(a <= '~'))  
#घोषणा ATM_DESC(skb) (skb->protocol)
#घोषणा IA_SKB_STATE(skb) (skb->protocol)
#घोषणा IA_DLED   1
#घोषणा IA_TX_DONE 2

/* iadbg defines */
#घोषणा IA_CMD   0x7749
प्रकार काष्ठा अणु
	पूर्णांक cmd;
        पूर्णांक sub_cmd;
        पूर्णांक len;
        u32 maddr;
        पूर्णांक status;
        व्योम __user *buf;
पूर्ण IA_CMDBUF, *PIA_CMDBUF;

/* cmds */
#घोषणा MEMDUMP     		0x01

/* sub_cmds */
#घोषणा MEMDUMP_SEGREG          0x2
#घोषणा MEMDUMP_DEV  		0x1
#घोषणा MEMDUMP_REASSREG        0x3
#घोषणा MEMDUMP_FFL             0x4
#घोषणा READ_REG                0x5
#घोषणा WAKE_DBG_WAIT           0x6

/************************ IADBG DEFINE END ***************************/

#घोषणा Boolean(x)    	((x) ? 1 : 0)
#घोषणा NR_VCI 1024		/* number of VCIs */  
#घोषणा NR_VCI_LD 10		/* log2(NR_VCI) */  
#घोषणा NR_VCI_4K 4096 		/* number of VCIs */  
#घोषणा NR_VCI_4K_LD 12		/* log2(NR_VCI) */  
#घोषणा MEM_VALID 0xfffffff0	/* mask base address with this */  
  
#अगर_अघोषित PCI_VENDOR_ID_IPHASE  
#घोषणा PCI_VENDOR_ID_IPHASE 0x107e  
#पूर्ण_अगर  
#अगर_अघोषित PCI_DEVICE_ID_IPHASE_5575  
#घोषणा PCI_DEVICE_ID_IPHASE_5575 0x0008  
#पूर्ण_अगर  
#घोषणा DEV_LABEL 	"ia"  
#घोषणा PCR	207692  
#घोषणा ICR	100000  
#घोषणा MCR	0  
#घोषणा TBE	1000  
#घोषणा FRTT	1  
#घोषणा RIF	2		  
#घोषणा RDF	4  
#घोषणा NRMCODE 5	/* 0 - 7 */  
#घोषणा TRMCODE	3	/* 0 - 7 */  
#घोषणा CDFCODE	6  
#घोषणा ATDFCODE 2	/* 0 - 15 */  
  
/*---------------------- Packet/Cell Memory ------------------------*/  
#घोषणा TX_PACKET_RAM 	0x00000 /* start of Trasnmit Packet memory - 0 */  
#घोषणा DFL_TX_BUF_SZ	10240	/* 10 K buffers */  
#घोषणा DFL_TX_BUFFERS     50 	/* number of packet buffers क्रम Tx   
					- descriptor 0 unused */  
#घोषणा REASS_RAM_SIZE 0x10000  /* क्रम 64K 1K VC board */  
#घोषणा RX_PACKET_RAM 	0x80000 /* start of Receive Packet memory - 512K */  
#घोषणा DFL_RX_BUF_SZ	10240	/* 10k buffers */  
#घोषणा DFL_RX_BUFFERS      50	/* number of packet buffers क्रम Rx   
					- descriptor 0 unused */  
  
काष्ठा cpcs_trailer 
अणु  
	u_लघु control;  
	u_लघु length;  
	u_पूर्णांक	crc32;  
पूर्ण;  

काष्ठा cpcs_trailer_desc
अणु
	काष्ठा cpcs_trailer *cpcs;
	dma_addr_t dma_addr;
पूर्ण;

काष्ठा ia_vcc 
अणु 
	पूर्णांक rxing;	 
	पूर्णांक txing;		 
        पूर्णांक NumCbrEntry;
        u32 pcr;
        u32 saved_tx_quota;
        पूर्णांक flow_inc;
        काष्ठा sk_buff_head txing_skb; 
        पूर्णांक  lसमयout;                  
        u8  vc_desc_cnt;                
                
पूर्ण;  
  
काष्ठा abr_vc_table 
अणु  
	u_अक्षर status;  
	u_अक्षर rdf;  
	u_लघु air;  
	u_पूर्णांक res[3];  
	u_पूर्णांक req_rm_cell_data1;  
	u_पूर्णांक req_rm_cell_data2;  
	u_पूर्णांक add_rm_cell_data1;  
	u_पूर्णांक add_rm_cell_data2;  
पूर्ण;  
    
/* 32 byte entries */  
काष्ठा मुख्य_vc 
अणु  
	u_लघु 	type;  
#घोषणा ABR	0x8000  
#घोषणा UBR 	0xc000  
#घोषणा CBR	0x0000  
	/* ABR fields */  
	u_लघु 	nrm;	 
 	u_लघु 	trm;	   
	u_लघु 	rm_बारtamp_hi;  
	u_लघु 	rm_बारtamp_lo:8,  
			crm:8;		  
	u_लघु 	reमुख्यder; 	/* ABR and UBR fields - last 10 bits*/  
	u_लघु 	next_vc_sched;  
	u_लघु 	present_desc;	/* all classes */  
	u_लघु 	last_cell_slot;	/* ABR and UBR */  
	u_लघु 	pcr;  
	u_लघु 	fraction;  
	u_लघु 	icr;  
	u_लघु 	atdf;  
	u_लघु 	mcr;  
	u_लघु 	acr;		 
	u_लघु 	unack:8,  
			status:8;	/* all classes */  
#घोषणा UIOLI 0x80  
#घोषणा CRC_APPEND 0x40			/* क्रम status field - CRC-32 append */  
#घोषणा ABR_STATE 0x02  
  
पूर्ण;  
  
  
/* 8 byte entries */  
काष्ठा ext_vc 
अणु  
	u_लघु 	aपंचांग_hdr1;  
	u_लघु 	aपंचांग_hdr2;  
	u_लघु 	last_desc;  
      	u_लघु 	out_of_rate_link;   /* reserved क्रम UBR and CBR */  
पूर्ण;  
  
  
#घोषणा DLE_ENTRIES 256  
#घोषणा DMA_INT_ENABLE 0x0002	/* use क्रम both Tx and Rx */  
#घोषणा TX_DLE_PSI 0x0001  
#घोषणा DLE_TOTAL_SIZE (माप(काष्ठा dle)*DLE_ENTRIES)
  
/* Descriptor List Entries (DLE) */  
काष्ठा dle 
अणु  
	u32 	sys_pkt_addr;  
	u32 	local_pkt_addr;  
	u32 	bytes;  
	u16 	prq_wr_ptr_data;  
	u16 	mode;  
पूर्ण;  
  
काष्ठा dle_q 
अणु  
	काष्ठा dle 	*start;  
	काष्ठा dle 	*end;  
	काष्ठा dle 	*पढ़ो;  
	काष्ठा dle 	*ग_लिखो;  
पूर्ण;  
  
काष्ठा मुक्त_desc_q 
अणु  
	पूर्णांक 	desc;	/* Descriptor number */  
	काष्ठा मुक्त_desc_q *next;  
पूर्ण;  
  
काष्ठा tx_buf_desc अणु  
	अचिन्हित लघु desc_mode;  
	अचिन्हित लघु vc_index;  
	अचिन्हित लघु res1;		/* reserved field */  
	अचिन्हित लघु bytes;  
	अचिन्हित लघु buf_start_hi;  
	अचिन्हित लघु buf_start_lo;  
	अचिन्हित लघु res2[10];	/* reserved field */  
पूर्ण;  
	  
  
काष्ठा rx_buf_desc अणु 
	अचिन्हित लघु desc_mode;
	अचिन्हित लघु vc_index;
	अचिन्हित लघु vpi; 
	अचिन्हित लघु bytes; 
	अचिन्हित लघु buf_start_hi;  
	अचिन्हित लघु buf_start_lo;  
	अचिन्हित लघु dma_start_hi;  
	अचिन्हित लघु dma_start_lo;  
	अचिन्हित लघु crc_upper;  
	अचिन्हित लघु crc_lower;  
	अचिन्हित लघु res:8, समयout:8;  
	अचिन्हित लघु res2[5];	/* reserved field */  
पूर्ण;  
  
/*--------SAR stuff ---------------------*/  
  
#घोषणा EPROM_SIZE 0x40000	/* says 64K in the करोcs ??? */  
#घोषणा MAC1_LEN	4	   					  
#घोषणा MAC2_LEN	2  
   
/*------------ PCI Memory Space Map, 128K SAR memory ----------------*/  
#घोषणा IPHASE5575_PCI_CONFIG_REG_BASE	0x0000  
#घोषणा IPHASE5575_BUS_CONTROL_REG_BASE 0x1000	/* offsets 0x00 - 0x3c */  
#घोषणा IPHASE5575_FRAG_CONTROL_REG_BASE 0x2000  
#घोषणा IPHASE5575_REASS_CONTROL_REG_BASE 0x3000  
#घोषणा IPHASE5575_DMA_CONTROL_REG_BASE	0x4000  
#घोषणा IPHASE5575_FRONT_END_REG_BASE IPHASE5575_DMA_CONTROL_REG_BASE  
#घोषणा IPHASE5575_FRAG_CONTROL_RAM_BASE 0x10000  
#घोषणा IPHASE5575_REASS_CONTROL_RAM_BASE 0x20000  
  
/*------------ Bus पूर्णांकerface control रेजिस्टरs -----------------*/  
#घोषणा IPHASE5575_BUS_CONTROL_REG	0x00  
#घोषणा IPHASE5575_BUS_STATUS_REG	0x01	/* actual offset 0x04 */  
#घोषणा IPHASE5575_MAC1			0x02  
#घोषणा IPHASE5575_REV			0x03  
#घोषणा IPHASE5575_MAC2			0x03	/*actual offset 0x0e-reg 0x0c*/  
#घोषणा IPHASE5575_EXT_RESET		0x04  
#घोषणा IPHASE5575_INT_RESET		0x05	/* addr 1c ?? reg 0x06 */  
#घोषणा IPHASE5575_PCI_ADDR_PAGE	0x07	/* reg 0x08, 0x09 ?? */  
#घोषणा IPHASE5575_EEPROM_ACCESS	0x0a	/* actual offset 0x28 */  
#घोषणा IPHASE5575_CELL_FIFO_QUEUE_SZ	0x0b  
#घोषणा IPHASE5575_CELL_FIFO_MARK_STATE	0x0c  
#घोषणा IPHASE5575_CELL_FIFO_READ_PTR	0x0d  
#घोषणा IPHASE5575_CELL_FIFO_WRITE_PTR	0x0e  
#घोषणा IPHASE5575_CELL_FIFO_CELLS_AVL	0x0f	/* actual offset 0x3c */  
  
/* Bus Interface Control Register bits */  
#घोषणा CTRL_FE_RST	0x80000000  
#घोषणा CTRL_LED	0x40000000  
#घोषणा CTRL_25MBPHY	0x10000000  
#घोषणा CTRL_ENCMBMEM	0x08000000  
#घोषणा CTRL_ENOFFSEG	0x01000000  
#घोषणा CTRL_ERRMASK	0x00400000  
#घोषणा CTRL_DLETMASK	0x00100000  
#घोषणा CTRL_DLERMASK	0x00080000  
#घोषणा CTRL_FEMASK	0x00040000  
#घोषणा CTRL_SEGMASK	0x00020000  
#घोषणा CTRL_REASSMASK	0x00010000  
#घोषणा CTRL_CSPREEMPT	0x00002000  
#घोषणा CTRL_B128	0x00000200  
#घोषणा CTRL_B64	0x00000100  
#घोषणा CTRL_B48	0x00000080  
#घोषणा CTRL_B32	0x00000040  
#घोषणा CTRL_B16	0x00000020  
#घोषणा CTRL_B8		0x00000010  
  
/* Bus Interface Status Register bits */  
#घोषणा STAT_CMEMSIZ	0xc0000000  
#घोषणा STAT_ADPARCK	0x20000000  
#घोषणा STAT_RESVD	0x1fffff80  
#घोषणा STAT_ERRINT	0x00000040  
#घोषणा STAT_MARKINT	0x00000020  
#घोषणा STAT_DLETINT	0x00000010  
#घोषणा STAT_DLERINT	0x00000008  
#घोषणा STAT_FEINT	0x00000004  
#घोषणा STAT_SEGINT	0x00000002  
#घोषणा STAT_REASSINT	0x00000001  
  
  
/*--------------- Segmentation control रेजिस्टरs -----------------*/  
/* The segmentation रेजिस्टरs are 16 bits access and the addresses  
	are defined as such so the addresses are the actual "offsets" */  
#घोषणा IDLEHEADHI	0x00  
#घोषणा IDLEHEADLO	0x01  
#घोषणा MAXRATE		0x02  
/* Values क्रम MAXRATE रेजिस्टर क्रम 155Mbps and 25.6 Mbps operation */  
#घोषणा RATE155		0x64b1 // 16 bits भग्न क्रमmat 
#घोषणा MAX_ATM_155     352768 // Cells/second p.118
#घोषणा RATE25		0x5f9d  
  
#घोषणा STPARMS		0x03  
#घोषणा STPARMS_1K	0x008c  
#घोषणा STPARMS_2K	0x0049  
#घोषणा STPARMS_4K	0x0026  
#घोषणा COMP_EN		0x4000  
#घोषणा CBR_EN		0x2000  
#घोषणा ABR_EN		0x0800  
#घोषणा UBR_EN		0x0400  
  
#घोषणा ABRUBR_ARB	0x04  
#घोषणा RM_TYPE		0x05  
/*Value क्रम RM_TYPE रेजिस्टर क्रम ATM Forum Traffic Mangement4.0 support*/  
#घोषणा RM_TYPE_4_0	0x0100  
  
#घोषणा SEG_COMMAND_REG		0x17  
/* Values क्रम the command रेजिस्टर */  
#घोषणा RESET_SEG 0x0055  
#घोषणा RESET_SEG_STATE	0x00aa  
#घोषणा RESET_TX_CELL_CTR 0x00cc  
  
#घोषणा CBR_PTR_BASE	0x20  
#घोषणा ABR_SBPTR_BASE	0x22  
#घोषणा UBR_SBPTR_BASE  0x23  
#घोषणा ABRWQ_BASE	0x26  
#घोषणा UBRWQ_BASE	0x27  
#घोषणा VCT_BASE	0x28  
#घोषणा VCTE_BASE	0x29  
#घोषणा CBR_TAB_BEG	0x2c  
#घोषणा CBR_TAB_END	0x2d  
#घोषणा PRQ_ST_ADR	0x30  
#घोषणा PRQ_ED_ADR	0x31  
#घोषणा PRQ_RD_PTR	0x32  
#घोषणा PRQ_WR_PTR	0x33  
#घोषणा TCQ_ST_ADR	0x34  
#घोषणा TCQ_ED_ADR 	0x35  
#घोषणा TCQ_RD_PTR	0x36  
#घोषणा TCQ_WR_PTR	0x37  
#घोषणा SEG_QUEUE_BASE	0x40  
#घोषणा SEG_DESC_BASE	0x41  
#घोषणा MODE_REG_0	0x45  
#घोषणा T_ONLINE	0x0002		/* (i)chipSAR is online */  
  
#घोषणा MODE_REG_1	0x46  
#घोषणा MODE_REG_1_VAL	0x0400		/*क्रम propoer device operation*/  
  
#घोषणा SEG_INTR_STATUS_REG 0x47  
#घोषणा SEG_MASK_REG	0x48  
#घोषणा TRANSMIT_DONE 0x0200
#घोषणा TCQ_NOT_EMPTY 0x1000	/* this can be used क्रम both the पूर्णांकerrupt   
				status रेजिस्टरs as well as the mask रेजिस्टर */  
  
#घोषणा CELL_CTR_HIGH_AUTO 0x49  
#घोषणा CELL_CTR_HIGH_NOAUTO 0xc9  
#घोषणा CELL_CTR_LO_AUTO 0x4a  
#घोषणा CELL_CTR_LO_NOAUTO 0xca  
  
/* Diagnostic रेजिस्टरs */  
#घोषणा NEXTDESC 	0x59  
#घोषणा NEXTVC		0x5a  
#घोषणा PSLOTCNT	0x5d  
#घोषणा NEWDN		0x6a  
#घोषणा NEWVC		0x6b  
#घोषणा SBPTR		0x6c  
#घोषणा ABRWQ_WRPTR	0x6f  
#घोषणा ABRWQ_RDPTR	0x70  
#घोषणा UBRWQ_WRPTR	0x71  
#घोषणा UBRWQ_RDPTR	0x72  
#घोषणा CBR_VC		0x73  
#घोषणा ABR_SBVC	0x75  
#घोषणा UBR_SBVC	0x76  
#घोषणा ABRNEXTLINK	0x78  
#घोषणा UBRNEXTLINK	0x79  
  
  
/*----------------- Reassembly control रेजिस्टरs ---------------------*/  
/* The reassembly रेजिस्टरs are 16 bits access and the addresses  
	are defined as such so the addresses are the actual "offsets" */  
#घोषणा MODE_REG	0x00  
#घोषणा R_ONLINE	0x0002		/* (i)chip is online */  
#घोषणा IGN_RAW_FL     	0x0004
  
#घोषणा PROTOCOL_ID	0x01  
#घोषणा REASS_MASK_REG	0x02  
#घोषणा REASS_INTR_STATUS_REG	0x03  
/* Interrupt Status रेजिस्टर bits */  
#घोषणा RX_PKT_CTR_OF	0x8000  
#घोषणा RX_ERR_CTR_OF	0x4000  
#घोषणा RX_CELL_CTR_OF	0x1000  
#घोषणा RX_FREEQ_EMPT	0x0200  
#घोषणा RX_EXCPQ_FL	0x0080  
#घोषणा	RX_RAWQ_FL	0x0010  
#घोषणा RX_EXCP_RCVD	0x0008  
#घोषणा RX_PKT_RCVD	0x0004  
#घोषणा RX_RAW_RCVD	0x0001  
  
#घोषणा DRP_PKT_CNTR	0x04  
#घोषणा ERR_CNTR	0x05  
#घोषणा RAW_BASE_ADR	0x08  
#घोषणा CELL_CTR0	0x0c  
#घोषणा CELL_CTR1	0x0d  
#घोषणा REASS_COMMAND_REG	0x0f  
/* Values क्रम command रेजिस्टर */  
#घोषणा RESET_REASS	0x0055  
#घोषणा RESET_REASS_STATE 0x00aa  
#घोषणा RESET_DRP_PKT_CNTR 0x00f1  
#घोषणा RESET_ERR_CNTR	0x00f2  
#घोषणा RESET_CELL_CNTR 0x00f8  
#घोषणा RESET_REASS_ALL_REGS 0x00ff  
  
#घोषणा REASS_DESC_BASE	0x10  
#घोषणा VC_LKUP_BASE	0x11  
#घोषणा REASS_TABLE_BASE 0x12  
#घोषणा REASS_QUEUE_BASE 0x13  
#घोषणा PKT_TM_CNT	0x16  
#घोषणा TMOUT_RANGE	0x17  
#घोषणा INTRVL_CNTR	0x18  
#घोषणा TMOUT_INDX	0x19  
#घोषणा VP_LKUP_BASE	0x1c  
#घोषणा VP_FILTER	0x1d  
#घोषणा ABR_LKUP_BASE	0x1e  
#घोषणा FREEQ_ST_ADR	0x24  
#घोषणा FREEQ_ED_ADR	0x25  
#घोषणा FREEQ_RD_PTR	0x26  
#घोषणा FREEQ_WR_PTR	0x27  
#घोषणा PCQ_ST_ADR	0x28  
#घोषणा PCQ_ED_ADR	0x29  
#घोषणा PCQ_RD_PTR	0x2a  
#घोषणा PCQ_WR_PTR	0x2b  
#घोषणा EXCP_Q_ST_ADR	0x2c  
#घोषणा EXCP_Q_ED_ADR	0x2d  
#घोषणा EXCP_Q_RD_PTR	0x2e  
#घोषणा EXCP_Q_WR_PTR	0x2f  
#घोषणा CC_FIFO_ST_ADR	0x34  
#घोषणा CC_FIFO_ED_ADR	0x35  
#घोषणा CC_FIFO_RD_PTR	0x36  
#घोषणा CC_FIFO_WR_PTR	0x37  
#घोषणा STATE_REG	0x38  
#घोषणा BUF_SIZE	0x42  
#घोषणा XTRA_RM_OFFSET	0x44  
#घोषणा DRP_PKT_CNTR_NC	0x84  
#घोषणा ERR_CNTR_NC	0x85  
#घोषणा CELL_CNTR0_NC	0x8c  
#घोषणा CELL_CNTR1_NC	0x8d  
  
/* State Register bits */  
#घोषणा EXCPQ_EMPTY	0x0040  
#घोषणा PCQ_EMPTY	0x0010  
#घोषणा FREEQ_EMPTY	0x0004  
  
  
/*----------------- Front End रेजिस्टरs/ DMA control --------------*/  
/* There is a lot of करोcumentation error regarding these offsets ???   
	eg:- 2 offsets given 800, a00 क्रम rx counter  
	similarly many others  
   Remember again that the offsets are to be 4*रेजिस्टर number, so  
	correct the #घोषणाs here   
*/  
#घोषणा IPHASE5575_TX_COUNTER		0x200	/* offset - 0x800 */  
#घोषणा IPHASE5575_RX_COUNTER		0x280	/* offset - 0xa00 */  
#घोषणा IPHASE5575_TX_LIST_ADDR		0x300	/* offset - 0xc00 */  
#घोषणा IPHASE5575_RX_LIST_ADDR		0x380	/* offset - 0xe00 */  
  
/*--------------------------- RAM ---------------------------*/  
/* These memory maps are actually offsets from the segmentation and reassembly  RAM base addresses */  
  
/* Segmentation Control Memory map */  
#घोषणा TX_DESC_BASE	0x0000	/* Buffer Decriptor Table */  
#घोषणा TX_COMP_Q	0x1000	/* Transmit Complete Queue */  
#घोषणा PKT_RDY_Q	0x1400	/* Packet Ready Queue */  
#घोषणा CBR_SCHED_TABLE	0x1800	/* CBR Table */  
#घोषणा UBR_SCHED_TABLE	0x3000	/* UBR Table */  
#घोषणा UBR_WAIT_Q	0x4000	/* UBR Wait Queue */  
#घोषणा ABR_SCHED_TABLE	0x5000	/* ABR Table */  
#घोषणा ABR_WAIT_Q	0x5800	/* ABR Wait Queue */  
#घोषणा EXT_VC_TABLE	0x6000	/* Extended VC Table */  
#घोषणा MAIN_VC_TABLE	0x8000	/* Main VC Table */  
#घोषणा SCHEDSZ		1024	/* ABR and UBR Scheduling Table size */  
#घोषणा TX_DESC_TABLE_SZ 128	/* Number of entries in the Transmit   
					Buffer Descriptor Table */  
  
/* These are used as table offsets in Descriptor Table address generation */  
#घोषणा DESC_MODE	0x0  
#घोषणा VC_INDEX	0x1  
#घोषणा BYTE_CNT	0x3  
#घोषणा PKT_START_HI	0x4  
#घोषणा PKT_START_LO	0x5  
  
/* Descriptor Mode Word Bits */  
#घोषणा EOM_EN	0x0800  
#घोषणा AAL5	0x0100  
#घोषणा APP_CRC32 0x0400  
#घोषणा CMPL_INT  0x1000
  
#घोषणा TABLE_ADDRESS(db, dn, to) \
	(((अचिन्हित दीर्घ)(db & 0x04)) << 16) | (dn << 5) | (to << 1)  
  
/* Reassembly Control Memory Map */  
#घोषणा RX_DESC_BASE	0x0000	/* Buffer Descriptor Table */  
#घोषणा VP_TABLE	0x5c00	/* VP Table */  
#घोषणा EXCEPTION_Q	0x5e00	/* Exception Queue */  
#घोषणा FREE_BUF_DESC_Q	0x6000	/* Free Buffer Descriptor Queue */  
#घोषणा PKT_COMP_Q	0x6800	/* Packet Complete Queue */  
#घोषणा REASS_TABLE	0x7000	/* Reassembly Table */  
#घोषणा RX_VC_TABLE	0x7800	/* VC Table */  
#घोषणा ABR_VC_TABLE	0x8000	/* ABR VC Table */  
#घोषणा RX_DESC_TABLE_SZ 736	/* Number of entries in the Receive   
					Buffer Descriptor Table */  
#घोषणा VP_TABLE_SZ	256	 /* Number of entries in VPTable */   
#घोषणा RX_VC_TABLE_SZ 	1024	/* Number of entries in VC Table */   
#घोषणा REASS_TABLE_SZ 	1024	/* Number of entries in Reassembly Table */  
 /* Buffer Descriptor Table */  
#घोषणा RX_ACT	0x8000  
#घोषणा RX_VPVC	0x4000  
#घोषणा RX_CNG	0x0040  
#घोषणा RX_CER	0x0008  
#घोषणा RX_PTE	0x0004  
#घोषणा RX_OFL	0x0002  
#घोषणा NUM_RX_EXCP   32

/* Reassembly Table */  
#घोषणा NO_AAL5_PKT	0x0000  
#घोषणा AAL5_PKT_REASSEMBLED 0x4000  
#घोषणा AAL5_PKT_TERMINATED 0x8000  
#घोषणा RAW_PKT		0xc000  
#घोषणा REASS_ABR	0x2000  
  
/*-------------------- Base Registers --------------------*/  
#घोषणा REG_BASE IPHASE5575_BUS_CONTROL_REG_BASE  
#घोषणा RAM_BASE IPHASE5575_FRAG_CONTROL_RAM_BASE  
#घोषणा PHY_BASE IPHASE5575_FRONT_END_REG_BASE  
#घोषणा SEG_BASE IPHASE5575_FRAG_CONTROL_REG_BASE  
#घोषणा REASS_BASE IPHASE5575_REASS_CONTROL_REG_BASE  

प्रकार अस्थिर u_पूर्णांक	ffreg_t;
प्रकार u_पूर्णांक   rreg_t;

प्रकार काष्ठा _ffredn_t अणु
	ffreg_t	idlehead_high;	/* Idle cell header (high)		*/
	ffreg_t	idlehead_low;	/* Idle cell header (low)		*/
	ffreg_t	maxrate;	/* Maximum rate				*/
	ffreg_t	stparms;	/* Traffic Management Parameters	*/
	ffreg_t	abrubr_abr;	/* ABRUBR Priority Byte 1, TCR Byte 0	*/
	ffreg_t	rm_type;	/*					*/
	u_पूर्णांक	filler5[0x17 - 0x06];
	ffreg_t	cmd_reg;	/* Command रेजिस्टर			*/
	u_पूर्णांक	filler18[0x20 - 0x18];
	ffreg_t	cbr_base;	/* CBR Poपूर्णांकer Base			*/
	ffreg_t	vbr_base;	/* VBR Poपूर्णांकer Base			*/
	ffreg_t	abr_base;	/* ABR Poपूर्णांकer Base			*/
	ffreg_t	ubr_base;	/* UBR Poपूर्णांकer Base			*/
	u_पूर्णांक	filler24;
	ffreg_t	vbrwq_base;	/* VBR Wait Queue Base			*/
	ffreg_t	abrwq_base;	/* ABR Wait Queue Base			*/
	ffreg_t	ubrwq_base;	/* UBR Wait Queue Base			*/
	ffreg_t	vct_base;	/* Main VC Table Base			*/
	ffreg_t	vcte_base;	/* Extended Main VC Table Base		*/
	u_पूर्णांक	filler2a[0x2C - 0x2A];
	ffreg_t	cbr_tab_beg;	/* CBR Table Begin			*/
	ffreg_t	cbr_tab_end;	/* CBR Table End			*/
	ffreg_t	cbr_poपूर्णांकer;	/* CBR Poपूर्णांकer				*/
	u_पूर्णांक	filler2f[0x30 - 0x2F];
	ffreg_t	prq_st_adr;	/* Packet Ready Queue Start Address	*/
	ffreg_t	prq_ed_adr;	/* Packet Ready Queue End Address	*/
	ffreg_t	prq_rd_ptr;	/* Packet Ready Queue पढ़ो poपूर्णांकer	*/
	ffreg_t	prq_wr_ptr;	/* Packet Ready Queue ग_लिखो poपूर्णांकer	*/
	ffreg_t	tcq_st_adr;	/* Transmit Complete Queue Start Address*/
	ffreg_t	tcq_ed_adr;	/* Transmit Complete Queue End Address	*/
	ffreg_t	tcq_rd_ptr;	/* Transmit Complete Queue पढ़ो poपूर्णांकer */
	ffreg_t	tcq_wr_ptr;	/* Transmit Complete Queue ग_लिखो poपूर्णांकer*/
	u_पूर्णांक	filler38[0x40 - 0x38];
	ffreg_t	queue_base;	/* Base address क्रम PRQ and TCQ		*/
	ffreg_t	desc_base;	/* Base address of descriptor table	*/
	u_पूर्णांक	filler42[0x45 - 0x42];
	ffreg_t	mode_reg_0;	/* Mode रेजिस्टर 0			*/
	ffreg_t	mode_reg_1;	/* Mode रेजिस्टर 1			*/
	ffreg_t	पूर्णांकr_status_reg;/* Interrupt Status रेजिस्टर		*/
	ffreg_t	mask_reg;	/* Mask Register			*/
	ffreg_t	cell_ctr_high1; /* Total cell transfer count (high)	*/
	ffreg_t	cell_ctr_lo1;	/* Total cell transfer count (low)	*/
	ffreg_t	state_reg;	/* Status रेजिस्टर			*/
	u_पूर्णांक	filler4c[0x58 - 0x4c];
	ffreg_t	curr_desc_num;	/* Contains the current descriptor num	*/
	ffreg_t	next_desc;	/* Next descriptor			*/
	ffreg_t	next_vc;	/* Next VC				*/
	u_पूर्णांक	filler5b[0x5d - 0x5b];
	ffreg_t	present_slot_cnt;/* Present slot count			*/
	u_पूर्णांक	filler5e[0x6a - 0x5e];
	ffreg_t	new_desc_num;	/* New descriptor number		*/
	ffreg_t	new_vc;		/* New VC				*/
	ffreg_t	sched_tbl_ptr;	/* Schedule table poपूर्णांकer		*/
	ffreg_t	vbrwq_wptr;	/* VBR रुको queue ग_लिखो poपूर्णांकer		*/
	ffreg_t	vbrwq_rptr;	/* VBR रुको queue पढ़ो poपूर्णांकer		*/
	ffreg_t	abrwq_wptr;	/* ABR रुको queue ग_लिखो poपूर्णांकer		*/
	ffreg_t	abrwq_rptr;	/* ABR रुको queue पढ़ो poपूर्णांकer		*/
	ffreg_t	ubrwq_wptr;	/* UBR रुको queue ग_लिखो poपूर्णांकer		*/
	ffreg_t	ubrwq_rptr;	/* UBR रुको queue पढ़ो poपूर्णांकer		*/
	ffreg_t	cbr_vc;		/* CBR VC				*/
	ffreg_t	vbr_sb_vc;	/* VBR SB VC				*/
	ffreg_t	abr_sb_vc;	/* ABR SB VC				*/
	ffreg_t	ubr_sb_vc;	/* UBR SB VC				*/
	ffreg_t	vbr_next_link;	/* VBR next link			*/
	ffreg_t	abr_next_link;	/* ABR next link			*/
	ffreg_t	ubr_next_link;	/* UBR next link			*/
	u_पूर्णांक	filler7a[0x7c-0x7a];
	ffreg_t	out_rate_head;	/* Out of rate head			*/
	u_पूर्णांक	filler7d[0xca-0x7d]; /* pad out to full address space	*/
	ffreg_t	cell_ctr_high1_nc;/* Total cell transfer count (high)	*/
	ffreg_t	cell_ctr_lo1_nc;/* Total cell transfer count (low)	*/
	u_पूर्णांक	fillercc[0x100-0xcc]; /* pad out to full address space	 */
पूर्ण ffredn_t;

प्रकार काष्ठा _rfredn_t अणु
        rreg_t  mode_reg_0;     /* Mode रेजिस्टर 0                      */
        rreg_t  protocol_id;    /* Protocol ID                          */
        rreg_t  mask_reg;       /* Mask Register                        */
        rreg_t  पूर्णांकr_status_reg;/* Interrupt status रेजिस्टर            */
        rreg_t  drp_pkt_cntr;   /* Dropped packet cntr (clear on पढ़ो)  */
        rreg_t  err_cntr;       /* Error Counter (cleared on पढ़ो)      */
        u_पूर्णांक   filler6[0x08 - 0x06];
        rreg_t  raw_base_adr;   /* Base addr क्रम raw cell Q             */
        u_पूर्णांक   filler2[0x0c - 0x09];
        rreg_t  cell_ctr0;      /* Cell Counter 0 (cleared when पढ़ो)   */
        rreg_t  cell_ctr1;      /* Cell Counter 1 (cleared when पढ़ो)   */
        u_पूर्णांक   filler3[0x0f - 0x0e];
        rreg_t  cmd_reg;        /* Command रेजिस्टर                     */
        rreg_t  desc_base;      /* Base address क्रम description table   */
        rreg_t  vc_lkup_base;   /* Base address क्रम VC lookup table     */
        rreg_t  reass_base;     /* Base address क्रम reassembler table   */
        rreg_t  queue_base;     /* Base address क्रम Communication queue */
        u_पूर्णांक   filler14[0x16 - 0x14];
        rreg_t  pkt_पंचांग_cnt;     /* Packet Timeout and count रेजिस्टर    */
        rreg_t  पंचांगout_range;    /* Range of reassembley IDs क्रम समयout */
        rreg_t  पूर्णांकrvl_cntr;    /* Packet aging पूर्णांकerval counter        */
        rreg_t  पंचांगout_indx;     /* index of pkt being tested क्रम aging  */
        u_पूर्णांक   filler1a[0x1c - 0x1a];
        rreg_t  vp_lkup_base;   /* Base address क्रम VP lookup table     */
        rreg_t  vp_filter;      /* VP filter रेजिस्टर                   */
        rreg_t  abr_lkup_base;  /* Base address of ABR VC Table         */
        u_पूर्णांक   filler1f[0x24 - 0x1f];
        rreg_t  fdq_st_adr;     /* Free desc queue start address        */
        rreg_t  fdq_ed_adr;     /* Free desc queue end address          */
        rreg_t  fdq_rd_ptr;     /* Free desc queue पढ़ो poपूर्णांकer         */
        rreg_t  fdq_wr_ptr;     /* Free desc queue ग_लिखो poपूर्णांकer        */
        rreg_t  pcq_st_adr;     /* Packet Complete queue start address  */
        rreg_t  pcq_ed_adr;     /* Packet Complete queue end address    */
        rreg_t  pcq_rd_ptr;     /* Packet Complete queue पढ़ो poपूर्णांकer   */
        rreg_t  pcq_wr_ptr;     /* Packet Complete queue ग_लिखो poपूर्णांकer  */
        rreg_t  excp_st_adr;    /* Exception queue start address        */
        rreg_t  excp_ed_adr;    /* Exception queue end address          */
        rreg_t  excp_rd_ptr;    /* Exception queue पढ़ो poपूर्णांकer         */
        rreg_t  excp_wr_ptr;    /* Exception queue ग_लिखो poपूर्णांकer        */
        u_पूर्णांक   filler30[0x34 - 0x30];
        rreg_t  raw_st_adr;     /* Raw Cell start address               */
        rreg_t  raw_ed_adr;     /* Raw Cell end address                 */
        rreg_t  raw_rd_ptr;     /* Raw Cell पढ़ो poपूर्णांकer                */
        rreg_t  raw_wr_ptr;     /* Raw Cell ग_लिखो poपूर्णांकer               */
        rreg_t  state_reg;      /* State Register                       */
        u_पूर्णांक   filler39[0x42 - 0x39];
        rreg_t  buf_size;       /* Buffer size                          */
        u_पूर्णांक   filler43;
        rreg_t  xtra_rm_offset; /* Offset of the additional turnaround RM */
        u_पूर्णांक   filler45[0x84 - 0x45];
        rreg_t  drp_pkt_cntr_nc;/* Dropped Packet cntr, Not clear on rd */
        rreg_t  err_cntr_nc;    /* Error Counter, Not clear on पढ़ो     */
        u_पूर्णांक   filler86[0x8c - 0x86];
        rreg_t  cell_ctr0_nc;   /* Cell Counter 0,  Not clear on पढ़ो   */
        rreg_t  cell_ctr1_nc;   /* Cell Counter 1, Not clear on पढ़ो    */
        u_पूर्णांक   filler8e[0x100-0x8e]; /* pad out to full address space   */
पूर्ण rfredn_t;

प्रकार काष्ठा अणु
        /* Atlantic */
        ffredn_t        ffredn;         /* F FRED                       */
        rfredn_t        rfredn;         /* R FRED                       */
पूर्ण ia_regs_t;

प्रकार काष्ठा अणु
	u_लघु		f_vc_type;	/* VC type              */
	u_लघु		f_nrm;		/* Nrm			*/
	u_लघु		f_nrmexp;	/* Nrm Exp              */
	u_लघु		reserved6;	/* 			*/
	u_लघु		f_crm;		/* Crm			*/
	u_लघु		reserved10;	/* Reserved		*/
	u_लघु		reserved12;	/* Reserved		*/
	u_लघु		reserved14;	/* Reserved		*/
	u_लघु		last_cell_slot;	/* last_cell_slot_count	*/
	u_लघु		f_pcr;		/* Peak Cell Rate	*/
	u_लघु		fraction;	/* fraction		*/
	u_लघु		f_icr;		/* Initial Cell Rate	*/
	u_लघु		f_cdf;		/* */
	u_लघु		f_mcr;		/* Minimum Cell Rate	*/
	u_लघु		f_acr;		/* Allowed Cell Rate	*/
	u_लघु		f_status;	/* */
पूर्ण f_vc_abr_entry;

प्रकार काष्ठा अणु
        u_लघु         r_status_rdf;   /* status + RDF         */
        u_लघु         r_air;          /* AIR                  */
        u_लघु         reserved4[14];  /* Reserved             */
पूर्ण r_vc_abr_entry;   

#घोषणा MRM 3

प्रकार काष्ठा srv_cls_param अणु
        u32 class_type;         /* CBR/VBR/ABR/UBR; use the क्रमागत above */
        u32 pcr;                /* Peak Cell Rate (24-bit) */ 
        /* VBR parameters */
        u32 scr;                /* sustainable cell rate */
        u32 max_burst_size;     /* ?? cell rate or data rate */
 
        /* ABR only UNI 4.0 Parameters */
        u32 mcr;                /* Min Cell Rate (24-bit) */
        u32 icr;                /* Initial Cell Rate (24-bit) */
        u32 tbe;                /* Transient Buffer Exposure (24-bit) */
        u32 frtt;               /* Fixed Round Trip Time (24-bit) */
 
#अगर 0   /* Additional Parameters of TM 4.0 */
bits  31          30           29          28       27-25 24-22 21-19  18-9
-----------------------------------------------------------------------------
| NRM present | TRM prsnt | CDF prsnt | ADTF prsnt | NRM | TRM | CDF | ADTF |
-----------------------------------------------------------------------------
#पूर्ण_अगर /* 0 */
 
        u8 nrm;                 /* Max # of Cells क्रम each क्रमward RM
                                        cell (3-bit) */
        u8 trm;                 /* Time between क्रमward RM cells (3-bit) */
        u16 adtf;               /* ACR Decrease Time Factor (10-bit) */
        u8 cdf;                 /* Cutoff Decrease Factor (3-bit) */
        u8 rअगर;                 /* Rate Increment Factor (4-bit) */
        u8 rdf;                 /* Rate Decrease Factor (4-bit) */
        u8 reserved;            /* 8 bits to keep काष्ठाure word aligned */
पूर्ण srv_cls_param_t;

काष्ठा testTable_t अणु
	u16 lastTime; 
	u16 fract; 
	u8 vc_status;
पूर्ण; 

प्रकार काष्ठा अणु
	u16 vci;
	u16 error;
पूर्ण RX_ERROR_Q;

प्रकार काष्ठा अणु
	u8 active: 1; 
	u8 abr: 1; 
	u8 ubr: 1; 
	u8 cnt: 5;
#घोषणा VC_ACTIVE 	0x01
#घोषणा VC_ABR		0x02
#घोषणा VC_UBR		0x04
पूर्ण vcstatus_t;
  
काष्ठा ia_rfL_t अणु
    	u32  fdq_st;     /* Free desc queue start address        */
        u32  fdq_ed;     /* Free desc queue end address          */
        u32  fdq_rd;     /* Free desc queue पढ़ो poपूर्णांकer         */
        u32  fdq_wr;     /* Free desc queue ग_लिखो poपूर्णांकer        */
        u32  pcq_st;     /* Packet Complete queue start address  */
        u32  pcq_ed;     /* Packet Complete queue end address    */
        u32  pcq_rd;     /* Packet Complete queue पढ़ो poपूर्णांकer   */
        u32  pcq_wr;     /* Packet Complete queue ग_लिखो poपूर्णांकer  */ 
पूर्ण;

काष्ठा ia_ffL_t अणु
	u32  prq_st;     /* Packet Ready Queue Start Address     */
        u32  prq_ed;     /* Packet Ready Queue End Address       */
        u32  prq_wr;     /* Packet Ready Queue ग_लिखो poपूर्णांकer     */
        u32  tcq_st;     /* Transmit Complete Queue Start Address*/
        u32  tcq_ed;     /* Transmit Complete Queue End Address  */
        u32  tcq_rd;     /* Transmit Complete Queue पढ़ो poपूर्णांकer */
पूर्ण;

काष्ठा desc_tbl_t अणु
        u32 बारtamp;
        काष्ठा ia_vcc *iavcc;
        काष्ठा sk_buff *txskb;
पूर्ण; 

प्रकार काष्ठा ia_rtn_q अणु
   काष्ठा desc_tbl_t data;
   काष्ठा ia_rtn_q *next, *tail;
पूर्ण IARTN_Q;

#घोषणा SUNI_LOSV   	0x04
क्रमागत ia_suni अणु
	SUNI_MASTER_RESET	= 0x000, /* SUNI Master Reset and Identity   */
	SUNI_MASTER_CONFIG	= 0x004, /* SUNI Master Configuration        */
	SUNI_MASTER_INTR_STAT	= 0x008, /* SUNI Master Interrupt Status     */
	SUNI_RESERVED1		= 0x00c, /* Reserved                         */
	SUNI_MASTER_CLK_MONITOR	= 0x010, /* SUNI Master Clock Monitor        */
	SUNI_MASTER_CONTROL	= 0x014, /* SUNI Master Clock Monitor        */
					 /* Reserved (10)                    */
	SUNI_RSOP_CONTROL	= 0x040, /* RSOP Control/Interrupt Enable    */
	SUNI_RSOP_STATUS	= 0x044, /* RSOP Status/Interrupt States     */
	SUNI_RSOP_SECTION_BIP8L	= 0x048, /* RSOP Section BIP-8 LSB           */
	SUNI_RSOP_SECTION_BIP8M	= 0x04c, /* RSOP Section BIP-8 MSB           */

	SUNI_TSOP_CONTROL	= 0x050, /* TSOP Control                     */
	SUNI_TSOP_DIAG		= 0x054, /* TSOP Disgnostics                 */
					 /* Reserved (2)                     */
	SUNI_RLOP_CS		= 0x060, /* RLOP Control/Status              */
	SUNI_RLOP_INTR		= 0x064, /* RLOP Interrupt Enable/Status     */
	SUNI_RLOP_LINE_BIP24L	= 0x068, /* RLOP Line BIP-24 LSB             */
	SUNI_RLOP_LINE_BIP24	= 0x06c, /* RLOP Line BIP-24                 */
	SUNI_RLOP_LINE_BIP24M	= 0x070, /* RLOP Line BIP-24 MSB             */
	SUNI_RLOP_LINE_FEBEL	= 0x074, /* RLOP Line FEBE LSB               */
	SUNI_RLOP_LINE_FEBE	= 0x078, /* RLOP Line FEBE                   */
	SUNI_RLOP_LINE_FEBEM	= 0x07c, /* RLOP Line FEBE MSB               */

	SUNI_TLOP_CONTROL	= 0x080, /* TLOP Control                     */
	SUNI_TLOP_DISG		= 0x084, /* TLOP Disgnostics                 */
					 /* Reserved (14)                    */
	SUNI_RPOP_CS		= 0x0c0, /* RPOP Status/Control              */
	SUNI_RPOP_INTR		= 0x0c4, /* RPOP Interrupt/Status            */
	SUNI_RPOP_RESERVED	= 0x0c8, /* RPOP Reserved                    */
	SUNI_RPOP_INTR_ENA	= 0x0cc, /* RPOP Interrupt Enable            */
					 /* Reserved (3)                     */
	SUNI_RPOP_PATH_SIG	= 0x0dc, /* RPOP Path Signal Label           */
	SUNI_RPOP_BIP8L		= 0x0e0, /* RPOP Path BIP-8 LSB              */
	SUNI_RPOP_BIP8M		= 0x0e4, /* RPOP Path BIP-8 MSB              */
	SUNI_RPOP_FEBEL		= 0x0e8, /* RPOP Path FEBE LSB               */
	SUNI_RPOP_FEBEM		= 0x0ec, /* RPOP Path FEBE MSB               */
					 /* Reserved (4)                     */
	SUNI_TPOP_CNTRL_DAIG	= 0x100, /* TPOP Control/Disgnostics         */
	SUNI_TPOP_POINTER_CTRL	= 0x104, /* TPOP Poपूर्णांकer Control             */
	SUNI_TPOP_SOURCER_CTRL	= 0x108, /* TPOP Source Control              */
					 /* Reserved (2)                     */
	SUNI_TPOP_ARB_PRTL	= 0x114, /* TPOP Arbitrary Poपूर्णांकer LSB       */
	SUNI_TPOP_ARB_PRTM	= 0x118, /* TPOP Arbitrary Poपूर्णांकer MSB       */
	SUNI_TPOP_RESERVED2	= 0x11c, /* TPOP Reserved                    */
	SUNI_TPOP_PATH_SIG	= 0x120, /* TPOP Path Signal Lable           */
	SUNI_TPOP_PATH_STATUS	= 0x124, /* TPOP Path Status                 */
					 /* Reserved (6)                     */
	SUNI_RACP_CS		= 0x140, /* RACP Control/Status              */
	SUNI_RACP_INTR		= 0x144, /* RACP Interrupt Enable/Status     */
	SUNI_RACP_HDR_PATTERN	= 0x148, /* RACP Match Header Pattern        */
	SUNI_RACP_HDR_MASK	= 0x14c, /* RACP Match Header Mask           */
	SUNI_RACP_CORR_HCS	= 0x150, /* RACP Correctable HCS Error Count */
	SUNI_RACP_UNCORR_HCS	= 0x154, /* RACP Uncorrectable HCS Err Count */
					 /* Reserved (10)                    */
	SUNI_TACP_CONTROL	= 0x180, /* TACP Control                     */
	SUNI_TACP_IDLE_HDR_PAT	= 0x184, /* TACP Idle Cell Header Pattern    */
	SUNI_TACP_IDLE_PAY_PAY	= 0x188, /* TACP Idle Cell Payld Octet Patrn */
					 /* Reserved (5)                     */
					 /* Reserved (24)                    */
	/* FIXME: unused but name conflicts.
	 * SUNI_MASTER_TEST	= 0x200,    SUNI Master Test                 */
	SUNI_RESERVED_TEST	= 0x204  /* SUNI Reserved क्रम Test           */
पूर्ण;

प्रकार काष्ठा _SUNI_STATS_
अणु
   u32 valid;                       // 1 = oc3 PHY card
   u32 carrier_detect;              // GPIN input
   // RSOP: receive section overhead processor
   u16 rsop_oof_state;              // 1 = out of frame
   u16 rsop_lof_state;              // 1 = loss of frame
   u16 rsop_los_state;              // 1 = loss of संकेत
   u32 rsop_los_count;              // loss of संकेत count
   u32 rsop_bse_count;              // section BIP-8 error count
   // RLOP: receive line overhead processor
   u16 rlop_ferf_state;             // 1 = far end receive failure
   u16 rlop_lais_state;             // 1 = line AIS
   u32 rlop_lbe_count;              // BIP-24 count
   u32 rlop_febe_count;             // FEBE count;
   // RPOP: receive path overhead processor
   u16 rpop_lop_state;              // 1 = LOP
   u16 rpop_pais_state;             // 1 = path AIS
   u16 rpop_pyel_state;             // 1 = path yellow alert
   u32 rpop_bip_count;              // path BIP-8 error count
   u32 rpop_febe_count;             // path FEBE error count
   u16 rpop_psig;                   // path संकेत label value
   // RACP: receive ATM cell processor
   u16 racp_hp_state;               // hunt/presync state
   u32 racp_fu_count;               // FIFO underrun count
   u32 racp_fo_count;               // FIFO overrun count
   u32 racp_chcs_count;             // correctable HCS error count
   u32 racp_uchcs_count;            // uncorrectable HCS error count
पूर्ण IA_SUNI_STATS; 

प्रकार काष्ठा iadev_priv अणु
	/*-----base poपूर्णांकers पूर्णांकo (i)chipSAR+ address space */   
	u32 __iomem *phy;	/* Base poपूर्णांकer पूर्णांकo phy (SUNI). */
	u32 __iomem *dma;	/* Base poपूर्णांकer पूर्णांकo DMA control रेजिस्टरs. */
	u32 __iomem *reg;	/* Base poपूर्णांकer to SAR रेजिस्टरs. */
	u32 __iomem *seg_reg;		/* base poपूर्णांकer to segmentation engine  
						पूर्णांकernal रेजिस्टरs */  
	u32 __iomem *reass_reg;		/* base poपूर्णांकer to reassemble engine  
						पूर्णांकernal रेजिस्टरs */  
	u32 __iomem *ram;		/* base poपूर्णांकer to SAR RAM */  
	व्योम __iomem *seg_ram;  
	व्योम __iomem *reass_ram;  
	काष्ठा dle_q tx_dle_q;  
	काष्ठा मुक्त_desc_q *tx_मुक्त_desc_qhead;  
	काष्ठा sk_buff_head tx_dma_q, tx_backlog;  
        spinlock_t            tx_lock;
        IARTN_Q               tx_वापस_q;
        u32                   बंद_pending;
        रुको_queue_head_t    बंद_रुको;
        रुको_queue_head_t    समयout_रुको;
	काष्ठा cpcs_trailer_desc *tx_buf;
        u16 num_tx_desc, tx_buf_sz, rate_limit;
        u32 tx_cell_cnt, tx_pkt_cnt;
        व्योम __iomem *MAIN_VC_TABLE_ADDR, *EXT_VC_TABLE_ADDR, *ABR_SCHED_TABLE_ADDR;
	काष्ठा dle_q rx_dle_q;  
	काष्ठा मुक्त_desc_q *rx_मुक्त_desc_qhead;  
	काष्ठा sk_buff_head rx_dma_q;  
	spinlock_t rx_lock;
	काष्ठा aपंचांग_vcc **rx_खोलो;	/* list of all खोलो VCs */  
        u16 num_rx_desc, rx_buf_sz, rxing;
        u32 rx_pkt_ram, rx_पंचांगp_cnt;
        अचिन्हित दीर्घ rx_पंचांगp_jअगर;
        व्योम __iomem *RX_DESC_BASE_ADDR;
        u32 drop_rxpkt, drop_rxcell, rx_cell_cnt, rx_pkt_cnt;
	काष्ठा aपंचांग_dev *next_board;	/* other iphase devices */  
	काष्ठा pci_dev *pci;  
	पूर्णांक mem;  
	अचिन्हित पूर्णांक real_base;	/* real and भव base address */  
	व्योम __iomem *base;
	अचिन्हित पूर्णांक pci_map_size;	/*pci map size of board */  
	अचिन्हित अक्षर irq;  
	अचिन्हित अक्षर bus;  
	अचिन्हित अक्षर dev_fn;  
        u_लघु  phy_type;
        u_लघु  num_vc, memSize, memType;
        काष्ठा ia_ffL_t ffL;
        काष्ठा ia_rfL_t rfL;
        /* Suni stat */
        // IA_SUNI_STATS suni_stats;
        अचिन्हित अक्षर carrier_detect;
        /* CBR related */
        // transmit DMA & Receive
        अचिन्हित पूर्णांक tx_dma_cnt;     // number of elements on dma queue
        अचिन्हित पूर्णांक rx_dma_cnt;     // number of elements on rx dma queue
        अचिन्हित पूर्णांक NumEnabledCBR;  // number of CBR VCI's enabled.     CBR
        // receive MARK  क्रम Cell FIFO
        अचिन्हित पूर्णांक rx_mark_cnt;    // number of elements on mark queue
        अचिन्हित पूर्णांक CbrTotEntries;  // Total CBR Entries in Scheduling Table.
        अचिन्हित पूर्णांक CbrRemEntries;  // Reमुख्यing CBR Entries in Scheduling Table.
        अचिन्हित पूर्णांक CbrEntryPt;     // CBR Sched Table Entry Poपूर्णांक.
        अचिन्हित पूर्णांक Granularity;    // CBR Granularity given Table Size.
        /* ABR related */
	अचिन्हित पूर्णांक  sum_mcr, sum_cbr, LineRate;
	अचिन्हित पूर्णांक  n_abr;
        काष्ठा desc_tbl_t *desc_tbl;
        u_लघु host_tcq_wr;
        काष्ठा testTable_t **testTable;
	dma_addr_t tx_dle_dma;
	dma_addr_t rx_dle_dma;
पूर्ण IADEV;
  
  
#घोषणा INPH_IA_DEV(d) ((IADEV *) (d)->dev_data)  
#घोषणा INPH_IA_VCC(v) ((काष्ठा ia_vcc *) (v)->dev_data)  

/******************* IDT77105 25MB/s PHY DEFINE *****************************/
क्रमागत ia_mb25 अणु
	MB25_MASTER_CTRL	= 0x00, /* Master control		     */
	MB25_INTR_STATUS	= 0x04,	/* Interrupt status		     */
	MB25_DIAG_CONTROL	= 0x08,	/* Diagnostic control		     */
	MB25_LED_HEC		= 0x0c,	/* LED driver and HEC status/control */
	MB25_LOW_BYTE_COUNTER	= 0x10,
	MB25_HIGH_BYTE_COUNTER	= 0x14
पूर्ण;

/*
 * Master Control
 */
#घोषणा	MB25_MC_UPLO	0x80		/* UPLO				     */
#घोषणा	MB25_MC_DREC	0x40		/* Discard receive cell errors	     */
#घोषणा	MB25_MC_ECEIO	0x20		/* Enable Cell Error Interrupts Only */
#घोषणा	MB25_MC_TDPC	0x10		/* Transmit data parity check	     */
#घोषणा	MB25_MC_DRIC	0x08		/* Discard receive idle cells	     */
#घोषणा	MB25_MC_HALTTX	0x04		/* Halt Tx			     */
#घोषणा	MB25_MC_UMS	0x02		/* UTOPIA mode select		     */
#घोषणा	MB25_MC_ENABLED	0x01		/* Enable पूर्णांकerrupt		     */

/*
 * Interrupt Status
 */
#घोषणा	MB25_IS_GSB	0x40		/* GOOD Symbol Bit		     */	
#घोषणा	MB25_IS_HECECR	0x20		/* HEC error cell received	     */
#घोषणा	MB25_IS_SCR	0x10		/* "Short Cell" Received	     */
#घोषणा	MB25_IS_TPE	0x08		/* Trnamsit Parity Error	     */
#घोषणा	MB25_IS_RSCC	0x04		/* Receive Signal Condition change   */
#घोषणा	MB25_IS_RCSE	0x02		/* Received Cell Symbol Error	     */
#घोषणा	MB25_IS_RFIFOO	0x01		/* Received FIFO Overrun	     */

/*
 * Diagnostic Control
 */
#घोषणा	MB25_DC_FTXCD	0x80		/* Force TxClav deनिश्चित	     */	
#घोषणा	MB25_DC_RXCOS	0x40		/* RxClav operation select	     */
#घोषणा	MB25_DC_ECEIO	0x20		/* Single/Multi-PHY config select    */
#घोषणा	MB25_DC_RLFLUSH	0x10		/* Clear receive FIFO		     */
#घोषणा	MB25_DC_IXPE	0x08		/* Insert xmit payload error	     */
#घोषणा	MB25_DC_IXHECE	0x04		/* Insert Xmit HEC Error	     */
#घोषणा	MB25_DC_LB_MASK	0x03		/* Loopback control mask	     */

#घोषणा	MB25_DC_LL	0x03		/* Line Loopback		     */
#घोषणा	MB25_DC_PL	0x02		/* PHY Loopback			     */
#घोषणा	MB25_DC_NM	0x00		

#घोषणा FE_MASK 	0x00F0
#घोषणा FE_MULTI_MODE	0x0000
#घोषणा FE_SINGLE_MODE  0x0010 
#घोषणा FE_UTP_OPTION  	0x0020
#घोषणा FE_25MBIT_PHY	0x0040
#घोषणा FE_DS3_PHY      0x0080          /* DS3 */
#घोषणा FE_E3_PHY       0x0090          /* E3 */
		     
/*********************** SUNI_PM7345 PHY DEFINE HERE *********************/
क्रमागत suni_pm7345 अणु
	SUNI_CONFIG			= 0x000, /* SUNI Configuration */
	SUNI_INTR_ENBL			= 0x004, /* SUNI Interrupt Enable */
	SUNI_INTR_STAT			= 0x008, /* SUNI Interrupt Status */
	SUNI_CONTROL			= 0x00c, /* SUNI Control */
	SUNI_ID_RESET			= 0x010, /* SUNI Reset and Identity */
	SUNI_DATA_LINK_CTRL		= 0x014,
	SUNI_RBOC_CONF_INTR_ENBL	= 0x018,
	SUNI_RBOC_STAT			= 0x01c,
	SUNI_DS3_FRM_CFG		= 0x020,
	SUNI_DS3_FRM_INTR_ENBL		= 0x024,
	SUNI_DS3_FRM_INTR_STAT		= 0x028,
	SUNI_DS3_FRM_STAT		= 0x02c,
	SUNI_RFDL_CFG			= 0x030,
	SUNI_RFDL_ENBL_STAT		= 0x034,
	SUNI_RFDL_STAT			= 0x038,
	SUNI_RFDL_DATA			= 0x03c,
	SUNI_PMON_CHNG			= 0x040,
	SUNI_PMON_INTR_ENBL_STAT	= 0x044,
	/* SUNI_RESERVED1 (0x13 - 0x11) */
	SUNI_PMON_LCV_EVT_CNT_LSB	= 0x050,
	SUNI_PMON_LCV_EVT_CNT_MSB	= 0x054,
	SUNI_PMON_FBE_EVT_CNT_LSB	= 0x058,
	SUNI_PMON_FBE_EVT_CNT_MSB	= 0x05c,
	SUNI_PMON_SEZ_DET_CNT_LSB	= 0x060,
	SUNI_PMON_SEZ_DET_CNT_MSB	= 0x064,
	SUNI_PMON_PE_EVT_CNT_LSB	= 0x068,
	SUNI_PMON_PE_EVT_CNT_MSB	= 0x06c,
	SUNI_PMON_PPE_EVT_CNT_LSB	= 0x070,
	SUNI_PMON_PPE_EVT_CNT_MSB	= 0x074,
	SUNI_PMON_FEBE_EVT_CNT_LSB	= 0x078,
	SUNI_PMON_FEBE_EVT_CNT_MSB	= 0x07c,
	SUNI_DS3_TRAN_CFG		= 0x080,
	SUNI_DS3_TRAN_DIAG		= 0x084,
	/* SUNI_RESERVED2 (0x23 - 0x21) */
	SUNI_XFDL_CFG			= 0x090,
	SUNI_XFDL_INTR_ST		= 0x094,
	SUNI_XFDL_XMIT_DATA		= 0x098,
	SUNI_XBOC_CODE			= 0x09c,
	SUNI_SPLR_CFG			= 0x0a0,
	SUNI_SPLR_INTR_EN		= 0x0a4,
	SUNI_SPLR_INTR_ST		= 0x0a8,
	SUNI_SPLR_STATUS		= 0x0ac,
	SUNI_SPLT_CFG			= 0x0b0,
	SUNI_SPLT_CNTL			= 0x0b4,
	SUNI_SPLT_DIAG_G1		= 0x0b8,
	SUNI_SPLT_F1			= 0x0bc,
	SUNI_CPPM_LOC_METERS		= 0x0c0,
	SUNI_CPPM_CHG_OF_CPPM_PERF_METR	= 0x0c4,
	SUNI_CPPM_B1_ERR_CNT_LSB	= 0x0c8,
	SUNI_CPPM_B1_ERR_CNT_MSB	= 0x0cc,
	SUNI_CPPM_FRAMING_ERR_CNT_LSB	= 0x0d0,
	SUNI_CPPM_FRAMING_ERR_CNT_MSB	= 0x0d4,
	SUNI_CPPM_FEBE_CNT_LSB		= 0x0d8,
	SUNI_CPPM_FEBE_CNT_MSB		= 0x0dc,
	SUNI_CPPM_HCS_ERR_CNT_LSB	= 0x0e0,
	SUNI_CPPM_HCS_ERR_CNT_MSB	= 0x0e4,
	SUNI_CPPM_IDLE_UN_CELL_CNT_LSB	= 0x0e8,
	SUNI_CPPM_IDLE_UN_CELL_CNT_MSB	= 0x0ec,
	SUNI_CPPM_RCV_CELL_CNT_LSB	= 0x0f0,
	SUNI_CPPM_RCV_CELL_CNT_MSB	= 0x0f4,
	SUNI_CPPM_XMIT_CELL_CNT_LSB	= 0x0f8,
	SUNI_CPPM_XMIT_CELL_CNT_MSB	= 0x0fc,
	SUNI_RXCP_CTRL			= 0x100,
	SUNI_RXCP_FCTRL			= 0x104,
	SUNI_RXCP_INTR_EN_STS		= 0x108,
	SUNI_RXCP_IDLE_PAT_H1		= 0x10c,
	SUNI_RXCP_IDLE_PAT_H2		= 0x110,
	SUNI_RXCP_IDLE_PAT_H3		= 0x114,
	SUNI_RXCP_IDLE_PAT_H4		= 0x118,
	SUNI_RXCP_IDLE_MASK_H1		= 0x11c,
	SUNI_RXCP_IDLE_MASK_H2		= 0x120,
	SUNI_RXCP_IDLE_MASK_H3		= 0x124,
	SUNI_RXCP_IDLE_MASK_H4		= 0x128,
	SUNI_RXCP_CELL_PAT_H1		= 0x12c,
	SUNI_RXCP_CELL_PAT_H2		= 0x130,
	SUNI_RXCP_CELL_PAT_H3		= 0x134,
	SUNI_RXCP_CELL_PAT_H4		= 0x138,
	SUNI_RXCP_CELL_MASK_H1		= 0x13c,
	SUNI_RXCP_CELL_MASK_H2		= 0x140,
	SUNI_RXCP_CELL_MASK_H3		= 0x144,
	SUNI_RXCP_CELL_MASK_H4		= 0x148,
	SUNI_RXCP_HCS_CS		= 0x14c,
	SUNI_RXCP_LCD_CNT_THRESHOLD	= 0x150,
	/* SUNI_RESERVED3 (0x57 - 0x54) */
	SUNI_TXCP_CTRL			= 0x160,
	SUNI_TXCP_INTR_EN_STS		= 0x164,
	SUNI_TXCP_IDLE_PAT_H1		= 0x168,
	SUNI_TXCP_IDLE_PAT_H2		= 0x16c,
	SUNI_TXCP_IDLE_PAT_H3		= 0x170,
	SUNI_TXCP_IDLE_PAT_H4		= 0x174,
	SUNI_TXCP_IDLE_PAT_H5		= 0x178,
	SUNI_TXCP_IDLE_PAYLOAD		= 0x17c,
	SUNI_E3_FRM_FRAM_OPTIONS	= 0x180,
	SUNI_E3_FRM_MAINT_OPTIONS	= 0x184,
	SUNI_E3_FRM_FRAM_INTR_ENBL	= 0x188,
	SUNI_E3_FRM_FRAM_INTR_IND_STAT	= 0x18c,
	SUNI_E3_FRM_MAINT_INTR_ENBL	= 0x190,
	SUNI_E3_FRM_MAINT_INTR_IND	= 0x194,
	SUNI_E3_FRM_MAINT_STAT		= 0x198,
	SUNI_RESERVED4			= 0x19c,
	SUNI_E3_TRAN_FRAM_OPTIONS	= 0x1a0,
	SUNI_E3_TRAN_STAT_DIAG_OPTIONS	= 0x1a4,
	SUNI_E3_TRAN_BIP_8_ERR_MASK	= 0x1a8,
	SUNI_E3_TRAN_MAINT_ADAPT_OPTS	= 0x1ac,
	SUNI_TTB_CTRL			= 0x1b0,
	SUNI_TTB_TRAIL_TRACE_ID_STAT	= 0x1b4,
	SUNI_TTB_IND_ADDR		= 0x1b8,
	SUNI_TTB_IND_DATA		= 0x1bc,
	SUNI_TTB_EXP_PAYLOAD_TYPE	= 0x1c0,
	SUNI_TTB_PAYLOAD_TYPE_CTRL_STAT	= 0x1c4,
	/* SUNI_PAD5 (0x7f - 0x71) */
	SUNI_MASTER_TEST		= 0x200,
	/* SUNI_PAD6 (0xff - 0x80) */
पूर्ण;

#घोषणा SUNI_PM7345_T suni_pm7345_t
#घोषणा SUNI_PM7345     0x20            /* Suni chip type */
#घोषणा SUNI_PM5346     0x30            /* Suni chip type */
/*
 * SUNI_PM7345 Configuration
 */
#घोषणा SUNI_PM7345_CLB         0x01    /* Cell loopback        */
#घोषणा SUNI_PM7345_PLB         0x02    /* Payload loopback     */
#घोषणा SUNI_PM7345_DLB         0x04    /* Diagnostic loopback  */
#घोषणा SUNI_PM7345_LLB         0x80    /* Line loopback        */
#घोषणा SUNI_PM7345_E3ENBL      0x40    /* E3 enable bit        */
#घोषणा SUNI_PM7345_LOOPT       0x10    /* LOOPT enable bit     */
#घोषणा SUNI_PM7345_FIFOBP      0x20    /* FIFO bypass          */
#घोषणा SUNI_PM7345_FRMRBP      0x08    /* Framer bypass        */
/*
 * DS3 FRMR Interrupt Enable
 */
#घोषणा SUNI_DS3_COFAE  0x80            /* Enable change of frame align */
#घोषणा SUNI_DS3_REDE   0x40            /* Enable DS3 RED state पूर्णांकr    */
#घोषणा SUNI_DS3_CBITE  0x20            /* Enable Appl ID channel पूर्णांकr  */
#घोषणा SUNI_DS3_FERFE  0x10            /* Enable Far End Receive Failure पूर्णांकr*/
#घोषणा SUNI_DS3_IDLE   0x08            /* Enable Idle संकेत पूर्णांकr      */
#घोषणा SUNI_DS3_AISE   0x04            /* Enable Alarm Indication संकेत पूर्णांकr*/
#घोषणा SUNI_DS3_OOFE   0x02            /* Enable Out of frame पूर्णांकr     */
#घोषणा SUNI_DS3_LOSE   0x01            /* Enable Loss of संकेत पूर्णांकr   */
 
/*
 * DS3 FRMR Status
 */
#घोषणा SUNI_DS3_ACE    0x80            /* Additional Configuration Reg */
#घोषणा SUNI_DS3_REDV   0x40            /* DS3 RED state                */
#घोषणा SUNI_DS3_CBITV  0x20            /* Application ID channel state */
#घोषणा SUNI_DS3_FERFV  0x10            /* Far End Receive Failure state*/
#घोषणा SUNI_DS3_IDLV   0x08            /* Idle संकेत state            */
#घोषणा SUNI_DS3_AISV   0x04            /* Alarm Indication संकेत state*/
#घोषणा SUNI_DS3_OOFV   0x02            /* Out of frame state           */
#घोषणा SUNI_DS3_LOSV   0x01            /* Loss of संकेत state         */

/*
 * E3 FRMR Interrupt/Status
 */
#घोषणा SUNI_E3_CZDI    0x40            /* Consecutive Zeros indicator  */
#घोषणा SUNI_E3_LOSI    0x20            /* Loss of संकेत पूर्णांकr status   */
#घोषणा SUNI_E3_LCVI    0x10            /* Line code violation पूर्णांकr     */
#घोषणा SUNI_E3_COFAI   0x08            /* Change of frame align पूर्णांकr   */
#घोषणा SUNI_E3_OOFI    0x04            /* Out of frame पूर्णांकr status     */
#घोषणा SUNI_E3_LOS     0x02            /* Loss of संकेत state         */
#घोषणा SUNI_E3_OOF     0x01            /* Out of frame state           */

/*
 * E3 FRMR Maपूर्णांकenance Status
 */
#घोषणा SUNI_E3_AISD    0x80            /* Alarm Indication संकेत state*/
#घोषणा SUNI_E3_FERF_RAI        0x40    /* FERF/RAI indicator           */
#घोषणा SUNI_E3_FEBE    0x20            /* Far End Block Error indicator*/

/*
 * RXCP Control/Status
 */
#घोषणा SUNI_DS3_HCSPASS        0x80    /* Pass cell with HEC errors    */
#घोषणा SUNI_DS3_HCSDQDB        0x40    /* Control octets in HCS calc   */
#घोषणा SUNI_DS3_HCSADD         0x20    /* Add coset poly               */
#घोषणा SUNI_DS3_HCK            0x10    /* Control FIFO data path पूर्णांकeg chk*/
#घोषणा SUNI_DS3_BLOCK          0x08    /* Enable cell filtering        */
#घोषणा SUNI_DS3_DSCR           0x04    /* Disable payload descrambling */
#घोषणा SUNI_DS3_OOCDV          0x02    /* Cell delineation state       */
#घोषणा SUNI_DS3_FIFORST        0x01    /* Cell FIFO reset              */

/*
 * RXCP Interrupt Enable/Status
 */
#घोषणा SUNI_DS3_OOCDE  0x80            /* Intr enable, change in CDS   */
#घोषणा SUNI_DS3_HCSE   0x40            /* Intr enable, corr HCS errors */
#घोषणा SUNI_DS3_FIFOE  0x20            /* Intr enable, unco HCS errors */
#घोषणा SUNI_DS3_OOCDI  0x10            /* SYNC state                   */
#घोषणा SUNI_DS3_UHCSI  0x08            /* Uncorr. HCS errors detected  */
#घोषणा SUNI_DS3_COCAI  0x04            /* Corr. HCS errors detected    */
#घोषणा SUNI_DS3_FOVRI  0x02            /* FIFO overrun                 */
#घोषणा SUNI_DS3_FUDRI  0x01            /* FIFO underrun                */

///////////////////SUNI_PM7345 PHY DEFINE END /////////////////////////////

/* ia_eeprom define*/
#घोषणा MEM_SIZE_MASK   0x000F          /* mask of 4 bits defining memory size*/
#घोषणा MEM_SIZE_128K   0x0000          /* board has 128k buffer */
#घोषणा MEM_SIZE_512K   0x0001          /* board has 512K of buffer */
#घोषणा MEM_SIZE_1M     0x0002          /* board has 1M of buffer */
                                        /* 0x3 to 0xF are reserved क्रम future */

#घोषणा FE_MASK         0x00F0          /* mask of 4 bits defining FE type */
#घोषणा FE_MULTI_MODE   0x0000          /* 155 MBit multimode fiber */
#घोषणा FE_SINGLE_MODE  0x0010          /* 155 MBit single mode laser */
#घोषणा FE_UTP_OPTION   0x0020          /* 155 MBit UTP front end */

#घोषणा	NOVRAM_SIZE	64
#घोषणा	CMD_LEN		10

/***********
 *
 *	Switches and defines क्रम header files.
 *
 *	The following defines are used to turn on and off
 *	various options in the header files. Primarily useful
 *	क्रम debugging.
 *
 ***********/

/*
 * a list of the commands that can be sent to the NOVRAM
 */

#घोषणा	EXTEND	0x100
#घोषणा	IAWRITE	0x140
#घोषणा	IAREAD	0x180
#घोषणा	ERASE	0x1c0

#घोषणा	EWDS	0x00
#घोषणा	WRAL	0x10
#घोषणा	ERAL	0x20
#घोषणा	EWEN	0x30

/*
 * these bits duplicate the hw_flip.h रेजिस्टर settings
 * note: how the data in / out bits are defined in the flipper specअगरication 
 */

#घोषणा	NVCE	0x02
#घोषणा	NVSK	0x01
#घोषणा	NVDO	0x08	
#घोषणा NVDI	0x04
/***********************
 *
 * This define ands the value and the current config रेजिस्टर and माला_दो
 * the result in the config रेजिस्टर
 *
 ***********************/

#घोषणा	CFG_AND(val) अणु \
		u32 t; \
		t = पढ़ोl(iadev->reg+IPHASE5575_EEPROM_ACCESS); \
		t &= (val); \
		ग_लिखोl(t, iadev->reg+IPHASE5575_EEPROM_ACCESS); \
	पूर्ण

/***********************
 *
 * This define ors the value and the current config रेजिस्टर and माला_दो
 * the result in the config रेजिस्टर
 *
 ***********************/

#घोषणा	CFG_OR(val) अणु \
		u32 t; \
		t =  पढ़ोl(iadev->reg+IPHASE5575_EEPROM_ACCESS); \
		t |= (val); \
		ग_लिखोl(t, iadev->reg+IPHASE5575_EEPROM_ACCESS); \
	पूर्ण

/***********************
 *
 * Send a command to the NOVRAM, the command is in cmd.
 *
 * clear CE and SK. Then निश्चित CE.
 * Clock each of the command bits out in the correct order with SK
 * निकास with CE still निश्चितed
 *
 ***********************/

#घोषणा	NVRAM_CMD(cmd) अणु \
		पूर्णांक	i; \
		u_लघु c = cmd; \
		CFG_AND(~(NVCE|NVSK)); \
		CFG_OR(NVCE); \
		क्रम (i=0; i<CMD_LEN; i++) अणु \
			NVRAM_CLKOUT((c & (1 << (CMD_LEN - 1))) ? 1 : 0); \
			c <<= 1; \
		पूर्ण \
	पूर्ण

/***********************
 *
 * clear the CE, this must be used after each command is complete
 *
 ***********************/

#घोषणा	NVRAM_CLR_CE	अणुCFG_AND(~NVCE)पूर्ण

/***********************
 *
 * घड़ी the data bit in bitval out to the NOVRAM.  The bitval must be
 * a 1 or 0, or the घड़ीout operation is undefined
 *
 ***********************/

#घोषणा	NVRAM_CLKOUT(bitval) अणु \
		CFG_AND(~NVDI); \
		CFG_OR((bitval) ? NVDI : 0); \
		CFG_OR(NVSK); \
		CFG_AND( ~NVSK); \
	पूर्ण

/***********************
 *
 * घड़ी the data bit in and वापस a 1 or 0, depending on the value
 * that was received from the NOVRAM
 *
 ***********************/

#घोषणा	NVRAM_CLKIN(value) अणु \
		u32 _t; \
		CFG_OR(NVSK); \
		CFG_AND(~NVSK); \
		_t = पढ़ोl(iadev->reg+IPHASE5575_EEPROM_ACCESS); \
		value = (_t & NVDO) ? 1 : 0; \
	पूर्ण


#पूर्ण_अगर /* IPHASE_H */
