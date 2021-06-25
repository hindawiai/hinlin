<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI VPD support
 *
 * Copyright (C) 2010 Broadcom Corporation.
 */

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/sched/संकेत.स>
#समावेश "pci.h"

/* VPD access through PCI 2.2+ VPD capability */

काष्ठा pci_vpd_ops अणु
	sमाप_प्रकार (*पढ़ो)(काष्ठा pci_dev *dev, loff_t pos, माप_प्रकार count, व्योम *buf);
	sमाप_प्रकार (*ग_लिखो)(काष्ठा pci_dev *dev, loff_t pos, माप_प्रकार count, स्थिर व्योम *buf);
पूर्ण;

काष्ठा pci_vpd अणु
	स्थिर काष्ठा pci_vpd_ops *ops;
	काष्ठा mutex	lock;
	अचिन्हित पूर्णांक	len;
	u16		flag;
	u8		cap;
	अचिन्हित पूर्णांक	busy:1;
	अचिन्हित पूर्णांक	valid:1;
पूर्ण;

अटल काष्ठा pci_dev *pci_get_func0_dev(काष्ठा pci_dev *dev)
अणु
	वापस pci_get_slot(dev->bus, PCI_DEVFN(PCI_SLOT(dev->devfn), 0));
पूर्ण

/**
 * pci_पढ़ो_vpd - Read one entry from Vital Product Data
 * @dev:	pci device काष्ठा
 * @pos:	offset in vpd space
 * @count:	number of bytes to पढ़ो
 * @buf:	poपूर्णांकer to where to store result
 */
sमाप_प्रकार pci_पढ़ो_vpd(काष्ठा pci_dev *dev, loff_t pos, माप_प्रकार count, व्योम *buf)
अणु
	अगर (!dev->vpd || !dev->vpd->ops)
		वापस -ENODEV;
	वापस dev->vpd->ops->पढ़ो(dev, pos, count, buf);
पूर्ण
EXPORT_SYMBOL(pci_पढ़ो_vpd);

/**
 * pci_ग_लिखो_vpd - Write entry to Vital Product Data
 * @dev:	pci device काष्ठा
 * @pos:	offset in vpd space
 * @count:	number of bytes to ग_लिखो
 * @buf:	buffer containing ग_लिखो data
 */
sमाप_प्रकार pci_ग_लिखो_vpd(काष्ठा pci_dev *dev, loff_t pos, माप_प्रकार count, स्थिर व्योम *buf)
अणु
	अगर (!dev->vpd || !dev->vpd->ops)
		वापस -ENODEV;
	वापस dev->vpd->ops->ग_लिखो(dev, pos, count, buf);
पूर्ण
EXPORT_SYMBOL(pci_ग_लिखो_vpd);

#घोषणा PCI_VPD_MAX_SIZE (PCI_VPD_ADDR_MASK + 1)

/**
 * pci_vpd_size - determine actual size of Vital Product Data
 * @dev:	pci device काष्ठा
 * @old_size:	current assumed size, also maximum allowed size
 */
