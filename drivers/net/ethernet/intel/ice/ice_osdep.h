<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2018, Intel Corporation. */

#अगर_अघोषित _ICE_OSDEP_H_
#घोषणा _ICE_OSDEP_H_

#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#अगर_अघोषित CONFIG_64BIT
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#पूर्ण_अगर

#घोषणा wr32(a, reg, value)	ग_लिखोl((value), ((a)->hw_addr + (reg)))
#घोषणा rd32(a, reg)		पढ़ोl((a)->hw_addr + (reg))
#घोषणा wr64(a, reg, value)	ग_लिखोq((value), ((a)->hw_addr + (reg)))
#घोषणा rd64(a, reg)		पढ़ोq((a)->hw_addr + (reg))

#घोषणा ice_flush(a)		rd32((a), GLGEN_STAT)
#घोषणा ICE_M(m, s)		((m) << (s))

काष्ठा ice_dma_mem अणु
	व्योम *va;
	dma_addr_t pa;
	माप_प्रकार size;
पूर्ण;

#घोषणा ice_hw_to_dev(ptr)	\
	(&(container_of((ptr), काष्ठा ice_pf, hw))->pdev->dev)

#अगर_घोषित CONFIG_DYNAMIC_DEBUG
#घोषणा ice_debug(hw, type, fmt, args...) \
	dev_dbg(ice_hw_to_dev(hw), fmt, ##args)

#घोषणा ice_debug_array(hw, type, rowsize, groupsize, buf, len) \
	prपूर्णांक_hex_dump_debug(KBUILD_MODNAME " ",		\
			     DUMP_PREFIX_OFFSET, rowsize,	\
			     groupsize, buf, len, false)
#अन्यथा
#घोषणा ice_debug(hw, type, fmt, args...)			\
करो अणु								\
	अगर ((type) & (hw)->debug_mask)				\
		dev_info(ice_hw_to_dev(hw), fmt, ##args);	\
पूर्ण जबतक (0)

#अगर_घोषित DEBUG
#घोषणा ice_debug_array(hw, type, rowsize, groupsize, buf, len) \
करो अणु								\
	अगर ((type) & (hw)->debug_mask)				\
		prपूर्णांक_hex_dump_debug(KBUILD_MODNAME,		\
				     DUMP_PREFIX_OFFSET,	\
				     rowsize, groupsize, buf,	\
				     len, false);		\
पूर्ण जबतक (0)
#अन्यथा
#घोषणा ice_debug_array(hw, type, rowsize, groupsize, buf, len) \
करो अणु								\
	काष्ठा ice_hw *hw_l = hw;				\
	अगर ((type) & (hw_l)->debug_mask) अणु			\
		u16 len_l = len;				\
		u8 *buf_l = buf;				\
		पूर्णांक i;						\
		क्रम (i = 0; i < (len_l - 16); i += 16)		\
			ice_debug(hw_l, type, "0x%04X  %16ph\n",\
				  i, ((buf_l) + i));		\
		अगर (i < len_l)					\
			ice_debug(hw_l, type, "0x%04X  %*ph\n", \
				  i, ((len_l) - i), ((buf_l) + i));\
	पूर्ण							\
पूर्ण जबतक (0)
#पूर्ण_अगर /* DEBUG */
#पूर्ण_अगर /* CONFIG_DYNAMIC_DEBUG */

#पूर्ण_अगर /* _ICE_OSDEP_H_ */
