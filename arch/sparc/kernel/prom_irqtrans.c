<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/upa.h>

#समावेश "prom.h"

#अगर_घोषित CONFIG_PCI
/* PSYCHO पूर्णांकerrupt mapping support. */
#घोषणा PSYCHO_IMAP_A_SLOT0	0x0c00UL
#घोषणा PSYCHO_IMAP_B_SLOT0	0x0c20UL
अटल अचिन्हित दीर्घ psycho_pcislot_imap_offset(अचिन्हित दीर्घ ino)
अणु
	अचिन्हित पूर्णांक bus =  (ino & 0x10) >> 4;
	अचिन्हित पूर्णांक slot = (ino & 0x0c) >> 2;

	अगर (bus == 0)
		वापस PSYCHO_IMAP_A_SLOT0 + (slot * 8);
	अन्यथा
		वापस PSYCHO_IMAP_B_SLOT0 + (slot * 8);
पूर्ण

#घोषणा PSYCHO_OBIO_IMAP_BASE	0x1000UL

#घोषणा PSYCHO_ONBOARD_IRQ_BASE		0x20
#घोषणा psycho_onboard_imap_offset(__ino) \
	(PSYCHO_OBIO_IMAP_BASE + (((__ino) & 0x1f) << 3))

#घोषणा PSYCHO_ICLR_A_SLOT0	0x1400UL
#घोषणा PSYCHO_ICLR_SCSI	0x1800UL

#घोषणा psycho_iclr_offset(ino)					      \
	((ino & 0x20) ? (PSYCHO_ICLR_SCSI + (((ino) & 0x1f) << 3)) :  \
			(PSYCHO_ICLR_A_SLOT0 + (((ino) & 0x1f)<<3)))

अटल अचिन्हित पूर्णांक psycho_irq_build(काष्ठा device_node *dp,
				     अचिन्हित पूर्णांक ino,
				     व्योम *_data)
अणु
	अचिन्हित दीर्घ controller_regs = (अचिन्हित दीर्घ) _data;
	अचिन्हित दीर्घ imap, iclr;
	अचिन्हित दीर्घ imap_off, iclr_off;
	पूर्णांक inofixup = 0;

	ino &= 0x3f;
	अगर (ino < PSYCHO_ONBOARD_IRQ_BASE) अणु
		/* PCI slot */
		imap_off = psycho_pcislot_imap_offset(ino);
	पूर्ण अन्यथा अणु
		/* Onboard device */
		imap_off = psycho_onboard_imap_offset(ino);
	पूर्ण

	/* Now build the IRQ bucket. */
	imap = controller_regs + imap_off;

	iclr_off = psycho_iclr_offset(ino);
	iclr = controller_regs + iclr_off;

	अगर ((ino & 0x20) == 0)
		inofixup = ino & 0x03;

	वापस build_irq(inofixup, iclr, imap);
पूर्ण

अटल व्योम __init psycho_irq_trans_init(काष्ठा device_node *dp)
अणु
	स्थिर काष्ठा linux_prom64_रेजिस्टरs *regs;

	dp->irq_trans = prom_early_alloc(माप(काष्ठा of_irq_controller));
	dp->irq_trans->irq_build = psycho_irq_build;

	regs = of_get_property(dp, "reg", शून्य);
	dp->irq_trans->data = (व्योम *) regs[2].phys_addr;
पूर्ण

#घोषणा sabre_पढ़ो(__reg) \
(अणु	u64 __ret; \
	__यंत्र__ __अस्थिर__("ldxa [%1] %2, %0" \
			     : "=r" (__ret) \
			     : "r" (__reg), "i" (ASI_PHYS_BYPASS_EC_E) \
			     : "memory"); \
	__ret; \
पूर्ण)

काष्ठा sabre_irq_data अणु
	अचिन्हित दीर्घ controller_regs;
	अचिन्हित पूर्णांक pci_first_busno;
पूर्ण;
#घोषणा SABRE_CONFIGSPACE	0x001000000UL
#घोषणा SABRE_WRSYNC		0x1c20UL

#घोषणा SABRE_CONFIG_BASE(CONFIG_SPACE)	\
	(CONFIG_SPACE | (1UL << 24))
#घोषणा SABRE_CONFIG_ENCODE(BUS, DEVFN, REG)	\
	(((अचिन्हित दीर्घ)(BUS)   << 16) |	\
	 ((अचिन्हित दीर्घ)(DEVFN) << 8)  |	\
	 ((अचिन्हित दीर्घ)(REG)))

