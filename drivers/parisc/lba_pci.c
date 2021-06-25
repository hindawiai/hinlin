<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
**
**  PCI Lower Bus Adapter (LBA) manager
**
**	(c) Copyright 1999,2000 Grant Grundler
**	(c) Copyright 1999,2000 Hewlett-Packard Company
**
**
**
** This module primarily provides access to PCI bus (config/IOport
** spaces) on platक्रमms with an SBA/LBA chipset. A/B/C/J/L/N-class
** with 4 digit model numbers - eg C3000 (and A400...sigh).
**
** LBA driver isn't as simple as the Dino driver because:
**   (a) this chip has substantial bug fixes between revisions
**       (Only one Dino bug has a software workaround :^(  )
**   (b) has more options which we करोn't (yet) support (DMA hपूर्णांकs, OLARD)
**   (c) IRQ support lives in the I/O SAPIC driver (not with PCI driver)
**   (d) play nicely with both PAT and "Legacy" PA-RISC firmware (PDC).
**       (dino only deals with "Legacy" PDC)
**
** LBA driver passes the I/O SAPIC HPA to the I/O SAPIC driver.
** (I/O SAPIC is पूर्णांकegratd in the LBA chip).
**
** FIXME: Add support to SBA and LBA drivers क्रम DMA hपूर्णांक sets
** FIXME: Add support क्रम PCI card hot-plug (OLARD).
*/

#समावेश <linux/delay.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/init.h>		/* क्रम __init */
#समावेश <linux/pci.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/pdc.h>
#समावेश <यंत्र/pdcpat.h>
#समावेश <यंत्र/page.h>

#समावेश <यंत्र/ropes.h>
#समावेश <यंत्र/hardware.h>	/* क्रम रेजिस्टर_parisc_driver() stuff */
#समावेश <यंत्र/parisc-device.h>
#समावेश <यंत्र/पन.स>		/* पढ़ो/ग_लिखो stuff */

#समावेश "iommu.h"

#अघोषित DEBUG_LBA	/* general stuff */
#अघोषित DEBUG_LBA_PORT	/* debug I/O Port access */
#अघोषित DEBUG_LBA_CFG	/* debug Config Space Access (ie PCI Bus walk) */
#अघोषित DEBUG_LBA_PAT	/* debug PCI Resource Mgt code - PDC PAT only */

#अघोषित FBB_SUPPORT	/* Fast Back-Back xfers - NOT READY YET */


#अगर_घोषित DEBUG_LBA
#घोषणा DBG(x...)	prपूर्णांकk(x)
#अन्यथा
#घोषणा DBG(x...)
#पूर्ण_अगर

#अगर_घोषित DEBUG_LBA_PORT
#घोषणा DBG_PORT(x...)	prपूर्णांकk(x)
#अन्यथा
#घोषणा DBG_PORT(x...)
#पूर्ण_अगर

#अगर_घोषित DEBUG_LBA_CFG
#घोषणा DBG_CFG(x...)	prपूर्णांकk(x)
#अन्यथा
#घोषणा DBG_CFG(x...)
#पूर्ण_अगर

#अगर_घोषित DEBUG_LBA_PAT
#घोषणा DBG_PAT(x...)	prपूर्णांकk(x)
#अन्यथा
#घोषणा DBG_PAT(x...)
#पूर्ण_अगर


/*
** Config accessor functions only pass in the 8-bit bus number and not
** the 8-bit "PCI Segment" number. Each LBA will be asचिन्हित a PCI bus
** number based on what firmware wrote पूर्णांकo the scratch रेजिस्टर.
**
** The "secondary" bus number is set to this beक्रमe calling
** pci_रेजिस्टर_ops(). If any PPB's are present, the scan will
** discover them and update the "secondary" and "subordinate"
** fields in the pci_bus काष्ठाure.
**
** Changes in the configuration *may* result in a dअगरferent
** bus number क्रम each LBA depending on what firmware करोes.
*/

#घोषणा MODULE_NAME "LBA"

/* non-postable I/O port space, densely packed */
#घोषणा LBA_PORT_BASE	(PCI_F_EXTEND | 0xfee00000UL)
अटल व्योम __iomem *astro_iop_base __पढ़ो_mostly;

अटल u32 lba_t32;

/* lba flags */
#घोषणा LBA_FLAG_SKIP_PROBE	0x10

#घोषणा LBA_SKIP_PROBE(d) ((d)->flags & LBA_FLAG_SKIP_PROBE)

अटल अंतरभूत काष्ठा lba_device *LBA_DEV(काष्ठा pci_hba_data *hba)
अणु
	वापस container_of(hba, काष्ठा lba_device, hba);
पूर्ण

/*
** Only allow 8 subsidiary busses per LBA
** Problem is the PCI bus numbering is globally shared.
*/
#घोषणा LBA_MAX_NUM_BUSES 8

/************************************
 * LBA रेजिस्टर पढ़ो and ग_लिखो support
 *
 * BE WARNED: रेजिस्टर ग_लिखोs are posted.
 *  (ie follow ग_लिखोs which must reach HW with a पढ़ो)
 */
#घोषणा READ_U8(addr)  __raw_पढ़ोb(addr)
#घोषणा READ_U16(addr) __raw_पढ़ोw(addr)
#घोषणा READ_U32(addr) __raw_पढ़ोl(addr)
#घोषणा WRITE_U8(value, addr)  __raw_ग_लिखोb(value, addr)
#घोषणा WRITE_U16(value, addr) __raw_ग_लिखोw(value, addr)
#घोषणा WRITE_U32(value, addr) __raw_ग_लिखोl(value, addr)

#घोषणा READ_REG8(addr)  पढ़ोb(addr)
#घोषणा READ_REG16(addr) पढ़ोw(addr)
#घोषणा READ_REG32(addr) पढ़ोl(addr)
#घोषणा READ_REG64(addr) पढ़ोq(addr)
#घोषणा WRITE_REG8(value, addr)  ग_लिखोb(value, addr)
#घोषणा WRITE_REG16(value, addr) ग_लिखोw(value, addr)
#घोषणा WRITE_REG32(value, addr) ग_लिखोl(value, addr)


#घोषणा LBA_CFG_TOK(bus,dfn) ((u32) ((bus)<<16 | (dfn)<<8))
#घोषणा LBA_CFG_BUS(tok)  ((u8) ((tok)>>16))
#घोषणा LBA_CFG_DEV(tok)  ((u8) ((tok)>>11) & 0x1f)
#घोषणा LBA_CFG_FUNC(tok) ((u8) ((tok)>>8 ) & 0x7)


/*
** Extract LBA (Rope) number from HPA
** REVISIT: 16 ropes क्रम Stretch/Ike?
*/
#घोषणा ROPES_PER_IOC	8
#घोषणा LBA_NUM(x)    ((((अचिन्हित दीर्घ) x) >> 13) & (ROPES_PER_IOC-1))


अटल व्योम
lba_dump_res(काष्ठा resource *r, पूर्णांक d)
अणु
	पूर्णांक i;

	अगर (शून्य == r)
		वापस;

	prपूर्णांकk(KERN_DEBUG "(%p)", r->parent);
	क्रम (i = d; i ; --i) prपूर्णांकk(" ");
	prपूर्णांकk(KERN_DEBUG "%p [%lx,%lx]/%lx\n", r,
		(दीर्घ)r->start, (दीर्घ)r->end, r->flags);
	lba_dump_res(r->child, d+2);
	lba_dump_res(r->sibling, d);
पूर्ण


/*
** LBA rev 2.0, 2.1, 2.2, and 3.0 bus walks require a complex
** workaround क्रम cfg cycles:
**	-- preserve  LBA state
**	-- prevent any DMA from occurring
**	-- turn on smart mode
**	-- probe with config ग_लिखोs beक्रमe करोing config पढ़ोs
**	-- check ERROR_STATUS
**	-- clear ERROR_STATUS
**	-- restore LBA state
**
** The workaround is only used क्रम device discovery.
*/

अटल पूर्णांक lba_device_present(u8 bus, u8 dfn, काष्ठा lba_device *d)
अणु
	u8 first_bus = d->hba.hba_bus->busn_res.start;
	u8 last_sub_bus = d->hba.hba_bus->busn_res.end;

	अगर ((bus < first_bus) ||
	    (bus > last_sub_bus) ||
	    ((bus - first_bus) >= LBA_MAX_NUM_BUSES)) अणु
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण



#घोषणा LBA_CFG_SETUP(d, tok) अणु				\
    /* Save contents of error config रेजिस्टर.  */			\
    error_config = READ_REG32(d->hba.base_addr + LBA_ERROR_CONFIG);		\
\
    /* Save contents of status control रेजिस्टर.  */			\
    status_control = READ_REG32(d->hba.base_addr + LBA_STAT_CTL);		\
\
    /* For LBA rev 2.0, 2.1, 2.2, and 3.0, we must disable DMA		\
    ** arbitration क्रम full bus walks.					\
    */									\
	/* Save contents of arb mask रेजिस्टर. */			\
	arb_mask = READ_REG32(d->hba.base_addr + LBA_ARB_MASK);		\
\
	/*								\
	 * Turn off all device arbitration bits (i.e. everything	\
	 * except arbitration enable bit).				\
	 */								\
	WRITE_REG32(0x1, d->hba.base_addr + LBA_ARB_MASK);		\
\
    /*									\
     * Set the smart mode bit so that master पातs करोn't cause		\
     * LBA to go पूर्णांकo PCI fatal mode (required).			\
     */									\
    WRITE_REG32(error_config | LBA_SMART_MODE, d->hba.base_addr + LBA_ERROR_CONFIG);	\
पूर्ण


#घोषणा LBA_CFG_PROBE(d, tok) अणु				\
    /*									\
     * Setup Venकरोr ID ग_लिखो and पढ़ो back the address रेजिस्टर		\
     * to make sure that LBA is the bus master.				\
     */									\
    WRITE_REG32(tok | PCI_VENDOR_ID, (d)->hba.base_addr + LBA_PCI_CFG_ADDR);\
    /*									\
     * Read address रेजिस्टर to ensure that LBA is the bus master,	\
     * which implies that DMA traffic has stopped when DMA arb is off.	\
     */									\
    lba_t32 = READ_REG32((d)->hba.base_addr + LBA_PCI_CFG_ADDR);	\
    /*									\
     * Generate a cfg ग_लिखो cycle (will have no affect on		\
     * Venकरोr ID रेजिस्टर since पढ़ो-only).				\
     */									\
    WRITE_REG32(~0, (d)->hba.base_addr + LBA_PCI_CFG_DATA);		\
    /*									\
     * Make sure ग_लिखो has completed beक्रमe proceeding further,		\
     * i.e. beक्रमe setting clear enable.				\
     */									\
    lba_t32 = READ_REG32((d)->hba.base_addr + LBA_PCI_CFG_ADDR);	\
पूर्ण


/*
 * HPREVISIT:
 *   -- Can't tell अगर config cycle got the error.
 *
 *		OV bit is broken until rev 4.0, so can't use OV bit and
 *		LBA_ERROR_LOG_ADDR to tell अगर error beदीर्घs to config cycle.
 *
 *		As of rev 4.0, no दीर्घer need the error check.
 *
 *   -- Even अगर we could tell, we still want to वापस -1
 *	क्रम **ANY** error (not just master पात).
 *
 *   -- Only clear non-fatal errors (we करोn't want to bring
 *	LBA out of pci-fatal mode).
 *
 *		Actually, there is still a race in which
 *		we could be clearing a fatal error.  We will
 *		live with this during our initial bus walk
 *		until rev 4.0 (no driver activity during
 *		initial bus walk).  The initial bus walk
 *		has race conditions concerning the use of
 *		smart mode as well.
 */

#घोषणा LBA_MASTER_ABORT_ERROR 0xc
#घोषणा LBA_FATAL_ERROR 0x10

#घोषणा LBA_CFG_MASTER_ABORT_CHECK(d, base, tok, error) अणु		\
    u32 error_status = 0;						\
    /*									\
     * Set clear enable (CE) bit. Unset by HW when new			\
     * errors are logged -- LBA HW ERS section 14.3.3).		\
     */									\
    WRITE_REG32(status_control | CLEAR_ERRLOG_ENABLE, base + LBA_STAT_CTL); \
    error_status = READ_REG32(base + LBA_ERROR_STATUS);		\
    अगर ((error_status & 0x1f) != 0) अणु					\
	/*								\
	 * Fail the config पढ़ो request.				\
	 */								\
	error = 1;							\
	अगर ((error_status & LBA_FATAL_ERROR) == 0) अणु			\
	    /*								\
	     * Clear error status (अगर fatal bit not set) by setting	\
	     * clear error log bit (CL).				\
	     */								\
	    WRITE_REG32(status_control | CLEAR_ERRLOG, base + LBA_STAT_CTL); \
	पूर्ण								\
    पूर्ण									\
पूर्ण

#घोषणा LBA_CFG_TR4_ADDR_SETUP(d, addr)					\
	WRITE_REG32(((addr) & ~3), (d)->hba.base_addr + LBA_PCI_CFG_ADDR);

#घोषणा LBA_CFG_ADDR_SETUP(d, addr) अणु					\
    WRITE_REG32(((addr) & ~3), (d)->hba.base_addr + LBA_PCI_CFG_ADDR);	\
    /*									\
     * Read address रेजिस्टर to ensure that LBA is the bus master,	\
     * which implies that DMA traffic has stopped when DMA arb is off.	\
     */									\
    lba_t32 = READ_REG32((d)->hba.base_addr + LBA_PCI_CFG_ADDR);	\
पूर्ण


#घोषणा LBA_CFG_RESTORE(d, base) अणु					\
    /*									\
     * Restore status control रेजिस्टर (turn off clear enable).		\
     */									\
    WRITE_REG32(status_control, base + LBA_STAT_CTL);			\
    /*									\
     * Restore error config रेजिस्टर (turn off smart mode).		\
     */									\
    WRITE_REG32(error_config, base + LBA_ERROR_CONFIG);			\
	/*								\
	 * Restore arb mask रेजिस्टर (reenables DMA arbitration).	\
	 */								\
	WRITE_REG32(arb_mask, base + LBA_ARB_MASK);			\
पूर्ण



अटल अचिन्हित पूर्णांक
lba_rd_cfg(काष्ठा lba_device *d, u32 tok, u8 reg, u32 size)
अणु
	u32 data = ~0U;
	पूर्णांक error = 0;
	u32 arb_mask = 0;	/* used by LBA_CFG_SETUP/RESTORE */
	u32 error_config = 0;	/* used by LBA_CFG_SETUP/RESTORE */
	u32 status_control = 0;	/* used by LBA_CFG_SETUP/RESTORE */

	LBA_CFG_SETUP(d, tok);
	LBA_CFG_PROBE(d, tok);
	LBA_CFG_MASTER_ABORT_CHECK(d, d->hba.base_addr, tok, error);
	अगर (!error) अणु
		व्योम __iomem *data_reg = d->hba.base_addr + LBA_PCI_CFG_DATA;

		LBA_CFG_ADDR_SETUP(d, tok | reg);
		चयन (size) अणु
		हाल 1: data = (u32) READ_REG8(data_reg + (reg & 3)); अवरोध;
		हाल 2: data = (u32) READ_REG16(data_reg+ (reg & 2)); अवरोध;
		हाल 4: data = READ_REG32(data_reg); अवरोध;
		पूर्ण
	पूर्ण
	LBA_CFG_RESTORE(d, d->hba.base_addr);
	वापस(data);
पूर्ण


अटल पूर्णांक elroy_cfg_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक pos, पूर्णांक size, u32 *data)
अणु
	काष्ठा lba_device *d = LBA_DEV(parisc_walk_tree(bus->bridge));
	u32 local_bus = (bus->parent == शून्य) ? 0 : bus->busn_res.start;
	u32 tok = LBA_CFG_TOK(local_bus, devfn);
	व्योम __iomem *data_reg = d->hba.base_addr + LBA_PCI_CFG_DATA;

	अगर ((pos > 255) || (devfn > 255))
		वापस -EINVAL;

