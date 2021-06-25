<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* 
 *  Copyright (C) 1997	Wu Ching Chen
 *  2.1.x update (C) 1998  Krzysztof G. Baranowski
 *  2.5.x update (C) 2002  Red Hat
 *  2.6.x update (C) 2004  Red Hat
 *
 * Marcelo Tosatti <marcelo@conectiva.com.br> : SMP fixes
 *
 * Wu Ching Chen : शून्य poपूर्णांकer fixes  2000/06/02
 *		   support atp876 chip
 *		   enable 32 bit fअगरo transfer
 *		   support cdrom & हटाओ device run ultra speed
 *		   fix disconnect bug  2000/12/21
 *		   support atp880 chip lvd u160 2001/05/15
 *		   fix prd table bug 2001/09/12 (7.1)
 *
 * atp885 support add by ACARD Hao Ping Lian 2005/01/05
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/पन.स>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>

#समावेश "atp870u.h"

अटल काष्ठा scsi_host_ढाँचा atp870u_ढाँचा;
अटल व्योम send_s870(काष्ठा atp_unit *dev,अचिन्हित अक्षर c);
अटल व्योम atp_is(काष्ठा atp_unit *dev, अचिन्हित अक्षर c, bool wide_chip,
		   अचिन्हित अक्षर lvdmode);

अटल अंतरभूत व्योम atp_ग_लिखोb_base(काष्ठा atp_unit *atp, u8 reg, u8 val)
अणु
	outb(val, atp->baseport + reg);
पूर्ण

अटल अंतरभूत व्योम atp_ग_लिखोw_base(काष्ठा atp_unit *atp, u8 reg, u16 val)
अणु
	outw(val, atp->baseport + reg);
पूर्ण

अटल अंतरभूत व्योम atp_ग_लिखोb_io(काष्ठा atp_unit *atp, u8 channel, u8 reg, u8 val)
अणु
	outb(val, atp->ioport[channel] + reg);
पूर्ण

अटल अंतरभूत व्योम atp_ग_लिखोw_io(काष्ठा atp_unit *atp, u8 channel, u8 reg, u16 val)
अणु
	outw(val, atp->ioport[channel] + reg);
पूर्ण

अटल अंतरभूत व्योम atp_ग_लिखोb_pci(काष्ठा atp_unit *atp, u8 channel, u8 reg, u8 val)
अणु
	outb(val, atp->pciport[channel] + reg);
पूर्ण

अटल अंतरभूत व्योम atp_ग_लिखोl_pci(काष्ठा atp_unit *atp, u8 channel, u8 reg, u32 val)
अणु
	outl(val, atp->pciport[channel] + reg);
पूर्ण

अटल अंतरभूत u8 atp_पढ़ोb_base(काष्ठा atp_unit *atp, u8 reg)
अणु
	वापस inb(atp->baseport + reg);
पूर्ण

अटल अंतरभूत u16 atp_पढ़ोw_base(काष्ठा atp_unit *atp, u8 reg)
अणु
	वापस inw(atp->baseport + reg);
पूर्ण

अटल अंतरभूत u32 atp_पढ़ोl_base(काष्ठा atp_unit *atp, u8 reg)
अणु
	वापस inl(atp->baseport + reg);
पूर्ण

अटल अंतरभूत u8 atp_पढ़ोb_io(काष्ठा atp_unit *atp, u8 channel, u8 reg)
अणु
	वापस inb(atp->ioport[channel] + reg);
पूर्ण

अटल अंतरभूत u16 atp_पढ़ोw_io(काष्ठा atp_unit *atp, u8 channel, u8 reg)
अणु
	वापस inw(atp->ioport[channel] + reg);
पूर्ण

अटल अंतरभूत u8 atp_पढ़ोb_pci(काष्ठा atp_unit *atp, u8 channel, u8 reg)
अणु
	वापस inb(atp->pciport[channel] + reg);
पूर्ण

अटल अंतरभूत bool is880(काष्ठा atp_unit *atp)
अणु
	वापस atp->pdev->device == ATP880_DEVID1 ||
	       atp->pdev->device == ATP880_DEVID2;
पूर्ण

अटल अंतरभूत bool is885(काष्ठा atp_unit *atp)
अणु
	वापस atp->pdev->device == ATP885_DEVID;
पूर्ण

