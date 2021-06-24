<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* include/net/ax88796.h
 *
 * Copyright 2005 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
*/

#अगर_अघोषित __NET_AX88796_PLAT_H
#घोषणा __NET_AX88796_PLAT_H

काष्ठा sk_buff;
काष्ठा net_device;
काष्ठा platक्रमm_device;

#घोषणा AXFLG_HAS_EEPROM		(1<<0)
#घोषणा AXFLG_MAC_FROMDEV		(1<<1)	/* device alपढ़ोy has MAC */
#घोषणा AXFLG_HAS_93CX6			(1<<2)	/* use eeprom_93cx6 driver */
#घोषणा AXFLG_MAC_FROMPLATFORM		(1<<3)	/* MAC given by platक्रमm data */

काष्ठा ax_plat_data अणु
	अचिन्हित पूर्णांक	 flags;
	अचिन्हित अक्षर	 wordlength;	/* 1 or 2 */
	अचिन्हित अक्षर	 dcr_val;	/* शेष value क्रम DCR */
	अचिन्हित अक्षर	 rcr_val;	/* शेष value क्रम RCR */
	अचिन्हित अक्षर	 gpoc_val;	/* शेष value क्रम GPOC */
	u32		*reg_offsets;	/* रेजिस्टर offsets */
	u8		*mac_addr;	/* MAC addr (only used when
					   AXFLG_MAC_FROMPLATFORM is used */

	/* uses शेष ax88796 buffer अगर set to शून्य */
	व्योम (*block_output)(काष्ठा net_device *dev, पूर्णांक count,
			स्थिर अचिन्हित अक्षर *buf, पूर्णांक star_page);
	व्योम (*block_input)(काष्ठा net_device *dev, पूर्णांक count,
			काष्ठा sk_buff *skb, पूर्णांक ring_offset);
	/* वापसs nonzero अगर a pending पूर्णांकerrupt request might by caused by
	 * the ax88786. Handles all पूर्णांकerrupts अगर set to शून्य
	 */
	पूर्णांक (*check_irq)(काष्ठा platक्रमm_device *pdev);
पूर्ण;

#पूर्ण_अगर /* __NET_AX88796_PLAT_H */
