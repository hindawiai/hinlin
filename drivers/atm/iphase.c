<शैली गुरु>
/******************************************************************************
         iphase.c: Device driver क्रम Interphase ATM PCI adapter cards 
                    Author: Peter Wang  <pwang@iphase.com>            
		   Some fixes: Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
                   Interphase Corporation  <www.iphase.com>           
                               Version: 1.0                           
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

#समावेश <linux/module.h>  
#समावेश <linux/kernel.h>  
#समावेश <linux/mm.h>  
#समावेश <linux/pci.h>  
#समावेश <linux/त्रुटिसं.स>  
#समावेश <linux/aपंचांग.h>  
#समावेश <linux/aपंचांगdev.h>  
#समावेश <linux/sonet.h>  
#समावेश <linux/skbuff.h>  
#समावेश <linux/समय.स>  
#समावेश <linux/delay.h>  
#समावेश <linux/uपन.स>  
#समावेश <linux/init.h>  
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/पन.स>  
#समावेश <linux/atomic.h>
#समावेश <linux/uaccess.h>  
#समावेश <यंत्र/माला.स>  
#समावेश <यंत्र/byteorder.h>  
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/nospec.h>
#समावेश "iphase.h"		  
#समावेश "suni.h"		  
#घोषणा swap_byte_order(x) (((x & 0xff) << 8) | ((x & 0xff00) >> 8))

#घोषणा PRIV(dev) ((काष्ठा suni_priv *) dev->phy_data)

अटल अचिन्हित अक्षर ia_phy_get(काष्ठा aपंचांग_dev *dev, अचिन्हित दीर्घ addr);
अटल व्योम desc_dbg(IADEV *iadev);

अटल IADEV *ia_dev[8];
अटल काष्ठा aपंचांग_dev *_ia_dev[8];
अटल पूर्णांक iadev_count;
अटल व्योम ia_led_समयr(काष्ठा समयr_list *unused);
अटल DEFINE_TIMER(ia_समयr, ia_led_समयr);
अटल पूर्णांक IA_TX_BUF = DFL_TX_BUFFERS, IA_TX_BUF_SZ = DFL_TX_BUF_SZ;
अटल पूर्णांक IA_RX_BUF = DFL_RX_BUFFERS, IA_RX_BUF_SZ = DFL_RX_BUF_SZ;
अटल uपूर्णांक IADebugFlag = /* IF_IADBG_ERR | IF_IADBG_CBR| IF_IADBG_INIT_ADAPTER
            |IF_IADBG_ABR | IF_IADBG_EVENT*/ 0; 

module_param(IA_TX_BUF, पूर्णांक, 0);
module_param(IA_TX_BUF_SZ, पूर्णांक, 0);
module_param(IA_RX_BUF, पूर्णांक, 0);
module_param(IA_RX_BUF_SZ, पूर्णांक, 0);
module_param(IADebugFlag, uपूर्णांक, 0644);

MODULE_LICENSE("GPL");

/**************************** IA_LIB **********************************/

अटल व्योम ia_init_rtn_q (IARTN_Q *que) 
अणु 
   que->next = शून्य; 
   que->tail = शून्य; 
पूर्ण

अटल व्योम ia_enque_head_rtn_q (IARTN_Q *que, IARTN_Q * data) 
अणु
   data->next = शून्य;
   अगर (que->next == शून्य) 
      que->next = que->tail = data;
   अन्यथा अणु
      data->next = que->next;
      que->next = data;
   पूर्ण 
   वापस;
पूर्ण

अटल पूर्णांक ia_enque_rtn_q (IARTN_Q *que, काष्ठा desc_tbl_t data) अणु
   IARTN_Q *entry = kदो_स्मृति(माप(*entry), GFP_ATOMIC);
   अगर (!entry)
      वापस -ENOMEM;
   entry->data = data;
   entry->next = शून्य;
   अगर (que->next == शून्य) 
      que->next = que->tail = entry;
   अन्यथा अणु
      que->tail->next = entry;
      que->tail = que->tail->next;
   पूर्ण      
   वापस 1;
पूर्ण

अटल IARTN_Q * ia_deque_rtn_q (IARTN_Q *que) अणु
   IARTN_Q *पंचांगpdata;
   अगर (que->next == शून्य)
      वापस शून्य;
   पंचांगpdata = que->next;
   अगर ( que->next == que->tail)  
      que->next = que->tail = शून्य;
   अन्यथा 
      que->next = que->next->next;
   वापस पंचांगpdata;
पूर्ण

अटल व्योम ia_hack_tcq(IADEV *dev) अणु

  u_लघु 		desc1;
  u_लघु		tcq_wr;
  काष्ठा ia_vcc         *iavcc_r = शून्य; 

  tcq_wr = पढ़ोl(dev->seg_reg+TCQ_WR_PTR) & 0xffff;
  जबतक (dev->host_tcq_wr != tcq_wr) अणु
     desc1 = *(u_लघु *)(dev->seg_ram + dev->host_tcq_wr);
     अगर (!desc1) ;
     अन्यथा अगर (!dev->desc_tbl[desc1 -1].बारtamp) अणु
        IF_ABR(prपूर्णांकk(" Desc %d is reset at %ld\n", desc1 -1, jअगरfies);)
        *(u_लघु *) (dev->seg_ram + dev->host_tcq_wr) = 0;
     पूर्ण                                 
     अन्यथा अगर (dev->desc_tbl[desc1 -1].बारtamp) अणु
        अगर (!(iavcc_r = dev->desc_tbl[desc1 -1].iavcc)) अणु 
           prपूर्णांकk("IA: Fatal err in get_desc\n");
           जारी;
        पूर्ण
        iavcc_r->vc_desc_cnt--;
        dev->desc_tbl[desc1 -1].बारtamp = 0;
        IF_EVENT(prपूर्णांकk("ia_hack: return_q skb = 0x%p desc = %d\n",
                                   dev->desc_tbl[desc1 -1].txskb, desc1);)
        अगर (iavcc_r->pcr < dev->rate_limit) अणु
           IA_SKB_STATE (dev->desc_tbl[desc1-1].txskb) |= IA_TX_DONE;
           अगर (ia_enque_rtn_q(&dev->tx_वापस_q, dev->desc_tbl[desc1 -1]) < 0)
              prपूर्णांकk("ia_hack_tcq: No memory available\n");
        पूर्ण 
        dev->desc_tbl[desc1 -1].iavcc = शून्य;
        dev->desc_tbl[desc1 -1].txskb = शून्य;
     पूर्ण
     dev->host_tcq_wr += 2;
     अगर (dev->host_tcq_wr > dev->ffL.tcq_ed) 
        dev->host_tcq_wr = dev->ffL.tcq_st;
  पूर्ण
पूर्ण /* ia_hack_tcq */

अटल u16 get_desc (IADEV *dev, काष्ठा ia_vcc *iavcc) अणु
  u_लघु 		desc_num, i;
  काष्ठा sk_buff        *skb;
  काष्ठा ia_vcc         *iavcc_r = शून्य; 
  अचिन्हित दीर्घ delta;
  अटल अचिन्हित दीर्घ समयr = 0;
  पूर्णांक lसमयout;

  ia_hack_tcq (dev);
  अगर((समय_after(jअगरfies,समयr+50)) || ((dev->ffL.tcq_rd==dev->host_tcq_wr))) अणु
     समयr = jअगरfies; 
     i=0;
     जबतक (i < dev->num_tx_desc) अणु
        अगर (!dev->desc_tbl[i].बारtamp) अणु
           i++;
           जारी;
        पूर्ण
        lसमयout = dev->desc_tbl[i].iavcc->lसमयout; 
        delta = jअगरfies - dev->desc_tbl[i].बारtamp;
        अगर (delta >= lसमयout) अणु
           IF_ABR(prपूर्णांकk("RECOVER run!! desc_tbl %d = %d  delta = %ld, time = %ld\n", i,dev->desc_tbl[i].बारtamp, delta, jअगरfies);)
           अगर (dev->ffL.tcq_rd == dev->ffL.tcq_st) 
              dev->ffL.tcq_rd =  dev->ffL.tcq_ed;
           अन्यथा 
              dev->ffL.tcq_rd -= 2;
           *(u_लघु *)(dev->seg_ram + dev->ffL.tcq_rd) = i+1;
           अगर (!(skb = dev->desc_tbl[i].txskb) || 
                          !(iavcc_r = dev->desc_tbl[i].iavcc))
              prपूर्णांकk("Fatal err, desc table vcc or skb is NULL\n");
           अन्यथा 
              iavcc_r->vc_desc_cnt--;
           dev->desc_tbl[i].बारtamp = 0;
           dev->desc_tbl[i].iavcc = शून्य;
           dev->desc_tbl[i].txskb = शून्य;
        पूर्ण
        i++;
     पूर्ण /* जबतक */
  पूर्ण
  अगर (dev->ffL.tcq_rd == dev->host_tcq_wr) 
     वापस 0xFFFF;
    
  /* Get the next available descriptor number from TCQ */
  desc_num = *(u_लघु *)(dev->seg_ram + dev->ffL.tcq_rd);

  जबतक (!desc_num || (dev->desc_tbl[desc_num -1]).बारtamp) अणु
     dev->ffL.tcq_rd += 2;
     अगर (dev->ffL.tcq_rd > dev->ffL.tcq_ed) 
	dev->ffL.tcq_rd = dev->ffL.tcq_st;
     अगर (dev->ffL.tcq_rd == dev->host_tcq_wr) 
        वापस 0xFFFF; 
     desc_num = *(u_लघु *)(dev->seg_ram + dev->ffL.tcq_rd);
  पूर्ण

  /* get प्रणाली समय */
  dev->desc_tbl[desc_num -1].बारtamp = jअगरfies;
  वापस desc_num;
पूर्ण

अटल व्योम clear_lockup (काष्ठा aपंचांग_vcc *vcc, IADEV *dev) अणु
  u_अक्षर          	foundLockUp;
  vcstatus_t		*vcstatus;
  u_लघु               *shd_tbl;
  u_लघु               tempCellSlot, tempFract;
  काष्ठा मुख्य_vc *abr_vc = (काष्ठा मुख्य_vc *)dev->MAIN_VC_TABLE_ADDR;
  काष्ठा ext_vc *eabr_vc = (काष्ठा ext_vc *)dev->EXT_VC_TABLE_ADDR;
  u_पूर्णांक  i;

  अगर (vcc->qos.txtp.traffic_class == ATM_ABR) अणु
     vcstatus = (vcstatus_t *) &(dev->testTable[vcc->vci]->vc_status);
     vcstatus->cnt++;
     foundLockUp = 0;
     अगर( vcstatus->cnt == 0x05 ) अणु
        abr_vc += vcc->vci;
	eabr_vc += vcc->vci;
	अगर( eabr_vc->last_desc ) अणु
	   अगर( (abr_vc->status & 0x07) == ABR_STATE /* 0x2 */ ) अणु
              /* Wait क्रम 10 Micro sec */
              udelay(10);
	      अगर ((eabr_vc->last_desc)&&((abr_vc->status & 0x07)==ABR_STATE))
		 foundLockUp = 1;
           पूर्ण
	   अन्यथा अणु
	      tempCellSlot = abr_vc->last_cell_slot;
              tempFract    = abr_vc->fraction;
              अगर((tempCellSlot == dev->testTable[vcc->vci]->lastTime)
                         && (tempFract == dev->testTable[vcc->vci]->fract))
	         foundLockUp = 1; 		    
              dev->testTable[vcc->vci]->lastTime = tempCellSlot;   
              dev->testTable[vcc->vci]->fract = tempFract; 
	   पूर्ण 	    
        पूर्ण /* last descriptor */	 	   
        vcstatus->cnt = 0;     	
     पूर्ण /* vcstatus->cnt */
	
     अगर (foundLockUp) अणु
        IF_ABR(prपूर्णांकk("LOCK UP found\n");) 
	ग_लिखोw(0xFFFD, dev->seg_reg+MODE_REG_0);
        /* Wait क्रम 10 Micro sec */
        udelay(10); 
        abr_vc->status &= 0xFFF8;
        abr_vc->status |= 0x0001;  /* state is idle */
	shd_tbl = (u_लघु *)dev->ABR_SCHED_TABLE_ADDR;                
	क्रम( i = 0; ((i < dev->num_vc) && (shd_tbl[i])); i++ );
	अगर (i < dev->num_vc)
           shd_tbl[i] = vcc->vci;
        अन्यथा
           IF_ERR(prपूर्णांकk("ABR Seg. may not continue on VC %x\n",vcc->vci);)
        ग_लिखोw(T_ONLINE, dev->seg_reg+MODE_REG_0);
        ग_लिखोw(~(TRANSMIT_DONE|TCQ_NOT_EMPTY), dev->seg_reg+SEG_MASK_REG);
        ग_लिखोw(TRANSMIT_DONE, dev->seg_reg+SEG_INTR_STATUS_REG);       
	vcstatus->cnt = 0;
     पूर्ण /* foundLockUp */

  पूर्ण /* अगर an ABR VC */


पूर्ण
 
/*
** Conversion of 24-bit cellrate (cells/sec) to 16-bit भग्नing poपूर्णांक क्रमmat.
**
**  +----+----+------------------+-------------------------------+
**  |  R | NZ |  5-bit exponent  |        9-bit mantissa         |
**  +----+----+------------------+-------------------------------+
** 
**    R = reserved (written as 0)
**    NZ = 0 अगर 0 cells/sec; 1 otherwise
**
**    अगर NZ = 1, rate = 1.mmmmmmmmm x 2^(eeeee) cells/sec
*/
अटल u16
cellrate_to_भग्न(u32 cr)
अणु

#घोषणा	NZ 		0x4000
#घोषणा	M_BITS		9		/* Number of bits in mantissa */
#घोषणा	E_BITS		5		/* Number of bits in exponent */
#घोषणा	M_MASK		0x1ff		
#घोषणा	E_MASK		0x1f
  u16   flot;
  u32	पंचांगp = cr & 0x00ffffff;
  पूर्णांक 	i   = 0;
  अगर (cr == 0)
     वापस 0;
  जबतक (पंचांगp != 1) अणु
     पंचांगp >>= 1;
     i++;
  पूर्ण
  अगर (i == M_BITS)
     flot = NZ | (i << M_BITS) | (cr & M_MASK);
  अन्यथा अगर (i < M_BITS)
     flot = NZ | (i << M_BITS) | ((cr << (M_BITS - i)) & M_MASK);
  अन्यथा
     flot = NZ | (i << M_BITS) | ((cr >> (i - M_BITS)) & M_MASK);
  वापस flot;
पूर्ण

#अगर 0
/*
** Conversion of 16-bit भग्नing poपूर्णांक क्रमmat to 24-bit cellrate (cells/sec).
*/
अटल u32
भग्न_to_cellrate(u16 rate)
अणु
  u32   exp, mantissa, cps;
  अगर ((rate & NZ) == 0)
     वापस 0;
  exp = (rate >> M_BITS) & E_MASK;
  mantissa = rate & M_MASK;
  अगर (exp == 0)
     वापस 1;
  cps = (1 << M_BITS) | mantissa;
  अगर (exp == M_BITS)
     cps = cps;
  अन्यथा अगर (exp > M_BITS)
     cps <<= (exp - M_BITS);
  अन्यथा
     cps >>= (M_BITS - exp);
  वापस cps;
पूर्ण
#पूर्ण_अगर 

अटल व्योम init_abr_vc (IADEV *dev, srv_cls_param_t *srv_p) अणु
  srv_p->class_type = ATM_ABR;
  srv_p->pcr        = dev->LineRate;
  srv_p->mcr        = 0;
  srv_p->icr        = 0x055cb7;
  srv_p->tbe        = 0xffffff;
  srv_p->frtt       = 0x3a;
  srv_p->rअगर        = 0xf;
  srv_p->rdf        = 0xb;
  srv_p->nrm        = 0x4;
  srv_p->trm        = 0x7;
  srv_p->cdf        = 0x3;
  srv_p->adtf       = 50;
पूर्ण

अटल पूर्णांक
ia_खोलो_abr_vc(IADEV *dev, srv_cls_param_t *srv_p, 
                                                काष्ठा aपंचांग_vcc *vcc, u8 flag)
अणु
  f_vc_abr_entry  *f_abr_vc;
  r_vc_abr_entry  *r_abr_vc;
  u32		icr;
  u8		trm, nrm, crm;
  u16		adtf, air, *ptr16;	
  f_abr_vc =(f_vc_abr_entry *)dev->MAIN_VC_TABLE_ADDR;
  f_abr_vc += vcc->vci;       
  चयन (flag) अणु
     हाल 1: /* FFRED initialization */
#अगर 0  /* sanity check */
       अगर (srv_p->pcr == 0)
          वापस INVALID_PCR;
       अगर (srv_p->pcr > dev->LineRate)
          srv_p->pcr = dev->LineRate;
       अगर ((srv_p->mcr + dev->sum_mcr) > dev->LineRate)
	  वापस MCR_UNAVAILABLE;
       अगर (srv_p->mcr > srv_p->pcr)
	  वापस INVALID_MCR;
       अगर (!(srv_p->icr))
	  srv_p->icr = srv_p->pcr;
       अगर ((srv_p->icr < srv_p->mcr) || (srv_p->icr > srv_p->pcr))
	  वापस INVALID_ICR;
       अगर ((srv_p->tbe < MIN_TBE) || (srv_p->tbe > MAX_TBE))
	  वापस INVALID_TBE;
       अगर ((srv_p->frtt < MIN_FRTT) || (srv_p->frtt > MAX_FRTT))
	  वापस INVALID_FRTT;
       अगर (srv_p->nrm > MAX_NRM)
	  वापस INVALID_NRM;
       अगर (srv_p->trm > MAX_TRM)
	  वापस INVALID_TRM;
       अगर (srv_p->adtf > MAX_ADTF)
          वापस INVALID_ADTF;
       अन्यथा अगर (srv_p->adtf == 0)
	  srv_p->adtf = 1;
       अगर (srv_p->cdf > MAX_CDF)
	  वापस INVALID_CDF;
       अगर (srv_p->rअगर > MAX_RIF)
	  वापस INVALID_RIF;
       अगर (srv_p->rdf > MAX_RDF)
	  वापस INVALID_RDF;
#पूर्ण_अगर
       स_रखो ((caddr_t)f_abr_vc, 0, माप(*f_abr_vc));
       f_abr_vc->f_vc_type = ABR;
       nrm = 2 << srv_p->nrm;     /* (2 ** (srv_p->nrm +1)) */
			          /* i.e 2**n = 2 << (n-1) */
       f_abr_vc->f_nrm = nrm << 8 | nrm;
       trm = 100000/(2 << (16 - srv_p->trm));
       अगर ( trm == 0) trm = 1;
       f_abr_vc->f_nrmexp =(((srv_p->nrm +1) & 0x0f) << 12)|(MRM << 8) | trm;
       crm = srv_p->tbe / nrm;
       अगर (crm == 0) crm = 1;
       f_abr_vc->f_crm = crm & 0xff;
       f_abr_vc->f_pcr = cellrate_to_भग्न(srv_p->pcr);
       icr = min( srv_p->icr, (srv_p->tbe > srv_p->frtt) ?
				((srv_p->tbe/srv_p->frtt)*1000000) :
				(1000000/(srv_p->frtt/srv_p->tbe)));
       f_abr_vc->f_icr = cellrate_to_भग्न(icr);
       adtf = (10000 * srv_p->adtf)/8192;
       अगर (adtf == 0) adtf = 1; 
       f_abr_vc->f_cdf = ((7 - srv_p->cdf) << 12 | adtf) & 0xfff;
       f_abr_vc->f_mcr = cellrate_to_भग्न(srv_p->mcr);
       f_abr_vc->f_acr = f_abr_vc->f_icr;
       f_abr_vc->f_status = 0x0042;
       अवरोध;
    हाल 0: /* RFRED initialization */	
       ptr16 = (u_लघु *)(dev->reass_ram + REASS_TABLE*dev->memSize); 
       *(ptr16 + vcc->vci) = NO_AAL5_PKT | REASS_ABR;
       r_abr_vc = (r_vc_abr_entry*)(dev->reass_ram+ABR_VC_TABLE*dev->memSize);
       r_abr_vc += vcc->vci;
       r_abr_vc->r_status_rdf = (15 - srv_p->rdf) & 0x000f;
       air = srv_p->pcr << (15 - srv_p->rअगर);
       अगर (air == 0) air = 1;
       r_abr_vc->r_air = cellrate_to_भग्न(air);
       dev->testTable[vcc->vci]->vc_status = VC_ACTIVE | VC_ABR;
       dev->sum_mcr	   += srv_p->mcr;
       dev->n_abr++;
       अवरोध;
    शेष:
       अवरोध;
  पूर्ण
  वापस	0;