/* FIXME: B2K/C3600 workaround is always use old method... */
	/* अगर (!LBA_SKIP_PROBE(d)) */ अणु
		/* original - Generate config cycle on broken elroy
		  with risk we will miss PCI bus errors. */
		*data = lba_rd_cfg(d, tok, pos, size);
		DBG_CFG("%s(%x+%2x) -> 0x%x (a)\n", __func__, tok, pos, *data);
		वापस 0;
	पूर्ण

	अगर (LBA_SKIP_PROBE(d) && !lba_device_present(bus->busn_res.start, devfn, d)) अणु
		DBG_CFG("%s(%x+%2x) -> -1 (b)\n", __func__, tok, pos);
		/* either करोn't want to look or know device isn't present. */
		*data = ~0U;
		वापस(0);
	पूर्ण

	/* Basic Algorithm
	** Should only get here on fully working LBA rev.
	** This is how simple the code should have been.
	*/
	LBA_CFG_ADDR_SETUP(d, tok | pos);
	चयन(size) अणु
	हाल 1: *data = READ_REG8 (data_reg + (pos & 3)); अवरोध;
	हाल 2: *data = READ_REG16(data_reg + (pos & 2)); अवरोध;
	हाल 4: *data = READ_REG32(data_reg); अवरोध;
	पूर्ण
	DBG_CFG("%s(%x+%2x) -> 0x%x (c)\n", __func__, tok, pos, *data);
	वापस 0;
पूर्ण


अटल व्योम
lba_wr_cfg(काष्ठा lba_device *d, u32 tok, u8 reg, u32 data, u32 size)
अणु
	पूर्णांक error = 0;
	u32 arb_mask = 0;
	u32 error_config = 0;
	u32 status_control = 0;
	व्योम __iomem *data_reg = d->hba.base_addr + LBA_PCI_CFG_DATA;

	LBA_CFG_SETUP(d, tok);
	LBA_CFG_ADDR_SETUP(d, tok | reg);
	चयन (size) अणु
	हाल 1: WRITE_REG8 (data, data_reg + (reg & 3)); अवरोध;
	हाल 2: WRITE_REG16(data, data_reg + (reg & 2)); अवरोध;
	हाल 4: WRITE_REG32(data, data_reg);             अवरोध;
	पूर्ण
	LBA_CFG_MASTER_ABORT_CHECK(d, d->hba.base_addr, tok, error);
	LBA_CFG_RESTORE(d, d->hba.base_addr);
पूर्ण


/*
 * LBA 4.0 config ग_लिखो code implements non-postable semantics
 * by करोing a पढ़ो of CONFIG ADDR after the ग_लिखो.
 */

