<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Derived from Applicom driver ac.c क्रम SCO Unix                            */
/* Ported by David Woodhouse, Axiom (Cambridge) Ltd.                         */
/* dwmw2@infradead.org 30/8/98                                               */
/* $Id: ac.c,v 1.30 2000/03/22 16:03:57 dwmw2 Exp $			     */
/* This module is क्रम Linux 2.1 and 2.2 series kernels.                      */
/*****************************************************************************/
/* J PAGET 18/02/94 passage V2.4.2 ioctl avec code 2 reset to les पूर्णांकerrupt  */
/* ceci pour reseter correctement apres une sortie sauvage                   */
/* J PAGET 02/05/94 passage V2.4.3 dans le traitement de d'पूर्णांकerruption,     */
/* LoopCount n'etait pas initialise a 0.                                     */
/* F LAFORSE 04/07/95 version V2.6.0 lecture biकरोn apres acces a une carte   */
/*           pour liberer le bus                                             */
/* J.PAGET 19/11/95 version V2.6.1 Nombre, addresse,irq n'est plus configure */
/* et passe en argument a acinit, mais est scrute sur le bus pour s'adapter  */
/* au nombre de cartes presentes sur le bus. IOCL code 6 affichait V2.4.3    */
/* F.LAFORSE 28/11/95 creation de fichiers acXX.o avec les dअगरferentes       */
/* addresses de base des cartes, IOCTL 6 plus complet                         */
/* J.PAGET le 19/08/96 copie de la version V2.6 en V2.8.0 sans modअगरication  */
/* de code autre que le texte V2.6.1 en V2.8.0                               */
/*****************************************************************************/


#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mutex.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/रुको.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/nospec.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

#समावेश "applicom.h"


/* NOTE: We use क्रम loops with अणुग_लिखो,पढ़ोपूर्णb() instead of 
   स_नकल_अणुfrom,toपूर्णio throughout this driver. This is because
   the board करोesn't correctly handle word accesses - only
   bytes. 
*/


#अघोषित DEBUG

#घोषणा MAX_BOARD 8		/* maximum of pc board possible */
#घोषणा MAX_ISA_BOARD 4
#घोषणा LEN_RAM_IO 0x800

#अगर_अघोषित PCI_VENDOR_ID_APPLICOM
#घोषणा PCI_VENDOR_ID_APPLICOM                0x1389
#घोषणा PCI_DEVICE_ID_APPLICOM_PCIGENERIC     0x0001
#घोषणा PCI_DEVICE_ID_APPLICOM_PCI2000IBS_CAN 0x0002
#घोषणा PCI_DEVICE_ID_APPLICOM_PCI2000PFB     0x0003
#पूर्ण_अगर

अटल DEFINE_MUTEX(ac_mutex);
अटल अक्षर *applicom_pci_devnames[] = अणु
	"PCI board",
	"PCI2000IBS / PCI2000CAN",
	"PCI2000PFB"
पूर्ण;

अटल स्थिर काष्ठा pci_device_id applicom_pci_tbl[] = अणु
	अणु PCI_VDEVICE(APPLICOM, PCI_DEVICE_ID_APPLICOM_PCIGENERIC) पूर्ण,
	अणु PCI_VDEVICE(APPLICOM, PCI_DEVICE_ID_APPLICOM_PCI2000IBS_CAN) पूर्ण,
	अणु PCI_VDEVICE(APPLICOM, PCI_DEVICE_ID_APPLICOM_PCI2000PFB) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, applicom_pci_tbl);

MODULE_AUTHOR("David Woodhouse & Applicom International");
MODULE_DESCRIPTION("Driver for Applicom Profibus card");
MODULE_LICENSE("GPL");
MODULE_ALIAS_MISCDEV(AC_MINOR);

अटल काष्ठा applicom_board अणु
	अचिन्हित दीर्घ PhysIO;
	व्योम __iomem *RamIO;
	रुको_queue_head_t FlagSleepSend;
	दीर्घ irq;
	spinlock_t mutex;
पूर्ण apbs[MAX_BOARD];

अटल अचिन्हित पूर्णांक irq = 0;	/* पूर्णांकerrupt number IRQ       */
अटल अचिन्हित दीर्घ mem = 0;	/* physical segment of board  */

module_param_hw(irq, uपूर्णांक, irq, 0);
MODULE_PARM_DESC(irq, "IRQ of the Applicom board");
module_param_hw(mem, uदीर्घ, iomem, 0);
MODULE_PARM_DESC(mem, "Shared Memory Address of Applicom board");

अटल अचिन्हित पूर्णांक numboards;	/* number of installed boards */
अटल अस्थिर अचिन्हित अक्षर Dummy;
अटल DECLARE_WAIT_QUEUE_HEAD(FlagSleepRec);
अटल अचिन्हित पूर्णांक WriteErrorCount;	/* number of ग_लिखो error      */
अटल अचिन्हित पूर्णांक ReadErrorCount;	/* number of पढ़ो error       */
अटल अचिन्हित पूर्णांक DeviceErrorCount;	/* number of device error     */

