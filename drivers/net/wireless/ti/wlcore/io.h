<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl1271
 *
 * Copyright (C) 1998-2009 Texas Instruments. All rights reserved.
 * Copyright (C) 2008-2010 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#अगर_अघोषित __IO_H__
#घोषणा __IO_H__

#समावेश <linux/irqवापस.h>

#घोषणा HW_ACCESS_MEMORY_MAX_RANGE	0x1FFC0

#घोषणा HW_PARTITION_REGISTERS_ADDR     0x1FFC0
#घोषणा HW_PART0_SIZE_ADDR              (HW_PARTITION_REGISTERS_ADDR)
#घोषणा HW_PART0_START_ADDR             (HW_PARTITION_REGISTERS_ADDR + 4)
#घोषणा HW_PART1_SIZE_ADDR              (HW_PARTITION_REGISTERS_ADDR + 8)
#घोषणा HW_PART1_START_ADDR             (HW_PARTITION_REGISTERS_ADDR + 12)
#घोषणा HW_PART2_SIZE_ADDR              (HW_PARTITION_REGISTERS_ADDR + 16)
#घोषणा HW_PART2_START_ADDR             (HW_PARTITION_REGISTERS_ADDR + 20)
#घोषणा HW_PART3_SIZE_ADDR              (HW_PARTITION_REGISTERS_ADDR + 24)
#घोषणा HW_PART3_START_ADDR             (HW_PARTITION_REGISTERS_ADDR + 28)

#घोषणा HW_ACCESS_REGISTER_SIZE         4

#घोषणा HW_ACCESS_PRAM_MAX_RANGE	0x3c000

काष्ठा wl1271;

व्योम wlcore_disable_पूर्णांकerrupts(काष्ठा wl1271 *wl);
व्योम wlcore_disable_पूर्णांकerrupts_nosync(काष्ठा wl1271 *wl);
व्योम wlcore_enable_पूर्णांकerrupts(काष्ठा wl1271 *wl);
व्योम wlcore_synchronize_पूर्णांकerrupts(काष्ठा wl1271 *wl);

व्योम wl1271_io_reset(काष्ठा wl1271 *wl);
व्योम wl1271_io_init(काष्ठा wl1271 *wl);
पूर्णांक wlcore_translate_addr(काष्ठा wl1271 *wl, पूर्णांक addr);

/* Raw target IO, address is not translated */
अटल अंतरभूत पूर्णांक __must_check wlcore_raw_ग_लिखो(काष्ठा wl1271 *wl, पूर्णांक addr,
						व्योम *buf, माप_प्रकार len,
						bool fixed)
अणु
	पूर्णांक ret;

	अगर (test_bit(WL1271_FLAG_IO_FAILED, &wl->flags) ||
	    WARN_ON((test_bit(WL1271_FLAG_IN_ELP, &wl->flags) &&
		     addr != HW_ACCESS_ELP_CTRL_REG)))
		वापस -EIO;

	ret = wl->अगर_ops->ग_लिखो(wl->dev, addr, buf, len, fixed);
	अगर (ret && wl->state != WLCORE_STATE_OFF)
		set_bit(WL1271_FLAG_IO_FAILED, &wl->flags);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक __must_check wlcore_raw_पढ़ो(काष्ठा wl1271 *wl, पूर्णांक addr,
					       व्योम *buf, माप_प्रकार len,
					       bool fixed)
अणु
	पूर्णांक ret;

	अगर (test_bit(WL1271_FLAG_IO_FAILED, &wl->flags) ||
	    WARN_ON((test_bit(WL1271_FLAG_IN_ELP, &wl->flags) &&
		     addr != HW_ACCESS_ELP_CTRL_REG)))
		वापस -EIO;

	ret = wl->अगर_ops->पढ़ो(wl->dev, addr, buf, len, fixed);
	अगर (ret && wl->state != WLCORE_STATE_OFF)
		set_bit(WL1271_FLAG_IO_FAILED, &wl->flags);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक __must_check wlcore_raw_पढ़ो_data(काष्ठा wl1271 *wl, पूर्णांक reg,
						    व्योम *buf, माप_प्रकार len,
						    bool fixed)
अणु
	वापस wlcore_raw_पढ़ो(wl, wl->rtable[reg], buf, len, fixed);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check wlcore_raw_ग_लिखो_data(काष्ठा wl1271 *wl, पूर्णांक reg,
						     व्योम *buf, माप_प्रकार len,
						     bool fixed)
अणु
	वापस wlcore_raw_ग_लिखो(wl, wl->rtable[reg], buf, len, fixed);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check wlcore_raw_पढ़ो32(काष्ठा wl1271 *wl, पूर्णांक addr,
						 u32 *val)