/* When a device lives behind a bridge deeper in the PCI bus topology
 * than APB, a special sequence must run to make sure all pending DMA
 * transfers at the समय of IRQ delivery are visible in the coherency
 * करोमुख्य by the cpu.  This sequence is to perक्रमm a पढ़ो on the far
 * side of the non-APB bridge, then perक्रमm a पढ़ो of Sabre's DMA
 * ग_लिखो-sync रेजिस्टर.
 */
अटल व्योम sabre_wsync_handler(अचिन्हित पूर्णांक ino, व्योम *_arg1, व्योम *_arg2)
अणु
	अचिन्हित पूर्णांक phys_hi = (अचिन्हित पूर्णांक) (अचिन्हित दीर्घ) _arg1;
	काष्ठा sabre_irq_data *irq_data = _arg2;
	अचिन्हित दीर्घ controller_regs = irq_data->controller_regs;
	अचिन्हित दीर्घ sync_reg = controller_regs + SABRE_WRSYNC;
	अचिन्हित दीर्घ config_space = controller_regs + SABRE_CONFIGSPACE;
	अचिन्हित पूर्णांक bus, devfn;
	u16 _unused;

	config_space = SABRE_CONFIG_BASE(config_space);

	bus = (phys_hi >> 16) & 0xff;
	devfn = (phys_hi >> 8) & 0xff;

	config_space |= SABRE_CONFIG_ENCODE(bus, devfn, 0x00);

	__यंत्र__ __अस्थिर__("membar #Sync\n\t"
			     "lduha [%1] %2, %0\n\t"
			     "membar #Sync"
			     : "=r" (_unused)
			     : "r" ((u16 *) config_space),
			       "i" (ASI_PHYS_BYPASS_EC_E_L)
			     : "memory");

	sabre_पढ़ो(sync_reg);
पूर्ण

#घोषणा SABRE_IMAP_A_SLOT0	0x0c00UL
#घोषणा SABRE_IMAP_B_SLOT0	0x0c20UL
#घोषणा SABRE_ICLR_A_SLOT0	0x1400UL
#घोषणा SABRE_ICLR_B_SLOT0	0x1480UL
#घोषणा SABRE_ICLR_SCSI		0x1800UL
#घोषणा SABRE_ICLR_ETH		0x1808UL
#घोषणा SABRE_ICLR_BPP		0x1810UL
#घोषणा SABRE_ICLR_AU_REC	0x1818UL
#घोषणा SABRE_ICLR_AU_PLAY	0x1820UL
#घोषणा SABRE_ICLR_PFAIL	0x1828UL
#घोषणा SABRE_ICLR_KMS		0x1830UL
#घोषणा SABRE_ICLR_FLPY		0x1838UL
#घोषणा SABRE_ICLR_SHW		0x1840UL
#घोषणा SABRE_ICLR_KBD		0x1848UL
#घोषणा SABRE_ICLR_MS		0x1850UL
#घोषणा SABRE_ICLR_SER		0x1858UL
#घोषणा SABRE_ICLR_UE		0x1870UL
#घोषणा SABRE_ICLR_CE		0x1878UL
#घोषणा SABRE_ICLR_PCIERR	0x1880UL

अटल अचिन्हित दीर्घ sabre_pcislot_imap_offset(अचिन्हित दीर्घ ino)
अणु
	अचिन्हित पूर्णांक bus =  (ino & 0x10) >> 4;
	अचिन्हित पूर्णांक slot = (ino & 0x0c) >> 2;

	अगर (bus == 0)
		वापस SABRE_IMAP_A_SLOT0 + (slot * 8);
	अन्यथा
		वापस SABRE_IMAP_B_SLOT0 + (slot * 8);
पूर्ण

#घोषणा SABRE_OBIO_IMAP_BASE	0x1000UL
#घोषणा SABRE_ONBOARD_IRQ_BASE	0x20
#घोषणा sabre_onboard_imap_offset(__ino) \
	(SABRE_OBIO_IMAP_BASE + (((__ino) & 0x1f) << 3))

#घोषणा sabre_iclr_offset(ino)					      \
	((ino & 0x20) ? (SABRE_ICLR_SCSI + (((ino) & 0x1f) << 3)) :  \
			(SABRE_ICLR_A_SLOT0 + (((ino) & 0x1f)<<3)))

