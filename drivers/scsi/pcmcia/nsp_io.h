<शैली गुरु>
/*
  NinjaSCSI I/O funtions 
      By: YOKOTA Hiroshi <yokota@netlab.is.tsukuba.ac.jp>
 
  This software may be used and distributed according to the terms of
  the GNU General Public License.

  */

/* $Id: nsp_पन.स,v 1.3 2003/08/04 21:15:26 elca Exp $ */

#अगर_अघोषित __NSP_IO_H__
#घोषणा __NSP_IO_H__

अटल अंतरभूत          व्योम nsp_ग_लिखो(अचिन्हित पूर्णांक base,
				      अचिन्हित पूर्णांक index,
				      अचिन्हित अक्षर val);
अटल अंतरभूत अचिन्हित अक्षर nsp_पढ़ो(अचिन्हित पूर्णांक base,
				     अचिन्हित पूर्णांक index);
अटल अंतरभूत          व्योम nsp_index_ग_लिखो(अचिन्हित पूर्णांक BaseAddr,
					    अचिन्हित पूर्णांक Register,
					    अचिन्हित अक्षर Value);
अटल अंतरभूत अचिन्हित अक्षर nsp_index_पढ़ो(अचिन्हित पूर्णांक BaseAddr,
					   अचिन्हित पूर्णांक Register);

/*******************************************************************
 * Basic IO
 */

अटल अंतरभूत व्योम nsp_ग_लिखो(अचिन्हित पूर्णांक  base,
			     अचिन्हित पूर्णांक  index,
			     अचिन्हित अक्षर val)
अणु
	outb(val, (base + index));
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर nsp_पढ़ो(अचिन्हित पूर्णांक base,
				     अचिन्हित पूर्णांक index)
अणु
	वापस inb(base + index);
पूर्ण


/**********************************************************************
 * Indexed IO
 */
अटल अंतरभूत अचिन्हित अक्षर nsp_index_पढ़ो(अचिन्हित पूर्णांक BaseAddr,
					   अचिन्हित पूर्णांक Register)
अणु
	outb(Register, BaseAddr + INDEXREG);
	वापस inb(BaseAddr + DATAREG);
पूर्ण

अटल अंतरभूत व्योम nsp_index_ग_लिखो(अचिन्हित पूर्णांक  BaseAddr,
				   अचिन्हित पूर्णांक  Register,
				   अचिन्हित अक्षर Value)
अणु
	outb(Register, BaseAddr + INDEXREG);
	outb(Value, BaseAddr + DATAREG);
पूर्ण

/*********************************************************************
 * fअगरo func
 */

/* पढ़ो 8 bit FIFO */
अटल अंतरभूत व्योम nsp_multi_पढ़ो_1(अचिन्हित पूर्णांक   BaseAddr,
				    अचिन्हित पूर्णांक   Register,
				    व्योम          *buf,
				    अचिन्हित दीर्घ  count)
अणु
	insb(BaseAddr + Register, buf, count);
पूर्ण

अटल अंतरभूत व्योम nsp_fअगरo8_पढ़ो(अचिन्हित पूर्णांक   base,
				  व्योम          *buf,
				  अचिन्हित दीर्घ  count)
अणु
	/*nsp_dbg(NSP_DEBUG_DATA_IO, "buf=0x%p, count=0x%lx", buf, count);*/
	nsp_multi_पढ़ो_1(base, FIFODATA, buf, count);
पूर्ण

/*--------------------------------------------------------------*/

/* पढ़ो 16 bit FIFO */
अटल अंतरभूत व्योम nsp_multi_पढ़ो_2(अचिन्हित पूर्णांक   BaseAddr,
				    अचिन्हित पूर्णांक   Register,
				    व्योम          *buf,
				    अचिन्हित दीर्घ  count)
अणु
	insw(BaseAddr + Register, buf, count);
पूर्ण

अटल अंतरभूत व्योम nsp_fअगरo16_पढ़ो(अचिन्हित पूर्णांक   base,
				   व्योम          *buf,
				   अचिन्हित दीर्घ  count)
