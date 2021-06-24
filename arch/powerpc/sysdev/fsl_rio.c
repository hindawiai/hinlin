<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale MPC85xx/MPC86xx RapidIO support
 *
 * Copyright 2009 Sysgo AG
 * Thomas Moll <thomas.moll@sysgo.com>
 * - fixed मुख्यtenance access routines, check क्रम aligned access
 *
 * Copyright 2009 Integrated Device Technology, Inc.
 * Alex Bounine <alexandre.bounine@idt.com>
 * - Added Port-Write message handling
 * - Added Machine Check exception handling
 *
 * Copyright (C) 2007, 2008, 2010, 2011 Freescale Semiconductor, Inc.
 * Zhang Wei <wei.zhang@मुक्तscale.com>
 *
 * Copyright 2005 MontaVista Software, Inc.
 * Matt Porter <mporter@kernel.crashing.org>
 */

#समावेश <linux/init.h>
#समावेश <linux/extable.h>
#समावेश <linux/types.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>

#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/machdep.h>

#समावेश "fsl_rio.h"

#अघोषित DEBUG_PW	/* Port-Write debugging */

#घोषणा RIO_PORT1_EDCSR		0x0640
#घोषणा RIO_PORT2_EDCSR		0x0680
#घोषणा RIO_PORT1_IECSR		0x10130
#घोषणा RIO_PORT2_IECSR		0x101B0

#घोषणा RIO_GCCSR		0x13c
#घोषणा RIO_ESCSR		0x158
#घोषणा ESCSR_CLEAR		0x07120204
#घोषणा RIO_PORT2_ESCSR		0x178
#घोषणा RIO_CCSR		0x15c
#घोषणा RIO_LTLEDCSR_IER	0x80000000
#घोषणा RIO_LTLEDCSR_PRT	0x01000000
#घोषणा IECSR_CLEAR		0x80000000
#घोषणा RIO_ISR_AACR		0x10120
#घोषणा RIO_ISR_AACR_AA		0x1	/* Accept All ID */

#घोषणा RIWTAR_TRAD_VAL_SHIFT	12
#घोषणा RIWTAR_TRAD_MASK	0x00FFFFFF
#घोषणा RIWBAR_BADD_VAL_SHIFT	12
#घोषणा RIWBAR_BADD_MASK	0x003FFFFF
#घोषणा RIWAR_ENABLE		0x80000000
#घोषणा RIWAR_TGINT_LOCAL	0x00F00000
#घोषणा RIWAR_RDTYP_NO_SNOOP	0x00040000
#घोषणा RIWAR_RDTYP_SNOOP	0x00050000
#घोषणा RIWAR_WRTYP_NO_SNOOP	0x00004000
#घोषणा RIWAR_WRTYP_SNOOP	0x00005000
#घोषणा RIWAR_WRTYP_ALLOC	0x00006000
#घोषणा RIWAR_SIZE_MASK		0x0000003F

अटल DEFINE_SPINLOCK(fsl_rio_config_lock);

#घोषणा __fsl_पढ़ो_rio_config(x, addr, err, op)		\
	__यंत्र__ __अस्थिर__(				\
		"1:	"op" %1,0(%2)\n"		\
		"	eieio\n"			\
		"2:\n"					\
		".section .fixup,\"ax\"\n"		\
		"3:	li %1,-1\n"			\
		"	li %0,%3\n"			\
		"	b 2b\n"				\
		".previous\n"				\
		EX_TABLE(1b, 3b)			\
		: "=r" (err), "=r" (x)			\
		: "b" (addr), "i" (-EFAULT), "0" (err))

व्योम __iomem *rio_regs_win;
व्योम __iomem *rmu_regs_win;
resource_माप_प्रकार rio_law_start;

काष्ठा fsl_rio_dbell *dbell;
काष्ठा fsl_rio_pw *pw;

