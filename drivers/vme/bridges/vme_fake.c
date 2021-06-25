<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Fake VME bridge support.
 *
 * This drive provides a fake VME bridge chip, this enables debugging of the
 * VME framework in the असलence of a VME प्रणाली.
 *
 * This driver has to करो a number of things in software that would be driven
 * by hardware अगर it was available, it will also result in extra overhead at
 * बार when compared with driving actual hardware.
 *
 * Author: Martyn Welch <martyn@welches.me.uk>
 * Copyright (c) 2014 Martyn Welch
 *
 * Based on vme_tsi148.c:
 *
 * Author: Martyn Welch <martyn.welch@ge.com>
 * Copyright 2008 GE Intelligent Platक्रमms Embedded Systems, Inc.
 *
 * Based on work by Tom Armistead and Ajit Prem
 * Copyright 2004 Motorola Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/vme.h>

#समावेश "../vme_bridge.h"

/*
 *  Define the number of each that the fake driver supports.
 */
#घोषणा FAKE_MAX_MASTER		8	/* Max Master Winकरोws */
#घोषणा FAKE_MAX_SLAVE		8	/* Max Slave Winकरोws */

/* Structures to hold inक्रमmation normally held in device रेजिस्टरs */
काष्ठा fake_slave_winकरोw अणु
	पूर्णांक enabled;
	अचिन्हित दीर्घ दीर्घ vme_base;
	अचिन्हित दीर्घ दीर्घ size;
	व्योम *buf_base;
	u32 aspace;
	u32 cycle;
पूर्ण;

काष्ठा fake_master_winकरोw अणु
	पूर्णांक enabled;
	अचिन्हित दीर्घ दीर्घ vme_base;
	अचिन्हित दीर्घ दीर्घ size;
	u32 aspace;
	u32 cycle;
	u32 dwidth;
पूर्ण;

/* Structure used to hold driver specअगरic inक्रमmation */
काष्ठा fake_driver अणु
	काष्ठा vme_bridge *parent;
	काष्ठा fake_slave_winकरोw slaves[FAKE_MAX_SLAVE];
	काष्ठा fake_master_winकरोw masters[FAKE_MAX_MASTER];
	u32 lm_enabled;
	अचिन्हित दीर्घ दीर्घ lm_base;
	u32 lm_aspace;
	u32 lm_cycle;
	व्योम (*lm_callback[4])(व्योम *);
	व्योम *lm_data[4];
	काष्ठा tasklet_काष्ठा पूर्णांक_tasklet;
	पूर्णांक पूर्णांक_level;
	पूर्णांक पूर्णांक_statid;
	व्योम *crcsr_kernel;
	dma_addr_t crcsr_bus;
	/* Only one VME पूर्णांकerrupt can be generated at a समय, provide locking */
	काष्ठा mutex vme_पूर्णांक;
पूर्ण;

/* Module parameter */
अटल पूर्णांक geoid;

अटल स्थिर अक्षर driver_name[] = "vme_fake";

अटल काष्ठा vme_bridge *निकास_poपूर्णांकer;

अटल काष्ठा device *vme_root;

/*
 * Calling VME bus पूर्णांकerrupt callback अगर provided.
 */
अटल व्योम fake_VIRQ_tasklet(अचिन्हित दीर्घ data)
अणु
	काष्ठा vme_bridge *fake_bridge;
	काष्ठा fake_driver *bridge;

	fake_bridge = (काष्ठा vme_bridge *) data;
	bridge = fake_bridge->driver_priv;

	vme_irq_handler(fake_bridge, bridge->पूर्णांक_level, bridge->पूर्णांक_statid);
पूर्ण

/*
 * Configure VME पूर्णांकerrupt
 */
अटल व्योम fake_irq_set(काष्ठा vme_bridge *fake_bridge, पूर्णांक level,
		पूर्णांक state, पूर्णांक sync)
अणु
	/* Nothing to करो */
पूर्ण

अटल व्योम *fake_pci_to_ptr(dma_addr_t addr)
अणु
	वापस (व्योम *)(uपूर्णांकptr_t)addr;
पूर्ण

अटल dma_addr_t fake_ptr_to_pci(व्योम *addr)
अणु
	वापस (dma_addr_t)(uपूर्णांकptr_t)addr;
पूर्ण

/*
 * Generate a VME bus पूर्णांकerrupt at the requested level & vector. Wait क्रम
 * पूर्णांकerrupt to be acked.
 */
अटल पूर्णांक fake_irq_generate(काष्ठा vme_bridge *fake_bridge, पूर्णांक level,
		पूर्णांक statid)
अणु
	काष्ठा fake_driver *bridge;

	bridge = fake_bridge->driver_priv;

	mutex_lock(&bridge->vme_पूर्णांक);

	bridge->पूर्णांक_level = level;

	bridge->पूर्णांक_statid = statid;

	/*
	 * Schedule tasklet to run VME handler to emulate normal VME पूर्णांकerrupt
	 * handler behaviour.
	 */
	tasklet_schedule(&bridge->पूर्णांक_tasklet);

	mutex_unlock(&bridge->vme_पूर्णांक);

	वापस 0;
पूर्ण

/*
 * Initialize a slave winकरोw with the requested attributes.
 */
अटल पूर्णांक fake_slave_set(काष्ठा vme_slave_resource *image, पूर्णांक enabled,
		अचिन्हित दीर्घ दीर्घ vme_base, अचिन्हित दीर्घ दीर्घ size,
		dma_addr_t buf_base, u32 aspace, u32 cycle)
