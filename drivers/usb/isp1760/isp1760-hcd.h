<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ISP1760_HCD_H_
#घोषणा _ISP1760_HCD_H_

#समावेश <linux/spinlock.h>

काष्ठा isp1760_qh;
काष्ठा isp1760_qtd;
काष्ठा resource;
काष्ठा usb_hcd;

/*
 * 60kb भागided in:
 * - 32 blocks @ 256  bytes
 * - 20 blocks @ 1024 bytes
 * -  4 blocks @ 8192 bytes
 */

#घोषणा BLOCK_1_NUM 32
#घोषणा BLOCK_2_NUM 20
#घोषणा BLOCK_3_NUM 4

#घोषणा BLOCK_1_SIZE 256
#घोषणा BLOCK_2_SIZE 1024
#घोषणा BLOCK_3_SIZE 8192
#घोषणा BLOCKS (BLOCK_1_NUM + BLOCK_2_NUM + BLOCK_3_NUM)
#घोषणा MAX_PAYLOAD_SIZE BLOCK_3_SIZE
#घोषणा PAYLOAD_AREA_SIZE 0xf000

काष्ठा isp1760_slotinfo अणु
	काष्ठा isp1760_qh *qh;
	काष्ठा isp1760_qtd *qtd;
	अचिन्हित दीर्घ बारtamp;
पूर्ण;

/* chip memory management */
काष्ठा isp1760_memory_chunk अणु
	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक मुक्त;
पूर्ण;

क्रमागत isp1760_queue_head_types अणु
	QH_CONTROL,
	QH_BULK,
	QH_INTERRUPT,
	QH_END
पूर्ण;

काष्ठा isp1760_hcd अणु
#अगर_घोषित CONFIG_USB_ISP1760_HCD
	काष्ठा usb_hcd		*hcd;

	u32 hcs_params;
	spinlock_t		lock;
	काष्ठा isp1760_slotinfo	atl_slots[32];
	पूर्णांक			atl_करोne_map;
	काष्ठा isp1760_slotinfo	पूर्णांक_slots[32];
	पूर्णांक			पूर्णांक_करोne_map;
	काष्ठा isp1760_memory_chunk memory_pool[BLOCKS];
	काष्ठा list_head	qh_list[QH_END];

	/* periodic schedule support */
#घोषणा	DEFAULT_I_TDPS		1024
	अचिन्हित		periodic_size;
	अचिन्हित		i_thresh;
	अचिन्हित दीर्घ		reset_करोne;
	अचिन्हित दीर्घ		next_statechange;
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_USB_ISP1760_HCD
पूर्णांक isp1760_hcd_रेजिस्टर(काष्ठा isp1760_hcd *priv, व्योम __iomem *regs,
			 काष्ठा resource *mem, पूर्णांक irq, अचिन्हित दीर्घ irqflags,
			 काष्ठा device *dev);
व्योम isp1760_hcd_unरेजिस्टर(काष्ठा isp1760_hcd *priv);

पूर्णांक isp1760_init_kmem_once(व्योम);
व्योम isp1760_deinit_kmem_cache(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक isp1760_hcd_रेजिस्टर(काष्ठा isp1760_hcd *priv,
				       व्योम __iomem *regs, काष्ठा resource *mem,
				       पूर्णांक irq, अचिन्हित दीर्घ irqflags,
				       काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम isp1760_hcd_unरेजिस्टर(काष्ठा isp1760_hcd *priv)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक isp1760_init_kmem_once(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम isp1760_deinit_kmem_cache(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ISP1760_HCD_H_ */
