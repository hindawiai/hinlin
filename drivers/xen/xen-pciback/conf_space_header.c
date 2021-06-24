<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI Backend - Handles the भव fields in the configuration space headers.
 *
 * Author: Ryan Wilson <hap9@epoch.ncsc.mil>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#घोषणा dev_fmt pr_fmt

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश "pciback.h"
#समावेश "conf_space.h"

काष्ठा pci_cmd_info अणु
	u16 val;
पूर्ण;

काष्ठा pci_bar_info अणु
	u32 val;
	u32 len_val;
	पूर्णांक which;
पूर्ण;

#घोषणा is_enable_cmd(value) ((value)&(PCI_COMMAND_MEMORY|PCI_COMMAND_IO))
#घोषणा is_master_cmd(value) ((value)&PCI_COMMAND_MASTER)

/* Bits guests are allowed to control in permissive mode. */
#घोषणा PCI_COMMAND_GUEST (PCI_COMMAND_MASTER|PCI_COMMAND_SPECIAL| \
			   PCI_COMMAND_INVALIDATE|PCI_COMMAND_VGA_PALETTE| \
			   PCI_COMMAND_WAIT|PCI_COMMAND_FAST_BACK)

अटल व्योम *command_init(काष्ठा pci_dev *dev, पूर्णांक offset)
अणु
	काष्ठा pci_cmd_info *cmd = kदो_स्मृति(माप(*cmd), GFP_KERNEL);
	पूर्णांक err;

	अगर (!cmd)
		वापस ERR_PTR(-ENOMEM);

	err = pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd->val);
	अगर (err) अणु
		kमुक्त(cmd);
		वापस ERR_PTR(err);
	पूर्ण

	वापस cmd;
पूर्ण

अटल पूर्णांक command_पढ़ो(काष्ठा pci_dev *dev, पूर्णांक offset, u16 *value, व्योम *data)
अणु
	पूर्णांक ret = pci_पढ़ो_config_word(dev, offset, value);
	स्थिर काष्ठा pci_cmd_info *cmd = data;

	*value &= PCI_COMMAND_GUEST;
	*value |= cmd->val & ~PCI_COMMAND_GUEST;

	वापस ret;
पूर्ण

अटल पूर्णांक command_ग_लिखो(काष्ठा pci_dev *dev, पूर्णांक offset, u16 value, व्योम *data)
अणु
	काष्ठा xen_pcibk_dev_data *dev_data;
	पूर्णांक err;
	u16 val;
	काष्ठा pci_cmd_info *cmd = data;

	dev_data = pci_get_drvdata(dev);
	अगर (!pci_is_enabled(dev) && is_enable_cmd(value)) अणु
		dev_dbg(&dev->dev, "enable\n");
		err = pci_enable_device(dev);
		अगर (err)
			वापस err;
		अगर (dev_data)
			dev_data->enable_पूर्णांकx = 1;
	पूर्ण अन्यथा अगर (pci_is_enabled(dev) && !is_enable_cmd(value)) अणु
		dev_dbg(&dev->dev, "disable\n");
		pci_disable_device(dev);
		अगर (dev_data)
			dev_data->enable_पूर्णांकx = 0;
	पूर्ण

	अगर (!dev->is_busmaster && is_master_cmd(value)) अणु
		dev_dbg(&dev->dev, "set bus master\n");
		pci_set_master(dev);
	पूर्ण अन्यथा अगर (dev->is_busmaster && !is_master_cmd(value)) अणु
		dev_dbg(&dev->dev, "clear bus master\n");
		pci_clear_master(dev);
	पूर्ण

	अगर (!(cmd->val & PCI_COMMAND_INVALIDATE) &&
	    (value & PCI_COMMAND_INVALIDATE)) अणु
		dev_dbg(&dev->dev, "enable memory-write-invalidate\n");
		err = pci_set_mwi(dev);
		अगर (err) अणु
			dev_warn(&dev->dev, "cannot enable memory-write-invalidate (%d)\n",
				err);
			value &= ~PCI_COMMAND_INVALIDATE;
		पूर्ण
	पूर्ण अन्यथा अगर ((cmd->val & PCI_COMMAND_INVALIDATE) &&
		   !(value & PCI_COMMAND_INVALIDATE)) अणु
		dev_dbg(&dev->dev, "disable memory-write-invalidate\n");
		pci_clear_mwi(dev);
	पूर्ण

	अगर (dev_data && dev_data->allow_पूर्णांकerrupt_control) अणु
		अगर ((cmd->val ^ value) & PCI_COMMAND_INTX_DISABLE) अणु
			अगर (value & PCI_COMMAND_INTX_DISABLE) अणु
				pci_पूर्णांकx(dev, 0);
			पूर्ण अन्यथा अणु
				/* Do not allow enabling INTx together with MSI or MSI-X. */
				चयन (xen_pcibk_get_पूर्णांकerrupt_type(dev)) अणु
				हाल INTERRUPT_TYPE_NONE:
					pci_पूर्णांकx(dev, 1);
					अवरोध;
				हाल INTERRUPT_TYPE_INTX:
					अवरोध;
				शेष:
					वापस PCIBIOS_SET_FAILED;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	cmd->val = value;

	अगर (!xen_pcibk_permissive && (!dev_data || !dev_data->permissive))
		वापस 0;

	/* Only allow the guest to control certain bits. */
	err = pci_पढ़ो_config_word(dev, offset, &val);
	अगर (err || val == value)
		वापस err;

	value &= PCI_COMMAND_GUEST;
	value |= val & ~PCI_COMMAND_GUEST;

	वापस pci_ग_लिखो_config_word(dev, offset, value);