पूर्ण
अटल पूर्णांक ia_cbr_setup (IADEV *dev, काष्ठा aपंचांग_vcc *vcc) अणु
   u32 rateLow=0, rateHigh, rate;
   पूर्णांक entries;
   काष्ठा ia_vcc *ia_vcc;

   पूर्णांक   idealSlot =0, testSlot, toBeAsचिन्हित, inc;
   u32   spacing;
   u16  *SchedTbl, *TstSchedTbl;
   u16  cbrVC, vcIndex;
   u32   fracSlot    = 0;
   u32   sp_mod      = 0;
   u32   sp_mod2     = 0;

   /* IpAdjustTrafficParams */
   अगर (vcc->qos.txtp.max_pcr <= 0) अणु
      IF_ERR(prपूर्णांकk("PCR for CBR not defined\n");)
      वापस -1;
   पूर्ण
   rate = vcc->qos.txtp.max_pcr;
   entries = rate / dev->Granularity;
   IF_CBR(prपूर्णांकk("CBR: CBR entries=0x%x for rate=0x%x & Gran=0x%x\n",
                                entries, rate, dev->Granularity);)
   अगर (entries < 1)
      IF_CBR(prपूर्णांकk("CBR: Bandwidth smaller than granularity of CBR table\n");) 
   rateLow  =  entries * dev->Granularity;
   rateHigh = (entries + 1) * dev->Granularity;
   अगर (3*(rate - rateLow) > (rateHigh - rate))
      entries++;
   अगर (entries > dev->CbrRemEntries) अणु
      IF_CBR(prपूर्णांकk("CBR: Not enough bandwidth to support this PCR.\n");)
      IF_CBR(prपूर्णांकk("Entries = 0x%x, CbrRemEntries = 0x%x.\n",
                                       entries, dev->CbrRemEntries);)
      वापस -EBUSY;
   पूर्ण   

   ia_vcc = INPH_IA_VCC(vcc);
   ia_vcc->NumCbrEntry = entries; 
   dev->sum_mcr += entries * dev->Granularity; 
   /* IaFFrednInsertCbrSched */
   // Starting at an arbitrary location, place the entries पूर्णांकo the table
   // as smoothly as possible
   cbrVC   = 0;
   spacing = dev->CbrTotEntries / entries;
   sp_mod  = dev->CbrTotEntries % entries; // get modulo
   toBeAsचिन्हित = entries;
   fracSlot = 0;
   vcIndex  = vcc->vci;
   IF_CBR(prपूर्णांकk("Vci=0x%x,Spacing=0x%x,Sp_mod=0x%x\n",vcIndex,spacing,sp_mod);)
   जबतक (toBeAsचिन्हित)
   अणु
      // If this is the first समय, start the table loading क्रम this connection
      // as बंद to entryPoपूर्णांक as possible.
      अगर (toBeAsचिन्हित == entries)
      अणु
         idealSlot = dev->CbrEntryPt;
         dev->CbrEntryPt += 2;    // Adding 2 helps to prevent clumping
         अगर (dev->CbrEntryPt >= dev->CbrTotEntries) 
            dev->CbrEntryPt -= dev->CbrTotEntries;// Wrap अगर necessary
      पूर्ण अन्यथा अणु
         idealSlot += (u32)(spacing + fracSlot); // Poपूर्णांक to the next location
         // in the table that would be  smoothest
         fracSlot = ((sp_mod + sp_mod2) / entries);  // get new पूर्णांकeger part
         sp_mod2  = ((sp_mod + sp_mod2) % entries);  // calc new fractional part
      पूर्ण
      अगर (idealSlot >= (पूर्णांक)dev->CbrTotEntries) 
         idealSlot -= dev->CbrTotEntries;  
      // Continuously check around this ideal value until a null
      // location is encountered.
      SchedTbl = (u16*)(dev->seg_ram+CBR_SCHED_TABLE*dev->memSize); 
      inc = 0;
      testSlot = idealSlot;
      TstSchedTbl = (u16*)(SchedTbl+testSlot);  //set index and पढ़ो in value
      IF_CBR(prपूर्णांकk("CBR Testslot 0x%x AT Location 0x%p, NumToAssign=%d\n",
                                testSlot, TstSchedTbl,toBeAsचिन्हित);)
      स_नकल((caddr_t)&cbrVC,(caddr_t)TstSchedTbl,माप(cbrVC));
      जबतक (cbrVC)  // If another VC at this location, we have to keep looking
      अणु
          inc++;
          testSlot = idealSlot - inc;
          अगर (testSlot < 0) अणु // Wrap अगर necessary
             testSlot += dev->CbrTotEntries;
             IF_CBR(prपूर्णांकk("Testslot Wrap. STable Start=0x%p,Testslot=%d\n",
                                                       SchedTbl,testSlot);)
          पूर्ण
          TstSchedTbl = (u16 *)(SchedTbl + testSlot);  // set table index
          स_नकल((caddr_t)&cbrVC,(caddr_t)TstSchedTbl,माप(cbrVC)); 
          अगर (!cbrVC)
             अवरोध;
          testSlot = idealSlot + inc;
          अगर (testSlot >= (पूर्णांक)dev->CbrTotEntries) अणु // Wrap अगर necessary
             testSlot -= dev->CbrTotEntries;
             IF_CBR(prपूर्णांकk("TotCbrEntries=%d",dev->CbrTotEntries);)
             IF_CBR(prपूर्णांकk(" Testslot=0x%x ToBeAssgned=%d\n", 
                                            testSlot, toBeAsचिन्हित);)
          पूर्ण 
          // set table index and पढ़ो in value
          TstSchedTbl = (u16*)(SchedTbl + testSlot);
          IF_CBR(prपूर्णांकk("Reading CBR Tbl from 0x%p, CbrVal=0x%x Iteration %d\n",
                          TstSchedTbl,cbrVC,inc);)
          स_नकल((caddr_t)&cbrVC,(caddr_t)TstSchedTbl,माप(cbrVC));
       पूर्ण /* जबतक */
       // Move this VCI number पूर्णांकo this location of the CBR Sched table.
       स_नकल((caddr_t)TstSchedTbl, (caddr_t)&vcIndex, माप(*TstSchedTbl));
       dev->CbrRemEntries--;
       toBeAsचिन्हित--;
   पूर्ण /* जबतक */ 

   /* IaFFrednCbrEnable */
   dev->NumEnabledCBR++;
   अगर (dev->NumEnabledCBR == 1) अणु
       ग_लिखोw((CBR_EN | UBR_EN | ABR_EN | (0x23 << 2)), dev->seg_reg+STPARMS);
       IF_CBR(prपूर्णांकk("CBR is enabled\n");)
   पूर्ण
   वापस 0;
पूर्ण
अटल व्योम ia_cbrVc_बंद (काष्ठा aपंचांग_vcc *vcc) अणु
   IADEV *iadev;
   u16 *SchedTbl, NullVci = 0;
   u32 i, NumFound;

   iadev = INPH_IA_DEV(vcc->dev);
   iadev->NumEnabledCBR--;
   SchedTbl = (u16*)(iadev->seg_ram+CBR_SCHED_TABLE*iadev->memSize);
   अगर (iadev->NumEnabledCBR == 0) अणु
      ग_लिखोw((UBR_EN | ABR_EN | (0x23 << 2)), iadev->seg_reg+STPARMS);
      IF_CBR (prपूर्णांकk("CBR support disabled\n");)
   पूर्ण
   NumFound = 0;
   क्रम (i=0; i < iadev->CbrTotEntries; i++)
   अणु
      अगर (*SchedTbl == vcc->vci) अणु
         iadev->CbrRemEntries++;
         *SchedTbl = NullVci;
         IF_CBR(NumFound++;)
      पूर्ण
      SchedTbl++;   
   पूर्ण 
   IF_CBR(prपूर्णांकk("Exit ia_cbrVc_close, NumRemoved=%d\n",NumFound);)
पूर्ण

अटल पूर्णांक ia_avail_descs(IADEV *iadev) अणु
   पूर्णांक पंचांगp = 0;
   ia_hack_tcq(iadev);
   अगर (iadev->host_tcq_wr >= iadev->ffL.tcq_rd)
      पंचांगp = (iadev->host_tcq_wr - iadev->ffL.tcq_rd) / 2;
   अन्यथा
      पंचांगp = (iadev->ffL.tcq_ed - iadev->ffL.tcq_rd + 2 + iadev->host_tcq_wr -
                   iadev->ffL.tcq_st) / 2;
   वापस पंचांगp;
पूर्ण    

अटल पूर्णांक ia_pkt_tx (काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb);

अटल पूर्णांक ia_que_tx (IADEV *iadev) अणु 
   काष्ठा sk_buff *skb;
   पूर्णांक num_desc;
   काष्ठा aपंचांग_vcc *vcc;
   num_desc = ia_avail_descs(iadev);

   जबतक (num_desc && (skb = skb_dequeue(&iadev->tx_backlog))) अणु
      अगर (!(vcc = ATM_SKB(skb)->vcc)) अणु
         dev_kमुक्त_skb_any(skb);
         prपूर्णांकk("ia_que_tx: Null vcc\n");
         अवरोध;
      पूर्ण
      अगर (!test_bit(ATM_VF_READY,&vcc->flags)) अणु
         dev_kमुक्त_skb_any(skb);
         prपूर्णांकk("Free the SKB on closed vci %d \n", vcc->vci);
         अवरोध;
      पूर्ण
      अगर (ia_pkt_tx (vcc, skb)) अणु
         skb_queue_head(&iadev->tx_backlog, skb);
      पूर्ण
      num_desc--;
   पूर्ण
   वापस 0;
पूर्ण

अटल व्योम ia_tx_poll (IADEV *iadev) अणु
   काष्ठा aपंचांग_vcc *vcc = शून्य;
   काष्ठा sk_buff *skb = शून्य, *skb1 = शून्य;
   काष्ठा ia_vcc *iavcc;
   IARTN_Q *  rtne;

   ia_hack_tcq(iadev);
   जबतक ( (rtne = ia_deque_rtn_q(&iadev->tx_वापस_q))) अणु
       skb = rtne->data.txskb;
       अगर (!skb) अणु
           prपूर्णांकk("ia_tx_poll: skb is null\n");
           जाओ out;
       पूर्ण
       vcc = ATM_SKB(skb)->vcc;
       अगर (!vcc) अणु
           prपूर्णांकk("ia_tx_poll: vcc is null\n");
           dev_kमुक्त_skb_any(skb);
	   जाओ out;
       पूर्ण

       iavcc = INPH_IA_VCC(vcc);
       अगर (!iavcc) अणु
           prपूर्णांकk("ia_tx_poll: iavcc is null\n");
           dev_kमुक्त_skb_any(skb);
	   जाओ out;
       पूर्ण

       skb1 = skb_dequeue(&iavcc->txing_skb);
       जबतक (skb1 && (skb1 != skb)) अणु
          अगर (!(IA_SKB_STATE(skb1) & IA_TX_DONE)) अणु
             prपूर्णांकk("IA_tx_intr: Vci %d lost pkt!!!\n", vcc->vci);
          पूर्ण
          IF_ERR(prपूर्णांकk("Release the SKB not match\n");)
          अगर ((vcc->pop) && (skb1->len != 0))
          अणु
             vcc->pop(vcc, skb1);
             IF_EVENT(prपूर्णांकk("Transmit Done - skb 0x%lx return\n",
                                                          (दीर्घ)skb1);)
          पूर्ण
          अन्यथा 
             dev_kमुक्त_skb_any(skb1);
          skb1 = skb_dequeue(&iavcc->txing_skb);
       पूर्ण                                                        
       अगर (!skb1) अणु
          IF_EVENT(prपूर्णांकk("IA: Vci %d - skb not found requeued\n",vcc->vci);)
          ia_enque_head_rtn_q (&iadev->tx_वापस_q, rtne);
          अवरोध;
       पूर्ण
       अगर ((vcc->pop) && (skb->len != 0))
       अणु
          vcc->pop(vcc, skb);
          IF_EVENT(prपूर्णांकk("Tx Done - skb 0x%lx return\n",(दीर्घ)skb);)
       पूर्ण
       अन्यथा 
          dev_kमुक्त_skb_any(skb);
       kमुक्त(rtne);
    पूर्ण
    ia_que_tx(iadev);
out:
    वापस;
पूर्ण
#अगर 0
अटल व्योम ia_eeprom_put (IADEV *iadev, u32 addr, u_लघु val)
अणु
        u32	t;
	पूर्णांक	i;
	/*
	 * Issue a command to enable ग_लिखोs to the NOVRAM
	 */
	NVRAM_CMD (EXTEND + EWEN);
	NVRAM_CLR_CE;
	/*
	 * issue the ग_लिखो command
	 */
	NVRAM_CMD(IAWRITE + addr);
	/* 
	 * Send the data, starting with D15, then D14, and so on क्रम 16 bits
	 */
	क्रम (i=15; i>=0; i--) अणु
		NVRAM_CLKOUT (val & 0x8000);
		val <<= 1;
	पूर्ण
	NVRAM_CLR_CE;
	CFG_OR(NVCE);
	t = पढ़ोl(iadev->reg+IPHASE5575_EEPROM_ACCESS); 
	जबतक (!(t & NVDO))
		t = पढ़ोl(iadev->reg+IPHASE5575_EEPROM_ACCESS); 

	NVRAM_CLR_CE;
	/*
	 * disable ग_लिखोs again
	 */
	NVRAM_CMD(EXTEND + EWDS)
	NVRAM_CLR_CE;
	CFG_AND(~NVDI);
पूर्ण
#पूर्ण_अगर

अटल u16 ia_eeprom_get (IADEV *iadev, u32 addr)
अणु
	u_लघु	val;
        u32	t;
	पूर्णांक	i;
	/*
	 * Read the first bit that was घड़ीed with the falling edge of the
	 * the last command data घड़ी
	 */
	NVRAM_CMD(IAREAD + addr);
	/*
	 * Now पढ़ो the rest of the bits, the next bit पढ़ो is D14, then D13,
	 * and so on.
	 */
	val = 0;
	क्रम (i=15; i>=0; i--) अणु
		NVRAM_CLKIN(t);
		val |= (t << i);
	पूर्ण
	NVRAM_CLR_CE;
	CFG_AND(~NVDI);
	वापस val;
पूर्ण

अटल व्योम ia_hw_type(IADEV *iadev) अणु
   u_लघु memType = ia_eeprom_get(iadev, 25);   
   iadev->memType = memType;
   अगर ((memType & MEM_SIZE_MASK) == MEM_SIZE_1M) अणु
      iadev->num_tx_desc = IA_TX_BUF;
      iadev->tx_buf_sz = IA_TX_BUF_SZ;
      iadev->num_rx_desc = IA_RX_BUF;
      iadev->rx_buf_sz = IA_RX_BUF_SZ; 
   पूर्ण अन्यथा अगर ((memType & MEM_SIZE_MASK) == MEM_SIZE_512K) अणु
      अगर (IA_TX_BUF == DFL_TX_BUFFERS)
        iadev->num_tx_desc = IA_TX_BUF / 2;
      अन्यथा 
        iadev->num_tx_desc = IA_TX_BUF;
      iadev->tx_buf_sz = IA_TX_BUF_SZ;
      अगर (IA_RX_BUF == DFL_RX_BUFFERS)
        iadev->num_rx_desc = IA_RX_BUF / 2;
      अन्यथा
        iadev->num_rx_desc = IA_RX_BUF;
      iadev->rx_buf_sz = IA_RX_BUF_SZ;
   पूर्ण
   अन्यथा अणु
      अगर (IA_TX_BUF == DFL_TX_BUFFERS) 
        iadev->num_tx_desc = IA_TX_BUF / 8;
      अन्यथा
        iadev->num_tx_desc = IA_TX_BUF;
      iadev->tx_buf_sz = IA_TX_BUF_SZ;
      अगर (IA_RX_BUF == DFL_RX_BUFFERS)
        iadev->num_rx_desc = IA_RX_BUF / 8;
      अन्यथा
        iadev->num_rx_desc = IA_RX_BUF;
      iadev->rx_buf_sz = IA_RX_BUF_SZ; 
   पूर्ण 
   iadev->rx_pkt_ram = TX_PACKET_RAM + (iadev->num_tx_desc * iadev->tx_buf_sz); 
   IF_INIT(prपूर्णांकk("BUF: tx=%d,sz=%d rx=%d sz= %d rx_pkt_ram=%d\n",
         iadev->num_tx_desc, iadev->tx_buf_sz, iadev->num_rx_desc,
         iadev->rx_buf_sz, iadev->rx_pkt_ram);)

#अगर 0
   अगर ((memType & FE_MASK) == FE_SINGLE_MODE) अणु
      iadev->phy_type = PHY_OC3C_S;
   अन्यथा अगर ((memType & FE_MASK) == FE_UTP_OPTION)
      iadev->phy_type = PHY_UTP155;
   अन्यथा
     iadev->phy_type = PHY_OC3C_M;
#पूर्ण_अगर
   
   iadev->phy_type = memType & FE_MASK;
   IF_INIT(prपूर्णांकk("memType = 0x%x iadev->phy_type = 0x%x\n", 
                                         memType,iadev->phy_type);)
   अगर (iadev->phy_type == FE_25MBIT_PHY) 
      iadev->LineRate = (u32)(((25600000/8)*26)/(27*53));
   अन्यथा अगर (iadev->phy_type == FE_DS3_PHY)
      iadev->LineRate = (u32)(((44736000/8)*26)/(27*53));
   अन्यथा अगर (iadev->phy_type == FE_E3_PHY) 
      iadev->LineRate = (u32)(((34368000/8)*26)/(27*53));
   अन्यथा
       iadev->LineRate = (u32)(ATM_OC3_PCR);
   IF_INIT(prपूर्णांकk("iadev->LineRate = %d \n", iadev->LineRate);)

पूर्ण