#अगर_घोषित CONFIG_E500
पूर्णांक fsl_rio_mcheck_exception(काष्ठा pt_regs *regs)
अणु
	स्थिर काष्ठा exception_table_entry *entry;
	अचिन्हित दीर्घ reason;

	अगर (!rio_regs_win)
		वापस 0;

	reason = in_be32((u32 *)(rio_regs_win + RIO_LTLEDCSR));
	अगर (reason & (RIO_LTLEDCSR_IER | RIO_LTLEDCSR_PRT)) अणु
		/* Check अगर we are prepared to handle this fault */
		entry = search_exception_tables(regs->nip);
		अगर (entry) अणु
			pr_debug("RIO: %s - MC Exception handled\n",
				 __func__);
			out_be32((u32 *)(rio_regs_win + RIO_LTLEDCSR),
				 0);
			regs->msr |= MSR_RI;
			regs->nip = extable_fixup(entry);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_rio_mcheck_exception);
#पूर्ण_अगर

/**
 * fsl_local_config_पढ़ो - Generate a MPC85xx local config space पढ़ो
 * @mport: RapidIO master port info
 * @index: ID of RapdiIO पूर्णांकerface
 * @offset: Offset पूर्णांकo configuration space
 * @len: Length (in bytes) of the मुख्यtenance transaction
 * @data: Value to be पढ़ो पूर्णांकo
 *
 * Generates a MPC85xx local configuration space पढ़ो. Returns %0 on
 * success or %-EINVAL on failure.
 */
अटल पूर्णांक fsl_local_config_पढ़ो(काष्ठा rio_mport *mport,
				पूर्णांक index, u32 offset, पूर्णांक len, u32 *data)
अणु
	काष्ठा rio_priv *priv = mport->priv;
	pr_debug("fsl_local_config_read: index %d offset %8.8x\n", index,
		 offset);
	*data = in_be32(priv->regs_win + offset);

	वापस 0;
पूर्ण

/**
 * fsl_local_config_ग_लिखो - Generate a MPC85xx local config space ग_लिखो
 * @mport: RapidIO master port info
 * @index: ID of RapdiIO पूर्णांकerface
 * @offset: Offset पूर्णांकo configuration space
 * @len: Length (in bytes) of the मुख्यtenance transaction
 * @data: Value to be written
 *
 * Generates a MPC85xx local configuration space ग_लिखो. Returns %0 on
 * success or %-EINVAL on failure.
 */
अटल पूर्णांक fsl_local_config_ग_लिखो(काष्ठा rio_mport *mport,
				पूर्णांक index, u32 offset, पूर्णांक len, u32 data)
अणु
	काष्ठा rio_priv *priv = mport->priv;
	pr_debug
		("fsl_local_config_write: index %d offset %8.8x data %8.8x\n",
		index, offset, data);
	out_be32(priv->regs_win + offset, data);

	वापस 0;
पूर्ण

/**
 * fsl_rio_config_पढ़ो - Generate a MPC85xx पढ़ो मुख्यtenance transaction
 * @mport: RapidIO master port info
 * @index: ID of RapdiIO पूर्णांकerface
 * @destid: Destination ID of transaction
 * @hopcount: Number of hops to target device
 * @offset: Offset पूर्णांकo configuration space
 * @len: Length (in bytes) of the मुख्यtenance transaction
 * @val: Location to be पढ़ो पूर्णांकo
 *
 * Generates a MPC85xx पढ़ो मुख्यtenance transaction. Returns %0 on
 * success or %-EINVAL on failure.
 */
अटल पूर्णांक
fsl_rio_config_पढ़ो(काष्ठा rio_mport *mport, पूर्णांक index, u16 destid,
			u8 hopcount, u32 offset, पूर्णांक len, u32 *val)