अटल पूर्णांक sabre_device_needs_wsync(काष्ठा device_node *dp)
अणु
	काष्ठा device_node *parent = dp->parent;
	स्थिर अक्षर *parent_model, *parent_compat;

	/* This traversal up towards the root is meant to
	 * handle two हालs:
	 *
	 * 1) non-PCI bus sitting under PCI, such as 'ebus'
	 * 2) the PCI controller पूर्णांकerrupts themselves, which
	 *    will use the sabre_irq_build but करो not need
	 *    the DMA synchronization handling
	 */
	जबतक (parent) अणु
		अगर (of_node_is_type(parent, "pci"))
			अवरोध;
		parent = parent->parent;
	पूर्ण

	अगर (!parent)
		वापस 0;

	parent_model = of_get_property(parent,
				       "model", शून्य);
	अगर (parent_model &&
	    (!म_भेद(parent_model, "SUNW,sabre") ||
	     !म_भेद(parent_model, "SUNW,simba")))
		वापस 0;

	parent_compat = of_get_property(parent,
					"compatible", शून्य);
	अगर (parent_compat &&
	    (!म_भेद(parent_compat, "pci108e,a000") ||
	     !म_भेद(parent_compat, "pci108e,a001")))
		वापस 0;

	वापस 1;
पूर्ण

अटल अचिन्हित पूर्णांक sabre_irq_build(काष्ठा device_node *dp,
				    अचिन्हित पूर्णांक ino,
				    व्योम *_data)
अणु
	काष्ठा sabre_irq_data *irq_data = _data;
	अचिन्हित दीर्घ controller_regs = irq_data->controller_regs;
	स्थिर काष्ठा linux_prom_pci_रेजिस्टरs *regs;
	अचिन्हित दीर्घ imap, iclr;
	अचिन्हित दीर्घ imap_off, iclr_off;
	पूर्णांक inofixup = 0;
	पूर्णांक irq;

	ino &= 0x3f;
	अगर (ino < SABRE_ONBOARD_IRQ_BASE) अणु
		/* PCI slot */
		imap_off = sabre_pcislot_imap_offset(ino);
	पूर्ण अन्यथा अणु
		/* onboard device */
		imap_off = sabre_onboard_imap_offset(ino);
	पूर्ण

	/* Now build the IRQ bucket. */
	imap = controller_regs + imap_off;

	iclr_off = sabre_iclr_offset(ino);
	iclr = controller_regs + iclr_off;

	अगर ((ino & 0x20) == 0)
		inofixup = ino & 0x03;

	irq = build_irq(inofixup, iclr, imap);

	/* If the parent device is a PCI<->PCI bridge other than
	 * APB, we have to install a pre-handler to ensure that
	 * all pending DMA is drained beक्रमe the पूर्णांकerrupt handler
	 * is run.
	 */
	regs = of_get_property(dp, "reg", शून्य);
	अगर (regs && sabre_device_needs_wsync(dp)) अणु
		irq_install_pre_handler(irq,
					sabre_wsync_handler,
					(व्योम *) (दीर्घ) regs->phys_hi,
					(व्योम *) irq_data);
	पूर्ण

	वापस irq;
पूर्ण

अटल व्योम __init sabre_irq_trans_init(काष्ठा device_node *dp)
अणु
	स्थिर काष्ठा linux_prom64_रेजिस्टरs *regs;
	काष्ठा sabre_irq_data *irq_data;
	स्थिर u32 *busrange;

	dp->irq_trans = prom_early_alloc(माप(काष्ठा of_irq_controller));
	dp->irq_trans->irq_build = sabre_irq_build;

	irq_data = prom_early_alloc(माप(काष्ठा sabre_irq_data));

	regs = of_get_property(dp, "reg", शून्य);
	irq_data->controller_regs = regs[0].phys_addr;

	busrange = of_get_property(dp, "bus-range", शून्य);
	irq_data->pci_first_busno = busrange[0];

	dp->irq_trans->data = irq_data;
पूर्ण

/* SCHIZO पूर्णांकerrupt mapping support.  Unlike Psycho, क्रम this controller the
 * imap/iclr रेजिस्टरs are per-PBM.
 */
#घोषणा SCHIZO_IMAP_BASE	0x1000UL
#घोषणा SCHIZO_ICLR_BASE	0x1400UL

अटल अचिन्हित दीर्घ schizo_imap_offset(अचिन्हित दीर्घ ino)
अणु
	वापस SCHIZO_IMAP_BASE + (ino * 8UL);
पूर्ण

अटल अचिन्हित दीर्घ schizo_iclr_offset(अचिन्हित दीर्घ ino)
अणु
	वापस SCHIZO_ICLR_BASE + (ino * 8UL);
पूर्ण

अटल अचिन्हित दीर्घ schizo_ino_to_iclr(अचिन्हित दीर्घ pbm_regs,
					अचिन्हित पूर्णांक ino)
अणु

	वापस pbm_regs + schizo_iclr_offset(ino);
पूर्ण

अटल अचिन्हित दीर्घ schizo_ino_to_imap(अचिन्हित दीर्घ pbm_regs,
					अचिन्हित पूर्णांक ino)
अणु
	वापस pbm_regs + schizo_imap_offset(ino);
पूर्ण