अटल irqवापस_t atp870u_पूर्णांकr_handle(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु पूर्णांक id;
	अचिन्हित अक्षर i, j, c, target_id, lun,cmdp;
	अचिन्हित अक्षर *prd;
	काष्ठा scsi_cmnd *workreq;
	अचिन्हित दीर्घ adrcnt, k;
#अगर_घोषित ED_DBGP
	अचिन्हित दीर्घ l;
#पूर्ण_अगर
	काष्ठा Scsi_Host *host = dev_id;
	काष्ठा atp_unit *dev = (काष्ठा atp_unit *)&host->hostdata;

	क्रम (c = 0; c < 2; c++) अणु
		j = atp_पढ़ोb_io(dev, c, 0x1f);
		अगर ((j & 0x80) != 0)
			अवरोध;
		dev->in_पूर्णांक[c] = 0;
	पूर्ण
	अगर ((j & 0x80) == 0)
		वापस IRQ_NONE;
#अगर_घोषित ED_DBGP
	prपूर्णांकk("atp870u_intr_handle enter\n");
#पूर्ण_अगर
	dev->in_पूर्णांक[c] = 1;
	cmdp = atp_पढ़ोb_io(dev, c, 0x10);
	अगर (dev->working[c] != 0) अणु
		अगर (is885(dev)) अणु
			अगर ((atp_पढ़ोb_io(dev, c, 0x16) & 0x80) == 0)
				atp_ग_लिखोb_io(dev, c, 0x16,
					      (atp_पढ़ोb_io(dev, c, 0x16) | 0x80));
		पूर्ण
		अगर ((atp_पढ़ोb_pci(dev, c, 0x00) & 0x08) != 0)
		अणु
			क्रम (k=0; k < 1000; k++) अणु
				अगर ((atp_पढ़ोb_pci(dev, c, 2) & 0x08) == 0)
					अवरोध;
				अगर ((atp_पढ़ोb_pci(dev, c, 2) & 0x01) == 0)
					अवरोध;
			पूर्ण
		पूर्ण
		atp_ग_लिखोb_pci(dev, c, 0, 0x00);

		i = atp_पढ़ोb_io(dev, c, 0x17);

		अगर (is885(dev))
			atp_ग_लिखोb_pci(dev, c, 2, 0x06);

		target_id = atp_पढ़ोb_io(dev, c, 0x15);

		/*
		 *	Remap wide devices onto id numbers
		 */

		अगर ((target_id & 0x40) != 0) अणु
			target_id = (target_id & 0x07) | 0x08;
		पूर्ण अन्यथा अणु
			target_id &= 0x07;
		पूर्ण

		अगर ((j & 0x40) != 0) अणु
		     अगर (dev->last_cmd[c] == 0xff) अणु
			dev->last_cmd[c] = target_id;
		     पूर्ण
		     dev->last_cmd[c] |= 0x40;
		पूर्ण
		अगर (is885(dev))
			dev->r1f[c][target_id] |= j;
#अगर_घोषित ED_DBGP
		prपूर्णांकk("atp870u_intr_handle status = %x\n",i);
#पूर्ण_अगर
		अगर (i == 0x85) अणु
			अगर ((dev->last_cmd[c] & 0xf0) != 0x40) अणु
			   dev->last_cmd[c] = 0xff;
			पूर्ण
			अगर (is885(dev)) अणु
				adrcnt = 0;
				((अचिन्हित अक्षर *) &adrcnt)[2] =
					atp_पढ़ोb_io(dev, c, 0x12);
				((अचिन्हित अक्षर *) &adrcnt)[1] =
					atp_पढ़ोb_io(dev, c, 0x13);
				((अचिन्हित अक्षर *) &adrcnt)[0] =
					atp_पढ़ोb_io(dev, c, 0x14);
				अगर (dev->id[c][target_id].last_len != adrcnt) अणु
					k = dev->id[c][target_id].last_len;
					k -= adrcnt;
					dev->id[c][target_id].tran_len = k;
					dev->id[c][target_id].last_len = adrcnt;
				पूर्ण
#अगर_घोषित ED_DBGP
				prपूर्णांकk("dev->id[c][target_id].last_len = %d "
				       "dev->id[c][target_id].tran_len = %d\n",
				       dev->id[c][target_id].last_len,
				       dev->id[c][target_id].tran_len);
#पूर्ण_अगर
			पूर्ण

			/*
			 *      Flip wide
			 */
			अगर (dev->wide_id[c] != 0) अणु
				atp_ग_लिखोb_io(dev, c, 0x1b, 0x01);
				जबतक ((atp_पढ़ोb_io(dev, c, 0x1b) & 0x01) != 0x01)
					atp_ग_लिखोb_io(dev, c, 0x1b, 0x01);
			पूर्ण
			/*
			 *	Issue more commands
			 */
			spin_lock_irqsave(dev->host->host_lock, flags);
			अगर (((dev->quhd[c] != dev->quend[c]) ||
			     (dev->last_cmd[c] != 0xff)) &&
			    (dev->in_snd[c] == 0)) अणु
#अगर_घोषित ED_DBGP
				prपूर्णांकk("Call sent_s870\n");
#पूर्ण_अगर
				send_s870(dev,c);
			पूर्ण
			spin_unlock_irqrestore(dev->host->host_lock, flags);
			/*
			 *	Done
			 */
			dev->in_पूर्णांक[c] = 0;
#अगर_घोषित ED_DBGP
				prपूर्णांकk("Status 0x85 return\n");
#पूर्ण_अगर
			वापस IRQ_HANDLED;
		पूर्ण

		अगर (i == 0x40) अणु
		     dev->last_cmd[c] |= 0x40;
		     dev->in_पूर्णांक[c] = 0;
		     वापस IRQ_HANDLED;
		पूर्ण

		अगर (i == 0x21) अणु
			अगर ((dev->last_cmd[c] & 0xf0) != 0x40) अणु
			   dev->last_cmd[c] = 0xff;
			पूर्ण
			adrcnt = 0;
			((अचिन्हित अक्षर *) &adrcnt)[2] =
				atp_पढ़ोb_io(dev, c, 0x12);
			((अचिन्हित अक्षर *) &adrcnt)[1] =
				atp_पढ़ोb_io(dev, c, 0x13);
			((अचिन्हित अक्षर *) &adrcnt)[0] =
				atp_पढ़ोb_io(dev, c, 0x14);
			k = dev->id[c][target_id].last_len;
			k -= adrcnt;
			dev->id[c][target_id].tran_len = k;
			dev->id[c][target_id].last_len = adrcnt;
			atp_ग_लिखोb_io(dev, c, 0x10, 0x41);
			atp_ग_लिखोb_io(dev, c, 0x18, 0x08);
			dev->in_पूर्णांक[c] = 0;
			वापस IRQ_HANDLED;
		पूर्ण

		अगर (is885(dev)) अणु
			अगर ((i == 0x4c) || (i == 0x4d) || (i == 0x8c) || (i == 0x8d)) अणु
				अगर ((i == 0x4c) || (i == 0x8c))
					i=0x48;
				अन्यथा
					i=0x49;
			पूर्ण
		पूर्ण
		अगर ((i == 0x80) || (i == 0x8f)) अणु
#अगर_घोषित ED_DBGP
			prपूर्णांकk(KERN_DEBUG "Device reselect\n");
#पूर्ण_अगर
			lun = 0;
			अगर (cmdp == 0x44 || i == 0x80)
				lun = atp_पढ़ोb_io(dev, c, 0x1d) & 0x07;
			अन्यथा अणु
				अगर ((dev->last_cmd[c] & 0xf0) != 0x40) अणु
				   dev->last_cmd[c] = 0xff;
				पूर्ण
				अगर (cmdp == 0x41) अणु
#अगर_घोषित ED_DBGP
					prपूर्णांकk("cmdp = 0x41\n");
#पूर्ण_अगर
					adrcnt = 0;
					((अचिन्हित अक्षर *) &adrcnt)[2] =
						atp_पढ़ोb_io(dev, c, 0x12);
					((अचिन्हित अक्षर *) &adrcnt)[1] =
						atp_पढ़ोb_io(dev, c, 0x13);
					((अचिन्हित अक्षर *) &adrcnt)[0] =
						atp_पढ़ोb_io(dev, c, 0x14);
					k = dev->id[c][target_id].last_len;
					k -= adrcnt;
					dev->id[c][target_id].tran_len = k;
					dev->id[c][target_id].last_len = adrcnt;
					atp_ग_लिखोb_io(dev, c, 0x18, 0x08);
					dev->in_पूर्णांक[c] = 0;
					वापस IRQ_HANDLED;
				पूर्ण अन्यथा अणु
#अगर_घोषित ED_DBGP
					prपूर्णांकk("cmdp != 0x41\n");
#पूर्ण_अगर
					atp_ग_लिखोb_io(dev, c, 0x10, 0x46);
					dev->id[c][target_id].dirct = 0x00;
					atp_ग_लिखोb_io(dev, c, 0x12, 0x00);
					atp_ग_लिखोb_io(dev, c, 0x13, 0x00);
					atp_ग_लिखोb_io(dev, c, 0x14, 0x00);
					atp_ग_लिखोb_io(dev, c, 0x18, 0x08);
					dev->in_पूर्णांक[c] = 0;
					वापस IRQ_HANDLED;
				पूर्ण
			पूर्ण
			अगर (dev->last_cmd[c] != 0xff) अणु
			   dev->last_cmd[c] |= 0x40;
			पूर्ण
			अगर (is885(dev)) अणु
				j = atp_पढ़ोb_base(dev, 0x29) & 0xfe;
				atp_ग_लिखोb_base(dev, 0x29, j);
			पूर्ण अन्यथा
				atp_ग_लिखोb_io(dev, c, 0x10, 0x45);

			target_id = atp_पढ़ोb_io(dev, c, 0x16);
			/*
			 *	Remap wide identअगरiers
			 */
			अगर ((target_id & 0x10) != 0) अणु
				target_id = (target_id & 0x07) | 0x08;
			पूर्ण अन्यथा अणु
				target_id &= 0x07;
			पूर्ण
			अगर (is885(dev))
				atp_ग_लिखोb_io(dev, c, 0x10, 0x45);
			workreq = dev->id[c][target_id].curr_req;
#अगर_घोषित ED_DBGP
			scmd_prपूर्णांकk(KERN_DEBUG, workreq, "CDB");
			क्रम (l = 0; l < workreq->cmd_len; l++)
				prपूर्णांकk(KERN_DEBUG " %x",workreq->cmnd[l]);
			prपूर्णांकk("\n");
#पूर्ण_अगर

			atp_ग_लिखोb_io(dev, c, 0x0f, lun);
			atp_ग_लिखोb_io(dev, c, 0x11, dev->id[c][target_id].devsp);
			adrcnt = dev->id[c][target_id].tran_len;
			k = dev->id[c][target_id].last_len;

			atp_ग_लिखोb_io(dev, c, 0x12, ((अचिन्हित अक्षर *) &k)[2]);
			atp_ग_लिखोb_io(dev, c, 0x13, ((अचिन्हित अक्षर *) &k)[1]);
			atp_ग_लिखोb_io(dev, c, 0x14, ((अचिन्हित अक्षर *) &k)[0]);
#अगर_घोषित ED_DBGP
			prपूर्णांकk("k %x, k[0] 0x%x k[1] 0x%x k[2] 0x%x\n", k,
			       atp_पढ़ोb_io(dev, c, 0x14),
			       atp_पढ़ोb_io(dev, c, 0x13),
			       atp_पढ़ोb_io(dev, c, 0x12));
#पूर्ण_अगर
			/* Remap wide */
			j = target_id;
			अगर (target_id > 7) अणु
				j = (j & 0x07) | 0x40;
			पूर्ण
			/* Add direction */
			j |= dev->id[c][target_id].dirct;
			atp_ग_लिखोb_io(dev, c, 0x15, j);
			atp_ग_लिखोb_io(dev, c, 0x16, 0x80);

			/* enable 32 bit fअगरo transfer */
			अगर (is885(dev)) अणु
				i = atp_पढ़ोb_pci(dev, c, 1) & 0xf3;
				//j=workreq->cmnd[0];
				अगर ((workreq->cmnd[0] == READ_6) ||
				    (workreq->cmnd[0] == READ_10) ||
				    (workreq->cmnd[0] == WRITE_6) ||
				    (workreq->cmnd[0] == WRITE_10)) अणु
				   i |= 0x0c;
				पूर्ण
				atp_ग_लिखोb_pci(dev, c, 1, i);
			पूर्ण अन्यथा अगर (is880(dev)) अणु
				अगर ((workreq->cmnd[0] == READ_6) ||
				    (workreq->cmnd[0] == READ_10) ||
				    (workreq->cmnd[0] == WRITE_6) ||
				    (workreq->cmnd[0] == WRITE_10))
					atp_ग_लिखोb_base(dev, 0x3b,
							(atp_पढ़ोb_base(dev, 0x3b) & 0x3f) | 0xc0);
				अन्यथा
					atp_ग_लिखोb_base(dev, 0x3b,
							atp_पढ़ोb_base(dev, 0x3b) & 0x3f);
			पूर्ण अन्यथा अणु
				अगर ((workreq->cmnd[0] == READ_6) ||
				    (workreq->cmnd[0] == READ_10) ||
				    (workreq->cmnd[0] == WRITE_6) ||
				    (workreq->cmnd[0] == WRITE_10))
					atp_ग_लिखोb_base(dev, 0x3a,
							(atp_पढ़ोb_base(dev, 0x3a) & 0xf3) | 0x08);
				अन्यथा
					atp_ग_लिखोb_base(dev, 0x3a,
							atp_पढ़ोb_base(dev, 0x3a) & 0xf3);
			पूर्ण
			j = 0;
			id = 1;
			id = id << target_id;
			/*
			 *	Is this a wide device
			 */
			अगर ((id & dev->wide_id[c]) != 0) अणु
				j |= 0x01;
			पूर्ण
			atp_ग_लिखोb_io(dev, c, 0x1b, j);
			जबतक ((atp_पढ़ोb_io(dev, c, 0x1b) & 0x01) != j)
				atp_ग_लिखोb_io(dev, c, 0x1b, j);
			अगर (dev->id[c][target_id].last_len == 0) अणु
				atp_ग_लिखोb_io(dev, c, 0x18, 0x08);
				dev->in_पूर्णांक[c] = 0;
#अगर_घोषित ED_DBGP
				prपूर्णांकk("dev->id[c][target_id].last_len = 0\n");
#पूर्ण_अगर
				वापस IRQ_HANDLED;
			पूर्ण
#अगर_घोषित ED_DBGP
			prपूर्णांकk("target_id = %d adrcnt = %d\n",target_id,adrcnt);
#पूर्ण_अगर
			prd = dev->id[c][target_id].prd_pos;
			जबतक (adrcnt != 0) अणु
				id = ((अचिन्हित लघु पूर्णांक *)prd)[2];
				अगर (id == 0) अणु
					k = 0x10000;
				पूर्ण अन्यथा अणु
					k = id;
				पूर्ण
				अगर (k > adrcnt) अणु
					((अचिन्हित लघु पूर्णांक *)prd)[2] =
						(अचिन्हित लघु पूर्णांक)(k - adrcnt);
					((अचिन्हित दीर्घ *)prd)[0] += adrcnt;
					adrcnt = 0;
					dev->id[c][target_id].prd_pos = prd;
				पूर्ण अन्यथा अणु
					adrcnt -= k;
					dev->id[c][target_id].prdaddr += 0x08;
					prd += 0x08;
					अगर (adrcnt == 0) अणु
						dev->id[c][target_id].prd_pos = prd;
					पूर्ण
				पूर्ण
			पूर्ण
			atp_ग_लिखोl_pci(dev, c, 0x04, dev->id[c][target_id].prdaddr);
#अगर_घोषित ED_DBGP
			prपूर्णांकk("dev->id[%d][%d].prdaddr 0x%8x\n",
			       c, target_id, dev->id[c][target_id].prdaddr);
#पूर्ण_अगर
			अगर (!is885(dev)) अणु
				atp_ग_लिखोb_pci(dev, c, 2, 0x06);
				atp_ग_लिखोb_pci(dev, c, 2, 0x00);
			पूर्ण
			/*
			 *	Check transfer direction
			 */
			अगर (dev->id[c][target_id].dirct != 0) अणु
				atp_ग_लिखोb_io(dev, c, 0x18, 0x08);
				atp_ग_लिखोb_pci(dev, c, 0, 0x01);
				dev->in_पूर्णांक[c] = 0;
#अगर_घोषित ED_DBGP
				prपूर्णांकk("status 0x80 return dirct != 0\n");
#पूर्ण_अगर
				वापस IRQ_HANDLED;
			पूर्ण
			atp_ग_लिखोb_io(dev, c, 0x18, 0x08);
			atp_ग_लिखोb_pci(dev, c, 0, 0x09);
			dev->in_पूर्णांक[c] = 0;
#अगर_घोषित ED_DBGP
			prपूर्णांकk("status 0x80 return dirct = 0\n");
#पूर्ण_अगर
			वापस IRQ_HANDLED;
		पूर्ण

		/*
		 *	Current scsi request on this target
		 */

		workreq = dev->id[c][target_id].curr_req;

		अगर (i == 0x42 || i == 0x16) अणु
			अगर ((dev->last_cmd[c] & 0xf0) != 0x40) अणु
			   dev->last_cmd[c] = 0xff;
			पूर्ण
			अगर (i == 0x16) अणु
				workreq->result = atp_पढ़ोb_io(dev, c, 0x0f);
				अगर (((dev->r1f[c][target_id] & 0x10) != 0) && is885(dev)) अणु
					prपूर्णांकk(KERN_WARNING "AEC67162 CRC ERROR !\n");
					workreq->result = SAM_STAT_CHECK_CONDITION;
				पूर्ण
			पूर्ण अन्यथा
				workreq->result = SAM_STAT_CHECK_CONDITION;

			अगर (is885(dev)) अणु
				j = atp_पढ़ोb_base(dev, 0x29) | 0x01;
				atp_ग_लिखोb_base(dev, 0x29, j);
			पूर्ण
			/*
			 *	Complete the command
			 */
			scsi_dma_unmap(workreq);

			spin_lock_irqsave(dev->host->host_lock, flags);
			(*workreq->scsi_करोne) (workreq);
#अगर_घोषित ED_DBGP
			   prपूर्णांकk("workreq->scsi_done\n");
#पूर्ण_अगर
			/*
			 *	Clear it off the queue
			 */
			dev->id[c][target_id].curr_req = शून्य;
			dev->working[c]--;
			spin_unlock_irqrestore(dev->host->host_lock, flags);
			/*
			 *      Take it back wide
			 */
			अगर (dev->wide_id[c] != 0) अणु
				atp_ग_लिखोb_io(dev, c, 0x1b, 0x01);
				जबतक ((atp_पढ़ोb_io(dev, c, 0x1b) & 0x01) != 0x01)
					atp_ग_लिखोb_io(dev, c, 0x1b, 0x01);
			पूर्ण
			/*
			 *	If there is stuff to send and nothing going then send it
			 */
			spin_lock_irqsave(dev->host->host_lock, flags);
			अगर (((dev->last_cmd[c] != 0xff) ||
			     (dev->quhd[c] != dev->quend[c])) &&
			    (dev->in_snd[c] == 0)) अणु
#अगर_घोषित ED_DBGP
			   prपूर्णांकk("Call sent_s870(scsi_done)\n");
#पूर्ण_अगर
			   send_s870(dev,c);
			पूर्ण
			spin_unlock_irqrestore(dev->host->host_lock, flags);
			dev->in_पूर्णांक[c] = 0;
			वापस IRQ_HANDLED;
		पूर्ण
		अगर ((dev->last_cmd[c] & 0xf0) != 0x40) अणु
		   dev->last_cmd[c] = 0xff;
		पूर्ण
		अगर (i == 0x4f) अणु
			i = 0x89;
		पूर्ण
		i &= 0x0f;
		अगर (i == 0x09) अणु
			atp_ग_लिखोl_pci(dev, c, 4, dev->id[c][target_id].prdaddr);
			atp_ग_लिखोb_pci(dev, c, 2, 0x06);
			atp_ग_लिखोb_pci(dev, c, 2, 0x00);
			atp_ग_लिखोb_io(dev, c, 0x10, 0x41);
			अगर (is885(dev)) अणु
				k = dev->id[c][target_id].last_len;
				atp_ग_लिखोb_io(dev, c, 0x12,
					      ((अचिन्हित अक्षर *) (&k))[2]);
				atp_ग_लिखोb_io(dev, c, 0x13,
					      ((अचिन्हित अक्षर *) (&k))[1]);
				atp_ग_लिखोb_io(dev, c, 0x14,
					      ((अचिन्हित अक्षर *) (&k))[0]);
				dev->id[c][target_id].dirct = 0x00;
			पूर्ण अन्यथा अणु
				dev->id[c][target_id].dirct = 0x00;
			पूर्ण
			atp_ग_लिखोb_io(dev, c, 0x18, 0x08);
			atp_ग_लिखोb_pci(dev, c, 0, 0x09);
			dev->in_पूर्णांक[c] = 0;
			वापस IRQ_HANDLED;
		पूर्ण
		अगर (i == 0x08) अणु
			atp_ग_लिखोl_pci(dev, c, 4, dev->id[c][target_id].prdaddr);
			atp_ग_लिखोb_pci(dev, c, 2, 0x06);
			atp_ग_लिखोb_pci(dev, c, 2, 0x00);
			atp_ग_लिखोb_io(dev, c, 0x10, 0x41);
			अगर (is885(dev)) अणु
				k = dev->id[c][target_id].last_len;
				atp_ग_लिखोb_io(dev, c, 0x12,
					      ((अचिन्हित अक्षर *) (&k))[2]);
				atp_ग_लिखोb_io(dev, c, 0x13,
					      ((अचिन्हित अक्षर *) (&k))[1]);
				atp_ग_लिखोb_io(dev, c, 0x14,
					      ((अचिन्हित अक्षर *) (&k))[0]);
			पूर्ण
			atp_ग_लिखोb_io(dev, c, 0x15,
				      atp_पढ़ोb_io(dev, c, 0x15) | 0x20);
			dev->id[c][target_id].dirct = 0x20;
			atp_ग_लिखोb_io(dev, c, 0x18, 0x08);
			atp_ग_लिखोb_pci(dev, c, 0, 0x01);
			dev->in_पूर्णांक[c] = 0;
			वापस IRQ_HANDLED;
		पूर्ण
		अगर (i == 0x0a)
			atp_ग_लिखोb_io(dev, c, 0x10, 0x30);
		अन्यथा
			atp_ग_लिखोb_io(dev, c, 0x10, 0x46);
		dev->id[c][target_id].dirct = 0x00;
		atp_ग_लिखोb_io(dev, c, 0x12, 0x00);
		atp_ग_लिखोb_io(dev, c, 0x13, 0x00);
		atp_ग_लिखोb_io(dev, c, 0x14, 0x00);
		atp_ग_लिखोb_io(dev, c, 0x18, 0x08);
	पूर्ण
	dev->in_पूर्णांक[c] = 0;

	वापस IRQ_HANDLED;
पूर्ण
/**
 *	atp870u_queuecommand_lck -	Queue SCSI command
 *	@req_p: request block
 *	@करोne: completion function
 *
 *	Queue a command to the ATP queue. Called with the host lock held.
 */
अटल पूर्णांक atp870u_queuecommand_lck(काष्ठा scsi_cmnd *req_p,
			 व्योम (*करोne) (काष्ठा scsi_cmnd *))
अणु
	अचिन्हित अक्षर c;
	अचिन्हित पूर्णांक m;
	काष्ठा atp_unit *dev;
	काष्ठा Scsi_Host *host;

	c = scmd_channel(req_p);
	req_p->sense_buffer[0]=0;
	scsi_set_resid(req_p, 0);
	अगर (scmd_channel(req_p) > 1) अणु
		req_p->result = DID_BAD_TARGET << 16;
		करोne(req_p);
#अगर_घोषित ED_DBGP
		prपूर्णांकk("atp870u_queuecommand : req_p->device->channel > 1\n");
#पूर्ण_अगर
		वापस 0;
	पूर्ण

	host = req_p->device->host;
	dev = (काष्ठा atp_unit *)&host->hostdata;

	m = 1;
	m = m << scmd_id(req_p);

	/*
	 *      Fake a समयout क्रम missing tarमाला_लो
	 */

	अगर ((m & dev->active_id[c]) == 0) अणु
		req_p->result = DID_BAD_TARGET << 16;
		करोne(req_p);
		वापस 0;
	पूर्ण

	अगर (करोne) अणु
		req_p->scsi_करोne = करोne;
	पूर्ण अन्यथा अणु
#अगर_घोषित ED_DBGP
		prपूर्णांकk( "atp870u_queuecommand: done can't be NULL\n");
#पूर्ण_अगर
		req_p->result = 0;
		करोne(req_p);
		वापस 0;
	पूर्ण

	/*
	 *	Count new command
	 */
	dev->quend[c]++;
	अगर (dev->quend[c] >= qcnt) अणु
		dev->quend[c] = 0;
	पूर्ण

	/*
	 *	Check queue state
	 */
	अगर (dev->quhd[c] == dev->quend[c]) अणु
		अगर (dev->quend[c] == 0) अणु
			dev->quend[c] = qcnt;
		पूर्ण
#अगर_घोषित ED_DBGP
		prपूर्णांकk("atp870u_queuecommand : dev->quhd[c] == dev->quend[c]\n");
#पूर्ण_अगर
		dev->quend[c]--;
		req_p->result = DID_BUS_BUSY << 16;
		करोne(req_p);
		वापस 0;
	पूर्ण
	dev->quereq[c][dev->quend[c]] = req_p;
#अगर_घोषित ED_DBGP
	prपूर्णांकk("dev->ioport[c] = %x atp_readb_io(dev, c, 0x1c) = %x "
	       "dev->in_int[%d] = %d dev->in_snd[%d] = %d\n",
	       dev->ioport[c], atp_पढ़ोb_io(dev, c, 0x1c), c,
	       dev->in_पूर्णांक[c],c,dev->in_snd[c]);
#पूर्ण_अगर
	अगर ((atp_पढ़ोb_io(dev, c, 0x1c) == 0) &&
	    (dev->in_पूर्णांक[c] == 0) &&
	    (dev->in_snd[c] == 0)) अणु
#अगर_घोषित ED_DBGP
		prपूर्णांकk("Call sent_s870(atp870u_queuecommand)\n");
#पूर्ण_अगर
		send_s870(dev,c);
	पूर्ण
#अगर_घोषित ED_DBGP
	prपूर्णांकk("atp870u_queuecommand : exit\n");
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(atp870u_queuecommand)

/*
 *	send_s870	-	send a command to the controller
 *
 *	On entry there is work queued to be करोne. We move some of that work to the
 *	controller itself.
 *
 *	Caller holds the host lock.
 */
अटल व्योम send_s870(काष्ठा atp_unit *dev, अचिन्हित अक्षर c)
अणु
	काष्ठा scsi_cmnd *workreq = शून्य;
	अचिन्हित पूर्णांक i;//,k;
	अचिन्हित अक्षर  j, target_id;
	अचिन्हित अक्षर *prd;
	अचिन्हित लघु पूर्णांक w;
	अचिन्हित दीर्घ l, bttl = 0;
	अचिन्हित दीर्घ  sg_count;

	अगर (dev->in_snd[c] != 0) अणु
#अगर_घोषित ED_DBGP
		prपूर्णांकk("cmnd in_snd\n");
#पूर्ण_अगर
		वापस;
	पूर्ण
#अगर_घोषित ED_DBGP
	prपूर्णांकk("Sent_s870 enter\n");
#पूर्ण_अगर
	dev->in_snd[c] = 1;
	अगर ((dev->last_cmd[c] != 0xff) && ((dev->last_cmd[c] & 0x40) != 0)) अणु
		dev->last_cmd[c] &= 0x0f;
		workreq = dev->id[c][dev->last_cmd[c]].curr_req;
		अगर (!workreq) अणु
			dev->last_cmd[c] = 0xff;
			अगर (dev->quhd[c] == dev->quend[c]) अणु
				dev->in_snd[c] = 0;
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!workreq) अणु
		अगर ((dev->last_cmd[c] != 0xff) && (dev->working[c] != 0)) अणु
			dev->in_snd[c] = 0;
			वापस;
		पूर्ण
		dev->working[c]++;
		j = dev->quhd[c];
		dev->quhd[c]++;
		अगर (dev->quhd[c] >= qcnt)
			dev->quhd[c] = 0;
		workreq = dev->quereq[c][dev->quhd[c]];
		अगर (dev->id[c][scmd_id(workreq)].curr_req != शून्य) अणु
			dev->quhd[c] = j;
			dev->working[c]--;
			dev->in_snd[c] = 0;
			वापस;
		पूर्ण
		dev->id[c][scmd_id(workreq)].curr_req = workreq;
		dev->last_cmd[c] = scmd_id(workreq);
	पूर्ण
	अगर ((atp_पढ़ोb_io(dev, c, 0x1f) & 0xb0) != 0 ||
	    atp_पढ़ोb_io(dev, c, 0x1c) != 0) अणु
