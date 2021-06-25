<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*******************************************************************************
  Header File to describe Normal/enhanced descriptor functions used क्रम RING
  and CHAINED modes.

  Copyright(C) 2011  STMicroelectronics Ltd

  It defines all the functions used to handle the normal/enhanced
  descriptors in हाल of the DMA is configured to work in chained or
  in ring mode.


  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
*******************************************************************************/

#अगर_अघोषित __DESC_COM_H__
#घोषणा __DESC_COM_H__

/* Specअगरic functions used क्रम Ring mode */

/* Enhanced descriptors */
अटल अंतरभूत व्योम ehn_desc_rx_set_on_ring(काष्ठा dma_desc *p, पूर्णांक end,
					   पूर्णांक bfsize)
अणु
	अगर (bfsize == BUF_SIZE_16KiB)
		p->des1 |= cpu_to_le32((BUF_SIZE_8KiB
				<< ERDES1_BUFFER2_SIZE_SHIFT)
			   & ERDES1_BUFFER2_SIZE_MASK);

	अगर (end)
		p->des1 |= cpu_to_le32(ERDES1_END_RING);
पूर्ण

अटल अंतरभूत व्योम enh_desc_end_tx_desc_on_ring(काष्ठा dma_desc *p, पूर्णांक end)
अणु
	अगर (end)
		p->des0 |= cpu_to_le32(ETDES0_END_RING);
	अन्यथा
		p->des0 &= cpu_to_le32(~ETDES0_END_RING);
पूर्ण

अटल अंतरभूत व्योम enh_set_tx_desc_len_on_ring(काष्ठा dma_desc *p, पूर्णांक len)
अणु
	अगर (unlikely(len > BUF_SIZE_4KiB)) अणु
		p->des1 |= cpu_to_le32((((len - BUF_SIZE_4KiB)
					<< ETDES1_BUFFER2_SIZE_SHIFT)
			    & ETDES1_BUFFER2_SIZE_MASK) | (BUF_SIZE_4KiB
			    & ETDES1_BUFFER1_SIZE_MASK));
	पूर्ण अन्यथा
		p->des1 |= cpu_to_le32((len & ETDES1_BUFFER1_SIZE_MASK));
पूर्ण

/* Normal descriptors */
अटल अंतरभूत व्योम ndesc_rx_set_on_ring(काष्ठा dma_desc *p, पूर्णांक end, पूर्णांक bfsize)
अणु
	अगर (bfsize >= BUF_SIZE_2KiB) अणु
		पूर्णांक bfsize2;

		bfsize2 = min(bfsize - BUF_SIZE_2KiB + 1, BUF_SIZE_2KiB - 1);
		p->des1 |= cpu_to_le32((bfsize2 << RDES1_BUFFER2_SIZE_SHIFT)
			    & RDES1_BUFFER2_SIZE_MASK);
	पूर्ण

	अगर (end)
		p->des1 |= cpu_to_le32(RDES1_END_RING);
पूर्ण

अटल अंतरभूत व्योम ndesc_end_tx_desc_on_ring(काष्ठा dma_desc *p, पूर्णांक end)
अणु
	अगर (end)
		p->des1 |= cpu_to_le32(TDES1_END_RING);
	अन्यथा
		p->des1 &= cpu_to_le32(~TDES1_END_RING);
पूर्ण

अटल अंतरभूत व्योम norm_set_tx_desc_len_on_ring(काष्ठा dma_desc *p, पूर्णांक len)
अणु
	अगर (unlikely(len > BUF_SIZE_2KiB)) अणु
		अचिन्हित पूर्णांक buffer1 = (BUF_SIZE_2KiB - 1)
					& TDES1_BUFFER1_SIZE_MASK;
		p->des1 |= cpu_to_le32((((len - buffer1)
					<< TDES1_BUFFER2_SIZE_SHIFT)
				& TDES1_BUFFER2_SIZE_MASK) | buffer1);
	पूर्ण अन्यथा
		p->des1 |= cpu_to_le32((len & TDES1_BUFFER1_SIZE_MASK));
पूर्ण

/* Specअगरic functions used क्रम Chain mode */

/* Enhanced descriptors */
अटल अंतरभूत व्योम ehn_desc_rx_set_on_chain(काष्ठा dma_desc *p)
अणु
	p->des1 |= cpu_to_le32(ERDES1_SECOND_ADDRESS_CHAINED);
पूर्ण

अटल अंतरभूत व्योम enh_desc_end_tx_desc_on_chain(काष्ठा dma_desc *p)
अणु
	p->des0 |= cpu_to_le32(ETDES0_SECOND_ADDRESS_CHAINED);
पूर्ण

अटल अंतरभूत व्योम enh_set_tx_desc_len_on_chain(काष्ठा dma_desc *p, पूर्णांक len)
अणु
	p->des1 |= cpu_to_le32(len & ETDES1_BUFFER1_SIZE_MASK);
पूर्ण

/* Normal descriptors */
अटल अंतरभूत व्योम ndesc_rx_set_on_chain(काष्ठा dma_desc *p, पूर्णांक end)
अणु
	p->des1 |= cpu_to_le32(RDES1_SECOND_ADDRESS_CHAINED);
पूर्ण

अटल अंतरभूत व्योम ndesc_tx_set_on_chain(काष्ठा dma_desc *p)
अणु
	p->des1 |= cpu_to_le32(TDES1_SECOND_ADDRESS_CHAINED);
पूर्ण

अटल अंतरभूत व्योम norm_set_tx_desc_len_on_chain(काष्ठा dma_desc *p, पूर्णांक len)
अणु
	p->des1 |= cpu_to_le32(len & TDES1_BUFFER1_SIZE_MASK);
पूर्ण
#पूर्ण_अगर /* __DESC_COM_H__ */