अणु
	//nsp_dbg(NSP_DEBUG_DATA_IO, "buf=0x%p, count=0x%lx*2", buf, count);
	nsp_multi_पढ़ो_2(base, FIFODATA, buf, count);
पूर्ण

/*--------------------------------------------------------------*/

/* पढ़ो 32bit FIFO */
अटल अंतरभूत व्योम nsp_multi_पढ़ो_4(अचिन्हित पूर्णांक   BaseAddr,
				    अचिन्हित पूर्णांक   Register,
				    व्योम          *buf,
				    अचिन्हित दीर्घ  count)
अणु
	insl(BaseAddr + Register, buf, count);
पूर्ण

अटल अंतरभूत व्योम nsp_fअगरo32_पढ़ो(अचिन्हित पूर्णांक   base,
				   व्योम          *buf,
				   अचिन्हित दीर्घ  count)
अणु
	//nsp_dbg(NSP_DEBUG_DATA_IO, "buf=0x%p, count=0x%lx*4", buf, count);
	nsp_multi_पढ़ो_4(base, FIFODATA, buf, count);
पूर्ण

/*----------------------------------------------------------*/

/* ग_लिखो 8bit FIFO */
अटल अंतरभूत व्योम nsp_multi_ग_लिखो_1(अचिन्हित पूर्णांक   BaseAddr,
				     अचिन्हित पूर्णांक   Register,
				     व्योम          *buf,
				     अचिन्हित दीर्घ  count)
अणु
	outsb(BaseAddr + Register, buf, count);
पूर्ण

अटल अंतरभूत व्योम nsp_fअगरo8_ग_लिखो(अचिन्हित पूर्णांक   base,
				   व्योम          *buf,
				   अचिन्हित दीर्घ  count)
अणु
	nsp_multi_ग_लिखो_1(base, FIFODATA, buf, count);
पूर्ण

/*---------------------------------------------------------*/

/* ग_लिखो 16bit FIFO */
अटल अंतरभूत व्योम nsp_multi_ग_लिखो_2(अचिन्हित पूर्णांक   BaseAddr,
				     अचिन्हित पूर्णांक   Register,
				     व्योम          *buf,
				     अचिन्हित दीर्घ  count)
अणु
	outsw(BaseAddr + Register, buf, count);
पूर्ण

अटल अंतरभूत व्योम nsp_fअगरo16_ग_लिखो(अचिन्हित पूर्णांक   base,
				    व्योम          *buf,
				    अचिन्हित दीर्घ  count)
अणु
	nsp_multi_ग_लिखो_2(base, FIFODATA, buf, count);
पूर्ण

/*---------------------------------------------------------*/

/* ग_लिखो 32bit FIFO */
अटल अंतरभूत व्योम nsp_multi_ग_लिखो_4(अचिन्हित पूर्णांक   BaseAddr,
				     अचिन्हित पूर्णांक   Register,
				     व्योम          *buf,
				     अचिन्हित दीर्घ  count)
अणु
	outsl(BaseAddr + Register, buf, count);
पूर्ण

अटल अंतरभूत व्योम nsp_fअगरo32_ग_लिखो(अचिन्हित पूर्णांक   base,
				    व्योम          *buf,
				    अचिन्हित दीर्घ  count)
अणु
	nsp_multi_ग_लिखो_4(base, FIFODATA, buf, count);
पूर्ण


/*====================================================================*/

अटल अंतरभूत व्योम nsp_mmio_ग_लिखो(अचिन्हित दीर्घ base,
				  अचिन्हित पूर्णांक  index,
				  अचिन्हित अक्षर val)
अणु
	अचिन्हित अक्षर *ptr = (अचिन्हित अक्षर *)(base + NSP_MMIO_OFFSET + index);

	ग_लिखोb(val, ptr);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर nsp_mmio_पढ़ो(अचिन्हित दीर्घ base,
					  अचिन्हित पूर्णांक  index)
अणु
	अचिन्हित अक्षर *ptr = (अचिन्हित अक्षर *)(base + NSP_MMIO_OFFSET + index);

	वापस पढ़ोb(ptr);
पूर्ण

/*-----------*/