अटल u32 ia_phy_पढ़ो32(काष्ठा iadev_priv *ia, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl(ia->phy + (reg >> 2));
पूर्ण

अटल व्योम ia_phy_ग_लिखो32(काष्ठा iadev_priv *ia, अचिन्हित पूर्णांक reg, u32 val)
अणु
	ग_लिखोl(val, ia->phy + (reg >> 2));
पूर्ण

अटल व्योम ia_frontend_पूर्णांकr(काष्ठा iadev_priv *iadev)
अणु
	u32 status;

	अगर (iadev->phy_type & FE_25MBIT_PHY) अणु
		status = ia_phy_पढ़ो32(iadev, MB25_INTR_STATUS);
		iadev->carrier_detect = (status & MB25_IS_GSB) ? 1 : 0;
	पूर्ण अन्यथा अगर (iadev->phy_type & FE_DS3_PHY) अणु
		ia_phy_पढ़ो32(iadev, SUNI_DS3_FRM_INTR_STAT);
		status = ia_phy_पढ़ो32(iadev, SUNI_DS3_FRM_STAT);
		iadev->carrier_detect = (status & SUNI_DS3_LOSV) ? 0 : 1;
	पूर्ण अन्यथा अगर (iadev->phy_type & FE_E3_PHY) अणु
		ia_phy_पढ़ो32(iadev, SUNI_E3_FRM_MAINT_INTR_IND);
		status = ia_phy_पढ़ो32(iadev, SUNI_E3_FRM_FRAM_INTR_IND_STAT);
		iadev->carrier_detect = (status & SUNI_E3_LOS) ? 0 : 1;
	पूर्ण अन्यथा अणु
		status = ia_phy_पढ़ो32(iadev, SUNI_RSOP_STATUS);
		iadev->carrier_detect = (status & SUNI_LOSV) ? 0 : 1;
	पूर्ण

	prपूर्णांकk(KERN_INFO "IA: SUNI carrier %s\n",
		iadev->carrier_detect ? "detected" : "lost signal");
पूर्ण

अटल व्योम ia_mb25_init(काष्ठा iadev_priv *iadev)
अणु
#अगर 0
   mb25->mb25_master_ctrl = MB25_MC_DRIC | MB25_MC_DREC | MB25_MC_ENABLED;
#पूर्ण_अगर
	ia_phy_ग_लिखो32(iadev, MB25_MASTER_CTRL, MB25_MC_DRIC | MB25_MC_DREC);
	ia_phy_ग_लिखो32(iadev, MB25_DIAG_CONTROL, 0);

	iadev->carrier_detect =
		(ia_phy_पढ़ो32(iadev, MB25_INTR_STATUS) & MB25_IS_GSB) ? 1 : 0;
पूर्ण

काष्ठा ia_reg अणु
	u16 reg;
	u16 val;
पूर्ण;

अटल व्योम ia_phy_ग_लिखो(काष्ठा iadev_priv *iadev,
			 स्थिर काष्ठा ia_reg *regs, पूर्णांक len)
अणु
	जबतक (len--) अणु
		ia_phy_ग_लिखो32(iadev, regs->reg, regs->val);
		regs++;
	पूर्ण
पूर्ण

अटल व्योम ia_suni_pm7345_init_ds3(काष्ठा iadev_priv *iadev)
अणु
	अटल स्थिर काष्ठा ia_reg suni_ds3_init[] = अणु
		अणु SUNI_DS3_FRM_INTR_ENBL,	0x17 पूर्ण,
		अणु SUNI_DS3_FRM_CFG,		0x01 पूर्ण,
		अणु SUNI_DS3_TRAN_CFG,		0x01 पूर्ण,
		अणु SUNI_CONFIG,			0 पूर्ण,
		अणु SUNI_SPLR_CFG,		0 पूर्ण,
		अणु SUNI_SPLT_CFG,		0 पूर्ण
	पूर्ण;
	u32 status;

	status = ia_phy_पढ़ो32(iadev, SUNI_DS3_FRM_STAT);
	iadev->carrier_detect = (status & SUNI_DS3_LOSV) ? 0 : 1;

	ia_phy_ग_लिखो(iadev, suni_ds3_init, ARRAY_SIZE(suni_ds3_init));
पूर्ण

अटल व्योम ia_suni_pm7345_init_e3(काष्ठा iadev_priv *iadev)
अणु
	अटल स्थिर काष्ठा ia_reg suni_e3_init[] = अणु
		अणु SUNI_E3_FRM_FRAM_OPTIONS,		0x04 पूर्ण,
		अणु SUNI_E3_FRM_MAINT_OPTIONS,		0x20 पूर्ण,
		अणु SUNI_E3_FRM_FRAM_INTR_ENBL,		0x1d पूर्ण,
		अणु SUNI_E3_FRM_MAINT_INTR_ENBL,		0x30 पूर्ण,
		अणु SUNI_E3_TRAN_STAT_DIAG_OPTIONS,	0 पूर्ण,
		अणु SUNI_E3_TRAN_FRAM_OPTIONS,		0x01 पूर्ण,
		अणु SUNI_CONFIG,				SUNI_PM7345_E3ENBL पूर्ण,
		अणु SUNI_SPLR_CFG,			0x41 पूर्ण,
		अणु SUNI_SPLT_CFG,			0x41 पूर्ण
	पूर्ण;
	u32 status;

	status = ia_phy_पढ़ो32(iadev, SUNI_E3_FRM_FRAM_INTR_IND_STAT);
	iadev->carrier_detect = (status & SUNI_E3_LOS) ? 0 : 1;
	ia_phy_ग_लिखो(iadev, suni_e3_init, ARRAY_SIZE(suni_e3_init));
पूर्ण

अटल व्योम ia_suni_pm7345_init(काष्ठा iadev_priv *iadev)
अणु
	अटल स्थिर काष्ठा ia_reg suni_init[] = अणु
		/* Enable RSOP loss of संकेत पूर्णांकerrupt. */
		अणु SUNI_INTR_ENBL,		0x28 पूर्ण,
		/* Clear error counters. */
		अणु SUNI_ID_RESET,		0 पूर्ण,
		/* Clear "PMCTST" in master test रेजिस्टर. */
		अणु SUNI_MASTER_TEST,		0 पूर्ण,

		अणु SUNI_RXCP_CTRL,		0x2c पूर्ण,
		अणु SUNI_RXCP_FCTRL,		0x81 पूर्ण,

		अणु SUNI_RXCP_IDLE_PAT_H1,	0 पूर्ण,
		अणु SUNI_RXCP_IDLE_PAT_H2,	0 पूर्ण,
		अणु SUNI_RXCP_IDLE_PAT_H3,	0 पूर्ण,
		अणु SUNI_RXCP_IDLE_PAT_H4,	0x01 पूर्ण,

		अणु SUNI_RXCP_IDLE_MASK_H1,	0xff पूर्ण,
		अणु SUNI_RXCP_IDLE_MASK_H2,	0xff पूर्ण,
		अणु SUNI_RXCP_IDLE_MASK_H3,	0xff पूर्ण,
		अणु SUNI_RXCP_IDLE_MASK_H4,	0xfe पूर्ण,

		अणु SUNI_RXCP_CELL_PAT_H1,	0 पूर्ण,
		अणु SUNI_RXCP_CELL_PAT_H2,	0 पूर्ण,
		अणु SUNI_RXCP_CELL_PAT_H3,	0 पूर्ण,
		अणु SUNI_RXCP_CELL_PAT_H4,	0x01 पूर्ण,

		अणु SUNI_RXCP_CELL_MASK_H1,	0xff पूर्ण,
		अणु SUNI_RXCP_CELL_MASK_H2,	0xff पूर्ण,
		अणु SUNI_RXCP_CELL_MASK_H3,	0xff पूर्ण,
		अणु SUNI_RXCP_CELL_MASK_H4,	0xff पूर्ण,

		अणु SUNI_TXCP_CTRL,		0xa4 पूर्ण,
		अणु SUNI_TXCP_INTR_EN_STS,	0x10 पूर्ण,
		अणु SUNI_TXCP_IDLE_PAT_H5,	0x55 पूर्ण
	पूर्ण;

	अगर (iadev->phy_type & FE_DS3_PHY)
		ia_suni_pm7345_init_ds3(iadev);
	अन्यथा
		ia_suni_pm7345_init_e3(iadev);

	ia_phy_ग_लिखो(iadev, suni_init, ARRAY_SIZE(suni_init));

	ia_phy_ग_लिखो32(iadev, SUNI_CONFIG, ia_phy_पढ़ो32(iadev, SUNI_CONFIG) &
		~(SUNI_PM7345_LLB | SUNI_PM7345_CLB |
		  SUNI_PM7345_DLB | SUNI_PM7345_PLB));
#अगर_घोषित __SNMP__
   suni_pm7345->suni_rxcp_पूर्णांकr_en_sts |= SUNI_OOCDE;
#पूर्ण_अगर /* __SNMP__ */
   वापस;
पूर्ण


/***************************** IA_LIB END *****************************/
    
#अगर_घोषित CONFIG_ATM_IA_DEBUG
अटल पूर्णांक tcnter = 0;
अटल व्योम xdump( u_अक्षर*  cp, पूर्णांक  length, अक्षर*  prefix )
अणु
    पूर्णांक col, count;
    u_अक्षर prntBuf[120];
    u_अक्षर*  pBuf = prntBuf;
    count = 0;
    जबतक(count < length)अणु
        pBuf += प्र_लिखो( pBuf, "%s", prefix );
        क्रम(col = 0;count + col < length && col < 16; col++)अणु
            अगर (col != 0 && (col % 4) == 0)
                pBuf += प्र_लिखो( pBuf, " " );
            pBuf += प्र_लिखो( pBuf, "%02X ", cp[count + col] );
        पूर्ण
        जबतक(col++ < 16)अणु      /* pad end of buffer with blanks */
            अगर ((col % 4) == 0)
                प्र_लिखो( pBuf, " " );
            pBuf += प्र_लिखो( pBuf, "   " );
        पूर्ण
        pBuf += प्र_लिखो( pBuf, "  " );
        क्रम(col = 0;count + col < length && col < 16; col++)अणु
            अगर (है_छाप((पूर्णांक)cp[count + col]))
                pBuf += प्र_लिखो( pBuf, "%c", cp[count + col] );
            अन्यथा
                pBuf += प्र_लिखो( pBuf, "." );
                पूर्ण
        prपूर्णांकk("%s\n", prntBuf);
        count += col;
        pBuf = prntBuf;
    पूर्ण

पूर्ण  /* बंद xdump(... */
#पूर्ण_अगर /* CONFIG_ATM_IA_DEBUG */

  
अटल काष्ठा aपंचांग_dev *ia_boards = शून्य;  
  
#घोषणा ACTUAL_RAM_BASE \
	RAM_BASE*((iadev->mem)/(128 * 1024))  
#घोषणा ACTUAL_SEG_RAM_BASE \
	IPHASE5575_FRAG_CONTROL_RAM_BASE*((iadev->mem)/(128 * 1024))  
#घोषणा ACTUAL_REASS_RAM_BASE \
	IPHASE5575_REASS_CONTROL_RAM_BASE*((iadev->mem)/(128 * 1024))  
  
  
/*-- some utilities and memory allocation stuff will come here -------------*/  
  
अटल व्योम desc_dbg(IADEV *iadev) अणु

  u_लघु tcq_wr_ptr, tcq_st_ptr, tcq_ed_ptr;
  u32 i;
  व्योम __iomem *पंचांगp;
  // regval = पढ़ोl((u32)ia_cmds->maddr);
  tcq_wr_ptr =  पढ़ोw(iadev->seg_reg+TCQ_WR_PTR);
  prपूर्णांकk("B_tcq_wr = 0x%x desc = %d last desc = %d\n",
                     tcq_wr_ptr, पढ़ोw(iadev->seg_ram+tcq_wr_ptr),
                     पढ़ोw(iadev->seg_ram+tcq_wr_ptr-2));
  prपूर्णांकk(" host_tcq_wr = 0x%x  host_tcq_rd = 0x%x \n",  iadev->host_tcq_wr, 
                   iadev->ffL.tcq_rd);
  tcq_st_ptr =  पढ़ोw(iadev->seg_reg+TCQ_ST_ADR);
  tcq_ed_ptr =  पढ़ोw(iadev->seg_reg+TCQ_ED_ADR);
  prपूर्णांकk("tcq_st_ptr = 0x%x    tcq_ed_ptr = 0x%x \n", tcq_st_ptr, tcq_ed_ptr);
  i = 0;
  जबतक (tcq_st_ptr != tcq_ed_ptr) अणु
      पंचांगp = iadev->seg_ram+tcq_st_ptr;
      prपूर्णांकk("TCQ slot %d desc = %d  Addr = %p\n", i++, पढ़ोw(पंचांगp), पंचांगp);
      tcq_st_ptr += 2;
  पूर्ण
  क्रम(i=0; i <iadev->num_tx_desc; i++)
      prपूर्णांकk("Desc_tbl[%d] = %d \n", i, iadev->desc_tbl[i].बारtamp);
पूर्ण 
  
  
/*----------------------------- Receiving side stuff --------------------------*/  
 
अटल व्योम rx_excp_rcvd(काष्ठा aपंचांग_dev *dev)  
अणु  
#अगर 0 /* closing the receiving size will cause too many excp पूर्णांक */  
  IADEV *iadev;  
  u_लघु state;  
  u_लघु excpq_rd_ptr;  
  //u_लघु *ptr;  
  पूर्णांक vci, error = 1;  
  iadev = INPH_IA_DEV(dev);  
  state = पढ़ोl(iadev->reass_reg + STATE_REG) & 0xffff;  
  जबतक((state & EXCPQ_EMPTY) != EXCPQ_EMPTY)  
  अणु prपूर्णांकk("state = %x \n", state); 
        excpq_rd_ptr = पढ़ोw(iadev->reass_reg + EXCP_Q_RD_PTR) & 0xffff;  
 prपूर्णांकk("state = %x excpq_rd_ptr = %x \n", state, excpq_rd_ptr); 
        अगर (excpq_rd_ptr == *(u16*)(iadev->reass_reg + EXCP_Q_WR_PTR))
            IF_ERR(prपूर्णांकk("excpq_rd_ptr is wrong!!!\n");)
        // TODO: update exception stat
	vci = पढ़ोw(iadev->reass_ram+excpq_rd_ptr);  
	error = पढ़ोw(iadev->reass_ram+excpq_rd_ptr+2) & 0x0007;  
        // pwang_test
	excpq_rd_ptr += 4;  
	अगर (excpq_rd_ptr > (पढ़ोw(iadev->reass_reg + EXCP_Q_ED_ADR)& 0xffff))  
 	    excpq_rd_ptr = पढ़ोw(iadev->reass_reg + EXCP_Q_ST_ADR)& 0xffff;
	ग_लिखोw( excpq_rd_ptr, iadev->reass_reg + EXCP_Q_RD_PTR);  
        state = पढ़ोl(iadev->reass_reg + STATE_REG) & 0xffff;  
  पूर्ण  
#पूर्ण_अगर
पूर्ण  
  
अटल व्योम मुक्त_desc(काष्ठा aपंचांग_dev *dev, पूर्णांक desc)  
अणु  
	IADEV *iadev;  
	iadev = INPH_IA_DEV(dev);  
        ग_लिखोw(desc, iadev->reass_ram+iadev->rfL.fdq_wr); 
	iadev->rfL.fdq_wr +=2;
	अगर (iadev->rfL.fdq_wr > iadev->rfL.fdq_ed)
		iadev->rfL.fdq_wr =  iadev->rfL.fdq_st;  
	ग_लिखोw(iadev->rfL.fdq_wr, iadev->reass_reg+FREEQ_WR_PTR);  
पूर्ण  
  
  
अटल पूर्णांक rx_pkt(काष्ठा aपंचांग_dev *dev)  
अणु  
	IADEV *iadev;  
	काष्ठा aपंचांग_vcc *vcc;  
	अचिन्हित लघु status;  
	काष्ठा rx_buf_desc __iomem *buf_desc_ptr;  
	पूर्णांक desc;   
	काष्ठा dle* wr_ptr;  
	पूर्णांक len;  
	काष्ठा sk_buff *skb;  
	u_पूर्णांक buf_addr, dma_addr;  

	iadev = INPH_IA_DEV(dev);  
	अगर (iadev->rfL.pcq_rd == (पढ़ोw(iadev->reass_reg+PCQ_WR_PTR)&0xffff)) 
	अणु  
   	    prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d) Receive queue empty\n", dev->number);  
	    वापस -EINVAL;  
	पूर्ण  
	/* mask 1st 3 bits to get the actual descno. */  
	desc = पढ़ोw(iadev->reass_ram+iadev->rfL.pcq_rd) & 0x1fff;  
        IF_RX(prपूर्णांकk("reass_ram = %p iadev->rfL.pcq_rd = 0x%x desc = %d\n", 
                                    iadev->reass_ram, iadev->rfL.pcq_rd, desc);
              prपूर्णांकk(" pcq_wr_ptr = 0x%x\n",
                               पढ़ोw(iadev->reass_reg+PCQ_WR_PTR)&0xffff);)
	/* update the पढ़ो poपूर्णांकer  - maybe we shud करो this in the end*/  
	अगर ( iadev->rfL.pcq_rd== iadev->rfL.pcq_ed) 
		iadev->rfL.pcq_rd = iadev->rfL.pcq_st;  
	अन्यथा  
		iadev->rfL.pcq_rd += 2;
	ग_लिखोw(iadev->rfL.pcq_rd, iadev->reass_reg+PCQ_RD_PTR);  
  
	/* get the buffer desc entry.  
		update stuff. - करोesn't seem to be any update necessary  
	*/  
	buf_desc_ptr = iadev->RX_DESC_BASE_ADDR;
	/* make the ptr poपूर्णांक to the corresponding buffer desc entry */  
	buf_desc_ptr += desc;	  
        अगर (!desc || (desc > iadev->num_rx_desc) || 
                      ((buf_desc_ptr->vc_index & 0xffff) >= iadev->num_vc)) अणु
            मुक्त_desc(dev, desc);
            IF_ERR(prपूर्णांकk("IA: bad descriptor desc = %d \n", desc);)
            वापस -1;
        पूर्ण
	vcc = iadev->rx_खोलो[buf_desc_ptr->vc_index & 0xffff];  
	अगर (!vcc)  
	अणु      
                मुक्त_desc(dev, desc); 
		prपूर्णांकk("IA: null vcc, drop PDU\n");  
		वापस -1;  
	पूर्ण  
	  
  
	/* might want to check the status bits क्रम errors */  
	status = (u_लघु) (buf_desc_ptr->desc_mode);  
	अगर (status & (RX_CER | RX_PTE | RX_OFL))  
	अणु  
                atomic_inc(&vcc->stats->rx_err);
		IF_ERR(prपूर्णांकk("IA: bad packet, dropping it");)  
                अगर (status & RX_CER) अणु 
                    IF_ERR(prपूर्णांकk(" cause: packet CRC error\n");)
                पूर्ण
                अन्यथा अगर (status & RX_PTE) अणु
                    IF_ERR(prपूर्णांकk(" cause: packet time out\n");)
                पूर्ण
                अन्यथा अणु
                    IF_ERR(prपूर्णांकk(" cause: buffer overflow\n");)
                पूर्ण
		जाओ out_मुक्त_desc;
	पूर्ण  
  
	/*  
		build DLE.	  
	*/  
  
	buf_addr = (buf_desc_ptr->buf_start_hi << 16) | buf_desc_ptr->buf_start_lo;  
	dma_addr = (buf_desc_ptr->dma_start_hi << 16) | buf_desc_ptr->dma_start_lo;  
	len = dma_addr - buf_addr;  
        अगर (len > iadev->rx_buf_sz) अणु
           prपूर्णांकk("Over %d bytes sdu received, dropped!!!\n", iadev->rx_buf_sz);
           atomic_inc(&vcc->stats->rx_err);
	   जाओ out_मुक्त_desc;
        पूर्ण
		  
        अगर (!(skb = aपंचांग_alloc_अक्षरge(vcc, len, GFP_ATOMIC))) अणु
           अगर (vcc->vci < 32)
              prपूर्णांकk("Drop control packets\n");
	   जाओ out_मुक्त_desc;
        पूर्ण
	skb_put(skb,len);  
        // pwang_test
        ATM_SKB(skb)->vcc = vcc;
        ATM_DESC(skb) = desc;        
	skb_queue_tail(&iadev->rx_dma_q, skb);  

	/* Build the DLE काष्ठाure */  
	wr_ptr = iadev->rx_dle_q.ग_लिखो;  
	wr_ptr->sys_pkt_addr = dma_map_single(&iadev->pci->dev, skb->data,
					      len, DMA_FROM_DEVICE);
	wr_ptr->local_pkt_addr = buf_addr;  
	wr_ptr->bytes = len;	/* We करोn't know this करो we ?? */  
	wr_ptr->mode = DMA_INT_ENABLE;  
  
	/* shud take care of wrap around here too. */  
        अगर(++wr_ptr == iadev->rx_dle_q.end)
             wr_ptr = iadev->rx_dle_q.start;
	iadev->rx_dle_q.ग_लिखो = wr_ptr;  
	udelay(1);  
	/* Increment transaction counter */  
	ग_लिखोl(1, iadev->dma+IPHASE5575_RX_COUNTER);   
out:	वापस 0;  
out_मुक्त_desc:
        मुक्त_desc(dev, desc);
        जाओ out;
पूर्ण  
  
अटल व्योम rx_पूर्णांकr(काष्ठा aपंचांग_dev *dev)  
अणु  
  IADEV *iadev;  
  u_लघु status;  
  u_लघु state, i;  
  
  iadev = INPH_IA_DEV(dev);  
  status = पढ़ोl(iadev->reass_reg+REASS_INTR_STATUS_REG) & 0xffff;  
  IF_EVENT(prपूर्णांकk("rx_intr: status = 0x%x\n", status);)
  अगर (status & RX_PKT_RCVD)  
  अणु  
	/* करो something */  
	/* Basically recvd an पूर्णांकerrupt क्रम receiving a packet.  
	A descriptor would have been written to the packet complete   
	queue. Get all the descriptors and set up dma to move the   
	packets till the packet complete queue is empty..  
	*/  
	state = पढ़ोl(iadev->reass_reg + STATE_REG) & 0xffff;  
        IF_EVENT(prपूर्णांकk("Rx intr status: RX_PKT_RCVD %08x\n", status);) 
	जबतक(!(state & PCQ_EMPTY))  
	अणु  
             rx_pkt(dev);  
	     state = पढ़ोl(iadev->reass_reg + STATE_REG) & 0xffff;  
	पूर्ण  
        iadev->rxing = 1;
  पूर्ण  
  अगर (status & RX_FREEQ_EMPT)  
  अणु   
     अगर (iadev->rxing) अणु
        iadev->rx_पंचांगp_cnt = iadev->rx_pkt_cnt;
        iadev->rx_पंचांगp_jअगर = jअगरfies; 
        iadev->rxing = 0;
     पूर्ण 
     अन्यथा अगर ((समय_after(jअगरfies, iadev->rx_पंचांगp_jअगर + 50)) &&
               ((iadev->rx_pkt_cnt - iadev->rx_पंचांगp_cnt) == 0)) अणु
        क्रम (i = 1; i <= iadev->num_rx_desc; i++)
               मुक्त_desc(dev, i);