#अगर_घोषित ED_DBGP
		prपूर्णांकk("Abort to Send\n");
#पूर्ण_अगर
		dev->last_cmd[c] |= 0x40;
		dev->in_snd[c] = 0;
		वापस;
	पूर्ण
#अगर_घोषित ED_DBGP
	prपूर्णांकk("OK to Send\n");
	scmd_prपूर्णांकk(KERN_DEBUG, workreq, "CDB");
	क्रम(i=0;i<workreq->cmd_len;i++) अणु
		prपूर्णांकk(" %x",workreq->cmnd[i]);
	पूर्ण
	prपूर्णांकk("\n");
#पूर्ण_अगर
	l = scsi_bufflen(workreq);

	अगर (is885(dev)) अणु
		j = atp_पढ़ोb_base(dev, 0x29) & 0xfe;
		atp_ग_लिखोb_base(dev, 0x29, j);
		dev->r1f[c][scmd_id(workreq)] = 0;
	पूर्ण

	अगर (workreq->cmnd[0] == READ_CAPACITY) अणु
		अगर (l > 8)
			l = 8;
	पूर्ण
	अगर (workreq->cmnd[0] == TEST_UNIT_READY) अणु
		l = 0;
	पूर्ण

	j = 0;
	target_id = scmd_id(workreq);

	/*
	 *	Wide ?
	 */
	w = 1;
	w = w << target_id;
	अगर ((w & dev->wide_id[c]) != 0) अणु
		j |= 0x01;
	पूर्ण
	atp_ग_लिखोb_io(dev, c, 0x1b, j);
	जबतक ((atp_पढ़ोb_io(dev, c, 0x1b) & 0x01) != j) अणु
		atp_ग_लिखोb_pci(dev, c, 0x1b, j);
#अगर_घोषित ED_DBGP
		prपूर्णांकk("send_s870 while loop 1\n");
#पूर्ण_अगर
	पूर्ण
	/*
	 *	Write the command
	 */

	atp_ग_लिखोb_io(dev, c, 0x00, workreq->cmd_len);
	atp_ग_लिखोb_io(dev, c, 0x01, 0x2c);
	अगर (is885(dev))
		atp_ग_लिखोb_io(dev, c, 0x02, 0x7f);
	अन्यथा
		atp_ग_लिखोb_io(dev, c, 0x02, 0xcf);
	क्रम (i = 0; i < workreq->cmd_len; i++)
		atp_ग_लिखोb_io(dev, c, 0x03 + i, workreq->cmnd[i]);
	atp_ग_लिखोb_io(dev, c, 0x0f, workreq->device->lun);
	/*
	 *	Write the target
	 */
	atp_ग_लिखोb_io(dev, c, 0x11, dev->id[c][target_id].devsp);
#अगर_घोषित ED_DBGP
	prपूर्णांकk("dev->id[%d][%d].devsp = %2x\n",c,target_id,
	       dev->id[c][target_id].devsp);
#पूर्ण_अगर

	sg_count = scsi_dma_map(workreq);
	/*
	 *	Write transfer size
	 */
	atp_ग_लिखोb_io(dev, c, 0x12, ((अचिन्हित अक्षर *) (&l))[2]);
	atp_ग_लिखोb_io(dev, c, 0x13, ((अचिन्हित अक्षर *) (&l))[1]);
	atp_ग_लिखोb_io(dev, c, 0x14, ((अचिन्हित अक्षर *) (&l))[0]);
	j = target_id;
	dev->id[c][j].last_len = l;
	dev->id[c][j].tran_len = 0;
#अगर_घोषित ED_DBGP
	prपूर्णांकk("dev->id[%2d][%2d].last_len = %d\n",c,j,dev->id[c][j].last_len);
#पूर्ण_अगर
	/*
	 *	Flip the wide bits
	 */
	अगर ((j & 0x08) != 0) अणु
		j = (j & 0x07) | 0x40;
	पूर्ण
	/*
	 *	Check transfer direction
	 */
	अगर (workreq->sc_data_direction == DMA_TO_DEVICE)
		atp_ग_लिखोb_io(dev, c, 0x15, j | 0x20);
	अन्यथा
		atp_ग_लिखोb_io(dev, c, 0x15, j);
	atp_ग_लिखोb_io(dev, c, 0x16, atp_पढ़ोb_io(dev, c, 0x16) | 0x80);
	atp_ग_लिखोb_io(dev, c, 0x16, 0x80);
	dev->id[c][target_id].dirct = 0;
	अगर (l == 0) अणु
		अगर (atp_पढ़ोb_io(dev, c, 0x1c) == 0) अणु
#अगर_घोषित ED_DBGP
			prपूर्णांकk("change SCSI_CMD_REG 0x08\n");
#पूर्ण_अगर
			atp_ग_लिखोb_io(dev, c, 0x18, 0x08);
		पूर्ण अन्यथा
			dev->last_cmd[c] |= 0x40;
		dev->in_snd[c] = 0;
		वापस;
	पूर्ण
	prd = dev->id[c][target_id].prd_table;
	dev->id[c][target_id].prd_pos = prd;

	/*
	 *	Now ग_लिखो the request list. Either as scatter/gather or as
	 *	a linear chain.
	 */

	अगर (l) अणु
		काष्ठा scatterlist *sgpnt;
		i = 0;
		scsi_क्रम_each_sg(workreq, sgpnt, sg_count, j) अणु
			bttl = sg_dma_address(sgpnt);
			l=sg_dma_len(sgpnt);
#अगर_घोषित ED_DBGP
			prपूर्णांकk("1. bttl %x, l %x\n",bttl, l);
#पूर्ण_अगर
			जबतक (l > 0x10000) अणु
				(((u16 *) (prd))[i + 3]) = 0x0000;
				(((u16 *) (prd))[i + 2]) = 0x0000;
				(((u32 *) (prd))[i >> 1]) = cpu_to_le32(bttl);
				l -= 0x10000;
				bttl += 0x10000;
				i += 0x04;
			पूर्ण
			(((u32 *) (prd))[i >> 1]) = cpu_to_le32(bttl);
			(((u16 *) (prd))[i + 2]) = cpu_to_le16(l);
			(((u16 *) (prd))[i + 3]) = 0;
			i += 0x04;
		पूर्ण
		(((u16 *) (prd))[i - 1]) = cpu_to_le16(0x8000);
#अगर_घोषित ED_DBGP
		prपूर्णांकk("prd %4x %4x %4x %4x\n",
		       (((अचिन्हित लघु पूर्णांक *)prd)[0]),
		       (((अचिन्हित लघु पूर्णांक *)prd)[1]),
		       (((अचिन्हित लघु पूर्णांक *)prd)[2]),
		       (((अचिन्हित लघु पूर्णांक *)prd)[3]));
		prपूर्णांकk("2. bttl %x, l %x\n",bttl, l);
#पूर्ण_अगर
	पूर्ण