पूर्ण

अटल पूर्णांक rom_ग_लिखो(काष्ठा pci_dev *dev, पूर्णांक offset, u32 value, व्योम *data)
अणु
	काष्ठा pci_bar_info *bar = data;

	अगर (unlikely(!bar)) अणु
		dev_warn(&dev->dev, "driver data not found\n");
		वापस XEN_PCI_ERR_op_failed;
	पूर्ण

	/* A ग_लिखो to obtain the length must happen as a 32-bit ग_लिखो.
	 * This करोes not (yet) support writing inभागidual bytes
	 */
	अगर ((value | ~PCI_ROM_ADDRESS_MASK) == ~0U)
		bar->which = 1;
	अन्यथा अणु
		u32 पंचांगpval;
		pci_पढ़ो_config_dword(dev, offset, &पंचांगpval);
		अगर (पंचांगpval != bar->val && value == bar->val) अणु
			/* Allow restoration of bar value. */
			pci_ग_लिखो_config_dword(dev, offset, bar->val);
		पूर्ण
		bar->which = 0;
	पूर्ण

	/* Do we need to support enabling/disabling the rom address here? */

	वापस 0;
पूर्ण

/* For the BARs, only allow ग_लिखोs which ग_लिखो ~0 or
 * the correct resource inक्रमmation
 * (Needed क्रम when the driver probes the resource usage)
 */
अटल पूर्णांक bar_ग_लिखो(काष्ठा pci_dev *dev, पूर्णांक offset, u32 value, व्योम *data)
अणु
	काष्ठा pci_bar_info *bar = data;
	अचिन्हित पूर्णांक pos = (offset - PCI_BASE_ADDRESS_0) / 4;
	स्थिर काष्ठा resource *res = dev->resource;
	u32 mask;

	अगर (unlikely(!bar)) अणु
		dev_warn(&dev->dev, "driver data not found\n");
		वापस XEN_PCI_ERR_op_failed;
	पूर्ण

	/* A ग_लिखो to obtain the length must happen as a 32-bit ग_लिखो.
	 * This करोes not (yet) support writing inभागidual bytes
	 */
	अगर (res[pos].flags & IORESOURCE_IO)
		mask = ~PCI_BASE_ADDRESS_IO_MASK;
	अन्यथा अगर (pos && (res[pos - 1].flags & IORESOURCE_MEM_64))
		mask = 0;
	अन्यथा
		mask = ~PCI_BASE_ADDRESS_MEM_MASK;
	अगर ((value | mask) == ~0U)
		bar->which = 1;
	अन्यथा अणु
		u32 पंचांगpval;
		pci_पढ़ो_config_dword(dev, offset, &पंचांगpval);
		अगर (पंचांगpval != bar->val && value == bar->val) अणु
			/* Allow restoration of bar value. */
			pci_ग_लिखो_config_dword(dev, offset, bar->val);
		पूर्ण
		bar->which = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bar_पढ़ो(काष्ठा pci_dev *dev, पूर्णांक offset, u32 * value, व्योम *data)