#घोषणा schizo_पढ़ो(__reg) \
(अणु	u64 __ret; \
	__यंत्र__ __अस्थिर__("ldxa [%1] %2, %0" \
			     : "=r" (__ret) \
			     : "r" (__reg), "i" (ASI_PHYS_BYPASS_EC_E) \
			     : "memory"); \
	__ret; \
पूर्ण)
#घोषणा schizo_ग_लिखो(__reg, __val) \
	__यंत्र__ __अस्थिर__("stxa %0, [%1] %2" \
			     : /* no outमाला_दो */ \
			     : "r" (__val), "r" (__reg), \
			       "i" (ASI_PHYS_BYPASS_EC_E) \
			     : "memory")

अटल व्योम tomatillo_wsync_handler(अचिन्हित पूर्णांक ino, व्योम *_arg1, व्योम *_arg2)
अणु
	अचिन्हित दीर्घ sync_reg = (अचिन्हित दीर्घ) _arg2;
	u64 mask = 1UL << (ino & IMAP_INO);
	u64 val;
	पूर्णांक limit;

	schizo_ग_लिखो(sync_reg, mask);

	limit = 100000;
	val = 0;
	जबतक (--limit) अणु
		val = schizo_पढ़ो(sync_reg);
		अगर (!(val & mask))
			अवरोध;
	पूर्ण
	अगर (limit <= 0) अणु
		prपूर्णांकk("tomatillo_wsync_handler: DMA won't sync [%llx:%llx]\n",
		       val, mask);
	पूर्ण

	अगर (_arg1) अणु
		अटल अचिन्हित अक्षर cacheline[64]
			__attribute__ ((aligned (64)));

		__यंत्र__ __अस्थिर__("rd %%fprs, %0\n\t"
				     "or %0, %4, %1\n\t"
				     "wr %1, 0x0, %%fprs\n\t"
				     "stda %%f0, [%5] %6\n\t"
				     "wr %0, 0x0, %%fprs\n\t"
				     "membar #Sync"
				     : "=&r" (mask), "=&r" (val)
				     : "0" (mask), "1" (val),
				     "i" (FPRS_FEF), "r" (&cacheline[0]),
				     "i" (ASI_BLK_COMMIT_P));
	पूर्ण
पूर्ण

काष्ठा schizo_irq_data अणु
	अचिन्हित दीर्घ pbm_regs;
	अचिन्हित दीर्घ sync_reg;
	u32 portid;
	पूर्णांक chip_version;
पूर्ण;

अटल अचिन्हित पूर्णांक schizo_irq_build(काष्ठा device_node *dp,
				     अचिन्हित पूर्णांक ino,
				     व्योम *_data)
अणु
	काष्ठा schizo_irq_data *irq_data = _data;
	अचिन्हित दीर्घ pbm_regs = irq_data->pbm_regs;
	अचिन्हित दीर्घ imap, iclr;
	पूर्णांक ign_fixup;
	पूर्णांक irq;
	पूर्णांक is_tomatillo;

	ino &= 0x3f;

	/* Now build the IRQ bucket. */
	imap = schizo_ino_to_imap(pbm_regs, ino);
	iclr = schizo_ino_to_iclr(pbm_regs, ino);

	/* On Schizo, no inofixup occurs.  This is because each
	 * INO has it's own IMAP रेजिस्टर.  On Psycho and Sabre
	 * there is only one IMAP रेजिस्टर क्रम each PCI slot even
	 * though four dअगरferent INOs can be generated by each
	 * PCI slot.
	 *
	 * But, क्रम JBUS variants (essentially, Tomatillo), we have
	 * to fixup the lowest bit of the पूर्णांकerrupt group number.
	 */
	ign_fixup = 0;

	is_tomatillo = (irq_data->sync_reg != 0UL);

	अगर (is_tomatillo) अणु
		अगर (irq_data->portid & 1)
			ign_fixup = (1 << 6);
	पूर्ण

	irq = build_irq(ign_fixup, iclr, imap);

	अगर (is_tomatillo) अणु
		irq_install_pre_handler(irq,
					tomatillo_wsync_handler,
					((irq_data->chip_version <= 4) ?
					 (व्योम *) 1 : (व्योम *) 0),
					(व्योम *) irq_data->sync_reg);
	पूर्ण

	वापस irq;
पूर्ण

अटल व्योम __init __schizo_irq_trans_init(काष्ठा device_node *dp,
					   पूर्णांक is_tomatillo)