#अगर_घोषित ED_DBGP
	prपूर्णांकk("send_s870: prdaddr_2 0x%8x target_id %d\n",
	       dev->id[c][target_id].prdaddr,target_id);
#पूर्ण_अगर
	dev->id[c][target_id].prdaddr = dev->id[c][target_id].prd_bus;
	atp_ग_लिखोl_pci(dev, c, 4, dev->id[c][target_id].prdaddr);
	atp_ग_लिखोb_pci(dev, c, 2, 0x06);
	atp_ग_लिखोb_pci(dev, c, 2, 0x00);
	अगर (is885(dev)) अणु
		j = atp_पढ़ोb_pci(dev, c, 1) & 0xf3;
		अगर ((workreq->cmnd[0] == READ_6) ||
		    (workreq->cmnd[0] == READ_10) ||
		    (workreq->cmnd[0] == WRITE_6) ||
		    (workreq->cmnd[0] == WRITE_10)) अणु
			j |= 0x0c;
		पूर्ण
		atp_ग_लिखोb_pci(dev, c, 1, j);
	पूर्ण अन्यथा अगर (is880(dev)) अणु
		अगर ((workreq->cmnd[0] == READ_6) ||
		    (workreq->cmnd[0] == READ_10) ||
		    (workreq->cmnd[0] == WRITE_6) ||
		    (workreq->cmnd[0] == WRITE_10))
			atp_ग_लिखोb_base(dev, 0x3b,
					(atp_पढ़ोb_base(dev, 0x3b) & 0x3f) | 0xc0);
		अन्यथा
			atp_ग_लिखोb_base(dev, 0x3b,
					atp_पढ़ोb_base(dev, 0x3b) & 0x3f);
	पूर्ण अन्यथा अणु
		अगर ((workreq->cmnd[0] == READ_6) ||
		    (workreq->cmnd[0] == READ_10) ||
		    (workreq->cmnd[0] == WRITE_6) ||
		    (workreq->cmnd[0] == WRITE_10))
			atp_ग_लिखोb_base(dev, 0x3a,
					(atp_पढ़ोb_base(dev, 0x3a) & 0xf3) | 0x08);
		अन्यथा
			atp_ग_लिखोb_base(dev, 0x3a,
					atp_पढ़ोb_base(dev, 0x3a) & 0xf3);
	पूर्ण

	अगर(workreq->sc_data_direction == DMA_TO_DEVICE) अणु
		dev->id[c][target_id].dirct = 0x20;
		अगर (atp_पढ़ोb_io(dev, c, 0x1c) == 0) अणु
			atp_ग_लिखोb_io(dev, c, 0x18, 0x08);
			atp_ग_लिखोb_pci(dev, c, 0, 0x01);
#अगर_घोषित ED_DBGP
		prपूर्णांकk( "start DMA(to target)\n");
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			dev->last_cmd[c] |= 0x40;
		पूर्ण
		dev->in_snd[c] = 0;
		वापस;
	पूर्ण
	अगर (atp_पढ़ोb_io(dev, c, 0x1c) == 0) अणु
		atp_ग_लिखोb_io(dev, c, 0x18, 0x08);
		atp_ग_लिखोb_pci(dev, c, 0, 0x09);
#अगर_घोषित ED_DBGP
		prपूर्णांकk( "start DMA(to host)\n");
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		dev->last_cmd[c] |= 0x40;
	पूर्ण
	dev->in_snd[c] = 0;
	वापस;

पूर्ण

अटल अचिन्हित अक्षर fun_scam(काष्ठा atp_unit *dev, अचिन्हित लघु पूर्णांक *val)
अणु
	अचिन्हित लघु पूर्णांक i, k;
	अचिन्हित अक्षर j;

	atp_ग_लिखोw_io(dev, 0, 0x1c, *val);
	क्रम (i = 0; i < 10; i++) अणु	/* stable >= bus settle delay(400 ns)  */
		k = atp_पढ़ोw_io(dev, 0, 0x1c);
		j = (अचिन्हित अक्षर) (k >> 8);
		अगर ((k & 0x8000) != 0)	/* DB7 all release?    */
			i = 0;
	पूर्ण
	*val |= 0x4000;		/* निश्चित DB6           */
	atp_ग_लिखोw_io(dev, 0, 0x1c, *val);
	*val &= 0xdfff;		/* निश्चित DB5           */
	atp_ग_लिखोw_io(dev, 0, 0x1c, *val);
	क्रम (i = 0; i < 10; i++) अणु	/* stable >= bus settle delay(400 ns) */
		अगर ((atp_पढ़ोw_io(dev, 0, 0x1c) & 0x2000) != 0)	/* DB5 all release?       */
			i = 0;
	पूर्ण
	*val |= 0x8000;		/* no DB4-0, निश्चित DB7    */
	*val &= 0xe0ff;
	atp_ग_लिखोw_io(dev, 0, 0x1c, *val);
	*val &= 0xbfff;		/* release DB6             */
	atp_ग_लिखोw_io(dev, 0, 0x1c, *val);
	क्रम (i = 0; i < 10; i++) अणु	/* stable >= bus settle delay(400 ns)  */
		अगर ((atp_पढ़ोw_io(dev, 0, 0x1c) & 0x4000) != 0)	/* DB6 all release?  */
			i = 0;
	पूर्ण

	वापस j;
पूर्ण

अटल व्योम tscam(काष्ठा Scsi_Host *host, bool wide_chip, u8 scam_on)
अणु

	अचिन्हित अक्षर i, j, k;
	अचिन्हित दीर्घ n;
	अचिन्हित लघु पूर्णांक m, assignid_map, val;
	अचिन्हित अक्षर mbuf[33], quपूर्णांकet[2];
	काष्ठा atp_unit *dev = (काष्ठा atp_unit *)&host->hostdata;
	अटल अचिन्हित अक्षर g2q_tab[8] = अणु
		0x38, 0x31, 0x32, 0x2b, 0x34, 0x2d, 0x2e, 0x27
	पूर्ण;

/*  I can't believe we need this before we've even करोne anything.  Remove it
 *  and see अगर anyone bitches.
	क्रम (i = 0; i < 0x10; i++) अणु
		udelay(0xffff);
	पूर्ण
 */

	atp_ग_लिखोb_io(dev, 0, 1, 0x08);
	atp_ग_लिखोb_io(dev, 0, 2, 0x7f);
	atp_ग_लिखोb_io(dev, 0, 0x11, 0x20);

	अगर ((scam_on & 0x40) == 0) अणु
		वापस;
	पूर्ण
	m = 1;
	m <<= dev->host_id[0];
	j = 16;
	अगर (!wide_chip) अणु
		m |= 0xff00;
		j = 8;
	पूर्ण
	assignid_map = m;
	atp_ग_लिखोb_io(dev, 0, 0x02, 0x02);	/* 2*2=4ms,3EH 2/32*3E=3.9ms */
	atp_ग_लिखोb_io(dev, 0, 0x03, 0);
	atp_ग_लिखोb_io(dev, 0, 0x04, 0);
	atp_ग_लिखोb_io(dev, 0, 0x05, 0);
	atp_ग_लिखोb_io(dev, 0, 0x06, 0);
	atp_ग_लिखोb_io(dev, 0, 0x07, 0);
	atp_ग_लिखोb_io(dev, 0, 0x08, 0);

	क्रम (i = 0; i < j; i++) अणु
		m = 1;
		m = m << i;
		अगर ((m & assignid_map) != 0) अणु
			जारी;
		पूर्ण
		atp_ग_लिखोb_io(dev, 0, 0x0f, 0);
		atp_ग_लिखोb_io(dev, 0, 0x12, 0);
		atp_ग_लिखोb_io(dev, 0, 0x13, 0);
		atp_ग_लिखोb_io(dev, 0, 0x14, 0);
		अगर (i > 7) अणु
			k = (i & 0x07) | 0x40;
		पूर्ण अन्यथा अणु
			k = i;
		पूर्ण
		atp_ग_लिखोb_io(dev, 0, 0x15, k);
		अगर (wide_chip)
			atp_ग_लिखोb_io(dev, 0, 0x1b, 0x01);
		अन्यथा
			atp_ग_लिखोb_io(dev, 0, 0x1b, 0x00);
		करो अणु
			atp_ग_लिखोb_io(dev, 0, 0x18, 0x09);

			जबतक ((atp_पढ़ोb_io(dev, 0, 0x1f) & 0x80) == 0x00)
				cpu_relax();
			k = atp_पढ़ोb_io(dev, 0, 0x17);
			अगर ((k == 0x85) || (k == 0x42))
				अवरोध;
			अगर (k != 0x16)
				atp_ग_लिखोb_io(dev, 0, 0x10, 0x41);
		पूर्ण जबतक (k != 0x16);
		अगर ((k == 0x85) || (k == 0x42))
			जारी;
		assignid_map |= m;

	पूर्ण
	atp_ग_लिखोb_io(dev, 0, 0x02, 0x7f);
	atp_ग_लिखोb_io(dev, 0, 0x1b, 0x02);

	udelay(2);

	val = 0x0080;		/* bsy  */
	atp_ग_लिखोw_io(dev, 0, 0x1c, val);
	val |= 0x0040;		/* sel  */
	atp_ग_लिखोw_io(dev, 0, 0x1c, val);
	val |= 0x0004;		/* msg  */
	atp_ग_लिखोw_io(dev, 0, 0x1c, val);
	udelay(2);		/* 2 deskew delay(45ns*2=90ns) */
	val &= 0x007f;		/* no bsy  */
	atp_ग_लिखोw_io(dev, 0, 0x1c, val);
	msleep(128);
	val &= 0x00fb;		/* after 1ms no msg */
	atp_ग_लिखोw_io(dev, 0, 0x1c, val);
	जबतक ((atp_पढ़ोb_io(dev, 0, 0x1c) & 0x04) != 0)
		;
	udelay(2);
	udelay(100);
	क्रम (n = 0; n < 0x30000; n++)
		अगर ((atp_पढ़ोb_io(dev, 0, 0x1c) & 0x80) != 0)	/* bsy ? */
			अवरोध;
	अगर (n < 0x30000)
		क्रम (n = 0; n < 0x30000; n++)
			अगर ((atp_पढ़ोb_io(dev, 0, 0x1c) & 0x81) == 0x0081) अणु
				udelay(2);
				val |= 0x8003;		/* io,cd,db7  */
				atp_ग_लिखोw_io(dev, 0, 0x1c, val);
				udelay(2);
				val &= 0x00bf;		/* no sel     */
				atp_ग_लिखोw_io(dev, 0, 0x1c, val);
				udelay(2);
				अवरोध;
			पूर्ण
	जबतक (1) अणु
	/*
	 * The funny भागision पूर्णांकo multiple delays is to accomodate
	 * arches like ARM where udelay() multiplies its argument by
	 * a large number to initialize a loop counter.  To aव्योम
	 * overflow, the maximum supported udelay is 2000 microseconds.
	 *
	 * XXX it would be more polite to find a way to use msleep()
	 */
	mdelay(2);
	udelay(48);
	अगर ((atp_पढ़ोb_io(dev, 0, 0x1c) & 0x80) == 0x00) अणु	/* bsy ? */
		atp_ग_लिखोw_io(dev, 0, 0x1c, 0);
		atp_ग_लिखोb_io(dev, 0, 0x1b, 0);
		atp_ग_लिखोb_io(dev, 0, 0x15, 0);
		atp_ग_लिखोb_io(dev, 0, 0x18, 0x09);
		जबतक ((atp_पढ़ोb_io(dev, 0, 0x1f) & 0x80) == 0)
			cpu_relax();
		atp_पढ़ोb_io(dev, 0, 0x17);
		वापस;
	पूर्ण
	val &= 0x00ff;		/* synchronization  */
	val |= 0x3f00;
	fun_scam(dev, &val);
	udelay(2);
	val &= 0x00ff;		/* isolation        */
	val |= 0x2000;
	fun_scam(dev, &val);
	udelay(2);
	i = 8;
	j = 0;

	जबतक (1) अणु
		अगर ((atp_पढ़ोw_io(dev, 0, 0x1c) & 0x2000) == 0)
			जारी;
		udelay(2);
		val &= 0x00ff;		/* get ID_STRING */
		val |= 0x2000;
		k = fun_scam(dev, &val);
		अगर ((k & 0x03) == 0)
			अवरोध;
		mbuf[j] <<= 0x01;
		mbuf[j] &= 0xfe;
		अगर ((k & 0x02) != 0)
			mbuf[j] |= 0x01;
		i--;
		अगर (i > 0)
			जारी;
		j++;
		i = 8;
	पूर्ण

	/* isolation complete..  */