अणु
	पूर्णांक ret;

	ret = wlcore_raw_पढ़ो(wl, addr, wl->buffer_32,
			      माप(*wl->buffer_32), false);
	अगर (ret < 0)
		वापस ret;

	अगर (val)
		*val = le32_to_cpu(*wl->buffer_32);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __must_check wlcore_raw_ग_लिखो32(काष्ठा wl1271 *wl, पूर्णांक addr,
						  u32 val)
अणु
	*wl->buffer_32 = cpu_to_le32(val);
	वापस wlcore_raw_ग_लिखो(wl, addr, wl->buffer_32,
				माप(*wl->buffer_32), false);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check wlcore_पढ़ो(काष्ठा wl1271 *wl, पूर्णांक addr,
					   व्योम *buf, माप_प्रकार len, bool fixed)
अणु
	पूर्णांक physical;

	physical = wlcore_translate_addr(wl, addr);

	वापस wlcore_raw_पढ़ो(wl, physical, buf, len, fixed);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check wlcore_ग_लिखो(काष्ठा wl1271 *wl, पूर्णांक addr,
					    व्योम *buf, माप_प्रकार len, bool fixed)
अणु
	पूर्णांक physical;

	physical = wlcore_translate_addr(wl, addr);

	वापस wlcore_raw_ग_लिखो(wl, physical, buf, len, fixed);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check wlcore_ग_लिखो_data(काष्ठा wl1271 *wl, पूर्णांक reg,
						 व्योम *buf, माप_प्रकार len,
						 bool fixed)
अणु
	वापस wlcore_ग_लिखो(wl, wl->rtable[reg], buf, len, fixed);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check wlcore_पढ़ो_data(काष्ठा wl1271 *wl, पूर्णांक reg,
						व्योम *buf, माप_प्रकार len,
						bool fixed)
अणु
	वापस wlcore_पढ़ो(wl, wl->rtable[reg], buf, len, fixed);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check wlcore_पढ़ो_hwaddr(काष्ठा wl1271 *wl, पूर्णांक hwaddr,
						  व्योम *buf, माप_प्रकार len,
						  bool fixed)
अणु
	पूर्णांक physical;
	पूर्णांक addr;

	/* Convert from FW पूर्णांकernal address which is chip arch dependent */
	addr = wl->ops->convert_hwaddr(wl, hwaddr);

	physical = wlcore_translate_addr(wl, addr);

	वापस wlcore_raw_पढ़ो(wl, physical, buf, len, fixed);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check wlcore_पढ़ो32(काष्ठा wl1271 *wl, पूर्णांक addr,
					     u32 *val)
अणु
	वापस wlcore_raw_पढ़ो32(wl, wlcore_translate_addr(wl, addr), val);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check wlcore_ग_लिखो32(काष्ठा wl1271 *wl, पूर्णांक addr,
					      u32 val)
अणु
	वापस wlcore_raw_ग_लिखो32(wl, wlcore_translate_addr(wl, addr), val);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check wlcore_पढ़ो_reg(काष्ठा wl1271 *wl, पूर्णांक reg,
					       u32 *val)
अणु
	वापस wlcore_raw_पढ़ो32(wl,
				 wlcore_translate_addr(wl, wl->rtable[reg]),
				 val);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check wlcore_ग_लिखो_reg(काष्ठा wl1271 *wl, पूर्णांक reg,
						u32 val)
अणु
	वापस wlcore_raw_ग_लिखो32(wl,
				  wlcore_translate_addr(wl, wl->rtable[reg]),
				  val);
पूर्ण

अटल अंतरभूत व्योम wl1271_घातer_off(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret = 0;

	अगर (!test_bit(WL1271_FLAG_GPIO_POWER, &wl->flags))
		वापस;

	अगर (wl->अगर_ops->घातer)
		ret = wl->अगर_ops->घातer(wl->dev, false);
	अगर (!ret)
		clear_bit(WL1271_FLAG_GPIO_POWER, &wl->flags);
पूर्ण

अटल अंतरभूत पूर्णांक wl1271_घातer_on(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret = 0;

	अगर (wl->अगर_ops->घातer)
		ret = wl->अगर_ops->घातer(wl->dev, true);
	अगर (ret == 0)
		set_bit(WL1271_FLAG_GPIO_POWER, &wl->flags);

	वापस ret;
पूर्ण

पूर्णांक wlcore_set_partition(काष्ठा wl1271 *wl,
			 स्थिर काष्ठा wlcore_partition_set *p);

bool wl1271_set_block_size(काष्ठा wl1271 *wl);

/* Functions from wl1271_मुख्य.c */

पूर्णांक wl1271_tx_dummy_packet(काष्ठा wl1271 *wl);

#पूर्ण_अगर