prपूर्णांकk("Test logic RUN!!!!\n");
        ग_लिखोw( ~(RX_FREEQ_EMPT|RX_EXCP_RCVD),iadev->reass_reg+REASS_MASK_REG);
        iadev->rxing = 1;
     पूर्ण
     IF_EVENT(prपूर्णांकk("Rx intr status: RX_FREEQ_EMPT %08x\n", status);)  
  पूर्ण  

  अगर (status & RX_EXCP_RCVD)  
  अणु  
	/* probably need to handle the exception queue also. */  
	IF_EVENT(prपूर्णांकk("Rx intr status: RX_EXCP_RCVD %08x\n", status);)  
	rx_excp_rcvd(dev);  
  पूर्ण  


  अगर (status & RX_RAW_RCVD)  
  अणु  
	/* need to handle the raw incoming cells. This deepnds on   
	whether we have programmed to receive the raw cells or not.  
	Else ignore. */  
	IF_EVENT(prपूर्णांकk("Rx intr status:  RX_RAW_RCVD %08x\n", status);)  
  पूर्ण  
पूर्ण  
  
  
अटल व्योम rx_dle_पूर्णांकr(काष्ठा aपंचांग_dev *dev)  
अणु  
  IADEV *iadev;  
  काष्ठा aपंचांग_vcc *vcc;   
  काष्ठा sk_buff *skb;  
  पूर्णांक desc;  
  u_लघु state;   
  काष्ठा dle *dle, *cur_dle;  
  u_पूर्णांक dle_lp;  
  पूर्णांक len;
  iadev = INPH_IA_DEV(dev);  
 
  /* मुक्त all the dles करोne, that is just update our own dle पढ़ो poपूर्णांकer   
	- करो we really need to करो this. Think not. */  
  /* DMA is करोne, just get all the recevie buffers from the rx dma queue  
	and push them up to the higher layer protocol. Also मुक्त the desc  
	associated with the buffer. */  
  dle = iadev->rx_dle_q.पढ़ो;  
  dle_lp = पढ़ोl(iadev->dma+IPHASE5575_RX_LIST_ADDR) & (माप(काष्ठा dle)*DLE_ENTRIES - 1);  
  cur_dle = (काष्ठा dle*)(iadev->rx_dle_q.start + (dle_lp >> 4));  
  जबतक(dle != cur_dle)  
  अणु  
      /* मुक्त the DMAed skb */  
      skb = skb_dequeue(&iadev->rx_dma_q);  
      अगर (!skb)  
         जाओ INCR_DLE;
      desc = ATM_DESC(skb);
      मुक्त_desc(dev, desc);  
               
      अगर (!(len = skb->len))
      अणु  
          prपूर्णांकk("rx_dle_intr: skb len 0\n");  
	  dev_kमुक्त_skb_any(skb);  
      पूर्ण  
      अन्यथा  
      अणु  
          काष्ठा cpcs_trailer *trailer;
          u_लघु length;
          काष्ठा ia_vcc *ia_vcc;

	  dma_unmap_single(&iadev->pci->dev, iadev->rx_dle_q.ग_लिखो->sys_pkt_addr,
			   len, DMA_FROM_DEVICE);
          /* no VCC related housekeeping करोne as yet. lets see */  
          vcc = ATM_SKB(skb)->vcc;
	  अगर (!vcc) अणु
	      prपूर्णांकk("IA: null vcc\n");  
              dev_kमुक्त_skb_any(skb);
              जाओ INCR_DLE;
          पूर्ण
          ia_vcc = INPH_IA_VCC(vcc);
          अगर (ia_vcc == शून्य)
          अणु
             atomic_inc(&vcc->stats->rx_err);
             aपंचांग_वापस(vcc, skb->truesize);
             dev_kमुक्त_skb_any(skb);
             जाओ INCR_DLE;
           पूर्ण
          // get real pkt length  pwang_test
          trailer = (काष्ठा cpcs_trailer*)((u_अक्षर *)skb->data +
                                 skb->len - माप(*trailer));
	  length = swap_byte_order(trailer->length);
          अगर ((length > iadev->rx_buf_sz) || (length > 
                              (skb->len - माप(काष्ठा cpcs_trailer))))
          अणु
             atomic_inc(&vcc->stats->rx_err);
             IF_ERR(prपूर्णांकk("rx_dle_intr: Bad  AAL5 trailer %d (skb len %d)", 
                                                            length, skb->len);)
             aपंचांग_वापस(vcc, skb->truesize);
             dev_kमुक्त_skb_any(skb);
             जाओ INCR_DLE;
          पूर्ण
          skb_trim(skb, length);
          
	  /* Display the packet */  
	  IF_RXPKT(prपूर्णांकk("\nDmad Recvd data: len = %d \n", skb->len);  
          xdump(skb->data, skb->len, "RX: ");
          prपूर्णांकk("\n");)

	  IF_RX(prपूर्णांकk("rx_dle_intr: skb push");)  
	  vcc->push(vcc,skb);  
	  atomic_inc(&vcc->stats->rx);
          iadev->rx_pkt_cnt++;
      पूर्ण  
INCR_DLE:
      अगर (++dle == iadev->rx_dle_q.end)  
    	  dle = iadev->rx_dle_q.start;  
  पूर्ण  
  iadev->rx_dle_q.पढ़ो = dle;  
  
  /* अगर the पूर्णांकerrupts are masked because there were no मुक्त desc available,  
		unmask them now. */ 
  अगर (!iadev->rxing) अणु
     state = पढ़ोl(iadev->reass_reg + STATE_REG) & 0xffff;
     अगर (!(state & FREEQ_EMPTY)) अणु
        state = पढ़ोl(iadev->reass_reg + REASS_MASK_REG) & 0xffff;
        ग_लिखोl(state & ~(RX_FREEQ_EMPT |/* RX_EXCP_RCVD |*/ RX_PKT_RCVD),
                                      iadev->reass_reg+REASS_MASK_REG);
        iadev->rxing++; 
     पूर्ण
  पूर्ण
पूर्ण  
  
  
अटल पूर्णांक खोलो_rx(काष्ठा aपंचांग_vcc *vcc)  
अणु  
	IADEV *iadev;  
	u_लघु __iomem *vc_table;  
	u_लघु __iomem *reass_ptr;  
	IF_EVENT(prपूर्णांकk("iadev: open_rx %d.%d\n", vcc->vpi, vcc->vci);)

	अगर (vcc->qos.rxtp.traffic_class == ATM_NONE) वापस 0;    
	iadev = INPH_IA_DEV(vcc->dev);  
        अगर (vcc->qos.rxtp.traffic_class == ATM_ABR) अणु  
           अगर (iadev->phy_type & FE_25MBIT_PHY) अणु
               prपूर्णांकk("IA:  ABR not support\n");
               वापस -EINVAL; 
           पूर्ण
        पूर्ण
	/* Make only this VCI in the vc table valid and let all   
		others be invalid entries */  
	vc_table = iadev->reass_ram+RX_VC_TABLE*iadev->memSize;
	vc_table += vcc->vci;
	/* mask the last 6 bits and OR it with 3 क्रम 1K VCs */  

        *vc_table = vcc->vci << 6;
	/* Also keep a list of खोलो rx vcs so that we can attach them with  
		incoming PDUs later. */  
	अगर ((vcc->qos.rxtp.traffic_class == ATM_ABR) || 
                                (vcc->qos.txtp.traffic_class == ATM_ABR))  
	अणु  
                srv_cls_param_t srv_p;
                init_abr_vc(iadev, &srv_p);
                ia_खोलो_abr_vc(iadev, &srv_p, vcc, 0);
	पूर्ण 
       	अन्यथा अणु  /* क्रम UBR  later may need to add CBR logic */
        	reass_ptr = iadev->reass_ram+REASS_TABLE*iadev->memSize;
           	reass_ptr += vcc->vci;
           	*reass_ptr = NO_AAL5_PKT;
       	पूर्ण
	
	अगर (iadev->rx_खोलो[vcc->vci])  
		prपूर्णांकk(KERN_CRIT DEV_LABEL "(itf %d): VCI %d already open\n",  
			vcc->dev->number, vcc->vci);  
	iadev->rx_खोलो[vcc->vci] = vcc;  
	वापस 0;  
पूर्ण  
  
अटल पूर्णांक rx_init(काष्ठा aपंचांग_dev *dev)  
अणु  
	IADEV *iadev;  
	काष्ठा rx_buf_desc __iomem *buf_desc_ptr;  
	अचिन्हित दीर्घ rx_pkt_start = 0;  
	व्योम *dle_addr;  
	काष्ठा abr_vc_table  *abr_vc_table; 
	u16 *vc_table;  
	u16 *reass_table;  
	पूर्णांक i,j, vcsize_sel;  
	u_लघु मुक्तq_st_adr;  
	u_लघु *मुक्तq_start;  
  
	iadev = INPH_IA_DEV(dev);  
  //    spin_lock_init(&iadev->rx_lock); 
  
	/* Allocate 4k bytes - more aligned than needed (4k boundary) */
	dle_addr = dma_alloc_coherent(&iadev->pci->dev, DLE_TOTAL_SIZE,
				      &iadev->rx_dle_dma, GFP_KERNEL);
	अगर (!dle_addr)  अणु  
		prपूर्णांकk(KERN_ERR DEV_LABEL "can't allocate DLEs\n");
		जाओ err_out;
	पूर्ण
	iadev->rx_dle_q.start = (काष्ठा dle *)dle_addr;
	iadev->rx_dle_q.पढ़ो = iadev->rx_dle_q.start;  
	iadev->rx_dle_q.ग_लिखो = iadev->rx_dle_q.start;  
	iadev->rx_dle_q.end = (काष्ठा dle*)((अचिन्हित दीर्घ)dle_addr+माप(काष्ठा dle)*DLE_ENTRIES);
	/* the end of the dle q poपूर्णांकs to the entry after the last  
	DLE that can be used. */  
  
	/* ग_लिखो the upper 20 bits of the start address to rx list address रेजिस्टर */  
	/* We know this is 32bit bus addressed so the following is safe */
	ग_लिखोl(iadev->rx_dle_dma & 0xfffff000,
	       iadev->dma + IPHASE5575_RX_LIST_ADDR);  
	IF_INIT(prपूर्णांकk("Tx Dle list addr: 0x%p value: 0x%0x\n",
                      iadev->dma+IPHASE5575_TX_LIST_ADDR,
                      पढ़ोl(iadev->dma + IPHASE5575_TX_LIST_ADDR));
	prपूर्णांकk("Rx Dle list addr: 0x%p value: 0x%0x\n",
                      iadev->dma+IPHASE5575_RX_LIST_ADDR,
                      पढ़ोl(iadev->dma + IPHASE5575_RX_LIST_ADDR));)
  
	ग_लिखोw(0xffff, iadev->reass_reg+REASS_MASK_REG);  
	ग_लिखोw(0, iadev->reass_reg+MODE_REG);  
	ग_लिखोw(RESET_REASS, iadev->reass_reg+REASS_COMMAND_REG);  
  
	/* Receive side control memory map  
	   -------------------------------  
  
		Buffer descr	0x0000 (736 - 23K)  
		VP Table	0x5c00 (256 - 512)  
		Except q	0x5e00 (128 - 512)  
		Free buffer q	0x6000 (1K - 2K)  
		Packet comp q	0x6800 (1K - 2K)  
		Reass Table	0x7000 (1K - 2K)  
		VC Table	0x7800 (1K - 2K)  
		ABR VC Table	0x8000 (1K - 32K)  
	*/  
	  
	/* Base address क्रम Buffer Descriptor Table */  
	ग_लिखोw(RX_DESC_BASE >> 16, iadev->reass_reg+REASS_DESC_BASE);  
	/* Set the buffer size रेजिस्टर */  
	ग_लिखोw(iadev->rx_buf_sz, iadev->reass_reg+BUF_SIZE);  
  
	/* Initialize each entry in the Buffer Descriptor Table */  
        iadev->RX_DESC_BASE_ADDR = iadev->reass_ram+RX_DESC_BASE*iadev->memSize;
	buf_desc_ptr = iadev->RX_DESC_BASE_ADDR;
	स_रखो_io(buf_desc_ptr, 0, माप(*buf_desc_ptr));
	buf_desc_ptr++;  
	rx_pkt_start = iadev->rx_pkt_ram;  
	क्रम(i=1; i<=iadev->num_rx_desc; i++)  
	अणु  
		स_रखो_io(buf_desc_ptr, 0, माप(*buf_desc_ptr));  
		buf_desc_ptr->buf_start_hi = rx_pkt_start >> 16;  
		buf_desc_ptr->buf_start_lo = rx_pkt_start & 0x0000ffff;  
		buf_desc_ptr++;		  
		rx_pkt_start += iadev->rx_buf_sz;  
	पूर्ण  
	IF_INIT(prपूर्णांकk("Rx Buffer desc ptr: 0x%p\n", buf_desc_ptr);)
        i = FREE_BUF_DESC_Q*iadev->memSize; 
	ग_लिखोw(i >> 16,  iadev->reass_reg+REASS_QUEUE_BASE); 
        ग_लिखोw(i, iadev->reass_reg+FREEQ_ST_ADR);
        ग_लिखोw(i+iadev->num_rx_desc*माप(u_लघु), 
                                         iadev->reass_reg+FREEQ_ED_ADR);
        ग_लिखोw(i, iadev->reass_reg+FREEQ_RD_PTR);
        ग_लिखोw(i+iadev->num_rx_desc*माप(u_लघु), 
                                        iadev->reass_reg+FREEQ_WR_PTR);    
	/* Fill the FREEQ with all the मुक्त descriptors. */  
	मुक्तq_st_adr = पढ़ोw(iadev->reass_reg+FREEQ_ST_ADR);  
	मुक्तq_start = (u_लघु *)(iadev->reass_ram+मुक्तq_st_adr);  
	क्रम(i=1; i<=iadev->num_rx_desc; i++)  
	अणु  
		*मुक्तq_start = (u_लघु)i;  
		मुक्तq_start++;  
	पूर्ण  
	IF_INIT(prपूर्णांकk("freeq_start: 0x%p\n", मुक्तq_start);)
        /* Packet Complete Queue */
        i = (PKT_COMP_Q * iadev->memSize) & 0xffff;
        ग_लिखोw(i, iadev->reass_reg+PCQ_ST_ADR);
        ग_लिखोw(i+iadev->num_vc*माप(u_लघु), iadev->reass_reg+PCQ_ED_ADR);
        ग_लिखोw(i, iadev->reass_reg+PCQ_RD_PTR);
        ग_लिखोw(i, iadev->reass_reg+PCQ_WR_PTR);

        /* Exception Queue */
        i = (EXCEPTION_Q * iadev->memSize) & 0xffff;
        ग_लिखोw(i, iadev->reass_reg+EXCP_Q_ST_ADR);
        ग_लिखोw(i + NUM_RX_EXCP * माप(RX_ERROR_Q), 
                                             iadev->reass_reg+EXCP_Q_ED_ADR);
        ग_लिखोw(i, iadev->reass_reg+EXCP_Q_RD_PTR);
        ग_लिखोw(i, iadev->reass_reg+EXCP_Q_WR_PTR); 
 
    	/* Load local copy of FREEQ and PCQ ptrs */
        iadev->rfL.fdq_st = पढ़ोw(iadev->reass_reg+FREEQ_ST_ADR) & 0xffff;
       	iadev->rfL.fdq_ed = पढ़ोw(iadev->reass_reg+FREEQ_ED_ADR) & 0xffff ;
	iadev->rfL.fdq_rd = पढ़ोw(iadev->reass_reg+FREEQ_RD_PTR) & 0xffff;
	iadev->rfL.fdq_wr = पढ़ोw(iadev->reass_reg+FREEQ_WR_PTR) & 0xffff;
        iadev->rfL.pcq_st = पढ़ोw(iadev->reass_reg+PCQ_ST_ADR) & 0xffff;
	iadev->rfL.pcq_ed = पढ़ोw(iadev->reass_reg+PCQ_ED_ADR) & 0xffff;
	iadev->rfL.pcq_rd = पढ़ोw(iadev->reass_reg+PCQ_RD_PTR) & 0xffff;
	iadev->rfL.pcq_wr = पढ़ोw(iadev->reass_reg+PCQ_WR_PTR) & 0xffff;
	
        IF_INIT(prपूर्णांकk("INIT:pcq_st:0x%x pcq_ed:0x%x pcq_rd:0x%x pcq_wr:0x%x", 
              iadev->rfL.pcq_st, iadev->rfL.pcq_ed, iadev->rfL.pcq_rd, 
              iadev->rfL.pcq_wr);)		  
	/* just क्रम check - no VP TBL */  
	/* VP Table */  
	/* ग_लिखोw(0x0b80, iadev->reass_reg+VP_LKUP_BASE); */  
	/* initialize VP Table क्रम invalid VPIs  
		- I guess we can ग_लिखो all 1s or 0x000f in the entire memory  
		  space or something similar.  
	*/  
  
	/* This seems to work and looks right to me too !!! */  
        i =  REASS_TABLE * iadev->memSize;
	ग_लिखोw((i >> 3), iadev->reass_reg+REASS_TABLE_BASE);   
 	/* initialize Reassembly table to I करोn't know what ???? */  
	reass_table = (u16 *)(iadev->reass_ram+i);  
        j = REASS_TABLE_SZ * iadev->memSize;
	क्रम(i=0; i < j; i++)  
		*reass_table++ = NO_AAL5_PKT;  
       i = 8*1024;
       vcsize_sel =  0;
       जबतक (i != iadev->num_vc) अणु
          i /= 2;
          vcsize_sel++;
       पूर्ण
       i = RX_VC_TABLE * iadev->memSize;
       ग_लिखोw(((i>>3) & 0xfff8) | vcsize_sel, iadev->reass_reg+VC_LKUP_BASE);
       vc_table = (u16 *)(iadev->reass_ram+RX_VC_TABLE*iadev->memSize);  
        j = RX_VC_TABLE_SZ * iadev->memSize;
	क्रम(i = 0; i < j; i++)  
	अणु  
		/* shअगरt the reassembly poपूर्णांकer by 3 + lower 3 bits of   
		vc_lkup_base रेजिस्टर (=3 क्रम 1K VCs) and the last byte   
		is those low 3 bits.   
		Shall program this later.  
		*/  
		*vc_table = (i << 6) | 15;	/* क्रम invalid VCI */  
		vc_table++;  
	पूर्ण  
        /* ABR VC table */
        i =  ABR_VC_TABLE * iadev->memSize;
        ग_लिखोw(i >> 3, iadev->reass_reg+ABR_LKUP_BASE);
                   
        i = ABR_VC_TABLE * iadev->memSize;
	abr_vc_table = (काष्ठा abr_vc_table *)(iadev->reass_ram+i);  
        j = REASS_TABLE_SZ * iadev->memSize;
        स_रखो ((अक्षर*)abr_vc_table, 0, j * माप(*abr_vc_table));
    	क्रम(i = 0; i < j; i++) अणु   		
		abr_vc_table->rdf = 0x0003;
             	abr_vc_table->air = 0x5eb1;
	       	abr_vc_table++;   	
        पूर्ण  

	/* Initialize other रेजिस्टरs */  
  
	/* VP Filter Register set क्रम VC Reassembly only */  
	ग_लिखोw(0xff00, iadev->reass_reg+VP_FILTER);  
        ग_लिखोw(0, iadev->reass_reg+XTRA_RM_OFFSET);
	ग_लिखोw(0x1,  iadev->reass_reg+PROTOCOL_ID);

	/* Packet Timeout Count  related Registers : 
	   Set packet समयout to occur in about 3 seconds
	   Set Packet Aging Interval count रेजिस्टर to overflow in about 4 us
 	*/  
        ग_लिखोw(0xF6F8, iadev->reass_reg+PKT_TM_CNT );

        i = (j >> 6) & 0xFF;
        j += 2 * (j - 1);
        i |= ((j << 2) & 0xFF00);
        ग_लिखोw(i, iadev->reass_reg+TMOUT_RANGE);

        /* initiate the desc_tble */
        क्रम(i=0; i<iadev->num_tx_desc;i++)
            iadev->desc_tbl[i].बारtamp = 0;

	/* to clear the पूर्णांकerrupt status रेजिस्टर - पढ़ो it */  
	पढ़ोw(iadev->reass_reg+REASS_INTR_STATUS_REG);   
  
	/* Mask Register - clear it */  
	ग_लिखोw(~(RX_FREEQ_EMPT|RX_PKT_RCVD), iadev->reass_reg+REASS_MASK_REG);  
  
	skb_queue_head_init(&iadev->rx_dma_q);  
	iadev->rx_मुक्त_desc_qhead = शून्य;   

	iadev->rx_खोलो = kसुस्मृति(iadev->num_vc, माप(व्योम *), GFP_KERNEL);
	अगर (!iadev->rx_खोलो) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL "itf %d couldn't get free page\n",
		dev->number);  
		जाओ err_मुक्त_dle;
	पूर्ण  

        iadev->rxing = 1;
        iadev->rx_pkt_cnt = 0;
	/* Mode Register */  
	ग_लिखोw(R_ONLINE, iadev->reass_reg+MODE_REG);  
	वापस 0;  