/*    mbuf[32]=0;
	prपूर्णांकk(" \n%x %x %x %s\n ",assignid_map,mbuf[0],mbuf[1],&mbuf[2]); */
	i = 15;
	j = mbuf[0];
	अगर ((j & 0x20) != 0) अणु	/* bit5=1:ID up to 7      */
		i = 7;
	पूर्ण
	अगर ((j & 0x06) != 0) अणु	/* IDvalid?             */
		k = mbuf[1];
		जबतक (1) अणु
			m = 1;
			m <<= k;
			अगर ((m & assignid_map) == 0)
				अवरोध;
			अगर (k > 0)
				k--;
			अन्यथा
				अवरोध;
		पूर्ण
	पूर्ण
	अगर ((m & assignid_map) != 0) अणु	/* srch from max acceptable ID#  */
		k = i;			/* max acceptable ID#            */
		जबतक (1) अणु
			m = 1;
			m <<= k;
			अगर ((m & assignid_map) == 0)
				अवरोध;
			अगर (k > 0)
				k--;
			अन्यथा
				अवरोध;
		पूर्ण
	पूर्ण
	/* k=binID#,       */
	assignid_map |= m;
	अगर (k < 8) अणु
		quपूर्णांकet[0] = 0x38;	/* 1st dft ID<8    */
	पूर्ण अन्यथा अणु
		quपूर्णांकet[0] = 0x31;	/* 1st  ID>=8      */
	पूर्ण
	k &= 0x07;
	quपूर्णांकet[1] = g2q_tab[k];

	val &= 0x00ff;		/* AssignID 1stQuपूर्णांकet,AH=001xxxxx  */
	m = quपूर्णांकet[0] << 8;
	val |= m;
	fun_scam(dev, &val);
	val &= 0x00ff;		/* AssignID 2ndQuपूर्णांकet,AH=001xxxxx */
	m = quपूर्णांकet[1] << 8;
	val |= m;
	fun_scam(dev, &val);

	पूर्ण
पूर्ण

अटल व्योम atp870u_मुक्त_tables(काष्ठा Scsi_Host *host)
अणु
	काष्ठा atp_unit *atp_dev = (काष्ठा atp_unit *)&host->hostdata;
	पूर्णांक j, k;
	क्रम (j=0; j < 2; j++) अणु
		क्रम (k = 0; k < 16; k++) अणु
			अगर (!atp_dev->id[j][k].prd_table)
				जारी;
			dma_मुक्त_coherent(&atp_dev->pdev->dev, 1024,
					  atp_dev->id[j][k].prd_table,
					  atp_dev->id[j][k].prd_bus);
			atp_dev->id[j][k].prd_table = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक atp870u_init_tables(काष्ठा Scsi_Host *host)
अणु
	काष्ठा atp_unit *atp_dev = (काष्ठा atp_unit *)&host->hostdata;
	पूर्णांक c,k;
	क्रम(c=0;c < 2;c++) अणु
		क्रम(k=0;k<16;k++) अणु
			atp_dev->id[c][k].prd_table =
				dma_alloc_coherent(&atp_dev->pdev->dev, 1024,
						   &(atp_dev->id[c][k].prd_bus),
						   GFP_KERNEL);
			अगर (!atp_dev->id[c][k].prd_table) अणु
				prपूर्णांकk("atp870u_init_tables fail\n");
				atp870u_मुक्त_tables(host);
				वापस -ENOMEM;
			पूर्ण
			atp_dev->id[c][k].prdaddr = atp_dev->id[c][k].prd_bus;
			atp_dev->id[c][k].devsp=0x20;
			atp_dev->id[c][k].devtype = 0x7f;
			atp_dev->id[c][k].curr_req = शून्य;
		पूर्ण

		atp_dev->active_id[c] = 0;
		atp_dev->wide_id[c] = 0;
		atp_dev->host_id[c] = 0x07;
		atp_dev->quhd[c] = 0;
		atp_dev->quend[c] = 0;
		atp_dev->last_cmd[c] = 0xff;
		atp_dev->in_snd[c] = 0;
		atp_dev->in_पूर्णांक[c] = 0;

		क्रम (k = 0; k < qcnt; k++) अणु
			atp_dev->quereq[c][k] = शून्य;
		पूर्ण
		क्रम (k = 0; k < 16; k++) अणु
			   atp_dev->id[c][k].curr_req = शून्य;
			   atp_dev->sp[c][k] = 0x04;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम atp_set_host_id(काष्ठा atp_unit *atp, u8 c, u8 host_id)
अणु
	atp_ग_लिखोb_io(atp, c, 0, host_id | 0x08);
	atp_ग_लिखोb_io(atp, c, 0x18, 0);
	जबतक ((atp_पढ़ोb_io(atp, c, 0x1f) & 0x80) == 0)
		mdelay(1);
	atp_पढ़ोb_io(atp, c, 0x17);
	atp_ग_लिखोb_io(atp, c, 1, 8);
	atp_ग_लिखोb_io(atp, c, 2, 0x7f);
	atp_ग_लिखोb_io(atp, c, 0x11, 0x20);
पूर्ण

अटल व्योम atp870_init(काष्ठा Scsi_Host *shpnt)
अणु
	काष्ठा atp_unit *atpdev = shost_priv(shpnt);
	काष्ठा pci_dev *pdev = atpdev->pdev;
	अचिन्हित अक्षर k, host_id;
	u8 scam_on;
	bool wide_chip =
		(pdev->device == PCI_DEVICE_ID_ARTOP_AEC7610 &&
		 pdev->revision == 4) ||
		(pdev->device == PCI_DEVICE_ID_ARTOP_AEC7612UW) ||
		(pdev->device == PCI_DEVICE_ID_ARTOP_AEC7612SUW);

	pci_पढ़ो_config_byte(pdev, 0x49, &host_id);

	dev_info(&pdev->dev, "ACARD AEC-671X PCI Ultra/W SCSI-2/3 "
		 "Host Adapter: IO:%lx, IRQ:%d.\n",
		 shpnt->io_port, shpnt->irq);

	atpdev->ioport[0] = shpnt->io_port;
	atpdev->pciport[0] = shpnt->io_port + 0x20;
	host_id &= 0x07;
	atpdev->host_id[0] = host_id;
	scam_on = atp_पढ़ोb_pci(atpdev, 0, 2);
	atpdev->global_map[0] = atp_पढ़ोb_base(atpdev, 0x2d);
	atpdev->ultra_map[0] = atp_पढ़ोw_base(atpdev, 0x2e);

	अगर (atpdev->ultra_map[0] == 0) अणु
		scam_on = 0x00;
		atpdev->global_map[0] = 0x20;
		atpdev->ultra_map[0] = 0xffff;
	पूर्ण

	अगर (pdev->revision > 0x07)	/* check अगर atp876 chip */
		atp_ग_लिखोb_base(atpdev, 0x3e, 0x00); /* enable terminator */

	k = (atp_पढ़ोb_base(atpdev, 0x3a) & 0xf3) | 0x10;
	atp_ग_लिखोb_base(atpdev, 0x3a, k);
	atp_ग_लिखोb_base(atpdev, 0x3a, k & 0xdf);
	msleep(32);
	atp_ग_लिखोb_base(atpdev, 0x3a, k);
	msleep(32);
	atp_set_host_id(atpdev, 0, host_id);

	tscam(shpnt, wide_chip, scam_on);
	atp_ग_लिखोb_base(atpdev, 0x3a, atp_पढ़ोb_base(atpdev, 0x3a) | 0x10);
	atp_is(atpdev, 0, wide_chip, 0);
	atp_ग_लिखोb_base(atpdev, 0x3a, atp_पढ़ोb_base(atpdev, 0x3a) & 0xef);
	atp_ग_लिखोb_base(atpdev, 0x3b, atp_पढ़ोb_base(atpdev, 0x3b) | 0x20);
	shpnt->max_id = wide_chip ? 16 : 8;
	shpnt->this_id = host_id;
पूर्ण

अटल व्योम atp880_init(काष्ठा Scsi_Host *shpnt)
अणु
	काष्ठा atp_unit *atpdev = shost_priv(shpnt);
	काष्ठा pci_dev *pdev = atpdev->pdev;
	अचिन्हित अक्षर k, m, host_id;
	अचिन्हित पूर्णांक n;

	pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER, 0x80);

	atpdev->ioport[0] = shpnt->io_port + 0x40;
	atpdev->pciport[0] = shpnt->io_port + 0x28;

	host_id = atp_पढ़ोb_base(atpdev, 0x39) >> 4;

	dev_info(&pdev->dev, "ACARD AEC-67160 PCI Ultra3 LVD "
		 "Host Adapter: IO:%lx, IRQ:%d.\n",
		 shpnt->io_port, shpnt->irq);
	atpdev->host_id[0] = host_id;

	atpdev->global_map[0] = atp_पढ़ोb_base(atpdev, 0x35);
	atpdev->ultra_map[0] = atp_पढ़ोw_base(atpdev, 0x3c);

	n = 0x3f09;
	जबतक (n < 0x4000) अणु
		m = 0;
		atp_ग_लिखोw_base(atpdev, 0x34, n);
		n += 0x0002;
		अगर (atp_पढ़ोb_base(atpdev, 0x30) == 0xff)
			अवरोध;

		atpdev->sp[0][m++] = atp_पढ़ोb_base(atpdev, 0x30);
		atpdev->sp[0][m++] = atp_पढ़ोb_base(atpdev, 0x31);
		atpdev->sp[0][m++] = atp_पढ़ोb_base(atpdev, 0x32);
		atpdev->sp[0][m++] = atp_पढ़ोb_base(atpdev, 0x33);
		atp_ग_लिखोw_base(atpdev, 0x34, n);
		n += 0x0002;
		atpdev->sp[0][m++] = atp_पढ़ोb_base(atpdev, 0x30);
		atpdev->sp[0][m++] = atp_पढ़ोb_base(atpdev, 0x31);
		atpdev->sp[0][m++] = atp_पढ़ोb_base(atpdev, 0x32);
		atpdev->sp[0][m++] = atp_पढ़ोb_base(atpdev, 0x33);
		atp_ग_लिखोw_base(atpdev, 0x34, n);
		n += 0x0002;
		atpdev->sp[0][m++] = atp_पढ़ोb_base(atpdev, 0x30);
		atpdev->sp[0][m++] = atp_पढ़ोb_base(atpdev, 0x31);
		atpdev->sp[0][m++] = atp_पढ़ोb_base(atpdev, 0x32);
		atpdev->sp[0][m++] = atp_पढ़ोb_base(atpdev, 0x33);
		atp_ग_लिखोw_base(atpdev, 0x34, n);
		n += 0x0002;
		atpdev->sp[0][m++] = atp_पढ़ोb_base(atpdev, 0x30);
		atpdev->sp[0][m++] = atp_पढ़ोb_base(atpdev, 0x31);
		atpdev->sp[0][m++] = atp_पढ़ोb_base(atpdev, 0x32);
		atpdev->sp[0][m++] = atp_पढ़ोb_base(atpdev, 0x33);
		n += 0x0018;
	पूर्ण
	atp_ग_लिखोw_base(atpdev, 0x34, 0);
	atpdev->ultra_map[0] = 0;
	atpdev->async[0] = 0;
	क्रम (k = 0; k < 16; k++) अणु
		n = 1 << k;
		अगर (atpdev->sp[0][k] > 1)
			atpdev->ultra_map[0] |= n;
		अन्यथा
			अगर (atpdev->sp[0][k] == 0)
				atpdev->async[0] |= n;
	पूर्ण
	atpdev->async[0] = ~(atpdev->async[0]);
	atp_ग_लिखोb_base(atpdev, 0x35, atpdev->global_map[0]);

	k = atp_पढ़ोb_base(atpdev, 0x38) & 0x80;
	atp_ग_लिखोb_base(atpdev, 0x38, k);
	atp_ग_लिखोb_base(atpdev, 0x3b, 0x20);
	msleep(32);
	atp_ग_लिखोb_base(atpdev, 0x3b, 0);
	msleep(32);
	atp_पढ़ोb_io(atpdev, 0, 0x1b);
	atp_पढ़ोb_io(atpdev, 0, 0x17);

	atp_set_host_id(atpdev, 0, host_id);

	tscam(shpnt, true, atp_पढ़ोb_base(atpdev, 0x22));
	atp_is(atpdev, 0, true, atp_पढ़ोb_base(atpdev, 0x3f) & 0x40);
	atp_ग_लिखोb_base(atpdev, 0x38, 0xb0);
	shpnt->max_id = 16;
	shpnt->this_id = host_id;
पूर्ण