अटल माप_प्रकार pci_vpd_size(काष्ठा pci_dev *dev, माप_प्रकार old_size)
अणु
	माप_प्रकार off = 0;
	अचिन्हित अक्षर header[1+2];	/* 1 byte tag, 2 bytes length */

	जबतक (off < old_size && pci_पढ़ो_vpd(dev, off, 1, header) == 1) अणु
		अचिन्हित अक्षर tag;

		अगर (!header[0] && !off) अणु
			pci_info(dev, "Invalid VPD tag 00, assume missing optional VPD EPROM\n");
			वापस 0;
		पूर्ण

		अगर (header[0] & PCI_VPD_LRDT) अणु
			/* Large Resource Data Type Tag */
			tag = pci_vpd_lrdt_tag(header);
			/* Only पढ़ो length from known tag items */
			अगर ((tag == PCI_VPD_LTIN_ID_STRING) ||
			    (tag == PCI_VPD_LTIN_RO_DATA) ||
			    (tag == PCI_VPD_LTIN_RW_DATA)) अणु
				अगर (pci_पढ़ो_vpd(dev, off+1, 2,
						 &header[1]) != 2) अणु
					pci_warn(dev, "invalid large VPD tag %02x size at offset %zu",
						 tag, off + 1);
					वापस 0;
				पूर्ण
				off += PCI_VPD_LRDT_TAG_SIZE +
					pci_vpd_lrdt_size(header);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Short Resource Data Type Tag */
			off += PCI_VPD_SRDT_TAG_SIZE +
				pci_vpd_srdt_size(header);
			tag = pci_vpd_srdt_tag(header);
		पूर्ण

		अगर (tag == PCI_VPD_STIN_END)	/* End tag descriptor */
			वापस off;

		अगर ((tag != PCI_VPD_LTIN_ID_STRING) &&
		    (tag != PCI_VPD_LTIN_RO_DATA) &&
		    (tag != PCI_VPD_LTIN_RW_DATA)) अणु
			pci_warn(dev, "invalid %s VPD tag %02x at offset %zu",
				 (header[0] & PCI_VPD_LRDT) ? "large" : "short",
				 tag, off);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Wait क्रम last operation to complete.
 * This code has to spin since there is no other notअगरication from the PCI
 * hardware. Since the VPD is often implemented by serial attachment to an
 * EEPROM, it may take many milliseconds to complete.
 *
 * Returns 0 on success, negative values indicate error.
 */