अणु
	काष्ठा rio_priv *priv = mport->priv;
	अचिन्हित दीर्घ flags;
	u8 *data;
	u32 rval, err = 0;

	pr_debug
		("fsl_rio_config_read:"
		" index %d destid %d hopcount %d offset %8.8x len %d\n",
		index, destid, hopcount, offset, len);

	/* 16MB मुख्यtenance winकरोw possible */
	/* allow only aligned access to मुख्यtenance रेजिस्टरs */
	अगर (offset > (0x1000000 - len) || !IS_ALIGNED(offset, len))
		वापस -EINVAL;

	spin_lock_irqsave(&fsl_rio_config_lock, flags);

	out_be32(&priv->मुख्यt_aपंचांगu_regs->rowtar,
		 (destid << 22) | (hopcount << 12) | (offset >> 12));
	out_be32(&priv->मुख्यt_aपंचांगu_regs->rowtear, (destid >> 10));

	data = (u8 *) priv->मुख्यt_win + (offset & (RIO_MAINT_WIN_SIZE - 1));
	चयन (len) अणु
	हाल 1:
		__fsl_पढ़ो_rio_config(rval, data, err, "lbz");
		अवरोध;
	हाल 2:
		__fsl_पढ़ो_rio_config(rval, data, err, "lhz");
		अवरोध;
	हाल 4:
		__fsl_पढ़ो_rio_config(rval, data, err, "lwz");
		अवरोध;
	शेष:
		spin_unlock_irqrestore(&fsl_rio_config_lock, flags);
		वापस -EINVAL;
	पूर्ण

	अगर (err) अणु
		pr_debug("RIO: cfg_read error %d for %x:%x:%x\n",
			 err, destid, hopcount, offset);
	पूर्ण

	spin_unlock_irqrestore(&fsl_rio_config_lock, flags);
	*val = rval;

	वापस err;
पूर्ण

/**
 * fsl_rio_config_ग_लिखो - Generate a MPC85xx ग_लिखो मुख्यtenance transaction
 * @mport: RapidIO master port info
 * @index: ID of RapdiIO पूर्णांकerface
 * @destid: Destination ID of transaction
 * @hopcount: Number of hops to target device
 * @offset: Offset पूर्णांकo configuration space
 * @len: Length (in bytes) of the मुख्यtenance transaction
 * @val: Value to be written
 *
 * Generates an MPC85xx ग_लिखो मुख्यtenance transaction. Returns %0 on
 * success or %-EINVAL on failure.
 */
अटल पूर्णांक
fsl_rio_config_ग_लिखो(काष्ठा rio_mport *mport, पूर्णांक index, u16 destid,
			u8 hopcount, u32 offset, पूर्णांक len, u32 val)
अणु
	काष्ठा rio_priv *priv = mport->priv;
	अचिन्हित दीर्घ flags;
	u8 *data;
	पूर्णांक ret = 0;

	pr_debug
		("fsl_rio_config_write:"
		" index %d destid %d hopcount %d offset %8.8x len %d val %8.8x\n",
		index, destid, hopcount, offset, len, val);

	/* 16MB मुख्यtenance winकरोws possible */
	/* allow only aligned access to मुख्यtenance रेजिस्टरs */
	अगर (offset > (0x1000000 - len) || !IS_ALIGNED(offset, len))
		वापस -EINVAL;

	spin_lock_irqsave(&fsl_rio_config_lock, flags);

	out_be32(&priv->मुख्यt_aपंचांगu_regs->rowtar,
		 (destid << 22) | (hopcount << 12) | (offset >> 12));
	out_be32(&priv->मुख्यt_aपंचांगu_regs->rowtear, (destid >> 10));

	data = (u8 *) priv->मुख्यt_win + (offset & (RIO_MAINT_WIN_SIZE - 1));
	चयन (len) अणु
	हाल 1:
		out_8((u8 *) data, val);
		अवरोध;
	हाल 2:
		out_be16((u16 *) data, val);
		अवरोध;
	हाल 4:
		out_be32((u32 *) data, val);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	spin_unlock_irqrestore(&fsl_rio_config_lock, flags);

	वापस ret;
पूर्ण

अटल व्योम fsl_rio_inbound_mem_init(काष्ठा rio_priv *priv)
अणु
	पूर्णांक i;

	/* बंद inbound winकरोws */
	क्रम (i = 0; i < RIO_INB_ATMU_COUNT; i++)
		out_be32(&priv->inb_aपंचांगu_regs[i].riwar, 0);
पूर्ण

पूर्णांक fsl_map_inb_mem(काष्ठा rio_mport *mport, dma_addr_t lstart,
	u64 rstart, u64 size, u32 flags)