अटल व्योम atp885_init(काष्ठा Scsi_Host *shpnt)
अणु
	काष्ठा atp_unit *atpdev = shost_priv(shpnt);
	काष्ठा pci_dev *pdev = atpdev->pdev;
	अचिन्हित अक्षर k, m, c;
	अचिन्हित पूर्णांक n;
	अचिन्हित अक्षर setupdata[2][16];

	dev_info(&pdev->dev, "ACARD AEC-67162 PCI Ultra3 LVD "
		 "Host Adapter: IO:%lx, IRQ:%d.\n",
		 shpnt->io_port, shpnt->irq);

	atpdev->ioport[0] = shpnt->io_port + 0x80;
	atpdev->ioport[1] = shpnt->io_port + 0xc0;
	atpdev->pciport[0] = shpnt->io_port + 0x40;
	atpdev->pciport[1] = shpnt->io_port + 0x50;

	c = atp_पढ़ोb_base(atpdev, 0x29);
	atp_ग_लिखोb_base(atpdev, 0x29, c | 0x04);

	n = 0x1f80;
	जबतक (n < 0x2000) अणु
		atp_ग_लिखोw_base(atpdev, 0x3c, n);
		अगर (atp_पढ़ोl_base(atpdev, 0x38) == 0xffffffff)
			अवरोध;
		क्रम (m = 0; m < 2; m++) अणु
			atpdev->global_map[m] = 0;
			क्रम (k = 0; k < 4; k++) अणु
				atp_ग_लिखोw_base(atpdev, 0x3c, n++);
				((u32 *)&setupdata[m][0])[k] =
					atp_पढ़ोl_base(atpdev, 0x38);
			पूर्ण
			क्रम (k = 0; k < 4; k++) अणु
				atp_ग_लिखोw_base(atpdev, 0x3c, n++);
				((u32 *)&atpdev->sp[m][0])[k] =
					atp_पढ़ोl_base(atpdev, 0x38);
			पूर्ण
			n += 8;
		पूर्ण
	पूर्ण
	c = atp_पढ़ोb_base(atpdev, 0x29);
	atp_ग_लिखोb_base(atpdev, 0x29, c & 0xfb);
	क्रम (c = 0; c < 2; c++) अणु
		atpdev->ultra_map[c] = 0;
		atpdev->async[c] = 0;
		क्रम (k = 0; k < 16; k++) अणु
			n = 1 << k;
			अगर (atpdev->sp[c][k] > 1)
				atpdev->ultra_map[c] |= n;
			अन्यथा
				अगर (atpdev->sp[c][k] == 0)
					atpdev->async[c] |= n;
		पूर्ण
		atpdev->async[c] = ~(atpdev->async[c]);

		अगर (atpdev->global_map[c] == 0) अणु
			k = setupdata[c][1];
			अगर ((k & 0x40) != 0)
				atpdev->global_map[c] |= 0x20;
			k &= 0x07;
			atpdev->global_map[c] |= k;
			अगर ((setupdata[c][2] & 0x04) != 0)
				atpdev->global_map[c] |= 0x08;
			atpdev->host_id[c] = setupdata[c][0] & 0x07;
		पूर्ण
	पूर्ण

	k = atp_पढ़ोb_base(atpdev, 0x28) & 0x8f;
	k |= 0x10;
	atp_ग_लिखोb_base(atpdev, 0x28, k);
	atp_ग_लिखोb_pci(atpdev, 0, 1, 0x80);
	atp_ग_लिखोb_pci(atpdev, 1, 1, 0x80);
	msleep(100);
	atp_ग_लिखोb_pci(atpdev, 0, 1, 0);
	atp_ग_लिखोb_pci(atpdev, 1, 1, 0);
	msleep(1000);
	atp_पढ़ोb_io(atpdev, 0, 0x1b);
	atp_पढ़ोb_io(atpdev, 0, 0x17);
	atp_पढ़ोb_io(atpdev, 1, 0x1b);
	atp_पढ़ोb_io(atpdev, 1, 0x17);

	k = atpdev->host_id[0];
	अगर (k > 7)
		k = (k & 0x07) | 0x40;
	atp_set_host_id(atpdev, 0, k);

	k = atpdev->host_id[1];
	अगर (k > 7)
		k = (k & 0x07) | 0x40;
	atp_set_host_id(atpdev, 1, k);

	msleep(600); /* this delay used to be called tscam_885() */
	dev_info(&pdev->dev, "Scanning Channel A SCSI Device ...\n");
	atp_is(atpdev, 0, true, atp_पढ़ोb_io(atpdev, 0, 0x1b) >> 7);
	atp_ग_लिखोb_io(atpdev, 0, 0x16, 0x80);
	dev_info(&pdev->dev, "Scanning Channel B SCSI Device ...\n");
	atp_is(atpdev, 1, true, atp_पढ़ोb_io(atpdev, 1, 0x1b) >> 7);
	atp_ग_लिखोb_io(atpdev, 1, 0x16, 0x80);
	k = atp_पढ़ोb_base(atpdev, 0x28) & 0xcf;
	k |= 0xc0;
	atp_ग_लिखोb_base(atpdev, 0x28, k);
	k = atp_पढ़ोb_base(atpdev, 0x1f) | 0x80;
	atp_ग_लिखोb_base(atpdev, 0x1f, k);
	k = atp_पढ़ोb_base(atpdev, 0x29) | 0x01;
	atp_ग_लिखोb_base(atpdev, 0x29, k);
	shpnt->max_id = 16;
	shpnt->max_lun = (atpdev->global_map[0] & 0x07) + 1;
	shpnt->max_channel = 1;
	shpnt->this_id = atpdev->host_id[0];
पूर्ण

/* वापस non-zero on detection */
अटल पूर्णांक atp870u_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा Scsi_Host *shpnt = शून्य;
	काष्ठा atp_unit *atpdev;
	पूर्णांक err;

	अगर (ent->device == PCI_DEVICE_ID_ARTOP_AEC7610 && pdev->revision < 2) अणु
		dev_err(&pdev->dev, "ATP850S chips (AEC6710L/F cards) are not supported.\n");
		वापस -ENODEV;
	पूर्ण

	err = pci_enable_device(pdev);
	अगर (err)
		जाओ fail;

	अगर (dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) अणु
		prपूर्णांकk(KERN_ERR "atp870u: DMA mask required but not available.\n");
		err = -EIO;
		जाओ disable_device;
	पूर्ण

	err = pci_request_regions(pdev, "atp870u");
	अगर (err)
		जाओ disable_device;
	pci_set_master(pdev);

	err = -ENOMEM;
	shpnt = scsi_host_alloc(&atp870u_ढाँचा, माप(काष्ठा atp_unit));
	अगर (!shpnt)
		जाओ release_region;

	atpdev = shost_priv(shpnt);

	atpdev->host = shpnt;
	atpdev->pdev = pdev;
	pci_set_drvdata(pdev, atpdev);

	shpnt->io_port = pci_resource_start(pdev, 0);
	shpnt->io_port &= 0xfffffff8;
	shpnt->n_io_port = pci_resource_len(pdev, 0);
	atpdev->baseport = shpnt->io_port;
	shpnt->unique_id = shpnt->io_port;
	shpnt->irq = pdev->irq;

	err = atp870u_init_tables(shpnt);
	अगर (err) अणु
		dev_err(&pdev->dev, "Unable to allocate tables for Acard controller\n");
		जाओ unरेजिस्टर;
	पूर्ण

	अगर (is880(atpdev))
		atp880_init(shpnt);
	अन्यथा अगर (is885(atpdev))
		atp885_init(shpnt);
	अन्यथा
		atp870_init(shpnt);

	err = request_irq(shpnt->irq, atp870u_पूर्णांकr_handle, IRQF_SHARED, "atp870u", shpnt);
	अगर (err) अणु
		dev_err(&pdev->dev, "Unable to allocate IRQ %d.\n", shpnt->irq);
		जाओ मुक्त_tables;
	पूर्ण

	err = scsi_add_host(shpnt, &pdev->dev);
	अगर (err)
		जाओ scsi_add_fail;
	scsi_scan_host(shpnt);

	वापस 0;

scsi_add_fail:
	मुक्त_irq(shpnt->irq, shpnt);
मुक्त_tables:
	atp870u_मुक्त_tables(shpnt);
unरेजिस्टर:
	scsi_host_put(shpnt);
release_region:
	pci_release_regions(pdev);
disable_device:
	pci_disable_device(pdev);
fail:
	वापस err;
पूर्ण

/* The पात command करोes not leave the device in a clean state where
   it is available to be used again.  Until this माला_लो worked out, we will
   leave it commented out.  */

अटल पूर्णांक atp870u_पात(काष्ठा scsi_cmnd * SCpnt)
अणु
	अचिन्हित अक्षर  j, k, c;
	काष्ठा scsi_cmnd *workrequ;
	काष्ठा atp_unit *dev;
	काष्ठा Scsi_Host *host;
	host = SCpnt->device->host;

	dev = (काष्ठा atp_unit *)&host->hostdata;
	c = scmd_channel(SCpnt);
	prपूर्णांकk(" atp870u: abort Channel = %x \n", c);
	prपूर्णांकk("working=%x last_cmd=%x ", dev->working[c], dev->last_cmd[c]);
	prपूर्णांकk(" quhdu=%x quendu=%x ", dev->quhd[c], dev->quend[c]);
	क्रम (j = 0; j < 0x18; j++) अणु
		prपूर्णांकk(" r%2x=%2x", j, atp_पढ़ोb_io(dev, c, j));
	पूर्ण
	prपूर्णांकk(" r1c=%2x", atp_पढ़ोb_io(dev, c, 0x1c));
	prपूर्णांकk(" r1f=%2x in_snd=%2x ", atp_पढ़ोb_io(dev, c, 0x1f), dev->in_snd[c]);
	prपूर्णांकk(" d00=%2x", atp_पढ़ोb_pci(dev, c, 0x00));
	prपूर्णांकk(" d02=%2x", atp_पढ़ोb_pci(dev, c, 0x02));
	क्रम(j=0;j<16;j++) अणु
	   अगर (dev->id[c][j].curr_req != शून्य) अणु
		workrequ = dev->id[c][j].curr_req;
		prपूर्णांकk("\n que cdb= ");
		क्रम (k=0; k < workrequ->cmd_len; k++) अणु
		    prपूर्णांकk(" %2x ",workrequ->cmnd[k]);
		पूर्ण
		prपूर्णांकk(" last_lenu= %x ",(अचिन्हित पूर्णांक)dev->id[c][j].last_len);
	   पूर्ण
	पूर्ण
	वापस SUCCESS;
पूर्ण

अटल स्थिर अक्षर *atp870u_info(काष्ठा Scsi_Host *notused)
अणु
	अटल अक्षर buffer[128];

	म_नकल(buffer, "ACARD AEC-6710/6712/67160 PCI Ultra/W/LVD SCSI-3 Adapter Driver V2.6+ac ");

	वापस buffer;
पूर्ण

अटल पूर्णांक atp870u_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *HBAptr)
अणु
	seq_माला_दो(m, "ACARD AEC-671X Driver Version: 2.6+ac\n\n"
		"Adapter Configuration:\n");
	seq_म_लिखो(m, "               Base IO: %#.4lx\n", HBAptr->io_port);
	seq_म_लिखो(m, "                   IRQ: %d\n", HBAptr->irq);
	वापस 0;
पूर्ण


अटल पूर्णांक atp870u_biosparam(काष्ठा scsi_device *disk, काष्ठा block_device *dev,
			sector_t capacity, पूर्णांक *ip)
अणु
	पूर्णांक heads, sectors, cylinders;

	heads = 64;
	sectors = 32;
	cylinders = (अचिन्हित दीर्घ)capacity / (heads * sectors);
	अगर (cylinders > 1024) अणु
		heads = 255;
		sectors = 63;
		cylinders = (अचिन्हित दीर्घ)capacity / (heads * sectors);
	पूर्ण
	ip[0] = heads;
	ip[1] = sectors;
	ip[2] = cylinders;

	वापस 0;
पूर्ण

अटल व्योम atp870u_हटाओ (काष्ठा pci_dev *pdev)
अणु
	काष्ठा atp_unit *devext = pci_get_drvdata(pdev);
	काष्ठा Scsi_Host *pshost = devext->host;

	scsi_हटाओ_host(pshost);
	मुक्त_irq(pshost->irq, pshost);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	atp870u_मुक्त_tables(pshost);
	scsi_host_put(pshost);
पूर्ण
MODULE_LICENSE("GPL");

अटल काष्ठा scsi_host_ढाँचा atp870u_ढाँचा = अणु
     .module			= THIS_MODULE,
     .name			= "atp870u"		/* name */,
     .proc_name			= "atp870u",
     .show_info			= atp870u_show_info,
     .info			= atp870u_info		/* info */,
     .queuecommand		= atp870u_queuecommand	/* queuecommand */,
     .eh_पात_handler		= atp870u_पात		/* पात */,
     .bios_param		= atp870u_biosparam	/* biosparm */,
     .can_queue			= qcnt			/* can_queue */,
     .this_id			= 7			/* SCSI ID */,
     .sg_tablesize		= ATP870U_SCATTER	/*SG_ALL*/,
     .max_sectors		= ATP870U_MAX_SECTORS,
पूर्ण;

अटल काष्ठा pci_device_id atp870u_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_ARTOP, ATP885_DEVID)			  पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ARTOP, ATP880_DEVID1)		  पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ARTOP, ATP880_DEVID2)		  पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ARTOP, PCI_DEVICE_ID_ARTOP_AEC7610)    पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ARTOP, PCI_DEVICE_ID_ARTOP_AEC7612UW)  पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ARTOP, PCI_DEVICE_ID_ARTOP_AEC7612U)   पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ARTOP, PCI_DEVICE_ID_ARTOP_AEC7612S)   पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ARTOP, PCI_DEVICE_ID_ARTOP_AEC7612D)	  पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ARTOP, PCI_DEVICE_ID_ARTOP_AEC7612SUW) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ARTOP, PCI_DEVICE_ID_ARTOP_8060)	  पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, atp870u_id_table);

अटल काष्ठा pci_driver atp870u_driver = अणु
	.id_table	= atp870u_id_table,
	.name		= "atp870u",
	.probe		= atp870u_probe,
	.हटाओ		= atp870u_हटाओ,
पूर्ण;

module_pci_driver(atp870u_driver);

अटल व्योम atp_is(काष्ठा atp_unit *dev, अचिन्हित अक्षर c, bool wide_chip,
		   अचिन्हित अक्षर lvdmode)