अणु
	स्थिर काष्ठा linux_prom64_रेजिस्टरs *regs;
	काष्ठा schizo_irq_data *irq_data;

	dp->irq_trans = prom_early_alloc(माप(काष्ठा of_irq_controller));
	dp->irq_trans->irq_build = schizo_irq_build;

	irq_data = prom_early_alloc(माप(काष्ठा schizo_irq_data));

	regs = of_get_property(dp, "reg", शून्य);
	dp->irq_trans->data = irq_data;

	irq_data->pbm_regs = regs[0].phys_addr;
	अगर (is_tomatillo)
		irq_data->sync_reg = regs[3].phys_addr + 0x1a18UL;
	अन्यथा
		irq_data->sync_reg = 0UL;
	irq_data->portid = of_getपूर्णांकprop_शेष(dp, "portid", 0);
	irq_data->chip_version = of_getपूर्णांकprop_शेष(dp, "version#", 0);
पूर्ण

अटल व्योम __init schizo_irq_trans_init(काष्ठा device_node *dp)
अणु
	__schizo_irq_trans_init(dp, 0);
पूर्ण

अटल व्योम __init tomatillo_irq_trans_init(काष्ठा device_node *dp)
अणु
	__schizo_irq_trans_init(dp, 1);
पूर्ण

अटल अचिन्हित पूर्णांक pci_sun4v_irq_build(काष्ठा device_node *dp,
					अचिन्हित पूर्णांक devino,
					व्योम *_data)
अणु
	u32 devhandle = (u32) (अचिन्हित दीर्घ) _data;

	वापस sun4v_build_irq(devhandle, devino);
पूर्ण

अटल व्योम __init pci_sun4v_irq_trans_init(काष्ठा device_node *dp)
अणु
	स्थिर काष्ठा linux_prom64_रेजिस्टरs *regs;

	dp->irq_trans = prom_early_alloc(माप(काष्ठा of_irq_controller));
	dp->irq_trans->irq_build = pci_sun4v_irq_build;

	regs = of_get_property(dp, "reg", शून्य);
	dp->irq_trans->data = (व्योम *) (अचिन्हित दीर्घ)
		((regs->phys_addr >> 32UL) & 0x0fffffff);
पूर्ण

काष्ठा fire_irq_data अणु
	अचिन्हित दीर्घ pbm_regs;
	u32 portid;
पूर्ण;

#घोषणा FIRE_IMAP_BASE	0x001000
#घोषणा FIRE_ICLR_BASE	0x001400

अटल अचिन्हित दीर्घ fire_imap_offset(अचिन्हित दीर्घ ino)
अणु
	वापस FIRE_IMAP_BASE + (ino * 8UL);
पूर्ण

अटल अचिन्हित दीर्घ fire_iclr_offset(अचिन्हित दीर्घ ino)
अणु
	वापस FIRE_ICLR_BASE + (ino * 8UL);
पूर्ण

अटल अचिन्हित दीर्घ fire_ino_to_iclr(अचिन्हित दीर्घ pbm_regs,
					    अचिन्हित पूर्णांक ino)
अणु
	वापस pbm_regs + fire_iclr_offset(ino);
पूर्ण

अटल अचिन्हित दीर्घ fire_ino_to_imap(अचिन्हित दीर्घ pbm_regs,
					    अचिन्हित पूर्णांक ino)
अणु
	वापस pbm_regs + fire_imap_offset(ino);
पूर्ण

अटल अचिन्हित पूर्णांक fire_irq_build(काष्ठा device_node *dp,
					 अचिन्हित पूर्णांक ino,
					 व्योम *_data)
अणु
	काष्ठा fire_irq_data *irq_data = _data;
	अचिन्हित दीर्घ pbm_regs = irq_data->pbm_regs;
	अचिन्हित दीर्घ imap, iclr;
	अचिन्हित दीर्घ पूर्णांक_ctrlr;

	ino &= 0x3f;

	/* Now build the IRQ bucket. */
	imap = fire_ino_to_imap(pbm_regs, ino);
	iclr = fire_ino_to_iclr(pbm_regs, ino);

	/* Set the पूर्णांकerrupt controller number.  */
	पूर्णांक_ctrlr = 1 << 6;
	upa_ग_लिखोq(पूर्णांक_ctrlr, imap);

	/* The पूर्णांकerrupt map रेजिस्टरs करो not have an INO field
	 * like other chips करो.  They वापस zero in the INO
	 * field, and the पूर्णांकerrupt controller number is controlled
	 * in bits 6 to 9.  So in order क्रम build_irq() to get
	 * the INO right we pass it in as part of the fixup
	 * which will get added to the map रेजिस्टर zero value
	 * पढ़ो by build_irq().
	 */
	ino |= (irq_data->portid << 6);
	ino -= पूर्णांक_ctrlr;
	वापस build_irq(ino, iclr, imap);
पूर्ण