अटल पूर्णांक elroy_cfg_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक pos, पूर्णांक size, u32 data)
अणु
	काष्ठा lba_device *d = LBA_DEV(parisc_walk_tree(bus->bridge));
	u32 local_bus = (bus->parent == शून्य) ? 0 : bus->busn_res.start;
	u32 tok = LBA_CFG_TOK(local_bus,devfn);

	अगर ((pos > 255) || (devfn > 255))
		वापस -EINVAL;

	अगर (!LBA_SKIP_PROBE(d)) अणु
		/* Original Workaround */
		lba_wr_cfg(d, tok, pos, (u32) data, size);
		DBG_CFG("%s(%x+%2x) = 0x%x (a)\n", __func__, tok, pos,data);
		वापस 0;
	पूर्ण

	अगर (LBA_SKIP_PROBE(d) && (!lba_device_present(bus->busn_res.start, devfn, d))) अणु
		DBG_CFG("%s(%x+%2x) = 0x%x (b)\n", __func__, tok, pos,data);
		वापस 1; /* New Workaround */
	पूर्ण

	DBG_CFG("%s(%x+%2x) = 0x%x (c)\n", __func__, tok, pos, data);

	/* Basic Algorithm */
	LBA_CFG_ADDR_SETUP(d, tok | pos);
	चयन(size) अणु
	हाल 1: WRITE_REG8 (data, d->hba.base_addr + LBA_PCI_CFG_DATA + (pos & 3));
		   अवरोध;
	हाल 2: WRITE_REG16(data, d->hba.base_addr + LBA_PCI_CFG_DATA + (pos & 2));
		   अवरोध;
	हाल 4: WRITE_REG32(data, d->hba.base_addr + LBA_PCI_CFG_DATA);
		   अवरोध;
	पूर्ण
	/* flush posted ग_लिखो */
	lba_t32 = READ_REG32(d->hba.base_addr + LBA_PCI_CFG_ADDR);
	वापस 0;
पूर्ण


अटल काष्ठा pci_ops elroy_cfg_ops = अणु
	.पढ़ो =		elroy_cfg_पढ़ो,
	.ग_लिखो =	elroy_cfg_ग_लिखो,
पूर्ण;

/*
 * The mercury_cfg_ops are slightly misnamed; they're also used क्रम Elroy
 * TR4.0 as no additional bugs were found in this areea between Elroy and
 * Mercury
 */

अटल पूर्णांक mercury_cfg_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक pos, पूर्णांक size, u32 *data)
अणु
	काष्ठा lba_device *d = LBA_DEV(parisc_walk_tree(bus->bridge));
	u32 local_bus = (bus->parent == शून्य) ? 0 : bus->busn_res.start;
	u32 tok = LBA_CFG_TOK(local_bus, devfn);
	व्योम __iomem *data_reg = d->hba.base_addr + LBA_PCI_CFG_DATA;

	अगर ((pos > 255) || (devfn > 255))
		वापस -EINVAL;

	LBA_CFG_TR4_ADDR_SETUP(d, tok | pos);
	चयन(size) अणु
	हाल 1:
		*data = READ_REG8(data_reg + (pos & 3));
		अवरोध;
	हाल 2:
		*data = READ_REG16(data_reg + (pos & 2));
		अवरोध;
	हाल 4:
		*data = READ_REG32(data_reg);             अवरोध;
		अवरोध;
	पूर्ण

	DBG_CFG("mercury_cfg_read(%x+%2x) -> 0x%x\n", tok, pos, *data);
	वापस 0;
पूर्ण

/*
 * LBA 4.0 config ग_लिखो code implements non-postable semantics
 * by करोing a पढ़ो of CONFIG ADDR after the ग_लिखो.
 */

अटल पूर्णांक mercury_cfg_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक pos, पूर्णांक size, u32 data)
अणु
	काष्ठा lba_device *d = LBA_DEV(parisc_walk_tree(bus->bridge));
	व्योम __iomem *data_reg = d->hba.base_addr + LBA_PCI_CFG_DATA;
	u32 local_bus = (bus->parent == शून्य) ? 0 : bus->busn_res.start;
	u32 tok = LBA_CFG_TOK(local_bus,devfn);

	अगर ((pos > 255) || (devfn > 255))
		वापस -EINVAL;

	DBG_CFG("%s(%x+%2x) <- 0x%x (c)\n", __func__, tok, pos, data);

	LBA_CFG_TR4_ADDR_SETUP(d, tok | pos);
	चयन(size) अणु
	हाल 1:
		WRITE_REG8 (data, data_reg + (pos & 3));
		अवरोध;
	हाल 2:
		WRITE_REG16(data, data_reg + (pos & 2));
		अवरोध;
	हाल 4:
		WRITE_REG32(data, data_reg);
		अवरोध;
	पूर्ण

	/* flush posted ग_लिखो */
	lba_t32 = READ_U32(d->hba.base_addr + LBA_PCI_CFG_ADDR);
	वापस 0;
पूर्ण

अटल काष्ठा pci_ops mercury_cfg_ops = अणु
	.पढ़ो =		mercury_cfg_पढ़ो,
	.ग_लिखो =	mercury_cfg_ग_लिखो,
पूर्ण;


अटल व्योम
lba_bios_init(व्योम)
अणु
	DBG(MODULE_NAME ": lba_bios_init\n");
पूर्ण


#अगर_घोषित CONFIG_64BIT

/*
 * truncate_pat_collision:  Deal with overlaps or outright collisions
 *			between PAT PDC reported ranges.
 *
 *   Broken PA8800 firmware will report lmmio range that
 *   overlaps with CPU HPA. Just truncate the lmmio range.
 *
 *   BEWARE: conflicts with this lmmio range may be an
 *   elmmio range which is poपूर्णांकing करोwn another rope.
 *
 *  FIXME: only deals with one collision per range...theoretically we
 *  could have several. Supporting more than one collision will get messy.
 */
अटल अचिन्हित दीर्घ
truncate_pat_collision(काष्ठा resource *root, काष्ठा resource *new)
अणु
	अचिन्हित दीर्घ start = new->start;
	अचिन्हित दीर्घ end = new->end;
	काष्ठा resource *पंचांगp = root->child;

	अगर (end <= start || start < root->start || !पंचांगp)
		वापस 0;

	/* find first overlap */
	जबतक (पंचांगp && पंचांगp->end < start)
		पंचांगp = पंचांगp->sibling;

	/* no entries overlap */
	अगर (!पंचांगp)  वापस 0;

	/* found one that starts behind the new one
	** Don't need to करो anything.
	*/
	अगर (पंचांगp->start >= end) वापस 0;

	अगर (पंचांगp->start <= start) अणु
		/* "front" of new one overlaps */
		new->start = पंचांगp->end + 1;

		अगर (पंचांगp->end >= end) अणु
			/* AACCKK! totally overlaps! drop this range. */
			वापस 1;
		पूर्ण
	पूर्ण 

	अगर (पंचांगp->end < end ) अणु
		/* "end" of new one overlaps */
		new->end = पंचांगp->start - 1;
	पूर्ण

	prपूर्णांकk(KERN_WARNING "LBA: Truncating lmmio_space [%lx/%lx] "
					"to [%lx,%lx]\n",
			start, end,
			(दीर्घ)new->start, (दीर्घ)new->end );

	वापस 0;	/* truncation successful */
पूर्ण

/*
 * extend_lmmio_len: extend lmmio range to maximum length
 *
 * This is needed at least on C8000 प्रणालीs to get the ATI FireGL card
 * working. On other प्रणालीs we will currently not extend the lmmio space.
 */
अटल अचिन्हित दीर्घ
extend_lmmio_len(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, अचिन्हित दीर्घ lba_len)
अणु
	काष्ठा resource *पंचांगp;

	/* निकास अगर not a C8000 */
	अगर (boot_cpu_data.cpu_type < mako)
		वापस end;

	pr_debug("LMMIO mismatch: PAT length = 0x%lx, MASK register = 0x%lx\n",
		end - start, lba_len);

	lba_len = min(lba_len+1, 256UL*1024*1024); /* limit to 256 MB */

	pr_debug("LBA: lmmio_space [0x%lx-0x%lx] - original\n", start, end);


	end += lba_len;
	अगर (end < start) /* fix overflow */
		end = -1ULL;

	pr_debug("LBA: lmmio_space [0x%lx-0x%lx] - current\n", start, end);

	/* first overlap */
	क्रम (पंचांगp = iomem_resource.child; पंचांगp; पंचांगp = पंचांगp->sibling) अणु
		pr_debug("LBA: testing %pR\n", पंचांगp);
		अगर (पंचांगp->start == start)
			जारी; /* ignore ourself */
		अगर (पंचांगp->end < start)
			जारी;
		अगर (पंचांगp->start > end)
			जारी;
		अगर (end >= पंचांगp->start)
			end = पंचांगp->start - 1;
	पूर्ण

	pr_info("LBA: lmmio_space [0x%lx-0x%lx] - new\n", start, end);

	/* वापस new end */
	वापस end;
पूर्ण

#अन्यथा
#घोषणा truncate_pat_collision(r,n)  (0)
#पूर्ण_अगर