अणु
	अचिन्हित अक्षर i, j, k, rmb, n;
	अचिन्हित लघु पूर्णांक m;
	अटल अचिन्हित अक्षर mbuf[512];
	अटल अचिन्हित अक्षर satn[9] = अणु 0, 0, 0, 0, 0, 0, 0, 6, 6 पूर्ण;
	अटल अचिन्हित अक्षर inqd[9] = अणु 0x12, 0, 0, 0, 0x24, 0, 0, 0x24, 6 पूर्ण;
	अटल अचिन्हित अक्षर synn[6] = अणु 0x80, 1, 3, 1, 0x19, 0x0e पूर्ण;
	अचिन्हित अक्षर synu[6] = अणु 0x80, 1, 3, 1, 0x0a, 0x0e पूर्ण;
	अटल अचिन्हित अक्षर synw[6] = अणु 0x80, 1, 3, 1, 0x19, 0x0e पूर्ण;
	अटल अचिन्हित अक्षर synw_870[6] = अणु 0x80, 1, 3, 1, 0x0c, 0x07 पूर्ण;
	अचिन्हित अक्षर synuw[6] = अणु 0x80, 1, 3, 1, 0x0a, 0x0e पूर्ण;
	अटल अचिन्हित अक्षर wide[6] = अणु 0x80, 1, 2, 3, 1, 0 पूर्ण;
	अटल अचिन्हित अक्षर u3[9] = अणु 0x80, 1, 6, 4, 0x09, 00, 0x0e, 0x01, 0x02 पूर्ण;

	क्रम (i = 0; i < 16; i++) अणु
		अगर (!wide_chip && (i > 7))
			अवरोध;
		m = 1;
		m = m << i;
		अगर ((m & dev->active_id[c]) != 0) अणु
			जारी;
		पूर्ण
		अगर (i == dev->host_id[c]) अणु
			prपूर्णांकk(KERN_INFO "         ID: %2d  Host Adapter\n", dev->host_id[c]);
			जारी;
		पूर्ण
		atp_ग_लिखोb_io(dev, c, 0x1b, wide_chip ? 0x01 : 0x00);
		atp_ग_लिखोb_io(dev, c, 1, 0x08);
		atp_ग_लिखोb_io(dev, c, 2, 0x7f);
		atp_ग_लिखोb_io(dev, c, 3, satn[0]);
		atp_ग_लिखोb_io(dev, c, 4, satn[1]);
		atp_ग_लिखोb_io(dev, c, 5, satn[2]);
		atp_ग_लिखोb_io(dev, c, 6, satn[3]);
		atp_ग_लिखोb_io(dev, c, 7, satn[4]);
		atp_ग_लिखोb_io(dev, c, 8, satn[5]);
		atp_ग_लिखोb_io(dev, c, 0x0f, 0);
		atp_ग_लिखोb_io(dev, c, 0x11, dev->id[c][i].devsp);
		atp_ग_लिखोb_io(dev, c, 0x12, 0);
		atp_ग_लिखोb_io(dev, c, 0x13, satn[6]);
		atp_ग_लिखोb_io(dev, c, 0x14, satn[7]);
		j = i;
		अगर ((j & 0x08) != 0) अणु
			j = (j & 0x07) | 0x40;
		पूर्ण
		atp_ग_लिखोb_io(dev, c, 0x15, j);
		atp_ग_लिखोb_io(dev, c, 0x18, satn[8]);

		जबतक ((atp_पढ़ोb_io(dev, c, 0x1f) & 0x80) == 0x00)
			cpu_relax();

		अगर (atp_पढ़ोb_io(dev, c, 0x17) != 0x11 && atp_पढ़ोb_io(dev, c, 0x17) != 0x8e)
			जारी;

		जबतक (atp_पढ़ोb_io(dev, c, 0x17) != 0x8e)
			cpu_relax();

		dev->active_id[c] |= m;

		atp_ग_लिखोb_io(dev, c, 0x10, 0x30);
		अगर (is885(dev) || is880(dev))
			atp_ग_लिखोb_io(dev, c, 0x14, 0x00);
		अन्यथा /* result of is870() merge - is this a bug? */
			atp_ग_लिखोb_io(dev, c, 0x04, 0x00);

phase_cmd:
		atp_ग_लिखोb_io(dev, c, 0x18, 0x08);

		जबतक ((atp_पढ़ोb_io(dev, c, 0x1f) & 0x80) == 0x00)
			cpu_relax();

		j = atp_पढ़ोb_io(dev, c, 0x17);
		अगर (j != 0x16) अणु
			atp_ग_लिखोb_io(dev, c, 0x10, 0x41);
			जाओ phase_cmd;
		पूर्ण
sel_ok:
		atp_ग_लिखोb_io(dev, c, 3, inqd[0]);
		atp_ग_लिखोb_io(dev, c, 4, inqd[1]);
		atp_ग_लिखोb_io(dev, c, 5, inqd[2]);
		atp_ग_लिखोb_io(dev, c, 6, inqd[3]);
		atp_ग_लिखोb_io(dev, c, 7, inqd[4]);
		atp_ग_लिखोb_io(dev, c, 8, inqd[5]);
		atp_ग_लिखोb_io(dev, c, 0x0f, 0);
		atp_ग_लिखोb_io(dev, c, 0x11, dev->id[c][i].devsp);
		atp_ग_लिखोb_io(dev, c, 0x12, 0);
		atp_ग_लिखोb_io(dev, c, 0x13, inqd[6]);
		atp_ग_लिखोb_io(dev, c, 0x14, inqd[7]);
		atp_ग_लिखोb_io(dev, c, 0x18, inqd[8]);

		जबतक ((atp_पढ़ोb_io(dev, c, 0x1f) & 0x80) == 0x00)
			cpu_relax();

		अगर (atp_पढ़ोb_io(dev, c, 0x17) != 0x11 && atp_पढ़ोb_io(dev, c, 0x17) != 0x8e)
			जारी;

		जबतक (atp_पढ़ोb_io(dev, c, 0x17) != 0x8e)
			cpu_relax();

		अगर (wide_chip)
			atp_ग_लिखोb_io(dev, c, 0x1b, 0x00);

		atp_ग_लिखोb_io(dev, c, 0x18, 0x08);
		j = 0;
rd_inq_data:
		k = atp_पढ़ोb_io(dev, c, 0x1f);
		अगर ((k & 0x01) != 0) अणु
			mbuf[j++] = atp_पढ़ोb_io(dev, c, 0x19);
			जाओ rd_inq_data;
		पूर्ण
		अगर ((k & 0x80) == 0) अणु
			जाओ rd_inq_data;
		पूर्ण
		j = atp_पढ़ोb_io(dev, c, 0x17);
		अगर (j == 0x16) अणु
			जाओ inq_ok;
		पूर्ण
		atp_ग_लिखोb_io(dev, c, 0x10, 0x46);
		atp_ग_लिखोb_io(dev, c, 0x12, 0);
		atp_ग_लिखोb_io(dev, c, 0x13, 0);
		atp_ग_लिखोb_io(dev, c, 0x14, 0);
		atp_ग_लिखोb_io(dev, c, 0x18, 0x08);

		जबतक ((atp_पढ़ोb_io(dev, c, 0x1f) & 0x80) == 0x00)
			cpu_relax();

		अगर (atp_पढ़ोb_io(dev, c, 0x17) != 0x16)
			जाओ sel_ok;

inq_ok:
		mbuf[36] = 0;
		prपूर्णांकk(KERN_INFO "         ID: %2d  %s\n", i, &mbuf[8]);
		dev->id[c][i].devtype = mbuf[0];
		rmb = mbuf[1];
		n = mbuf[7];
		अगर (!wide_chip)
			जाओ not_wide;
		अगर ((mbuf[7] & 0x60) == 0) अणु
			जाओ not_wide;
		पूर्ण
		अगर (is885(dev) || is880(dev)) अणु
			अगर ((i < 8) && ((dev->global_map[c] & 0x20) == 0))
				जाओ not_wide;
		पूर्ण अन्यथा अणु /* result of is870() merge - is this a bug? */
			अगर ((dev->global_map[c] & 0x20) == 0)
				जाओ not_wide;
		पूर्ण
		अगर (lvdmode == 0) अणु
			जाओ chg_wide;
		पूर्ण
		अगर (dev->sp[c][i] != 0x04)	// क्रमce u2
		अणु
			जाओ chg_wide;
		पूर्ण

		atp_ग_लिखोb_io(dev, c, 0x1b, 0x01);
		atp_ग_लिखोb_io(dev, c, 3, satn[0]);
		atp_ग_लिखोb_io(dev, c, 4, satn[1]);
		atp_ग_लिखोb_io(dev, c, 5, satn[2]);
		atp_ग_लिखोb_io(dev, c, 6, satn[3]);
		atp_ग_लिखोb_io(dev, c, 7, satn[4]);
		atp_ग_लिखोb_io(dev, c, 8, satn[5]);
		atp_ग_लिखोb_io(dev, c, 0x0f, 0);
		atp_ग_लिखोb_io(dev, c, 0x11, dev->id[c][i].devsp);
		atp_ग_लिखोb_io(dev, c, 0x12, 0);
		atp_ग_लिखोb_io(dev, c, 0x13, satn[6]);
		atp_ग_लिखोb_io(dev, c, 0x14, satn[7]);
		atp_ग_लिखोb_io(dev, c, 0x18, satn[8]);

		जबतक ((atp_पढ़ोb_io(dev, c, 0x1f) & 0x80) == 0x00)
			cpu_relax();

		अगर (atp_पढ़ोb_io(dev, c, 0x17) != 0x11 && atp_पढ़ोb_io(dev, c, 0x17) != 0x8e)
			जारी;

		जबतक (atp_पढ़ोb_io(dev, c, 0x17) != 0x8e)
			cpu_relax();

try_u3:
		j = 0;
		atp_ग_लिखोb_io(dev, c, 0x14, 0x09);
		atp_ग_लिखोb_io(dev, c, 0x18, 0x20);

		जबतक ((atp_पढ़ोb_io(dev, c, 0x1f) & 0x80) == 0) अणु
			अगर ((atp_पढ़ोb_io(dev, c, 0x1f) & 0x01) != 0)
				atp_ग_लिखोb_io(dev, c, 0x19, u3[j++]);
			cpu_relax();
		पूर्ण

		जबतक ((atp_पढ़ोb_io(dev, c, 0x17) & 0x80) == 0x00)
			cpu_relax();

		j = atp_पढ़ोb_io(dev, c, 0x17) & 0x0f;
		अगर (j == 0x0f) अणु
			जाओ u3p_in;
		पूर्ण
		अगर (j == 0x0a) अणु
			जाओ u3p_cmd;
		पूर्ण
		अगर (j == 0x0e) अणु
			जाओ try_u3;
		पूर्ण
		जारी;
u3p_out:
		atp_ग_लिखोb_io(dev, c, 0x18, 0x20);
		जबतक ((atp_पढ़ोb_io(dev, c, 0x1f) & 0x80) == 0) अणु
			अगर ((atp_पढ़ोb_io(dev, c, 0x1f) & 0x01) != 0)
				atp_ग_लिखोb_io(dev, c, 0x19, 0);
			cpu_relax();
		पूर्ण
		j = atp_पढ़ोb_io(dev, c, 0x17) & 0x0f;
		अगर (j == 0x0f) अणु
			जाओ u3p_in;
		पूर्ण
		अगर (j == 0x0a) अणु
			जाओ u3p_cmd;
		पूर्ण
		अगर (j == 0x0e) अणु
			जाओ u3p_out;
		पूर्ण
		जारी;
u3p_in:
		atp_ग_लिखोb_io(dev, c, 0x14, 0x09);
		atp_ग_लिखोb_io(dev, c, 0x18, 0x20);
		k = 0;
u3p_in1:
		j = atp_पढ़ोb_io(dev, c, 0x1f);
		अगर ((j & 0x01) != 0) अणु
			mbuf[k++] = atp_पढ़ोb_io(dev, c, 0x19);
			जाओ u3p_in1;
		पूर्ण
		अगर ((j & 0x80) == 0x00) अणु
			जाओ u3p_in1;
		पूर्ण
		j = atp_पढ़ोb_io(dev, c, 0x17) & 0x0f;
		अगर (j == 0x0f) अणु
			जाओ u3p_in;
		पूर्ण
		अगर (j == 0x0a) अणु
			जाओ u3p_cmd;
		पूर्ण
		अगर (j == 0x0e) अणु
			जाओ u3p_out;
		पूर्ण
		जारी;
u3p_cmd:
		atp_ग_लिखोb_io(dev, c, 0x10, 0x30);
		atp_ग_लिखोb_io(dev, c, 0x14, 0x00);
		atp_ग_लिखोb_io(dev, c, 0x18, 0x08);

		जबतक ((atp_पढ़ोb_io(dev, c, 0x1f) & 0x80) == 0x00);

		j = atp_पढ़ोb_io(dev, c, 0x17);
		अगर (j != 0x16) अणु
			अगर (j == 0x4e) अणु
				जाओ u3p_out;
			पूर्ण
			जारी;
		पूर्ण
		अगर (mbuf[0] != 0x01) अणु
			जाओ chg_wide;
		पूर्ण
		अगर (mbuf[1] != 0x06) अणु
			जाओ chg_wide;
		पूर्ण
		अगर (mbuf[2] != 0x04) अणु
			जाओ chg_wide;
		पूर्ण
		अगर (mbuf[3] == 0x09) अणु
			m = 1;
			m = m << i;
			dev->wide_id[c] |= m;
			dev->id[c][i].devsp = 0xce;
#अगर_घोषित ED_DBGP
			prपूर्णांकk("dev->id[%2d][%2d].devsp = %2x\n",
			       c, i, dev->id[c][i].devsp);
#पूर्ण_अगर
			जारी;
		पूर्ण