अटल व्योम __init fire_irq_trans_init(काष्ठा device_node *dp)
अणु
	स्थिर काष्ठा linux_prom64_रेजिस्टरs *regs;
	काष्ठा fire_irq_data *irq_data;

	dp->irq_trans = prom_early_alloc(माप(काष्ठा of_irq_controller));
	dp->irq_trans->irq_build = fire_irq_build;

	irq_data = prom_early_alloc(माप(काष्ठा fire_irq_data));

	regs = of_get_property(dp, "reg", शून्य);
	dp->irq_trans->data = irq_data;

	irq_data->pbm_regs = regs[0].phys_addr;
	irq_data->portid = of_getपूर्णांकprop_शेष(dp, "portid", 0);
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI */

#अगर_घोषित CONFIG_SBUS
/* INO number to IMAP रेजिस्टर offset क्रम SYSIO बाह्यal IRQ's.
 * This should conक्रमm to both Sunfire/Wildfire server and Fusion
 * desktop designs.
 */
#घोषणा SYSIO_IMAP_SLOT0	0x2c00UL
#घोषणा SYSIO_IMAP_SLOT1	0x2c08UL
#घोषणा SYSIO_IMAP_SLOT2	0x2c10UL
#घोषणा SYSIO_IMAP_SLOT3	0x2c18UL
#घोषणा SYSIO_IMAP_SCSI		0x3000UL
#घोषणा SYSIO_IMAP_ETH		0x3008UL
#घोषणा SYSIO_IMAP_BPP		0x3010UL
#घोषणा SYSIO_IMAP_AUDIO	0x3018UL
#घोषणा SYSIO_IMAP_PFAIL	0x3020UL
#घोषणा SYSIO_IMAP_KMS		0x3028UL
#घोषणा SYSIO_IMAP_FLPY		0x3030UL
#घोषणा SYSIO_IMAP_SHW		0x3038UL
#घोषणा SYSIO_IMAP_KBD		0x3040UL
#घोषणा SYSIO_IMAP_MS		0x3048UL
#घोषणा SYSIO_IMAP_SER		0x3050UL
#घोषणा SYSIO_IMAP_TIM0		0x3060UL
#घोषणा SYSIO_IMAP_TIM1		0x3068UL
#घोषणा SYSIO_IMAP_UE		0x3070UL
#घोषणा SYSIO_IMAP_CE		0x3078UL
#घोषणा SYSIO_IMAP_SBERR	0x3080UL
#घोषणा SYSIO_IMAP_PMGMT	0x3088UL
#घोषणा SYSIO_IMAP_GFX		0x3090UL
#घोषणा SYSIO_IMAP_EUPA		0x3098UL

#घोषणा bogon     ((अचिन्हित दीर्घ) -1)
अटल अचिन्हित दीर्घ sysio_irq_offsets[] = अणु
	/* SBUS Slot 0 --> 3, level 1 --> 7 */
	SYSIO_IMAP_SLOT0, SYSIO_IMAP_SLOT0, SYSIO_IMAP_SLOT0, SYSIO_IMAP_SLOT0,
	SYSIO_IMAP_SLOT0, SYSIO_IMAP_SLOT0, SYSIO_IMAP_SLOT0, SYSIO_IMAP_SLOT0,
	SYSIO_IMAP_SLOT1, SYSIO_IMAP_SLOT1, SYSIO_IMAP_SLOT1, SYSIO_IMAP_SLOT1,
	SYSIO_IMAP_SLOT1, SYSIO_IMAP_SLOT1, SYSIO_IMAP_SLOT1, SYSIO_IMAP_SLOT1,
	SYSIO_IMAP_SLOT2, SYSIO_IMAP_SLOT2, SYSIO_IMAP_SLOT2, SYSIO_IMAP_SLOT2,
	SYSIO_IMAP_SLOT2, SYSIO_IMAP_SLOT2, SYSIO_IMAP_SLOT2, SYSIO_IMAP_SLOT2,
	SYSIO_IMAP_SLOT3, SYSIO_IMAP_SLOT3, SYSIO_IMAP_SLOT3, SYSIO_IMAP_SLOT3,
	SYSIO_IMAP_SLOT3, SYSIO_IMAP_SLOT3, SYSIO_IMAP_SLOT3, SYSIO_IMAP_SLOT3,

	/* Onboard devices (not relevant/used on SunFire). */
	SYSIO_IMAP_SCSI,
	SYSIO_IMAP_ETH,
	SYSIO_IMAP_BPP,
	bogon,
	SYSIO_IMAP_AUDIO,
	SYSIO_IMAP_PFAIL,
	bogon,
	bogon,
	SYSIO_IMAP_KMS,
	SYSIO_IMAP_FLPY,
	SYSIO_IMAP_SHW,
	SYSIO_IMAP_KBD,
	SYSIO_IMAP_MS,
	SYSIO_IMAP_SER,
	bogon,
	bogon,
	SYSIO_IMAP_TIM0,
	SYSIO_IMAP_TIM1,
	bogon,
	bogon,
	SYSIO_IMAP_UE,
	SYSIO_IMAP_CE,
	SYSIO_IMAP_SBERR,
	SYSIO_IMAP_PMGMT,
	SYSIO_IMAP_GFX,
	SYSIO_IMAP_EUPA,