अणु
	काष्ठा rio_priv *priv = mport->priv;
	u32 base_size;
	अचिन्हित पूर्णांक base_size_log;
	u64 win_start, win_end;
	u32 riwar;
	पूर्णांक i;

	अगर ((size & (size - 1)) != 0 || size > 0x400000000ULL)
		वापस -EINVAL;

	base_size_log = ilog2(size);
	base_size = 1 << base_size_log;

	/* check अगर addresses are aligned with the winकरोw size */
	अगर (lstart & (base_size - 1))
		वापस -EINVAL;
	अगर (rstart & (base_size - 1))
		वापस -EINVAL;

	/* check क्रम conflicting ranges */
	क्रम (i = 0; i < RIO_INB_ATMU_COUNT; i++) अणु
		riwar = in_be32(&priv->inb_aपंचांगu_regs[i].riwar);
		अगर ((riwar & RIWAR_ENABLE) == 0)
			जारी;
		win_start = ((u64)(in_be32(&priv->inb_aपंचांगu_regs[i].riwbar) & RIWBAR_BADD_MASK))
			<< RIWBAR_BADD_VAL_SHIFT;
		win_end = win_start + ((1 << ((riwar & RIWAR_SIZE_MASK) + 1)) - 1);
		अगर (rstart < win_end && (rstart + size) > win_start)
			वापस -EINVAL;
	पूर्ण

	/* find unused aपंचांगu */
	क्रम (i = 0; i < RIO_INB_ATMU_COUNT; i++) अणु
		riwar = in_be32(&priv->inb_aपंचांगu_regs[i].riwar);
		अगर ((riwar & RIWAR_ENABLE) == 0)
			अवरोध;
	पूर्ण
	अगर (i >= RIO_INB_ATMU_COUNT)
		वापस -ENOMEM;

	out_be32(&priv->inb_aपंचांगu_regs[i].riwtar, lstart >> RIWTAR_TRAD_VAL_SHIFT);
	out_be32(&priv->inb_aपंचांगu_regs[i].riwbar, rstart >> RIWBAR_BADD_VAL_SHIFT);
	out_be32(&priv->inb_aपंचांगu_regs[i].riwar, RIWAR_ENABLE | RIWAR_TGINT_LOCAL |
		RIWAR_RDTYP_SNOOP | RIWAR_WRTYP_SNOOP | (base_size_log - 1));

	वापस 0;
पूर्ण

व्योम fsl_unmap_inb_mem(काष्ठा rio_mport *mport, dma_addr_t lstart)
अणु
	u32 win_start_shअगरt, base_start_shअगरt;
	काष्ठा rio_priv *priv = mport->priv;
	u32 riwar, riwtar;
	पूर्णांक i;

	/* skip शेष winकरोw */
	base_start_shअगरt = lstart >> RIWTAR_TRAD_VAL_SHIFT;
	क्रम (i = 0; i < RIO_INB_ATMU_COUNT; i++) अणु
		riwar = in_be32(&priv->inb_aपंचांगu_regs[i].riwar);
		अगर ((riwar & RIWAR_ENABLE) == 0)
			जारी;

		riwtar = in_be32(&priv->inb_aपंचांगu_regs[i].riwtar);
		win_start_shअगरt = riwtar & RIWTAR_TRAD_MASK;
		अगर (win_start_shअगरt == base_start_shअगरt) अणु
			out_be32(&priv->inb_aपंचांगu_regs[i].riwar, riwar & ~RIWAR_ENABLE);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

व्योम fsl_rio_port_error_handler(पूर्णांक offset)
अणु
	/*XXX: Error recovery is not implemented, we just clear errors */
	out_be32((u32 *)(rio_regs_win + RIO_LTLEDCSR), 0);

	अगर (offset == 0) अणु
		out_be32((u32 *)(rio_regs_win + RIO_PORT1_EDCSR), 0);
		out_be32((u32 *)(rio_regs_win + RIO_PORT1_IECSR), IECSR_CLEAR);
		out_be32((u32 *)(rio_regs_win + RIO_ESCSR), ESCSR_CLEAR);
	पूर्ण अन्यथा अणु
		out_be32((u32 *)(rio_regs_win + RIO_PORT2_EDCSR), 0);
		out_be32((u32 *)(rio_regs_win + RIO_PORT2_IECSR), IECSR_CLEAR);
		out_be32((u32 *)(rio_regs_win + RIO_PORT2_ESCSR), ESCSR_CLEAR);
	पूर्ण
