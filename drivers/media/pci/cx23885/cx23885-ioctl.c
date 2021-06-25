<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the Conexant CX23885/7/8 PCIe bridge
 *
 *  Various common ioctl() support functions
 *
 *  Copyright (c) 2009 Andy Walls <awalls@md.metrocast.net>
 */

#समावेश "cx23885.h"
#समावेश "cx23885-ioctl.h"

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
पूर्णांक cx23885_g_chip_info(काष्ठा file *file, व्योम *fh,
			 काष्ठा v4l2_dbg_chip_info *chip)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);

	अगर (chip->match.addr > 1)
		वापस -EINVAL;
	अगर (chip->match.addr == 1) अणु
		अगर (dev->v4l_device == शून्य)
			वापस -EINVAL;
		strscpy(chip->name, "cx23417", माप(chip->name));
	पूर्ण अन्यथा अणु
		strscpy(chip->name, dev->v4l2_dev.name, माप(chip->name));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cx23417_g_रेजिस्टर(काष्ठा cx23885_dev *dev,
			      काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	u32 value;

	अगर (dev->v4l_device == शून्य)
		वापस -EINVAL;

	अगर ((reg->reg & 0x3) != 0 || reg->reg >= 0x10000)
		वापस -EINVAL;

	अगर (mc417_रेजिस्टर_पढ़ो(dev, (u16) reg->reg, &value))
		वापस -EINVAL; /* V4L2 spec, but -EREMOTEIO really */

	reg->size = 4;
	reg->val = value;
	वापस 0;
पूर्ण

पूर्णांक cx23885_g_रेजिस्टर(काष्ठा file *file, व्योम *fh,
		       काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);

	अगर (reg->match.addr > 1)
		वापस -EINVAL;
	अगर (reg->match.addr)
		वापस cx23417_g_रेजिस्टर(dev, reg);

	अगर ((reg->reg & 0x3) != 0 || reg->reg >= pci_resource_len(dev->pci, 0))
		वापस -EINVAL;

	reg->size = 4;
	reg->val = cx_पढ़ो(reg->reg);
	वापस 0;
पूर्ण

अटल पूर्णांक cx23417_s_रेजिस्टर(काष्ठा cx23885_dev *dev,
			      स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	अगर (dev->v4l_device == शून्य)
		वापस -EINVAL;

	अगर ((reg->reg & 0x3) != 0 || reg->reg >= 0x10000)
		वापस -EINVAL;

	अगर (mc417_रेजिस्टर_ग_लिखो(dev, (u16) reg->reg, (u32) reg->val))
		वापस -EINVAL; /* V4L2 spec, but -EREMOTEIO really */
	वापस 0;
पूर्ण

पूर्णांक cx23885_s_रेजिस्टर(काष्ठा file *file, व्योम *fh,
		       स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);

	अगर (reg->match.addr > 1)
		वापस -EINVAL;
	अगर (reg->match.addr)
		वापस cx23417_s_रेजिस्टर(dev, reg);

	अगर ((reg->reg & 0x3) != 0 || reg->reg >= pci_resource_len(dev->pci, 0))
		वापस -EINVAL;

	cx_ग_लिखो(reg->reg, reg->val);
	वापस 0;
पूर्ण
#पूर्ण_अगर