अटल पूर्णांक pci_vpd_रुको(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_vpd *vpd = dev->vpd;
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(125);
	अचिन्हित दीर्घ max_sleep = 16;
	u16 status;
	पूर्णांक ret;

	अगर (!vpd->busy)
		वापस 0;

	करो अणु
		ret = pci_user_पढ़ो_config_word(dev, vpd->cap + PCI_VPD_ADDR,
						&status);
		अगर (ret < 0)
			वापस ret;

		अगर ((status & PCI_VPD_ADDR_F) == vpd->flag) अणु
			vpd->busy = 0;
			वापस 0;
		पूर्ण

		अगर (fatal_संकेत_pending(current))
			वापस -EINTR;

		अगर (समय_after(jअगरfies, समयout))
			अवरोध;

		usleep_range(10, max_sleep);
		अगर (max_sleep < 1024)
			max_sleep *= 2;
	पूर्ण जबतक (true);

	pci_warn(dev, "VPD access failed.  This is likely a firmware bug on this device.  Contact the card vendor for a firmware update\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल sमाप_प्रकार pci_vpd_पढ़ो(काष्ठा pci_dev *dev, loff_t pos, माप_प्रकार count,
			    व्योम *arg)
अणु
	काष्ठा pci_vpd *vpd = dev->vpd;
	पूर्णांक ret;
	loff_t end = pos + count;
	u8 *buf = arg;

	अगर (pos < 0)
		वापस -EINVAL;

	अगर (!vpd->valid) अणु
		vpd->valid = 1;
		vpd->len = pci_vpd_size(dev, vpd->len);
	पूर्ण

	अगर (vpd->len == 0)
		वापस -EIO;

	अगर (pos > vpd->len)
		वापस 0;

	अगर (end > vpd->len) अणु
		end = vpd->len;
		count = end - pos;
	पूर्ण

	अगर (mutex_lock_समाप्तable(&vpd->lock))
		वापस -EINTR;

	ret = pci_vpd_रुको(dev);
	अगर (ret < 0)
		जाओ out;

	जबतक (pos < end) अणु
		u32 val;
		अचिन्हित पूर्णांक i, skip;

		ret = pci_user_ग_लिखो_config_word(dev, vpd->cap + PCI_VPD_ADDR,
						 pos & ~3);
		अगर (ret < 0)
			अवरोध;
		vpd->busy = 1;
		vpd->flag = PCI_VPD_ADDR_F;
		ret = pci_vpd_रुको(dev);
		अगर (ret < 0)
			अवरोध;

		ret = pci_user_पढ़ो_config_dword(dev, vpd->cap + PCI_VPD_DATA, &val);
		अगर (ret < 0)
			अवरोध;

		skip = pos & 3;
		क्रम (i = 0;  i < माप(u32); i++) अणु
			अगर (i >= skip) अणु
				*buf++ = val;
				अगर (++pos == end)
					अवरोध;
			पूर्ण
			val >>= 8;
		पूर्ण
	पूर्ण
out:
	mutex_unlock(&vpd->lock);
	वापस ret ? ret : count;
पूर्ण

अटल sमाप_प्रकार pci_vpd_ग_लिखो(काष्ठा pci_dev *dev, loff_t pos, माप_प्रकार count,
			     स्थिर व्योम *arg)
अणु
	काष्ठा pci_vpd *vpd = dev->vpd;
	स्थिर u8 *buf = arg;
	loff_t end = pos + count;
	पूर्णांक ret = 0;

	अगर (pos < 0 || (pos & 3) || (count & 3))
		वापस -EINVAL;

	अगर (!vpd->valid) अणु
		vpd->valid = 1;
		vpd->len = pci_vpd_size(dev, vpd->len);
	पूर्ण

	अगर (vpd->len == 0)
		वापस -EIO;

	अगर (end > vpd->len)
		वापस -EINVAL;

	अगर (mutex_lock_समाप्तable(&vpd->lock))
		वापस -EINTR;

	ret = pci_vpd_रुको(dev);
	अगर (ret < 0)
		जाओ out;

	जबतक (pos < end) अणु
		u32 val;

		val = *buf++;
		val |= *buf++ << 8;
		val |= *buf++ << 16;
		val |= *buf++ << 24;

		ret = pci_user_ग_लिखो_config_dword(dev, vpd->cap + PCI_VPD_DATA, val);
		अगर (ret < 0)
			अवरोध;
		ret = pci_user_ग_लिखो_config_word(dev, vpd->cap + PCI_VPD_ADDR,
						 pos | PCI_VPD_ADDR_F);
		अगर (ret < 0)
			अवरोध;

		vpd->busy = 1;
		vpd->flag = 0;
		ret = pci_vpd_रुको(dev);
		अगर (ret < 0)
			अवरोध;

		pos += माप(u32);
	पूर्ण
out:
	mutex_unlock(&vpd->lock);
	वापस ret ? ret : count;
पूर्ण

अटल स्थिर काष्ठा pci_vpd_ops pci_vpd_ops = अणु
	.पढ़ो = pci_vpd_पढ़ो,
	.ग_लिखो = pci_vpd_ग_लिखो,
पूर्ण;

अटल sमाप_प्रकार pci_vpd_f0_पढ़ो(काष्ठा pci_dev *dev, loff_t pos, माप_प्रकार count,
			       व्योम *arg)
अणु
	काष्ठा pci_dev *tdev = pci_get_func0_dev(dev);
	sमाप_प्रकार ret;

	अगर (!tdev)
		वापस -ENODEV;

	ret = pci_पढ़ो_vpd(tdev, pos, count, arg);
	pci_dev_put(tdev);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार pci_vpd_f0_ग_लिखो(काष्ठा pci_dev *dev, loff_t pos, माप_प्रकार count,
				स्थिर व्योम *arg)
अणु
	काष्ठा pci_dev *tdev = pci_get_func0_dev(dev);
	sमाप_प्रकार ret;

	अगर (!tdev)
		वापस -ENODEV;

	ret = pci_ग_लिखो_vpd(tdev, pos, count, arg);
	pci_dev_put(tdev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pci_vpd_ops pci_vpd_f0_ops = अणु
	.पढ़ो = pci_vpd_f0_पढ़ो,
	.ग_लिखो = pci_vpd_f0_ग_लिखो,
पूर्ण;

व्योम pci_vpd_init(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_vpd *vpd;
	u8 cap;

	cap = pci_find_capability(dev, PCI_CAP_ID_VPD);
	अगर (!cap)
		वापस;

	vpd = kzalloc(माप(*vpd), GFP_ATOMIC);
	अगर (!vpd)
		वापस;

	vpd->len = PCI_VPD_MAX_SIZE;
	अगर (dev->dev_flags & PCI_DEV_FLAGS_VPD_REF_F0)
		vpd->ops = &pci_vpd_f0_ops;
	अन्यथा
		vpd->ops = &pci_vpd_ops;
	mutex_init(&vpd->lock);
	vpd->cap = cap;
	vpd->busy = 0;
	vpd->valid = 0;
	dev->vpd = vpd;
पूर्ण

व्योम pci_vpd_release(काष्ठा pci_dev *dev)
अणु
	kमुक्त(dev->vpd);
पूर्ण

अटल sमाप_प्रकार vpd_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			काष्ठा bin_attribute *bin_attr, अक्षर *buf, loff_t off,
			माप_प्रकार count)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(kobj_to_dev(kobj));

	वापस pci_पढ़ो_vpd(dev, off, count, buf);
पूर्ण

अटल sमाप_प्रकार vpd_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
			 काष्ठा bin_attribute *bin_attr, अक्षर *buf, loff_t off,
			 माप_प्रकार count)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(kobj_to_dev(kobj));

	वापस pci_ग_लिखो_vpd(dev, off, count, buf);
पूर्ण
अटल BIN_ATTR(vpd, 0600, vpd_पढ़ो, vpd_ग_लिखो, 0);

अटल काष्ठा bin_attribute *vpd_attrs[] = अणु
	&bin_attr_vpd,
	शून्य,
पूर्ण;

अटल umode_t vpd_attr_is_visible(काष्ठा kobject *kobj,
				   काष्ठा bin_attribute *a, पूर्णांक n)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(kobj_to_dev(kobj));

	अगर (!pdev->vpd)
		वापस 0;

	वापस a->attr.mode;
पूर्ण

स्थिर काष्ठा attribute_group pci_dev_vpd_attr_group = अणु
	.bin_attrs = vpd_attrs,
	.is_bin_visible = vpd_attr_is_visible,
पूर्ण;

पूर्णांक pci_vpd_find_tag(स्थिर u8 *buf, अचिन्हित पूर्णांक len, u8 rdt)
अणु
	पूर्णांक i = 0;

	/* look क्रम LRDT tags only, end tag is the only SRDT tag */
	जबतक (i + PCI_VPD_LRDT_TAG_SIZE <= len && buf[i] & PCI_VPD_LRDT) अणु
		अगर (buf[i] == rdt)
			वापस i;

		i += PCI_VPD_LRDT_TAG_SIZE + pci_vpd_lrdt_size(buf + i);
	पूर्ण

	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL_GPL(pci_vpd_find_tag);

पूर्णांक pci_vpd_find_info_keyword(स्थिर u8 *buf, अचिन्हित पूर्णांक off,
			      अचिन्हित पूर्णांक len, स्थिर अक्षर *kw)
अणु
	पूर्णांक i;

	क्रम (i = off; i + PCI_VPD_INFO_FLD_HDR_SIZE <= off + len;) अणु
		अगर (buf[i + 0] == kw[0] &&
		    buf[i + 1] == kw[1])
			वापस i;

		i += PCI_VPD_INFO_FLD_HDR_SIZE +
		     pci_vpd_info_field_size(&buf[i]);
	पूर्ण

	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL_GPL(pci_vpd_find_info_keyword);

#अगर_घोषित CONFIG_PCI_QUIRKS
/*
 * Quirk non-zero PCI functions to route VPD access through function 0 क्रम
 * devices that share VPD resources between functions.  The functions are
 * expected to be identical devices.
 */
अटल व्योम quirk_f0_vpd_link(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dev *f0;

	अगर (!PCI_FUNC(dev->devfn))
		वापस;

	f0 = pci_get_func0_dev(dev);
	अगर (!f0)
		वापस;

	अगर (f0->vpd && dev->class == f0->class &&
	    dev->venकरोr == f0->venकरोr && dev->device == f0->device)
		dev->dev_flags |= PCI_DEV_FLAGS_VPD_REF_F0;

	pci_dev_put(f0);
पूर्ण
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, PCI_ANY_ID,
			      PCI_CLASS_NETWORK_ETHERNET, 8, quirk_f0_vpd_link);

/*
 * If a device follows the VPD क्रमmat spec, the PCI core will not पढ़ो or
 * ग_लिखो past the VPD End Tag.  But some venकरोrs करो not follow the VPD
 * क्रमmat spec, so we can't tell how much data is safe to access.  Devices
 * may behave unpredictably अगर we access too much.  Blacklist these devices
 * so we करोn't touch VPD at all.
 */
अटल व्योम quirk_blacklist_vpd(काष्ठा pci_dev *dev)
अणु
	अगर (dev->vpd) अणु
		dev->vpd->len = 0;
		pci_warn(dev, FW_BUG "disabling VPD access (can't determine size of non-standard VPD format)\n");
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_LSI_LOGIC, 0x0060, quirk_blacklist_vpd);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_LSI_LOGIC, 0x007c, quirk_blacklist_vpd);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_LSI_LOGIC, 0x0413, quirk_blacklist_vpd);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_LSI_LOGIC, 0x0078, quirk_blacklist_vpd);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_LSI_LOGIC, 0x0079, quirk_blacklist_vpd);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_LSI_LOGIC, 0x0073, quirk_blacklist_vpd);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_LSI_LOGIC, 0x0071, quirk_blacklist_vpd);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_LSI_LOGIC, 0x005b, quirk_blacklist_vpd);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_LSI_LOGIC, 0x002f, quirk_blacklist_vpd);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_LSI_LOGIC, 0x005d, quirk_blacklist_vpd);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_LSI_LOGIC, 0x005f, quirk_blacklist_vpd);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATTANSIC, PCI_ANY_ID,
		quirk_blacklist_vpd);