पूर्ण
अटल अंतरभूत व्योम fsl_rio_info(काष्ठा device *dev, u32 ccsr)
अणु
	स्थिर अक्षर *str;
	अगर (ccsr & 1) अणु
		/* Serial phy */
		चयन (ccsr >> 30) अणु
		हाल 0:
			str = "1";
			अवरोध;
		हाल 1:
			str = "4";
			अवरोध;
		शेष:
			str = "Unknown";
			अवरोध;
		पूर्ण
		dev_info(dev, "Hardware port width: %s\n", str);

		चयन ((ccsr >> 27) & 7) अणु
		हाल 0:
			str = "Single-lane 0";
			अवरोध;
		हाल 1:
			str = "Single-lane 2";
			अवरोध;
		हाल 2:
			str = "Four-lane";
			अवरोध;
		शेष:
			str = "Unknown";
			अवरोध;
		पूर्ण
		dev_info(dev, "Training connection status: %s\n", str);
	पूर्ण अन्यथा अणु
		/* Parallel phy */
		अगर (!(ccsr & 0x80000000))
			dev_info(dev, "Output port operating in 8-bit mode\n");
		अगर (!(ccsr & 0x08000000))
			dev_info(dev, "Input port operating in 8-bit mode\n");
	पूर्ण
पूर्ण

/**
 * fsl_rio_setup - Setup Freescale PowerPC RapidIO पूर्णांकerface
 * @dev: platक्रमm_device poपूर्णांकer
 *
 * Initializes MPC85xx RapidIO hardware पूर्णांकerface, configures
 * master port with प्रणाली-specअगरic info, and रेजिस्टरs the
 * master port with the RapidIO subप्रणाली.
 */