पूर्ण;

#अघोषित bogon

#घोषणा NUM_SYSIO_OFFSETS ARRAY_SIZE(sysio_irq_offsets)

/* Convert Interrupt Mapping रेजिस्टर poपूर्णांकer to associated
 * Interrupt Clear रेजिस्टर poपूर्णांकer, SYSIO specअगरic version.
 */
#घोषणा SYSIO_ICLR_UNUSED0	0x3400UL
#घोषणा SYSIO_ICLR_SLOT0	0x3408UL
#घोषणा SYSIO_ICLR_SLOT1	0x3448UL
#घोषणा SYSIO_ICLR_SLOT2	0x3488UL
#घोषणा SYSIO_ICLR_SLOT3	0x34c8UL
अटल अचिन्हित दीर्घ sysio_imap_to_iclr(अचिन्हित दीर्घ imap)
अणु
	अचिन्हित दीर्घ dअगरf = SYSIO_ICLR_UNUSED0 - SYSIO_IMAP_SLOT0;
	वापस imap + dअगरf;
पूर्ण

अटल अचिन्हित पूर्णांक sbus_of_build_irq(काष्ठा device_node *dp,
				      अचिन्हित पूर्णांक ino,
				      व्योम *_data)
अणु
	अचिन्हित दीर्घ reg_base = (अचिन्हित दीर्घ) _data;
	स्थिर काष्ठा linux_prom_रेजिस्टरs *regs;
	अचिन्हित दीर्घ imap, iclr;
	पूर्णांक sbus_slot = 0;
	पूर्णांक sbus_level = 0;

	ino &= 0x3f;

	regs = of_get_property(dp, "reg", शून्य);
	अगर (regs)
		sbus_slot = regs->which_io;

	अगर (ino < 0x20)
		ino += (sbus_slot * 8);

	imap = sysio_irq_offsets[ino];
	अगर (imap == ((अचिन्हित दीर्घ)-1)) अणु
		prom_म_लिखो("get_irq_translations: Bad SYSIO INO[%x]\n",
			    ino);
		prom_halt();
	पूर्ण
	imap += reg_base;

	/* SYSIO inconsistency.  For बाह्यal SLOTS, we have to select
	 * the right ICLR रेजिस्टर based upon the lower SBUS irq level
	 * bits.
	 */
	अगर (ino >= 0x20) अणु
		iclr = sysio_imap_to_iclr(imap);
	पूर्ण अन्यथा अणु
		sbus_level = ino & 0x7;

		चयन(sbus_slot) अणु
		हाल 0:
			iclr = reg_base + SYSIO_ICLR_SLOT0;
			अवरोध;
		हाल 1:
			iclr = reg_base + SYSIO_ICLR_SLOT1;
			अवरोध;
		हाल 2:
			iclr = reg_base + SYSIO_ICLR_SLOT2;
			अवरोध;
		शेष:
		हाल 3:
			iclr = reg_base + SYSIO_ICLR_SLOT3;
			अवरोध;
		पूर्ण

		iclr += ((अचिन्हित दीर्घ)sbus_level - 1UL) * 8UL;
	पूर्ण
	वापस build_irq(sbus_level, iclr, imap);
पूर्ण

अटल व्योम __init sbus_irq_trans_init(काष्ठा device_node *dp)
अणु
	स्थिर काष्ठा linux_prom64_रेजिस्टरs *regs;

	dp->irq_trans = prom_early_alloc(माप(काष्ठा of_irq_controller));
	dp->irq_trans->irq_build = sbus_of_build_irq;

	regs = of_get_property(dp, "reg", शून्य);
	dp->irq_trans->data = (व्योम *) (अचिन्हित दीर्घ) regs->phys_addr;
पूर्ण
#पूर्ण_अगर /* CONFIG_SBUS */


अटल अचिन्हित पूर्णांक central_build_irq(काष्ठा device_node *dp,
				      अचिन्हित पूर्णांक ino,
				      व्योम *_data)
