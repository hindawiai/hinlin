<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl12xx
 *
 * Copyright (C) 2008 Nokia Corporation
 */
#अगर_अघोषित __WL1251_IO_H__
#घोषणा __WL1251_IO_H__

#समावेश "wl1251.h"

#घोषणा HW_ACCESS_MEMORY_MAX_RANGE		0x1FFC0

#घोषणा HW_ACCESS_PART0_SIZE_ADDR           0x1FFC0
#घोषणा HW_ACCESS_PART0_START_ADDR          0x1FFC4
#घोषणा HW_ACCESS_PART1_SIZE_ADDR           0x1FFC8
#घोषणा HW_ACCESS_PART1_START_ADDR          0x1FFCC

#घोषणा HW_ACCESS_REGISTER_SIZE             4

#घोषणा HW_ACCESS_PRAM_MAX_RANGE		0x3c000

अटल अंतरभूत u32 wl1251_पढ़ो32(काष्ठा wl1251 *wl, पूर्णांक addr)
अणु
	wl->अगर_ops->पढ़ो(wl, addr, &wl->buffer_32, माप(wl->buffer_32));

	वापस le32_to_cpu(wl->buffer_32);
पूर्ण

अटल अंतरभूत व्योम wl1251_ग_लिखो32(काष्ठा wl1251 *wl, पूर्णांक addr, u32 val)
अणु
	wl->buffer_32 = cpu_to_le32(val);
	wl->अगर_ops->ग_लिखो(wl, addr, &wl->buffer_32, माप(wl->buffer_32));
पूर्ण

अटल अंतरभूत u32 wl1251_पढ़ो_elp(काष्ठा wl1251 *wl, पूर्णांक addr)
अणु
	u32 response;

	अगर (wl->अगर_ops->पढ़ो_elp)
		wl->अगर_ops->पढ़ो_elp(wl, addr, &response);
	अन्यथा
		wl->अगर_ops->पढ़ो(wl, addr, &response, माप(u32));

	वापस response;
पूर्ण

अटल अंतरभूत व्योम wl1251_ग_लिखो_elp(काष्ठा wl1251 *wl, पूर्णांक addr, u32 val)
अणु
	अगर (wl->अगर_ops->ग_लिखो_elp)
		wl->अगर_ops->ग_लिखो_elp(wl, addr, val);
	अन्यथा
		wl->अगर_ops->ग_लिखो(wl, addr, &val, माप(u32));
पूर्ण

/* Memory target IO, address is translated to partition 0 */
व्योम wl1251_mem_पढ़ो(काष्ठा wl1251 *wl, पूर्णांक addr, व्योम *buf, माप_प्रकार len);
व्योम wl1251_mem_ग_लिखो(काष्ठा wl1251 *wl, पूर्णांक addr, व्योम *buf, माप_प्रकार len);
u32 wl1251_mem_पढ़ो32(काष्ठा wl1251 *wl, पूर्णांक addr);
व्योम wl1251_mem_ग_लिखो32(काष्ठा wl1251 *wl, पूर्णांक addr, u32 val);
/* Registers IO */
u32 wl1251_reg_पढ़ो32(काष्ठा wl1251 *wl, पूर्णांक addr);
व्योम wl1251_reg_ग_लिखो32(काष्ठा wl1251 *wl, पूर्णांक addr, u32 val);

व्योम wl1251_set_partition(काष्ठा wl1251 *wl,
			  u32 part_start, u32 part_size,
			  u32 reg_start,  u32 reg_size);

#पूर्ण_अगर