पूर्णांक fsl_rio_setup(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा rio_ops *ops;
	काष्ठा rio_mport *port;
	काष्ठा rio_priv *priv;
	पूर्णांक rc = 0;
	स्थिर u32 *dt_range, *cell, *port_index;
	u32 active_ports = 0;
	काष्ठा resource regs, rmu_regs;
	काष्ठा device_node *np, *rmu_node;
	पूर्णांक rlen;
	u32 ccsr;
	u64 range_start, range_size;
	पूर्णांक paw, aw, sw;
	u32 i;
	अटल पूर्णांक पंचांगp;
	काष्ठा device_node *rmu_np[MAX_MSG_UNIT_NUM] = अणुशून्यपूर्ण;

	अगर (!dev->dev.of_node) अणु
		dev_err(&dev->dev, "Device OF-Node is NULL");
		वापस -ENODEV;
	पूर्ण

	rc = of_address_to_resource(dev->dev.of_node, 0, &regs);
	अगर (rc) अणु
		dev_err(&dev->dev, "Can't get %pOF property 'reg'\n",
				dev->dev.of_node);
		वापस -EFAULT;
	पूर्ण
	dev_info(&dev->dev, "Of-device full name %pOF\n",
			dev->dev.of_node);
	dev_info(&dev->dev, "Regs: %pR\n", &regs);

	rio_regs_win = ioremap(regs.start, resource_size(&regs));
	अगर (!rio_regs_win) अणु
		dev_err(&dev->dev, "Unable to map rio register window\n");
		rc = -ENOMEM;
		जाओ err_rio_regs;
	पूर्ण

	ops = kzalloc(माप(काष्ठा rio_ops), GFP_KERNEL);
	अगर (!ops) अणु
		rc = -ENOMEM;
		जाओ err_ops;
	पूर्ण
	ops->lcपढ़ो = fsl_local_config_पढ़ो;
	ops->lcग_लिखो = fsl_local_config_ग_लिखो;
	ops->cपढ़ो = fsl_rio_config_पढ़ो;
	ops->cग_लिखो = fsl_rio_config_ग_लिखो;
	ops->dsend = fsl_rio_करोorbell_send;
	ops->pwenable = fsl_rio_pw_enable;
	ops->खोलो_outb_mbox = fsl_खोलो_outb_mbox;
	ops->खोलो_inb_mbox = fsl_खोलो_inb_mbox;
	ops->बंद_outb_mbox = fsl_बंद_outb_mbox;
	ops->बंद_inb_mbox = fsl_बंद_inb_mbox;
	ops->add_outb_message = fsl_add_outb_message;
	ops->add_inb_buffer = fsl_add_inb_buffer;
	ops->get_inb_message = fsl_get_inb_message;
	ops->map_inb = fsl_map_inb_mem;
	ops->unmap_inb = fsl_unmap_inb_mem;

	rmu_node = of_parse_phandle(dev->dev.of_node, "fsl,srio-rmu-handle", 0);
	अगर (!rmu_node) अणु
		dev_err(&dev->dev, "No valid fsl,srio-rmu-handle property\n");
		rc = -ENOENT;
		जाओ err_rmu;
	पूर्ण
	rc = of_address_to_resource(rmu_node, 0, &rmu_regs);
	अगर (rc) अणु
		dev_err(&dev->dev, "Can't get %pOF property 'reg'\n",
				rmu_node);
		जाओ err_rmu;
	पूर्ण
	rmu_regs_win = ioremap(rmu_regs.start, resource_size(&rmu_regs));
	अगर (!rmu_regs_win) अणु
		dev_err(&dev->dev, "Unable to map rmu register window\n");
		rc = -ENOMEM;
		जाओ err_rmu;
	पूर्ण
	क्रम_each_compatible_node(np, शून्य, "fsl,srio-msg-unit") अणु
		rmu_np[पंचांगp] = np;
		पंचांगp++;
	पूर्ण

	/*set up करोobell node*/
	np = of_find_compatible_node(शून्य, शून्य, "fsl,srio-dbell-unit");
	अगर (!np) अणु
		dev_err(&dev->dev, "No fsl,srio-dbell-unit node\n");
		rc = -ENODEV;
		जाओ err_dbell;
	पूर्ण
	dbell = kzalloc(माप(काष्ठा fsl_rio_dbell), GFP_KERNEL);
	अगर (!(dbell)) अणु
		dev_err(&dev->dev, "Can't alloc memory for 'fsl_rio_dbell'\n");
		rc = -ENOMEM;
		जाओ err_dbell;
	पूर्ण
	dbell->dev = &dev->dev;
	dbell->bellirq = irq_of_parse_and_map(np, 1);
	dev_info(&dev->dev, "bellirq: %d\n", dbell->bellirq);

	aw = of_n_addr_cells(np);
	dt_range = of_get_property(np, "reg", &rlen);
	अगर (!dt_range) अणु
		pr_err("%pOF: unable to find 'reg' property\n",
			np);
		rc = -ENOMEM;
		जाओ err_pw;
	पूर्ण
	range_start = of_पढ़ो_number(dt_range, aw);
	dbell->dbell_regs = (काष्ठा rio_dbell_regs *)(rmu_regs_win +
				(u32)range_start);

	/*set up port ग_लिखो node*/
	np = of_find_compatible_node(शून्य, शून्य, "fsl,srio-port-write-unit");
	अगर (!np) अणु
		dev_err(&dev->dev, "No fsl,srio-port-write-unit node\n");
		rc = -ENODEV;
		जाओ err_pw;
	पूर्ण
	pw = kzalloc(माप(काष्ठा fsl_rio_pw), GFP_KERNEL);
	अगर (!(pw)) अणु
		dev_err(&dev->dev, "Can't alloc memory for 'fsl_rio_pw'\n");
		rc = -ENOMEM;
		जाओ err_pw;
	पूर्ण
	pw->dev = &dev->dev;
	pw->pwirq = irq_of_parse_and_map(np, 0);
	dev_info(&dev->dev, "pwirq: %d\n", pw->pwirq);
	aw = of_n_addr_cells(np);
	dt_range = of_get_property(np, "reg", &rlen);
	अगर (!dt_range) अणु
		pr_err("%pOF: unable to find 'reg' property\n",
			np);
		rc = -ENOMEM;
		जाओ err;
	पूर्ण
	range_start = of_पढ़ो_number(dt_range, aw);
	pw->pw_regs = (काष्ठा rio_pw_regs *)(rmu_regs_win + (u32)range_start);

	/*set up ports node*/
	क्रम_each_child_of_node(dev->dev.of_node, np) अणु
		port_index = of_get_property(np, "cell-index", शून्य);
		अगर (!port_index) अणु
			dev_err(&dev->dev, "Can't get %pOF property 'cell-index'\n",
					np);
			जारी;
		पूर्ण

		dt_range = of_get_property(np, "ranges", &rlen);
		अगर (!dt_range) अणु
			dev_err(&dev->dev, "Can't get %pOF property 'ranges'\n",
					np);
			जारी;
		पूर्ण

		/* Get node address wide */
		cell = of_get_property(np, "#address-cells", शून्य);
		अगर (cell)
			aw = *cell;
		अन्यथा
			aw = of_n_addr_cells(np);
		/* Get node size wide */
		cell = of_get_property(np, "#size-cells", शून्य);
		अगर (cell)
			sw = *cell;
		अन्यथा
			sw = of_n_size_cells(np);
		/* Get parent address wide wide */
		paw = of_n_addr_cells(np);
		range_start = of_पढ़ो_number(dt_range + aw, paw);
		range_size = of_पढ़ो_number(dt_range + aw + paw, sw);

		dev_info(&dev->dev, "%pOF: LAW start 0x%016llx, size 0x%016llx.\n",
				np, range_start, range_size);

		port = kzalloc(माप(काष्ठा rio_mport), GFP_KERNEL);
		अगर (!port)
			जारी;

		rc = rio_mport_initialize(port);
		अगर (rc) अणु
			kमुक्त(port);
			जारी;
		पूर्ण

		i = *port_index - 1;
		port->index = (अचिन्हित अक्षर)i;

		priv = kzalloc(माप(काष्ठा rio_priv), GFP_KERNEL);
		अगर (!priv) अणु
			dev_err(&dev->dev, "Can't alloc memory for 'priv'\n");
			kमुक्त(port);
			जारी;
		पूर्ण

		INIT_LIST_HEAD(&port->dbells);
		port->iores.start = range_start;
		port->iores.end = port->iores.start + range_size - 1;
		port->iores.flags = IORESOURCE_MEM;
		port->iores.name = "rio_io_win";

		अगर (request_resource(&iomem_resource, &port->iores) < 0) अणु
			dev_err(&dev->dev, "RIO: Error requesting master port region"
				" 0x%016llx-0x%016llx\n",
				(u64)port->iores.start, (u64)port->iores.end);
				kमुक्त(priv);
				kमुक्त(port);
				जारी;
		पूर्ण
		प्र_लिखो(port->name, "RIO mport %d", i);

		priv->dev = &dev->dev;
		port->dev.parent = &dev->dev;
		port->ops = ops;
		port->priv = priv;
		port->phys_efptr = 0x100;
		port->phys_rmap = 1;
		priv->regs_win = rio_regs_win;

		ccsr = in_be32(priv->regs_win + RIO_CCSR + i*0x20);

		/* Checking the port training status */
		अगर (in_be32((priv->regs_win + RIO_ESCSR + i*0x20)) & 1) अणु
			dev_err(&dev->dev, "Port %d is not ready. "
			"Try to restart connection...\n", i);
			/* Disable ports */
			out_be32(priv->regs_win
				+ RIO_CCSR + i*0x20, 0);
			/* Set 1x lane */
			setbits32(priv->regs_win
				+ RIO_CCSR + i*0x20, 0x02000000);
			/* Enable ports */
			setbits32(priv->regs_win
				+ RIO_CCSR + i*0x20, 0x00600000);
			msleep(100);
			अगर (in_be32((priv->regs_win
					+ RIO_ESCSR + i*0x20)) & 1) अणु
				dev_err(&dev->dev,
					"Port %d restart failed.\n", i);
				release_resource(&port->iores);
				kमुक्त(priv);
				kमुक्त(port);
				जारी;
			पूर्ण
			dev_info(&dev->dev, "Port %d restart success!\n", i);
		पूर्ण
		fsl_rio_info(&dev->dev, ccsr);

		port->sys_size = (in_be32((priv->regs_win + RIO_PEF_CAR))
					& RIO_PEF_CTLS) >> 4;
		dev_info(&dev->dev, "RapidIO Common Transport System size: %d\n",
				port->sys_size ? 65536 : 256);

		अगर (port->host_deviceid >= 0)
			out_be32(priv->regs_win + RIO_GCCSR, RIO_PORT_GEN_HOST |
				RIO_PORT_GEN_MASTER | RIO_PORT_GEN_DISCOVERED);
		अन्यथा
			out_be32(priv->regs_win + RIO_GCCSR,
				RIO_PORT_GEN_MASTER);

		priv->aपंचांगu_regs = (काष्ठा rio_aपंचांगu_regs *)(priv->regs_win
			+ ((i == 0) ? RIO_ATMU_REGS_PORT1_OFFSET :
			RIO_ATMU_REGS_PORT2_OFFSET));

		priv->मुख्यt_aपंचांगu_regs = priv->aपंचांगu_regs + 1;
		priv->inb_aपंचांगu_regs = (काष्ठा rio_inb_aपंचांगu_regs __iomem *)
			(priv->regs_win +
			((i == 0) ? RIO_INB_ATMU_REGS_PORT1_OFFSET :
			RIO_INB_ATMU_REGS_PORT2_OFFSET));

		/* Set to receive packets with any dest ID */
		out_be32((priv->regs_win + RIO_ISR_AACR + i*0x80),
			 RIO_ISR_AACR_AA);

		/* Configure मुख्यtenance transaction winकरोw */
		out_be32(&priv->मुख्यt_aपंचांगu_regs->rowbar,
			port->iores.start >> 12);
		out_be32(&priv->मुख्यt_aपंचांगu_regs->rowar,
			 0x80077000 | (ilog2(RIO_MAINT_WIN_SIZE) - 1));

		priv->मुख्यt_win = ioremap(port->iores.start,
				RIO_MAINT_WIN_SIZE);

		rio_law_start = range_start;

		fsl_rio_setup_rmu(port, rmu_np[i]);
		fsl_rio_inbound_mem_init(priv);

		dbell->mport[i] = port;
		pw->mport[i] = port;

		अगर (rio_रेजिस्टर_mport(port)) अणु
			release_resource(&port->iores);
			kमुक्त(priv);
			kमुक्त(port);
			जारी;
		पूर्ण
		active_ports++;
	पूर्ण

	अगर (!active_ports) अणु
		rc = -ENOLINK;
		जाओ err;
	पूर्ण

	fsl_rio_करोorbell_init(dbell);
	fsl_rio_port_ग_लिखो_init(pw);

	वापस 0;
err:
	kमुक्त(pw);
	pw = शून्य;
err_pw:
	kमुक्त(dbell);
	dbell = शून्य;
err_dbell:
	iounmap(rmu_regs_win);
	rmu_regs_win = शून्य;
err_rmu:
	kमुक्त(ops);
err_ops:
	iounmap(rio_regs_win);
	rio_regs_win = शून्य;
err_rio_regs:
	वापस rc;
पूर्ण

/* The probe function क्रम RapidIO peer-to-peer network.
 */
अटल पूर्णांक fsl_of_rio_rpn_probe(काष्ठा platक्रमm_device *dev)
अणु
	prपूर्णांकk(KERN_INFO "Setting up RapidIO peer-to-peer network %pOF\n",
			dev->dev.of_node);

	वापस fsl_rio_setup(dev);
पूर्ण;

अटल स्थिर काष्ठा of_device_id fsl_of_rio_rpn_ids[] = अणु
	अणु
		.compatible = "fsl,srio",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver fsl_of_rio_rpn_driver = अणु
	.driver = अणु
		.name = "fsl-of-rio",
		.of_match_table = fsl_of_rio_rpn_ids,
	पूर्ण,
	.probe = fsl_of_rio_rpn_probe,
पूर्ण;

अटल __init पूर्णांक fsl_of_rio_rpn_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&fsl_of_rio_rpn_driver);
पूर्ण

subsys_initcall(fsl_of_rio_rpn_init);