अटल sमाप_प्रकार ac_पढ़ो (काष्ठा file *, अक्षर __user *, माप_प्रकार, loff_t *);
अटल sमाप_प्रकार ac_ग_लिखो (काष्ठा file *, स्थिर अक्षर __user *, माप_प्रकार, loff_t *);
अटल दीर्घ ac_ioctl(काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
अटल irqवापस_t ac_पूर्णांकerrupt(पूर्णांक, व्योम *);

अटल स्थिर काष्ठा file_operations ac_fops = अणु
	.owner = THIS_MODULE,
	.llseek = no_llseek,
	.पढ़ो = ac_पढ़ो,
	.ग_लिखो = ac_ग_लिखो,
	.unlocked_ioctl = ac_ioctl,
पूर्ण;

अटल काष्ठा miscdevice ac_miscdev = अणु
	AC_MINOR,
	"ac",
	&ac_fops
पूर्ण;

अटल पूर्णांक dummy;	/* dev_id क्रम request_irq() */

अटल पूर्णांक ac_रेजिस्टर_board(अचिन्हित दीर्घ physloc, व्योम __iomem *loc, 
		      अचिन्हित अक्षर boardno)
अणु
	अस्थिर अचिन्हित अक्षर byte_reset_it;

	अगर((पढ़ोb(loc + CONF_END_TEST)     != 0x00) ||
	   (पढ़ोb(loc + CONF_END_TEST + 1) != 0x55) ||
	   (पढ़ोb(loc + CONF_END_TEST + 2) != 0xAA) ||
	   (पढ़ोb(loc + CONF_END_TEST + 3) != 0xFF))
		वापस 0;

	अगर (!boardno)
		boardno = पढ़ोb(loc + NUMCARD_OWNER_TO_PC);

	अगर (!boardno || boardno > MAX_BOARD) अणु
		prपूर्णांकk(KERN_WARNING "Board #%d (at 0x%lx) is out of range (1 <= x <= %d).\n",
		       boardno, physloc, MAX_BOARD);
		वापस 0;
	पूर्ण

	अगर (apbs[boardno - 1].RamIO) अणु
		prपूर्णांकk(KERN_WARNING "Board #%d (at 0x%lx) conflicts with previous board #%d (at 0x%lx)\n", 
		       boardno, physloc, boardno, apbs[boardno-1].PhysIO);
		वापस 0;
	पूर्ण

	boardno--;

	apbs[boardno].PhysIO = physloc;
	apbs[boardno].RamIO = loc;
	init_रुकोqueue_head(&apbs[boardno].FlagSleepSend);
	spin_lock_init(&apbs[boardno].mutex);
	byte_reset_it = पढ़ोb(loc + RAM_IT_TO_PC);

	numboards++;
	वापस boardno + 1;
पूर्ण

अटल व्योम __निकास applicom_निकास(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	misc_deरेजिस्टर(&ac_miscdev);

	क्रम (i = 0; i < MAX_BOARD; i++) अणु

		अगर (!apbs[i].RamIO)
			जारी;

		अगर (apbs[i].irq)
			मुक्त_irq(apbs[i].irq, &dummy);

		iounmap(apbs[i].RamIO);
	पूर्ण
पूर्ण

अटल पूर्णांक __init applicom_init(व्योम)
अणु
	पूर्णांक i, numisa = 0;
	काष्ठा pci_dev *dev = शून्य;
	व्योम __iomem *RamIO;
	पूर्णांक boardno, ret;

	prपूर्णांकk(KERN_INFO "Applicom driver: $Id: ac.c,v 1.30 2000/03/22 16:03:57 dwmw2 Exp $\n");

	/* No mem and irq given - check क्रम a PCI card */

	जबतक ( (dev = pci_get_class(PCI_CLASS_OTHERS << 16, dev))) अणु

		अगर (!pci_match_id(applicom_pci_tbl, dev))
			जारी;
		
		अगर (pci_enable_device(dev))
			वापस -EIO;

		RamIO = ioremap(pci_resource_start(dev, 0), LEN_RAM_IO);

		अगर (!RamIO) अणु
			prपूर्णांकk(KERN_INFO "ac.o: Failed to ioremap PCI memory "
				"space at 0x%llx\n",
				(अचिन्हित दीर्घ दीर्घ)pci_resource_start(dev, 0));
			pci_disable_device(dev);
			वापस -EIO;
		पूर्ण

		prपूर्णांकk(KERN_INFO "Applicom %s found at mem 0x%llx, irq %d\n",
		       applicom_pci_devnames[dev->device-1],
			   (अचिन्हित दीर्घ दीर्घ)pci_resource_start(dev, 0),
		       dev->irq);

		boardno = ac_रेजिस्टर_board(pci_resource_start(dev, 0),
				RamIO, 0);
		अगर (!boardno) अणु
			prपूर्णांकk(KERN_INFO "ac.o: PCI Applicom device doesn't have correct signature.\n");
			iounmap(RamIO);
			pci_disable_device(dev);
			जारी;
		पूर्ण

		अगर (request_irq(dev->irq, &ac_पूर्णांकerrupt, IRQF_SHARED, "Applicom PCI", &dummy)) अणु
			prपूर्णांकk(KERN_INFO "Could not allocate IRQ %d for PCI Applicom device.\n", dev->irq);
			iounmap(RamIO);
			pci_disable_device(dev);
			apbs[boardno - 1].RamIO = शून्य;
			जारी;
		पूर्ण

		/* Enable पूर्णांकerrupts. */

		ग_लिखोb(0x40, apbs[boardno - 1].RamIO + RAM_IT_FROM_PC);

		apbs[boardno - 1].irq = dev->irq;
	पूर्ण

	/* Finished with PCI cards. If none रेजिस्टरed, 
	 * and there was no mem/irq specअगरied, निकास */

	अगर (!mem || !irq) अणु
		अगर (numboards)
			जाओ fin;
		अन्यथा अणु
			prपूर्णांकk(KERN_INFO "ac.o: No PCI boards found.\n");
			prपूर्णांकk(KERN_INFO "ac.o: For an ISA board you must supply memory and irq parameters.\n");
			वापस -ENXIO;
		पूर्ण
	पूर्ण

	/* Now try the specअगरied ISA cards */

	क्रम (i = 0; i < MAX_ISA_BOARD; i++) अणु
		RamIO = ioremap(mem + (LEN_RAM_IO * i), LEN_RAM_IO);

		अगर (!RamIO) अणु
			prपूर्णांकk(KERN_INFO "ac.o: Failed to ioremap the ISA card's memory space (slot #%d)\n", i + 1);
			जारी;
		पूर्ण

		अगर (!(boardno = ac_रेजिस्टर_board((अचिन्हित दीर्घ)mem+ (LEN_RAM_IO*i),
						  RamIO,i+1))) अणु
			iounmap(RamIO);
			जारी;
		पूर्ण

		prपूर्णांकk(KERN_NOTICE "Applicom ISA card found at mem 0x%lx, irq %d\n", mem + (LEN_RAM_IO*i), irq);

		अगर (!numisa) अणु
			अगर (request_irq(irq, &ac_पूर्णांकerrupt, IRQF_SHARED, "Applicom ISA", &dummy)) अणु
				prपूर्णांकk(KERN_WARNING "Could not allocate IRQ %d for ISA Applicom device.\n", irq);
				iounmap(RamIO);
				apbs[boardno - 1].RamIO = शून्य;
			पूर्ण
			अन्यथा
				apbs[boardno - 1].irq = irq;
		पूर्ण
		अन्यथा
			apbs[boardno - 1].irq = 0;

		numisa++;
	पूर्ण

	अगर (!numisa)
		prपूर्णांकk(KERN_WARNING "ac.o: No valid ISA Applicom boards found "
				"at mem 0x%lx\n", mem);

 fin:
	init_रुकोqueue_head(&FlagSleepRec);

	WriteErrorCount = 0;
	ReadErrorCount = 0;
	DeviceErrorCount = 0;

	अगर (numboards) अणु
		ret = misc_रेजिस्टर(&ac_miscdev);
		अगर (ret) अणु
			prपूर्णांकk(KERN_WARNING "ac.o: Unable to register misc device\n");
			जाओ out;
		पूर्ण
		क्रम (i = 0; i < MAX_BOARD; i++) अणु
			पूर्णांक serial;
			अक्षर boardname[(SERIAL_NUMBER - TYPE_CARD) + 1];

			अगर (!apbs[i].RamIO)
				जारी;

			क्रम (serial = 0; serial < SERIAL_NUMBER - TYPE_CARD; serial++)
				boardname[serial] = पढ़ोb(apbs[i].RamIO + TYPE_CARD + serial);

			boardname[serial] = 0;


			prपूर्णांकk(KERN_INFO "Applicom board %d: %s, PROM V%d.%d",
			       i+1, boardname,
			       (पूर्णांक)(पढ़ोb(apbs[i].RamIO + VERS) >> 4),
			       (पूर्णांक)(पढ़ोb(apbs[i].RamIO + VERS) & 0xF));
			
			serial = (पढ़ोb(apbs[i].RamIO + SERIAL_NUMBER) << 16) + 
				(पढ़ोb(apbs[i].RamIO + SERIAL_NUMBER + 1) << 8) + 
				(पढ़ोb(apbs[i].RamIO + SERIAL_NUMBER + 2) );

			अगर (serial != 0)
				prपूर्णांकk(" S/N %d\n", serial);
			अन्यथा
				prपूर्णांकk("\n");
		पूर्ण
		वापस 0;
	पूर्ण

	अन्यथा
		वापस -ENXIO;

out:
	क्रम (i = 0; i < MAX_BOARD; i++) अणु
		अगर (!apbs[i].RamIO)
			जारी;
		अगर (apbs[i].irq)
			मुक्त_irq(apbs[i].irq, &dummy);
		iounmap(apbs[i].RamIO);
	पूर्ण
	वापस ret;
पूर्ण

module_init(applicom_init);
module_निकास(applicom_निकास);


अटल sमाप_प्रकार ac_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t * ppos)
अणु
	अचिन्हित पूर्णांक NumCard;	/* Board number 1 -> 8           */
	अचिन्हित पूर्णांक IndexCard;	/* Index board number 0 -> 7     */
	अचिन्हित अक्षर TicCard;	/* Board TIC to send             */
	अचिन्हित दीर्घ flags;	/* Current priority              */
	काष्ठा st_ram_io st_loc;
	काष्ठा mailbox पंचांगpmailbox;
#अगर_घोषित DEBUG
	पूर्णांक c;
#पूर्ण_अगर
	DECLARE_WAITQUEUE(रुको, current);

	अगर (count != माप(काष्ठा st_ram_io) + माप(काष्ठा mailbox)) अणु
		अटल पूर्णांक warncount = 5;
		अगर (warncount) अणु
			prपूर्णांकk(KERN_INFO "Hmmm. write() of Applicom card, length %zd != expected %zd\n",
			       count, माप(काष्ठा st_ram_io) + माप(काष्ठा mailbox));
			warncount--;
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	अगर(copy_from_user(&st_loc, buf, माप(काष्ठा st_ram_io))) 
		वापस -EFAULT;
	
	अगर(copy_from_user(&पंचांगpmailbox, &buf[माप(काष्ठा st_ram_io)],
			  माप(काष्ठा mailbox))) 
		वापस -EFAULT;

	NumCard = st_loc.num_card;	/* board number to send          */
	TicCard = st_loc.tic_des_from_pc;	/* tic number to send            */
	IndexCard = NumCard - 1;

	अगर (IndexCard >= MAX_BOARD)
		वापस -EINVAL;
	IndexCard = array_index_nospec(IndexCard, MAX_BOARD);

	अगर (!apbs[IndexCard].RamIO)
		वापस -EINVAL;

#अगर_घोषित DEBUG
	prपूर्णांकk("Write to applicom card #%d. struct st_ram_io follows:",
	       IndexCard+1);

		क्रम (c = 0; c < माप(काष्ठा st_ram_io);) अणु
		
			prपूर्णांकk("\n%5.5X: %2.2X", c, ((अचिन्हित अक्षर *) &st_loc)[c]);

			क्रम (c++; c % 8 && c < माप(काष्ठा st_ram_io); c++) अणु
				prपूर्णांकk(" %2.2X", ((अचिन्हित अक्षर *) &st_loc)[c]);
			पूर्ण
		पूर्ण

		prपूर्णांकk("\nstruct mailbox follows:");

		क्रम (c = 0; c < माप(काष्ठा mailbox);) अणु
			prपूर्णांकk("\n%5.5X: %2.2X", c, ((अचिन्हित अक्षर *) &पंचांगpmailbox)[c]);

			क्रम (c++; c % 8 && c < माप(काष्ठा mailbox); c++) अणु
				prपूर्णांकk(" %2.2X", ((अचिन्हित अक्षर *) &पंचांगpmailbox)[c]);
			पूर्ण
		पूर्ण

		prपूर्णांकk("\n");
#पूर्ण_अगर

	spin_lock_irqsave(&apbs[IndexCard].mutex, flags);

	/* Test octet पढ़ोy correct */
	अगर(पढ़ोb(apbs[IndexCard].RamIO + DATA_FROM_PC_READY) > 2) अणु 
		Dummy = पढ़ोb(apbs[IndexCard].RamIO + VERS);
		spin_unlock_irqrestore(&apbs[IndexCard].mutex, flags);
		prपूर्णांकk(KERN_WARNING "APPLICOM driver write error board %d, DataFromPcReady = %d\n",
		       IndexCard,(पूर्णांक)पढ़ोb(apbs[IndexCard].RamIO + DATA_FROM_PC_READY));
		DeviceErrorCount++;
		वापस -EIO;
	पूर्ण
	
	/* Place ourselves on the रुको queue */
	set_current_state(TASK_INTERRUPTIBLE);
	add_रुको_queue(&apbs[IndexCard].FlagSleepSend, &रुको);

	/* Check whether the card is पढ़ोy क्रम us */
	जबतक (पढ़ोb(apbs[IndexCard].RamIO + DATA_FROM_PC_READY) != 0) अणु
		Dummy = पढ़ोb(apbs[IndexCard].RamIO + VERS);
		/* It's busy. Sleep. */

		spin_unlock_irqrestore(&apbs[IndexCard].mutex, flags);
		schedule();
		अगर (संकेत_pending(current)) अणु
			हटाओ_रुको_queue(&apbs[IndexCard].FlagSleepSend,
					  &रुको);
			वापस -EINTR;
		पूर्ण
		spin_lock_irqsave(&apbs[IndexCard].mutex, flags);
		set_current_state(TASK_INTERRUPTIBLE);
	पूर्ण

	/* We may not have actually slept */
	set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&apbs[IndexCard].FlagSleepSend, &रुको);

	ग_लिखोb(1, apbs[IndexCard].RamIO + DATA_FROM_PC_READY);

	/* Which is best - lock करोwn the pages with rawio and then
	   copy directly, or use bounce buffers? For now we करो the latter 
	   because it works with 2.2 still */
	अणु
		अचिन्हित अक्षर *from = (अचिन्हित अक्षर *) &पंचांगpmailbox;
		व्योम __iomem *to = apbs[IndexCard].RamIO + RAM_FROM_PC;
		पूर्णांक c;

		क्रम (c = 0; c < माप(काष्ठा mailbox); c++)
			ग_लिखोb(*(from++), to++);
	पूर्ण

	ग_लिखोb(0x20, apbs[IndexCard].RamIO + TIC_OWNER_FROM_PC);
	ग_लिखोb(0xff, apbs[IndexCard].RamIO + NUMCARD_OWNER_FROM_PC);
	ग_लिखोb(TicCard, apbs[IndexCard].RamIO + TIC_DES_FROM_PC);
	ग_लिखोb(NumCard, apbs[IndexCard].RamIO + NUMCARD_DES_FROM_PC);
	ग_लिखोb(2, apbs[IndexCard].RamIO + DATA_FROM_PC_READY);
	ग_लिखोb(1, apbs[IndexCard].RamIO + RAM_IT_FROM_PC);
	Dummy = पढ़ोb(apbs[IndexCard].RamIO + VERS);
	spin_unlock_irqrestore(&apbs[IndexCard].mutex, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक करो_ac_पढ़ो(पूर्णांक IndexCard, अक्षर __user *buf,
		काष्ठा st_ram_io *st_loc, काष्ठा mailbox *mailbox)
अणु
	व्योम __iomem *from = apbs[IndexCard].RamIO + RAM_TO_PC;
	अचिन्हित अक्षर *to = (अचिन्हित अक्षर *)mailbox;
#अगर_घोषित DEBUG
	पूर्णांक c;
#पूर्ण_अगर

	st_loc->tic_owner_to_pc = पढ़ोb(apbs[IndexCard].RamIO + TIC_OWNER_TO_PC);
	st_loc->numcard_owner_to_pc = पढ़ोb(apbs[IndexCard].RamIO + NUMCARD_OWNER_TO_PC);


	अणु
		पूर्णांक c;

		क्रम (c = 0; c < माप(काष्ठा mailbox); c++)
			*(to++) = पढ़ोb(from++);
	पूर्ण
	ग_लिखोb(1, apbs[IndexCard].RamIO + ACK_FROM_PC_READY);
	ग_लिखोb(1, apbs[IndexCard].RamIO + TYP_ACK_FROM_PC);
	ग_लिखोb(IndexCard+1, apbs[IndexCard].RamIO + NUMCARD_ACK_FROM_PC);
	ग_लिखोb(पढ़ोb(apbs[IndexCard].RamIO + TIC_OWNER_TO_PC), 
	       apbs[IndexCard].RamIO + TIC_ACK_FROM_PC);
	ग_लिखोb(2, apbs[IndexCard].RamIO + ACK_FROM_PC_READY);
	ग_लिखोb(0, apbs[IndexCard].RamIO + DATA_TO_PC_READY);
	ग_लिखोb(2, apbs[IndexCard].RamIO + RAM_IT_FROM_PC);
	Dummy = पढ़ोb(apbs[IndexCard].RamIO + VERS);

#अगर_घोषित DEBUG
		prपूर्णांकk("Read from applicom card #%d. struct st_ram_io follows:", NumCard);

		क्रम (c = 0; c < माप(काष्ठा st_ram_io);) अणु
			prपूर्णांकk("\n%5.5X: %2.2X", c, ((अचिन्हित अक्षर *)st_loc)[c]);

			क्रम (c++; c % 8 && c < माप(काष्ठा st_ram_io); c++) अणु
				prपूर्णांकk(" %2.2X", ((अचिन्हित अक्षर *)st_loc)[c]);
			पूर्ण
		पूर्ण

		prपूर्णांकk("\nstruct mailbox follows:");

		क्रम (c = 0; c < माप(काष्ठा mailbox);) अणु
			prपूर्णांकk("\n%5.5X: %2.2X", c, ((अचिन्हित अक्षर *)mailbox)[c]);

			क्रम (c++; c % 8 && c < माप(काष्ठा mailbox); c++) अणु
				prपूर्णांकk(" %2.2X", ((अचिन्हित अक्षर *)mailbox)[c]);
			पूर्ण
		पूर्ण
		prपूर्णांकk("\n");
#पूर्ण_अगर
	वापस (माप(काष्ठा st_ram_io) + माप(काष्ठा mailbox));
पूर्ण

अटल sमाप_प्रकार ac_पढ़ो (काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count, loff_t *ptr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;
	अचिन्हित अक्षर पंचांगp;
	पूर्णांक ret = 0;
	DECLARE_WAITQUEUE(रुको, current);
#अगर_घोषित DEBUG
	पूर्णांक loopcount=0;
#पूर्ण_अगर
	/* No need to ratelimit this. Only root can trigger it anyway */
	अगर (count != माप(काष्ठा st_ram_io) + माप(काष्ठा mailbox)) अणु
		prपूर्णांकk( KERN_WARNING "Hmmm. read() of Applicom card, length %zd != expected %zd\n",
			count,माप(काष्ठा st_ram_io) + माप(काष्ठा mailbox));
		वापस -EINVAL;
	पूर्ण
	
	जबतक(1) अणु
		/* Stick ourself on the रुको queue */
		set_current_state(TASK_INTERRUPTIBLE);
		add_रुको_queue(&FlagSleepRec, &रुको);
		
		/* Scan each board, looking क्रम one which has a packet क्रम us */
		क्रम (i=0; i < MAX_BOARD; i++) अणु
			अगर (!apbs[i].RamIO)
				जारी;
			spin_lock_irqsave(&apbs[i].mutex, flags);
			
			पंचांगp = पढ़ोb(apbs[i].RamIO + DATA_TO_PC_READY);
			
			अगर (पंचांगp == 2) अणु
				काष्ठा st_ram_io st_loc;
				काष्ठा mailbox mailbox;

				/* Got a packet क्रम us */
				स_रखो(&st_loc, 0, माप(st_loc));
				ret = करो_ac_पढ़ो(i, buf, &st_loc, &mailbox);
				spin_unlock_irqrestore(&apbs[i].mutex, flags);
				set_current_state(TASK_RUNNING);
				हटाओ_रुको_queue(&FlagSleepRec, &रुको);

				अगर (copy_to_user(buf, &st_loc, माप(st_loc)))
					वापस -EFAULT;
				अगर (copy_to_user(buf + माप(st_loc), &mailbox, माप(mailbox)))
					वापस -EFAULT;
				वापस पंचांगp;
			पूर्ण
			
			अगर (पंचांगp > 2) अणु
				/* Got an error */
				Dummy = पढ़ोb(apbs[i].RamIO + VERS);
				
				spin_unlock_irqrestore(&apbs[i].mutex, flags);
				set_current_state(TASK_RUNNING);
				हटाओ_रुको_queue(&FlagSleepRec, &रुको);
				
				prपूर्णांकk(KERN_WARNING "APPLICOM driver read error board %d, DataToPcReady = %d\n",
				       i,(पूर्णांक)पढ़ोb(apbs[i].RamIO + DATA_TO_PC_READY));
				DeviceErrorCount++;
				वापस -EIO;
			पूर्ण
			
			/* Nothing क्रम us. Try the next board */
			Dummy = पढ़ोb(apbs[i].RamIO + VERS);
			spin_unlock_irqrestore(&apbs[i].mutex, flags);
			
		पूर्ण /* per board */

		/* OK - No boards had data क्रम us. Sleep now */

		schedule();
		हटाओ_रुको_queue(&FlagSleepRec, &रुको);

		अगर (संकेत_pending(current))
			वापस -EINTR;

#अगर_घोषित DEBUG
		अगर (loopcount++ > 2) अणु
			prपूर्णांकk(KERN_DEBUG "Looping in ac_read. loopcount %d\n", loopcount);
		पूर्ण
#पूर्ण_अगर
	पूर्ण 
पूर्ण

अटल irqवापस_t ac_पूर्णांकerrupt(पूर्णांक vec, व्योम *dev_instance)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक FlagInt;
	अचिन्हित पूर्णांक LoopCount;
	पूर्णांक handled = 0;

	//    prपूर्णांकk("Applicom interrupt on IRQ %d occurred\n", vec);

	LoopCount = 0;

	करो अणु
		FlagInt = 0;
		क्रम (i = 0; i < MAX_BOARD; i++) अणु
			
			/* Skip अगर this board करोesn't exist */
			अगर (!apbs[i].RamIO)
				जारी;

			spin_lock(&apbs[i].mutex);

			/* Skip अगर this board करोesn't want attention */
			अगर(पढ़ोb(apbs[i].RamIO + RAM_IT_TO_PC) == 0) अणु
				spin_unlock(&apbs[i].mutex);
				जारी;
			पूर्ण

			handled = 1;
			FlagInt = 1;
			ग_लिखोb(0, apbs[i].RamIO + RAM_IT_TO_PC);

			अगर (पढ़ोb(apbs[i].RamIO + DATA_TO_PC_READY) > 2) अणु
				prपूर्णांकk(KERN_WARNING "APPLICOM driver interrupt err board %d, DataToPcReady = %d\n",
				       i+1,(पूर्णांक)पढ़ोb(apbs[i].RamIO + DATA_TO_PC_READY));
				DeviceErrorCount++;
			पूर्ण

			अगर((पढ़ोb(apbs[i].RamIO + DATA_FROM_PC_READY) > 2) && 
			   (पढ़ोb(apbs[i].RamIO + DATA_FROM_PC_READY) != 6)) अणु
				
				prपूर्णांकk(KERN_WARNING "APPLICOM driver interrupt err board %d, DataFromPcReady = %d\n",
				       i+1,(पूर्णांक)पढ़ोb(apbs[i].RamIO + DATA_FROM_PC_READY));
				DeviceErrorCount++;
			पूर्ण

			अगर (पढ़ोb(apbs[i].RamIO + DATA_TO_PC_READY) == 2) अणु	/* mailbox sent by the card ?   */
				अगर (रुकोqueue_active(&FlagSleepRec)) अणु
				wake_up_पूर्णांकerruptible(&FlagSleepRec);
			पूर्ण
			पूर्ण

			अगर (पढ़ोb(apbs[i].RamIO + DATA_FROM_PC_READY) == 0) अणु	/* ram i/o मुक्त क्रम ग_लिखो by pc ? */
				अगर (रुकोqueue_active(&apbs[i].FlagSleepSend)) अणु	/* process sleep during पढ़ो ?    */
					wake_up_पूर्णांकerruptible(&apbs[i].FlagSleepSend);
				पूर्ण
			पूर्ण
			Dummy = पढ़ोb(apbs[i].RamIO + VERS);

			अगर(पढ़ोb(apbs[i].RamIO + RAM_IT_TO_PC)) अणु
				/* There's another पूर्णांक रुकोing on this card */
				spin_unlock(&apbs[i].mutex);
				i--;
			पूर्ण अन्यथा अणु
				spin_unlock(&apbs[i].mutex);
			पूर्ण
		पूर्ण
		अगर (FlagInt)
			LoopCount = 0;
		अन्यथा
			LoopCount++;
	पूर्ण जबतक(LoopCount < 2);
	वापस IRQ_RETVAL(handled);
पूर्ण



अटल दीर्घ ac_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
     
अणु				/* @ ADG ou ATO selon le cas */
	पूर्णांक i;
	अचिन्हित अक्षर IndexCard;
	व्योम __iomem *pmem;
	पूर्णांक ret = 0;
	अटल पूर्णांक warncount = 10;
	अस्थिर अचिन्हित अक्षर byte_reset_it;
	काष्ठा st_ram_io *adgl;
	व्योम __user *argp = (व्योम __user *)arg;

	/* In general, the device is only खोलोable by root anyway, so we're not
	   particularly concerned that bogus ioctls can flood the console. */

	adgl = memdup_user(argp, माप(काष्ठा st_ram_io));
	अगर (IS_ERR(adgl))
		वापस PTR_ERR(adgl);

	mutex_lock(&ac_mutex);	
	IndexCard = adgl->num_card-1;
	 
	अगर (cmd != 6 && IndexCard >= MAX_BOARD)
		जाओ err;
	IndexCard = array_index_nospec(IndexCard, MAX_BOARD);

	अगर (cmd != 6 && !apbs[IndexCard].RamIO)
		जाओ err;

	चयन (cmd) अणु
		
	हाल 0:
		pmem = apbs[IndexCard].RamIO;
		क्रम (i = 0; i < माप(काष्ठा st_ram_io); i++)
			((अचिन्हित अक्षर *)adgl)[i]=पढ़ोb(pmem++);
		अगर (copy_to_user(argp, adgl, माप(काष्ठा st_ram_io)))
			ret = -EFAULT;
		अवरोध;
	हाल 1:
		pmem = apbs[IndexCard].RamIO + CONF_END_TEST;
		क्रम (i = 0; i < 4; i++)
			adgl->conf_end_test[i] = पढ़ोb(pmem++);
		क्रम (i = 0; i < 2; i++)
			adgl->error_code[i] = पढ़ोb(pmem++);
		क्रम (i = 0; i < 4; i++)
			adgl->parameter_error[i] = पढ़ोb(pmem++);
		pmem = apbs[IndexCard].RamIO + VERS;
		adgl->vers = पढ़ोb(pmem);
		pmem = apbs[IndexCard].RamIO + TYPE_CARD;
		क्रम (i = 0; i < 20; i++)
			adgl->reserv1[i] = पढ़ोb(pmem++);
		*(पूर्णांक *)&adgl->reserv1[20] =  
			(पढ़ोb(apbs[IndexCard].RamIO + SERIAL_NUMBER) << 16) + 
			(पढ़ोb(apbs[IndexCard].RamIO + SERIAL_NUMBER + 1) << 8) + 
			(पढ़ोb(apbs[IndexCard].RamIO + SERIAL_NUMBER + 2) );

		अगर (copy_to_user(argp, adgl, माप(काष्ठा st_ram_io)))
			ret = -EFAULT;
		अवरोध;
	हाल 2:
		pmem = apbs[IndexCard].RamIO + CONF_END_TEST;
		क्रम (i = 0; i < 10; i++)
			ग_लिखोb(0xff, pmem++);
		ग_लिखोb(adgl->data_from_pc_पढ़ोy, 
		       apbs[IndexCard].RamIO + DATA_FROM_PC_READY);

		ग_लिखोb(1, apbs[IndexCard].RamIO + RAM_IT_FROM_PC);
		
		क्रम (i = 0; i < MAX_BOARD; i++) अणु
			अगर (apbs[i].RamIO) अणु
				byte_reset_it = पढ़ोb(apbs[i].RamIO + RAM_IT_TO_PC);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल 3:
		pmem = apbs[IndexCard].RamIO + TIC_DES_FROM_PC;
		ग_लिखोb(adgl->tic_des_from_pc, pmem);
		अवरोध;
	हाल 4:
		pmem = apbs[IndexCard].RamIO + TIC_OWNER_TO_PC;
		adgl->tic_owner_to_pc     = पढ़ोb(pmem++);
		adgl->numcard_owner_to_pc = पढ़ोb(pmem);
		अगर (copy_to_user(argp, adgl,माप(काष्ठा st_ram_io)))
			ret = -EFAULT;
		अवरोध;
	हाल 5:
		ग_लिखोb(adgl->num_card, apbs[IndexCard].RamIO + NUMCARD_OWNER_TO_PC);
		ग_लिखोb(adgl->num_card, apbs[IndexCard].RamIO + NUMCARD_DES_FROM_PC);
		ग_लिखोb(adgl->num_card, apbs[IndexCard].RamIO + NUMCARD_ACK_FROM_PC);
		ग_लिखोb(4, apbs[IndexCard].RamIO + DATA_FROM_PC_READY);
		ग_लिखोb(1, apbs[IndexCard].RamIO + RAM_IT_FROM_PC);
		अवरोध;
	हाल 6:
		prपूर्णांकk(KERN_INFO "APPLICOM driver release .... V2.8.0 ($Revision: 1.30 $)\n");
		prपूर्णांकk(KERN_INFO "Number of installed boards . %d\n", (पूर्णांक) numboards);
		prपूर्णांकk(KERN_INFO "Segment of board ........... %X\n", (पूर्णांक) mem);
		prपूर्णांकk(KERN_INFO "Interrupt IRQ number ....... %d\n", (पूर्णांक) irq);
		क्रम (i = 0; i < MAX_BOARD; i++) अणु
			पूर्णांक serial;
			अक्षर boardname[(SERIAL_NUMBER - TYPE_CARD) + 1];

			अगर (!apbs[i].RamIO)
				जारी;

			क्रम (serial = 0; serial < SERIAL_NUMBER - TYPE_CARD; serial++)
				boardname[serial] = पढ़ोb(apbs[i].RamIO + TYPE_CARD + serial);
			boardname[serial] = 0;

			prपूर्णांकk(KERN_INFO "Prom version board %d ....... V%d.%d %s",
			       i+1,
			       (पूर्णांक)(पढ़ोb(apbs[i].RamIO + VERS) >> 4),
			       (पूर्णांक)(पढ़ोb(apbs[i].RamIO + VERS) & 0xF),
			       boardname);


			serial = (पढ़ोb(apbs[i].RamIO + SERIAL_NUMBER) << 16) + 
				(पढ़ोb(apbs[i].RamIO + SERIAL_NUMBER + 1) << 8) + 
				(पढ़ोb(apbs[i].RamIO + SERIAL_NUMBER + 2) );

			अगर (serial != 0)
				prपूर्णांकk(" S/N %d\n", serial);
			अन्यथा
				prपूर्णांकk("\n");
		पूर्ण
		अगर (DeviceErrorCount != 0)
			prपूर्णांकk(KERN_INFO "DeviceErrorCount ........... %d\n", DeviceErrorCount);
		अगर (ReadErrorCount != 0)
			prपूर्णांकk(KERN_INFO "ReadErrorCount ............. %d\n", ReadErrorCount);
		अगर (WriteErrorCount != 0)
			prपूर्णांकk(KERN_INFO "WriteErrorCount ............ %d\n", WriteErrorCount);
		अगर (रुकोqueue_active(&FlagSleepRec))
			prपूर्णांकk(KERN_INFO "Process in read pending\n");
		क्रम (i = 0; i < MAX_BOARD; i++) अणु
			अगर (apbs[i].RamIO && रुकोqueue_active(&apbs[i].FlagSleepSend))
				prपूर्णांकk(KERN_INFO "Process in write pending board %d\n",i+1);
		पूर्ण
		अवरोध;
	शेष:
		ret = -ENOTTY;
		अवरोध;
	पूर्ण
	Dummy = पढ़ोb(apbs[IndexCard].RamIO + VERS);
	kमुक्त(adgl);
	mutex_unlock(&ac_mutex);
	वापस ret;

err:
	अगर (warncount) अणु
		pr_warn("APPLICOM driver IOCTL, bad board number %d\n",
			(पूर्णांक)IndexCard + 1);
		warncount--;
	पूर्ण
	kमुक्त(adgl);
	mutex_unlock(&ac_mutex);
	वापस -EINVAL;

पूर्ण