err_मुक्त_dle:
	dma_मुक्त_coherent(&iadev->pci->dev, DLE_TOTAL_SIZE, iadev->rx_dle_q.start,
			  iadev->rx_dle_dma);
err_out:
	वापस -ENOMEM;
पूर्ण  
  

/*  
	The memory map suggested in appendix A and the coding क्रम it.   
	Keeping it around just in हाल we change our mind later.  
  
		Buffer descr	0x0000 (128 - 4K)  
		UBR sched	0x1000 (1K - 4K)  
		UBR Wait q	0x2000 (1K - 4K)  
		Commn queues	0x3000 Packet Ready, Trयंत्रit comp(0x3100)  
					(128 - 256) each  
		extended VC	0x4000 (1K - 8K)  
		ABR sched	0x6000	and ABR रुको queue (1K - 2K) each  
		CBR sched	0x7000 (as needed)  
		VC table	0x8000 (1K - 32K)  
*/  
  
अटल व्योम tx_पूर्णांकr(काष्ठा aपंचांग_dev *dev)  
अणु  
	IADEV *iadev;  
	अचिन्हित लघु status;  
        अचिन्हित दीर्घ flags;

	iadev = INPH_IA_DEV(dev);  
  
	status = पढ़ोl(iadev->seg_reg+SEG_INTR_STATUS_REG);  
        अगर (status & TRANSMIT_DONE)अणु

           IF_EVENT(prपूर्णांकk("Transmit Done Intr logic run\n");)
           spin_lock_irqsave(&iadev->tx_lock, flags);
           ia_tx_poll(iadev);
           spin_unlock_irqrestore(&iadev->tx_lock, flags);
           ग_लिखोw(TRANSMIT_DONE, iadev->seg_reg+SEG_INTR_STATUS_REG);
           अगर (iadev->बंद_pending)  
               wake_up(&iadev->बंद_रुको);
        पूर्ण     	  
	अगर (status & TCQ_NOT_EMPTY)  
	अणु  
	    IF_EVENT(prपूर्णांकk("TCQ_NOT_EMPTY int received\n");)  
	पूर्ण  
पूर्ण  
  
अटल व्योम tx_dle_पूर्णांकr(काष्ठा aपंचांग_dev *dev)
अणु
        IADEV *iadev;
        काष्ठा dle *dle, *cur_dle; 
        काष्ठा sk_buff *skb;
        काष्ठा aपंचांग_vcc *vcc;
        काष्ठा ia_vcc  *iavcc;
        u_पूर्णांक dle_lp;
        अचिन्हित दीर्घ flags;

        iadev = INPH_IA_DEV(dev);
        spin_lock_irqsave(&iadev->tx_lock, flags);   
        dle = iadev->tx_dle_q.पढ़ो;
        dle_lp = पढ़ोl(iadev->dma+IPHASE5575_TX_LIST_ADDR) & 
                                        (माप(काष्ठा dle)*DLE_ENTRIES - 1);
        cur_dle = (काष्ठा dle*)(iadev->tx_dle_q.start + (dle_lp >> 4));
        जबतक (dle != cur_dle)
        अणु
            /* मुक्त the DMAed skb */ 
            skb = skb_dequeue(&iadev->tx_dma_q); 
            अगर (!skb) अवरोध;

	    /* Revenge of the 2 dle (skb + trailer) used in ia_pkt_tx() */
	    अगर (!((dle - iadev->tx_dle_q.start)%(2*माप(काष्ठा dle)))) अणु
		dma_unmap_single(&iadev->pci->dev, dle->sys_pkt_addr, skb->len,
				 DMA_TO_DEVICE);
	    पूर्ण
            vcc = ATM_SKB(skb)->vcc;
            अगर (!vcc) अणु
                  prपूर्णांकk("tx_dle_intr: vcc is null\n");
		  spin_unlock_irqrestore(&iadev->tx_lock, flags);
                  dev_kमुक्त_skb_any(skb);

                  वापस;
            पूर्ण
            iavcc = INPH_IA_VCC(vcc);
            अगर (!iavcc) अणु
                  prपूर्णांकk("tx_dle_intr: iavcc is null\n");
		  spin_unlock_irqrestore(&iadev->tx_lock, flags);
                  dev_kमुक्त_skb_any(skb);
                  वापस;
            पूर्ण
            अगर (vcc->qos.txtp.pcr >= iadev->rate_limit) अणु
               अगर ((vcc->pop) && (skb->len != 0))
               अणु     
                 vcc->pop(vcc, skb);
               पूर्ण 
               अन्यथा अणु
                 dev_kमुक्त_skb_any(skb);
               पूर्ण
            पूर्ण
            अन्यथा अणु /* Hold the rate-limited skb क्रम flow control */
               IA_SKB_STATE(skb) |= IA_DLED;
               skb_queue_tail(&iavcc->txing_skb, skb);
            पूर्ण
            IF_EVENT(prपूर्णांकk("tx_dle_intr: enque skb = 0x%p \n", skb);)
            अगर (++dle == iadev->tx_dle_q.end)
                 dle = iadev->tx_dle_q.start;
        पूर्ण
        iadev->tx_dle_q.पढ़ो = dle;
        spin_unlock_irqrestore(&iadev->tx_lock, flags);
पूर्ण
  
अटल पूर्णांक खोलो_tx(काष्ठा aपंचांग_vcc *vcc)  
अणु  
	काष्ठा ia_vcc *ia_vcc;  
	IADEV *iadev;  
	काष्ठा मुख्य_vc *vc;  
	काष्ठा ext_vc *evc;  
        पूर्णांक ret;
	IF_EVENT(prपूर्णांकk("iadev: open_tx entered vcc->vci = %d\n", vcc->vci);)  
	अगर (vcc->qos.txtp.traffic_class == ATM_NONE) वापस 0;  
	iadev = INPH_IA_DEV(vcc->dev);  
        
        अगर (iadev->phy_type & FE_25MBIT_PHY) अणु
           अगर (vcc->qos.txtp.traffic_class == ATM_ABR) अणु
               prपूर्णांकk("IA:  ABR not support\n");
               वापस -EINVAL; 
           पूर्ण
	  अगर (vcc->qos.txtp.traffic_class == ATM_CBR) अणु
               prपूर्णांकk("IA:  CBR not support\n");
               वापस -EINVAL; 
          पूर्ण
        पूर्ण
        ia_vcc =  INPH_IA_VCC(vcc);
        स_रखो((caddr_t)ia_vcc, 0, माप(*ia_vcc));
        अगर (vcc->qos.txtp.max_sdu > 
                         (iadev->tx_buf_sz - माप(काष्ठा cpcs_trailer)))अणु
           prपूर्णांकk("IA:  SDU size over (%d) the configured SDU size %d\n",
		  vcc->qos.txtp.max_sdu,iadev->tx_buf_sz);
	   vcc->dev_data = शून्य;
           kमुक्त(ia_vcc);
           वापस -EINVAL; 
        पूर्ण
	ia_vcc->vc_desc_cnt = 0;
        ia_vcc->txing = 1;

        /* find pcr */
        अगर (vcc->qos.txtp.max_pcr == ATM_MAX_PCR) 
           vcc->qos.txtp.pcr = iadev->LineRate;
        अन्यथा अगर ((vcc->qos.txtp.max_pcr == 0)&&( vcc->qos.txtp.pcr <= 0))
           vcc->qos.txtp.pcr = iadev->LineRate;
        अन्यथा अगर ((vcc->qos.txtp.max_pcr > vcc->qos.txtp.pcr) && (vcc->qos.txtp.max_pcr> 0)) 
           vcc->qos.txtp.pcr = vcc->qos.txtp.max_pcr;
        अगर (vcc->qos.txtp.pcr > iadev->LineRate)
             vcc->qos.txtp.pcr = iadev->LineRate;
        ia_vcc->pcr = vcc->qos.txtp.pcr;

        अगर (ia_vcc->pcr > (iadev->LineRate / 6) ) ia_vcc->lसमयout = HZ / 10;
        अन्यथा अगर (ia_vcc->pcr > (iadev->LineRate / 130)) ia_vcc->lसमयout = HZ;
        अन्यथा अगर (ia_vcc->pcr <= 170) ia_vcc->lसमयout = 16 * HZ;
        अन्यथा ia_vcc->lसमयout = 2700 * HZ  / ia_vcc->pcr;
        अगर (ia_vcc->pcr < iadev->rate_limit)
           skb_queue_head_init (&ia_vcc->txing_skb);
        अगर (ia_vcc->pcr < iadev->rate_limit) अणु
	   काष्ठा sock *sk = sk_aपंचांग(vcc);

	   अगर (vcc->qos.txtp.max_sdu != 0) अणु
               अगर (ia_vcc->pcr > 60000)
                  sk->sk_sndbuf = vcc->qos.txtp.max_sdu * 5;
               अन्यथा अगर (ia_vcc->pcr > 2000)
                  sk->sk_sndbuf = vcc->qos.txtp.max_sdu * 4;
               अन्यथा
                 sk->sk_sndbuf = vcc->qos.txtp.max_sdu * 3;
           पूर्ण
           अन्यथा
             sk->sk_sndbuf = 24576;
        पूर्ण
           
	vc = (काष्ठा मुख्य_vc *)iadev->MAIN_VC_TABLE_ADDR;  
	evc = (काष्ठा ext_vc *)iadev->EXT_VC_TABLE_ADDR;  
	vc += vcc->vci;  
	evc += vcc->vci;  
	स_रखो((caddr_t)vc, 0, माप(*vc));  
	स_रखो((caddr_t)evc, 0, माप(*evc));  
	  
	/* store the most signअगरicant 4 bits of vci as the last 4 bits   
		of first part of aपंचांग header.  
	   store the last 12 bits of vci as first 12 bits of the second  
		part of the aपंचांग header.  
	*/  
	evc->aपंचांग_hdr1 = (vcc->vci >> 12) & 0x000f;  
	evc->aपंचांग_hdr2 = (vcc->vci & 0x0fff) << 4;  
 
	/* check the following क्रम dअगरferent traffic classes */  
	अगर (vcc->qos.txtp.traffic_class == ATM_UBR)  
	अणु  
		vc->type = UBR;  
                vc->status = CRC_APPEND;
		vc->acr = cellrate_to_भग्न(iadev->LineRate);  
                अगर (vcc->qos.txtp.pcr > 0) 
                   vc->acr = cellrate_to_भग्न(vcc->qos.txtp.pcr);  
                IF_UBR(prपूर्णांकk("UBR: txtp.pcr = 0x%x f_rate = 0x%x\n", 
                                             vcc->qos.txtp.max_pcr,vc->acr);)
	पूर्ण  
	अन्यथा अगर (vcc->qos.txtp.traffic_class == ATM_ABR)  
	अणु       srv_cls_param_t srv_p;
		IF_ABR(prपूर्णांकk("Tx ABR VCC\n");)  
                init_abr_vc(iadev, &srv_p);
                अगर (vcc->qos.txtp.pcr > 0) 
                   srv_p.pcr = vcc->qos.txtp.pcr;
                अगर (vcc->qos.txtp.min_pcr > 0) अणु
                   पूर्णांक पंचांगpsum = iadev->sum_mcr+iadev->sum_cbr+vcc->qos.txtp.min_pcr;
                   अगर (पंचांगpsum > iadev->LineRate)
                       वापस -EBUSY;
                   srv_p.mcr = vcc->qos.txtp.min_pcr;
                   iadev->sum_mcr += vcc->qos.txtp.min_pcr;
                पूर्ण 
                अन्यथा srv_p.mcr = 0;
                अगर (vcc->qos.txtp.icr)
                   srv_p.icr = vcc->qos.txtp.icr;
                अगर (vcc->qos.txtp.tbe)
                   srv_p.tbe = vcc->qos.txtp.tbe;
                अगर (vcc->qos.txtp.frtt)
                   srv_p.frtt = vcc->qos.txtp.frtt;
                अगर (vcc->qos.txtp.rअगर)
                   srv_p.rअगर = vcc->qos.txtp.rअगर;
                अगर (vcc->qos.txtp.rdf)
                   srv_p.rdf = vcc->qos.txtp.rdf;
                अगर (vcc->qos.txtp.nrm_pres)
                   srv_p.nrm = vcc->qos.txtp.nrm;
                अगर (vcc->qos.txtp.trm_pres)
                   srv_p.trm = vcc->qos.txtp.trm;
                अगर (vcc->qos.txtp.adtf_pres)
                   srv_p.adtf = vcc->qos.txtp.adtf;
                अगर (vcc->qos.txtp.cdf_pres)
                   srv_p.cdf = vcc->qos.txtp.cdf;    
                अगर (srv_p.icr > srv_p.pcr)
                   srv_p.icr = srv_p.pcr;    
                IF_ABR(prपूर्णांकk("ABR:vcc->qos.txtp.max_pcr = %d  mcr = %d\n", 
                                                      srv_p.pcr, srv_p.mcr);)
		ia_खोलो_abr_vc(iadev, &srv_p, vcc, 1);
	पूर्ण अन्यथा अगर (vcc->qos.txtp.traffic_class == ATM_CBR) अणु
                अगर (iadev->phy_type & FE_25MBIT_PHY) अणु
                    prपूर्णांकk("IA:  CBR not support\n");
                    वापस -EINVAL; 
                पूर्ण
                अगर (vcc->qos.txtp.max_pcr > iadev->LineRate) अणु
                   IF_CBR(prपूर्णांकk("PCR is not available\n");)
                   वापस -1;
                पूर्ण
                vc->type = CBR;
                vc->status = CRC_APPEND;
                अगर ((ret = ia_cbr_setup (iadev, vcc)) < 0) अणु     
                    वापस ret;
                पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk("iadev:  Non UBR, ABR and CBR traffic not supported\n");
	पूर्ण
        
        iadev->testTable[vcc->vci]->vc_status |= VC_ACTIVE;
	IF_EVENT(prपूर्णांकk("ia open_tx returning \n");)  
	वापस 0;  
पूर्ण  
  
  
अटल पूर्णांक tx_init(काष्ठा aपंचांग_dev *dev)  
अणु  
	IADEV *iadev;  
	काष्ठा tx_buf_desc *buf_desc_ptr;
	अचिन्हित पूर्णांक tx_pkt_start;  
	व्योम *dle_addr;  
	पूर्णांक i;  
	u_लघु tcq_st_adr;  
	u_लघु *tcq_start;  
	u_लघु prq_st_adr;  
	u_लघु *prq_start;  
	काष्ठा मुख्य_vc *vc;  
	काष्ठा ext_vc *evc;   
        u_लघु पंचांगp16;
        u32 vcsize_sel;
 
	iadev = INPH_IA_DEV(dev);  
        spin_lock_init(&iadev->tx_lock);
 
	IF_INIT(prपूर्णांकk("Tx MASK REG: 0x%0x\n", 
                                पढ़ोw(iadev->seg_reg+SEG_MASK_REG));)  

	/* Allocate 4k (boundary aligned) bytes */
	dle_addr = dma_alloc_coherent(&iadev->pci->dev, DLE_TOTAL_SIZE,
				      &iadev->tx_dle_dma, GFP_KERNEL);
	अगर (!dle_addr)  अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL "can't allocate DLEs\n");
		जाओ err_out;
	पूर्ण
	iadev->tx_dle_q.start = (काष्ठा dle*)dle_addr;  
	iadev->tx_dle_q.पढ़ो = iadev->tx_dle_q.start;  
	iadev->tx_dle_q.ग_लिखो = iadev->tx_dle_q.start;  
	iadev->tx_dle_q.end = (काष्ठा dle*)((अचिन्हित दीर्घ)dle_addr+माप(काष्ठा dle)*DLE_ENTRIES);

	/* ग_लिखो the upper 20 bits of the start address to tx list address रेजिस्टर */  
	ग_लिखोl(iadev->tx_dle_dma & 0xfffff000,
	       iadev->dma + IPHASE5575_TX_LIST_ADDR);  
	ग_लिखोw(0xffff, iadev->seg_reg+SEG_MASK_REG);  
	ग_लिखोw(0, iadev->seg_reg+MODE_REG_0);  
	ग_लिखोw(RESET_SEG, iadev->seg_reg+SEG_COMMAND_REG);  
        iadev->MAIN_VC_TABLE_ADDR = iadev->seg_ram+MAIN_VC_TABLE*iadev->memSize;
        iadev->EXT_VC_TABLE_ADDR = iadev->seg_ram+EXT_VC_TABLE*iadev->memSize;
        iadev->ABR_SCHED_TABLE_ADDR=iadev->seg_ram+ABR_SCHED_TABLE*iadev->memSize;
  
	/*  
	   Transmit side control memory map  
	   --------------------------------    
	 Buffer descr 	0x0000 (128 - 4K)  
	 Commn queues	0x1000	Transmit comp, Packet पढ़ोy(0x1400)   
					(512 - 1K) each  
					TCQ - 4K, PRQ - 5K  
	 CBR Table 	0x1800 (as needed) - 6K  
	 UBR Table	0x3000 (1K - 4K) - 12K  
	 UBR Wait queue	0x4000 (1K - 4K) - 16K  
	 ABR sched	0x5000	and ABR रुको queue (1K - 2K) each  
				ABR Tbl - 20K, ABR Wq - 22K   
	 extended VC	0x6000 (1K - 8K) - 24K  
	 VC Table	0x8000 (1K - 32K) - 32K  
	  
	Between 0x2000 (8K) and 0x3000 (12K) there is 4K space left क्रम VBR Tbl  
	and Wait q, which can be allotted later.  
	*/  
     
	/* Buffer Descriptor Table Base address */  
	ग_लिखोw(TX_DESC_BASE, iadev->seg_reg+SEG_DESC_BASE);  
  
	/* initialize each entry in the buffer descriptor table */  
	buf_desc_ptr =(काष्ठा tx_buf_desc *)(iadev->seg_ram+TX_DESC_BASE);  
	स_रखो((caddr_t)buf_desc_ptr, 0, माप(*buf_desc_ptr));  
	buf_desc_ptr++;  
	tx_pkt_start = TX_PACKET_RAM;  
	क्रम(i=1; i<=iadev->num_tx_desc; i++)  
	अणु  
		स_रखो((caddr_t)buf_desc_ptr, 0, माप(*buf_desc_ptr));  
		buf_desc_ptr->desc_mode = AAL5;  
		buf_desc_ptr->buf_start_hi = tx_pkt_start >> 16;  
		buf_desc_ptr->buf_start_lo = tx_pkt_start & 0x0000ffff;  
		buf_desc_ptr++;		  
		tx_pkt_start += iadev->tx_buf_sz;  
	पूर्ण  
	iadev->tx_buf = kदो_स्मृति_array(iadev->num_tx_desc,
				      माप(*iadev->tx_buf),
				      GFP_KERNEL);
        अगर (!iadev->tx_buf) अणु
            prपूर्णांकk(KERN_ERR DEV_LABEL " couldn't get mem\n");
	    जाओ err_मुक्त_dle;
        पूर्ण
       	क्रम (i= 0; i< iadev->num_tx_desc; i++)
       	अणु
	    काष्ठा cpcs_trailer *cpcs;
 
       	    cpcs = kदो_स्मृति(माप(*cpcs), GFP_KERNEL|GFP_DMA);
            अगर(!cpcs) अणु                
		prपूर्णांकk(KERN_ERR DEV_LABEL " couldn't get freepage\n"); 
		जाओ err_मुक्त_tx_bufs;
            पूर्ण
	    iadev->tx_buf[i].cpcs = cpcs;
	    iadev->tx_buf[i].dma_addr = dma_map_single(&iadev->pci->dev,
						       cpcs,
						       माप(*cpcs),
						       DMA_TO_DEVICE);
        पूर्ण
	iadev->desc_tbl = kदो_स्मृति_array(iadev->num_tx_desc,
					माप(*iadev->desc_tbl),
					GFP_KERNEL);
	अगर (!iadev->desc_tbl) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL " couldn't get mem\n");
		जाओ err_मुक्त_all_tx_bufs;
	पूर्ण
  
	/* Communication Queues base address */  
        i = TX_COMP_Q * iadev->memSize;
	ग_लिखोw(i >> 16, iadev->seg_reg+SEG_QUEUE_BASE);  
  
	/* Transmit Complete Queue */  
	ग_लिखोw(i, iadev->seg_reg+TCQ_ST_ADR);  
	ग_लिखोw(i, iadev->seg_reg+TCQ_RD_PTR);  
	ग_लिखोw(i+iadev->num_tx_desc*माप(u_लघु),iadev->seg_reg+TCQ_WR_PTR); 
	iadev->host_tcq_wr = i + iadev->num_tx_desc*माप(u_लघु);
        ग_लिखोw(i+2 * iadev->num_tx_desc * माप(u_लघु), 
                                              iadev->seg_reg+TCQ_ED_ADR); 
	/* Fill the TCQ with all the मुक्त descriptors. */  
	tcq_st_adr = पढ़ोw(iadev->seg_reg+TCQ_ST_ADR);  
	tcq_start = (u_लघु *)(iadev->seg_ram+tcq_st_adr);  
	क्रम(i=1; i<=iadev->num_tx_desc; i++)  
	अणु  
		*tcq_start = (u_लघु)i;  
		tcq_start++;  
	पूर्ण  
  
	/* Packet Ready Queue */  
        i = PKT_RDY_Q * iadev->memSize; 
	ग_लिखोw(i, iadev->seg_reg+PRQ_ST_ADR);  
	ग_लिखोw(i+2 * iadev->num_tx_desc * माप(u_लघु), 
                                              iadev->seg_reg+PRQ_ED_ADR);
	ग_लिखोw(i, iadev->seg_reg+PRQ_RD_PTR);  
	ग_लिखोw(i, iadev->seg_reg+PRQ_WR_PTR);  
	 
        /* Load local copy of PRQ and TCQ ptrs */
        iadev->ffL.prq_st = पढ़ोw(iadev->seg_reg+PRQ_ST_ADR) & 0xffff;
	iadev->ffL.prq_ed = पढ़ोw(iadev->seg_reg+PRQ_ED_ADR) & 0xffff;
 	iadev->ffL.prq_wr = पढ़ोw(iadev->seg_reg+PRQ_WR_PTR) & 0xffff;

	iadev->ffL.tcq_st = पढ़ोw(iadev->seg_reg+TCQ_ST_ADR) & 0xffff;
	iadev->ffL.tcq_ed = पढ़ोw(iadev->seg_reg+TCQ_ED_ADR) & 0xffff;
	iadev->ffL.tcq_rd = पढ़ोw(iadev->seg_reg+TCQ_RD_PTR) & 0xffff;

	/* Just क्रम safety initializing the queue to have desc 1 always */  
	/* Fill the PRQ with all the मुक्त descriptors. */  
	prq_st_adr = पढ़ोw(iadev->seg_reg+PRQ_ST_ADR);  
	prq_start = (u_लघु *)(iadev->seg_ram+prq_st_adr);  
	क्रम(i=1; i<=iadev->num_tx_desc; i++)  
	अणु  
		*prq_start = (u_लघु)0;	/* desc 1 in all entries */  
		prq_start++;  
	पूर्ण  
	/* CBR Table */  
        IF_INIT(prपूर्णांकk("Start CBR Init\n");)