/*
 * The Amazon Annapurna Lअसल 0x0031 device id is reused क्रम other non Root Port
 * device types, so the quirk is रेजिस्टरed क्रम the PCI_CLASS_BRIDGE_PCI class.
 */
DECLARE_PCI_FIXUP_CLASS_FINAL(PCI_VENDOR_ID_AMAZON_ANNAPURNA_LABS, 0x0031,
			      PCI_CLASS_BRIDGE_PCI, 8, quirk_blacklist_vpd);

अटल व्योम pci_vpd_set_size(काष्ठा pci_dev *dev, माप_प्रकार len)
अणु
	काष्ठा pci_vpd *vpd = dev->vpd;

	अगर (!vpd || len == 0 || len > PCI_VPD_MAX_SIZE)
		वापस;

	vpd->valid = 1;
	vpd->len = len;
पूर्ण

अटल व्योम quirk_chelsio_extend_vpd(काष्ठा pci_dev *dev)
अणु
	पूर्णांक chip = (dev->device & 0xf000) >> 12;
	पूर्णांक func = (dev->device & 0x0f00) >>  8;
	पूर्णांक prod = (dev->device & 0x00ff) >>  0;

	/*
	 * If this is a T3-based adapter, there's a 1KB VPD area at offset
	 * 0xc00 which contains the preferred VPD values.  If this is a T4 or
	 * later based adapter, the special VPD is at offset 0x400 क्रम the
	 * Physical Functions (the SR-IOV Virtual Functions have no VPD
	 * Capabilities).  The PCI VPD Access core routines will normally
	 * compute the size of the VPD by parsing the VPD Data Structure at
	 * offset 0x000.  This will result in silent failures when attempting
	 * to accesses these other VPD areas which are beyond those computed
	 * limits.
	 */
	अगर (chip == 0x0 && prod >= 0x20)
		pci_vpd_set_size(dev, 8192);
	अन्यथा अगर (chip >= 0x4 && func < 0x8)
		pci_vpd_set_size(dev, 2048);
पूर्ण

DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_CHELSIO, PCI_ANY_ID,
			quirk_chelsio_extend_vpd);

#पूर्ण_अगर