अणु
	अचिन्हित पूर्णांक i, granularity = 0;
	अचिन्हित दीर्घ दीर्घ vme_bound;
	काष्ठा vme_bridge *fake_bridge;
	काष्ठा fake_driver *bridge;

	fake_bridge = image->parent;
	bridge = fake_bridge->driver_priv;

	i = image->number;

	चयन (aspace) अणु
	हाल VME_A16:
		granularity = 0x10;
		अवरोध;
	हाल VME_A24:
		granularity = 0x1000;
		अवरोध;
	हाल VME_A32:
		granularity = 0x10000;
		अवरोध;
	हाल VME_A64:
		granularity = 0x10000;
		अवरोध;
	हाल VME_CRCSR:
	हाल VME_USER1:
	हाल VME_USER2:
	हाल VME_USER3:
	हाल VME_USER4:
	शेष:
		pr_err("Invalid address space\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Bound address is a valid address क्रम the winकरोw, adjust
	 * accordingly
	 */
	vme_bound = vme_base + size - granularity;

	अगर (vme_base & (granularity - 1)) अणु
		pr_err("Invalid VME base alignment\n");
		वापस -EINVAL;
	पूर्ण
	अगर (vme_bound & (granularity - 1)) अणु
		pr_err("Invalid VME bound alignment\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&image->mtx);

	bridge->slaves[i].enabled = enabled;
	bridge->slaves[i].vme_base = vme_base;
	bridge->slaves[i].size = size;
	bridge->slaves[i].buf_base = fake_pci_to_ptr(buf_base);
	bridge->slaves[i].aspace = aspace;
	bridge->slaves[i].cycle = cycle;

	mutex_unlock(&image->mtx);

	वापस 0;
पूर्ण

/*
 * Get slave winकरोw configuration.
 */
अटल पूर्णांक fake_slave_get(काष्ठा vme_slave_resource *image, पूर्णांक *enabled,
		अचिन्हित दीर्घ दीर्घ *vme_base, अचिन्हित दीर्घ दीर्घ *size,
		dma_addr_t *buf_base, u32 *aspace, u32 *cycle)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा fake_driver *bridge;

	bridge = image->parent->driver_priv;

	i = image->number;

	mutex_lock(&image->mtx);

	*enabled = bridge->slaves[i].enabled;
	*vme_base = bridge->slaves[i].vme_base;
	*size = bridge->slaves[i].size;
	*buf_base = fake_ptr_to_pci(bridge->slaves[i].buf_base);
	*aspace = bridge->slaves[i].aspace;
	*cycle = bridge->slaves[i].cycle;

	mutex_unlock(&image->mtx);

	वापस 0;
पूर्ण

/*
 * Set the attributes of an outbound winकरोw.
 */
अटल पूर्णांक fake_master_set(काष्ठा vme_master_resource *image, पूर्णांक enabled,
		अचिन्हित दीर्घ दीर्घ vme_base, अचिन्हित दीर्घ दीर्घ size,
		u32 aspace, u32 cycle, u32 dwidth)
अणु
	पूर्णांक retval = 0;
	अचिन्हित पूर्णांक i;
	काष्ठा vme_bridge *fake_bridge;
	काष्ठा fake_driver *bridge;

	fake_bridge = image->parent;

	bridge = fake_bridge->driver_priv;

	/* Verअगरy input data */
	अगर (vme_base & 0xFFFF) अणु
		pr_err("Invalid VME Window alignment\n");
		retval = -EINVAL;
		जाओ err_winकरोw;
	पूर्ण

	अगर (size & 0xFFFF) अणु
		pr_err("Invalid size alignment\n");
		retval = -EINVAL;
		जाओ err_winकरोw;
	पूर्ण

	अगर ((size == 0) && (enabled != 0)) अणु
		pr_err("Size must be non-zero for enabled windows\n");
		retval = -EINVAL;
		जाओ err_winकरोw;
	पूर्ण

	/* Setup data width */
	चयन (dwidth) अणु
	हाल VME_D8:
	हाल VME_D16:
	हाल VME_D32:
		अवरोध;
	शेष:
		pr_err("Invalid data width\n");
		retval = -EINVAL;
		जाओ err_dwidth;
	पूर्ण

	/* Setup address space */
	चयन (aspace) अणु
	हाल VME_A16:
	हाल VME_A24:
	हाल VME_A32:
	हाल VME_A64:
	हाल VME_CRCSR:
	हाल VME_USER1:
	हाल VME_USER2:
	हाल VME_USER3:
	हाल VME_USER4:
		अवरोध;
	शेष:
		pr_err("Invalid address space\n");
		retval = -EINVAL;
		जाओ err_aspace;
	पूर्ण

	spin_lock(&image->lock);

	i = image->number;

	bridge->masters[i].enabled = enabled;
	bridge->masters[i].vme_base = vme_base;
	bridge->masters[i].size = size;
	bridge->masters[i].aspace = aspace;
	bridge->masters[i].cycle = cycle;
	bridge->masters[i].dwidth = dwidth;

	spin_unlock(&image->lock);

	वापस 0;

err_aspace:
err_dwidth:
err_winकरोw:
	वापस retval;

पूर्ण

/*
 * Set the attributes of an outbound winकरोw.
 */
अटल पूर्णांक __fake_master_get(काष्ठा vme_master_resource *image, पूर्णांक *enabled,
		अचिन्हित दीर्घ दीर्घ *vme_base, अचिन्हित दीर्घ दीर्घ *size,
		u32 *aspace, u32 *cycle, u32 *dwidth)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा fake_driver *bridge;

	bridge = image->parent->driver_priv;

	i = image->number;

	*enabled = bridge->masters[i].enabled;
	*vme_base = bridge->masters[i].vme_base;
	*size = bridge->masters[i].size;
	*aspace = bridge->masters[i].aspace;
	*cycle = bridge->masters[i].cycle;
	*dwidth = bridge->masters[i].dwidth;

	वापस 0;
पूर्ण


अटल पूर्णांक fake_master_get(काष्ठा vme_master_resource *image, पूर्णांक *enabled,
		अचिन्हित दीर्घ दीर्घ *vme_base, अचिन्हित दीर्घ दीर्घ *size,
		u32 *aspace, u32 *cycle, u32 *dwidth)
अणु
	पूर्णांक retval;

	spin_lock(&image->lock);

	retval = __fake_master_get(image, enabled, vme_base, size, aspace,
			cycle, dwidth);

	spin_unlock(&image->lock);

	वापस retval;
पूर्ण


अटल व्योम fake_lm_check(काष्ठा fake_driver *bridge, अचिन्हित दीर्घ दीर्घ addr,
			  u32 aspace, u32 cycle)
अणु
	काष्ठा vme_bridge *fake_bridge;
	अचिन्हित दीर्घ दीर्घ lm_base;
	u32 lm_aspace, lm_cycle;
	पूर्णांक i;
	काष्ठा vme_lm_resource *lm;
	काष्ठा list_head *pos = शून्य, *n;

	/* Get vme_bridge */
	fake_bridge = bridge->parent;

	/* Loop through each location monitor resource */
	list_क्रम_each_safe(pos, n, &fake_bridge->lm_resources) अणु
		lm = list_entry(pos, काष्ठा vme_lm_resource, list);

		/* If disabled, we're करोne */
		अगर (bridge->lm_enabled == 0)
			वापस;

		lm_base = bridge->lm_base;
		lm_aspace = bridge->lm_aspace;
		lm_cycle = bridge->lm_cycle;

		/* First make sure that the cycle and address space match */
		अगर ((lm_aspace == aspace) && (lm_cycle == cycle)) अणु
			क्रम (i = 0; i < lm->monitors; i++) अणु
				/* Each location monitor covers 8 bytes */
				अगर (((lm_base + (8 * i)) <= addr) &&
				    ((lm_base + (8 * i) + 8) > addr)) अणु
					अगर (bridge->lm_callback[i])
						bridge->lm_callback[i](
							bridge->lm_data[i]);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल noअंतरभूत_क्रम_stack u8 fake_vmeपढ़ो8(काष्ठा fake_driver *bridge,
					   अचिन्हित दीर्घ दीर्घ addr,
					   u32 aspace, u32 cycle)
अणु
	u8 retval = 0xff;
	पूर्णांक i;
	अचिन्हित दीर्घ दीर्घ start, end, offset;
	u8 *loc;

	क्रम (i = 0; i < FAKE_MAX_SLAVE; i++) अणु
		start = bridge->slaves[i].vme_base;
		end = bridge->slaves[i].vme_base + bridge->slaves[i].size;

		अगर (aspace != bridge->slaves[i].aspace)
			जारी;

		अगर (cycle != bridge->slaves[i].cycle)
			जारी;

		अगर ((addr >= start) && (addr < end)) अणु
			offset = addr - bridge->slaves[i].vme_base;
			loc = (u8 *)(bridge->slaves[i].buf_base + offset);
			retval = *loc;

			अवरोध;
		पूर्ण
	पूर्ण

	fake_lm_check(bridge, addr, aspace, cycle);

	वापस retval;
पूर्ण

अटल noअंतरभूत_क्रम_stack u16 fake_vmeपढ़ो16(काष्ठा fake_driver *bridge,
					     अचिन्हित दीर्घ दीर्घ addr,
					     u32 aspace, u32 cycle)
अणु
	u16 retval = 0xffff;
	पूर्णांक i;
	अचिन्हित दीर्घ दीर्घ start, end, offset;
	u16 *loc;

	क्रम (i = 0; i < FAKE_MAX_SLAVE; i++) अणु
		अगर (aspace != bridge->slaves[i].aspace)
			जारी;

		अगर (cycle != bridge->slaves[i].cycle)
			जारी;

		start = bridge->slaves[i].vme_base;
		end = bridge->slaves[i].vme_base + bridge->slaves[i].size;

		अगर ((addr >= start) && ((addr + 1) < end)) अणु
			offset = addr - bridge->slaves[i].vme_base;
			loc = (u16 *)(bridge->slaves[i].buf_base + offset);
			retval = *loc;

			अवरोध;
		पूर्ण
	पूर्ण

	fake_lm_check(bridge, addr, aspace, cycle);

	वापस retval;
पूर्ण

अटल noअंतरभूत_क्रम_stack u32 fake_vmeपढ़ो32(काष्ठा fake_driver *bridge,
					     अचिन्हित दीर्घ दीर्घ addr,
					     u32 aspace, u32 cycle)
अणु
	u32 retval = 0xffffffff;
	पूर्णांक i;
	अचिन्हित दीर्घ दीर्घ start, end, offset;
	u32 *loc;

	क्रम (i = 0; i < FAKE_MAX_SLAVE; i++) अणु
		अगर (aspace != bridge->slaves[i].aspace)
			जारी;

		अगर (cycle != bridge->slaves[i].cycle)
			जारी;

		start = bridge->slaves[i].vme_base;
		end = bridge->slaves[i].vme_base + bridge->slaves[i].size;

		अगर ((addr >= start) && ((addr + 3) < end)) अणु
			offset = addr - bridge->slaves[i].vme_base;
			loc = (u32 *)(bridge->slaves[i].buf_base + offset);
			retval = *loc;

			अवरोध;
		पूर्ण
	पूर्ण

	fake_lm_check(bridge, addr, aspace, cycle);

	वापस retval;
पूर्ण

अटल sमाप_प्रकार fake_master_पढ़ो(काष्ठा vme_master_resource *image, व्योम *buf,
		माप_प्रकार count, loff_t offset)
अणु
	पूर्णांक retval;
	u32 aspace, cycle, dwidth;
	काष्ठा vme_bridge *fake_bridge;
	काष्ठा fake_driver *priv;
	पूर्णांक i;
	अचिन्हित दीर्घ दीर्घ addr;
	अचिन्हित पूर्णांक करोne = 0;
	अचिन्हित पूर्णांक count32;

	fake_bridge = image->parent;

	priv = fake_bridge->driver_priv;

	i = image->number;

	addr = (अचिन्हित दीर्घ दीर्घ)priv->masters[i].vme_base + offset;
	aspace = priv->masters[i].aspace;
	cycle = priv->masters[i].cycle;
	dwidth = priv->masters[i].dwidth;

	spin_lock(&image->lock);

	/* The following code handles VME address alignment. We cannot use
	 * स_नकल_xxx here because it may cut data transfers in to 8-bit
	 * cycles when D16 or D32 cycles are required on the VME bus.
	 * On the other hand, the bridge itself assures that the maximum data
	 * cycle configured क्रम the transfer is used and splits it
	 * स्वतःmatically क्रम non-aligned addresses, so we करोn't want the
	 * overhead of needlessly क्रमcing small transfers क्रम the entire cycle.
	 */
	अगर (addr & 0x1) अणु
		*(u8 *)buf = fake_vmeपढ़ो8(priv, addr, aspace, cycle);
		करोne += 1;
		अगर (करोne == count)
			जाओ out;
	पूर्ण
	अगर ((dwidth == VME_D16) || (dwidth == VME_D32)) अणु
		अगर ((addr + करोne) & 0x2) अणु
			अगर ((count - करोne) < 2) अणु
				*(u8 *)(buf + करोne) = fake_vmeपढ़ो8(priv,
						addr + करोne, aspace, cycle);
				करोne += 1;
				जाओ out;
			पूर्ण अन्यथा अणु
				*(u16 *)(buf + करोne) = fake_vmeपढ़ो16(priv,
						addr + करोne, aspace, cycle);
				करोne += 2;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (dwidth == VME_D32) अणु
		count32 = (count - करोne) & ~0x3;
		जबतक (करोne < count32) अणु
			*(u32 *)(buf + करोne) = fake_vmeपढ़ो32(priv, addr + करोne,
					aspace, cycle);
			करोne += 4;
		पूर्ण
	पूर्ण अन्यथा अगर (dwidth == VME_D16) अणु
		count32 = (count - करोne) & ~0x3;
		जबतक (करोne < count32) अणु
			*(u16 *)(buf + करोne) = fake_vmeपढ़ो16(priv, addr + करोne,
					aspace, cycle);
			करोne += 2;
		पूर्ण
	पूर्ण अन्यथा अगर (dwidth == VME_D8) अणु
		count32 = (count - करोne);
		जबतक (करोne < count32) अणु
			*(u8 *)(buf + करोne) = fake_vmeपढ़ो8(priv, addr + करोne,
					aspace, cycle);
			करोne += 1;
		पूर्ण

	पूर्ण

	अगर ((dwidth == VME_D16) || (dwidth == VME_D32)) अणु
		अगर ((count - करोne) & 0x2) अणु
			*(u16 *)(buf + करोne) = fake_vmeपढ़ो16(priv, addr + करोne,
					aspace, cycle);
			करोne += 2;
		पूर्ण
	पूर्ण
	अगर ((count - करोne) & 0x1) अणु
		*(u8 *)(buf + करोne) = fake_vmeपढ़ो8(priv, addr + करोne, aspace,
				cycle);
		करोne += 1;
	पूर्ण

out:
	retval = count;

	spin_unlock(&image->lock);

	वापस retval;
पूर्ण

अटल noअंतरभूत_क्रम_stack व्योम fake_vmeग_लिखो8(काष्ठा fake_driver *bridge,
					      u8 *buf, अचिन्हित दीर्घ दीर्घ addr,
					      u32 aspace, u32 cycle)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ दीर्घ start, end, offset;
	u8 *loc;

	क्रम (i = 0; i < FAKE_MAX_SLAVE; i++) अणु
		अगर (aspace != bridge->slaves[i].aspace)
			जारी;

		अगर (cycle != bridge->slaves[i].cycle)
			जारी;

		start = bridge->slaves[i].vme_base;
		end = bridge->slaves[i].vme_base + bridge->slaves[i].size;

		अगर ((addr >= start) && (addr < end)) अणु
			offset = addr - bridge->slaves[i].vme_base;
			loc = (u8 *)((व्योम *)bridge->slaves[i].buf_base + offset);
			*loc = *buf;

			अवरोध;
		पूर्ण
	पूर्ण

	fake_lm_check(bridge, addr, aspace, cycle);

पूर्ण

अटल noअंतरभूत_क्रम_stack व्योम fake_vmeग_लिखो16(काष्ठा fake_driver *bridge,
					       u16 *buf, अचिन्हित दीर्घ दीर्घ addr,
					       u32 aspace, u32 cycle)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ दीर्घ start, end, offset;
	u16 *loc;

	क्रम (i = 0; i < FAKE_MAX_SLAVE; i++) अणु
		अगर (aspace != bridge->slaves[i].aspace)
			जारी;

		अगर (cycle != bridge->slaves[i].cycle)
			जारी;

		start = bridge->slaves[i].vme_base;
		end = bridge->slaves[i].vme_base + bridge->slaves[i].size;

		अगर ((addr >= start) && ((addr + 1) < end)) अणु
			offset = addr - bridge->slaves[i].vme_base;
			loc = (u16 *)((व्योम *)bridge->slaves[i].buf_base + offset);
			*loc = *buf;

			अवरोध;
		पूर्ण
	पूर्ण

	fake_lm_check(bridge, addr, aspace, cycle);

पूर्ण

अटल noअंतरभूत_क्रम_stack व्योम fake_vmeग_लिखो32(काष्ठा fake_driver *bridge,
					       u32 *buf, अचिन्हित दीर्घ दीर्घ addr,
					       u32 aspace, u32 cycle)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ दीर्घ start, end, offset;
	u32 *loc;

	क्रम (i = 0; i < FAKE_MAX_SLAVE; i++) अणु
		अगर (aspace != bridge->slaves[i].aspace)
			जारी;

		अगर (cycle != bridge->slaves[i].cycle)
			जारी;

		start = bridge->slaves[i].vme_base;
		end = bridge->slaves[i].vme_base + bridge->slaves[i].size;

		अगर ((addr >= start) && ((addr + 3) < end)) अणु
			offset = addr - bridge->slaves[i].vme_base;
			loc = (u32 *)((व्योम *)bridge->slaves[i].buf_base + offset);
			*loc = *buf;

			अवरोध;
		पूर्ण
	पूर्ण

	fake_lm_check(bridge, addr, aspace, cycle);

पूर्ण

अटल sमाप_प्रकार fake_master_ग_लिखो(काष्ठा vme_master_resource *image, व्योम *buf,
		माप_प्रकार count, loff_t offset)
अणु
	पूर्णांक retval = 0;
	u32 aspace, cycle, dwidth;
	अचिन्हित दीर्घ दीर्घ addr;
	पूर्णांक i;
	अचिन्हित पूर्णांक करोne = 0;
	अचिन्हित पूर्णांक count32;

	काष्ठा vme_bridge *fake_bridge;
	काष्ठा fake_driver *bridge;

	fake_bridge = image->parent;

	bridge = fake_bridge->driver_priv;

	i = image->number;

	addr = bridge->masters[i].vme_base + offset;
	aspace = bridge->masters[i].aspace;
	cycle = bridge->masters[i].cycle;
	dwidth = bridge->masters[i].dwidth;

	spin_lock(&image->lock);

	/* Here we apply क्रम the same strategy we करो in master_पढ़ो
	 * function in order to assure the correct cycles.
	 */
	अगर (addr & 0x1) अणु
		fake_vmeग_लिखो8(bridge, (u8 *)buf, addr, aspace, cycle);
		करोne += 1;
		अगर (करोne == count)
			जाओ out;
	पूर्ण

	अगर ((dwidth == VME_D16) || (dwidth == VME_D32)) अणु
		अगर ((addr + करोne) & 0x2) अणु
			अगर ((count - करोne) < 2) अणु
				fake_vmeग_लिखो8(bridge, (u8 *)(buf + करोne),
						addr + करोne, aspace, cycle);
				करोne += 1;
				जाओ out;
			पूर्ण अन्यथा अणु
				fake_vmeग_लिखो16(bridge, (u16 *)(buf + करोne),
						addr + करोne, aspace, cycle);
				करोne += 2;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (dwidth == VME_D32) अणु
		count32 = (count - करोne) & ~0x3;
		जबतक (करोne < count32) अणु
			fake_vmeग_लिखो32(bridge, (u32 *)(buf + करोne),
					addr + करोne, aspace, cycle);
			करोne += 4;
		पूर्ण
	पूर्ण अन्यथा अगर (dwidth == VME_D16) अणु
		count32 = (count - करोne) & ~0x3;
		जबतक (करोne < count32) अणु
			fake_vmeग_लिखो16(bridge, (u16 *)(buf + करोne),
					addr + करोne, aspace, cycle);
			करोne += 2;
		पूर्ण
	पूर्ण अन्यथा अगर (dwidth == VME_D8) अणु
		count32 = (count - करोne);
		जबतक (करोne < count32) अणु
			fake_vmeग_लिखो8(bridge, (u8 *)(buf + करोne), addr + करोne,
					aspace, cycle);
			करोne += 1;
		पूर्ण

	पूर्ण

	अगर ((dwidth == VME_D16) || (dwidth == VME_D32)) अणु
		अगर ((count - करोne) & 0x2) अणु
			fake_vmeग_लिखो16(bridge, (u16 *)(buf + करोne),
					addr + करोne, aspace, cycle);
			करोne += 2;
		पूर्ण
	पूर्ण

	अगर ((count - करोne) & 0x1) अणु
		fake_vmeग_लिखो8(bridge, (u8 *)(buf + करोne), addr + करोne, aspace,
				cycle);
		करोne += 1;
	पूर्ण

out:
	retval = count;

	spin_unlock(&image->lock);

	वापस retval;
पूर्ण

/*
 * Perक्रमm an RMW cycle on the VME bus.
 *
 * Requires a previously configured master winकरोw, वापसs final value.
 */
अटल अचिन्हित पूर्णांक fake_master_rmw(काष्ठा vme_master_resource *image,
		अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक compare, अचिन्हित पूर्णांक swap,
		loff_t offset)
अणु
	u32 पंचांगp, base;
	u32 aspace, cycle;
	पूर्णांक i;
	काष्ठा fake_driver *bridge;

	bridge = image->parent->driver_priv;

	/* Find the PCI address that maps to the desired VME address */
	i = image->number;

	base = bridge->masters[i].vme_base;
	aspace = bridge->masters[i].aspace;
	cycle = bridge->masters[i].cycle;

	/* Lock image */
	spin_lock(&image->lock);

	/* Read existing value */
	पंचांगp = fake_vmeपढ़ो32(bridge, base + offset, aspace, cycle);

	/* Perक्रमm check */
	अगर ((पंचांगp && mask) == (compare && mask)) अणु
		पंचांगp = पंचांगp | (mask | swap);
		पंचांगp = पंचांगp & (~mask | swap);

		/* Write back */
		fake_vmeग_लिखो32(bridge, &पंचांगp, base + offset, aspace, cycle);
	पूर्ण

	/* Unlock image */
	spin_unlock(&image->lock);

	वापस पंचांगp;
पूर्ण

/*
 * All 4 location monitors reside at the same base - this is thereक्रमe a
 * प्रणाली wide configuration.
 *
 * This करोes not enable the LM monitor - that should be करोne when the first
 * callback is attached and disabled when the last callback is हटाओd.
 */
अटल पूर्णांक fake_lm_set(काष्ठा vme_lm_resource *lm, अचिन्हित दीर्घ दीर्घ lm_base,
		u32 aspace, u32 cycle)
अणु
	पूर्णांक i;
	काष्ठा vme_bridge *fake_bridge;
	काष्ठा fake_driver *bridge;

	fake_bridge = lm->parent;

	bridge = fake_bridge->driver_priv;

	mutex_lock(&lm->mtx);

	/* If we alपढ़ोy have a callback attached, we can't move it! */
	क्रम (i = 0; i < lm->monitors; i++) अणु
		अगर (bridge->lm_callback[i]) अणु
			mutex_unlock(&lm->mtx);
			pr_err("Location monitor callback attached, can't reset\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	चयन (aspace) अणु
	हाल VME_A16:
	हाल VME_A24:
	हाल VME_A32:
	हाल VME_A64:
		अवरोध;
	शेष:
		mutex_unlock(&lm->mtx);
		pr_err("Invalid address space\n");
		वापस -EINVAL;
	पूर्ण

	bridge->lm_base = lm_base;
	bridge->lm_aspace = aspace;
	bridge->lm_cycle = cycle;

	mutex_unlock(&lm->mtx);

	वापस 0;
पूर्ण

/* Get configuration of the callback monitor and वापस whether it is enabled
 * or disabled.
 */
अटल पूर्णांक fake_lm_get(काष्ठा vme_lm_resource *lm,
		अचिन्हित दीर्घ दीर्घ *lm_base, u32 *aspace, u32 *cycle)
अणु
	काष्ठा fake_driver *bridge;

	bridge = lm->parent->driver_priv;

	mutex_lock(&lm->mtx);

	*lm_base = bridge->lm_base;
	*aspace = bridge->lm_aspace;
	*cycle = bridge->lm_cycle;

	mutex_unlock(&lm->mtx);

	वापस bridge->lm_enabled;
पूर्ण

/*
 * Attach a callback to a specअगरic location monitor.
 *
 * Callback will be passed the monitor triggered.
 */
अटल पूर्णांक fake_lm_attach(काष्ठा vme_lm_resource *lm, पूर्णांक monitor,
		व्योम (*callback)(व्योम *), व्योम *data)
अणु
	काष्ठा vme_bridge *fake_bridge;
	काष्ठा fake_driver *bridge;

	fake_bridge = lm->parent;

	bridge = fake_bridge->driver_priv;

	mutex_lock(&lm->mtx);

	/* Ensure that the location monitor is configured - need PGM or DATA */
	अगर (bridge->lm_cycle == 0) अणु
		mutex_unlock(&lm->mtx);
		pr_err("Location monitor not properly configured\n");
		वापस -EINVAL;
	पूर्ण

	/* Check that a callback isn't alपढ़ोy attached */
	अगर (bridge->lm_callback[monitor]) अणु
		mutex_unlock(&lm->mtx);
		pr_err("Existing callback attached\n");
		वापस -EBUSY;
	पूर्ण

	/* Attach callback */
	bridge->lm_callback[monitor] = callback;
	bridge->lm_data[monitor] = data;

	/* Ensure that global Location Monitor Enable set */
	bridge->lm_enabled = 1;

	mutex_unlock(&lm->mtx);

	वापस 0;
पूर्ण

/*
 * Detach a callback function क्रमn a specअगरic location monitor.
 */
अटल पूर्णांक fake_lm_detach(काष्ठा vme_lm_resource *lm, पूर्णांक monitor)
अणु
	u32 पंचांगp;
	पूर्णांक i;
	काष्ठा fake_driver *bridge;

	bridge = lm->parent->driver_priv;

	mutex_lock(&lm->mtx);

	/* Detach callback */
	bridge->lm_callback[monitor] = शून्य;
	bridge->lm_data[monitor] = शून्य;

	/* If all location monitors disabled, disable global Location Monitor */
	पंचांगp = 0;
	क्रम (i = 0; i < lm->monitors; i++) अणु
		अगर (bridge->lm_callback[i])
			पंचांगp = 1;
	पूर्ण

	अगर (पंचांगp == 0)
		bridge->lm_enabled = 0;

	mutex_unlock(&lm->mtx);

	वापस 0;
पूर्ण

/*
 * Determine Geographical Addressing
 */
अटल पूर्णांक fake_slot_get(काष्ठा vme_bridge *fake_bridge)
अणु
	वापस geoid;
पूर्ण

अटल व्योम *fake_alloc_consistent(काष्ठा device *parent, माप_प्रकार size,
		dma_addr_t *dma)
अणु
	व्योम *alloc = kदो_स्मृति(size, GFP_KERNEL);

	अगर (alloc)
		*dma = fake_ptr_to_pci(alloc);

	वापस alloc;
पूर्ण

अटल व्योम fake_मुक्त_consistent(काष्ठा device *parent, माप_प्रकार size,
		व्योम *vaddr, dma_addr_t dma)
अणु
	kमुक्त(vaddr);
/*
	dma_मुक्त_coherent(parent, size, vaddr, dma);
*/
पूर्ण

/*
 * Configure CR/CSR space
 *
 * Access to the CR/CSR can be configured at घातer-up. The location of the
 * CR/CSR रेजिस्टरs in the CR/CSR address space is determined by the boards
 * Geographic address.
 *
 * Each board has a 512kB winकरोw, with the highest 4kB being used क्रम the
 * boards रेजिस्टरs, this means there is a fix length 508kB winकरोw which must
 * be mapped onto PCI memory.
 */
अटल पूर्णांक fake_crcsr_init(काष्ठा vme_bridge *fake_bridge)
अणु
	u32 vstat;
	काष्ठा fake_driver *bridge;

	bridge = fake_bridge->driver_priv;

	/* Allocate mem क्रम CR/CSR image */
	bridge->crcsr_kernel = kzalloc(VME_CRCSR_BUF_SIZE, GFP_KERNEL);
	bridge->crcsr_bus = fake_ptr_to_pci(bridge->crcsr_kernel);
	अगर (!bridge->crcsr_kernel)
		वापस -ENOMEM;

	vstat = fake_slot_get(fake_bridge);

	pr_info("CR/CSR Offset: %d\n", vstat);

	वापस 0;
पूर्ण

अटल व्योम fake_crcsr_निकास(काष्ठा vme_bridge *fake_bridge)
अणु
	काष्ठा fake_driver *bridge;

	bridge = fake_bridge->driver_priv;

	kमुक्त(bridge->crcsr_kernel);
पूर्ण


अटल पूर्णांक __init fake_init(व्योम)
अणु
	पूर्णांक retval, i;
	काष्ठा list_head *pos = शून्य, *n;
	काष्ठा vme_bridge *fake_bridge;
	काष्ठा fake_driver *fake_device;
	काष्ठा vme_master_resource *master_image;
	काष्ठा vme_slave_resource *slave_image;
	काष्ठा vme_lm_resource *lm;

	/* We need a fake parent device */
	vme_root = __root_device_रेजिस्टर("vme", THIS_MODULE);

	/* If we want to support more than one bridge at some poपूर्णांक, we need to
	 * dynamically allocate this so we get one per device.
	 */
	fake_bridge = kzalloc(माप(*fake_bridge), GFP_KERNEL);
	अगर (!fake_bridge) अणु
		retval = -ENOMEM;
		जाओ err_काष्ठा;
	पूर्ण

	fake_device = kzalloc(माप(*fake_device), GFP_KERNEL);
	अगर (!fake_device) अणु
		retval = -ENOMEM;
		जाओ err_driver;
	पूर्ण

	fake_bridge->driver_priv = fake_device;

	fake_bridge->parent = vme_root;

	fake_device->parent = fake_bridge;

	/* Initialize रुको queues & mutual exclusion flags */
	mutex_init(&fake_device->vme_पूर्णांक);
	mutex_init(&fake_bridge->irq_mtx);
	tasklet_init(&fake_device->पूर्णांक_tasklet, fake_VIRQ_tasklet,
			(अचिन्हित दीर्घ) fake_bridge);

	म_नकल(fake_bridge->name, driver_name);

	/* Add master winकरोws to list */
	INIT_LIST_HEAD(&fake_bridge->master_resources);
	क्रम (i = 0; i < FAKE_MAX_MASTER; i++) अणु
		master_image = kदो_स्मृति(माप(*master_image), GFP_KERNEL);
		अगर (!master_image) अणु
			retval = -ENOMEM;
			जाओ err_master;
		पूर्ण
		master_image->parent = fake_bridge;
		spin_lock_init(&master_image->lock);
		master_image->locked = 0;
		master_image->number = i;
		master_image->address_attr = VME_A16 | VME_A24 | VME_A32 |
			VME_A64;
		master_image->cycle_attr = VME_SCT | VME_BLT | VME_MBLT |
			VME_2eVME | VME_2eSST | VME_2eSSTB | VME_2eSST160 |
			VME_2eSST267 | VME_2eSST320 | VME_SUPER | VME_USER |
			VME_PROG | VME_DATA;
		master_image->width_attr = VME_D16 | VME_D32;
		स_रखो(&master_image->bus_resource, 0,
				माप(काष्ठा resource));
		master_image->kern_base  = शून्य;
		list_add_tail(&master_image->list,
				&fake_bridge->master_resources);
	पूर्ण

	/* Add slave winकरोws to list */
	INIT_LIST_HEAD(&fake_bridge->slave_resources);
	क्रम (i = 0; i < FAKE_MAX_SLAVE; i++) अणु
		slave_image = kदो_स्मृति(माप(*slave_image), GFP_KERNEL);
		अगर (!slave_image) अणु
			retval = -ENOMEM;
			जाओ err_slave;
		पूर्ण
		slave_image->parent = fake_bridge;
		mutex_init(&slave_image->mtx);
		slave_image->locked = 0;
		slave_image->number = i;
		slave_image->address_attr = VME_A16 | VME_A24 | VME_A32 |
			VME_A64 | VME_CRCSR | VME_USER1 | VME_USER2 |
			VME_USER3 | VME_USER4;
		slave_image->cycle_attr = VME_SCT | VME_BLT | VME_MBLT |
			VME_2eVME | VME_2eSST | VME_2eSSTB | VME_2eSST160 |
			VME_2eSST267 | VME_2eSST320 | VME_SUPER | VME_USER |
			VME_PROG | VME_DATA;
		list_add_tail(&slave_image->list,
				&fake_bridge->slave_resources);
	पूर्ण

	/* Add location monitor to list */
	INIT_LIST_HEAD(&fake_bridge->lm_resources);
	lm = kदो_स्मृति(माप(*lm), GFP_KERNEL);
	अगर (!lm) अणु
		retval = -ENOMEM;
		जाओ err_lm;
	पूर्ण
	lm->parent = fake_bridge;
	mutex_init(&lm->mtx);
	lm->locked = 0;
	lm->number = 1;
	lm->monitors = 4;
	list_add_tail(&lm->list, &fake_bridge->lm_resources);

	fake_bridge->slave_get = fake_slave_get;
	fake_bridge->slave_set = fake_slave_set;
	fake_bridge->master_get = fake_master_get;
	fake_bridge->master_set = fake_master_set;
	fake_bridge->master_पढ़ो = fake_master_पढ़ो;
	fake_bridge->master_ग_लिखो = fake_master_ग_लिखो;
	fake_bridge->master_rmw = fake_master_rmw;
	fake_bridge->irq_set = fake_irq_set;
	fake_bridge->irq_generate = fake_irq_generate;
	fake_bridge->lm_set = fake_lm_set;
	fake_bridge->lm_get = fake_lm_get;
	fake_bridge->lm_attach = fake_lm_attach;
	fake_bridge->lm_detach = fake_lm_detach;
	fake_bridge->slot_get = fake_slot_get;
	fake_bridge->alloc_consistent = fake_alloc_consistent;
	fake_bridge->मुक्त_consistent = fake_मुक्त_consistent;

	pr_info("Board is%s the VME system controller\n",
			(geoid == 1) ? "" : " not");

	pr_info("VME geographical address is set to %d\n", geoid);

	retval = fake_crcsr_init(fake_bridge);
	अगर (retval) अणु
		pr_err("CR/CSR configuration failed.\n");
		जाओ err_crcsr;
	पूर्ण

	retval = vme_रेजिस्टर_bridge(fake_bridge);
	अगर (retval != 0) अणु
		pr_err("Chip Registration failed.\n");
		जाओ err_reg;
	पूर्ण

	निकास_poपूर्णांकer = fake_bridge;

	वापस 0;

err_reg:
	fake_crcsr_निकास(fake_bridge);
err_crcsr:
err_lm:
	/* resources are stored in link list */
	list_क्रम_each_safe(pos, n, &fake_bridge->lm_resources) अणु
		lm = list_entry(pos, काष्ठा vme_lm_resource, list);
		list_del(pos);
		kमुक्त(lm);
	पूर्ण
err_slave:
	/* resources are stored in link list */
	list_क्रम_each_safe(pos, n, &fake_bridge->slave_resources) अणु
		slave_image = list_entry(pos, काष्ठा vme_slave_resource, list);
		list_del(pos);
		kमुक्त(slave_image);
	पूर्ण
err_master:
	/* resources are stored in link list */
	list_क्रम_each_safe(pos, n, &fake_bridge->master_resources) अणु
		master_image = list_entry(pos, काष्ठा vme_master_resource,
				list);
		list_del(pos);
		kमुक्त(master_image);
	पूर्ण

	kमुक्त(fake_device);
err_driver:
	kमुक्त(fake_bridge);
err_काष्ठा:
	वापस retval;

पूर्ण


अटल व्योम __निकास fake_निकास(व्योम)
अणु
	काष्ठा list_head *pos = शून्य;
	काष्ठा list_head *पंचांगplist;
	काष्ठा vme_master_resource *master_image;
	काष्ठा vme_slave_resource *slave_image;
	पूर्णांक i;
	काष्ठा vme_bridge *fake_bridge;
	काष्ठा fake_driver *bridge;

	fake_bridge = निकास_poपूर्णांकer;

	bridge = fake_bridge->driver_priv;

	pr_debug("Driver is being unloaded.\n");

	/*
	 *  Shutकरोwn all inbound and outbound winकरोws.
	 */
	क्रम (i = 0; i < FAKE_MAX_MASTER; i++)
		bridge->masters[i].enabled = 0;

	क्रम (i = 0; i < FAKE_MAX_SLAVE; i++)
		bridge->slaves[i].enabled = 0;

	/*
	 *  Shutकरोwn Location monitor.
	 */
	bridge->lm_enabled = 0;

	vme_unरेजिस्टर_bridge(fake_bridge);

	fake_crcsr_निकास(fake_bridge);
	/* resources are stored in link list */
	list_क्रम_each_safe(pos, पंचांगplist, &fake_bridge->slave_resources) अणु
		slave_image = list_entry(pos, काष्ठा vme_slave_resource, list);
		list_del(pos);
		kमुक्त(slave_image);
	पूर्ण

	/* resources are stored in link list */
	list_क्रम_each_safe(pos, पंचांगplist, &fake_bridge->master_resources) अणु
		master_image = list_entry(pos, काष्ठा vme_master_resource,
				list);
		list_del(pos);
		kमुक्त(master_image);
	पूर्ण

	kमुक्त(fake_bridge->driver_priv);

	kमुक्त(fake_bridge);

	root_device_unरेजिस्टर(vme_root);
पूर्ण


MODULE_PARM_DESC(geoid, "Set geographical addressing");
module_param(geoid, पूर्णांक, 0);

MODULE_DESCRIPTION("Fake VME bridge driver");
MODULE_LICENSE("GPL");

module_init(fake_init);
module_निकास(fake_निकास);