#अगर 1  /* क्रम 1K VC board, CBR_PTR_BASE is 0 */
        ग_लिखोw(0,iadev->seg_reg+CBR_PTR_BASE);
#अन्यथा /* Charlie's logic is wrong ? */
        पंचांगp16 = (iadev->seg_ram+CBR_SCHED_TABLE*iadev->memSize)>>17;
        IF_INIT(prपूर्णांकk("cbr_ptr_base = 0x%x ", पंचांगp16);)
        ग_लिखोw(पंचांगp16,iadev->seg_reg+CBR_PTR_BASE);
#पूर्ण_अगर

        IF_INIT(prपूर्णांकk("value in register = 0x%x\n",
                                   पढ़ोw(iadev->seg_reg+CBR_PTR_BASE));)
        पंचांगp16 = (CBR_SCHED_TABLE*iadev->memSize) >> 1;
        ग_लिखोw(पंचांगp16, iadev->seg_reg+CBR_TAB_BEG);
        IF_INIT(prपूर्णांकk("cbr_tab_beg = 0x%x in reg = 0x%x \n", पंचांगp16,
                                        पढ़ोw(iadev->seg_reg+CBR_TAB_BEG));)
        ग_लिखोw(पंचांगp16, iadev->seg_reg+CBR_TAB_END+1); // CBR_PTR;
        पंचांगp16 = (CBR_SCHED_TABLE*iadev->memSize + iadev->num_vc*6 - 2) >> 1;
        ग_लिखोw(पंचांगp16, iadev->seg_reg+CBR_TAB_END);
        IF_INIT(prपूर्णांकk("iadev->seg_reg = 0x%p CBR_PTR_BASE = 0x%x\n",
               iadev->seg_reg, पढ़ोw(iadev->seg_reg+CBR_PTR_BASE));)
        IF_INIT(prपूर्णांकk("CBR_TAB_BEG = 0x%x, CBR_TAB_END = 0x%x, CBR_PTR = 0x%x\n",
          पढ़ोw(iadev->seg_reg+CBR_TAB_BEG), पढ़ोw(iadev->seg_reg+CBR_TAB_END),
          पढ़ोw(iadev->seg_reg+CBR_TAB_END+1));)

        /* Initialize the CBR Schedualing Table */
        स_रखो_io(iadev->seg_ram+CBR_SCHED_TABLE*iadev->memSize, 
                                                          0, iadev->num_vc*6); 
        iadev->CbrRemEntries = iadev->CbrTotEntries = iadev->num_vc*3;
        iadev->CbrEntryPt = 0;
        iadev->Granularity = MAX_ATM_155 / iadev->CbrTotEntries;
        iadev->NumEnabledCBR = 0;

	/* UBR scheduling Table and रुको queue */  
	/* initialize all bytes of UBR scheduler table and रुको queue to 0   
		- SCHEDSZ is 1K (# of entries).  
		- UBR Table size is 4K  
		- UBR रुको queue is 4K  
	   since the table and रुको queues are contiguous, all the bytes   
	   can be initialized by one memeset.
	*/  
        
        vcsize_sel = 0;
        i = 8*1024;
        जबतक (i != iadev->num_vc) अणु
          i /= 2;
          vcsize_sel++;
        पूर्ण
 
        i = MAIN_VC_TABLE * iadev->memSize;
        ग_लिखोw(vcsize_sel | ((i >> 8) & 0xfff8),iadev->seg_reg+VCT_BASE);
        i =  EXT_VC_TABLE * iadev->memSize;
        ग_लिखोw((i >> 8) & 0xfffe, iadev->seg_reg+VCTE_BASE);
        i = UBR_SCHED_TABLE * iadev->memSize;
        ग_लिखोw((i & 0xffff) >> 11,  iadev->seg_reg+UBR_SBPTR_BASE);
        i = UBR_WAIT_Q * iadev->memSize; 
        ग_लिखोw((i >> 7) & 0xffff,  iadev->seg_reg+UBRWQ_BASE);
 	स_रखो((caddr_t)(iadev->seg_ram+UBR_SCHED_TABLE*iadev->memSize),
                                                       0, iadev->num_vc*8);
	/* ABR scheduling Table(0x5000-0x57ff) and रुको queue(0x5800-0x5fff)*/  
	/* initialize all bytes of ABR scheduler table and रुको queue to 0   
		- SCHEDSZ is 1K (# of entries).  
		- ABR Table size is 2K  
		- ABR रुको queue is 2K  
	   since the table and रुको queues are contiguous, all the bytes   
	   can be initialized by one memeset.
	*/  
        i = ABR_SCHED_TABLE * iadev->memSize;
        ग_लिखोw((i >> 11) & 0xffff, iadev->seg_reg+ABR_SBPTR_BASE);
        i = ABR_WAIT_Q * iadev->memSize;
        ग_लिखोw((i >> 7) & 0xffff, iadev->seg_reg+ABRWQ_BASE);
 
        i = ABR_SCHED_TABLE*iadev->memSize;
	स_रखो((caddr_t)(iadev->seg_ram+i),  0, iadev->num_vc*4);
	vc = (काष्ठा मुख्य_vc *)iadev->MAIN_VC_TABLE_ADDR;  
	evc = (काष्ठा ext_vc *)iadev->EXT_VC_TABLE_ADDR;  
	iadev->testTable = kदो_स्मृति_array(iadev->num_vc,
					 माप(*iadev->testTable),
					 GFP_KERNEL);
        अगर (!iadev->testTable) अणु
           prपूर्णांकk("Get freepage  failed\n");
	   जाओ err_मुक्त_desc_tbl;
        पूर्ण
	क्रम(i=0; i<iadev->num_vc; i++)  
	अणु  
		स_रखो((caddr_t)vc, 0, माप(*vc));  
		स_रखो((caddr_t)evc, 0, माप(*evc));  
                iadev->testTable[i] = kदो_स्मृति(माप(काष्ठा testTable_t),
						GFP_KERNEL);
		अगर (!iadev->testTable[i])
			जाओ err_मुक्त_test_tables;
              	iadev->testTable[i]->lastTime = 0;
 		iadev->testTable[i]->fract = 0;
                iadev->testTable[i]->vc_status = VC_UBR;
		vc++;  
		evc++;  
	पूर्ण  
  
	/* Other Initialization */  
	  
	/* Max Rate Register */  
        अगर (iadev->phy_type & FE_25MBIT_PHY) अणु
	   ग_लिखोw(RATE25, iadev->seg_reg+MAXRATE);  
	   ग_लिखोw((UBR_EN | (0x23 << 2)), iadev->seg_reg+STPARMS);  
        पूर्ण
        अन्यथा अणु
	   ग_लिखोw(cellrate_to_भग्न(iadev->LineRate),iadev->seg_reg+MAXRATE);
	   ग_लिखोw((UBR_EN | ABR_EN | (0x23 << 2)), iadev->seg_reg+STPARMS);  
        पूर्ण
	/* Set Idle Header Reigisters to be sure */  
	ग_लिखोw(0, iadev->seg_reg+IDLEHEADHI);  
	ग_लिखोw(0, iadev->seg_reg+IDLEHEADLO);  
  
	/* Program ABR UBR Priority Register  as  PRI_ABR_UBR_EQUAL */
        ग_लिखोw(0xaa00, iadev->seg_reg+ABRUBR_ARB); 

        iadev->बंद_pending = 0;
        init_रुकोqueue_head(&iadev->बंद_रुको);
        init_रुकोqueue_head(&iadev->समयout_रुको);
	skb_queue_head_init(&iadev->tx_dma_q);  
	ia_init_rtn_q(&iadev->tx_वापस_q);  

	/* RM Cell Protocol ID and Message Type */  
	ग_लिखोw(RM_TYPE_4_0, iadev->seg_reg+RM_TYPE);  
        skb_queue_head_init (&iadev->tx_backlog);
  
	/* Mode Register 1 */  
	ग_लिखोw(MODE_REG_1_VAL, iadev->seg_reg+MODE_REG_1);  
  
	/* Mode Register 0 */  
	ग_लिखोw(T_ONLINE, iadev->seg_reg+MODE_REG_0);  
  
	/* Interrupt Status Register - पढ़ो to clear */  
	पढ़ोw(iadev->seg_reg+SEG_INTR_STATUS_REG);  
  
	/* Interrupt Mask Reg- करोn't mask TCQ_NOT_EMPTY पूर्णांकerrupt generation */  
        ग_लिखोw(~(TRANSMIT_DONE | TCQ_NOT_EMPTY), iadev->seg_reg+SEG_MASK_REG);
        ग_लिखोw(TRANSMIT_DONE, iadev->seg_reg+SEG_INTR_STATUS_REG);  
        iadev->tx_pkt_cnt = 0;
        iadev->rate_limit = iadev->LineRate / 3;
  
	वापस 0;

err_मुक्त_test_tables:
	जबतक (--i >= 0)
		kमुक्त(iadev->testTable[i]);
	kमुक्त(iadev->testTable);
err_मुक्त_desc_tbl:
	kमुक्त(iadev->desc_tbl);
err_मुक्त_all_tx_bufs:
	i = iadev->num_tx_desc;
err_मुक्त_tx_bufs:
	जबतक (--i >= 0) अणु
		काष्ठा cpcs_trailer_desc *desc = iadev->tx_buf + i;

		dma_unmap_single(&iadev->pci->dev, desc->dma_addr,
				 माप(*desc->cpcs), DMA_TO_DEVICE);
		kमुक्त(desc->cpcs);
	पूर्ण
	kमुक्त(iadev->tx_buf);
err_मुक्त_dle:
	dma_मुक्त_coherent(&iadev->pci->dev, DLE_TOTAL_SIZE, iadev->tx_dle_q.start,
			  iadev->tx_dle_dma);
err_out:
	वापस -ENOMEM;
पूर्ण   
   
अटल irqवापस_t ia_पूर्णांक(पूर्णांक irq, व्योम *dev_id)  
अणु  
   काष्ठा aपंचांग_dev *dev;  
   IADEV *iadev;  
   अचिन्हित पूर्णांक status;  
   पूर्णांक handled = 0;

   dev = dev_id;  
   iadev = INPH_IA_DEV(dev);  
   जबतक( (status = पढ़ोl(iadev->reg+IPHASE5575_BUS_STATUS_REG) & 0x7f))  
   अणु 
	handled = 1;
        IF_EVENT(prपूर्णांकk("ia_int: status = 0x%x\n", status);) 
	अगर (status & STAT_REASSINT)  
	अणु  
	   /* करो something */  
	   IF_EVENT(prपूर्णांकk("REASSINT Bus status reg: %08x\n", status);) 
	   rx_पूर्णांकr(dev);  
	पूर्ण  
	अगर (status & STAT_DLERINT)  
	अणु  
	   /* Clear this bit by writing a 1 to it. */  
	   ग_लिखोl(STAT_DLERINT, iadev->reg + IPHASE5575_BUS_STATUS_REG);
	   rx_dle_पूर्णांकr(dev);  
	पूर्ण  
	अगर (status & STAT_SEGINT)  
	अणु  
	   /* करो something */ 
           IF_EVENT(prपूर्णांकk("IA: tx_intr \n");) 
	   tx_पूर्णांकr(dev);  
	पूर्ण  
	अगर (status & STAT_DLETINT)  
	अणु  
	   ग_लिखोl(STAT_DLETINT, iadev->reg + IPHASE5575_BUS_STATUS_REG);
	   tx_dle_पूर्णांकr(dev);  
	पूर्ण  
	अगर (status & (STAT_FEINT | STAT_ERRINT | STAT_MARKINT))  
	अणु  
           अगर (status & STAT_FEINT) 
               ia_frontend_पूर्णांकr(iadev);
	पूर्ण  
   पूर्ण
   वापस IRQ_RETVAL(handled);
पूर्ण  
	  
	  
	  
/*----------------------------- entries --------------------------------*/  
अटल पूर्णांक get_esi(काष्ठा aपंचांग_dev *dev)  
अणु  
	IADEV *iadev;  
	पूर्णांक i;  
	u32 mac1;  
	u16 mac2;  
	  
	iadev = INPH_IA_DEV(dev);  
	mac1 = cpu_to_be32(le32_to_cpu(पढ़ोl(  
				iadev->reg+IPHASE5575_MAC1)));  
	mac2 = cpu_to_be16(le16_to_cpu(पढ़ोl(iadev->reg+IPHASE5575_MAC2)));  
	IF_INIT(prपूर्णांकk("ESI: 0x%08x%04x\n", mac1, mac2);)  
	क्रम (i=0; i<MAC1_LEN; i++)  
		dev->esi[i] = mac1 >>(8*(MAC1_LEN-1-i));  
	  
	क्रम (i=0; i<MAC2_LEN; i++)  
		dev->esi[i+MAC1_LEN] = mac2 >>(8*(MAC2_LEN - 1 -i));  
	वापस 0;  
पूर्ण  
	  
अटल पूर्णांक reset_sar(काष्ठा aपंचांग_dev *dev)  
अणु  
	IADEV *iadev;  
	पूर्णांक i, error = 1;  
	अचिन्हित पूर्णांक pci[64];  
	  
	iadev = INPH_IA_DEV(dev);  
	क्रम(i=0; i<64; i++)  
	  अगर ((error = pci_पढ़ो_config_dword(iadev->pci,  
				i*4, &pci[i])) != PCIBIOS_SUCCESSFUL)  
  	      वापस error;  
	ग_लिखोl(0, iadev->reg+IPHASE5575_EXT_RESET);  
	क्रम(i=0; i<64; i++)  
	  अगर ((error = pci_ग_लिखो_config_dword(iadev->pci,  
					i*4, pci[i])) != PCIBIOS_SUCCESSFUL)  
	    वापस error;  
	udelay(5);  
	वापस 0;  
पूर्ण  
	  
	  
अटल पूर्णांक ia_init(काष्ठा aपंचांग_dev *dev)
अणु  
	IADEV *iadev;  
	अचिन्हित दीर्घ real_base;
	व्योम __iomem *base;
	अचिन्हित लघु command;  
	पूर्णांक error, i; 
	  
	/* The device has been identअगरied and रेजिस्टरed. Now we पढ़ो   
	   necessary configuration info like memory base address,   
	   पूर्णांकerrupt number etc */  
	  
	IF_INIT(prपूर्णांकk(">ia_init\n");)  
	dev->ci_range.vpi_bits = 0;  
	dev->ci_range.vci_bits = NR_VCI_LD;  

	iadev = INPH_IA_DEV(dev);  
	real_base = pci_resource_start (iadev->pci, 0);
	iadev->irq = iadev->pci->irq;
		  
	error = pci_पढ़ो_config_word(iadev->pci, PCI_COMMAND, &command);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): init error 0x%x\n",  
				dev->number,error);  
		वापस -EINVAL;  
	पूर्ण  
	IF_INIT(prपूर्णांकk(DEV_LABEL "(itf %d): rev.%d,realbase=0x%lx,irq=%d\n",  
			dev->number, iadev->pci->revision, real_base, iadev->irq);)
	  
	/* find mapping size of board */  
	  
	iadev->pci_map_size = pci_resource_len(iadev->pci, 0);

        अगर (iadev->pci_map_size == 0x100000)अणु
          iadev->num_vc = 4096;
	  dev->ci_range.vci_bits = NR_VCI_4K_LD;  
          iadev->memSize = 4;
        पूर्ण
        अन्यथा अगर (iadev->pci_map_size == 0x40000) अणु
          iadev->num_vc = 1024;
          iadev->memSize = 1;
        पूर्ण
        अन्यथा अणु
           prपूर्णांकk("Unknown pci_map_size = 0x%x\n", iadev->pci_map_size);
           वापस -EINVAL;
        पूर्ण
	IF_INIT(prपूर्णांकk (DEV_LABEL "map size: %i\n", iadev->pci_map_size);)  
	  
	/* enable bus mastering */
	pci_set_master(iadev->pci);

	/*  
	 * Delay at least 1us beक्रमe करोing any mem accesses (how 'bout 10?)  
	 */  
	udelay(10);  
	  
	/* mapping the physical address to a भव address in address space */  
	base = ioremap(real_base,iadev->pci_map_size);  /* ioremap is not resolved ??? */  
	  
	अगर (!base)  
	अणु  
		prपूर्णांकk(DEV_LABEL " (itf %d): can't set up page mapping\n",  
			    dev->number);  
		वापस -ENOMEM;
	पूर्ण  
	IF_INIT(prपूर्णांकk(DEV_LABEL " (itf %d): rev.%d,base=%p,irq=%d\n",  
			dev->number, iadev->pci->revision, base, iadev->irq);)
	  
	/* filling the iphase dev काष्ठाure */  
	iadev->mem = iadev->pci_map_size /2;  
	iadev->real_base = real_base;  
	iadev->base = base;  
		  
	/* Bus Interface Control Registers */  
	iadev->reg = base + REG_BASE;
	/* Segmentation Control Registers */  
	iadev->seg_reg = base + SEG_BASE;
	/* Reassembly Control Registers */  
	iadev->reass_reg = base + REASS_BASE;  
	/* Front end/ DMA control रेजिस्टरs */  
	iadev->phy = base + PHY_BASE;  
	iadev->dma = base + PHY_BASE;  
	/* RAM - Segmentation RAm and Reassembly RAM */  
	iadev->ram = base + ACTUAL_RAM_BASE;  
	iadev->seg_ram = base + ACTUAL_SEG_RAM_BASE;  
	iadev->reass_ram = base + ACTUAL_REASS_RAM_BASE;  
  
	/* lets prपूर्णांक out the above */  
	IF_INIT(prपूर्णांकk("Base addrs: %p %p %p \n %p %p %p %p\n", 
          iadev->reg,iadev->seg_reg,iadev->reass_reg, 
          iadev->phy, iadev->ram, iadev->seg_ram, 
          iadev->reass_ram);) 
	  
	/* lets try पढ़ोing the MAC address */  
	error = get_esi(dev);  
	अगर (error) अणु
	  iounmap(iadev->base);
	  वापस error;  
	पूर्ण
        prपूर्णांकk("IA: ");
	क्रम (i=0; i < ESI_LEN; i++)  
                prपूर्णांकk("%s%02X",i ? "-" : "",dev->esi[i]);  
        prपूर्णांकk("\n");  
  
        /* reset SAR */  
        अगर (reset_sar(dev)) अणु
	   iounmap(iadev->base);
           prपूर्णांकk("IA: reset SAR fail, please try again\n");
           वापस 1;
        पूर्ण
	वापस 0;  