अटल व्योम pcibios_allocate_bridge_resources(काष्ठा pci_dev *dev)
अणु
	पूर्णांक idx;
	काष्ठा resource *r;

	क्रम (idx = PCI_BRIDGE_RESOURCES; idx < PCI_NUM_RESOURCES; idx++) अणु
		r = &dev->resource[idx];
		अगर (!r->flags)
			जारी;
		अगर (r->parent)	/* Alपढ़ोy allocated */
			जारी;
		अगर (!r->start || pci_claim_bridge_resource(dev, idx) < 0) अणु
			/*
			 * Something is wrong with the region.
			 * Invalidate the resource to prevent
			 * child resource allocations in this
			 * range.
			 */
			r->start = r->end = 0;
			r->flags = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pcibios_allocate_bus_resources(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_bus *child;

	/* Depth-First Search on bus tree */
	अगर (bus->self)
		pcibios_allocate_bridge_resources(bus->self);
	list_क्रम_each_entry(child, &bus->children, node)
		pcibios_allocate_bus_resources(child);
पूर्ण


/*
** The algorithm is generic code.
** But it needs to access local data काष्ठाures to get the IRQ base.
** Could make this a "pci_fixup_irq(bus, region)" but not sure
** it's worth it.
**
** Called by करो_pci_scan_bus() immediately after each PCI bus is walked.
** Resources aren't allocated until recursive buswalk below HBA is completed.
*/
अटल व्योम
lba_fixup_bus(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev;
#अगर_घोषित FBB_SUPPORT
	u16 status;
#पूर्ण_अगर
	काष्ठा lba_device *ldev = LBA_DEV(parisc_walk_tree(bus->bridge));

	DBG("lba_fixup_bus(0x%p) bus %d platform_data 0x%p\n",
		bus, (पूर्णांक)bus->busn_res.start, bus->bridge->platक्रमm_data);

	/*
	** Properly Setup MMIO resources क्रम this bus.
	** pci_alloc_primary_bus() mangles this.
	*/
	अगर (bus->parent) अणु
		/* PCI-PCI Bridge */
		pci_पढ़ो_bridge_bases(bus);

		/* check and allocate bridge resources */
		pcibios_allocate_bus_resources(bus);
	पूर्ण अन्यथा अणु
		/* Host-PCI Bridge */
		पूर्णांक err;

		DBG("lba_fixup_bus() %s [%lx/%lx]/%lx\n",
			ldev->hba.io_space.name,
			ldev->hba.io_space.start, ldev->hba.io_space.end,
			ldev->hba.io_space.flags);
		DBG("lba_fixup_bus() %s [%lx/%lx]/%lx\n",
			ldev->hba.lmmio_space.name,
			ldev->hba.lmmio_space.start, ldev->hba.lmmio_space.end,
			ldev->hba.lmmio_space.flags);

		err = request_resource(&ioport_resource, &(ldev->hba.io_space));
		अगर (err < 0) अणु
			lba_dump_res(&ioport_resource, 2);
			BUG();
		पूर्ण

		अगर (ldev->hba.elmmio_space.flags) अणु
			err = request_resource(&iomem_resource,
					&(ldev->hba.elmmio_space));
			अगर (err < 0) अणु

				prपूर्णांकk("FAILED: lba_fixup_bus() request for "
						"elmmio_space [%lx/%lx]\n",
						(दीर्घ)ldev->hba.elmmio_space.start,
						(दीर्घ)ldev->hba.elmmio_space.end);

				/* lba_dump_res(&iomem_resource, 2); */
				/* BUG(); */
			पूर्ण
		पूर्ण

		अगर (ldev->hba.lmmio_space.flags) अणु
			err = request_resource(&iomem_resource, &(ldev->hba.lmmio_space));
			अगर (err < 0) अणु
				prपूर्णांकk(KERN_ERR "FAILED: lba_fixup_bus() request for "
					"lmmio_space [%lx/%lx]\n",
					(दीर्घ)ldev->hba.lmmio_space.start,
					(दीर्घ)ldev->hba.lmmio_space.end);
			पूर्ण
		पूर्ण

#अगर_घोषित CONFIG_64BIT
		/* GMMIO is  distributed range. Every LBA/Rope माला_लो part it. */
		अगर (ldev->hba.gmmio_space.flags) अणु
			err = request_resource(&iomem_resource, &(ldev->hba.gmmio_space));
			अगर (err < 0) अणु
				prपूर्णांकk("FAILED: lba_fixup_bus() request for "
					"gmmio_space [%lx/%lx]\n",
					(दीर्घ)ldev->hba.gmmio_space.start,
					(दीर्घ)ldev->hba.gmmio_space.end);
				lba_dump_res(&iomem_resource, 2);
				BUG();
			पूर्ण
		पूर्ण
#पूर्ण_अगर

	पूर्ण

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		पूर्णांक i;

		DBG("lba_fixup_bus() %s\n", pci_name(dev));

		/* Virtualize Device/Bridge Resources. */
		क्रम (i = 0; i < PCI_BRIDGE_RESOURCES; i++) अणु
			काष्ठा resource *res = &dev->resource[i];

			/* If resource not allocated - skip it */
			अगर (!res->start)
				जारी;

			/*
			** FIXME: this will result in whinging क्रम devices
			** that share expansion ROMs (think quad tulip), but
			** isn't harmful.
			*/
			pci_claim_resource(dev, i);
		पूर्ण

#अगर_घोषित FBB_SUPPORT
		/*
		** If one device करोes not support FBB transfers,
		** No one on the bus can be allowed to use them.
		*/
		(व्योम) pci_पढ़ो_config_word(dev, PCI_STATUS, &status);
		bus->bridge_ctl &= ~(status & PCI_STATUS_FAST_BACK);
#पूर्ण_अगर

                /*
		** P2PB's have no IRQs. ignore them.
		*/
		अगर ((dev->class >> 8) == PCI_CLASS_BRIDGE_PCI) अणु
			pcibios_init_bridge(dev);
			जारी;
		पूर्ण

		/* Adjust INTERRUPT_LINE क्रम this dev */
		iosapic_fixup_irq(ldev->iosapic_obj, dev);
	पूर्ण

#अगर_घोषित FBB_SUPPORT
/* FIXME/REVISIT - finish figuring out to set FBB on both
** pci_setup_bridge() clobbers PCI_BRIDGE_CONTROL.
** Can't fixup here anyway....garr...
*/
	अगर (fbb_enable) अणु
		अगर (bus->parent) अणु
			u8 control;
			/* enable on PPB */
			(व्योम) pci_पढ़ो_config_byte(bus->self, PCI_BRIDGE_CONTROL, &control);
			(व्योम) pci_ग_लिखो_config_byte(bus->self, PCI_BRIDGE_CONTROL, control | PCI_STATUS_FAST_BACK);

		पूर्ण अन्यथा अणु
			/* enable on LBA */
		पूर्ण
		fbb_enable = PCI_COMMAND_FAST_BACK;
	पूर्ण

	/* Lastly enable FBB/PERR/SERR on all devices too */
	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		(व्योम) pci_पढ़ो_config_word(dev, PCI_COMMAND, &status);
		status |= PCI_COMMAND_PARITY | PCI_COMMAND_SERR | fbb_enable;
		(व्योम) pci_ग_लिखो_config_word(dev, PCI_COMMAND, status);
	पूर्ण
#पूर्ण_अगर
पूर्ण


अटल काष्ठा pci_bios_ops lba_bios_ops = अणु
	.init =		lba_bios_init,
	.fixup_bus =	lba_fixup_bus,
पूर्ण;




/*******************************************************
**
** LBA Sprockets "I/O Port" Space Accessor Functions
**
** This set of accessor functions is पूर्णांकended क्रम use with
** "legacy firmware" (ie Sprockets on Allegro/Forte boxes).
**
** Many PCI devices करोn't require use of I/O port space (eg Tulip,
** NCR720) since they export the same रेजिस्टरs to both MMIO and
** I/O port space. In general I/O port space is slower than
** MMIO since drivers are deचिन्हित so PIO ग_लिखोs can be posted.
**
********************************************************/

#घोषणा LBA_PORT_IN(size, mask) \
अटल u##size lba_astro_in##size (काष्ठा pci_hba_data *d, u16 addr) \
अणु \
	u##size t; \
	t = READ_REG##size(astro_iop_base + addr); \
	DBG_PORT(" 0x%x\n", t); \
	वापस (t); \
पूर्ण

LBA_PORT_IN( 8, 3)
LBA_PORT_IN(16, 2)
LBA_PORT_IN(32, 0)



/*
** BUG X4107:  Ordering broken - DMA RD वापस can bypass PIO WR
**
** Fixed in Elroy 2.2. The READ_U32(..., LBA_FUNC_ID) below is
** guarantee non-postable completion semantics - not aव्योम X4107.
** The READ_U32 only guarantees the ग_लिखो data माला_लो to elroy but
** out to the PCI bus. We can't पढ़ो stuff from I/O port space
** since we करोn't know what has side-effects. Attempting to पढ़ो
** from configuration space would be suicidal given the number of
** bugs in that elroy functionality.
**
**      Description:
**          DMA पढ़ो results can improperly pass PIO ग_लिखोs (X4107).  The
**          result of this bug is that अगर a processor modअगरies a location in
**          memory after having issued PIO ग_लिखोs, the PIO ग_लिखोs are not
**          guaranteed to be completed beक्रमe a PCI device is allowed to see
**          the modअगरied data in a DMA पढ़ो.
**
**          Note that IKE bug X3719 in TR1 IKEs will result in the same
**          symptom.
**
**      Workaround:
**          The workaround क्रम this bug is to always follow a PIO ग_लिखो with
**          a PIO पढ़ो to the same bus beक्रमe starting DMA on that PCI bus.
**
*/
#घोषणा LBA_PORT_OUT(size, mask) \
अटल व्योम lba_astro_out##size (काष्ठा pci_hba_data *d, u16 addr, u##size val) \
अणु \
	DBG_PORT("%s(0x%p, 0x%x, 0x%x)\n", __func__, d, addr, val); \
	WRITE_REG##size(val, astro_iop_base + addr); \
	अगर (LBA_DEV(d)->hw_rev < 3) \
		lba_t32 = READ_U32(d->base_addr + LBA_FUNC_ID); \
पूर्ण

LBA_PORT_OUT( 8, 3)
LBA_PORT_OUT(16, 2)
LBA_PORT_OUT(32, 0)


अटल काष्ठा pci_port_ops lba_astro_port_ops = अणु
	.inb =	lba_astro_in8,
	.inw =	lba_astro_in16,
	.inl =	lba_astro_in32,
	.outb =	lba_astro_out8,
	.outw =	lba_astro_out16,
	.outl =	lba_astro_out32
पूर्ण;


#अगर_घोषित CONFIG_64BIT
#घोषणा PIOP_TO_GMMIO(lba, addr) \
	((lba)->iop_base + (((addr)&0xFFFC)<<10) + ((addr)&3))

/*******************************************************
**
** LBA PAT "I/O Port" Space Accessor Functions
**
** This set of accessor functions is पूर्णांकended क्रम use with
** "PAT PDC" firmware (ie Prelude/Rhapsody/Piranha boxes).
**
** This uses the PIOP space located in the first 64MB of GMMIO.
** Each rope माला_लो a full 64*KB* (ie 4 bytes per page) this way.
** bits 1:0 stay the same.  bits 15:2 become 25:12.
** Then add the base and we can generate an I/O Port cycle.
********************************************************/
#अघोषित LBA_PORT_IN
#घोषणा LBA_PORT_IN(size, mask) \
अटल u##size lba_pat_in##size (काष्ठा pci_hba_data *l, u16 addr) \
अणु \
	u##size t; \
	DBG_PORT("%s(0x%p, 0x%x) ->", __func__, l, addr); \
	t = READ_REG##size(PIOP_TO_GMMIO(LBA_DEV(l), addr)); \
	DBG_PORT(" 0x%x\n", t); \
	वापस (t); \
पूर्ण

LBA_PORT_IN( 8, 3)
LBA_PORT_IN(16, 2)
LBA_PORT_IN(32, 0)


#अघोषित LBA_PORT_OUT
#घोषणा LBA_PORT_OUT(size, mask) \
अटल व्योम lba_pat_out##size (काष्ठा pci_hba_data *l, u16 addr, u##size val) \
अणु \
	व्योम __iomem *where = PIOP_TO_GMMIO(LBA_DEV(l), addr); \
	DBG_PORT("%s(0x%p, 0x%x, 0x%x)\n", __func__, l, addr, val); \
	WRITE_REG##size(val, where); \
	/* flush the I/O करोwn to the elroy at least */ \
	lba_t32 = READ_U32(l->base_addr + LBA_FUNC_ID); \
पूर्ण

LBA_PORT_OUT( 8, 3)
LBA_PORT_OUT(16, 2)
LBA_PORT_OUT(32, 0)


अटल काष्ठा pci_port_ops lba_pat_port_ops = अणु
	.inb =	lba_pat_in8,
	.inw =	lba_pat_in16,
	.inl =	lba_pat_in32,
	.outb =	lba_pat_out8,
	.outw =	lba_pat_out16,
	.outl =	lba_pat_out32
पूर्ण;



/*
** make range inक्रमmation from PDC available to PCI subप्रणाली.
** We make the PDC call here in order to get the PCI bus range
** numbers. The rest will get क्रमwarded in pcibios_fixup_bus().
** We करोn't have a काष्ठा pci_bus asचिन्हित to us yet.
*/
अटल व्योम
lba_pat_resources(काष्ठा parisc_device *pa_dev, काष्ठा lba_device *lba_dev)
अणु
	अचिन्हित दीर्घ bytecnt;
	दीर्घ io_count;
	दीर्घ status;	/* PDC वापस status */
	दीर्घ pa_count;
	pdc_pat_cell_mod_maddr_block_t *pa_pdc_cell;	/* PA_VIEW */
	pdc_pat_cell_mod_maddr_block_t *io_pdc_cell;	/* IO_VIEW */
	पूर्णांक i;

	pa_pdc_cell = kzalloc(माप(pdc_pat_cell_mod_maddr_block_t), GFP_KERNEL);
	अगर (!pa_pdc_cell)
		वापस;

	io_pdc_cell = kzalloc(माप(pdc_pat_cell_mod_maddr_block_t), GFP_KERNEL);
	अगर (!io_pdc_cell) अणु
		kमुक्त(pa_pdc_cell);
		वापस;
	पूर्ण

	/* वापस cell module (IO view) */
	status = pdc_pat_cell_module(&bytecnt, pa_dev->pcell_loc, pa_dev->mod_index,
				PA_VIEW, pa_pdc_cell);
	pa_count = pa_pdc_cell->mod[1];

	status |= pdc_pat_cell_module(&bytecnt, pa_dev->pcell_loc, pa_dev->mod_index,
				IO_VIEW, io_pdc_cell);
	io_count = io_pdc_cell->mod[1];

	/* We've alपढ़ोy करोne this once क्रम device discovery...*/
	अगर (status != PDC_OK) अणु
		panic("pdc_pat_cell_module() call failed for LBA!\n");
	पूर्ण

	अगर (PAT_GET_ENTITY(pa_pdc_cell->mod_info) != PAT_ENTITY_LBA) अणु
		panic("pdc_pat_cell_module() entity returned != PAT_ENTITY_LBA!\n");
	पूर्ण

	/*
	** Inspect the resources PAT tells us about
	*/
	क्रम (i = 0; i < pa_count; i++) अणु
		काष्ठा अणु
			अचिन्हित दीर्घ type;
			अचिन्हित दीर्घ start;
			अचिन्हित दीर्घ end;	/* aka finish */
		पूर्ण *p, *io;
		काष्ठा resource *r;

		p = (व्योम *) &(pa_pdc_cell->mod[2+i*3]);
		io = (व्योम *) &(io_pdc_cell->mod[2+i*3]);

		/* Convert the PAT range data to PCI "struct resource" */
		चयन(p->type & 0xff) अणु
		हाल PAT_PBNUM:
			lba_dev->hba.bus_num.start = p->start;
			lba_dev->hba.bus_num.end   = p->end;
			lba_dev->hba.bus_num.flags = IORESOURCE_BUS;
			अवरोध;

		हाल PAT_LMMIO:
			/* used to fix up pre-initialized MEM BARs */
			अगर (!lba_dev->hba.lmmio_space.flags) अणु
				अचिन्हित दीर्घ lba_len;

				lba_len = ~READ_REG32(lba_dev->hba.base_addr
						+ LBA_LMMIO_MASK);
				अगर ((p->end - p->start) != lba_len)
					p->end = extend_lmmio_len(p->start,
						p->end, lba_len);

				प्र_लिखो(lba_dev->hba.lmmio_name,
						"PCI%02x LMMIO",
						(पूर्णांक)lba_dev->hba.bus_num.start);
				lba_dev->hba.lmmio_space_offset = p->start -
					io->start;
				r = &lba_dev->hba.lmmio_space;
				r->name = lba_dev->hba.lmmio_name;
			पूर्ण अन्यथा अगर (!lba_dev->hba.elmmio_space.flags) अणु
				प्र_लिखो(lba_dev->hba.elmmio_name,
						"PCI%02x ELMMIO",
						(पूर्णांक)lba_dev->hba.bus_num.start);
				r = &lba_dev->hba.elmmio_space;
				r->name = lba_dev->hba.elmmio_name;
			पूर्ण अन्यथा अणु
				prपूर्णांकk(KERN_WARNING MODULE_NAME
					" only supports 2 LMMIO resources!\n");
				अवरोध;
			पूर्ण

			r->start  = p->start;
			r->end    = p->end;
			r->flags  = IORESOURCE_MEM;
			r->parent = r->sibling = r->child = शून्य;
			अवरोध;

		हाल PAT_GMMIO:
			/* MMIO space > 4GB phys addr; क्रम 64-bit BAR */
			प्र_लिखो(lba_dev->hba.gmmio_name, "PCI%02x GMMIO",
					(पूर्णांक)lba_dev->hba.bus_num.start);
			r = &lba_dev->hba.gmmio_space;
			r->name  = lba_dev->hba.gmmio_name;
			r->start  = p->start;
			r->end    = p->end;
			r->flags  = IORESOURCE_MEM;
			r->parent = r->sibling = r->child = शून्य;
			अवरोध;

		हाल PAT_NPIOP:
			prपूर्णांकk(KERN_WARNING MODULE_NAME
				" range[%d] : ignoring NPIOP (0x%lx)\n",
				i, p->start);
			अवरोध;

		हाल PAT_PIOP:
			/*
			** Postable I/O port space is per PCI host adapter.
			** base of 64MB PIOP region
			*/
			lba_dev->iop_base = ioremap(p->start, 64 * 1024 * 1024);

			प्र_लिखो(lba_dev->hba.io_name, "PCI%02x Ports",
					(पूर्णांक)lba_dev->hba.bus_num.start);
			r = &lba_dev->hba.io_space;
			r->name  = lba_dev->hba.io_name;
			r->start  = HBA_PORT_BASE(lba_dev->hba.hba_num);
			r->end    = r->start + HBA_PORT_SPACE_SIZE - 1;
			r->flags  = IORESOURCE_IO;
			r->parent = r->sibling = r->child = शून्य;
			अवरोध;

		शेष:
			prपूर्णांकk(KERN_WARNING MODULE_NAME
				" range[%d] : unknown pat range type (0x%lx)\n",
				i, p->type & 0xff);
			अवरोध;
		पूर्ण
	पूर्ण

	kमुक्त(pa_pdc_cell);
	kमुक्त(io_pdc_cell);
पूर्ण
#अन्यथा
/* keep compiler from complaining about missing declarations */
#घोषणा lba_pat_port_ops lba_astro_port_ops
#घोषणा lba_pat_resources(pa_dev, lba_dev)
#पूर्ण_अगर	/* CONFIG_64BIT */


बाह्य व्योम sba_distributed_lmmio(काष्ठा parisc_device *, काष्ठा resource *);
बाह्य व्योम sba_directed_lmmio(काष्ठा parisc_device *, काष्ठा resource *);


अटल व्योम
lba_legacy_resources(काष्ठा parisc_device *pa_dev, काष्ठा lba_device *lba_dev)
अणु
	काष्ठा resource *r;
	पूर्णांक lba_num;

	lba_dev->hba.lmmio_space_offset = PCI_F_EXTEND;

	/*
	** With "legacy" firmware, the lowest byte of FW_SCRATCH
	** represents bus->secondary and the second byte represents
	** bus->subsidiary (i.e. highest PPB programmed by firmware).
	** PCI bus walk *should* end up with the same result.
	** FIXME: But we करोn't have sanity checks in PCI or LBA.
	*/
	lba_num = READ_REG32(lba_dev->hba.base_addr + LBA_FW_SCRATCH);
	r = &(lba_dev->hba.bus_num);
	r->name = "LBA PCI Busses";
	r->start = lba_num & 0xff;
	r->end = (lba_num>>8) & 0xff;
	r->flags = IORESOURCE_BUS;

	/* Set up local PCI Bus resources - we करोn't need them क्रम
	** Legacy boxes but it's nice to see in /proc/iomem.
	*/
	r = &(lba_dev->hba.lmmio_space);
	प्र_लिखो(lba_dev->hba.lmmio_name, "PCI%02x LMMIO",
					(पूर्णांक)lba_dev->hba.bus_num.start);
	r->name  = lba_dev->hba.lmmio_name;

#अगर 1
	/* We want the CPU -> IO routing of addresses.
	 * The SBA BASE/MASK रेजिस्टरs control CPU -> IO routing.
	 * Ask SBA what is routed to this rope/LBA.
	 */
	sba_distributed_lmmio(pa_dev, r);
#अन्यथा
	/*
	 * The LBA BASE/MASK रेजिस्टरs control IO -> System routing.
	 *
	 * The following code works but करोesn't get us what we want.
	 * Well, only because firmware (v5.0) on C3000 करोesn't program
	 * the LBA BASE/MASE रेजिस्टरs to be the exact inverse of 
	 * the corresponding SBA रेजिस्टरs. Other Astro/Pluto
	 * based platक्रमm firmware may करो it right.
	 *
	 * Should someone want to mess with MSI, they may need to
	 * reprogram LBA BASE/MASK रेजिस्टरs. Thus preserve the code
	 * below until MSI is known to work on C3000/A500/N4000/RP3440.
	 *
	 * Using the code below, /proc/iomem shows:
	 * ...
	 * f0000000-f0ffffff : PCI00 LMMIO
	 *   f05d0000-f05d0000 : lcd_data
	 *   f05d0008-f05d0008 : lcd_cmd
	 * f1000000-f1ffffff : PCI01 LMMIO
	 * f4000000-f4ffffff : PCI02 LMMIO
	 *   f4000000-f4001fff : sym53c8xx
	 *   f4002000-f4003fff : sym53c8xx
	 *   f4004000-f40043ff : sym53c8xx
	 *   f4005000-f40053ff : sym53c8xx
	 *   f4007000-f4007fff : ohci_hcd
	 *   f4008000-f40083ff : tulip
	 * f6000000-f6ffffff : PCI03 LMMIO
	 * f8000000-fbffffff : PCI00 ELMMIO
	 *   fa100000-fa4fffff : stअगरb mmio
	 *   fb000000-fb1fffff : stअगरb fb
	 *
	 * But everything listed under PCI02 actually lives under PCI00.
	 * This is clearly wrong.
	 *
	 * Asking SBA how things are routed tells the correct story:
	 * LMMIO_BASE/MASK/ROUTE f4000001 fc000000 00000000
	 * सूची0_BASE/MASK/ROUTE fa000001 fe000000 00000006
	 * सूची1_BASE/MASK/ROUTE f9000001 ff000000 00000004
	 * सूची2_BASE/MASK/ROUTE f0000000 fc000000 00000000
	 * सूची3_BASE/MASK/ROUTE f0000000 fc000000 00000000
	 *
	 * Which looks like this in /proc/iomem:
	 * f4000000-f47fffff : PCI00 LMMIO
	 *   f4000000-f4001fff : sym53c8xx
	 *   ...[deteled core devices - same as above]...
	 *   f4008000-f40083ff : tulip
	 * f4800000-f4ffffff : PCI01 LMMIO
	 * f6000000-f67fffff : PCI02 LMMIO
	 * f7000000-f77fffff : PCI03 LMMIO
	 * f9000000-f9ffffff : PCI02 ELMMIO
	 * fa000000-fbffffff : PCI03 ELMMIO
	 *   fa100000-fa4fffff : stअगरb mmio
	 *   fb000000-fb1fffff : stअगरb fb
	 *
	 * ie all Built-in core are under now correctly under PCI00.
	 * The "PCI02 ELMMIO" directed range is क्रम:
	 *  +-[02]---03.0  3Dfx Interactive, Inc. Vooकरोo 2
	 *
	 * All is well now.
	 */
	r->start = READ_REG32(lba_dev->hba.base_addr + LBA_LMMIO_BASE);
	अगर (r->start & 1) अणु
		अचिन्हित दीर्घ rsize;

		r->flags = IORESOURCE_MEM;
		/* mmio_mask also clears Enable bit */
		r->start &= mmio_mask;
		r->start = PCI_HOST_ADDR(&lba_dev->hba, r->start);
		rsize = ~ READ_REG32(lba_dev->hba.base_addr + LBA_LMMIO_MASK);

		/*
		** Each rope only माला_लो part of the distributed range.
		** Adjust "window" क्रम this rope.
		*/
		rsize /= ROPES_PER_IOC;
		r->start += (rsize + 1) * LBA_NUM(pa_dev->hpa.start);
		r->end = r->start + rsize;
	पूर्ण अन्यथा अणु
		r->end = r->start = 0;	/* Not enabled. */
	पूर्ण
#पूर्ण_अगर

	/*
	** "Directed" ranges are used when the "distributed range" isn't
	** sufficient क्रम all devices below a given LBA.  Typically devices
	** like graphics cards or X25 may need a directed range when the
	** bus has multiple slots (ie multiple devices) or the device
	** needs more than the typical 4 or 8MB a distributed range offers.
	**
	** The मुख्य reason क्रम ignoring it now frigging complications.
	** Directed ranges may overlap (and have precedence) over
	** distributed ranges. Or a distributed range asचिन्हित to a unused
	** rope may be used by a directed range on a dअगरferent rope.
	** Support क्रम graphics devices may require fixing this
	** since they may be asचिन्हित a directed range which overlaps
	** an existing (but unused portion of) distributed range.
	*/
	r = &(lba_dev->hba.elmmio_space);
	प्र_लिखो(lba_dev->hba.elmmio_name, "PCI%02x ELMMIO",
					(पूर्णांक)lba_dev->hba.bus_num.start);
	r->name  = lba_dev->hba.elmmio_name;

#अगर 1
	/* See comment which precedes call to sba_directed_lmmio() */
	sba_directed_lmmio(pa_dev, r);
#अन्यथा
	r->start = READ_REG32(lba_dev->hba.base_addr + LBA_ELMMIO_BASE);

	अगर (r->start & 1) अणु
		अचिन्हित दीर्घ rsize;
		r->flags = IORESOURCE_MEM;
		/* mmio_mask also clears Enable bit */
		r->start &= mmio_mask;
		r->start = PCI_HOST_ADDR(&lba_dev->hba, r->start);
		rsize = READ_REG32(lba_dev->hba.base_addr + LBA_ELMMIO_MASK);
		r->end = r->start + ~rsize;
	पूर्ण
#पूर्ण_अगर

	r = &(lba_dev->hba.io_space);
	प्र_लिखो(lba_dev->hba.io_name, "PCI%02x Ports",
					(पूर्णांक)lba_dev->hba.bus_num.start);
	r->name  = lba_dev->hba.io_name;
	r->flags = IORESOURCE_IO;
	r->start = READ_REG32(lba_dev->hba.base_addr + LBA_IOS_BASE) & ~1L;
	r->end   = r->start + (READ_REG32(lba_dev->hba.base_addr + LBA_IOS_MASK) ^ (HBA_PORT_SPACE_SIZE - 1));

	/* Virtualize the I/O Port space ranges */
	lba_num = HBA_PORT_BASE(lba_dev->hba.hba_num);
	r->start |= lba_num;
	r->end   |= lba_num;
पूर्ण


/**************************************************************************
**
**   LBA initialization code (HW and SW)
**
**   o identअगरy LBA chip itself
**   o initialize LBA chip modes (HardFail)
**   o FIXME: initialize DMA hपूर्णांकs क्रम reasonable शेषs
**   o enable configuration functions
**   o call pci_रेजिस्टर_ops() to discover devs (fixup/fixup_bus get invoked)
**
**************************************************************************/

अटल पूर्णांक __init
lba_hw_init(काष्ठा lba_device *d)
अणु
	u32 stat;
	u32 bus_reset;	/* PDC_PAT_BUG */

#अगर 0
	prपूर्णांकk(KERN_DEBUG "LBA %lx  STAT_CTL %Lx  ERROR_CFG %Lx  STATUS %Lx DMA_CTL %Lx\n",
		d->hba.base_addr,
		READ_REG64(d->hba.base_addr + LBA_STAT_CTL),
		READ_REG64(d->hba.base_addr + LBA_ERROR_CONFIG),
		READ_REG64(d->hba.base_addr + LBA_ERROR_STATUS),
		READ_REG64(d->hba.base_addr + LBA_DMA_CTL) );
	prपूर्णांकk(KERN_DEBUG "	ARB mask %Lx  pri %Lx  mode %Lx  mtlt %Lx\n",
		READ_REG64(d->hba.base_addr + LBA_ARB_MASK),
		READ_REG64(d->hba.base_addr + LBA_ARB_PRI),
		READ_REG64(d->hba.base_addr + LBA_ARB_MODE),
		READ_REG64(d->hba.base_addr + LBA_ARB_MTLT) );
	prपूर्णांकk(KERN_DEBUG "	HINT cfg 0x%Lx\n",
		READ_REG64(d->hba.base_addr + LBA_HINT_CFG));
	prपूर्णांकk(KERN_DEBUG "	HINT reg ");
	अणु पूर्णांक i;
	क्रम (i=LBA_HINT_BASE; i< (14*8 + LBA_HINT_BASE); i+=8)
		prपूर्णांकk(" %Lx", READ_REG64(d->hba.base_addr + i));
	पूर्ण
	prपूर्णांकk("\n");
#पूर्ण_अगर	/* DEBUG_LBA_PAT */

#अगर_घोषित CONFIG_64BIT
/*
 * FIXME add support क्रम PDC_PAT_IO "Get slot status" - OLAR support
 * Only N-Class and up can really make use of Get slot status.
 * maybe L-class too but I've never played with it there.
 */
#पूर्ण_अगर

	/* PDC_PAT_BUG: exhibited in rev 40.48  on L2000 */
	bus_reset = READ_REG32(d->hba.base_addr + LBA_STAT_CTL + 4) & 1;
	अगर (bus_reset) अणु
		prपूर्णांकk(KERN_DEBUG "NOTICE: PCI bus reset still asserted! (clearing)\n");
	पूर्ण

	stat = READ_REG32(d->hba.base_addr + LBA_ERROR_CONFIG);
	अगर (stat & LBA_SMART_MODE) अणु
		prपूर्णांकk(KERN_DEBUG "NOTICE: LBA in SMART mode! (cleared)\n");
		stat &= ~LBA_SMART_MODE;
		WRITE_REG32(stat, d->hba.base_addr + LBA_ERROR_CONFIG);
	पूर्ण


	/*
	 * Hard Fail vs. Soft Fail on PCI "Master Abort".
	 *
	 * "Master Abort" means the MMIO transaction समयd out - usually due to
	 * the device not responding to an MMIO पढ़ो. We would like HF to be
	 * enabled to find driver problems, though it means the प्रणाली will
	 * crash with a HPMC.
	 *
	 * In SoftFail mode "~0L" is वापसed as a result of a समयout on the
	 * pci bus. This is like how PCI busses on x86 and most other
	 * architectures behave.  In order to increase compatibility with
	 * existing (x86) PCI hardware and existing Linux drivers we enable
	 * Soft Faul mode on PA-RISC now too.
	 */
        stat = READ_REG32(d->hba.base_addr + LBA_STAT_CTL);
#अगर defined(ENABLE_HARDFAIL)
	WRITE_REG32(stat | HF_ENABLE, d->hba.base_addr + LBA_STAT_CTL);
#अन्यथा
	WRITE_REG32(stat & ~HF_ENABLE, d->hba.base_addr + LBA_STAT_CTL);
#पूर्ण_अगर

	/*
	** Writing a zero to STAT_CTL.rf (bit 0) will clear reset संकेत
	** अगर it's not alपढ़ोy set. If we just cleared the PCI Bus Reset
	** संकेत, रुको a bit क्रम the PCI devices to recover and setup.
	*/
	अगर (bus_reset)
		mdelay(pci_post_reset_delay);

	अगर (0 == READ_REG32(d->hba.base_addr + LBA_ARB_MASK)) अणु
		/*
		** PDC_PAT_BUG: PDC rev 40.48 on L2000.
		** B2000/C3600/J6000 also have this problem?
		** 
		** Elroys with hot pluggable slots करोn't get configured
		** correctly अगर the slot is empty.  ARB_MASK is set to 0
		** and we can't master transactions on the bus if it's
		** not at least one. 0x3 enables elroy and first slot.
		*/
		prपूर्णांकk(KERN_DEBUG "NOTICE: Enabling PCI Arbitration\n");
		WRITE_REG32(0x3, d->hba.base_addr + LBA_ARB_MASK);
	पूर्ण

	/*
	** FIXME: Hपूर्णांक रेजिस्टरs are programmed with शेष hपूर्णांक
	** values by firmware. Hपूर्णांकs should be sane even अगर we
	** can't reprogram them the way drivers want.
	*/
	वापस 0;
पूर्ण

/*
 * Unक्रमtunately, when firmware numbers busses, it करोesn't take पूर्णांकo account
 * Cardbus bridges.  So we have to rक्रमागतber the busses to suit ourselves.
 * Elroy/Mercury करोn't actually know what bus number they're attached to;
 * we use bus 0 to indicate the directly attached bus and any other bus
 * number will be taken care of by the PCI-PCI bridge.
 */
अटल अचिन्हित पूर्णांक lba_next_bus = 0;

/*
 * Determine अगर lba should claim this chip (वापस 0) or not (वापस 1).
 * If so, initialize the chip and tell other partners in crime they
 * have work to करो.
 */
अटल पूर्णांक __init
lba_driver_probe(काष्ठा parisc_device *dev)
अणु
	काष्ठा lba_device *lba_dev;
	LIST_HEAD(resources);
	काष्ठा pci_bus *lba_bus;
	काष्ठा pci_ops *cfg_ops;
	u32 func_class;
	व्योम *पंचांगp_obj;
	अक्षर *version;
	व्योम __iomem *addr = ioremap(dev->hpa.start, 4096);
	पूर्णांक max;

	/* Read HW Rev First */
	func_class = READ_REG32(addr + LBA_FCLASS);

	अगर (IS_ELROY(dev)) अणु	
		func_class &= 0xf;
		चयन (func_class) अणु
		हाल 0:	version = "TR1.0"; अवरोध;
		हाल 1:	version = "TR2.0"; अवरोध;
		हाल 2:	version = "TR2.1"; अवरोध;
		हाल 3:	version = "TR2.2"; अवरोध;
		हाल 4:	version = "TR3.0"; अवरोध;
		हाल 5:	version = "TR4.0"; अवरोध;
		शेष: version = "TR4+";
		पूर्ण

		prपूर्णांकk(KERN_INFO "Elroy version %s (0x%x) found at 0x%lx\n",
		       version, func_class & 0xf, (दीर्घ)dev->hpa.start);

		अगर (func_class < 2) अणु
			prपूर्णांकk(KERN_WARNING "Can't support LBA older than "
				"TR2.1 - continuing under adversity.\n");
		पूर्ण

#अगर 0
/* Elroy TR4.0 should work with simple algorithm.
   But it करोesn't.  Still missing something. *sigh*
*/
		अगर (func_class > 4) अणु
			cfg_ops = &mercury_cfg_ops;
		पूर्ण अन्यथा
#पूर्ण_अगर
		अणु
			cfg_ops = &elroy_cfg_ops;
		पूर्ण

	पूर्ण अन्यथा अगर (IS_MERCURY(dev) || IS_QUICKSILVER(dev)) अणु
		पूर्णांक major, minor;

		func_class &= 0xff;
		major = func_class >> 4, minor = func_class & 0xf;

		/* We could use one prपूर्णांकk क्रम both Elroy and Mercury,
                 * but क्रम the mask क्रम func_class.
                 */ 
		prपूर्णांकk(KERN_INFO "%s version TR%d.%d (0x%x) found at 0x%lx\n",
		       IS_MERCURY(dev) ? "Mercury" : "Quicksilver", major,
		       minor, func_class, (दीर्घ)dev->hpa.start);

		cfg_ops = &mercury_cfg_ops;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "Unknown LBA found at 0x%lx\n",
			(दीर्घ)dev->hpa.start);
		वापस -ENODEV;
	पूर्ण

	/* Tell I/O SAPIC driver we have a IRQ handler/region. */
	पंचांगp_obj = iosapic_रेजिस्टर(dev->hpa.start + LBA_IOSAPIC_BASE);

	/* NOTE: PCI devices (e.g. 103c:1005 graphics card) which करोn't
	**	have an IRT entry will get शून्य back from iosapic code.
	*/
	
	lba_dev = kzalloc(माप(काष्ठा lba_device), GFP_KERNEL);
	अगर (!lba_dev) अणु
		prपूर्णांकk(KERN_ERR "lba_init_chip - couldn't alloc lba_device\n");
		वापस(1);
	पूर्ण


	/* ---------- First : initialize data we alपढ़ोy have --------- */

	lba_dev->hw_rev = func_class;
	lba_dev->hba.base_addr = addr;
	lba_dev->hba.dev = dev;
	lba_dev->iosapic_obj = पंचांगp_obj;  /* save पूर्णांकerrupt handle */
	lba_dev->hba.iommu = sba_get_iommu(dev);  /* get iommu data */
	parisc_set_drvdata(dev, lba_dev);

	/* ------------ Second : initialize common stuff ---------- */
	pci_bios = &lba_bios_ops;
	pcibios_रेजिस्टर_hba(&lba_dev->hba);
	spin_lock_init(&lba_dev->lba_lock);

	अगर (lba_hw_init(lba_dev))
		वापस(1);

	/* ---------- Third : setup I/O Port and MMIO resources  --------- */

	अगर (is_pdc_pat()) अणु
		/* PDC PAT firmware uses PIOP region of GMMIO space. */
		pci_port = &lba_pat_port_ops;
		/* Go ask PDC PAT what resources this LBA has */
		lba_pat_resources(dev, lba_dev);
	पूर्ण अन्यथा अणु
		अगर (!astro_iop_base) अणु
			/* Sprockets PDC uses NPIOP region */
			astro_iop_base = ioremap(LBA_PORT_BASE, 64 * 1024);
			pci_port = &lba_astro_port_ops;
		पूर्ण

		/* Poke the chip a bit क्रम /proc output */
		lba_legacy_resources(dev, lba_dev);
	पूर्ण

	अगर (lba_dev->hba.bus_num.start < lba_next_bus)
		lba_dev->hba.bus_num.start = lba_next_bus;

	/*   Overlaps with elmmio can (and should) fail here.
	 *   We will prune (or ignore) the distributed range.
	 *
	 *   FIXME: SBA code should रेजिस्टर all elmmio ranges first.
	 *      that would take care of elmmio ranges routed
	 *	to a dअगरferent rope (alपढ़ोy discovered) from
	 *	getting रेजिस्टरed *after* LBA code has alपढ़ोy
	 *	रेजिस्टरed it's distributed lmmio range.
	 */
	अगर (truncate_pat_collision(&iomem_resource,
				   &(lba_dev->hba.lmmio_space))) अणु
		prपूर्णांकk(KERN_WARNING "LBA: lmmio_space [%lx/%lx] duplicate!\n",
				(दीर्घ)lba_dev->hba.lmmio_space.start,
				(दीर्घ)lba_dev->hba.lmmio_space.end);
		lba_dev->hba.lmmio_space.flags = 0;
	पूर्ण

	pci_add_resource_offset(&resources, &lba_dev->hba.io_space,
				HBA_PORT_BASE(lba_dev->hba.hba_num));
	अगर (lba_dev->hba.elmmio_space.flags)
		pci_add_resource_offset(&resources, &lba_dev->hba.elmmio_space,
					lba_dev->hba.lmmio_space_offset);
	अगर (lba_dev->hba.lmmio_space.flags)
		pci_add_resource_offset(&resources, &lba_dev->hba.lmmio_space,
					lba_dev->hba.lmmio_space_offset);
	अगर (lba_dev->hba.gmmio_space.flags) अणु
		/* Not रेजिस्टरing GMMIO space - according to करोcs it's not
		 * even used on HP-UX. */
		/* pci_add_resource(&resources, &lba_dev->hba.gmmio_space); */
	पूर्ण

	pci_add_resource(&resources, &lba_dev->hba.bus_num);

	dev->dev.platक्रमm_data = lba_dev;
	lba_bus = lba_dev->hba.hba_bus =
		pci_create_root_bus(&dev->dev, lba_dev->hba.bus_num.start,
				    cfg_ops, शून्य, &resources);
	अगर (!lba_bus) अणु
		pci_मुक्त_resource_list(&resources);
		वापस 0;
	पूर्ण

	max = pci_scan_child_bus(lba_bus);

	/* This is in lieu of calling pci_assign_unasचिन्हित_resources() */
	अगर (is_pdc_pat()) अणु
		/* assign resources to un-initialized devices */

		DBG_PAT("LBA pci_bus_size_bridges()\n");
		pci_bus_size_bridges(lba_bus);

		DBG_PAT("LBA pci_bus_assign_resources()\n");
		pci_bus_assign_resources(lba_bus);

#अगर_घोषित DEBUG_LBA_PAT
		DBG_PAT("\nLBA PIOP resource tree\n");
		lba_dump_res(&lba_dev->hba.io_space, 2);
		DBG_PAT("\nLBA LMMIO resource tree\n");
		lba_dump_res(&lba_dev->hba.lmmio_space, 2);
#पूर्ण_अगर
	पूर्ण

	/*
	** Once PCI रेजिस्टर ops has walked the bus, access to config
	** space is restricted. Aव्योमs master पातs on config cycles.
	** Early LBA revs go fatal on *any* master पात.
	*/
	अगर (cfg_ops == &elroy_cfg_ops) अणु
		lba_dev->flags |= LBA_FLAG_SKIP_PROBE;
	पूर्ण

	lba_next_bus = max + 1;
	pci_bus_add_devices(lba_bus);

	/* Whew! Finally करोne! Tell services we got this one covered. */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा parisc_device_id lba_tbl[] __initस्थिर = अणु
	अणु HPHW_BRIDGE, HVERSION_REV_ANY_ID, ELROY_HVERS, 0xa पूर्ण,
	अणु HPHW_BRIDGE, HVERSION_REV_ANY_ID, MERCURY_HVERS, 0xa पूर्ण,
	अणु HPHW_BRIDGE, HVERSION_REV_ANY_ID, QUICKSILVER_HVERS, 0xa पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल काष्ठा parisc_driver lba_driver __refdata = अणु
	.name =		MODULE_NAME,
	.id_table =	lba_tbl,
	.probe =	lba_driver_probe,
पूर्ण;

/*
** One समय initialization to let the world know the LBA was found.
** Must be called exactly once beक्रमe pci_init().
*/
व्योम __init lba_init(व्योम)
अणु
	रेजिस्टर_parisc_driver(&lba_driver);
पूर्ण

/*
** Initialize the IBASE/IMASK रेजिस्टरs क्रम LBA (Elroy).
** Only called from sba_iommu.c in order to route ranges (MMIO vs DMA).
** sba_iommu is responsible क्रम locking (none needed at init समय).
*/
व्योम lba_set_iregs(काष्ठा parisc_device *lba, u32 ibase, u32 imask)
अणु
	व्योम __iomem * base_addr = ioremap(lba->hpa.start, 4096);

	imask <<= 2;	/* adjust क्रम hपूर्णांकs - 2 more bits */

	/* Make sure we aren't trying to set bits that aren't ग_लिखोable. */
	WARN_ON((ibase & 0x001fffff) != 0);
	WARN_ON((imask & 0x001fffff) != 0);
	
	DBG("%s() ibase 0x%x imask 0x%x\n", __func__, ibase, imask);
	WRITE_REG32( imask, base_addr + LBA_IMASK);
	WRITE_REG32( ibase, base_addr + LBA_IBASE);
	iounmap(base_addr);
पूर्ण


/*
 * The design of the Diva management card in rp34x0 machines (rp3410, rp3440)
 * seems rushed, so that many built-in components simply करोn't work.
 * The following quirks disable the serial AUX port and the built-in ATI RV100
 * Radeon 7000 graphics card which both करोn't have any बाह्यal connectors and
 * thus are useless, and even worse, e.g. the AUX port occupies ttyS0 and as
 * such makes those machines the only PARISC machines on which we can't use
 * ttyS0 as boot console.
 */
अटल व्योम quirk_भागa_ati_card(काष्ठा pci_dev *dev)
अणु
	अगर (dev->subप्रणाली_venकरोr != PCI_VENDOR_ID_HP ||
	    dev->subप्रणाली_device != 0x1292)
		वापस;

	dev_info(&dev->dev, "Hiding Diva built-in ATI card");
	dev->device = 0;
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_QY,
	quirk_भागa_ati_card);

अटल व्योम quirk_भागa_aux_disable(काष्ठा pci_dev *dev)
अणु
	अगर (dev->subप्रणाली_venकरोr != PCI_VENDOR_ID_HP ||
	    dev->subप्रणाली_device != 0x1291)
		वापस;

	dev_info(&dev->dev, "Hiding Diva built-in AUX serial device");
	dev->device = 0;
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_HP, PCI_DEVICE_ID_HP_DIVA_AUX,
	quirk_भागa_aux_disable);

अटल व्योम quirk_tosca_aux_disable(काष्ठा pci_dev *dev)
अणु
	अगर (dev->subप्रणाली_venकरोr != PCI_VENDOR_ID_HP ||
	    dev->subप्रणाली_device != 0x104a)
		वापस;

	dev_info(&dev->dev, "Hiding Tosca secondary built-in AUX serial device");
	dev->device = 0;
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_HP, PCI_DEVICE_ID_HP_DIVA,
	quirk_tosca_aux_disable);