chg_wide:
		atp_ग_लिखोb_io(dev, c, 0x1b, 0x01);
		atp_ग_लिखोb_io(dev, c, 3, satn[0]);
		atp_ग_लिखोb_io(dev, c, 4, satn[1]);
		atp_ग_लिखोb_io(dev, c, 5, satn[2]);
		atp_ग_लिखोb_io(dev, c, 6, satn[3]);
		atp_ग_लिखोb_io(dev, c, 7, satn[4]);
		atp_ग_लिखोb_io(dev, c, 8, satn[5]);
		atp_ग_लिखोb_io(dev, c, 0x0f, 0);
		atp_ग_लिखोb_io(dev, c, 0x11, dev->id[c][i].devsp);
		atp_ग_लिखोb_io(dev, c, 0x12, 0);
		atp_ग_लिखोb_io(dev, c, 0x13, satn[6]);
		atp_ग_लिखोb_io(dev, c, 0x14, satn[7]);
		atp_ग_लिखोb_io(dev, c, 0x18, satn[8]);

		जबतक ((atp_पढ़ोb_io(dev, c, 0x1f) & 0x80) == 0x00)
			cpu_relax();

		अगर (atp_पढ़ोb_io(dev, c, 0x17) != 0x11 &&
		    atp_पढ़ोb_io(dev, c, 0x17) != 0x8e)
			जारी;

		जबतक (atp_पढ़ोb_io(dev, c, 0x17) != 0x8e)
			cpu_relax();

try_wide:
		j = 0;
		atp_ग_लिखोb_io(dev, c, 0x14, 0x05);
		atp_ग_लिखोb_io(dev, c, 0x18, 0x20);

		जबतक ((atp_पढ़ोb_io(dev, c, 0x1f) & 0x80) == 0) अणु
			अगर ((atp_पढ़ोb_io(dev, c, 0x1f) & 0x01) != 0)
				atp_ग_लिखोb_io(dev, c, 0x19, wide[j++]);
			cpu_relax();
		पूर्ण

		जबतक ((atp_पढ़ोb_io(dev, c, 0x17) & 0x80) == 0x00)
			cpu_relax();

		j = atp_पढ़ोb_io(dev, c, 0x17) & 0x0f;
		अगर (j == 0x0f) अणु
			जाओ widep_in;
		पूर्ण
		अगर (j == 0x0a) अणु
			जाओ widep_cmd;
		पूर्ण
		अगर (j == 0x0e) अणु
			जाओ try_wide;
		पूर्ण
		जारी;
widep_out:
		atp_ग_लिखोb_io(dev, c, 0x18, 0x20);
		जबतक ((atp_पढ़ोb_io(dev, c, 0x1f) & 0x80) == 0) अणु
			अगर ((atp_पढ़ोb_io(dev, c, 0x1f) & 0x01) != 0)
				atp_ग_लिखोb_io(dev, c, 0x19, 0);
			cpu_relax();
		पूर्ण
		j = atp_पढ़ोb_io(dev, c, 0x17) & 0x0f;
		अगर (j == 0x0f) अणु
			जाओ widep_in;
		पूर्ण
		अगर (j == 0x0a) अणु
			जाओ widep_cmd;
		पूर्ण
		अगर (j == 0x0e) अणु
			जाओ widep_out;
		पूर्ण
		जारी;
widep_in:
		atp_ग_लिखोb_io(dev, c, 0x14, 0xff);
		atp_ग_लिखोb_io(dev, c, 0x18, 0x20);
		k = 0;
widep_in1:
		j = atp_पढ़ोb_io(dev, c, 0x1f);
		अगर ((j & 0x01) != 0) अणु
			mbuf[k++] = atp_पढ़ोb_io(dev, c, 0x19);
			जाओ widep_in1;
		पूर्ण
		अगर ((j & 0x80) == 0x00) अणु
			जाओ widep_in1;
		पूर्ण
		j = atp_पढ़ोb_io(dev, c, 0x17) & 0x0f;
		अगर (j == 0x0f) अणु
			जाओ widep_in;
		पूर्ण
		अगर (j == 0x0a) अणु
			जाओ widep_cmd;
		पूर्ण
		अगर (j == 0x0e) अणु
			जाओ widep_out;
		पूर्ण
		जारी;
widep_cmd:
		atp_ग_लिखोb_io(dev, c, 0x10, 0x30);
		atp_ग_लिखोb_io(dev, c, 0x14, 0x00);
		atp_ग_लिखोb_io(dev, c, 0x18, 0x08);

		जबतक ((atp_पढ़ोb_io(dev, c, 0x1f) & 0x80) == 0x00)
			cpu_relax();

		j = atp_पढ़ोb_io(dev, c, 0x17);
		अगर (j != 0x16) अणु
			अगर (j == 0x4e) अणु
				जाओ widep_out;
			पूर्ण
			जारी;
		पूर्ण
		अगर (mbuf[0] != 0x01) अणु
			जाओ not_wide;
		पूर्ण
		अगर (mbuf[1] != 0x02) अणु
			जाओ not_wide;
		पूर्ण
		अगर (mbuf[2] != 0x03) अणु
			जाओ not_wide;
		पूर्ण
		अगर (mbuf[3] != 0x01) अणु
			जाओ not_wide;
		पूर्ण
		m = 1;
		m = m << i;
		dev->wide_id[c] |= m;
not_wide:
		अगर ((dev->id[c][i].devtype == 0x00) ||
		    (dev->id[c][i].devtype == 0x07) ||
		    ((dev->id[c][i].devtype == 0x05) && ((n & 0x10) != 0))) अणु
			m = 1;
			m = m << i;
			अगर ((dev->async[c] & m) != 0) अणु
				जाओ set_sync;
			पूर्ण
		पूर्ण
		जारी;
set_sync:
		अगर ((!is885(dev) && !is880(dev)) || (dev->sp[c][i] == 0x02)) अणु
			synu[4] = 0x0c;
			synuw[4] = 0x0c;
		पूर्ण अन्यथा अणु
			अगर (dev->sp[c][i] >= 0x03) अणु
				synu[4] = 0x0a;
				synuw[4] = 0x0a;
			पूर्ण
		पूर्ण
		j = 0;
		अगर ((m & dev->wide_id[c]) != 0) अणु
			j |= 0x01;
		पूर्ण
		atp_ग_लिखोb_io(dev, c, 0x1b, j);
		atp_ग_लिखोb_io(dev, c, 3, satn[0]);
		atp_ग_लिखोb_io(dev, c, 4, satn[1]);
		atp_ग_लिखोb_io(dev, c, 5, satn[2]);
		atp_ग_लिखोb_io(dev, c, 6, satn[3]);
		atp_ग_लिखोb_io(dev, c, 7, satn[4]);
		atp_ग_लिखोb_io(dev, c, 8, satn[5]);
		atp_ग_लिखोb_io(dev, c, 0x0f, 0);
		atp_ग_लिखोb_io(dev, c, 0x11, dev->id[c][i].devsp);
		atp_ग_लिखोb_io(dev, c, 0x12, 0);
		atp_ग_लिखोb_io(dev, c, 0x13, satn[6]);
		atp_ग_लिखोb_io(dev, c, 0x14, satn[7]);
		atp_ग_लिखोb_io(dev, c, 0x18, satn[8]);

		जबतक ((atp_पढ़ोb_io(dev, c, 0x1f) & 0x80) == 0x00)
			cpu_relax();

		अगर (atp_पढ़ोb_io(dev, c, 0x17) != 0x11 &&
		    atp_पढ़ोb_io(dev, c, 0x17) != 0x8e)
			जारी;

		जबतक (atp_पढ़ोb_io(dev, c, 0x17) != 0x8e)
			cpu_relax();

try_sync:
		j = 0;
		atp_ग_लिखोb_io(dev, c, 0x14, 0x06);
		atp_ग_लिखोb_io(dev, c, 0x18, 0x20);

		जबतक ((atp_पढ़ोb_io(dev, c, 0x1f) & 0x80) == 0) अणु
			अगर ((atp_पढ़ोb_io(dev, c, 0x1f) & 0x01) != 0) अणु
				अगर ((m & dev->wide_id[c]) != 0) अणु
					अगर (is885(dev) || is880(dev)) अणु
						अगर ((m & dev->ultra_map[c]) != 0) अणु
							atp_ग_लिखोb_io(dev, c, 0x19, synuw[j++]);
						पूर्ण अन्यथा अणु
							atp_ग_लिखोb_io(dev, c, 0x19, synw[j++]);
						पूर्ण
					पूर्ण अन्यथा
						atp_ग_लिखोb_io(dev, c, 0x19, synw_870[j++]);
				पूर्ण अन्यथा अणु
					अगर ((m & dev->ultra_map[c]) != 0) अणु
						atp_ग_लिखोb_io(dev, c, 0x19, synu[j++]);
					पूर्ण अन्यथा अणु
						atp_ग_लिखोb_io(dev, c, 0x19, synn[j++]);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण

		जबतक ((atp_पढ़ोb_io(dev, c, 0x17) & 0x80) == 0x00)
			cpu_relax();

		j = atp_पढ़ोb_io(dev, c, 0x17) & 0x0f;
		अगर (j == 0x0f) अणु
			जाओ phase_ins;
		पूर्ण
		अगर (j == 0x0a) अणु
			जाओ phase_cmds;
		पूर्ण
		अगर (j == 0x0e) अणु
			जाओ try_sync;
		पूर्ण
		जारी;
phase_outs:
		atp_ग_लिखोb_io(dev, c, 0x18, 0x20);
		जबतक ((atp_पढ़ोb_io(dev, c, 0x1f) & 0x80) == 0x00) अणु
			अगर ((atp_पढ़ोb_io(dev, c, 0x1f) & 0x01) != 0x00)
				atp_ग_लिखोb_io(dev, c, 0x19, 0x00);
			cpu_relax();
		पूर्ण
		j = atp_पढ़ोb_io(dev, c, 0x17);
		अगर (j == 0x85) अणु
			जाओ tar_dcons;
		पूर्ण
		j &= 0x0f;
		अगर (j == 0x0f) अणु
			जाओ phase_ins;
		पूर्ण
		अगर (j == 0x0a) अणु
			जाओ phase_cmds;
		पूर्ण
		अगर (j == 0x0e) अणु
			जाओ phase_outs;
		पूर्ण
		जारी;
phase_ins:
		अगर (is885(dev) || is880(dev))
			atp_ग_लिखोb_io(dev, c, 0x14, 0x06);
		अन्यथा
			atp_ग_लिखोb_io(dev, c, 0x14, 0xff);
		atp_ग_लिखोb_io(dev, c, 0x18, 0x20);
		k = 0;
phase_ins1:
		j = atp_पढ़ोb_io(dev, c, 0x1f);
		अगर ((j & 0x01) != 0x00) अणु
			mbuf[k++] = atp_पढ़ोb_io(dev, c, 0x19);
			जाओ phase_ins1;
		पूर्ण
		अगर ((j & 0x80) == 0x00) अणु
			जाओ phase_ins1;
		पूर्ण

		जबतक ((atp_पढ़ोb_io(dev, c, 0x17) & 0x80) == 0x00);

		j = atp_पढ़ोb_io(dev, c, 0x17);
		अगर (j == 0x85) अणु
			जाओ tar_dcons;
		पूर्ण
		j &= 0x0f;
		अगर (j == 0x0f) अणु
			जाओ phase_ins;
		पूर्ण
		अगर (j == 0x0a) अणु
			जाओ phase_cmds;
		पूर्ण
		अगर (j == 0x0e) अणु
			जाओ phase_outs;
		पूर्ण
		जारी;
phase_cmds:
		atp_ग_लिखोb_io(dev, c, 0x10, 0x30);
tar_dcons:
		atp_ग_लिखोb_io(dev, c, 0x14, 0x00);
		atp_ग_लिखोb_io(dev, c, 0x18, 0x08);

		जबतक ((atp_पढ़ोb_io(dev, c, 0x1f) & 0x80) == 0x00)
			cpu_relax();

		j = atp_पढ़ोb_io(dev, c, 0x17);
		अगर (j != 0x16) अणु
			जारी;
		पूर्ण
		अगर (mbuf[0] != 0x01) अणु
			जारी;
		पूर्ण
		अगर (mbuf[1] != 0x03) अणु
			जारी;
		पूर्ण
		अगर (mbuf[4] == 0x00) अणु
			जारी;
		पूर्ण
		अगर (mbuf[3] > 0x64) अणु
			जारी;
		पूर्ण
		अगर (is885(dev) || is880(dev)) अणु
			अगर (mbuf[4] > 0x0e) अणु
				mbuf[4] = 0x0e;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (mbuf[4] > 0x0c) अणु
				mbuf[4] = 0x0c;
			पूर्ण
		पूर्ण
		dev->id[c][i].devsp = mbuf[4];
		अगर (is885(dev) || is880(dev))
			अगर (mbuf[3] < 0x0c) अणु
				j = 0xb0;
				जाओ set_syn_ok;
			पूर्ण
		अगर ((mbuf[3] < 0x0d) && (rmb == 0)) अणु
			j = 0xa0;
			जाओ set_syn_ok;
		पूर्ण
		अगर (mbuf[3] < 0x1a) अणु
			j = 0x20;
			जाओ set_syn_ok;
		पूर्ण
		अगर (mbuf[3] < 0x33) अणु
			j = 0x40;
			जाओ set_syn_ok;
		पूर्ण
		अगर (mbuf[3] < 0x4c) अणु
			j = 0x50;
			जाओ set_syn_ok;
		पूर्ण
		j = 0x60;
set_syn_ok:
		dev->id[c][i].devsp = (dev->id[c][i].devsp & 0x0f) | j;
#अगर_घोषित ED_DBGP
		prपूर्णांकk("dev->id[%2d][%2d].devsp = %2x\n",
		       c,i,dev->id[c][i].devsp);
#पूर्ण_अगर
	पूर्ण
पूर्ण