पूर्ण  

अटल व्योम ia_update_stats(IADEV *iadev) अणु
    अगर (!iadev->carrier_detect)
        वापस;
    iadev->rx_cell_cnt += पढ़ोw(iadev->reass_reg+CELL_CTR0)&0xffff;
    iadev->rx_cell_cnt += (पढ़ोw(iadev->reass_reg+CELL_CTR1) & 0xffff) << 16;
    iadev->drop_rxpkt +=  पढ़ोw(iadev->reass_reg + DRP_PKT_CNTR ) & 0xffff;
    iadev->drop_rxcell += पढ़ोw(iadev->reass_reg + ERR_CNTR) & 0xffff;
    iadev->tx_cell_cnt += पढ़ोw(iadev->seg_reg + CELL_CTR_LO_AUTO)&0xffff;
    iadev->tx_cell_cnt += (पढ़ोw(iadev->seg_reg+CELL_CTR_HIGH_AUTO)&0xffff)<<16;
    वापस;
पूर्ण
  
अटल व्योम ia_led_समयr(काष्ठा समयr_list *unused) अणु
 	अचिन्हित दीर्घ flags;
  	अटल u_अक्षर blinking[8] = अणु0, 0, 0, 0, 0, 0, 0, 0पूर्ण;
        u_अक्षर i;
        अटल u32 ctrl_reg; 
        क्रम (i = 0; i < iadev_count; i++) अणु
           अगर (ia_dev[i]) अणु
	      ctrl_reg = पढ़ोl(ia_dev[i]->reg+IPHASE5575_BUS_CONTROL_REG);
	      अगर (blinking[i] == 0) अणु
		 blinking[i]++;
                 ctrl_reg &= (~CTRL_LED);
                 ग_लिखोl(ctrl_reg, ia_dev[i]->reg+IPHASE5575_BUS_CONTROL_REG);
                 ia_update_stats(ia_dev[i]);
              पूर्ण
              अन्यथा अणु
		 blinking[i] = 0;
		 ctrl_reg |= CTRL_LED;
                 ग_लिखोl(ctrl_reg, ia_dev[i]->reg+IPHASE5575_BUS_CONTROL_REG);
                 spin_lock_irqsave(&ia_dev[i]->tx_lock, flags);
                 अगर (ia_dev[i]->बंद_pending)  
                    wake_up(&ia_dev[i]->बंद_रुको);
                 ia_tx_poll(ia_dev[i]);
                 spin_unlock_irqrestore(&ia_dev[i]->tx_lock, flags);
              पूर्ण
           पूर्ण
        पूर्ण
	mod_समयr(&ia_समयr, jअगरfies + HZ / 4);
 	वापस;
पूर्ण

अटल व्योम ia_phy_put(काष्ठा aपंचांग_dev *dev, अचिन्हित अक्षर value,   
	अचिन्हित दीर्घ addr)  
अणु  
	ग_लिखोl(value, INPH_IA_DEV(dev)->phy+addr);  
पूर्ण  
  
अटल अचिन्हित अक्षर ia_phy_get(काष्ठा aपंचांग_dev *dev, अचिन्हित दीर्घ addr)  
अणु  
	वापस पढ़ोl(INPH_IA_DEV(dev)->phy+addr);  
पूर्ण  

अटल व्योम ia_मुक्त_tx(IADEV *iadev)
अणु
	पूर्णांक i;

	kमुक्त(iadev->desc_tbl);
	क्रम (i = 0; i < iadev->num_vc; i++)
		kमुक्त(iadev->testTable[i]);
	kमुक्त(iadev->testTable);
	क्रम (i = 0; i < iadev->num_tx_desc; i++) अणु
		काष्ठा cpcs_trailer_desc *desc = iadev->tx_buf + i;

		dma_unmap_single(&iadev->pci->dev, desc->dma_addr,
				 माप(*desc->cpcs), DMA_TO_DEVICE);
		kमुक्त(desc->cpcs);
	पूर्ण
	kमुक्त(iadev->tx_buf);
	dma_मुक्त_coherent(&iadev->pci->dev, DLE_TOTAL_SIZE, iadev->tx_dle_q.start,
			  iadev->tx_dle_dma);
पूर्ण

अटल व्योम ia_मुक्त_rx(IADEV *iadev)
अणु
	kमुक्त(iadev->rx_खोलो);
	dma_मुक्त_coherent(&iadev->pci->dev, DLE_TOTAL_SIZE, iadev->rx_dle_q.start,
			  iadev->rx_dle_dma);
पूर्ण

अटल पूर्णांक ia_start(काष्ठा aपंचांग_dev *dev)
अणु  
	IADEV *iadev;  
	पूर्णांक error;  
	अचिन्हित अक्षर phy;  
	u32 ctrl_reg;  
	IF_EVENT(prपूर्णांकk(">ia_start\n");)  
	iadev = INPH_IA_DEV(dev);  
        अगर (request_irq(iadev->irq, &ia_पूर्णांक, IRQF_SHARED, DEV_LABEL, dev)) अणु
                prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): IRQ%d is already in use\n",  
                    dev->number, iadev->irq);  
		error = -EAGAIN;
		जाओ err_out;
        पूर्ण  
        /* @@@ should release IRQ on error */  
	/* enabling memory + master */  
        अगर ((error = pci_ग_लिखो_config_word(iadev->pci,   
				PCI_COMMAND,   
				PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER )))   
	अणु  
                prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): can't enable memory+"  
                    "master (0x%x)\n",dev->number, error);  
		error = -EIO;  
		जाओ err_मुक्त_irq;
        पूर्ण  
	udelay(10);  
  
	/* Maybe we should reset the front end, initialize Bus Interface Control   
		Registers and see. */  
  
	IF_INIT(prपूर्णांकk("Bus ctrl reg: %08x\n", 
                            पढ़ोl(iadev->reg+IPHASE5575_BUS_CONTROL_REG));)  
	ctrl_reg = पढ़ोl(iadev->reg+IPHASE5575_BUS_CONTROL_REG);  
	ctrl_reg = (ctrl_reg & (CTRL_LED | CTRL_FE_RST))  
			| CTRL_B8  
			| CTRL_B16  
			| CTRL_B32  
			| CTRL_B48  
			| CTRL_B64  
			| CTRL_B128  
			| CTRL_ERRMASK  
			| CTRL_DLETMASK		/* shud be हटाओd l8r */  
			| CTRL_DLERMASK  
			| CTRL_SEGMASK  
			| CTRL_REASSMASK 	  
			| CTRL_FEMASK  
			| CTRL_CSPREEMPT;  
  
       ग_लिखोl(ctrl_reg, iadev->reg+IPHASE5575_BUS_CONTROL_REG);   
  
	IF_INIT(prपूर्णांकk("Bus ctrl reg after initializing: %08x\n", 
                           पढ़ोl(iadev->reg+IPHASE5575_BUS_CONTROL_REG));  
	   prपूर्णांकk("Bus status reg after init: %08x\n", 
                            पढ़ोl(iadev->reg+IPHASE5575_BUS_STATUS_REG));)  
    
        ia_hw_type(iadev); 
	error = tx_init(dev);  
	अगर (error)
		जाओ err_मुक्त_irq;
	error = rx_init(dev);  
	अगर (error)
		जाओ err_मुक्त_tx;
  
	ctrl_reg = पढ़ोl(iadev->reg+IPHASE5575_BUS_CONTROL_REG);  
       	ग_लिखोl(ctrl_reg | CTRL_FE_RST, iadev->reg+IPHASE5575_BUS_CONTROL_REG);   
	IF_INIT(prपूर्णांकk("Bus ctrl reg after initializing: %08x\n", 
                               पढ़ोl(iadev->reg+IPHASE5575_BUS_CONTROL_REG));)  
        phy = 0; /* resolve compiler complaपूर्णांक */
        IF_INIT ( 
	अगर ((phy=ia_phy_get(dev,0)) == 0x30)  
		prपूर्णांकk("IA: pm5346,rev.%d\n",phy&0x0f);  
	अन्यथा  
		prपूर्णांकk("IA: utopia,rev.%0x\n",phy);) 

	अगर (iadev->phy_type &  FE_25MBIT_PHY)
           ia_mb25_init(iadev);
	अन्यथा अगर (iadev->phy_type & (FE_DS3_PHY | FE_E3_PHY))
           ia_suni_pm7345_init(iadev);
	अन्यथा अणु
		error = suni_init(dev);
		अगर (error)
			जाओ err_मुक्त_rx;
		अगर (dev->phy->start) अणु
			error = dev->phy->start(dev);
			अगर (error)
				जाओ err_मुक्त_rx;
		पूर्ण
		/* Get iadev->carrier_detect status */
		ia_frontend_पूर्णांकr(iadev);
	पूर्ण
	वापस 0;

err_मुक्त_rx:
	ia_मुक्त_rx(iadev);
err_मुक्त_tx:
	ia_मुक्त_tx(iadev);
err_मुक्त_irq:
	मुक्त_irq(iadev->irq, dev);  
err_out:
	वापस error;
पूर्ण  
  
अटल व्योम ia_बंद(काष्ठा aपंचांग_vcc *vcc)  
अणु
	DEFINE_WAIT(रुको);
        u16 *vc_table;
        IADEV *iadev;
        काष्ठा ia_vcc *ia_vcc;
        काष्ठा sk_buff *skb = शून्य;
        काष्ठा sk_buff_head पंचांगp_tx_backlog, पंचांगp_vcc_backlog;
        अचिन्हित दीर्घ बंदसमय, flags;

        iadev = INPH_IA_DEV(vcc->dev);
        ia_vcc = INPH_IA_VCC(vcc);
	अगर (!ia_vcc) वापस;  

        IF_EVENT(prपूर्णांकk("ia_close: ia_vcc->vc_desc_cnt = %d  vci = %d\n", 
                                              ia_vcc->vc_desc_cnt,vcc->vci);)
	clear_bit(ATM_VF_READY,&vcc->flags);
        skb_queue_head_init (&पंचांगp_tx_backlog);
        skb_queue_head_init (&पंचांगp_vcc_backlog); 
        अगर (vcc->qos.txtp.traffic_class != ATM_NONE) अणु
           iadev->बंद_pending++;
	   prepare_to_रुको(&iadev->समयout_रुको, &रुको, TASK_UNINTERRUPTIBLE);
	   schedule_समयout(msecs_to_jअगरfies(500));
	   finish_रुको(&iadev->समयout_रुको, &रुको);
           spin_lock_irqsave(&iadev->tx_lock, flags); 
           जबतक((skb = skb_dequeue(&iadev->tx_backlog))) अणु
              अगर (ATM_SKB(skb)->vcc == vcc)अणु 
                 अगर (vcc->pop) vcc->pop(vcc, skb);
                 अन्यथा dev_kमुक्त_skb_any(skb);
              पूर्ण
              अन्यथा 
                 skb_queue_tail(&पंचांगp_tx_backlog, skb);
           पूर्ण 
           जबतक((skb = skb_dequeue(&पंचांगp_tx_backlog))) 
             skb_queue_tail(&iadev->tx_backlog, skb);
           IF_EVENT(prपूर्णांकk("IA TX Done decs_cnt = %d\n", ia_vcc->vc_desc_cnt);) 
           बंदसमय = 300000 / ia_vcc->pcr;
           अगर (बंदसमय == 0)
              बंदसमय = 1;
           spin_unlock_irqrestore(&iadev->tx_lock, flags);
           रुको_event_समयout(iadev->बंद_रुको, (ia_vcc->vc_desc_cnt <= 0), बंदसमय);
           spin_lock_irqsave(&iadev->tx_lock, flags);
           iadev->बंद_pending--;
           iadev->testTable[vcc->vci]->lastTime = 0;
           iadev->testTable[vcc->vci]->fract = 0; 
           iadev->testTable[vcc->vci]->vc_status = VC_UBR; 
           अगर (vcc->qos.txtp.traffic_class == ATM_ABR) अणु
              अगर (vcc->qos.txtp.min_pcr > 0)
                 iadev->sum_mcr -= vcc->qos.txtp.min_pcr;
           पूर्ण
           अगर (vcc->qos.txtp.traffic_class == ATM_CBR) अणु
              ia_vcc = INPH_IA_VCC(vcc); 
              iadev->sum_mcr -= ia_vcc->NumCbrEntry*iadev->Granularity;
              ia_cbrVc_बंद (vcc);
           पूर्ण
           spin_unlock_irqrestore(&iadev->tx_lock, flags);
        पूर्ण
        
        अगर (vcc->qos.rxtp.traffic_class != ATM_NONE) अणु   
           // reset reass table
           vc_table = (u16 *)(iadev->reass_ram+REASS_TABLE*iadev->memSize);
           vc_table += vcc->vci; 
           *vc_table = NO_AAL5_PKT;
           // reset vc table
           vc_table = (u16 *)(iadev->reass_ram+RX_VC_TABLE*iadev->memSize);
           vc_table += vcc->vci;
           *vc_table = (vcc->vci << 6) | 15;
           अगर (vcc->qos.rxtp.traffic_class == ATM_ABR) अणु
              काष्ठा abr_vc_table __iomem *abr_vc_table = 
                                (iadev->reass_ram+ABR_VC_TABLE*iadev->memSize);
              abr_vc_table +=  vcc->vci;
              abr_vc_table->rdf = 0x0003;
              abr_vc_table->air = 0x5eb1;
           पूर्ण                                 
           // Drain the packets
           rx_dle_पूर्णांकr(vcc->dev); 
           iadev->rx_खोलो[vcc->vci] = शून्य;
        पूर्ण
	kमुक्त(INPH_IA_VCC(vcc));  
        ia_vcc = शून्य;
        vcc->dev_data = शून्य;
        clear_bit(ATM_VF_ADDR,&vcc->flags);
        वापस;        
पूर्ण  
  
अटल पूर्णांक ia_खोलो(काष्ठा aपंचांग_vcc *vcc)
अणु  
	काष्ठा ia_vcc *ia_vcc;  
	पूर्णांक error;  
	अगर (!test_bit(ATM_VF_PARTIAL,&vcc->flags))  
	अणु  
		IF_EVENT(prपूर्णांकk("ia: not partially allocated resources\n");)  
		vcc->dev_data = शून्य;
	पूर्ण  
	अगर (vcc->vci != ATM_VPI_UNSPEC && vcc->vpi != ATM_VCI_UNSPEC)  
	अणु  
		IF_EVENT(prपूर्णांकk("iphase open: unspec part\n");)  
		set_bit(ATM_VF_ADDR,&vcc->flags);
	पूर्ण  
	अगर (vcc->qos.aal != ATM_AAL5)  
		वापस -EINVAL;  
	IF_EVENT(prपूर्णांकk(DEV_LABEL "(itf %d): open %d.%d\n", 
                                 vcc->dev->number, vcc->vpi, vcc->vci);)  
  
	/* Device dependent initialization */  
	ia_vcc = kदो_स्मृति(माप(*ia_vcc), GFP_KERNEL);  
	अगर (!ia_vcc) वापस -ENOMEM;  
	vcc->dev_data = ia_vcc;
  
	अगर ((error = खोलो_rx(vcc)))  
	अणु  
		IF_EVENT(prपूर्णांकk("iadev: error in open_rx, closing\n");)  
		ia_बंद(vcc);  
		वापस error;  
	पूर्ण  
  
	अगर ((error = खोलो_tx(vcc)))  
	अणु  
		IF_EVENT(prपूर्णांकk("iadev: error in open_tx, closing\n");)  
		ia_बंद(vcc);  
		वापस error;  
	पूर्ण  
  
	set_bit(ATM_VF_READY,&vcc->flags);

#अगर 0
        अणु
           अटल u8 first = 1; 
           अगर (first) अणु
              ia_समयr.expires = jअगरfies + 3*HZ;
              add_समयr(&ia_समयr);
              first = 0;
           पूर्ण           
        पूर्ण
#पूर्ण_अगर
	IF_EVENT(prपूर्णांकk("ia open returning\n");)  
	वापस 0;  
पूर्ण  
  
अटल पूर्णांक ia_change_qos(काष्ठा aपंचांग_vcc *vcc, काष्ठा aपंचांग_qos *qos, पूर्णांक flags)  
अणु  
	IF_EVENT(prपूर्णांकk(">ia_change_qos\n");)  
	वापस 0;  
पूर्ण  
  
अटल पूर्णांक ia_ioctl(काष्ठा aपंचांग_dev *dev, अचिन्हित पूर्णांक cmd, व्योम __user *arg)  
अणु  
   IA_CMDBUF ia_cmds;
   IADEV *iadev;
   पूर्णांक i, board;
   u16 __user *पंचांगps;
   IF_EVENT(prपूर्णांकk(">ia_ioctl\n");)  
   अगर (cmd != IA_CMD) अणु
      अगर (!dev->phy->ioctl) वापस -EINVAL;
      वापस dev->phy->ioctl(dev,cmd,arg);
   पूर्ण
   अगर (copy_from_user(&ia_cmds, arg, माप ia_cmds)) वापस -EFAULT; 
   board = ia_cmds.status;

	अगर ((board < 0) || (board > iadev_count))
		board = 0;
	board = array_index_nospec(board, iadev_count + 1);

   iadev = ia_dev[board];
   चयन (ia_cmds.cmd) अणु
   हाल MEMDUMP:
   अणु
	चयन (ia_cmds.sub_cmd) अणु
          हाल MEMDUMP_SEGREG:
	     अगर (!capable(CAP_NET_ADMIN)) वापस -EPERM;
             पंचांगps = (u16 __user *)ia_cmds.buf;
             क्रम(i=0; i<0x80; i+=2, पंचांगps++)
                अगर(put_user((u16)(पढ़ोl(iadev->seg_reg+i) & 0xffff), पंचांगps)) वापस -EFAULT;
             ia_cmds.status = 0;
             ia_cmds.len = 0x80;
             अवरोध;
          हाल MEMDUMP_REASSREG:
	     अगर (!capable(CAP_NET_ADMIN)) वापस -EPERM;
             पंचांगps = (u16 __user *)ia_cmds.buf;
             क्रम(i=0; i<0x80; i+=2, पंचांगps++)
                अगर(put_user((u16)(पढ़ोl(iadev->reass_reg+i) & 0xffff), पंचांगps)) वापस -EFAULT;
             ia_cmds.status = 0;
             ia_cmds.len = 0x80;
             अवरोध;
          हाल MEMDUMP_FFL:
          अणु  
             ia_regs_t       *regs_local;
             ffredn_t        *ffL;
             rfredn_t        *rfL;
                     
	     अगर (!capable(CAP_NET_ADMIN)) वापस -EPERM;
	     regs_local = kदो_स्मृति(माप(*regs_local), GFP_KERNEL);
	     अगर (!regs_local) वापस -ENOMEM;
	     ffL = &regs_local->ffredn;
	     rfL = &regs_local->rfredn;
             /* Copy real rfred रेजिस्टरs पूर्णांकo the local copy */
 	     क्रम (i=0; i<(माप (rfredn_t))/4; i++)
                ((u_पूर्णांक *)rfL)[i] = पढ़ोl(iadev->reass_reg + i) & 0xffff;
             	/* Copy real ffred रेजिस्टरs पूर्णांकo the local copy */
	     क्रम (i=0; i<(माप (ffredn_t))/4; i++)
                ((u_पूर्णांक *)ffL)[i] = पढ़ोl(iadev->seg_reg + i) & 0xffff;

             अगर (copy_to_user(ia_cmds.buf, regs_local,माप(ia_regs_t))) अणु
                kमुक्त(regs_local);
                वापस -EFAULT;
             पूर्ण
             kमुक्त(regs_local);
             prपूर्णांकk("Board %d registers dumped\n", board);
             ia_cmds.status = 0;                  
	 पूर्ण	
    	     अवरोध;        
         हाल READ_REG:
         अणु  
	     अगर (!capable(CAP_NET_ADMIN)) वापस -EPERM;
             desc_dbg(iadev); 
             ia_cmds.status = 0; 
         पूर्ण
             अवरोध;
         हाल 0x6:
         अणु  
             ia_cmds.status = 0; 
             prपूर्णांकk("skb = 0x%p\n", skb_peek(&iadev->tx_backlog));
             prपूर्णांकk("rtn_q: 0x%p\n",ia_deque_rtn_q(&iadev->tx_वापस_q));
         पूर्ण
             अवरोध;
         हाल 0x8:
         अणु
             काष्ठा k_sonet_stats *stats;
             stats = &PRIV(_ia_dev[board])->sonet_stats;
             prपूर्णांकk("section_bip: %d\n", atomic_पढ़ो(&stats->section_bip));
             prपूर्णांकk("line_bip   : %d\n", atomic_पढ़ो(&stats->line_bip));
             prपूर्णांकk("path_bip   : %d\n", atomic_पढ़ो(&stats->path_bip));
             prपूर्णांकk("line_febe  : %d\n", atomic_पढ़ो(&stats->line_febe));
             prपूर्णांकk("path_febe  : %d\n", atomic_पढ़ो(&stats->path_febe));
             prपूर्णांकk("corr_hcs   : %d\n", atomic_पढ़ो(&stats->corr_hcs));
             prपूर्णांकk("uncorr_hcs : %d\n", atomic_पढ़ो(&stats->uncorr_hcs));
             prपूर्णांकk("tx_cells   : %d\n", atomic_पढ़ो(&stats->tx_cells));
             prपूर्णांकk("rx_cells   : %d\n", atomic_पढ़ो(&stats->rx_cells));
         पूर्ण
            ia_cmds.status = 0;
            अवरोध;
         हाल 0x9:
	    अगर (!capable(CAP_NET_ADMIN)) वापस -EPERM;
            क्रम (i = 1; i <= iadev->num_rx_desc; i++)
               मुक्त_desc(_ia_dev[board], i);
            ग_लिखोw( ~(RX_FREEQ_EMPT | RX_EXCP_RCVD), 
                                            iadev->reass_reg+REASS_MASK_REG);
            iadev->rxing = 1;
            
            ia_cmds.status = 0;
            अवरोध;

         हाल 0xb:
	    अगर (!capable(CAP_NET_ADMIN)) वापस -EPERM;
            ia_frontend_पूर्णांकr(iadev);
            अवरोध;
         हाल 0xa:
	    अगर (!capable(CAP_NET_ADMIN)) वापस -EPERM;
         अणु  
             ia_cmds.status = 0; 
             IADebugFlag = ia_cmds.maddr;
             prपूर्णांकk("New debug option loaded\n");
         पूर्ण
             अवरोध;
         शेष:
             ia_cmds.status = 0;
             अवरोध;
      पूर्ण	
   पूर्ण
      अवरोध;
   शेष:
      अवरोध;

   पूर्ण	
   वापस 0;  