अणु
	काष्ठा pci_bar_info *bar = data;

	अगर (unlikely(!bar)) अणु
		dev_warn(&dev->dev, "driver data not found\n");
		वापस XEN_PCI_ERR_op_failed;
	पूर्ण

	*value = bar->which ? bar->len_val : bar->val;

	वापस 0;
पूर्ण

अटल व्योम *bar_init(काष्ठा pci_dev *dev, पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक pos;
	स्थिर काष्ठा resource *res = dev->resource;
	काष्ठा pci_bar_info *bar = kzalloc(माप(*bar), GFP_KERNEL);

	अगर (!bar)
		वापस ERR_PTR(-ENOMEM);

	अगर (offset == PCI_ROM_ADDRESS || offset == PCI_ROM_ADDRESS1)
		pos = PCI_ROM_RESOURCE;
	अन्यथा अणु
		pos = (offset - PCI_BASE_ADDRESS_0) / 4;
		अगर (pos && (res[pos - 1].flags & IORESOURCE_MEM_64)) अणु
			bar->val = res[pos - 1].start >> 32;
			bar->len_val = -resource_size(&res[pos - 1]) >> 32;
			वापस bar;
		पूर्ण
	पूर्ण

	अगर (!res[pos].flags ||
	    (res[pos].flags & (IORESOURCE_DISABLED | IORESOURCE_UNSET |
			       IORESOURCE_BUSY)))
		वापस bar;

	bar->val = res[pos].start |
		   (res[pos].flags & PCI_REGION_FLAG_MASK);
	bar->len_val = -resource_size(&res[pos]) |
		       (res[pos].flags & PCI_REGION_FLAG_MASK);

	वापस bar;
पूर्ण

अटल व्योम bar_reset(काष्ठा pci_dev *dev, पूर्णांक offset, व्योम *data)
अणु
	काष्ठा pci_bar_info *bar = data;

	bar->which = 0;
पूर्ण

अटल व्योम bar_release(काष्ठा pci_dev *dev, पूर्णांक offset, व्योम *data)
अणु
	kमुक्त(data);
पूर्ण

अटल पूर्णांक xen_pcibk_पढ़ो_venकरोr(काष्ठा pci_dev *dev, पूर्णांक offset,
			       u16 *value, व्योम *data)
अणु
	*value = dev->venकरोr;

	वापस 0;
पूर्ण

अटल पूर्णांक xen_pcibk_पढ़ो_device(काष्ठा pci_dev *dev, पूर्णांक offset,
			       u16 *value, व्योम *data)
अणु
	*value = dev->device;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकerrupt_पढ़ो(काष्ठा pci_dev *dev, पूर्णांक offset, u8 * value,
			  व्योम *data)
अणु
	*value = (u8) dev->irq;

	वापस 0;
पूर्ण

अटल पूर्णांक bist_ग_लिखो(काष्ठा pci_dev *dev, पूर्णांक offset, u8 value, व्योम *data)
अणु
	u8 cur_value;
	पूर्णांक err;

	err = pci_पढ़ो_config_byte(dev, offset, &cur_value);
	अगर (err)
		जाओ out;

	अगर ((cur_value & ~PCI_BIST_START) == (value & ~PCI_BIST_START)
	    || value == PCI_BIST_START)
		err = pci_ग_लिखो_config_byte(dev, offset, value);

out:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा config_field header_common[] = अणु
	अणु
	 .offset    = PCI_VENDOR_ID,
	 .size      = 2,
	 .u.w.पढ़ो  = xen_pcibk_पढ़ो_venकरोr,
	पूर्ण,
	अणु
	 .offset    = PCI_DEVICE_ID,
	 .size      = 2,
	 .u.w.पढ़ो  = xen_pcibk_पढ़ो_device,
	पूर्ण,
	अणु
	 .offset    = PCI_COMMAND,
	 .size      = 2,
	 .init      = command_init,
	 .release   = bar_release,
	 .u.w.पढ़ो  = command_पढ़ो,
	 .u.w.ग_लिखो = command_ग_लिखो,
	पूर्ण,
	अणु
	 .offset    = PCI_INTERRUPT_LINE,
	 .size      = 1,
	 .u.b.पढ़ो  = पूर्णांकerrupt_पढ़ो,
	पूर्ण,
	अणु
	 .offset    = PCI_INTERRUPT_PIN,
	 .size      = 1,
	 .u.b.पढ़ो  = xen_pcibk_पढ़ो_config_byte,
	पूर्ण,
	अणु
	 /* Any side effects of letting driver करोमुख्य control cache line? */
	 .offset    = PCI_CACHE_LINE_SIZE,
	 .size      = 1,
	 .u.b.पढ़ो  = xen_pcibk_पढ़ो_config_byte,
	 .u.b.ग_लिखो = xen_pcibk_ग_लिखो_config_byte,
	पूर्ण,
	अणु
	 .offset    = PCI_LATENCY_TIMER,
	 .size      = 1,
	 .u.b.पढ़ो  = xen_pcibk_पढ़ो_config_byte,
	पूर्ण,
	अणु
	 .offset    = PCI_BIST,
	 .size      = 1,
	 .u.b.पढ़ो  = xen_pcibk_पढ़ो_config_byte,
	 .u.b.ग_लिखो = bist_ग_लिखो,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

#घोषणा CFG_FIELD_BAR(reg_offset)			\
	अणु						\
	.offset     = reg_offset,			\
	.size       = 4,				\
	.init       = bar_init,				\
	.reset      = bar_reset,			\
	.release    = bar_release,			\
	.u.dw.पढ़ो  = bar_पढ़ो,				\
	.u.dw.ग_लिखो = bar_ग_लिखो,			\
	पूर्ण

#घोषणा CFG_FIELD_ROM(reg_offset)			\
	अणु						\
	.offset     = reg_offset,			\
	.size       = 4,				\
	.init       = bar_init,				\
	.reset      = bar_reset,			\
	.release    = bar_release,			\
	.u.dw.पढ़ो  = bar_पढ़ो,				\
	.u.dw.ग_लिखो = rom_ग_लिखो,			\
	पूर्ण

अटल स्थिर काष्ठा config_field header_0[] = अणु
	CFG_FIELD_BAR(PCI_BASE_ADDRESS_0),
	CFG_FIELD_BAR(PCI_BASE_ADDRESS_1),
	CFG_FIELD_BAR(PCI_BASE_ADDRESS_2),
	CFG_FIELD_BAR(PCI_BASE_ADDRESS_3),
	CFG_FIELD_BAR(PCI_BASE_ADDRESS_4),
	CFG_FIELD_BAR(PCI_BASE_ADDRESS_5),
	CFG_FIELD_ROM(PCI_ROM_ADDRESS),
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा config_field header_1[] = अणु
	CFG_FIELD_BAR(PCI_BASE_ADDRESS_0),
	CFG_FIELD_BAR(PCI_BASE_ADDRESS_1),
	CFG_FIELD_ROM(PCI_ROM_ADDRESS1),
	अणुपूर्ण
पूर्ण;

पूर्णांक xen_pcibk_config_header_add_fields(काष्ठा pci_dev *dev)
अणु
	पूर्णांक err;

	err = xen_pcibk_config_add_fields(dev, header_common);
	अगर (err)
		जाओ out;

	चयन (dev->hdr_type) अणु
	हाल PCI_HEADER_TYPE_NORMAL:
		err = xen_pcibk_config_add_fields(dev, header_0);
		अवरोध;

	हाल PCI_HEADER_TYPE_BRIDGE:
		err = xen_pcibk_config_add_fields(dev, header_1);
		अवरोध;

	शेष:
		err = -EINVAL;
		dev_err(&dev->dev, "Unsupported header type %d!\n",
			dev->hdr_type);
		अवरोध;
	पूर्ण

out:
	वापस err;
पूर्ण