अटल अंतरभूत अचिन्हित अक्षर nsp_mmio_index_पढ़ो(अचिन्हित दीर्घ base,
						अचिन्हित पूर्णांक  reg)
अणु
	अचिन्हित अक्षर *index_ptr = (अचिन्हित अक्षर *)(base + NSP_MMIO_OFFSET + INDEXREG);
	अचिन्हित अक्षर *data_ptr  = (अचिन्हित अक्षर *)(base + NSP_MMIO_OFFSET + DATAREG);

	ग_लिखोb((अचिन्हित अक्षर)reg, index_ptr);
	वापस पढ़ोb(data_ptr);
पूर्ण

अटल अंतरभूत व्योम nsp_mmio_index_ग_लिखो(अचिन्हित दीर्घ base,
					अचिन्हित पूर्णांक  reg,
					अचिन्हित अक्षर val)
अणु
	अचिन्हित अक्षर *index_ptr = (अचिन्हित अक्षर *)(base + NSP_MMIO_OFFSET + INDEXREG);
	अचिन्हित अक्षर *data_ptr  = (अचिन्हित अक्षर *)(base + NSP_MMIO_OFFSET + DATAREG);

	ग_लिखोb((अचिन्हित अक्षर)reg, index_ptr);
	ग_लिखोb(val,                data_ptr);
पूर्ण

/* पढ़ो 32bit FIFO */
अटल अंतरभूत व्योम nsp_mmio_multi_पढ़ो_4(अचिन्हित दीर्घ  base,
					 अचिन्हित पूर्णांक   Register,
					 व्योम          *buf,
					 अचिन्हित दीर्घ  count)
अणु
	अचिन्हित दीर्घ *ptr = (अचिन्हित दीर्घ *)(base + Register);
	अचिन्हित दीर्घ *पंचांगp = (अचिन्हित दीर्घ *)buf;
	पूर्णांक i;

	//nsp_dbg(NSP_DEBUG_DATA_IO, "base 0x%0lx ptr 0x%p",base,ptr);

	क्रम (i = 0; i < count; i++) अणु
		*पंचांगp = पढ़ोl(ptr);
		//nsp_dbg(NSP_DEBUG_DATA_IO, "<%d,%p,%p,%lx>", i, ptr, पंचांगp, *पंचांगp);
		पंचांगp++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम nsp_mmio_fअगरo32_पढ़ो(अचिन्हित पूर्णांक   base,
					व्योम          *buf,
					अचिन्हित दीर्घ  count)
अणु
	//nsp_dbg(NSP_DEBUG_DATA_IO, "buf=0x%p, count=0x%lx*4", buf, count);
	nsp_mmio_multi_पढ़ो_4(base, FIFODATA, buf, count);
पूर्ण

अटल अंतरभूत व्योम nsp_mmio_multi_ग_लिखो_4(अचिन्हित दीर्घ  base,
					  अचिन्हित पूर्णांक   Register,
					  व्योम          *buf,
					  अचिन्हित दीर्घ  count)
अणु
	अचिन्हित दीर्घ *ptr = (अचिन्हित दीर्घ *)(base + Register);
	अचिन्हित दीर्घ *पंचांगp = (अचिन्हित दीर्घ *)buf;
	पूर्णांक i;

	//nsp_dbg(NSP_DEBUG_DATA_IO, "base 0x%0lx ptr 0x%p",base,ptr);

	क्रम (i = 0; i < count; i++) अणु
		ग_लिखोl(*पंचांगp, ptr);
		//nsp_dbg(NSP_DEBUG_DATA_IO, "<%d,%p,%p,%lx>", i, ptr, पंचांगp, *पंचांगp);
		पंचांगp++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम nsp_mmio_fअगरo32_ग_लिखो(अचिन्हित पूर्णांक   base,
					 व्योम          *buf,
					 अचिन्हित दीर्घ  count)
अणु
	//nsp_dbg(NSP_DEBUG_DATA_IO, "buf=0x%p, count=0x%lx*4", buf, count);
	nsp_mmio_multi_ग_लिखो_4(base, FIFODATA, buf, count);
पूर्ण



#पूर्ण_अगर
/* end */