पूर्ण  
  
अटल पूर्णांक ia_pkt_tx (काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb) अणु
        IADEV *iadev;
        काष्ठा dle *wr_ptr;
        काष्ठा tx_buf_desc __iomem *buf_desc_ptr;
        पूर्णांक desc;
        पूर्णांक comp_code;
        पूर्णांक total_len;
        काष्ठा cpcs_trailer *trailer;
        काष्ठा ia_vcc *iavcc;

        iadev = INPH_IA_DEV(vcc->dev);  
        iavcc = INPH_IA_VCC(vcc);
        अगर (!iavcc->txing) अणु
           prपूर्णांकk("discard packet on closed VC\n");
           अगर (vcc->pop)
		vcc->pop(vcc, skb);
           अन्यथा
		dev_kमुक्त_skb_any(skb);
	   वापस 0;
        पूर्ण

        अगर (skb->len > iadev->tx_buf_sz - 8) अणु
           prपूर्णांकk("Transmit size over tx buffer size\n");
           अगर (vcc->pop)
                 vcc->pop(vcc, skb);
           अन्यथा
                 dev_kमुक्त_skb_any(skb);
          वापस 0;
        पूर्ण
        अगर ((अचिन्हित दीर्घ)skb->data & 3) अणु
           prपूर्णांकk("Misaligned SKB\n");
           अगर (vcc->pop)
                 vcc->pop(vcc, skb);
           अन्यथा
                 dev_kमुक्त_skb_any(skb);
           वापस 0;
        पूर्ण       
	/* Get a descriptor number from our मुक्त descriptor queue  
	   We get the descr number from the TCQ now, since I am using  
	   the TCQ as a मुक्त buffer queue. Initially TCQ will be   
	   initialized with all the descriptors and is hence, full.  
	*/
	desc = get_desc (iadev, iavcc);
	अगर (desc == 0xffff) 
	    वापस 1;
	comp_code = desc >> 13;  
	desc &= 0x1fff;  
  
	अगर ((desc == 0) || (desc > iadev->num_tx_desc))  
	अणु  
		IF_ERR(prपूर्णांकk(DEV_LABEL "invalid desc for send: %d\n", desc);) 
                atomic_inc(&vcc->stats->tx);
		अगर (vcc->pop)   
		    vcc->pop(vcc, skb);   
		अन्यथा  
		    dev_kमुक्त_skb_any(skb);
		वापस 0;   /* वापस SUCCESS */
	पूर्ण  
  
	अगर (comp_code)  
	अणु  
	    IF_ERR(prपूर्णांकk(DEV_LABEL "send desc:%d completion code %d error\n", 
                                                            desc, comp_code);)  
	पूर्ण  
       
        /* remember the desc and vcc mapping */
        iavcc->vc_desc_cnt++;
        iadev->desc_tbl[desc-1].iavcc = iavcc;
        iadev->desc_tbl[desc-1].txskb = skb;
        IA_SKB_STATE(skb) = 0;

        iadev->ffL.tcq_rd += 2;
        अगर (iadev->ffL.tcq_rd > iadev->ffL.tcq_ed)
	  	iadev->ffL.tcq_rd  = iadev->ffL.tcq_st;
	ग_लिखोw(iadev->ffL.tcq_rd, iadev->seg_reg+TCQ_RD_PTR);
  
	/* Put the descriptor number in the packet पढ़ोy queue  
		and put the updated ग_लिखो poपूर्णांकer in the DLE field   
	*/   
	*(u16*)(iadev->seg_ram+iadev->ffL.prq_wr) = desc; 

 	iadev->ffL.prq_wr += 2;
        अगर (iadev->ffL.prq_wr > iadev->ffL.prq_ed)
                iadev->ffL.prq_wr = iadev->ffL.prq_st;
	  
	/* Figure out the exact length of the packet and padding required to 
           make it  aligned on a 48 byte boundary.  */
	total_len = skb->len + माप(काष्ठा cpcs_trailer);  
	total_len = ((total_len + 47) / 48) * 48;
	IF_TX(prपूर्णांकk("ia packet len:%d padding:%d\n", total_len, total_len - skb->len);)  
 
	/* Put the packet in a tx buffer */   
	trailer = iadev->tx_buf[desc-1].cpcs;
        IF_TX(prपूर्णांकk("Sent: skb = 0x%p skb->data: 0x%p len: %d, desc: %d\n",
                  skb, skb->data, skb->len, desc);)
	trailer->control = 0; 
        /*big endian*/ 
	trailer->length = ((skb->len & 0xff) << 8) | ((skb->len & 0xff00) >> 8);
	trailer->crc32 = 0;	/* not needed - dummy bytes */  

	/* Display the packet */  
	IF_TXPKT(prपूर्णांकk("Sent data: len = %d MsgNum = %d\n", 
                                                        skb->len, tcnter++);  
        xdump(skb->data, skb->len, "TX: ");
        prपूर्णांकk("\n");)

	/* Build the buffer descriptor */  
	buf_desc_ptr = iadev->seg_ram+TX_DESC_BASE;
	buf_desc_ptr += desc;	/* poपूर्णांकs to the corresponding entry */  
	buf_desc_ptr->desc_mode = AAL5 | EOM_EN | APP_CRC32 | CMPL_INT;   
	/* Huh ? p.115 of users guide describes this as a पढ़ो-only रेजिस्टर */
        ग_लिखोw(TRANSMIT_DONE, iadev->seg_reg+SEG_INTR_STATUS_REG);
	buf_desc_ptr->vc_index = vcc->vci;
	buf_desc_ptr->bytes = total_len;  

        अगर (vcc->qos.txtp.traffic_class == ATM_ABR)  
	   clear_lockup (vcc, iadev);

	/* Build the DLE काष्ठाure */  
	wr_ptr = iadev->tx_dle_q.ग_लिखो;  
	स_रखो((caddr_t)wr_ptr, 0, माप(*wr_ptr));  
	wr_ptr->sys_pkt_addr = dma_map_single(&iadev->pci->dev, skb->data,
					      skb->len, DMA_TO_DEVICE);
	wr_ptr->local_pkt_addr = (buf_desc_ptr->buf_start_hi << 16) | 
                                                  buf_desc_ptr->buf_start_lo;  
	/* wr_ptr->bytes = swap_byte_order(total_len); didn't seem to affect?? */
	wr_ptr->bytes = skb->len;  

        /* hw bug - DLEs of 0x2d, 0x2e, 0x2f cause DMA lockup */
        अगर ((wr_ptr->bytes >> 2) == 0xb)
           wr_ptr->bytes = 0x30;

	wr_ptr->mode = TX_DLE_PSI; 
	wr_ptr->prq_wr_ptr_data = 0;
  
	/* end is not to be used क्रम the DLE q */  
	अगर (++wr_ptr == iadev->tx_dle_q.end)  
		wr_ptr = iadev->tx_dle_q.start;  
        
        /* Build trailer dle */
        wr_ptr->sys_pkt_addr = iadev->tx_buf[desc-1].dma_addr;
        wr_ptr->local_pkt_addr = ((buf_desc_ptr->buf_start_hi << 16) | 
          buf_desc_ptr->buf_start_lo) + total_len - माप(काष्ठा cpcs_trailer);

        wr_ptr->bytes = माप(काष्ठा cpcs_trailer);
        wr_ptr->mode = DMA_INT_ENABLE; 
        wr_ptr->prq_wr_ptr_data = iadev->ffL.prq_wr;
        
        /* end is not to be used क्रम the DLE q */
        अगर (++wr_ptr == iadev->tx_dle_q.end)  
                wr_ptr = iadev->tx_dle_q.start;

	iadev->tx_dle_q.ग_लिखो = wr_ptr;  
        ATM_DESC(skb) = vcc->vci;
        skb_queue_tail(&iadev->tx_dma_q, skb);

        atomic_inc(&vcc->stats->tx);
        iadev->tx_pkt_cnt++;
	/* Increment transaction counter */  
	ग_लिखोl(2, iadev->dma+IPHASE5575_TX_COUNTER);  
        
#अगर 0        
        /* add flow control logic */ 
        अगर (atomic_पढ़ो(&vcc->stats->tx) % 20 == 0) अणु
          अगर (iavcc->vc_desc_cnt > 10) अणु
             vcc->tx_quota =  vcc->tx_quota * 3 / 4;
            prपूर्णांकk("Tx1:  vcc->tx_quota = %d \n", (u32)vcc->tx_quota );
              iavcc->flow_inc = -1;
              iavcc->saved_tx_quota = vcc->tx_quota;
           पूर्ण अन्यथा अगर ((iavcc->flow_inc < 0) && (iavcc->vc_desc_cnt < 3)) अणु
             // vcc->tx_quota = 3 * iavcc->saved_tx_quota / 4;
             prपूर्णांकk("Tx2:  vcc->tx_quota = %d \n", (u32)vcc->tx_quota ); 
              iavcc->flow_inc = 0;
           पूर्ण
        पूर्ण
#पूर्ण_अगर
	IF_TX(prपूर्णांकk("ia send done\n");)  
	वापस 0;  
पूर्ण  

अटल पूर्णांक ia_send(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
        IADEV *iadev; 
        अचिन्हित दीर्घ flags;

        iadev = INPH_IA_DEV(vcc->dev);
        अगर ((!skb)||(skb->len>(iadev->tx_buf_sz-माप(काष्ठा cpcs_trailer))))
        अणु
            अगर (!skb)
                prपूर्णांकk(KERN_CRIT "null skb in ia_send\n");
            अन्यथा dev_kमुक्त_skb_any(skb);
            वापस -EINVAL;
        पूर्ण                         
        spin_lock_irqsave(&iadev->tx_lock, flags); 
        अगर (!test_bit(ATM_VF_READY,&vcc->flags))अणु 
            dev_kमुक्त_skb_any(skb);
            spin_unlock_irqrestore(&iadev->tx_lock, flags);
            वापस -EINVAL; 
        पूर्ण
        ATM_SKB(skb)->vcc = vcc;
 
        अगर (skb_peek(&iadev->tx_backlog)) अणु
           skb_queue_tail(&iadev->tx_backlog, skb);
        पूर्ण
        अन्यथा अणु
           अगर (ia_pkt_tx (vcc, skb)) अणु
              skb_queue_tail(&iadev->tx_backlog, skb);
           पूर्ण
        पूर्ण
        spin_unlock_irqrestore(&iadev->tx_lock, flags);
        वापस 0;

पूर्ण

अटल पूर्णांक ia_proc_पढ़ो(काष्ठा aपंचांग_dev *dev,loff_t *pos,अक्षर *page)
अणु 
  पूर्णांक   left = *pos, n;   
  अक्षर  *पंचांगpPtr;
  IADEV *iadev = INPH_IA_DEV(dev);
  अगर(!left--) अणु
     अगर (iadev->phy_type == FE_25MBIT_PHY) अणु
       n = प्र_लिखो(page, "  Board Type         :  Iphase5525-1KVC-128K\n");
       वापस n;
     पूर्ण
     अगर (iadev->phy_type == FE_DS3_PHY)
        n = प्र_लिखो(page, "  Board Type         :  Iphase-ATM-DS3");
     अन्यथा अगर (iadev->phy_type == FE_E3_PHY)
        n = प्र_लिखो(page, "  Board Type         :  Iphase-ATM-E3");
     अन्यथा अगर (iadev->phy_type == FE_UTP_OPTION)
         n = प्र_लिखो(page, "  Board Type         :  Iphase-ATM-UTP155"); 
     अन्यथा
        n = प्र_लिखो(page, "  Board Type         :  Iphase-ATM-OC3");
     पंचांगpPtr = page + n;
     अगर (iadev->pci_map_size == 0x40000)
        n += प्र_लिखो(पंचांगpPtr, "-1KVC-");
     अन्यथा
        n += प्र_लिखो(पंचांगpPtr, "-4KVC-");  
     पंचांगpPtr = page + n; 
     अगर ((iadev->memType & MEM_SIZE_MASK) == MEM_SIZE_1M)
        n += प्र_लिखो(पंचांगpPtr, "1M  \n");
     अन्यथा अगर ((iadev->memType & MEM_SIZE_MASK) == MEM_SIZE_512K)
        n += प्र_लिखो(पंचांगpPtr, "512K\n");
     अन्यथा
       n += प्र_लिखो(पंचांगpPtr, "128K\n");
     वापस n;
  पूर्ण
  अगर (!left) अणु
     वापस  प्र_लिखो(page, "  Number of Tx Buffer:  %u\n"
                           "  Size of Tx Buffer  :  %u\n"
                           "  Number of Rx Buffer:  %u\n"
                           "  Size of Rx Buffer  :  %u\n"
                           "  Packets Received   :  %u\n"
                           "  Packets Transmitted:  %u\n"
                           "  Cells Received     :  %u\n"
                           "  Cells Transmitted  :  %u\n"
                           "  Board Dropped Cells:  %u\n"
                           "  Board Dropped Pkts :  %u\n",
                           iadev->num_tx_desc,  iadev->tx_buf_sz,
                           iadev->num_rx_desc,  iadev->rx_buf_sz,
                           iadev->rx_pkt_cnt,   iadev->tx_pkt_cnt,
                           iadev->rx_cell_cnt, iadev->tx_cell_cnt,
                           iadev->drop_rxcell, iadev->drop_rxpkt);                        
  पूर्ण
  वापस 0;
पूर्ण
  
अटल स्थिर काष्ठा aपंचांगdev_ops ops = अणु  
	.खोलो		= ia_खोलो,  
	.बंद		= ia_बंद,  
	.ioctl		= ia_ioctl,  
	.send		= ia_send,  
	.phy_put	= ia_phy_put,  
	.phy_get	= ia_phy_get,  
	.change_qos	= ia_change_qos,  
	.proc_पढ़ो	= ia_proc_पढ़ो,
	.owner		= THIS_MODULE,
पूर्ण;  
	  
अटल पूर्णांक ia_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु  
	काष्ठा aपंचांग_dev *dev;  
	IADEV *iadev;  
	पूर्णांक ret;

	iadev = kzalloc(माप(*iadev), GFP_KERNEL);
	अगर (!iadev) अणु
		ret = -ENOMEM;
		जाओ err_out;
	पूर्ण

	iadev->pci = pdev;

	IF_INIT(prपूर्णांकk("ia detected at bus:%d dev: %d function:%d\n",
		pdev->bus->number, PCI_SLOT(pdev->devfn), PCI_FUNC(pdev->devfn));)
	अगर (pci_enable_device(pdev)) अणु
		ret = -ENODEV;
		जाओ err_out_मुक्त_iadev;
	पूर्ण
	dev = aपंचांग_dev_रेजिस्टर(DEV_LABEL, &pdev->dev, &ops, -1, शून्य);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ err_out_disable_dev;
	पूर्ण
	dev->dev_data = iadev;
	IF_INIT(prपूर्णांकk(DEV_LABEL "registered at (itf :%d)\n", dev->number);)
	IF_INIT(prपूर्णांकk("dev_id = 0x%p iadev->LineRate = %d \n", dev,
		iadev->LineRate);)

	pci_set_drvdata(pdev, dev);

	ia_dev[iadev_count] = iadev;
	_ia_dev[iadev_count] = dev;
	iadev_count++;
	अगर (ia_init(dev) || ia_start(dev)) अणु  
		IF_INIT(prपूर्णांकk("IA register failed!\n");)
		iadev_count--;
		ia_dev[iadev_count] = शून्य;
		_ia_dev[iadev_count] = शून्य;
		ret = -EINVAL;
		जाओ err_out_deरेजिस्टर_dev;
	पूर्ण
	IF_EVENT(prपूर्णांकk("iadev_count = %d\n", iadev_count);)

	iadev->next_board = ia_boards;  
	ia_boards = dev;  

	वापस 0;

err_out_deरेजिस्टर_dev:
	aपंचांग_dev_deरेजिस्टर(dev);  
err_out_disable_dev:
	pci_disable_device(pdev);
err_out_मुक्त_iadev:
	kमुक्त(iadev);
err_out:
	वापस ret;
पूर्ण

अटल व्योम ia_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा aपंचांग_dev *dev = pci_get_drvdata(pdev);
	IADEV *iadev = INPH_IA_DEV(dev);

	/* Disable phy पूर्णांकerrupts */
	ia_phy_put(dev, ia_phy_get(dev, SUNI_RSOP_CIE) & ~(SUNI_RSOP_CIE_LOSE),
				   SUNI_RSOP_CIE);
	udelay(1);

	अगर (dev->phy && dev->phy->stop)
		dev->phy->stop(dev);

	/* De-रेजिस्टर device */  
      	मुक्त_irq(iadev->irq, dev);
	iadev_count--;
	ia_dev[iadev_count] = शून्य;
	_ia_dev[iadev_count] = शून्य;
	IF_EVENT(prपूर्णांकk("deregistering iav at (itf:%d)\n", dev->number);)
	aपंचांग_dev_deरेजिस्टर(dev);

      	iounmap(iadev->base);  
	pci_disable_device(pdev);

	ia_मुक्त_rx(iadev);
	ia_मुक्त_tx(iadev);

      	kमुक्त(iadev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id ia_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_IPHASE, 0x0008, PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु PCI_VENDOR_ID_IPHASE, 0x0009, PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु 0,पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ia_pci_tbl);

अटल काष्ठा pci_driver ia_driver = अणु
	.name =         DEV_LABEL,
	.id_table =     ia_pci_tbl,
	.probe =        ia_init_one,
	.हटाओ =       ia_हटाओ_one,
पूर्ण;

अटल पूर्णांक __init ia_module_init(व्योम)
अणु
	पूर्णांक ret;

	ret = pci_रेजिस्टर_driver(&ia_driver);
	अगर (ret >= 0) अणु
		ia_समयr.expires = jअगरfies + 3*HZ;
		add_समयr(&ia_समयr); 
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_ERR DEV_LABEL ": no adapter found\n");  
	वापस ret;
पूर्ण

अटल व्योम __निकास ia_module_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ia_driver);

        del_समयr(&ia_समयr);
पूर्ण

module_init(ia_module_init);
module_निकास(ia_module_निकास);