अणु
	काष्ठा device_node *central_dp = _data;
	काष्ठा platक्रमm_device *central_op = of_find_device_by_node(central_dp);
	काष्ठा resource *res;
	अचिन्हित दीर्घ imap, iclr;
	u32 पंचांगp;

	अगर (of_node_name_eq(dp, "eeprom")) अणु
		res = &central_op->resource[5];
	पूर्ण अन्यथा अगर (of_node_name_eq(dp, "zs")) अणु
		res = &central_op->resource[4];
	पूर्ण अन्यथा अगर (of_node_name_eq(dp, "clock-board")) अणु
		res = &central_op->resource[3];
	पूर्ण अन्यथा अणु
		वापस ino;
	पूर्ण

	imap = res->start + 0x00UL;
	iclr = res->start + 0x10UL;

	/* Set the INO state to idle, and disable.  */
	upa_ग_लिखोl(0, iclr);
	upa_पढ़ोl(iclr);

	पंचांगp = upa_पढ़ोl(imap);
	पंचांगp &= ~0x80000000;
	upa_ग_लिखोl(पंचांगp, imap);

	वापस build_irq(0, iclr, imap);
पूर्ण

अटल व्योम __init central_irq_trans_init(काष्ठा device_node *dp)
अणु
	dp->irq_trans = prom_early_alloc(माप(काष्ठा of_irq_controller));
	dp->irq_trans->irq_build = central_build_irq;

	dp->irq_trans->data = dp;
पूर्ण

काष्ठा irq_trans अणु
	स्थिर अक्षर *name;
	व्योम (*init)(काष्ठा device_node *);
पूर्ण;

#अगर_घोषित CONFIG_PCI
अटल काष्ठा irq_trans __initdata pci_irq_trans_table[] = अणु
	अणु "SUNW,sabre", sabre_irq_trans_init पूर्ण,
	अणु "pci108e,a000", sabre_irq_trans_init पूर्ण,
	अणु "pci108e,a001", sabre_irq_trans_init पूर्ण,
	अणु "SUNW,psycho", psycho_irq_trans_init पूर्ण,
	अणु "pci108e,8000", psycho_irq_trans_init पूर्ण,
	अणु "SUNW,schizo", schizo_irq_trans_init पूर्ण,
	अणु "pci108e,8001", schizo_irq_trans_init पूर्ण,
	अणु "SUNW,schizo+", schizo_irq_trans_init पूर्ण,
	अणु "pci108e,8002", schizo_irq_trans_init पूर्ण,
	अणु "SUNW,tomatillo", tomatillo_irq_trans_init पूर्ण,
	अणु "pci108e,a801", tomatillo_irq_trans_init पूर्ण,
	अणु "SUNW,sun4v-pci", pci_sun4v_irq_trans_init पूर्ण,
	अणु "pciex108e,80f0", fire_irq_trans_init पूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक sun4v_vdev_irq_build(काष्ठा device_node *dp,
					 अचिन्हित पूर्णांक devino,
					 व्योम *_data)
अणु
	u32 devhandle = (u32) (अचिन्हित दीर्घ) _data;

	वापस sun4v_build_irq(devhandle, devino);
पूर्ण

अटल व्योम __init sun4v_vdev_irq_trans_init(काष्ठा device_node *dp)
अणु
	स्थिर काष्ठा linux_prom64_रेजिस्टरs *regs;

	dp->irq_trans = prom_early_alloc(माप(काष्ठा of_irq_controller));
	dp->irq_trans->irq_build = sun4v_vdev_irq_build;

	regs = of_get_property(dp, "reg", शून्य);
	dp->irq_trans->data = (व्योम *) (अचिन्हित दीर्घ)
		((regs->phys_addr >> 32UL) & 0x0fffffff);
पूर्ण

व्योम __init irq_trans_init(काष्ठा device_node *dp)
अणु
#अगर_घोषित CONFIG_PCI
	स्थिर अक्षर *model;
	पूर्णांक i;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI
	model = of_get_property(dp, "model", शून्य);
	अगर (!model)
		model = of_get_property(dp, "compatible", शून्य);
	अगर (model) अणु
		क्रम (i = 0; i < ARRAY_SIZE(pci_irq_trans_table); i++) अणु
			काष्ठा irq_trans *t = &pci_irq_trans_table[i];

			अगर (!म_भेद(model, t->name)) अणु
				t->init(dp);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_SBUS
	अगर (of_node_name_eq(dp, "sbus") ||
	    of_node_name_eq(dp, "sbi")) अणु
		sbus_irq_trans_init(dp);
		वापस;
	पूर्ण
#पूर्ण_अगर
	अगर (of_node_name_eq(dp, "fhc") &&
	    of_node_name_eq(dp->parent, "central")) अणु
		central_irq_trans_init(dp);
		वापस;
	पूर्ण
	अगर (of_node_name_eq(dp, "virtual-devices") ||
	    of_node_name_eq(dp, "niu")) अणु
		sun4v_vdev_irq_trans_init(dp);
		वापस;
	पूर्ण
पूर्ण
